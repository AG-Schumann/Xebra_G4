//XEBRA header files
#include "XebraPrimaryGeneratorMessenger.hh"
#include "XebraPrimaryGeneratorAction.hh"

//Additional Header Files
#include <fstream>
#include <iomanip>

//G4 Header Files
#include <G4Geantino.hh>
#include <G4ThreeVector.hh>
#include <G4ParticleTable.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithABool.hh>
#include <G4Tokenizer.hh>
#include <G4ios.hh>


XebraPrimaryGeneratorMessenger::XebraPrimaryGeneratorMessenger(XebraPrimaryGeneratorAction *pPrimaryGeneratorAction):
  m_pPrimaryGeneratorAction(pPrimaryGeneratorAction)
{
  G4cout <<"XebraPrimaryGeneratorMessenger:: Define Primary Generator I/O"<<G4endl;
  // create directory
  m_pDirectory = new G4UIdirectory("/run/forced/");
  m_pDirectory->SetGuidance("Primary generator control commands.");

  // do we want to do forced transport?
  m_pVarianceReductionCmd = new G4UIcmdWithABool("/run/forced/setVarianceReduction", this);
  m_pVarianceReductionCmd->SetGuidance("In case of a gamma MC you can choose to use a variance reduction algorithm");
  G4bool transportDef = false;
  m_pVarianceReductionCmd->SetDefaultValue(transportDef);

  // variance reduction mode
  m_pVarianceReductionModeCmd = new G4UIcmdWithAnInteger("/run/forced/setVarianceReductionMode", this);
  m_pVarianceReductionModeCmd->SetGuidance("Select the mode of variance reduction");
  m_pVarianceReductionModeCmd->SetGuidance(" 0 - kills gammas not hitting the target cylinder AND gammas with p<cut (default)");
  m_pVarianceReductionModeCmd->SetGuidance(" 1 - kills gammas not hitting the target cylinder AND weight russian roulette (TBD)");
  m_pVarianceReductionModeCmd->SetGuidance(" 2 - as option 0 + Forced Transport to target cylinder");
  m_pVarianceReductionModeCmd->SetGuidance(" 3 - as option 0 + Forced Transport to random location on path to target cylinder");
  m_pVarianceReductionModeCmd->SetDefaultValue(0);

  // cut on gamma survival probability
  p_survival_cutCmd = new G4UIcmdWithADouble("/run/forced/setSurvivalProbabilityCut",this);
  p_survival_cutCmd->SetGuidance("Cut on gamma probability to reach target cylinder");
  p_survival_cutCmd->SetParameterName("P",true,true);
  p_survival_cutCmd->SetDefaultValue(0.);

  //
  // Define the target area for forced transportation and gamma killing studies
  //
  ft_positionCmd = new G4UIcmdWith3VectorAndUnit("/run/forced/ft_cyl_center",this);
  ft_positionCmd->SetGuidance("Set center of forced transport target cylinder.");
  ft_positionCmd->SetParameterName("X","Y","Z",true,true);
  ft_positionCmd->SetDefaultUnit("cm");
  ft_positionCmd->SetUnitCandidates("micron mm cm m km");

  ft_lengthCmd = new G4UIcmdWithADoubleAndUnit("/run/forced/ft_cyl_length",this);
  ft_lengthCmd->SetGuidance("Set length of forced transport target cylinder.");
  ft_lengthCmd->SetParameterName("L",true,true);
  ft_lengthCmd->SetDefaultUnit("cm");
  ft_lengthCmd->SetUnitCandidates("micron mm cm m km");

  ft_radiusCmd = new G4UIcmdWithADoubleAndUnit("/run/forced/ft_cyl_radius",this);
  ft_radiusCmd->SetGuidance("Set radius of forced transport target cylinder.");
  ft_radiusCmd->SetParameterName("L",true,true);
  ft_radiusCmd->SetDefaultUnit("cm");
  ft_radiusCmd->SetUnitCandidates("micron mm cm m km");
  
  // write empty events to file or not  
  m_pWriteEmptyCmd = new G4UIcmdWithABool("/run/writeEmpty", this);
  m_pWriteEmptyCmd->SetGuidance("Write empty events to the root tree true/false");
  m_pWriteEmptyCmd->SetDefaultValue(false);
//  m_pWriteEmptyCmd->AvailableForStates(G4State_PreInit);
}

XebraPrimaryGeneratorMessenger::~XebraPrimaryGeneratorMessenger()
{
  delete m_pDirectory;
}

void
XebraPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command, G4String newValues)
{
  if(command == m_pVarianceReductionCmd) 
    m_pPrimaryGeneratorAction->SetVarianceReduction(m_pVarianceReductionCmd->GetNewBoolValue(newValues));
  if(command == m_pVarianceReductionModeCmd) 
    m_pPrimaryGeneratorAction->SetVarianceReductionMode(m_pVarianceReductionModeCmd->GetNewIntValue(newValues));
  if(command == p_survival_cutCmd) 
    m_pPrimaryGeneratorAction->SetSurvivalProbabilityCut(p_survival_cutCmd->GetNewDoubleValue(newValues));
  if(command == ft_positionCmd) 
    m_pPrimaryGeneratorAction->SetFT_cyl_center(ft_positionCmd->GetNew3VectorValue(newValues));
  if(command == ft_lengthCmd) 
    m_pPrimaryGeneratorAction->SetFT_cyl_length(ft_lengthCmd->GetNewDoubleValue(newValues));
  if(command == ft_radiusCmd) 
    m_pPrimaryGeneratorAction->SetFT_cyl_radius(ft_radiusCmd->GetNewDoubleValue(newValues));
  if(command == m_pWriteEmptyCmd) 
    m_pPrimaryGeneratorAction->SetWriteEmpty(m_pWriteEmptyCmd->GetNewBoolValue(newValues));
}


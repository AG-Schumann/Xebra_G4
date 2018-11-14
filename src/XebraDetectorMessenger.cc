//XENON Header Files
#include "XebraDetectorMessenger.hh"
#include "XebraDetectorConstruction.hh"

//Additional Header Files
#include <fstream>
#include <iomanip>

//G4 Header Files
#include <G4UnitsTable.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
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
#include <G4SystemOfUnits.hh>

XebraDetectorMessenger::XebraDetectorMessenger(XebraDetectorConstruction *pXeDetector)
:m_pXeDetector(pXeDetector)
{
    
	m_pDetectorDir = new G4UIdirectory("/Xe/detector/");
	m_pDetectorDir->SetGuidance("detector control.");

	m_pTeflonReflectivityCmd = new G4UIcmdWithADouble("/Xe/detector/setTeflonReflectivity", this);
	m_pTeflonReflectivityCmd->SetGuidance("Define teflon reflectivity.");
	m_pTeflonReflectivityCmd->SetParameterName("R", false);
	m_pTeflonReflectivityCmd->SetRange("R >= 0. && R <= 1.");
  	m_pTeflonReflectivityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	m_pLXeScintillationCmd = new G4UIcmdWithABool("/Xe/detector/setLXeScintillation", this);
	m_pLXeScintillationCmd->SetGuidance("Switch on/off LXe scintillation in the sensitive volume.");
	m_pLXeScintillationCmd->SetParameterName("LXeScint", false); 
	m_pLXeScintillationCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	
	// DR 20160701 - Activation Gd-LS scintillation
	m_pGdLScintScintillationCmd = new G4UIcmdWithABool("/Xe/detector/setGdLScintScintillation", this);
	m_pGdLScintScintillationCmd->SetGuidance("Switch on/off GdLScint scintillation in the sensitive volume.");
	m_pGdLScintScintillationCmd->SetParameterName("GdLScintScint", false); 
	m_pGdLScintScintillationCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	m_pLXeAbsorbtionLengthCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setLXeAbsorbtionLength", this);
	m_pLXeAbsorbtionLengthCmd->SetGuidance("Define LXe absorbtion length.");
	m_pLXeAbsorbtionLengthCmd->SetParameterName("AbsL", false);
	m_pLXeAbsorbtionLengthCmd->SetRange("AbsL >= 0.");
	m_pLXeAbsorbtionLengthCmd->SetUnitCategory("Length");
	m_pLXeAbsorbtionLengthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	m_pLXeRayScatterLengthCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setLXeRayScatterLength", this);
	m_pLXeRayScatterLengthCmd->SetGuidance("Define LXe Rayleigh Scattering length.");
	m_pLXeRayScatterLengthCmd->SetParameterName("ScatL", false);
	m_pLXeRayScatterLengthCmd->SetRange("ScatL >= 0.");
	m_pLXeRayScatterLengthCmd->SetUnitCategory("Length");
	m_pLXeRayScatterLengthCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	
  // SERENA: you need  all commands below
	//
	// Selection for the cryostat design type.
	// For now there are two types: 
	//      1. standard = what was in the Xebra simulations already at 25-07-2011
	//      2. Nikhef   = following the Nikhef design
	//
	// A.P.Colijn 25-07-2011
	m_pCryostatTypeCmd = new G4UIcmdWithAString("/Xe/detector/setCryostatType", this);
	m_pCryostatTypeCmd->SetGuidance("Choice of cryostat geometry");
	m_pCryostatTypeCmd->SetParameterName("cryoType", false);
	m_pCryostatTypeCmd->AvailableForStates(G4State_PreInit);
	m_pCryostatTypeCmd->SetDefaultValue("Columbia");

	
	// cryostat material selector....
	m_pCryostatMaterialCmd = new G4UIcmdWithAString("/Xe/detector/setCryostatMaterial", this);
	m_pCryostatMaterialCmd->SetGuidance("Choice of cryostat geometry");
	m_pCryostatMaterialCmd->SetParameterName("cryoMaterial", false);
	m_pCryostatMaterialCmd->AvailableForStates(G4State_PreInit);
    
    // neutron source selector Andrew Brown 22/08/10
    m_pNeutronSourceSurroundingsCmd = new G4UIcmdWithAString("/Xe/detector/setNeutronSourceSurroundings", this);
    m_pNeutronSourceSurroundingsCmd->SetGuidance("Choice of neutron source surroungings: (1) LeadBrick (2) NeutronGenerator (3) None [default]");
    m_pNeutronSourceSurroundingsCmd->SetParameterName("neutSurr", false);
    m_pNeutronSourceSurroundingsCmd->SetDefaultValue("None");
    m_pNeutronSourceSurroundingsCmd->AvailableForStates(G4State_PreInit);
    		
	// cryostat outer vessel wall thickness 
  // APC put this back, because we want to play with the cryostat diameter+thickness
	G4double dOuterDefault = 0; //  mm
	m_pCryostatOuterWallCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setCryostatOuterWallThickness", this);
    m_pCryostatOuterWallCmd->SetGuidance("Wall thickness of outer cryostat vessel");
	m_pCryostatOuterWallCmd->SetParameterName("cryoOuterWallThickness", false);
    m_pCryostatOuterWallCmd->SetDefaultValue(dOuterDefault);
	m_pCryostatOuterWallCmd->SetUnitCategory("Length");
	m_pCryostatOuterWallCmd->SetDefaultUnit("mm");
	m_pCryostatOuterWallCmd->AvailableForStates(G4State_PreInit);
	
	// cryostat inner vessel wall thickness
	G4double dInnerDefault = 0; // mm
	m_pCryostatInnerWallCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setCryostatInnerWallThickness", this);
    m_pCryostatInnerWallCmd->SetGuidance("Wall thickness of inner cryostat vessel");
	m_pCryostatInnerWallCmd->SetParameterName("cryoInnerWallThickness", false);
	m_pCryostatInnerWallCmd->SetDefaultValue(dInnerDefault);
	m_pCryostatInnerWallCmd->SetUnitCategory("Length");
	m_pCryostatInnerWallCmd->SetDefaultUnit("mm");
	m_pCryostatInnerWallCmd->AvailableForStates(G4State_PreInit);

  // outer vessel wall thickness only with ColumbiaXL cryostat
  G4double dOuterODDefault = 0; //  mm
	m_pCryostatOuterODCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setCryostatOuterOD", this);
    m_pCryostatOuterODCmd->SetGuidance("OD of outer cryostat vessel");
	m_pCryostatOuterODCmd->SetParameterName("cryoOuterOD", false);
    m_pCryostatOuterODCmd->SetDefaultValue(dOuterODDefault);
	m_pCryostatOuterODCmd->SetUnitCategory("Length");
	m_pCryostatOuterODCmd->SetDefaultUnit("mm");
	m_pCryostatOuterODCmd->AvailableForStates(G4State_PreInit);
  // inner vessel wall thickness only with ColumbiaXL cryostat
  G4double dInnerODDefault = 0; //  mm
	m_pCryostatInnerODCmd = new G4UIcmdWithADoubleAndUnit("/Xe/detector/setCryostatInnerOD", this);
    m_pCryostatInnerODCmd->SetGuidance("OD of inner cryostat vessel");
	m_pCryostatInnerODCmd->SetParameterName("cryoInnerrOD", false);
    m_pCryostatInnerODCmd->SetDefaultValue(dInnerODDefault);
	m_pCryostatInnerODCmd->SetUnitCategory("Length");
	m_pCryostatInnerODCmd->SetDefaultUnit("mm");
	m_pCryostatInnerODCmd->AvailableForStates(G4State_PreInit);

  // check for overlapping objetcs
  m_pCheckOverlapCmd = new G4UIcmdWithABool("/xebra/detector/setCheckOverlap", this);
  m_pCheckOverlapCmd->SetGuidance("Check for overlapping objects in the geometry.");
  m_pCheckOverlapCmd->SetParameterName("CheckOverlap", false); 
  m_pCheckOverlapCmd->AvailableForStates(G4State_PreInit);

  m_pXeDetector->SetCheckOverlap(false);


  // run the simulation with / without TPC
  m_pSetTPCCmd = new G4UIcmdWithABool("/Xe/detector/setTPC", this);
  m_pSetTPCCmd->SetGuidance("Run the simulation with / without the TPC.");
  m_pSetTPCCmd->SetParameterName("TPC", true); 
  m_pSetTPCCmd->AvailableForStates(G4State_PreInit);
 
// cryostat inner vessel wall thickness 

}

XebraDetectorMessenger::~XebraDetectorMessenger()
{
  delete m_pCheckOverlapCmd;
}



void XebraDetectorMessenger::SetNewValue(G4UIcommand *pUIcommand, G4String hNewValue)
{
  if(pUIcommand == m_pCheckOverlapCmd)
	  m_pXeDetector->SetCheckOverlap(m_pCheckOverlapCmd->GetNewBoolValue(hNewValue));
}



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
#include <fstream>
#include <iomanip>

#include "XebraRunActionMessenger.hh"
#include "XebraRunAction.hh"

XebraRunActionMessenger::XebraRunActionMessenger(XebraRunAction *pRunAction):
m_pRunAction(pRunAction)
{
	// create directory
	m_pDirectory = new G4UIdirectory("/run/random/");
	m_pDirectory->SetGuidance("RunAction control commands.");

	// set particle  
	m_pRanSeedCmd = new G4UIcmdWithAnInteger("/run/random/setRandomSeed", this);
	m_pRanSeedCmd->SetGuidance("Random seed");
	G4int iDef = 12345;
	m_pRanSeedCmd->SetDefaultValue(iDef);

        // do we want to do forced transport
//	m_pForcedTransportCmd = new G4UIcmdWithABool("/run/setForcedTransport", this);
//	m_pForcedTransportCmd->SetGuidance("In case of a gamma MC you can choose to use a forced transport algorithm");
//	G4bool transportDef = false;
//	m_pForcedTransportCmd->SetDefaultValue(transportDef);
}

XebraRunActionMessenger::~XebraRunActionMessenger()
{
	delete m_pDirectory;
}

void
XebraRunActionMessenger::SetNewValue(G4UIcommand * command, G4String newValues)
{
	if(command == m_pRanSeedCmd)
		m_pRunAction->SetRanSeed(m_pRanSeedCmd->GetNewIntValue(newValues));
//	if(command == m_pForcedTransportCmd)
//		m_pRunAction->SetForcedTransport(m_pForcedTransportCmd->GetNewBoolValue(newValues));
}


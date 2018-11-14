#ifndef __XEBRAPHYSICSLIST_H__
#define __XEBRAPHYSICSLIST_H__

#include "G4VModularPhysicsList.hh"
#include "XebraPhysicsMessenger.hh"
#include "globals.hh"

#include <vector>
using namespace std;

class XebraPhysicsList: public G4VModularPhysicsList 
{

public:
  XebraPhysicsList(G4String fName);
  virtual ~XebraPhysicsList();
  
public:
  void SetCuts();

  // functions for the messenger interface
  void SetCerenkov(G4bool useCerenkov) { m_bCerenkov = useCerenkov; }
  void SetEMlowEnergyModel(G4String theModel) { m_hEMlowEnergyModel = theModel; }
  void SetHadronicModel(G4String theModel)    { m_hHadronicModel = theModel; }
  void SetHistograms(G4bool makeHistos) { makePhysicsHistograms = makeHistos; }

  void MakePhysicsPlots();
  void WriteParameter(G4String parName);

private:

  G4VPhysicsConstructor *X1TG4OpticalPhysics;
  
  G4double defaultCutValue;
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  //G4double cutForProton;
  //G4double cutForAlpha;
  //G4double cutForGenericIon;
  
  G4int VerboseLevel;
	
  XebraPhysicsMessenger *m_pMessenger;
  G4String                 m_hEMlowEnergyModel;
  G4String                 m_hHadronicModel;
  G4bool                   m_bCerenkov;
  G4bool                   makePhysicsHistograms;
  
  G4String physRootFile;

};
#endif

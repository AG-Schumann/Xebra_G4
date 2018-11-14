#ifndef __XEBRAPHYSICSMESSENGER_H__
#define __XEBRAPHYSICSMESSENGER_H__

//  XebraPhysicsMessenger class.
//  Allow for setting of preferences in the PhysicsList

#include <G4UImessenger.hh>
#include <globals.hh>

class XebraPhysicsList;

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class XebraPhysicsMessenger: public G4UImessenger
{
public:
  XebraPhysicsMessenger(XebraPhysicsList *pPhysicsList);
  ~XebraPhysicsMessenger();
  
  void SetNewValue(G4UIcommand *pCommand, G4String hNewValues);
private:
  XebraPhysicsList          *m_pPhysicsList;
  G4UIdirectory              *m_pDirectory;
  G4UIcmdWithAString         *m_pEMlowEnergyModelCmd;
  G4UIcmdWithAString         *m_pHadronicModelCmd;
  G4UIcmdWithABool           *m_pCerenkovCmd;
  G4UIcmdWithABool           *m_pHistosCmd;
};

#endif

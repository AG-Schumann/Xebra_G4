#ifndef __XEBRAPRIMARYGENERATORMESSENGER_H__
#define __XEBRAPRIMARYGENERATORMESSENGER_H__

#include <G4UImessenger.hh>
#include <globals.hh>

class XebraPrimaryGeneratorAction;

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

class XebraPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  XebraPrimaryGeneratorMessenger(XebraPrimaryGeneratorAction *pPrimaryGeneratorAction);
  ~XebraPrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand *pCommand, G4String hNewValues);

private:
  XebraPrimaryGeneratorAction *m_pPrimaryGeneratorAction;
  G4UIdirectory                 *m_pDirectory;
  G4UIcmdWithABool              *m_pVarianceReductionCmd;
  G4UIcmdWithABool              *m_pWriteEmptyCmd;
  G4UIcmdWithAnInteger          *m_pVarianceReductionModeCmd;
  G4UIcmdWithADouble            *p_survival_cutCmd;
  G4UIcmdWith3VectorAndUnit     *ft_positionCmd;
  G4UIcmdWithADoubleAndUnit     *ft_lengthCmd;
  G4UIcmdWithADoubleAndUnit     *ft_radiusCmd;

};

#endif

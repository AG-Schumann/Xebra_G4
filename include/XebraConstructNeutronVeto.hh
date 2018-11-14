#ifndef XEBRACONSTRUCTNEUTRONVETO_H
#define XEBRACONSTRUCTNEUTRONVETO_H

//XEBRA header files
#include "XebraDetectorConstruction.hh"
#include "XebraConstructCryostat.hh"

//G4 Header Files
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>

class XebraConstructNeutronVeto{

public:
  XebraConstructNeutronVeto(XebraDetectorConstruction*);
  ~XebraConstructNeutronVeto();

  G4LogicalVolume* Construct( G4double outer_RadiusCryostat, G4double outer_HeightCryostat );
  G4LogicalVolume* GetMotherVolume();

  void PrintGeometryInformation();

private:
    
  //Materials
  G4Material *NeutronVetoScintillatorMaterial;
  G4Material *NeutronVetoSensorsMaterial;

  //Parameters
  G4double Thickness_Sensor;
  G4double Thickness_Scintillator;
  G4double outer_RadiusSensor;
  G4double outer_HeightSensor;

  //Solids
  G4Tubs *NeutronVetoScintillatorTube;
  G4Tubs *NeutronVetoSensorsTube;

  //LogicalVolumes
  G4LogicalVolume *NeutronVetoSensorsLogicalVolume;
  G4LogicalVolume *NeutronVetoScintillatorLogicalVolume;

  // PhysicalVolumes
  G4VPhysicalVolume *NeutronVetoScintillatorPhysicalVolume;

  //Visualization
  G4VisAttributes *NeutronVetoSensorsVisAtt;
  G4VisAttributes *NeutronVetoScintillatorVisAtt;

};

#endif

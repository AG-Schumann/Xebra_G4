#ifndef XEBRACONSTRUCTSENSORS_H
#define XEBRACONSTRUCTSENSORS_H

//XEBRA header files
#include "XebraConstructTPC.hh"
#include "XebraPmtSensitiveDetector.hh"

//G4 Header Files
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

class XebraConstructSensors{

public:
  XebraConstructSensors(XebraConstructTPC*);
  ~XebraConstructSensors();

  G4LogicalVolume* Construct( G4double Sensordisk_thickness, G4double Sensordisk_radius);

private:

  G4SDManager *SDManager;

  //Materials
  G4Material *PMT_material;

  //Parameters
  G4double Thickness_Sensor;
  G4double outer_RadiusSensor;

  //Solids
  G4Tubs *Sensor_disk;

  //LogicalVolumes
  G4LogicalVolume *Sensor_LogicalVolume;

  //Others
  XebraPmtSensitiveDetector *PmtSD;

  //Visualization
  G4VisAttributes *SensorVisAtt;

};

#endif

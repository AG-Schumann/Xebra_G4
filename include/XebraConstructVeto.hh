#ifndef XEBRACONSTRUCTVETO_H
#define XEBRACONSTRUCTVETO_H

//XEBRA header files
#include "XebraDetectorConstruction.hh"

//G4 Header Files
#include <G4SystemOfUnits.hh>

class XebraConstructVeto{

public:
  XebraConstructVeto(XebraDetectorConstruction*);
  ~XebraConstructVeto();

  G4LogicalVolume* Construct();
  G4LogicalVolume* GetMotherVolume();

private:
    
  //Materials
  G4Material *Water;
  G4Material *Air;

  //Parameters
  G4double WaterTankHeight;
  G4double WaterTankRadius;

  //LogicalVolumes
  G4LogicalVolume *WaterLogicalVolume;

  //Solids
  G4Tubs *WaterTank;

  //Visualization
  G4VisAttributes *WaterVisAtt;

};

#endif

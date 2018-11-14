#include "XebraConstructVeto.hh"

XebraConstructVeto::XebraConstructVeto( XebraDetectorConstruction *){;}

XebraConstructVeto::~XebraConstructVeto(){;}

G4LogicalVolume* XebraConstructVeto::Construct(){

	// Parameters
        WaterTankHeight   = 14.0*m; // Water height
        WaterTankRadius	  = 7.0*m; // Radius cylinder 

	// Materials
	Water = G4Material::GetMaterial("Water");
	Air = G4Material::GetMaterial("G4_AIR");	

	// Objects
	WaterTank = new G4Tubs("WaterTank", 0.*cm, WaterTankRadius, WaterTankHeight/2 , 0.*deg, 360.*deg);

	// Logical Volume
	WaterLogicalVolume = new G4LogicalVolume(WaterTank, Water, "WaterVolume", 0, 0, 0);

	// Visualization Settings
	G4Colour WaterColor(0., 0., 0.500, 0.7);
	WaterVisAtt = new G4VisAttributes(WaterColor);
	WaterVisAtt->SetVisibility(true);
	WaterLogicalVolume->SetVisAttributes(WaterVisAtt); 

	return WaterLogicalVolume;

}

G4LogicalVolume* XebraConstructVeto::GetMotherVolume(){
  return this->WaterLogicalVolume;
}


#ifndef XEBRACONSTRUCTTPC_H
#define XEBRACONSTRUCTTPC_H

//XEBRA header files
#include "XebraDetectorConstruction.hh"
#include "XebraLXeSensitiveDetector.hh"

//G4 Header Files
#include <G4SystemOfUnits.hh>
#include <G4SDManager.hh>

class XebraConstructTPC{

public:
   XebraConstructTPC(XebraDetectorConstruction*);
   ~XebraConstructTPC();
 
   G4LogicalVolume* Construct();

   G4double GetInnerRadiusCryostat();
   G4double GetInnerHeightCryostat();

   void PrintGeometryInformation();

private:

   //Materials
   G4Material *LXe;
   G4Material *GXe;
   G4Material *Teflon;
   G4Material *SS304LSteel;
   G4Material *Copper;
   G4Material *PMT_material;

   G4Material *Aluminium;

   //Parameters
   G4double cryostat_innerRadius;
   G4double cryostat_innerHeight;
   G4double GXe_height;

   G4double TPC_dimension_z;
   G4double TPC_dimension_r;
   G4double TPC_offsetOrigin_z;

   G4RotationMatrix* rmz45;
   G4RotationMatrix* rmz120;	
   G4RotationMatrix* rmz165;	
   G4RotationMatrix* rmz285;
 
   //Solids
   G4Tubs *TPC_cylinder;
   G4Tubs *GXe_cylinder; 

   G4Tubs* TPC_SS_PMTfixture_solid_orig;
   G4Box* TPC_SS_PMTfixture_solid_union1;	
   G4VSolid* TPC_SS_PMTfixture_solid_1;
   G4VSolid* TPC_SS_PMTfixture_solid_2;
   G4VSolid* TPC_SS_PMTfixture_solid;

   G4Tubs* TPC_Al_filler_solid_orig;
   G4Tubs* TPC_Al_filler_solid_sub1;
   G4VSolid* TPC_Al_filler_solid_1;
   G4Tubs* TPC_Al_filler_solid_sub2_orig;
   G4Box* TPC_Al_filler_solid_sub2_union1;	
   G4VSolid* TPC_Al_filler_solid_sub2_1;
   G4VSolid* TPC_Al_filler_solid_sub2_2;
   G4VSolid* TPC_Al_filler_solid_sub2;   
   G4VSolid* TPC_Al_filler_solid_2;
   G4VSolid* TPC_Al_filler_solid;

   //LogicalVolumes
   G4LogicalVolume *test_Logical;

   G4LogicalVolume *TPC_Logical;
   G4LogicalVolume *LXe_Logical;
   G4LogicalVolume *GXe_Logical;

   G4LogicalVolume* TPC_SS_PMTfixture_log;
   G4LogicalVolume* TPC_Al_filler_log;

   //PhysicalVolumes
   G4VPhysicalVolume *test_phys;

   G4VPhysicalVolume *LXe_Physical;
   G4VPhysicalVolume *GXe_Physical; 

   G4VPhysicalVolume* TPC_SS_PMTfixture_phys;
   G4VPhysicalVolume* TPC_Al_filler_phys;

   //Visualization
   G4VisAttributes *TeflonVisAtt;
   G4VisAttributes *LXeVisAtt;
   G4VisAttributes *GXeVisAtt;
   G4VisAttributes *ElectrodesVisAtt;
   G4VisAttributes *CathodeVisAtt;
   G4VisAttributes *BottomscreenVisAtt;
   G4VisAttributes *RingsVisAtt;
   G4VisAttributes *SensorVisAtt;

};

#endif

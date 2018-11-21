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

   //Parameters
   G4double cryostat_innerRadius;
   G4double cryostat_innerHeight;
   G4double GXe_height;
   //a// G4double activeTPC_height;
   //a// G4double activeTPC_innerRadius;
   //a// G4double reflector_bottom_height;
   //a// G4double reflector_offsetZ;
   //a// G4double reflector_thickness;
   //a// G4double electrodes_frame_thickness;
   //a// G4double electrodes_top_frame_height;
   //a// G4double cathode_frame_height;
   //a// G4double bottomscreen_frame_height;
   //a// G4double LXe_extra_filling;
   //a// G4double FSR_thickness;
   //a// G4double FSR_height;
   //a// G4double FSR_innerRadius;
   //a// G4double FSR_number;
   //a// G4double FSR_offsetZ;
   //a// G4double FSR_separation;
   //a// G4double pillar_width;
   //a// G4double pillar_thickness;
   //a// G4double pillar_number;
   //a// G4double sensor_thickness;
 
   //Solids
   G4Tubs *TPC_cylinder;
   G4Tubs *GXe_cylinder; 
   //a// G4Tubs *PTFE_reflector;
   //a// G4Tubs *PTFE_reflector_top;
   //a// G4Tubs *PTFE_reflector_bottom;
   //a// G4Tubs *SS304_electrodes_top_frame;
   //a// G4Tubs *SS304_cathode_frame;
   //a// G4Tubs *SS304_bottomscreen_frame; 
   //a// G4Tubs *LXe_extra_filling_inside;
   //a// G4Tubs *LXe_extra_filling_outside;
   //a// G4Tubs *LXe_sensitive; 
   //a// G4Tubs *Cu_Fsr;
   //a// G4Box *PTFE_pillar;
   //a// G4Box *PTFE_pillar_bottom;

   //LogicalVolumes
   G4LogicalVolume *TPC_Logical;
   G4LogicalVolume *LXe_Logical;
   G4LogicalVolume *GXe_Logical;

   //a// G4LogicalVolume *PTFE_reflector_Logical;
   //a// G4LogicalVolume *PTFE_reflector_top_Logical;
   //a// G4LogicalVolume *PTFE_reflector_bottom_Logical;

   //a// G4LogicalVolume *SS304_electrodes_top_frame_Logical;
   //a// G4LogicalVolume *SS304_cathode_frame_Logical;
   //a// G4LogicalVolume *SS304_bottomscreen_frame_Logical;

   //a// G4LogicalVolume *LXe_extra_filling_inside_Logical;
   //a// G4LogicalVolume *LXe_extra_filling_outside_Logical;
   //a// G4LogicalVolume *LXe_sensitive_Logical; 

   //a// G4LogicalVolume *Cu_FSR_Logical;

   //a// G4LogicalVolume *PTFE_pillar_Logical;
   //a// G4LogicalVolume *PTFE_pillar_bottom_Logical;

   //a// G4LogicalVolume *PMT_sensorarray_Logical;

   //PhysicalVolumes
   G4VPhysicalVolume *LXe_Physical;
   G4VPhysicalVolume *GXe_Physical; 

   //a// G4VPhysicalVolume *PTFE_reflector_Physical;
   //a// G4VPhysicalVolume *PTFE_reflector_top_Physical;
   //a// G4VPhysicalVolume *PTFE_reflector_bottom_Physical;

   //a// G4VPhysicalVolume *SS304_electrodes_top_frame_Physical;
   //a// G4VPhysicalVolume *SS304_cathode_frame_Physical;
   //a// G4VPhysicalVolume *SS304_bottomscreen_frame_Physical;
 
   //a// G4VPhysicalVolume *LXe_extra_filling_inside_Physical;
   //a// G4VPhysicalVolume *LXe_extra_filling_outside_Physical;
   //a// G4VPhysicalVolume *LXe_sensitive_Physical;

   //a// G4VPhysicalVolume *Cu_FSR_Physical;  

   //a// G4VPhysicalVolume *PTFE_pillar_Physical;
   //a// G4VPhysicalVolume *PTFE_pillar_bottom_Physical;

   //a// G4VPhysicalVolume *PMT_sensorarray_bottom_Physical;
   //a// G4VPhysicalVolume *PMT_sensorarray_top_Physical;

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

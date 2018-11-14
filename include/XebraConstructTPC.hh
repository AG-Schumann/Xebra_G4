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
   G4double activeTPC_height;
   G4double activeTPC_innerRadius;
   G4double reflector_bottom_height;
   G4double reflector_offsetZ;
   G4double reflector_thickness;
   G4double electrodes_frame_thickness;
   G4double electrodes_top_frame_height;
   G4double cathode_frame_height;
   G4double bottomscreen_frame_height;
   G4double LXe_extra_filling;
   G4double FSR_thickness;
   G4double FSR_height;
   G4double FSR_innerRadius;
   G4double FSR_number;
   G4double FSR_offsetZ;
   G4double FSR_separation;
   G4double pillar_width;
   G4double pillar_thickness;
   G4double pillar_number;
   G4double sensor_thickness;
 
   //Solids
   G4Tubs *TPC_cylinder;
   G4Tubs *GXe_cylinder; 
   G4Tubs *PTFE_reflector;
   G4Tubs *PTFE_reflector_top;
   G4Tubs *PTFE_reflector_bottom;
   G4Tubs *SS304_electrodes_top_frame;
   G4Tubs *SS304_cathode_frame;
   G4Tubs *SS304_bottomscreen_frame; 
   G4Tubs *LXe_extra_filling_inside;
   G4Tubs *LXe_extra_filling_outside;
   G4Tubs *LXe_sensitive; 
   G4Tubs *Cu_Fsr;
   G4Box *PTFE_pillar;
   G4Box *PTFE_pillar_bottom;

   //LogicalVolumes
   G4LogicalVolume *TPC_Logical;
   G4LogicalVolume *LXe_Logical;
   G4LogicalVolume *GXe_Logical;

   G4LogicalVolume *PTFE_reflector_Logical;
   G4LogicalVolume *PTFE_reflector_top_Logical;
   G4LogicalVolume *PTFE_reflector_bottom_Logical;

   G4LogicalVolume *SS304_electrodes_top_frame_Logical;
   G4LogicalVolume *SS304_cathode_frame_Logical;
   G4LogicalVolume *SS304_bottomscreen_frame_Logical;

   G4LogicalVolume *LXe_extra_filling_inside_Logical;
   G4LogicalVolume *LXe_extra_filling_outside_Logical;
   G4LogicalVolume *LXe_sensitive_Logical; 

   G4LogicalVolume *Cu_FSR_Logical;

   G4LogicalVolume *PTFE_pillar_Logical;
   G4LogicalVolume *PTFE_pillar_bottom_Logical;

   G4LogicalVolume *PMT_sensorarray_Logical;

   //PhysicalVolumes
   G4VPhysicalVolume *LXe_Physical;
   G4VPhysicalVolume *GXe_Physical; 

   G4VPhysicalVolume *PTFE_reflector_Physical;
   G4VPhysicalVolume *PTFE_reflector_top_Physical;
   G4VPhysicalVolume *PTFE_reflector_bottom_Physical;

   G4VPhysicalVolume *SS304_electrodes_top_frame_Physical;
   G4VPhysicalVolume *SS304_cathode_frame_Physical;
   G4VPhysicalVolume *SS304_bottomscreen_frame_Physical;
 
   G4VPhysicalVolume *LXe_extra_filling_inside_Physical;
   G4VPhysicalVolume *LXe_extra_filling_outside_Physical;
   G4VPhysicalVolume *LXe_sensitive_Physical;

   G4VPhysicalVolume *Cu_FSR_Physical;  

   G4VPhysicalVolume *PTFE_pillar_Physical;
   G4VPhysicalVolume *PTFE_pillar_bottom_Physical;

   G4VPhysicalVolume *PMT_sensorarray_bottom_Physical;
   G4VPhysicalVolume *PMT_sensorarray_top_Physical;

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

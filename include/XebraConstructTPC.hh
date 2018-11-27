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

   G4double TPC_PTFE_pillar_number;
   G4double TPC_PTFE_pillar_dimension_y;
   G4double TPC_PTFE_pillar_a_dimension_x;
   G4double TPC_PTFE_pillar_a_dimension_z;
   G4double TPC_PTFE_pillar_a_position_r;
   G4double TPC_PTFE_pillar_b_dimension_x;
   G4double TPC_PTFE_pillar_b_dimension_z;
   G4double TPC_PTFE_pillar_b_position_r;
   G4double TPC_PTFE_pillar_c_dimension_x;
   G4double TPC_PTFE_pillar_c_dimension_z;
   G4double TPC_PTFE_pillar_c_position_r;
   G4double TPC_PTFE_pillar_d_dimension_x;
   G4double TPC_PTFE_pillar_d_dimension_z;
   G4double TPC_PTFE_pillar_d_position_r;
   G4double TPC_PTFE_pillar_e_dimension_x;
   G4double TPC_PTFE_pillar_e_dimension_z;
   G4double TPC_PTFE_pillar_e_position_r;
   G4double TPC_PTFE_pillar_f_dimension_x;
   G4double TPC_PTFE_pillar_f_dimension_z;
   G4double TPC_PTFE_pillar_f_position_r;
   G4double TPC_PTFE_pillar_g_dimension_x;
   G4double TPC_PTFE_pillar_g_dimension_z;
   G4double TPC_PTFE_pillar_g_position_r;
   G4double TPC_PTFE_pillar_h_dimension_x;
   G4double TPC_PTFE_pillar_h_dimension_z;
   G4double TPC_PTFE_pillar_h_position_r;

   G4RotationMatrix* rmz45;
   G4RotationMatrix* rmz120;	
   G4RotationMatrix* rmz165;
   G4RotationMatrix* rmz225;	
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
   G4Box* TPC_Al_filler_solid_sub3;
   G4VSolid* TPC_Al_filler_solid_3;
   G4Box* TPC_Al_filler_solid_sub4;
   G4VSolid* TPC_Al_filler_solid_4;
   G4Tubs* TPC_Al_filler_solid_sub5;
   G4VSolid* TPC_Al_filler_solid_sub5_1;
   G4VSolid* TPC_Al_filler_solid_5;
   G4VSolid* TPC_Al_filler_solid;

   G4Tubs* TPC_Cu_FSE_solid;

   G4Box* TPC_PTFE_pillar_a_solid;
   G4Box* TPC_PTFE_pillar_b_solid;
   G4Box* TPC_PTFE_pillar_c_solid;
   G4Box* TPC_PTFE_pillar_d_solid;
   G4Box* TPC_PTFE_pillar_e_solid;
   G4Box* TPC_PTFE_pillar_f_solid;
   G4Box* TPC_PTFE_pillar_g_solid;
   G4Box* TPC_PTFE_pillar_h_solid;

   //LogicalVolumes
   G4LogicalVolume *test_Logical;

   G4LogicalVolume *TPC_Logical;
   G4LogicalVolume *LXe_Logical;
   G4LogicalVolume *GXe_Logical;

   G4LogicalVolume* TPC_SS_PMTfixture_log;
   G4LogicalVolume* TPC_Al_filler_log;
   G4LogicalVolume* TPC_Cu_FSE_log;
   G4LogicalVolume* TPC_PTFE_pillar_a_log;
   G4LogicalVolume* TPC_PTFE_pillar_b_log;
   G4LogicalVolume* TPC_PTFE_pillar_c_log;
   G4LogicalVolume* TPC_PTFE_pillar_d_log;
   G4LogicalVolume* TPC_PTFE_pillar_e_log;
   G4LogicalVolume* TPC_PTFE_pillar_f_log;
   G4LogicalVolume* TPC_PTFE_pillar_g_log;
   G4LogicalVolume* TPC_PTFE_pillar_h_log;

   //PhysicalVolumes
   G4VPhysicalVolume *test_phys;

   G4VPhysicalVolume *LXe_Physical;
   G4VPhysicalVolume *GXe_Physical; 

   G4VPhysicalVolume* TPC_SS_PMTfixture_phys;
   G4VPhysicalVolume* TPC_Al_filler_phys;
   G4VPhysicalVolume* TPC_Cu_FSE_1_phys;
   G4VPhysicalVolume* TPC_Cu_FSE_2_phys;
   G4VPhysicalVolume* TPC_Cu_FSE_3_phys;
   G4VPhysicalVolume* TPC_Cu_FSE_4_phys;
   G4VPhysicalVolume* TPC_Cu_FSE_5_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer1_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer2_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer3_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer4_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer5_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer6_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer7_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer8_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer9_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer10_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer11_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer12_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer13_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer14_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer15_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer16_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_layer17_phys;

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

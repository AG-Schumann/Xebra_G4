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
   G4double TPC_PTFE_pillar_i_dimension_x;
   G4double TPC_PTFE_pillar_i_dimension_z;
   G4double TPC_PTFE_pillar_i_position_r;

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
   G4Box* TPC_PTFE_pillar_i_solid;
   G4VSolid* TPC_PTFE_pillar_LXe_solid;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_1;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_2;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_3;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_4;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_5;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_6;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_7;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_8;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_9;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_10;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_11;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_12;
   G4VSolid* TPC_PTFE_pillar_LXe_solid_13;
   G4VSolid* TPC_PTFE_pillar_GXe_solid;
   G4VSolid* TPC_PTFE_pillar_GXe_solid_1;
   G4VSolid* TPC_PTFE_pillar_GXe_solid_2;

   G4Tubs* TPC_SS_BottomRing_solid;
   G4Tubs* TPC_SS_pillar_solid;

   G4VSolid* TPC_SS_TopRing_solid;
   G4Tubs* TPC_SS_TopRing_solid_orig;
   G4Tubs* TPC_SS_TopRing_solid_sub1_a;
   G4Tubs* TPC_SS_TopRing_solid_sub1_b;
   G4Tubs* TPC_SS_TopRing_solid_sub1_c;
   G4Tubs* TPC_SS_TopRing_solid_sub1_d;
   G4Tubs* TPC_SS_TopRing_solid_sub2_a;
   G4Tubs* TPC_SS_TopRing_solid_sub2_b;
   G4Tubs* TPC_SS_TopRing_solid_sub2_c;
   G4Tubs* TPC_SS_TopRing_solid_sub2_d;
   G4Tubs* TPC_SS_TopRing_solid_sub3;
   G4Tubs* TPC_SS_TopRing_solid_sub4;
   G4Tubs* TPC_SS_TopRing_solid_sub5;
   G4VSolid* TPC_SS_TopRing_solid_1;
   G4VSolid* TPC_SS_TopRing_solid_2;
   G4VSolid* TPC_SS_TopRing_solid_3;
   G4VSolid* TPC_SS_TopRing_solid_4;
   G4VSolid* TPC_SS_TopRing_solid_5;
   G4VSolid* TPC_SS_TopRing_solid_6;
   G4VSolid* TPC_SS_TopRing_solid_7;
   G4VSolid* TPC_SS_TopRing_solid_8;
   G4VSolid* TPC_SS_TopRing_solid_9;
   G4VSolid* TPC_SS_TopRing_solid_10;
   G4VSolid* TPC_SS_TopRing_solid_11;
   G4VSolid* TPC_SS_TopRing_solid_12;
   G4VSolid* TPC_SS_TopRing_solid_13;
   G4VSolid* TPC_SS_TopRing_solid_14;
   G4VSolid* TPC_SS_TopRing_solid_15;
   G4VSolid* TPC_SS_TopRing_solid_16;
   G4VSolid* TPC_SS_TopRing_solid_17;
   G4VSolid* TPC_SS_TopRing_solid_18;

   G4Tubs* TPC_PTFE_filler_solid;

   G4Tubs* TPC_PTFE_BottomPMTHolder_solid_orig;
   G4Tubs* TPC_PTFE_BottomPMTHolder_solid_union;
   G4VSolid* TPC_PTFE_BottomPMTHolder_solid;

   G4Tubs* TPC_PTFE_spacer1_solid;
   G4Tubs* TPC_PTFE_spacer2_solid;

   G4Tubs* TPC_PTFE_reflector_LXe_solid;
   G4Tubs* TPC_PTFE_reflector_GXe_solid;

   G4Tubs* TPC_SS_gate_ring_solid_orig;
   G4Tubs* TPC_SS_gate_ring_solid_sub1_a;
   G4Tubs* TPC_SS_gate_ring_solid_sub1_b;
   G4Tubs* TPC_SS_gate_ring_solid_sub1_c;
   G4Tubs* TPC_SS_gate_ring_solid_sub1_d;
   G4Tubs* TPC_SS_gate_ring_solid_sub1_e;
   G4Tubs* TPC_SS_gate_ring_solid_sub1_f;
   G4Tubs* TPC_SS_gate_ring_solid_sub2_a;
   G4Tubs* TPC_SS_gate_ring_solid_sub2_b;
   G4Tubs* TPC_SS_gate_ring_solid_sub2_c;
   G4Tubs* TPC_SS_gate_ring_solid_sub2_d;
   G4Tubs* TPC_SS_gate_ring_solid_sub2_e;
   G4Tubs* TPC_SS_gate_ring_solid_sub2_f;
   G4Tubs* TPC_SS_gate_ring_solid_sub3;
   G4VSolid* TPC_SS_gate_ring_solid_1;
   G4VSolid* TPC_SS_gate_ring_solid_2;
   G4VSolid* TPC_SS_gate_ring_solid_3;
   G4VSolid* TPC_SS_gate_ring_solid_4;
   G4VSolid* TPC_SS_gate_ring_solid_5;
   G4VSolid* TPC_SS_gate_ring_solid_6;
   G4VSolid* TPC_SS_gate_ring_solid_7;
   G4VSolid* TPC_SS_gate_ring_solid_8;
   G4VSolid* TPC_SS_gate_ring_solid_9;
   G4VSolid* TPC_SS_gate_ring_solid_10;
   G4VSolid* TPC_SS_gate_ring_solid_11;
   G4VSolid* TPC_SS_gate_ring_solid_12;
   G4VSolid* TPC_SS_gate_ring_solid_13;
   G4VSolid* TPC_SS_gate_ring_solid_14;
   G4VSolid* TPC_SS_gate_ring_solid_15;
   G4VSolid* TPC_SS_gate_ring_solid_16;
   G4VSolid* TPC_SS_gate_ring_solid_17;
   G4VSolid* TPC_SS_gate_ring_solid_18;
   G4VSolid* TPC_SS_gate_ring_solid_19;
   G4VSolid* TPC_SS_gate_ring_solid_20;
   G4VSolid* TPC_SS_gate_ring_solid_21;
   G4VSolid* TPC_SS_gate_ring_solid_22;
   G4VSolid* TPC_SS_gate_ring_solid_23;
   G4VSolid* TPC_SS_gate_ring_solid_24;
   G4VSolid* TPC_SS_gate_ring_solid;

   G4Tubs* TPC_PTFE_TopPMTHolder_solid_orig;
   G4Box* TPC_PTFE_TopPMTHolder_solid_sub1_1;
   G4Box* TPC_PTFE_TopPMTHolder_solid_sub1_2;
   G4Tubs* TPC_PTFE_TopPMTHolder_solid_sub1_3;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub1_a;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub1_b;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub1_c;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub1_d;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub1;
   G4Box* TPC_PTFE_TopPMTHolder_solid_sub2_1;
   G4Box* TPC_PTFE_TopPMTHolder_solid_sub2_2;
   G4Tubs* TPC_PTFE_TopPMTHolder_solid_sub2_3;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub2_a;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub2_b;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub2_c;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub2_d;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_sub2;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_1;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_2;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_3;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_4;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_5;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_6;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_7;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_8;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_9;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_10;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_11;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_12;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid_13;
   G4VSolid* TPC_PTFE_TopPMTHolder_solid;

   G4Box* TPC_R8520_solid_orig_1;
   G4Box* TPC_R8520_solid_orig_2;
   G4Tubs* TPC_R8520_solid_orig_3;
   G4VSolid* TPC_R8520_solid_orig_a;
   G4VSolid* TPC_R8520_solid_orig_b;
   G4VSolid* TPC_R8520_solid_orig_c;
   G4VSolid* TPC_R8520_solid_orig_d;
   G4VSolid* TPC_R8520_solid_orig;

   G4Tubs* TPC_SS_cathode_ring_solid;

   G4Tubs* TPC_SS_anode_ring_solid;

   G4Tubs* TPC_SS_TopMesh_ring_solid;


   //LogicalVolumes
   G4LogicalVolume *test_Logical;

   G4LogicalVolume *TPC_Logical;
   G4LogicalVolume *LXe_Logical;
   G4LogicalVolume *GXe_Logical;

   G4LogicalVolume* TPC_SS_PMTfixture_log;
   G4LogicalVolume* TPC_Al_filler_log;
   G4LogicalVolume* TPC_Cu_FSE_log;
   G4LogicalVolume* TPC_PTFE_pillar_LXe_log;
   G4LogicalVolume* TPC_PTFE_pillar_GXe_log;
   G4LogicalVolume* TPC_SS_BottomRing_log;
   G4LogicalVolume* TPC_SS_pillar_log;
   G4LogicalVolume* TPC_SS_TopRing_log;
   G4LogicalVolume* TPC_PTFE_filler_log;
   G4LogicalVolume* TPC_PTFE_BottomPMTHolder_log;
   G4LogicalVolume* TPC_PTFE_spacer1_log;
   G4LogicalVolume* TPC_PTFE_spacer2_log;
   G4LogicalVolume* TPC_PTFE_reflector_LXe_log;
   G4LogicalVolume* TPC_PTFE_reflector_GXe_log;
   G4LogicalVolume* TPC_SS_gate_ring_log;
   G4LogicalVolume* TPC_PTFE_TopPMTHolder_log;
   G4LogicalVolume* TPC_SS_cathode_ring_log;
   G4LogicalVolume* TPC_SS_anode_ring_log;
   G4LogicalVolume* TPC_SS_TopMesh_ring_log;

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
   G4VPhysicalVolume* TPC_PTFE_pillar_LXe_phys;
   G4VPhysicalVolume* TPC_PTFE_pillar_GXe_phys;
   G4VPhysicalVolume* TPC_SS_BottomRing_phys;
   G4VPhysicalVolume* TPC_SS_pillar_phys;
   G4VPhysicalVolume* TPC_SS_TopRing_phys;
   G4VPhysicalVolume* TPC_PTFE_filler_phys;
   G4VPhysicalVolume* TPC_PTFE_BottomPMTHolder_phys;
   G4VPhysicalVolume* TPC_PTFE_spacer1_phys;
   G4VPhysicalVolume* TPC_PTFE_spacer2_phys;
   G4VPhysicalVolume* TPC_PTFE_reflector_LXe_phys;
   G4VPhysicalVolume* TPC_PTFE_reflector_GXe_phys;
   G4VPhysicalVolume* TPC_SS_gate_ring_phys;
   G4VPhysicalVolume* TPC_PTFE_TopPMTHolder_phys;
   G4VPhysicalVolume* TPC_SS_cathode_ring_phys;
   G4VPhysicalVolume* TPC_SS_anode_ring_phys;
   G4VPhysicalVolume* TPC_SS_TopMesh_ring_phys;

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

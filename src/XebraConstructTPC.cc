#include "XebraConstructTPC.hh"

//Detector Components
#include "XebraConstructSensors.hh"
#include "XebraPMTsR11410.hh"
#include "XebraPMTsR8520.hh"

XebraConstructTPC::XebraConstructTPC(XebraDetectorConstruction *){

	//these values will be used for the cryostat (given by Julia); ToDo: cylindrical shape correct?
	cryostat_innerRadius = 0.15*m / 2;
	cryostat_innerHeight = 0.4*m;

}

XebraConstructTPC::~XebraConstructTPC() {;}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

G4LogicalVolume* XebraConstructTPC::Construct(){

using std::stringstream;
	stringstream name;

	//Materials
	LXe = G4Material::GetMaterial("LXe");
	GXe = G4Material::GetMaterial("GXe");
	Teflon = G4Material::GetMaterial("Teflon");
	SS304LSteel = G4Material::GetMaterial("SS304LSteel");
	Copper = G4Material::GetMaterial("Copper");
	Aluminium  = G4Material::GetMaterial("Aluminium");
	PEEK  = G4Material::GetMaterial("PEEK");
	Torlon  = G4Material::GetMaterial("Torlon");

	// General useful functions
	rmz45 = new G4RotationMatrix();
	rmz45->rotateZ(45.*deg);	
	rmz60 = new G4RotationMatrix();
	rmz60->rotateZ(60.*deg);	
	rmz120 = new G4RotationMatrix();
	rmz120->rotateZ(120.*deg);	
	rmz165 = new G4RotationMatrix();
	rmz165->rotateZ(165.*deg);
	rmz180 = new G4RotationMatrix();
	rmz180->rotateZ(180.*deg);
	rmz225 = new G4RotationMatrix();
	rmz225->rotateZ(225.*deg);	
	rmz285 = new G4RotationMatrix();
	rmz285->rotateZ(285.*deg);
	rmz300 = new G4RotationMatrix();
	rmz300->rotateZ(300.*deg);
	rmy90 = new G4RotationMatrix();
	rmy90->rotateY(90.*deg);
 
	// Parameters Cryostat, TPC and Teflon
	TPC_dimension_z = 310.0 * mm;
	TPC_dimension_r = 72.0 * mm;
	TPC_offset_z = -42. * mm; // so that only 3mm LXe below TPC

	TPC_PTFE_pillar_number = 6;
	TPC_PTFE_pillar_dimension_y = 15.0 * mm;
	TPC_PTFE_pillar_a_dimension_x = 9.8 * mm;
	TPC_PTFE_pillar_a_dimension_z = 5.2 * mm;
	TPC_PTFE_pillar_a_position_r = 70.0*mm-(TPC_PTFE_pillar_a_dimension_x/2);
	TPC_PTFE_pillar_b_dimension_x = 20.0 * mm;
	TPC_PTFE_pillar_b_dimension_z = 6.8 * mm;
	TPC_PTFE_pillar_b_position_r = 70.0*mm-(TPC_PTFE_pillar_b_dimension_x/2);
	TPC_PTFE_pillar_c_dimension_x = 9.8 * mm;
	TPC_PTFE_pillar_c_dimension_z = 3.5 * mm;
	TPC_PTFE_pillar_c_position_r = 70.0*mm-(TPC_PTFE_pillar_c_dimension_x/2);
	TPC_PTFE_pillar_d_dimension_x = 20.0 * mm;
	TPC_PTFE_pillar_d_dimension_z = 3.0 * mm;
	TPC_PTFE_pillar_d_position_r = 70.0*mm-(TPC_PTFE_pillar_d_dimension_x/2);
	TPC_PTFE_pillar_e_dimension_x = 14.8 * mm;
	TPC_PTFE_pillar_e_dimension_z = 10.2 * mm;
	TPC_PTFE_pillar_e_position_r = 70.0*mm-(TPC_PTFE_pillar_e_dimension_x/2);
	TPC_PTFE_pillar_f_dimension_x = 20.0 * mm;
	TPC_PTFE_pillar_f_dimension_z = 2.8 * mm;
	TPC_PTFE_pillar_f_position_r = 70.0*mm-(TPC_PTFE_pillar_f_dimension_x/2);
	TPC_PTFE_pillar_g_dimension_x = 9.8 * mm;
	TPC_PTFE_pillar_g_dimension_z = 16.0 * mm;
	TPC_PTFE_pillar_g_position_r = 70.0*mm-(TPC_PTFE_pillar_g_dimension_x/2);
	TPC_PTFE_pillar_h_dimension_x = 9.8 * mm;
	TPC_PTFE_pillar_h_dimension_z = 40.5 * mm;
	TPC_PTFE_pillar_h_position_r = 70.0*mm-(TPC_PTFE_pillar_h_dimension_x/2);
	TPC_PTFE_pillar_i_dimension_x = 10.2 * mm;
	TPC_PTFE_pillar_i_dimension_z = 10.0 * mm;
	TPC_PTFE_pillar_i_position_r = 60.2*mm-(TPC_PTFE_pillar_i_dimension_x/2);

	// Parameters LXe and GXe
	GXe_height = 86.5*mm + (cryostat_innerHeight - TPC_dimension_z) / 2 - TPC_offset_z; // currently at lower edge of gate ring
	LXe_extra_filling_height = 5.5 * mm;

	// Parameters Electrodes, Field Shaping Rings (FSR) and sensors


//**************************************************CONSTRUCT*********************************************************

	// Construct objects
	// Abbreviations (p...) according to https://wiki.uni-freiburg.de/app/lib/exe/fetch.php?media=start:ultimate:xebra:tpc:labtpc_assembly.pdf

	// Xenon volumes
	TPC_cylinder = new G4Tubs("TPC_cylinder", 0.*cm, cryostat_innerRadius, cryostat_innerHeight/2, 0.*deg, 360.*deg);  
	GXe_cylinder = new G4Tubs("GXe_cylinder", 0.*cm, cryostat_innerRadius, GXe_height/2, 0.*deg, 360.*deg);
		// LXe extra filling see bottom of CONSTRUCT section
		
		// fillings in weir
		filling_ratio_weir = 0.5; // ratio by how much the weir is filled with LXe, default = 0.5, range = (0,1)

			// LXe weir in TPC_cylinder volume without GXe_cylinder volume
			height_LXe_TPC_cylinder = std::min(filling_ratio_weir * (70.5*mm + 5.5*mm), 70.5*mm);

			if (height_LXe_TPC_cylinder > 0.)	
			{
				LXe_weir_1_solid_union_1 = new G4Tubs("LXe_weir_1_solid_union_1", 61.5*mm, 71.5*mm, height_LXe_TPC_cylinder / 2, 136.*deg, (164.-136.)*deg);
				LXe_weir_1_solid_union_2 = new G4Tubs("LXe_weir_1_solid_union_2", 0.*mm, 5.*mm, height_LXe_TPC_cylinder / 2, 0.*deg, 360.*deg);
				LXe_weir_1_solid_1 = new G4UnionSolid("LXe_weir_1_solid_1", LXe_weir_1_solid_union_1, LXe_weir_1_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), 0.*mm));
				LXe_weir_1_solid = new G4UnionSolid("LXe_weir_1_solid", LXe_weir_1_solid_1, LXe_weir_1_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), 0.*mm));
			}
				
			// GXe weir in TPC_cylinder volume without GXe_cylinder volume
			height_GXe_TPC_cylinder = 70.5*mm - height_LXe_TPC_cylinder;

			if (height_GXe_TPC_cylinder > 0.)	
			{
				GXe_weir_1_solid_union_1 = new G4Tubs("GXe_weir_1_solid_union_1", 61.5*mm, 71.5*mm, height_GXe_TPC_cylinder / 2, 136.*deg, (164.-136.)*deg);
				GXe_weir_1_solid_union_2 = new G4Tubs("GXe_weir_1_solid_union_2", 0.*mm, 5.*mm, height_GXe_TPC_cylinder / 2, 0.*deg, 360.*deg);
				GXe_weir_1_solid_1 = new G4UnionSolid("GXe_weir_1_solid_1", GXe_weir_1_solid_union_1, GXe_weir_1_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), 0.*mm));
				GXe_weir_1_solid = new G4UnionSolid("GXe_weir_1_solid", GXe_weir_1_solid_1, GXe_weir_1_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), 0.*mm));
			}

			// LXe weir in GXe_cylinder volume
			height_LXe_GXe_cylinder = std::max(filling_ratio_weir * (70.5*mm + 5.5*mm) - 70.5*mm, 0.*mm);

			if (height_LXe_GXe_cylinder > 0.)	
			{
				LXe_weir_2_solid_union_1 = new G4Tubs("LXe_weir_2_solid_union_1", 61.5*mm, 71.5*mm, height_LXe_GXe_cylinder / 2, 136.*deg, (164.-136.)*deg);
				LXe_weir_2_solid_union_2 = new G4Tubs("LXe_weir_2_solid_union_2", 0.*mm, 5.*mm, height_LXe_GXe_cylinder / 2, 0.*deg, 360.*deg);
				LXe_weir_2_solid_1 = new G4UnionSolid("LXe_weir_2_solid_1", LXe_weir_2_solid_union_1, LXe_weir_2_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), 0.*mm));
				LXe_weir_2_solid = new G4UnionSolid("LXe_weir_2_solid", LXe_weir_2_solid_1, LXe_weir_2_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), 0.*mm));
			}

			// GXe weir in GXe_cylinder volume
			height_GXe_GXe_cylinder = 5.5*mm - height_LXe_GXe_cylinder;

			if (height_GXe_GXe_cylinder > 0.)	
			{
				GXe_weir_2_solid_union_1 = new G4Tubs("GXe_weir_2_solid_union_1", 61.5*mm, 71.5*mm, height_GXe_GXe_cylinder / 2, 136.*deg, (164.-136.)*deg);
				GXe_weir_2_solid_union_2 = new G4Tubs("GXe_weir_2_solid_union_2", 0.*mm, 5.*mm, height_GXe_GXe_cylinder / 2, 0.*deg, 360.*deg);
				GXe_weir_2_solid_1 = new G4UnionSolid("GXe_weir_2_solid_1", GXe_weir_2_solid_union_1, GXe_weir_2_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), 0.*mm));
				GXe_weir_2_solid = new G4UnionSolid("GXe_weir_2_solid", GXe_weir_2_solid_1, GXe_weir_2_solid_union_2, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), 0.*mm));
			}

	// PMT fixture (p11)
	TPC_SS_PMTfixture_solid_orig = new G4Tubs("TPC_SS_PMTfixture_solid_orig", 0.0*mm, 2.0*mm / 2, 2.0*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_PMTfixture_solid_union1 = new G4Box("TPC_SS_PMTfixture_solid_union1", 55.0*mm / 2, 10.0*mm / 2, 5.0*mm / 2);
	TPC_SS_PMTfixture_solid_1 = new G4UnionSolid("TPC_SS_PMTfixture_solid_1", TPC_SS_PMTfixture_solid_orig, TPC_SS_PMTfixture_solid_union1, rmz45, G4ThreeVector(cos(-45.*deg) * 55.0*mm / 2, sin(-45.*deg) * 55.0*mm / 2,0.));	
	TPC_SS_PMTfixture_solid_2 = new G4UnionSolid("TPC_SS_PMTfixture_solid_2", TPC_SS_PMTfixture_solid_1, TPC_SS_PMTfixture_solid_union1, rmz165, G4ThreeVector(cos(-165.*deg) * 55.0*mm / 2, sin(-165.*deg) * 55.0*mm / 2,0.));	
	TPC_SS_PMTfixture_solid = new G4UnionSolid("TPC_SS_PMTfixture_solid", TPC_SS_PMTfixture_solid_2, TPC_SS_PMTfixture_solid_union1, rmz285, G4ThreeVector(cos(-285.*deg) * 55.0*mm / 2, sin(-285.*deg) * 55.0*mm / 2,0.));

	// Al-Filler (p10b)
	TPC_Al_filler_solid_orig = new G4Tubs("TPC_Al_filler_solid_orig", 40.*mm, 72.*mm, 135.*mm / 2, 0.*deg, 360.*deg);	
	TPC_Al_filler_solid_sub1 = new G4Tubs("TPC_Al_filler_solid_sub1", 0.*mm, 45.*mm, 35.*mm / 2, 0.*deg, 360.*deg);
	TPC_Al_filler_solid_1 = new G4SubtractionSolid("TPC_Al_filler_solid_1", TPC_Al_filler_solid_orig, TPC_Al_filler_solid_sub1, 0, G4ThreeVector(0.,0.,135.*mm / 2 - 35.*mm / 2));

	TPC_Al_filler_solid_sub2_orig = new G4Tubs("TPC_Al_filler_solid_sub2_orig", 0.0*mm, 2.0*mm / 2, 2.0*mm / 2, 0.*deg, 360.*deg);
	TPC_Al_filler_solid_sub2_union1 = new G4Box("TPC_Al_filler_solid_sub2_union1", 56.5*mm / 2, 11.0*mm / 2, 5.0*mm / 2);
	TPC_Al_filler_solid_sub2_1 = new G4UnionSolid("TPC_Al_filler_solid_sub2_1", TPC_Al_filler_solid_sub2_orig, TPC_Al_filler_solid_sub2_union1, rmz45, G4ThreeVector(cos(-45.*deg) * 56.5*mm / 2, sin(-45.*deg) * 56.5*mm / 2,0.));	
	TPC_Al_filler_solid_sub2_2 = new G4UnionSolid("TPC_Al_filler_solid_sub2_2", TPC_Al_filler_solid_sub2_1, TPC_Al_filler_solid_sub2_union1, rmz165, G4ThreeVector(cos(-165.*deg) * 56.5*mm / 2, sin(-165.*deg) * 56.5*mm / 2,0.));	
	TPC_Al_filler_solid_sub2 = new G4UnionSolid("TPC_Al_filler_solid_sub2", TPC_Al_filler_solid_sub2_2, TPC_Al_filler_solid_sub2_union1, rmz285, G4ThreeVector(cos(-285.*deg) * 56.5*mm / 2, sin(-285.*deg) * 56.5*mm / 2,0.));
	TPC_Al_filler_solid_2 = new G4SubtractionSolid("TPC_Al_filler_solid_2", TPC_Al_filler_solid_1, TPC_Al_filler_solid_sub2, 0, G4ThreeVector(0.,0.,5.*mm / 2 - 135.*mm / 2));

	TPC_Al_filler_solid_sub3 = new G4Box("TPC_Al_filler_solid_sub3", 50.0*mm / 2, 10.0*mm / 2, 5.0*mm / 2);
	TPC_Al_filler_solid_3 = new G4SubtractionSolid("TPC_Al_filler_solid_3", TPC_Al_filler_solid_2, TPC_Al_filler_solid_sub3, rmz225, G4ThreeVector(cos(-225.*deg) * 60.0*mm, sin(-225.*deg) * 60.0*mm, 5.*mm / 2 - 135.*mm / 2));
	TPC_Al_filler_solid_sub4 = new G4Box("TPC_Al_filler_solid_sub4", 10.0*mm / 2, 30.0*mm / 2, 5.0*mm / 2);
	TPC_Al_filler_solid_4 = new G4SubtractionSolid("TPC_Al_filler_solid_4", TPC_Al_filler_solid_3, TPC_Al_filler_solid_sub4, rmz225, G4ThreeVector(-40.21*mm, 40.21*mm, 5.*mm / 2 - 135.*mm / 2));
	TPC_Al_filler_solid_sub5 = new G4Tubs("TPC_Al_filler_solid_sub5", 0.0*mm, 5.0*mm / 2, 5.0*mm / 2, 0.*deg, 360.*deg);
	TPC_Al_filler_solid_sub5_1 = new G4SubtractionSolid("TPC_Al_filler_solid_sub5_1", TPC_Al_filler_solid_4, TPC_Al_filler_solid_sub5, 0, G4ThreeVector(-50.816*mm, 29.603*mm, 5.*mm / 2 - 135.*mm / 2));
	TPC_Al_filler_solid = new G4SubtractionSolid("TPC_Al_filler_solid", TPC_Al_filler_solid_sub5_1, TPC_Al_filler_solid_sub5, 0, G4ThreeVector(-29.603*mm, 50.816*mm, 5.*mm / 2 - 135.*mm / 2));

	// Field Shaping Electrodes (p5)
	TPC_Cu_FSE_solid =  new G4Tubs("TPC_SS_PMTfixture_solid_orig", 100.0*mm / 2, 110.0*mm / 2, 10.0*mm / 2, 0.*deg, 360.*deg);

	// PTFE pillar (p2) - numbering parts from low to high z-position (excluding repetitive solids)
		// parts emerged in LXe:
	TPC_PTFE_pillar_a_solid = new G4Box("TPC_PTFE_pillar_a_solid", TPC_PTFE_pillar_a_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_a_dimension_z / 2);
	TPC_PTFE_pillar_b_solid = new G4Box("TPC_PTFE_pillar_b_solid", TPC_PTFE_pillar_b_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_b_dimension_z / 2);
	TPC_PTFE_pillar_c_solid = new G4Box("TPC_PTFE_pillar_c_solid", TPC_PTFE_pillar_c_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_c_dimension_z / 2);
	TPC_PTFE_pillar_d_solid = new G4Box("TPC_PTFE_pillar_d_solid", TPC_PTFE_pillar_d_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_d_dimension_z / 2);
	TPC_PTFE_pillar_e_solid = new G4Box("TPC_PTFE_pillar_e_solid", TPC_PTFE_pillar_e_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_e_dimension_z / 2);
	TPC_PTFE_pillar_f_solid = new G4Box("TPC_PTFE_pillar_f_solid", TPC_PTFE_pillar_f_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_f_dimension_z / 2);
		// parts emerged in GXe:
	TPC_PTFE_pillar_g_solid = new G4Box("TPC_PTFE_pillar_g_solid", TPC_PTFE_pillar_g_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_g_dimension_z / 2);
	TPC_PTFE_pillar_h_solid = new G4Box("TPC_PTFE_pillar_h_solid", TPC_PTFE_pillar_h_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_h_dimension_z / 2);
	TPC_PTFE_pillar_i_solid = new G4Box("TPC_PTFE_pillar_i_solid", TPC_PTFE_pillar_i_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_i_dimension_z / 2);
		// merge parts emerged in LXe:
	TPC_PTFE_pillar_LXe_solid_1 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_1", TPC_PTFE_pillar_a_solid, TPC_PTFE_pillar_b_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_b_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_2 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_2", TPC_PTFE_pillar_LXe_solid_1, TPC_PTFE_pillar_c_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_c_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_3 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_3", TPC_PTFE_pillar_LXe_solid_2, TPC_PTFE_pillar_d_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_d_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_4 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_4", TPC_PTFE_pillar_LXe_solid_3, TPC_PTFE_pillar_e_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_e_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + TPC_PTFE_pillar_e_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_5 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_5", TPC_PTFE_pillar_LXe_solid_4, TPC_PTFE_pillar_f_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_f_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + TPC_PTFE_pillar_e_dimension_z + TPC_PTFE_pillar_f_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_6 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_6", TPC_PTFE_pillar_LXe_solid_5, TPC_PTFE_pillar_e_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_e_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + TPC_PTFE_pillar_e_dimension_z + TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_e_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_7 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_7", TPC_PTFE_pillar_LXe_solid_6, TPC_PTFE_pillar_f_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_f_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 2*TPC_PTFE_pillar_e_dimension_z + 1*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_f_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_8 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_8", TPC_PTFE_pillar_LXe_solid_7, TPC_PTFE_pillar_e_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_e_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 2*TPC_PTFE_pillar_e_dimension_z + 2*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_e_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_9 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_9", TPC_PTFE_pillar_LXe_solid_8, TPC_PTFE_pillar_f_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_f_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 3*TPC_PTFE_pillar_e_dimension_z + 2*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_f_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_10 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_10", TPC_PTFE_pillar_LXe_solid_9, TPC_PTFE_pillar_e_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_e_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 3*TPC_PTFE_pillar_e_dimension_z + 3*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_e_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_11 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_11", TPC_PTFE_pillar_LXe_solid_10, TPC_PTFE_pillar_f_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_f_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 4*TPC_PTFE_pillar_e_dimension_z + 3*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_f_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_12 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_12", TPC_PTFE_pillar_LXe_solid_11, TPC_PTFE_pillar_e_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_e_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 4*TPC_PTFE_pillar_e_dimension_z + 4*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_e_dimension_z / 2));
	TPC_PTFE_pillar_LXe_solid_13 = new G4UnionSolid("TPC_PTFE_pillar_LXe_solid_13", TPC_PTFE_pillar_LXe_solid_12, TPC_PTFE_pillar_f_solid, 0, G4ThreeVector(TPC_PTFE_pillar_a_dimension_x / 2 - TPC_PTFE_pillar_f_dimension_x / 2, 0., TPC_PTFE_pillar_a_dimension_z / 2 + TPC_PTFE_pillar_b_dimension_z + TPC_PTFE_pillar_c_dimension_z + TPC_PTFE_pillar_d_dimension_z + 5*TPC_PTFE_pillar_e_dimension_z + 4*TPC_PTFE_pillar_f_dimension_z + TPC_PTFE_pillar_f_dimension_z / 2));	
	TPC_PTFE_pillar_LXe_solid = TPC_PTFE_pillar_LXe_solid_13;
		// merge parts emerged in GXe:
	TPC_PTFE_pillar_GXe_solid_1 = new G4UnionSolid("TPC_PTFE_pillar_GXe_solid_1", TPC_PTFE_pillar_h_solid, TPC_PTFE_pillar_g_solid, 0, G4ThreeVector(TPC_PTFE_pillar_h_dimension_x / 2 - TPC_PTFE_pillar_g_dimension_x / 2, 0., - (TPC_PTFE_pillar_h_dimension_z / 2 + TPC_PTFE_pillar_g_dimension_z / 2)));
	TPC_PTFE_pillar_GXe_solid_2 = new G4UnionSolid("TPC_PTFE_pillar_GXe_solid_2", TPC_PTFE_pillar_GXe_solid_1, TPC_PTFE_pillar_i_solid, 0, G4ThreeVector(- TPC_PTFE_pillar_h_dimension_x / 2 - TPC_PTFE_pillar_i_dimension_x / 2, 0., - (17.5 - 13.0) / 2 * mm));
	TPC_PTFE_pillar_GXe_solid = TPC_PTFE_pillar_GXe_solid_2;

	// Bottom Ring (p12)
	TPC_SS_BottomRing_solid =  new G4Tubs("TPC_SS_BottomRing_solid", 45.*mm, 70.*mm, 5.*mm / 2, 0.*deg, 360.*deg);	

	// SS pillar (p2a)
	TPC_SS_pillar_solid = new G4Tubs("TPC_SS_pillar_solid", 0.0*mm, 11.0*mm / 2, 25.0*mm / 2, 0.*deg, 360.*deg);

	// Top Ring (p8)
	TPC_SS_TopRing_solid_orig = new G4Tubs("TPC_SS_TopRing_solid_orig", 45.0*mm, 70.0*mm, 5.0*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_TopRing_solid_sub1_a = new G4Tubs("TPC_SS_TopRing_solid_sub1_a", 62.929*mm, 70.0*mm, 5.2*mm / 2, 10.*deg, 40.*deg);
	TPC_SS_TopRing_solid_sub1_b = new G4Tubs("TPC_SS_TopRing_solid_sub1_b", 62.929*mm, 70.0*mm, 5.2*mm / 2, 130.*deg, 40.*deg);
	TPC_SS_TopRing_solid_sub1_c = new G4Tubs("TPC_SS_TopRing_solid_sub1_c", 62.929*mm, 70.0*mm, 5.2*mm / 2, 190.*deg, 40.*deg);
	TPC_SS_TopRing_solid_sub1_d = new G4Tubs("TPC_SS_TopRing_solid_sub1_d", 62.929*mm, 70.0*mm, 5.2*mm / 2, 310.*deg, 40.*deg);
	G4double TopRing_sub2_shift = (3./(63.*2.*CLHEP::pi)*360.)*deg;
	TPC_SS_TopRing_solid_sub2_a = new G4Tubs("TPC_SS_TopRing_solid_sub2_a", 60.0*mm, 70.0*mm, 5.2*mm / 2, 10.*deg + TopRing_sub2_shift, 40.*deg - 2* TopRing_sub2_shift);
	TPC_SS_TopRing_solid_sub2_b = new G4Tubs("TPC_SS_TopRing_solid_sub2_b", 60.0*mm, 70.0*mm, 5.2*mm / 2, 130.*deg + TopRing_sub2_shift, 40.*deg - 2* TopRing_sub2_shift);
	TPC_SS_TopRing_solid_sub2_c = new G4Tubs("TPC_SS_TopRing_solid_sub2_c", 60.0*mm, 70.0*mm, 5.2*mm / 2, (180.+10.)*deg + TopRing_sub2_shift, 40.*deg - 2* TopRing_sub2_shift);
	TPC_SS_TopRing_solid_sub2_d = new G4Tubs("TPC_SS_TopRing_solid_sub2_d", 60.0*mm, 70.0*mm, 5.2*mm / 2, (180.+130.)*deg + TopRing_sub2_shift, 40.*deg - 2* TopRing_sub2_shift);
	TPC_SS_TopRing_solid_sub3 = new G4Tubs("TPC_SS_TopRing_solid_sub3", 0.0*mm, 3.0*mm, 5.2*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_TopRing_solid_sub4 = new G4Tubs("TPC_SS_TopRing_solid_sub4", 0.0*mm, 6.5*mm, 5.2*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_TopRing_solid_sub5 = new G4Tubs("TPC_SS_TopRing_solid_sub5", 0.0*mm, 2.5*mm, 5.2*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_TopRing_solid_1 = new G4SubtractionSolid("TPC_SS_TopRing_solid_1", TPC_SS_TopRing_solid_orig, TPC_SS_TopRing_solid_sub4, 0, G4ThreeVector(10.825*mm,-66.120*mm,0.));
	TPC_SS_TopRing_solid_2 = new G4SubtractionSolid("TPC_SS_TopRing_solid_2", TPC_SS_TopRing_solid_1, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(10.*deg + TopRing_sub2_shift),(63.*mm)*sin(10.*deg + TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_3 = new G4SubtractionSolid("TPC_SS_TopRing_solid_3", TPC_SS_TopRing_solid_2, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector(-(63.*mm)*cos(10.*deg + TopRing_sub2_shift),(63.*mm)*sin(10.*deg + TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_4 = new G4SubtractionSolid("TPC_SS_TopRing_solid_4", TPC_SS_TopRing_solid_3, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(10.*deg + TopRing_sub2_shift),-(63.*mm)*sin(10.*deg + TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_5 = new G4SubtractionSolid("TPC_SS_TopRing_solid_5", TPC_SS_TopRing_solid_4, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector(-(63.*mm)*cos(10.*deg + TopRing_sub2_shift),-(63.*mm)*sin(10.*deg + TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_6 = new G4SubtractionSolid("TPC_SS_TopRing_solid_6", TPC_SS_TopRing_solid_5, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(50.*deg - TopRing_sub2_shift),(63.*mm)*sin(50.*deg - TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_7 = new G4SubtractionSolid("TPC_SS_TopRing_solid_7", TPC_SS_TopRing_solid_6, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector(-(63.*mm)*cos(50.*deg - TopRing_sub2_shift),(63.*mm)*sin(50.*deg - TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_8 = new G4SubtractionSolid("TPC_SS_TopRing_solid_8", TPC_SS_TopRing_solid_7, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(50.*deg - TopRing_sub2_shift),-(63.*mm)*sin(50.*deg - TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_9 = new G4SubtractionSolid("TPC_SS_TopRing_solid_9", TPC_SS_TopRing_solid_8, TPC_SS_TopRing_solid_sub3, 0, G4ThreeVector(-(63.*mm)*cos(50.*deg - TopRing_sub2_shift),-(63.*mm)*sin(50.*deg - TopRing_sub2_shift),0.));
	TPC_SS_TopRing_solid_10 = new G4SubtractionSolid("TPC_SS_TopRing_solid_10", TPC_SS_TopRing_solid_9, TPC_SS_TopRing_solid_sub1_a, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_11 = new G4SubtractionSolid("TPC_SS_TopRing_solid_11", TPC_SS_TopRing_solid_10, TPC_SS_TopRing_solid_sub1_b, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_12 = new G4SubtractionSolid("TPC_SS_TopRing_solid_12", TPC_SS_TopRing_solid_11, TPC_SS_TopRing_solid_sub1_c, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_13 = new G4SubtractionSolid("TPC_SS_TopRing_solid_13", TPC_SS_TopRing_solid_12, TPC_SS_TopRing_solid_sub1_d, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_14 = new G4SubtractionSolid("TPC_SS_TopRing_solid_14", TPC_SS_TopRing_solid_13, TPC_SS_TopRing_solid_sub2_a, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_15 = new G4SubtractionSolid("TPC_SS_TopRing_solid_15", TPC_SS_TopRing_solid_14, TPC_SS_TopRing_solid_sub2_b, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_16 = new G4SubtractionSolid("TPC_SS_TopRing_solid_16", TPC_SS_TopRing_solid_15, TPC_SS_TopRing_solid_sub2_c, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_17 = new G4SubtractionSolid("TPC_SS_TopRing_solid_17", TPC_SS_TopRing_solid_16, TPC_SS_TopRing_solid_sub2_d, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_TopRing_solid_18 = TPC_SS_TopRing_solid_17;
	for (int a=0; a < 12; ++a)
	{ 
		G4double rotate_angle = a*(360./12);
		G4double TopRing_holes_XStep = cos(rotate_angle*deg)*52.0*mm;
		G4double TopRing_holes_YStep = sin(rotate_angle*deg)*52.0*mm;
		name.str("");
		name << "TPC_SS_TopRing_solid_18_" << a;
		TPC_SS_TopRing_solid_18 = new G4SubtractionSolid(name.str(), TPC_SS_TopRing_solid_18, TPC_SS_TopRing_solid_sub5, 0, G4ThreeVector(TopRing_holes_XStep,TopRing_holes_YStep,0.));
	}
	TPC_SS_TopRing_solid = TPC_SS_TopRing_solid_18;

	// PTFE-Filler (p10a)
	TPC_PTFE_filler_solid = new G4Tubs("TPC_PTFE_filler_solid", 40.*mm, 45.*mm, 40.*mm / 2, 0.*deg, 360.*deg);	

	// Bottom PMT Holder (p9)
	TPC_PTFE_BottomPMTHolder_solid_orig = new G4Tubs("TPC_PTFE_BottomPMTHolder_solid_orig", 39.*mm, 60.*mm, 5.*mm / 2, 0.*deg, 360.*deg);	
	TPC_PTFE_BottomPMTHolder_solid_union = new G4Tubs("TPC_PTFE_BottomPMTHolder_solid_union", 35.*mm, 40.*mm, 12.*mm / 2, 0.*deg, 360.*deg);
	TPC_PTFE_BottomPMTHolder_solid = new G4UnionSolid("TPC_PTFE_BottomPMTHolder_solid", TPC_PTFE_BottomPMTHolder_solid_orig, TPC_PTFE_BottomPMTHolder_solid_union, 0, G4ThreeVector(0., 0., (5.0*mm+12.*mm)/2-2.*mm));	

	// PTFE spacer 1 (p4) - "the upper one"
	TPC_PTFE_spacer1_solid = new G4Tubs("TPC_PTFE_spacer1_solid", 35.*mm, 60.*mm, 2.*mm / 2, 0.*deg, 360.*deg);

	// PTFE spacer 2 (p4) - "the lower one"
	TPC_PTFE_spacer2_solid = new G4Tubs("TPC_PTFE_spacer2_solid", 35.*mm, 60.*mm, 5.*mm / 2, 0.*deg, 360.*deg);

	// Reflector (p6)
	TPC_PTFE_reflector_LXe_solid = new G4Tubs("TPC_PTFE_reflector_LXe_solid", 35.*mm, 40.*mm, 68.*mm / 2, 0.*deg, 360.*deg);
	TPC_PTFE_reflector_GXe_solid = new G4Tubs("TPC_PTFE_reflector_GXe_solid", 35.*mm, 40.*mm, (70.-68.)*mm / 2, 0.*deg, 360.*deg);

	// Gate (p3b)
	TPC_SS_gate_ring_solid_orig =  new G4Tubs("TPC_SS_gate_ring_solid_orig", 50.*mm, 70.*mm, 3.*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_gate_ring_solid_sub1_a = new G4Tubs("TPC_SS_gate_ring_solid_sub1_a", 62.929*mm, 70.0*mm, 3.2*mm / 2, (360.-10.)*deg, (70.+10.)*deg);
	TPC_SS_gate_ring_solid_sub1_b = new G4Tubs("TPC_SS_gate_ring_solid_sub1_b", 62.929*mm, 70.0*mm, 3.2*mm / 2, 75.*deg, (105.-75.)*deg);
	TPC_SS_gate_ring_solid_sub1_c = new G4Tubs("TPC_SS_gate_ring_solid_sub1_c", 62.929*mm, 70.0*mm, 3.2*mm / 2, 110.*deg, ((360.-170.)-110.)*deg);
	TPC_SS_gate_ring_solid_sub1_d = new G4Tubs("TPC_SS_gate_ring_solid_sub1_d", 62.929*mm, 70.0*mm, 3.2*mm / 2, (360.-165.)*deg, ((360.-135.)-(360.-165.))*deg);
	TPC_SS_gate_ring_solid_sub1_e = new G4Tubs("TPC_SS_gate_ring_solid_sub1_e", 62.929*mm, 70.0*mm, 3.2*mm / 2, (360.-130.)*deg, ((360.-50.)-(360.-130.))*deg);
	TPC_SS_gate_ring_solid_sub1_f = new G4Tubs("TPC_SS_gate_ring_solid_sub1_f", 62.929*mm, 70.0*mm, 3.2*mm / 2, (360.-45.)*deg, ((360.-15.)-(360.-45.))*deg);
	G4double gate_ring_sub2_shift = (3./(63.*2.*CLHEP::pi)*360.)*deg;
	TPC_SS_gate_ring_solid_sub2_a = new G4Tubs("TPC_SS_gate_ring_solid_sub2_a", 60.0*mm, 70.0*mm, 3.2*mm / 2, (360.-10.)*deg + gate_ring_sub2_shift, (70.+10.)*deg - 2*gate_ring_sub2_shift);
	TPC_SS_gate_ring_solid_sub2_b = new G4Tubs("TPC_SS_gate_ring_solid_sub2_b", 60.0*mm, 70.0*mm, 3.2*mm / 2, 75.*deg + gate_ring_sub2_shift, (105.-75.)*deg - 2*gate_ring_sub2_shift);
	TPC_SS_gate_ring_solid_sub2_c = new G4Tubs("TPC_SS_gate_ring_solid_sub2_c", 60.0*mm, 70.0*mm, 3.2*mm / 2, 110.*deg + gate_ring_sub2_shift, ((360.-170.)-110.)*deg - 2*gate_ring_sub2_shift);
	TPC_SS_gate_ring_solid_sub2_d = new G4Tubs("TPC_SS_gate_ring_solid_sub2_d", 60.0*mm, 70.0*mm, 3.2*mm / 2, (360.-165.)*deg + gate_ring_sub2_shift, ((360.-135.)-(360.-165.))*deg - 2*gate_ring_sub2_shift);
	TPC_SS_gate_ring_solid_sub2_e = new G4Tubs("TPC_SS_gate_ring_solid_sub2_e", 60.0*mm, 70.0*mm, 3.2*mm / 2, (360.-130.)*deg + gate_ring_sub2_shift, ((360.-50.)-(360.-130.))*deg - 2*gate_ring_sub2_shift);
	TPC_SS_gate_ring_solid_sub2_f = new G4Tubs("TPC_SS_gate_ring_solid_sub2_f", 60.0*mm, 70.0*mm, 3.2*mm / 2, (360.-45.)*deg + gate_ring_sub2_shift, ((360.-15.)-(360.-45.))*deg - 2*gate_ring_sub2_shift);
	TPC_SS_gate_ring_solid_sub3 = new G4Tubs("TPC_SS_gate_ring_solid_sub3", 0.0*mm, 3.0*mm, 3.2*mm / 2, 0.*deg, 360.*deg);
	TPC_SS_gate_ring_solid_1 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_1", TPC_SS_gate_ring_solid_orig, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-10.)*deg + gate_ring_sub2_shift),(63.*mm)*sin((360.-10.)*deg + gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_2 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_2", TPC_SS_gate_ring_solid_1, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((70.)*deg - gate_ring_sub2_shift),(63.*mm)*sin((70.)*deg - gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_3 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_3", TPC_SS_gate_ring_solid_2, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(75.*deg + gate_ring_sub2_shift),(63.*mm)*sin(75.*deg + gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_4 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_4", TPC_SS_gate_ring_solid_3, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((105.)*deg - gate_ring_sub2_shift),(63.*mm)*sin((105.)*deg - gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_5 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_5", TPC_SS_gate_ring_solid_4, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(110.*deg + gate_ring_sub2_shift),(63.*mm)*sin(110.*deg + gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_6 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_6", TPC_SS_gate_ring_solid_5, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos(((360.-170.))*deg - gate_ring_sub2_shift),(63.*mm)*sin(((360.-170.))*deg - gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_7 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_7", TPC_SS_gate_ring_solid_6, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-165.)*deg + gate_ring_sub2_shift),(63.*mm)*sin((360.-165.)*deg + gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_8 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_8", TPC_SS_gate_ring_solid_7, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-135.)*deg - gate_ring_sub2_shift),(63.*mm)*sin((360.-135.)*deg - gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_9 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_9", TPC_SS_gate_ring_solid_8, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-130.)*deg + gate_ring_sub2_shift),(63.*mm)*sin((360.-130.)*deg + gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_10 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_10", TPC_SS_gate_ring_solid_9, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-50.)*deg - gate_ring_sub2_shift),(63.*mm)*sin((360.-50.)*deg - gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_11 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_11", TPC_SS_gate_ring_solid_10, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-45.)*deg + gate_ring_sub2_shift),(63.*mm)*sin((360.-45.)*deg + gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_12 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_12", TPC_SS_gate_ring_solid_11, TPC_SS_gate_ring_solid_sub3, 0, G4ThreeVector((63.*mm)*cos((360.-15.)*deg - gate_ring_sub2_shift),(63.*mm)*sin((360.-15.)*deg - gate_ring_sub2_shift),0.));
	TPC_SS_gate_ring_solid_13 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_13", TPC_SS_gate_ring_solid_12, TPC_SS_gate_ring_solid_sub1_a, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_14 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_14", TPC_SS_gate_ring_solid_13, TPC_SS_gate_ring_solid_sub1_b, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_15 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_15", TPC_SS_gate_ring_solid_14, TPC_SS_gate_ring_solid_sub1_c, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_16 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_16", TPC_SS_gate_ring_solid_15, TPC_SS_gate_ring_solid_sub1_d, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_17 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_17", TPC_SS_gate_ring_solid_16, TPC_SS_gate_ring_solid_sub1_e, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_18 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_18", TPC_SS_gate_ring_solid_17, TPC_SS_gate_ring_solid_sub1_f, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_19 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_19", TPC_SS_gate_ring_solid_18, TPC_SS_gate_ring_solid_sub2_a, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_20 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_20", TPC_SS_gate_ring_solid_19, TPC_SS_gate_ring_solid_sub2_b, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_21 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_21", TPC_SS_gate_ring_solid_20, TPC_SS_gate_ring_solid_sub2_c, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_22 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_22", TPC_SS_gate_ring_solid_21, TPC_SS_gate_ring_solid_sub2_d, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_23 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_23", TPC_SS_gate_ring_solid_22, TPC_SS_gate_ring_solid_sub2_e, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid_24 = new G4SubtractionSolid("TPC_SS_gate_ring_solid_24", TPC_SS_gate_ring_solid_23, TPC_SS_gate_ring_solid_sub2_f, 0, G4ThreeVector(0.,0.,0.));
	TPC_SS_gate_ring_solid = TPC_SS_gate_ring_solid_24;

	// Top PMT Holder (p1)
	TPC_PTFE_TopPMTHolder_solid_orig = new G4Tubs("TPC_PTFE_TopPMTHolder_solid_orig", 0.*mm, 60.*mm, 8.*mm / 2, 0.*deg, 360.*deg);
	TPC_PTFE_TopPMTHolder_solid_sub1_1 = new G4Box("TPC_PTFE_TopPMTHolder_solid_sub1_1", 22.0*mm / 2, 26.0*mm / 2, 6.0*mm / 2);
	TPC_PTFE_TopPMTHolder_solid_sub1_2 = new G4Box("TPC_PTFE_TopPMTHolder_solid_sub1_2", 26.0*mm / 2, 22.0*mm / 2, 6.0*mm / 2);
	TPC_PTFE_TopPMTHolder_solid_sub1_3 = new G4Tubs("TPC_PTFE_TopPMTHolder_solid_sub1_3", 0.*mm, 2.*mm, 6.*mm / 2, 0.*deg, 360.*deg);
	TPC_PTFE_TopPMTHolder_solid_sub1_a = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub1_a", TPC_PTFE_TopPMTHolder_solid_sub1_1, TPC_PTFE_TopPMTHolder_solid_sub1_2, 0, G4ThreeVector(0., 0., 0.));
	TPC_PTFE_TopPMTHolder_solid_sub1_b = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub1_b", TPC_PTFE_TopPMTHolder_solid_sub1_a, TPC_PTFE_TopPMTHolder_solid_sub1_3, 0, G4ThreeVector(11.*mm, 11.*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub1_c = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub1_c", TPC_PTFE_TopPMTHolder_solid_sub1_b, TPC_PTFE_TopPMTHolder_solid_sub1_3, 0, G4ThreeVector(-11.*mm, 11.*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub1_d = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub1_d", TPC_PTFE_TopPMTHolder_solid_sub1_c, TPC_PTFE_TopPMTHolder_solid_sub1_3, 0, G4ThreeVector(11.*mm, -11.*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub1 = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub1", TPC_PTFE_TopPMTHolder_solid_sub1_d, TPC_PTFE_TopPMTHolder_solid_sub1_3, 0, G4ThreeVector(-11.*mm, -11.*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub2_1 = new G4Box("TPC_PTFE_TopPMTHolder_solid_sub2_1", 17.0*mm / 2, 21.0*mm / 2, 2.0*mm / 2);
	TPC_PTFE_TopPMTHolder_solid_sub2_2 = new G4Box("TPC_PTFE_TopPMTHolder_solid_sub2_2", 21.0*mm / 2, 17.0*mm / 2, 2.0*mm / 2);
	TPC_PTFE_TopPMTHolder_solid_sub2_3 = new G4Tubs("TPC_PTFE_TopPMTHolder_solid_sub2_3", 0.*mm, 2.*mm, 2.*mm / 2, 0.*deg, 360.*deg);
	TPC_PTFE_TopPMTHolder_solid_sub2_a = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub2_a", TPC_PTFE_TopPMTHolder_solid_sub2_1, TPC_PTFE_TopPMTHolder_solid_sub2_2, 0, G4ThreeVector(0., 0., 0.));
	TPC_PTFE_TopPMTHolder_solid_sub2_b = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub2_b", TPC_PTFE_TopPMTHolder_solid_sub2_a, TPC_PTFE_TopPMTHolder_solid_sub2_3, 0, G4ThreeVector(8.5*mm, 8.5*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub2_c = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub2_c", TPC_PTFE_TopPMTHolder_solid_sub2_b, TPC_PTFE_TopPMTHolder_solid_sub2_3, 0, G4ThreeVector(-8.5*mm, 8.5*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub2_d = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub2_d", TPC_PTFE_TopPMTHolder_solid_sub2_c, TPC_PTFE_TopPMTHolder_solid_sub2_3, 0, G4ThreeVector(8.5*mm, -8.5*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_sub2 = new G4UnionSolid("TPC_PTFE_TopPMTHolder_solid_sub2", TPC_PTFE_TopPMTHolder_solid_sub2_d, TPC_PTFE_TopPMTHolder_solid_sub2_3, 0, G4ThreeVector(-8.5*mm, -8.5*mm, 0.));
	TPC_PTFE_TopPMTHolder_solid_1 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_1", TPC_PTFE_TopPMTHolder_solid_orig, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(-14.*mm, 28.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_2 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_2", TPC_PTFE_TopPMTHolder_solid_1, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(14.*mm, 28.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_3 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_3", TPC_PTFE_TopPMTHolder_solid_2, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(14.*mm, -28.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_4 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_4", TPC_PTFE_TopPMTHolder_solid_3, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(-14.*mm, -28.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_5 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_5", TPC_PTFE_TopPMTHolder_solid_4, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(-28.*mm, 0.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_6 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_6", TPC_PTFE_TopPMTHolder_solid_5, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(0.*mm, 0.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_7 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_7", TPC_PTFE_TopPMTHolder_solid_6, TPC_PTFE_TopPMTHolder_solid_sub1, 0, G4ThreeVector(28.*mm, 0.*mm, 2.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_8 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_8", TPC_PTFE_TopPMTHolder_solid_7, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(-14.*mm, 28.*mm, -6.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_9 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_9", TPC_PTFE_TopPMTHolder_solid_8, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(14.*mm, 28.*mm, -6.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_10 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_10", TPC_PTFE_TopPMTHolder_solid_9, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(14.*mm, -28.*mm, -6.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_11 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_11", TPC_PTFE_TopPMTHolder_solid_10, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(-14.*mm, -28.*mm, -6.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_12 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_12", TPC_PTFE_TopPMTHolder_solid_11, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(-28.*mm, 0.*mm, -6.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid_13 = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid_13", TPC_PTFE_TopPMTHolder_solid_12, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(0.*mm, 0.*mm, -6.*mm / 2));
	TPC_PTFE_TopPMTHolder_solid = new G4SubtractionSolid("TPC_PTFE_TopPMTHolder_solid", TPC_PTFE_TopPMTHolder_solid_13, TPC_PTFE_TopPMTHolder_solid_sub2, 0, G4ThreeVector(28.*mm, 0.*mm, -6.*mm / 2));

	// Cathode (p3)
	TPC_SS_cathode_ring_solid = new G4Tubs("TPC_SS_cathode_ring_solid", 50.*mm, 60.*mm, 3.*mm / 2, 0.*deg, 360.*deg);

	// Anode (p3)
	TPC_SS_anode_ring_solid = new G4Tubs("TPC_SS_anode_ring_solid", 50.*mm, 60.*mm, 3.*mm / 2, 0.*deg, 360.*deg);

	// Top Mesh (p3)
	TPC_SS_TopMesh_ring_solid = new G4Tubs("TPC_SS_TopMesh_ring_solid", 50.*mm, 60.*mm, 3.*mm / 2, 0.*deg, 360.*deg);

	// Rod (p7)
	TPC_Torlon_rod_solid_orig = new G4Orb("TPC_Torlon_rod_solid_orig", 1.1*mm);
	TPC_Torlon_rod_solid_1 = new G4Tubs("TPC_Torlon_rod_solid_1", 0.*mm, 1.1*mm, (50.-40.)*mm / 2, 0.*deg, 360.*deg);
	TPC_Torlon_rod_solid = new G4UnionSolid("TPC_Torlon_rod_solid", TPC_Torlon_rod_solid_orig, TPC_Torlon_rod_solid_1, rmy90, G4ThreeVector(0., 0., 0.));

	// Weir for leveling (p13)
		// LXe original filling part -> ToDo: variable GXe filling
	TPC_PEEK_weir_LXe_solid_orig = new G4Tubs("TPC_PEEK_weir_LXe_solid_orig", 60.*mm, 73.*mm, 83.5*mm / 2, 130.*deg, (170.-130.)*deg);
	TPC_PEEK_weir_LXe_solid_sub1 = new G4Tubs("TPC_PEEK_weir_LXe_solid_sub1", 0.*mm, 5.*mm, 70.5*mm / 2, 0.*deg, 360.*deg);
	TPC_PEEK_weir_LXe_solid_sub2 = new G4Tubs("TPC_PEEK_weir_LXe_solid_sub2", 61.5*mm, 71.5*mm, 70.5*mm / 2, 136.*deg, (164.-136.)*deg);
	TPC_PEEK_weir_LXe_solid_1 = new G4SubtractionSolid("TPC_PEEK_weir_LXe_solid_1", TPC_PEEK_weir_LXe_solid_orig, TPC_PEEK_weir_LXe_solid_sub2, 0, G4ThreeVector(0.*mm, 0.*mm, (83.5-70.5)*mm / 2));
	TPC_PEEK_weir_LXe_solid_2 = new G4SubtractionSolid("TPC_PEEK_weir_LXe_solid_2", TPC_PEEK_weir_LXe_solid_1, TPC_PEEK_weir_LXe_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), (83.5-70.5)*mm / 2));
	TPC_PEEK_weir_LXe_solid = new G4SubtractionSolid("TPC_PEEK_weir_LXe_solid", TPC_PEEK_weir_LXe_solid_2, TPC_PEEK_weir_LXe_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), (83.5-70.5)*mm / 2));

		// LXe extra filling part -> ToDo: variable GXe filling
	TPC_PEEK_weir_LXe2_solid_orig = new G4Tubs("TPC_PEEK_weir_LXe2_solid_orig", 60.*mm, 73.*mm, 5.5*mm / 2, 130.*deg, (170.-130.)*deg);
	TPC_PEEK_weir_LXe2_solid_sub1 = new G4Tubs("TPC_PEEK_weir_LXe2_solid_sub1", 0.*mm, 5.*mm, 5.5*mm / 2, 0.*deg, 360.*deg);
	TPC_PEEK_weir_LXe2_solid_sub2 = new G4Tubs("TPC_PEEK_weir_LXe_solid_sub2", 61.5*mm, 71.5*mm, 5.5*mm / 2, 136.*deg, (164.-136.)*deg);
	TPC_PEEK_weir_LXe2_solid_1 = new G4SubtractionSolid("TPC_PEEK_weir_LXe2_solid_1", TPC_PEEK_weir_LXe2_solid_orig, TPC_PEEK_weir_LXe2_solid_sub2, 0, G4ThreeVector(0.*mm, 0.*mm, 0*mm));
	TPC_PEEK_weir_LXe2_solid_2 = new G4SubtractionSolid("TPC_PEEK_weir_LXe2_solid_2", TPC_PEEK_weir_LXe2_solid_1, TPC_PEEK_weir_LXe2_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), 0*mm));
	TPC_PEEK_weir_LXe2_solid = new G4SubtractionSolid("TPC_PEEK_weir_LXe2_solid", TPC_PEEK_weir_LXe2_solid_2, TPC_PEEK_weir_LXe2_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), 0*mm));



	// LXe extra filling (increase LXe filling level to weir) // ToDo: subtract other solids
	LXe_extra_filling_solid_orig = new G4Tubs("LXe_extra_filling_solid_orig", 0.*cm, cryostat_innerRadius, LXe_extra_filling_height/2, 0.*deg, 360.*deg);	
	if (height_LXe_GXe_cylinder > 0. && height_GXe_GXe_cylinder <= 0.)	
	{
	LXe_extra_filling_solid_1 =  new G4SubtractionSolid("LXe_extra_filling_solid_1", LXe_extra_filling_solid_orig, LXe_weir_2_solid, 0, G4ThreeVector(0.*mm, 0.*mm, - GXe_height/2 + height_LXe_GXe_cylinder/2  + (GXe_height - LXe_extra_filling_height)/2));
	}
	if (height_LXe_GXe_cylinder <= 0. && height_GXe_GXe_cylinder > 0.)	
	{
	LXe_extra_filling_solid_1 =  new G4SubtractionSolid("LXe_extra_filling_solid_1", LXe_extra_filling_solid_orig, GXe_weir_2_solid, 0, G4ThreeVector(0.*mm, 0.*mm, - GXe_height/2 + height_LXe_GXe_cylinder + height_GXe_GXe_cylinder/2  + (GXe_height - LXe_extra_filling_height)/2));
	}
	if (height_LXe_GXe_cylinder > 0. && height_GXe_GXe_cylinder > 0.)	
	{
	LXe_extra_filling_solid_1a =  new G4SubtractionSolid("LXe_extra_filling_solid_1a", LXe_extra_filling_solid_orig, GXe_weir_2_solid, 0, G4ThreeVector(0.*mm, 0.*mm, - GXe_height/2 + height_LXe_GXe_cylinder + height_GXe_GXe_cylinder/2  + (GXe_height - LXe_extra_filling_height)/2));
	LXe_extra_filling_solid_1 =  new G4SubtractionSolid("LXe_extra_filling_solid_1", LXe_extra_filling_solid_1a, LXe_weir_2_solid, 0, G4ThreeVector(0.*mm, 0.*mm, - GXe_height/2 + height_LXe_GXe_cylinder/2  + (GXe_height - LXe_extra_filling_height)/2));
	}
	LXe_extra_filling_solid_2 =  new G4SubtractionSolid("LXe_extra_filling_solid_2", LXe_extra_filling_solid_1, TPC_SS_TopRing_solid, 0, G4ThreeVector(0.*mm, 0.*mm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 5.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	LXe_extra_filling_solid_3 =  new G4SubtractionSolid("LXe_extra_filling_solid_3", LXe_extra_filling_solid_2, TPC_PTFE_spacer1_solid, 0, G4ThreeVector(0.*mm, 0.*mm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 73.5*mm - 2.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	LXe_extra_filling_solid_4 =  new G4SubtractionSolid("LXe_extra_filling_solid_4", LXe_extra_filling_solid_3, TPC_PTFE_spacer2_solid, 0, G4ThreeVector(0.*mm, 0.*mm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 78.5*mm - 5.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	LXe_extra_filling_solid_5 =  new G4SubtractionSolid("LXe_extra_filling_solid_5", LXe_extra_filling_solid_4, TPC_PTFE_reflector_GXe_solid, 0, G4ThreeVector(0.*mm, 0.*mm, - GXe_height / 2 + (70.-68.)*mm / 2  + (GXe_height - LXe_extra_filling_height)/2));
	LXe_extra_filling_solid_6 =  new G4SubtractionSolid("LXe_extra_filling_solid_6", LXe_extra_filling_solid_5, TPC_SS_gate_ring_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  - GXe_height / 2 + 3.*mm / 2  + (GXe_height - LXe_extra_filling_height)/2));
	LXe_extra_filling_solid_7 =  new G4SubtractionSolid("LXe_extra_filling_solid_7", LXe_extra_filling_solid_6, TPC_PTFE_TopPMTHolder_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 62.5*mm - 8.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	LXe_extra_filling_solid_8 =  new G4SubtractionSolid("LXe_extra_filling_solid_8", LXe_extra_filling_solid_7, TPC_SS_anode_ring_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 75.5*mm - 3.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	LXe_extra_filling_solid_9 =  new G4SubtractionSolid("LXe_extra_filling_solid_9", LXe_extra_filling_solid_8, TPC_SS_TopMesh_ring_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 70.5*mm - 3.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	LXe_extra_filling_solid_10 =  new G4SubtractionSolid("LXe_extra_filling_solid_10", LXe_extra_filling_solid_9, TPC_PEEK_weir_LXe2_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  -GXe_height / 2 + 5.5*mm / 2  + (GXe_height - LXe_extra_filling_height)/2));
	LXe_extra_filling_solid_11 = LXe_extra_filling_solid_10;
	for (int a=0; a < TPC_PTFE_pillar_number; ++a)
	{ 
		G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);
		G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
		pillarRotation->rotateZ(rotate_angle*deg);
		G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;
		G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;
		name.str("");
		name << "LXe_extra_filling_solid_11_" << a;
		LXe_extra_filling_solid_11 =  new G4SubtractionSolid(name.str(), LXe_extra_filling_solid_11, TPC_PTFE_pillar_GXe_solid, pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	}
	LXe_extra_filling_solid_12 = LXe_extra_filling_solid_11;
	for (int a=0; a < TPC_PTFE_pillar_number; ++a)
	{ 
		G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);
		G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;
		G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;
		name.str("");
		name << "LXe_extra_filling_solid_12_" << a;
		LXe_extra_filling_solid_12 =  new G4SubtractionSolid(name.str(), LXe_extra_filling_solid_12, TPC_SS_pillar_solid, 0, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm + 25.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	}
	LXe_extra_filling_solid = LXe_extra_filling_solid_12;

// ToDo: Add missing TPC components.

//**************************************************LOGICALVOLUMES*****************************************************

	TPC_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "TPC_Logical", 0, 0, 0);
	LXe_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "LXe_Logical", 0, 0, 0);
	GXe_Logical = new G4LogicalVolume(GXe_cylinder, GXe, "GXe_Logical", 0, 0, 0);
	if (height_LXe_TPC_cylinder > 0.)	
		{
		LXe_weir_1_log = new G4LogicalVolume(LXe_weir_1_solid, LXe, "LXe_weir_1_log");
		}
	if (height_GXe_TPC_cylinder > 0.)	
		{
		GXe_weir_1_log = new G4LogicalVolume(GXe_weir_1_solid, GXe, "GXe_weir_1_log");
		}
	if (height_LXe_GXe_cylinder > 0.)	
		{
		LXe_weir_2_log = new G4LogicalVolume(LXe_weir_2_solid, LXe, "LXe_weir_2_log");
		}
	if (height_GXe_GXe_cylinder > 0.)	
		{
		GXe_weir_2_log = new G4LogicalVolume(GXe_weir_2_solid, GXe, "GXe_weir_2_log");
		}
	LXe_extra_filling_log = new G4LogicalVolume(LXe_extra_filling_solid, LXe, "LXe_extra_filling_log");

	TPC_SS_PMTfixture_log = new G4LogicalVolume(TPC_SS_PMTfixture_solid, SS304LSteel, "TPC_SS_PMTfixture_log");
	TPC_Al_filler_log = new G4LogicalVolume(TPC_Al_filler_solid, Aluminium, "TPC_Al_filler_log");
	TPC_Cu_FSE_log = new G4LogicalVolume(TPC_Cu_FSE_solid, Copper, "TPC_Cu_FSE_log");
	TPC_PTFE_pillar_LXe_log = new G4LogicalVolume(TPC_PTFE_pillar_LXe_solid, Teflon, "TPC_PTFE_pillar_LXe_log");
	TPC_PTFE_pillar_GXe_log = new G4LogicalVolume(TPC_PTFE_pillar_GXe_solid, Teflon, "TPC_PTFE_pillar_GXe_log");
	TPC_SS_BottomRing_log = new G4LogicalVolume(TPC_SS_BottomRing_solid, SS304LSteel, "TPC_SS_BottomRing_log");
	TPC_SS_pillar_log = new G4LogicalVolume(TPC_SS_pillar_solid, SS304LSteel, "TPC_SS_pillar_log");
	TPC_SS_TopRing_log = new G4LogicalVolume(TPC_SS_TopRing_solid, SS304LSteel, "TPC_SS_TopRing_log");
	TPC_PTFE_filler_log = new G4LogicalVolume(TPC_PTFE_filler_solid, Teflon, "TPC_PTFE_filler_log");
	TPC_PTFE_BottomPMTHolder_log = new G4LogicalVolume(TPC_PTFE_BottomPMTHolder_solid, Teflon, "TPC_PTFE_BottomPMTHolder_log");
	TPC_PTFE_spacer1_log = new G4LogicalVolume(TPC_PTFE_spacer1_solid, Teflon, "TPC_PTFE_spacer1_log");
	TPC_PTFE_spacer2_log = new G4LogicalVolume(TPC_PTFE_spacer2_solid, Teflon, "TPC_PTFE_spacer2_log");
	TPC_PTFE_reflector_LXe_log = new G4LogicalVolume(TPC_PTFE_reflector_LXe_solid, Teflon, "TPC_PTFE_reflector_LXe_log");
	TPC_PTFE_reflector_GXe_log = new G4LogicalVolume(TPC_PTFE_reflector_GXe_solid, Teflon, "TPC_PTFE_reflector_GXe_log");
	TPC_SS_gate_ring_log = new G4LogicalVolume(TPC_SS_gate_ring_solid, SS304LSteel, "TPC_SS_gate_ring_log");
	TPC_PTFE_TopPMTHolder_log = new G4LogicalVolume(TPC_PTFE_TopPMTHolder_solid, Teflon, "TPC_PTFE_TopPMTHolder_log");
	TPC_SS_cathode_ring_log =  new G4LogicalVolume(TPC_SS_cathode_ring_solid, SS304LSteel, "TPC_SS_cathode_ring_log");
	TPC_SS_anode_ring_log =  new G4LogicalVolume(TPC_SS_anode_ring_solid, SS304LSteel, "TPC_SS_anode_ring_log");
	TPC_SS_TopMesh_ring_log =  new G4LogicalVolume(TPC_SS_TopMesh_ring_solid, SS304LSteel, "TPC_SS_TopMesh_ring_log");
	TPC_Torlon_rod_log = new G4LogicalVolume(TPC_Torlon_rod_solid, Torlon, "TPC_Torlon_rod_log");
	TPC_PEEK_weir_LXe_log = new G4LogicalVolume(TPC_PEEK_weir_LXe_solid, PEEK, "TPC_PEEK_weir_LXe_log");
	TPC_PEEK_weir_LXe2_log = new G4LogicalVolume(TPC_PEEK_weir_LXe2_solid, PEEK, "TPC_PEEK_weir_LXe2_log");

  // Create Logical XebraPMTsR11410 Volume from corresponding class
	XebraPMTsR11410 *r11410 = new XebraPMTsR11410(this);
	PMTR11410LogicalVolume = r11410->Construct();

  // Create Logical XebraPMTsR8520 Volume from corresponding class
	XebraPMTsR8520 *r8520 = new XebraPMTsR8520(this);
	PMTR8520LogicalVolume = r8520->Construct();

  
//***********************************************PHYSICALVOLUME*******************************************************

	// Filling TPC Volume with LXe
	LXe_Physical = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), LXe_Logical,"LXe_TPC", TPC_Logical, false, 0);
  
	// Replacing LXe with GXe
	GXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height/2), GXe_Logical,"GXe_TPC", LXe_Logical, false, 0);

	// Filling weir with LXe and GXe
	if (height_LXe_TPC_cylinder > 0.)
		{
		LXe_weir_1_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, cryostat_innerHeight/2 - GXe_height - height_GXe_TPC_cylinder - height_LXe_TPC_cylinder/2), LXe_weir_1_log,"LXe_weir_1", LXe_Logical, 0, 0);
		}
	if (height_GXe_TPC_cylinder > 0.)	
		{
		GXe_weir_1_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, cryostat_innerHeight/2 - GXe_height - height_GXe_TPC_cylinder/2), GXe_weir_1_log,"GXe_weir_1", LXe_Logical, 0, 0);
		}
	if (height_LXe_GXe_cylinder > 0.)	
		{
		LXe_weir_2_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height/2 + height_LXe_GXe_cylinder/2), LXe_weir_2_log,"LXe_weir_2", GXe_Logical, 0, 0);
		}
	if (height_GXe_GXe_cylinder > 0.)	
		{
		GXe_weir_2_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height/2 + height_LXe_GXe_cylinder + height_GXe_GXe_cylinder/2), GXe_weir_2_log,"GXe_weir_2", GXe_Logical, 0, 0);
		}

	// Adding extra LXe filling up to weir level
	LXe_extra_filling_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height/2 + LXe_extra_filling_height/2), LXe_extra_filling_log,"LXe_extra_filling", GXe_Logical, 0, 0);

	// Placing all TPC components fully emerged in LXe
	TPC_SS_PMTfixture_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, 5.*mm / 2 - TPC_dimension_z / 2 + TPC_offset_z), TPC_SS_PMTfixture_log,"TPC_SS_PMTfixture", LXe_Logical, 0, 0);
	TPC_Al_filler_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 135.*mm / 2 + TPC_offset_z), TPC_Al_filler_log,"TPC_Al_filler", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_1_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-1) * 13 * mm + 10.0*mm / 2 + TPC_offset_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_1", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_2_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-2) * 13 * mm + 10.0*mm / 2 + TPC_offset_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_2", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_3_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-3) * 13 * mm + 10.0*mm / 2 + TPC_offset_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_3", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_4_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-4) * 13 * mm + 10.0*mm / 2 + TPC_offset_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_4", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_5_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-5) * 13 * mm + 10.0*mm / 2 + TPC_offset_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_5", LXe_Logical, 0, 0); 
	TPC_SS_BottomRing_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 135.*mm + 5.*mm / 2 + TPC_offset_z), TPC_SS_BottomRing_log,"TPC_SS_BottomRing", LXe_Logical, 0, 0); 
	TPC_PTFE_filler_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 140.*mm - 40.*mm / 2 + TPC_offset_z), TPC_PTFE_filler_log,"TPC_PTFE_filler", LXe_Logical, 0, 0);
	TPC_PTFE_BottomPMTHolder_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 140.*mm + 5.*mm / 2 + TPC_offset_z), TPC_PTFE_BottomPMTHolder_log,"TPC_PTFE_BottomPMTHolder", LXe_Logical, 0, 0);
	TPC_PTFE_reflector_LXe_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 155.5*mm + 68.*mm / 2 + TPC_offset_z), TPC_PTFE_reflector_LXe_log,"TPC_PTFE_reflector_LXe", LXe_Logical, 0, 0);
	TPC_SS_cathode_ring_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 152.0*mm + 3.*mm / 2 + TPC_offset_z), TPC_SS_cathode_ring_log,"TPC_SS_cathode_ring", LXe_Logical, 0, 0);
	TPC_PEEK_weir_LXe_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 140.0*mm + 83.5*mm / 2 + TPC_offset_z), TPC_PEEK_weir_LXe_log,"TPC_PEEK_weir_LXe", LXe_Logical, 0, 0);
	TPC_Torlon_rod_1_phys =  new G4PVPlacement(rmz300,G4ThreeVector((50.+40.)*mm / 2 * cos(60.*deg), (50.+40.)*mm / 2 * sin(60.*deg), -TPC_dimension_z / 2 + 170.0*mm + TPC_offset_z), TPC_Torlon_rod_log,"TPC_Torlon_rod_1", LXe_Logical, 0, 0);
	TPC_Torlon_rod_2_phys =  new G4PVPlacement(rmz300,G4ThreeVector((50.+40.)*mm / 2 * cos(60.*deg), (50.+40.)*mm / 2 * sin(60.*deg), -TPC_dimension_z / 2 + 222.0*mm + TPC_offset_z), TPC_Torlon_rod_log,"TPC_Torlon_rod_2", LXe_Logical, 0, 0);
	TPC_Torlon_rod_3_phys =  new G4PVPlacement(rmz180,G4ThreeVector((50.+40.)*mm / 2 * cos(180.*deg), (50.+40.)*mm / 2 * sin(180.*deg), -TPC_dimension_z / 2 + 170.0*mm + TPC_offset_z), TPC_Torlon_rod_log,"TPC_Torlon_rod_3", LXe_Logical, 0, 0);
	TPC_Torlon_rod_4_phys =  new G4PVPlacement(rmz180,G4ThreeVector((50.+40.)*mm / 2 * cos(180.*deg), (50.+40.)*mm / 2 * sin(180.*deg), -TPC_dimension_z / 2 + 222.0*mm + TPC_offset_z), TPC_Torlon_rod_log,"TPC_Torlon_rod_4", LXe_Logical, 0, 0);
	TPC_Torlon_rod_5_phys =  new G4PVPlacement(rmz60,G4ThreeVector((50.+40.)*mm / 2 * cos(300.*deg), (50.+40.)*mm / 2 * sin(300.*deg), -TPC_dimension_z / 2 + 170.0*mm + TPC_offset_z), TPC_Torlon_rod_log,"TPC_Torlon_rod_5", LXe_Logical, 0, 0);
	TPC_Torlon_rod_6_phys =  new G4PVPlacement(rmz60,G4ThreeVector((50.+40.)*mm / 2 * cos(300.*deg), (50.+40.)*mm / 2 * sin(300.*deg), -TPC_dimension_z / 2 + 222.0*mm + TPC_offset_z), TPC_Torlon_rod_log,"TPC_Torlon_rod_6", LXe_Logical, 0, 0);
	
	// Placing Teflon pillars fully emerged in LXe around active TPC
	for (int a=0; a < TPC_PTFE_pillar_number; ++a)
	{ 
		G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);
		G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
		pillarRotation->rotateZ(rotate_angle*deg);

		G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_a_position_r;
		G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_a_position_r;

		name.str("");
		name << "TPC_PTFE_pillar_LXe_" << a;
		TPC_PTFE_pillar_LXe_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
	}

	//Placing PMT R11410
	rmy180 = new G4RotationMatrix();
	rmy180->rotateY(180.*deg);
	PMT0PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(0.,0.,-(83.5*mm + 114.0*mm/2 -29.5*mm)), PMTR11410LogicalVolume,"PMT0_Body", LXe_Logical, false, 0); //ToDo important: understand and check properties

	// Placing all TPC components fully emerged in original GXe volume (neglecting extra filling)
	TPC_SS_TopRing_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 5.0*mm / 2 + TPC_offset_z), TPC_SS_TopRing_log, "TPC_SS_TopRing", GXe_Logical, false, 0);
	TPC_PTFE_spacer1_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 73.5*mm - 2.0*mm / 2 + TPC_offset_z), TPC_PTFE_spacer1_log, "TPC_PTFE_spacer1", GXe_Logical, false, 0);
	TPC_PTFE_spacer2_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 78.5*mm - 5.0*mm / 2 + TPC_offset_z), TPC_PTFE_spacer2_log, "TPC_PTFE_spacer2", GXe_Logical, false, 0);
	TPC_PTFE_reflector_GXe_phys = new G4PVPlacement(0,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + (70.-68.)*mm / 2), TPC_PTFE_reflector_GXe_log,"TPC_PTFE_reflector_GXe", GXe_Logical, 0, 0);
	TPC_SS_gate_ring_phys = new G4PVPlacement(0,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 3.*mm / 2), TPC_SS_gate_ring_log,"TPC_SS_gate_ring", GXe_Logical, 0, 0);
	TPC_PTFE_TopPMTHolder_phys = new G4PVPlacement(0,G4ThreeVector(0*cm, 0*cm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 62.5*mm - 8.0*mm / 2 + TPC_offset_z), TPC_PTFE_TopPMTHolder_log,"TPC_PTFE_TopPMTHolder", GXe_Logical, 0, 0);
	TPC_SS_anode_ring_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 75.5*mm - 3.0*mm / 2 + TPC_offset_z), TPC_SS_anode_ring_log,"TPC_SS_anode_ring", GXe_Logical, 0, 0);
	TPC_SS_TopMesh_ring_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 70.5*mm - 3.0*mm / 2 + TPC_offset_z), TPC_SS_TopMesh_ring_log,"TPC_SS_TopMesh_ring", GXe_Logical, 0, 0);
	TPC_PEEK_weir_LXe2_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -GXe_height / 2 + 5.5*mm / 2), TPC_PEEK_weir_LXe2_log,"TPC_PEEK_weir_LXe2", GXe_Logical, 0, 0);

		// Placing Teflon pillars fully emerged in GXe around active TPC
	for (int a=0; a < TPC_PTFE_pillar_number; ++a)
	{ 
		G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);
		G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
		pillarRotation->rotateZ(rotate_angle*deg);

		G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;
		G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;

		name.str("");
		name << "TPC_PTFE_pillar_GXe_" << a;
		TPC_PTFE_pillar_GXe_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
	}

		// Placing steel pillars fully emerged in GXe around active TPC
	for (int a=0; a < TPC_PTFE_pillar_number; ++a)
	{ 
		G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);

		G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;
		G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_h_position_r;

		name.str("");
		name << "TPC_SS_pillar_" << a;
		TPC_SS_pillar_phys = new G4PVPlacement(0, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm + 25.0*mm / 2 + TPC_offset_z), TPC_SS_pillar_log, name.str(), GXe_Logical, false, 0);
	}

	//Placing PMT R8520
	PMT1PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(-14.*mm,-28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT1_Body", GXe_Logical, false, 0);
	PMT2PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(-28.*mm,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT2_Body", GXe_Logical, false, 0);
	PMT3PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(-14.*mm,28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT3_Body", GXe_Logical, false, 0);
	PMT4PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(14.*mm,28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT4_Body", GXe_Logical, false, 0);
	PMT5PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(28.*mm,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT5_Body", GXe_Logical, false, 0);
	PMT6PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(14.*mm,-28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT6_Body", GXe_Logical, false, 0);
	PMT7PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(0.,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z)), PMTR8520LogicalVolume,"PMT7_Body", GXe_Logical, false, 0);


//**********************************************VISUALIZATION**********************************************
//ToDo: adjust visatts?

	// Visualization Settings : TeflonColor
	G4Colour TeflonColor(1.,1.,1.);
	TeflonVisAtt = new G4VisAttributes(TeflonColor);
	TeflonVisAtt->SetVisibility(true);
  
	// Visualization Settings : LXe
	G4Colour LXeColor(0.,1.,0.);
	LXeVisAtt = new G4VisAttributes(LXeColor);
	LXeVisAtt->SetVisibility(true);
	LXe_Logical->SetVisAttributes(LXeVisAtt); 

	// Visualization Settings : GXe
	G4Colour GXeColor(1.,0.,0.);
	GXeVisAtt = new G4VisAttributes(GXeColor);
	GXeVisAtt->SetVisibility(true);
	GXe_Logical->SetVisAttributes(GXeVisAtt); 

	// Visualization Settings : Electrodes_top_frame
	G4Colour ElectrodesColor(0.,1.,1.);
	ElectrodesVisAtt = new G4VisAttributes(ElectrodesColor);
	ElectrodesVisAtt->SetVisibility(true);

	// Visualization Settings: Cathode_frame
	G4Colour CathodeColor(1.,1.,0.);
	CathodeVisAtt = new G4VisAttributes(CathodeColor);
	CathodeVisAtt->SetVisibility(true);

	// Visualization Settings: Bottomscreen_frame
	G4Colour BottomscreenColor(1.,0.,1.);
	BottomscreenVisAtt = new G4VisAttributes(BottomscreenColor);
	BottomscreenVisAtt->SetVisibility(true);

	// Visualization Settings: Field_shaping_rings
	G4Colour RingsColor(0.,0.,1.);
	RingsVisAtt = new G4VisAttributes(RingsColor);
	RingsVisAtt->SetVisibility(true);

	//Visualization Settings: Sensor_array
	G4Colour SensorColor(0.5, 0.5,0.5);
	SensorVisAtt = new G4VisAttributes(SensorColor);
	SensorVisAtt->SetVisibility(true);

	//Sensitive Detector: Setting the LXe_Logical as a Sensitive Detector
	G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
	XebraLXeSensitiveDetector *pLXeSD = new XebraLXeSensitiveDetector("Xebra/LXeSD");
	pSDManager->AddNewDetector(pLXeSD);
	LXe_Logical->SetSensitiveDetector(pLXeSD);

	return TPC_Logical;
}

G4double XebraConstructTPC::GetInnerRadiusCryostat(){
	return this->cryostat_innerRadius;
}

G4double XebraConstructTPC::GetInnerHeightCryostat(){
	return this->cryostat_innerHeight;
}
 
void XebraConstructTPC:: PrintGeometryInformation()
{
	//================================== Xenon ===============================================================  
	const G4double LXeMass = LXe_Logical->GetMass(false, false)/kg + LXe_weir_1_log->GetMass(false, false)/kg + LXe_extra_filling_log->GetMass(false, false)/kg;
	const G4double LXeVolume = LXeMass/(LXe->GetDensity()*m3/kg);
	G4cout << "LXe:                               " << LXeMass << " kg " << "    =============    " << LXeVolume << " m3 " << G4endl;
	const G4double GXeMass = GXe_Logical->GetMass(false, false)/kg + GXe_weir_1_log->GetMass(false, false)/kg + GXe_weir_2_log->GetMass(false, false)/kg;
	const G4double GXeVolume = GXeMass/(GXe->GetDensity()*m3/kg);
	G4cout << "GXe:                              	" << GXeMass << " kg " << "     =============    " << GXeVolume << " m3 " << G4endl;
	const G4double TotalXenonMass = LXeMass + GXeMass;
	const G4double TotalXenonVolume = LXeVolume + GXeVolume;
	G4cout << "                                          =================================================== " << G4endl;
	G4cout << "Total Xenon in TPC envelope:       " << TotalXenonMass << " kg " << "    =============    " << TotalXenonVolume << " m3 " << G4endl;
	G4cout << "============================================================================================= " << G4endl;

}


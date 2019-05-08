#include "XebraConstructTPC.hh"

//Detector Components
#include "XebraConstructSensors.hh"
#include "XebraPMTsR11410.hh"
#include "XebraPMTsR8520.hh"

// Added by Alex
#include "XebraLXeSensitiveDetector.hh"
#include "XebraPmtSensitiveDetector.hh"
#include "XebraDetectorMessenger.hh"

//Optical surface properties
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>

XebraConstructTPC::XebraConstructTPC(XebraDetectorConstruction *){

	//these values will be used for the cryostat (given by Julia)
	cryostat_innerRadius = 0.15*m / 2;
	cryostat_innerHeight = 0.4*m; //roughly 0.4*m, according to thesis Basho: 37.*cm

}

XebraConstructTPC::~XebraConstructTPC() {;}


//////////////////////////////////////////////////////////////////////////////////////////////////

G4LogicalVolume* XebraConstructTPC::Construct(){

using std::stringstream;
	stringstream name;
	stringstream namesurface;

	// Materials
	LXe = G4Material::GetMaterial("LXe");
	GXe = G4Material::GetMaterial("GXe");
	Teflon = G4Material::GetMaterial("Teflon");
	SS304LSteel = G4Material::GetMaterial("SS304LSteel");
	Copper = G4Material::GetMaterial("Copper");
	Aluminium  = G4Material::GetMaterial("Aluminium");
	PEEK  = G4Material::GetMaterial("PEEK");
	Torlon  = G4Material::GetMaterial("Torlon");
	GridMeshSS316LSteelLXe  = G4Material::GetMaterial("GridMeshSS316LSteelLXe");
	GridMeshSS316LSteelGXe  = G4Material::GetMaterial("GridMeshSS316LSteelGXe");
	WireMeshGoldLXe  = G4Material::GetMaterial("WireMeshGoldLXe");
  G4Material *GXeTeflon = G4Material::GetMaterial("GXeTeflon");
  
  // Optical Surfaces
  // see https://indico.cern.ch/event/679723/contributions/2792554/attachments/1559217/2453758/BookForApplicationDevelopers.pdf, p. 219
  
  G4double dSigmaAlpha = 0.1; // defines roughness of the surface (microfacets)
  
	//G4OpticalSurface *pTeflonOpticalSurface = new G4OpticalSurface("TeflonOpticalSurface", unified, ground, dielectric_metal, dSigmaAlpha); //old/wrong
	G4OpticalSurface *pTeflonOpticalSurface = new G4OpticalSurface("TeflonOpticalSurface", unified, groundbackpainted, dielectric_dielectric, dSigmaAlpha);
	G4OpticalSurface *pGXeTeflonOpticalSurface = new G4OpticalSurface("GXeTeflonOpticalSurface", unified, groundbackpainted, dielectric_dielectric, dSigmaAlpha);
		
	pTeflonOpticalSurface->SetMaterialPropertiesTable(Teflon->GetMaterialPropertiesTable());
	pGXeTeflonOpticalSurface->SetMaterialPropertiesTable(GXeTeflon->GetMaterialPropertiesTable());

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

	// Parameters LXe and GXe + meshes
		// height GXe without LXe extra filling, currently at lower edge of gate ring
		// default: 86.5*mm + (cryostat_innerHeight - TPC_dimension_z) / 2 - TPC_offset_z
	GXe_height = 86.5*mm + (cryostat_innerHeight - TPC_dimension_z) / 2 - TPC_offset_z;
		// LXe extra filling
			// dual phase mode -> up to upper edge weir
			// default: 5.5 * mm
	LXe_extra_filling_height = 5.5 * mm;
	useThinWireMesh = false;
			// single phase mode -> at least photocathode top PMTs submerged in LXe 
			// default: 5 mm above lower edge quartz window = 18. * mm + 5. * mm
	//LXe_extra_filling_height = 18. * mm + 5. * mm;
	//useThinWireMesh = true;
	
	AnodeThicknessGridMesh = 0.15 * mm; // also implement changes in XebraDetectorConstruction::DefineGeometryParameters
	AnodeThicknessThinWire = 10 * um;
	
	// extra gap to PMTs for position reconstruction improvement
		// PTFE spacer 3 thickness
		TPC_PTFE_spacer3_height        = 4.5 * mm; // <= 5.*mm, otherwise collision with pillar, if on top of top mesh; default 0.*mm
		TPC_PTFE_spacer3_radius_inner  = 35.* mm; // 35.* mm
		TPC_PTFE_spacer3_radius_outer  = 60.* mm; // 60.* mm
		TPC_PTFE_spacer3_extragap      = 0. * mm; // 0. *mm if on top of top mesh
		
		// size extra gap
		TPC_TopPMTs_extragap           = 4.5 * mm; // >= TPC_PTFE_spacer3_height
		
		G4cout << "---> Heigth spacer 3:          " << TPC_PTFE_spacer3_height << " mm" << G4endl;
		G4cout << "---> Heigth extra gap to PMTs: " << TPC_TopPMTs_extragap << " mm" << G4endl;


//**************************************************CONSTRUCT*******************************************

	// Construct objects
	// Abbreviations (p...) according to https://wiki.uni-freiburg.de/app/lib/exe/fetch.php?media=start:ultimate:xebra:tpc:labtpc_assembly.pdf

	//**************************************************
	// Xenon volumes
	//**************************************************
		// LXe extra filling see bottom of CONSTRUCT section

	TPC_cylinder = new G4Tubs("TPC_cylinder", 0.*cm, cryostat_innerRadius, cryostat_innerHeight/2, 0.*deg, 360.*deg);  
	GXe_cylinder_orig = new G4Tubs("GXe_cylinder_orig", 0.*cm, cryostat_innerRadius, GXe_height/2, 0.*deg, 360.*deg);
	
	LXe_ActiveVolume_solid = new G4Tubs("LXe_ActiveVolume_solid", 0.*mm, 35.*mm, (68.5*mm - AnodeThicknessGridMesh)/2 + (3.*mm - AnodeThicknessGridMesh)/2, 0.*deg, 360.*deg);
	LXe_ActiveVolume_extra_filling_solid = new G4Tubs("LXe_ActiveVolume_extra_filling_solid", 0.*mm, 35.*mm, (3.*mm - AnodeThicknessGridMesh)/2, 0.*deg, 360.*deg);
	
	GXe_cylinder = new G4SubtractionSolid("GXe_cylinder", GXe_cylinder_orig, LXe_ActiveVolume_extra_filling_solid, 0, G4ThreeVector(0., 0., -GXe_height/2 + (3.*mm - AnodeThicknessGridMesh)/2));
		
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

	//**************************************************

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
	
	// PTFE spacer 3 - added for improved position reconstruction, might deteriorate due to refelctions, but needed to shild external interactions and better than unknown material
	if (TPC_PTFE_spacer3_height > 0)
	{
		TPC_PTFE_spacer3_solid = new G4Tubs("TPC_PTFE_spacer3_solid", TPC_PTFE_spacer3_radius_inner, TPC_PTFE_spacer3_radius_outer, TPC_PTFE_spacer3_height / 2, 0.*deg, 360.*deg);
	}

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

	// Electrode Meshes
	TPC_SS_electrode_mesh_small_solid = new G4Tubs("TPC_SS_electrode_mesh_small_solid", 0.*mm, 50.*mm, AnodeThicknessGridMesh / 2, 0.*deg, 360.*deg);
	TPC_SS_electrode_mesh_large_solid = new G4Tubs("TPC_SS_electrode_mesh_large_solid", 0.*mm, (118./2)*mm, AnodeThicknessGridMesh / 2, 0.*deg, 360.*deg);
	
	TPC_Au_electrode_mesh_small_solid = new G4Tubs("TPC_Au_electrode_mesh_small_solid", 0.*mm, 50.*mm, AnodeThicknessThinWire / 2, 0.*deg, 360.*deg);

	// Rod (p7)
	TPC_Torlon_rod_solid_orig = new G4Orb("TPC_Torlon_rod_solid_orig", 1.1*mm);
	TPC_Torlon_rod_solid_1 = new G4Tubs("TPC_Torlon_rod_solid_1", 0.*mm, 1.1*mm, (50.-40.)*mm / 2, 0.*deg, 360.*deg);
	TPC_Torlon_rod_solid = new G4UnionSolid("TPC_Torlon_rod_solid", TPC_Torlon_rod_solid_orig, TPC_Torlon_rod_solid_1, rmy90, G4ThreeVector(0., 0., 0.));

	// Weir for leveling (p13)
		// LXe original filling part
	TPC_PEEK_weir_LXe_solid_orig = new G4Tubs("TPC_PEEK_weir_LXe_solid_orig", 60.*mm, 73.*mm, 83.5*mm / 2, 130.*deg, (170.-130.)*deg);
	TPC_PEEK_weir_LXe_solid_sub1 = new G4Tubs("TPC_PEEK_weir_LXe_solid_sub1", 0.*mm, 5.*mm, 70.5*mm / 2, 0.*deg, 360.*deg);
	TPC_PEEK_weir_LXe_solid_sub2 = new G4Tubs("TPC_PEEK_weir_LXe_solid_sub2", 61.5*mm, 71.5*mm, 70.5*mm / 2, 136.*deg, (164.-136.)*deg);
	TPC_PEEK_weir_LXe_solid_1 = new G4SubtractionSolid("TPC_PEEK_weir_LXe_solid_1", TPC_PEEK_weir_LXe_solid_orig, TPC_PEEK_weir_LXe_solid_sub2, 0, G4ThreeVector(0.*mm, 0.*mm, (83.5-70.5)*mm / 2));
	TPC_PEEK_weir_LXe_solid_2 = new G4SubtractionSolid("TPC_PEEK_weir_LXe_solid_2", TPC_PEEK_weir_LXe_solid_1, TPC_PEEK_weir_LXe_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), (83.5-70.5)*mm / 2));
	TPC_PEEK_weir_LXe_solid = new G4SubtractionSolid("TPC_PEEK_weir_LXe_solid", TPC_PEEK_weir_LXe_solid_2, TPC_PEEK_weir_LXe_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), (83.5-70.5)*mm / 2));

		// LXe extra filling part
	TPC_PEEK_weir_LXe2_solid_orig = new G4Tubs("TPC_PEEK_weir_LXe2_solid_orig", 60.*mm, 73.*mm, 5.5*mm / 2, 130.*deg, (170.-130.)*deg);
	TPC_PEEK_weir_LXe2_solid_sub1 = new G4Tubs("TPC_PEEK_weir_LXe2_solid_sub1", 0.*mm, 5.*mm, 5.5*mm / 2, 0.*deg, 360.*deg);
	TPC_PEEK_weir_LXe2_solid_sub2 = new G4Tubs("TPC_PEEK_weir_LXe_solid_sub2", 61.5*mm, 71.5*mm, 5.5*mm / 2, 136.*deg, (164.-136.)*deg);
	TPC_PEEK_weir_LXe2_solid_1 = new G4SubtractionSolid("TPC_PEEK_weir_LXe2_solid_1", TPC_PEEK_weir_LXe2_solid_orig, TPC_PEEK_weir_LXe2_solid_sub2, 0, G4ThreeVector(0.*mm, 0.*mm, 0*mm));
	TPC_PEEK_weir_LXe2_solid_2 = new G4SubtractionSolid("TPC_PEEK_weir_LXe2_solid_2", TPC_PEEK_weir_LXe2_solid_1, TPC_PEEK_weir_LXe2_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(136.*deg), 66.5*mm * sin(136.*deg), 0*mm));
	TPC_PEEK_weir_LXe2_solid = new G4SubtractionSolid("TPC_PEEK_weir_LXe2_solid", TPC_PEEK_weir_LXe2_solid_2, TPC_PEEK_weir_LXe2_solid_sub1, 0, G4ThreeVector(66.5*mm * cos(164.*deg), 66.5*mm * sin(164.*deg), 0*mm));
	
	
	//------------------------- PMT R8520 body ---------------------
	// only used for cuts in LXe extra filling, otherwise implemented in XebraPMTsR8520 class
	
	const G4double R8520_body_width = 25.7 * mm;
  const G4double R8520_body_cornerradius = 2. * mm;
  const G4double R8520_height = 28.25 * mm;
  const G4double R8520_window_height = 1.2 * mm;
  const G4double R8520_window_width = 24. * mm;
  const G4double R8520_body_height = R8520_height; // without subtracted Al ring and window
	
		// general outer dimensions PMT
	R8520_body_solid_orig_1 = new G4Box("R8520_body_solid_orig_1", R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_width / 2, R8520_body_height / 2);
	R8520_body_solid_orig_2 = new G4Box("R8520_body_solid_orig_2", R8520_body_width / 2, R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_height / 2);
	R8520_body_solid_orig_3 = new G4Tubs("R8520_body_solid_orig_3", 0.*mm, R8520_body_cornerradius, R8520_body_height / 2, 0.*deg, 360.*deg);
	R8520_body_solid_orig_a = new G4UnionSolid("R8520_body_solid_orig_a", R8520_body_solid_orig_1, R8520_body_solid_orig_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_body_solid_orig_b = new G4UnionSolid("R8520_body_solid_orig_b", R8520_body_solid_orig_a, R8520_body_solid_orig_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig_c = new G4UnionSolid("R8520_body_solid_orig_c", R8520_body_solid_orig_b, R8520_body_solid_orig_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig_d = new G4UnionSolid("R8520_body_solid_orig_d", R8520_body_solid_orig_c, R8520_body_solid_orig_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig = new G4UnionSolid("R8520_body_solid_orig", R8520_body_solid_orig_d, R8520_body_solid_orig_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));

		// subtract edge outside of window
	R8520_body_solid_cut1 = new G4Box("R8520_body_solid_cut1", R8520_body_width / 2, R8520_body_width / 2, R8520_window_height / 2);
	R8520_body_solid_sub1 = new G4SubtractionSolid("R8520_body_solid_sub1", R8520_body_solid_orig, R8520_body_solid_cut1, 0, G4ThreeVector(0.,0.,(R8520_body_height - R8520_window_height)/2));

	R8520_body_solid_cut2_1 = new G4Box("R8520_body_solid_cut2_1", R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_width / 2, R8520_window_height / 2);
	R8520_body_solid_cut2_2 = new G4Box("R8520_body_solid_cut2_2", R8520_window_width / 2, R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_height / 2);
	R8520_body_solid_cut2_3 = new G4Tubs("R8520_body_solid_cut2_3", 0.*mm, R8520_body_cornerradius, R8520_window_height / 2, 0.*deg, 360.*deg);
	R8520_body_solid_cut2_a = new G4UnionSolid("R8520_body_solid_cut2_a", R8520_body_solid_cut2_1, R8520_body_solid_cut2_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_body_solid_cut2_b = new G4UnionSolid("R8520_body_solid_cut2_b", R8520_body_solid_cut2_a, R8520_body_solid_cut2_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut2_c = new G4UnionSolid("R8520_body_solid_cut2_c", R8520_body_solid_cut2_b, R8520_body_solid_cut2_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut2_d = new G4UnionSolid("R8520_body_solid_cut2_d", R8520_body_solid_cut2_c, R8520_body_solid_cut2_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut2 = new G4UnionSolid("R8520_body_solid_cut2", R8520_body_solid_cut2_d, R8520_body_solid_cut2_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));

	R8520_body_solid = new G4UnionSolid("R8520_body_solid", R8520_body_solid_sub1, R8520_body_solid_cut2, 0, G4ThreeVector(0., 0., (R8520_body_height - R8520_window_height)/2));
	
	// ----------------------------------



	// LXe extra filling (increase LXe filling level to weir)
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
	LXe_extra_filling_solid_7 =  new G4SubtractionSolid("LXe_extra_filling_solid_7", LXe_extra_filling_solid_6, TPC_PTFE_TopPMTHolder_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 62.5*mm - 8.0*mm / 2  + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z + TPC_TopPMTs_extragap));
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
	LXe_extra_filling_solid_13 = new G4SubtractionSolid("LXe_extra_filling_solid_13", LXe_extra_filling_solid_12, TPC_SS_electrode_mesh_small_solid, 0, G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 3.*mm - AnodeThicknessGridMesh / 2 + (GXe_height - LXe_extra_filling_height)/2));	
	if (useThinWireMesh == true)	
	{
		LXe_extra_filling_solid_14 = new G4SubtractionSolid("LXe_extra_filling_solid_14", LXe_extra_filling_solid_13, TPC_Au_electrode_mesh_small_solid, 0, G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 8.*mm + AnodeThicknessThinWire / 2 + (GXe_height - LXe_extra_filling_height)/2));
	}
	else
	{
		LXe_extra_filling_solid_14 = new G4SubtractionSolid("LXe_extra_filling_solid_14", LXe_extra_filling_solid_13, TPC_SS_electrode_mesh_small_solid, 0, G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 8.*mm + AnodeThicknessGridMesh / 2 + (GXe_height - LXe_extra_filling_height)/2));
	}
	LXe_extra_filling_solid_15 = new G4SubtractionSolid("LXe_extra_filling_solid_15", LXe_extra_filling_solid_14, TPC_SS_electrode_mesh_small_solid, 0, G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 13.*mm + AnodeThicknessGridMesh / 2 + (GXe_height - LXe_extra_filling_height)/2));
	LXe_extra_filling_solid_16 = new G4SubtractionSolid("LXe_extra_filling_solid_16", LXe_extra_filling_solid_15, LXe_ActiveVolume_extra_filling_solid, 0, G4ThreeVector(0., 0., -LXe_extra_filling_height/2 + (3.*mm - AnodeThicknessGridMesh)/2));	
	LXe_extra_filling_solid_17 = new G4SubtractionSolid("LXe_extra_filling_solid_17", LXe_extra_filling_solid_16, R8520_body_solid, 0, G4ThreeVector(-14.*mm,-28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));	
	LXe_extra_filling_solid_18 = new G4SubtractionSolid("LXe_extra_filling_solid_18", LXe_extra_filling_solid_17, R8520_body_solid, 0, G4ThreeVector(-28.*mm,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));
	LXe_extra_filling_solid_19 = new G4SubtractionSolid("LXe_extra_filling_solid_19", LXe_extra_filling_solid_18, R8520_body_solid, 0, G4ThreeVector(-14.*mm,28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));
	LXe_extra_filling_solid_20 = new G4SubtractionSolid("LXe_extra_filling_solid_20", LXe_extra_filling_solid_19, R8520_body_solid, 0, G4ThreeVector(14.*mm,28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));	
	LXe_extra_filling_solid_21 = new G4SubtractionSolid("LXe_extra_filling_solid_21", LXe_extra_filling_solid_20, R8520_body_solid, 0, G4ThreeVector(28.*mm,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));
	LXe_extra_filling_solid_22 = new G4SubtractionSolid("LXe_extra_filling_solid_22", LXe_extra_filling_solid_21, R8520_body_solid, 0, G4ThreeVector(14.*mm,-28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));
	LXe_extra_filling_solid_23 = new G4SubtractionSolid("LXe_extra_filling_solid_23", LXe_extra_filling_solid_22, R8520_body_solid, 0, G4ThreeVector(0.,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z) + (GXe_height - LXe_extra_filling_height)/2 + TPC_TopPMTs_extragap));
	if (TPC_PTFE_spacer3_height > 0)
	{
		LXe_extra_filling_solid_24 = new G4SubtractionSolid("LXe_extra_filling_solid_24", LXe_extra_filling_solid_23, TPC_PTFE_spacer3_solid, 0, G4ThreeVector(0.*mm, 0.*mm,  GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 70.5*mm + TPC_PTFE_spacer3_height / 2 + TPC_PTFE_spacer3_extragap + (GXe_height - LXe_extra_filling_height)/2 + TPC_offset_z));
	}
	else
	{
		LXe_extra_filling_solid_24 = LXe_extra_filling_solid_23;
	}
	LXe_extra_filling_solid = LXe_extra_filling_solid_24;

// ToDo: Add missing TPC components (LLM and SLMs).

//**************************************************LOGICALVOLUMES***************************************

	TPC_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "TPC_Logical", 0, 0, 0);
	LXe_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "LXe_Logical", 0, 0, 0);
	LXe_ActiveVolume_Logical = new G4LogicalVolume(LXe_ActiveVolume_solid, LXe, "LXe_ActiveVolume_Logical", 0, 0, 0);
	//LXe_ActiveVolume_extra_filling_Logical = new G4LogicalVolume(LXe_ActiveVolume_extra_filling_solid, LXe, "LXe_ActiveVolume_extra_filling_Logical", 0, 0, 0);
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
	TPC_PTFE_pillar_GXe_log = new G4LogicalVolume(TPC_PTFE_pillar_GXe_solid, GXeTeflon, "TPC_PTFE_pillar_GXe_log");
	TPC_SS_BottomRing_log = new G4LogicalVolume(TPC_SS_BottomRing_solid, SS304LSteel, "TPC_SS_BottomRing_log");
	TPC_SS_pillar_log = new G4LogicalVolume(TPC_SS_pillar_solid, SS304LSteel, "TPC_SS_pillar_log");
	TPC_SS_TopRing_log = new G4LogicalVolume(TPC_SS_TopRing_solid, SS304LSteel, "TPC_SS_TopRing_log");
	TPC_PTFE_filler_log = new G4LogicalVolume(TPC_PTFE_filler_solid, Teflon, "TPC_PTFE_filler_log");
	TPC_PTFE_BottomPMTHolder_log = new G4LogicalVolume(TPC_PTFE_BottomPMTHolder_solid, Teflon, "TPC_PTFE_BottomPMTHolder_log");
	TPC_PTFE_spacer1_log = new G4LogicalVolume(TPC_PTFE_spacer1_solid, GXeTeflon, "TPC_PTFE_spacer1_log");
	TPC_PTFE_spacer2_log = new G4LogicalVolume(TPC_PTFE_spacer2_solid, GXeTeflon, "TPC_PTFE_spacer2_log");
	if (TPC_PTFE_spacer3_height > 0)
	{
		TPC_PTFE_spacer3_log = new G4LogicalVolume(TPC_PTFE_spacer3_solid, GXeTeflon, "TPC_PTFE_spacer3_log");
	}
	TPC_PTFE_reflector_LXe_log = new G4LogicalVolume(TPC_PTFE_reflector_LXe_solid, Teflon, "TPC_PTFE_reflector_LXe_log");
	TPC_PTFE_reflector_GXe_log = new G4LogicalVolume(TPC_PTFE_reflector_GXe_solid, Teflon, "TPC_PTFE_reflector_GXe_log");
	TPC_SS_gate_ring_log = new G4LogicalVolume(TPC_SS_gate_ring_solid, SS304LSteel, "TPC_SS_gate_ring_log");
	TPC_PTFE_TopPMTHolder_log = new G4LogicalVolume(TPC_PTFE_TopPMTHolder_solid, GXeTeflon, "TPC_PTFE_TopPMTHolder_log");
	TPC_SS_cathode_ring_log =  new G4LogicalVolume(TPC_SS_cathode_ring_solid, SS304LSteel, "TPC_SS_cathode_ring_log");
	TPC_SS_anode_ring_log =  new G4LogicalVolume(TPC_SS_anode_ring_solid, SS304LSteel, "TPC_SS_anode_ring_log");
	TPC_SS_TopMesh_ring_log =  new G4LogicalVolume(TPC_SS_TopMesh_ring_solid, SS304LSteel, "TPC_SS_TopMesh_ring_log");
	TPC_Torlon_rod_log = new G4LogicalVolume(TPC_Torlon_rod_solid, Torlon, "TPC_Torlon_rod_log");
	TPC_PEEK_weir_LXe_log = new G4LogicalVolume(TPC_PEEK_weir_LXe_solid, PEEK, "TPC_PEEK_weir_LXe_log");
	TPC_PEEK_weir_LXe2_log = new G4LogicalVolume(TPC_PEEK_weir_LXe2_solid, PEEK, "TPC_PEEK_weir_LXe2_log");

	TPC_SS_electrode_mesh_LXe_small_log = new G4LogicalVolume(TPC_SS_electrode_mesh_small_solid, GridMeshSS316LSteelLXe, "TPC_SS_electrode_mesh_LXe_small_log");
	TPC_SS_electrode_mesh_LXe_large_log = new G4LogicalVolume(TPC_SS_electrode_mesh_large_solid, GridMeshSS316LSteelLXe, "TPC_SS_electrode_mesh_LXe_large_log");
	TPC_SS_electrode_mesh_GXe_small_log = new G4LogicalVolume(TPC_SS_electrode_mesh_small_solid, GridMeshSS316LSteelGXe, "TPC_SS_electrode_mesh_GXe_small_log");
	TPC_SS_electrode_mesh_GXe_large_log = new G4LogicalVolume(TPC_SS_electrode_mesh_large_solid, GridMeshSS316LSteelGXe, "TPC_SS_electrode_mesh_GXe_large_log");
	
	TPC_Au_electrode_mesh_LXe_small_log = new G4LogicalVolume(TPC_Au_electrode_mesh_small_solid, WireMeshGoldLXe, "TPC_Au_electrode_mesh_LXe_small_log");

  // Create Logical XebraPMTsR11410 Volume from corresponding class
	XebraPMTsR11410 *r11410 = new XebraPMTsR11410(this);
	PMTR11410LogicalVolume = r11410->Construct();

  // Create Logical XebraPMTsR8520 Volume from corresponding class
	XebraPMTsR8520 *r8520 = new XebraPMTsR8520(this);
	PMTR8520LogicalVolume = r8520->Construct();

  
//***********************************************PHYSICALVOLUME********************************************

	// Filling TPC Volume with LXe
	LXe_Physical = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), LXe_Logical,"LXe_TPC", TPC_Logical, false, 0);
  
	// Replacing LXe with GXe
	GXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height/2), GXe_Logical,"GXe_TPC", LXe_Logical, false, 0);
	
	// Placing LXe Active Volume
	LXe_ActiveVolume_Physical = new G4PVPlacement(0, G4ThreeVector(0., 0., (-TPC_dimension_z / 2 + 152.0*mm + 3.*mm + AnodeThicknessGridMesh + TPC_offset_z) + (68.5*mm - AnodeThicknessGridMesh)/2 + (3.*mm - AnodeThicknessGridMesh)/2), LXe_ActiveVolume_Logical,"LXe_ActiveVolume", LXe_Logical, false, 0);
	//LXe_ActiveVolume_extra_filling_Physical = new G4PVPlacement(0, G4ThreeVector(0., 0., -LXe_extra_filling_height/2 + (3.*mm - AnodeThicknessGridMesh)/2), LXe_ActiveVolume_extra_filling_Logical,"LXe_ActiveVolume_extra_filling", LXe_extra_filling_log, false, 0);

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

	//**************************************************
	// Placing all TPC components fully emerged in LXe
	//**************************************************

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
	TPC_SS_cathode_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 152.0*mm + 3.*mm + AnodeThicknessGridMesh / 2 + TPC_offset_z), TPC_SS_electrode_mesh_LXe_large_log,"TPC_SS_cathode_mesh", LXe_Logical, 0, 0);
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
		namesurface.str("");
		namesurface << "LXe_PTFEpillarLXe_LogicalBorderSurface_" << a;
		
		if (a==0)
		{
			TPC_PTFE_pillar_LXe_0_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
			new G4LogicalBorderSurface(namesurface.str(), LXe_Physical, TPC_PTFE_pillar_LXe_0_phys, pTeflonOpticalSurface);
		}
		
		if (a==1)
		{
			TPC_PTFE_pillar_LXe_1_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
			new G4LogicalBorderSurface(namesurface.str(), LXe_Physical, TPC_PTFE_pillar_LXe_1_phys, pTeflonOpticalSurface);
		}
		
		if (a==2)
		{
			TPC_PTFE_pillar_LXe_2_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
			new G4LogicalBorderSurface(namesurface.str(), LXe_Physical, TPC_PTFE_pillar_LXe_2_phys, pTeflonOpticalSurface);
		}
		
		if (a==3)
		{
			TPC_PTFE_pillar_LXe_3_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
			new G4LogicalBorderSurface(namesurface.str(), LXe_Physical, TPC_PTFE_pillar_LXe_3_phys, pTeflonOpticalSurface);
		}
		
		if (a==4)
		{
			TPC_PTFE_pillar_LXe_4_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
			new G4LogicalBorderSurface(namesurface.str(), LXe_Physical, TPC_PTFE_pillar_LXe_4_phys, pTeflonOpticalSurface);
		}
		
		if (a==5)
		{
			TPC_PTFE_pillar_LXe_5_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_LXe_log, name.str(), LXe_Logical, false, 0);
			new G4LogicalBorderSurface(namesurface.str(), LXe_Physical, TPC_PTFE_pillar_LXe_5_phys, pTeflonOpticalSurface);
		}
		
	}

	//Placing PMT R11410
	rmy180 = new G4RotationMatrix();
	rmy180->rotateY(180.*deg);
	G4int iPmtNb=0;
	PMT0PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(0.,0.,-(83.5*mm + 114.0*mm/2 -29.5*mm)), PMTR11410LogicalVolume,"PMT0_Body", LXe_Logical, false, iPmtNb);

	//**************************************************
	// Placing all TPC components fully emerged in original GXe volume (neglecting extra filling)
	//**************************************************

	TPC_SS_TopRing_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 5.0*mm / 2 + TPC_offset_z), TPC_SS_TopRing_log, "TPC_SS_TopRing", GXe_Logical, false, 0);
	TPC_PTFE_spacer1_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 73.5*mm - 2.0*mm / 2 + TPC_offset_z), TPC_PTFE_spacer1_log, "TPC_PTFE_spacer1", GXe_Logical, false, 0);
	TPC_PTFE_spacer2_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 78.5*mm - 5.0*mm / 2 + TPC_offset_z), TPC_PTFE_spacer2_log, "TPC_PTFE_spacer2", GXe_Logical, false, 0);
	if (TPC_PTFE_spacer3_height > 0)
	{	
		TPC_PTFE_spacer3_phys = new G4PVPlacement(0, G4ThreeVector(0., 0. , (GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 70.5*mm + TPC_offset_z) + TPC_PTFE_spacer3_height / 2 + TPC_PTFE_spacer3_extragap), TPC_PTFE_spacer3_log, "TPC_PTFE_spacer3", GXe_Logical, false, 0);
	}
	TPC_PTFE_reflector_GXe_phys = new G4PVPlacement(0,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + (70.-68.)*mm / 2), TPC_PTFE_reflector_GXe_log,"TPC_PTFE_reflector_GXe", GXe_Logical, 0, 0);
	TPC_SS_gate_ring_phys = new G4PVPlacement(0,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 3.*mm / 2), TPC_SS_gate_ring_log,"TPC_SS_gate_ring", GXe_Logical, 0, 0);
	if (LXe_extra_filling_height > 3.*mm - AnodeThicknessGridMesh)	
	{
	TPC_SS_gate_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 3.*mm - AnodeThicknessGridMesh / 2), TPC_SS_electrode_mesh_LXe_small_log,"TPC_SS_gate_mesh", GXe_Logical, 0, 0);
	}
	else
	{
	TPC_SS_gate_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 3.*mm - AnodeThicknessGridMesh / 2), TPC_SS_electrode_mesh_GXe_small_log,"TPC_SS_gate_mesh", GXe_Logical, 0, 0);	
	}
	TPC_PTFE_TopPMTHolder_phys = new G4PVPlacement(0,G4ThreeVector(0*cm, 0*cm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 62.5*mm - 8.0*mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap), TPC_PTFE_TopPMTHolder_log,"TPC_PTFE_TopPMTHolder", GXe_Logical, 0, 0);
	TPC_SS_anode_ring_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 75.5*mm - 3.0*mm / 2 + TPC_offset_z), TPC_SS_anode_ring_log,"TPC_SS_anode_ring", GXe_Logical, 0, 0);
	
	if (LXe_extra_filling_height > 8.*mm)	
	{
		if (useThinWireMesh == true)	
		{
		TPC_Au_anode_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 8.*mm + AnodeThicknessThinWire / 2), TPC_Au_electrode_mesh_LXe_small_log,"TPC_Au_anode_mesh", GXe_Logical, 0, 0);
		}
		else
		{
		TPC_SS_anode_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 8.*mm + AnodeThicknessGridMesh / 2), TPC_SS_electrode_mesh_LXe_small_log,"TPC_SS_anode_mesh", GXe_Logical, 0, 0);
		}
	}
	else
	{
	TPC_SS_anode_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 8.*mm + AnodeThicknessGridMesh / 2), TPC_SS_electrode_mesh_GXe_small_log,"TPC_SS_anode_mesh", GXe_Logical, 0, 0);	
	}
	
	TPC_SS_TopMesh_ring_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 70.5*mm - 3.0*mm / 2 + TPC_offset_z), TPC_SS_TopMesh_ring_log,"TPC_SS_TopMesh_ring", GXe_Logical, 0, 0);
	if (LXe_extra_filling_height > 13.*mm)	
	{
	TPC_SS_TopMesh_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 13.*mm + AnodeThicknessGridMesh / 2), TPC_SS_electrode_mesh_LXe_small_log,"TPC_SS_TopMesh_mesh", GXe_Logical, 0, 0);
	}
	else
	{
	TPC_SS_TopMesh_mesh_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, - GXe_height / 2 + 13.*mm + AnodeThicknessGridMesh / 2), TPC_SS_electrode_mesh_GXe_small_log,"TPC_SS_TopMesh_mesh", GXe_Logical, 0, 0);	
	}
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
		
		if (a==0)
		{
			TPC_PTFE_pillar_GXe_0_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
			
			// optical surfaces
			namesurface.str("");
			namesurface << "GXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), GXe_Physical, TPC_PTFE_pillar_GXe_0_phys, pGXeTeflonOpticalSurface);
			
			namesurface.str("");
			namesurface << "LXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_0_phys, pTeflonOpticalSurface);
		}
		
		if (a==1)
		{
			TPC_PTFE_pillar_GXe_1_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
			
			// optical surfaces
			namesurface.str("");
			namesurface << "GXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), GXe_Physical, TPC_PTFE_pillar_GXe_1_phys, pGXeTeflonOpticalSurface);
			
			namesurface.str("");
			namesurface << "LXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_1_phys, pTeflonOpticalSurface);
		}
		
		if (a==2)
		{
			TPC_PTFE_pillar_GXe_2_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
			
			// optical surfaces
			namesurface.str("");
			namesurface << "GXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), GXe_Physical, TPC_PTFE_pillar_GXe_2_phys, pGXeTeflonOpticalSurface);
			
			namesurface.str("");
			namesurface << "LXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_2_phys, pTeflonOpticalSurface);
		}
		
		if (a==3)
		{
			TPC_PTFE_pillar_GXe_3_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
			
			// optical surfaces
			namesurface.str("");
			namesurface << "GXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), GXe_Physical, TPC_PTFE_pillar_GXe_3_phys, pGXeTeflonOpticalSurface);
			
			namesurface.str("");
			namesurface << "LXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_3_phys, pTeflonOpticalSurface);
		}
		
		if (a==4)
		{
			TPC_PTFE_pillar_GXe_4_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
			
			// optical surfaces
			namesurface.str("");
			namesurface << "GXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), GXe_Physical, TPC_PTFE_pillar_GXe_4_phys, pGXeTeflonOpticalSurface);
			
			namesurface.str("");
			namesurface << "LXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_4_phys, pTeflonOpticalSurface);
		}
		
		if (a==5)
		{
			TPC_PTFE_pillar_GXe_5_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 30.0 * mm - TPC_PTFE_pillar_h_dimension_z / 2 + TPC_offset_z), TPC_PTFE_pillar_GXe_log, name.str(), GXe_Logical, false, 0);
			
			// optical surfaces
			namesurface.str("");
			namesurface << "GXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), GXe_Physical, TPC_PTFE_pillar_GXe_5_phys, pGXeTeflonOpticalSurface);
			
			namesurface.str("");
			namesurface << "LXe_PTFEpillarGXe_LogicalBorderSurface_" << a;
			new G4LogicalBorderSurface(namesurface.str(), LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_5_phys, pTeflonOpticalSurface);
		}
		
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
	iPmtNb=1;
	PMT1PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(-14.*mm,-28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT1_Body", GXe_Logical, false, iPmtNb);
	iPmtNb=2;
	PMT2PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(-28.*mm,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT2_Body", GXe_Logical, false, iPmtNb);
	iPmtNb=3;
	PMT3PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(-14.*mm,28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT3_Body", GXe_Logical, false, iPmtNb);
	iPmtNb=4;
	PMT4PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(14.*mm,28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT4_Body", GXe_Logical, false, iPmtNb);
	iPmtNb=5;
	PMT5PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(28.*mm,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT5_Body", GXe_Logical, false, iPmtNb);
	iPmtNb=6;
	PMT6PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(14.*mm,-28.*mm,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT6_Body", GXe_Logical, false, iPmtNb);
	iPmtNb=7;
	PMT7PhysicalVolume = new G4PVPlacement(rmy180, G4ThreeVector(0.,0.,(GXe_height / 2 - (cryostat_innerHeight - TPC_dimension_z) / 2 - 68.5*mm + 28.25 * mm / 2 + TPC_offset_z + TPC_TopPMTs_extragap)), PMTR8520LogicalVolume,"PMT7_Body", GXe_Logical, false, iPmtNb);

//**********************************************OPTICAL SURFACES**********************************************

// G4OpticalSurfaces defined above together with materials
// Teflon surfaces in LXe / GXe

	// PTFE Filler
	new G4LogicalBorderSurface("LXe_PTFEFiller_LogicalBorderSurface",
		LXe_Physical, TPC_PTFE_filler_phys, pTeflonOpticalSurface);

	// PTFE Bottom PMT Holder
	new G4LogicalBorderSurface("LXe_BottomPMTHolder_LogicalBorderSurface",
		LXe_Physical, TPC_PTFE_BottomPMTHolder_phys, pTeflonOpticalSurface);

	// PTFE Reflector
	new G4LogicalBorderSurface("LXe_PTFEReflectorLXe_LogicalBorderSurface",
		LXe_Physical, TPC_PTFE_reflector_LXe_phys, pTeflonOpticalSurface);
	new G4LogicalBorderSurface("LXe_PTFEReflectorLXe_LogicalBorderSurface2",
		LXe_ActiveVolume_Physical, TPC_PTFE_reflector_LXe_phys, pTeflonOpticalSurface);

	new G4LogicalBorderSurface("LXe_PTFEReflectorGXe_LogicalBorderSurface",
		LXe_extra_filling_phys, TPC_PTFE_reflector_GXe_phys, pTeflonOpticalSurface);
	new G4LogicalBorderSurface("LXe_PTFEReflectorGXe_LogicalBorderSurface2",
		LXe_ActiveVolume_Physical, TPC_PTFE_reflector_GXe_phys, pTeflonOpticalSurface);

	// Top PMT Holder
	if (LXe_extra_filling_height > 16.*mm)	
	{
	new G4LogicalBorderSurface("LXe_TopPMTHolder_LogicalBorderSurface",
		LXe_extra_filling_phys, TPC_PTFE_TopPMTHolder_phys, pTeflonOpticalSurface);
	}
	if (LXe_extra_filling_height < 24.*mm)
	{
	new G4LogicalBorderSurface("GXe_TopPMTHolder_LogicalBorderSurface",
		GXe_Physical, TPC_PTFE_TopPMTHolder_phys, pGXeTeflonOpticalSurface);
	}

	// PTFE spacer 1 - "the upper one"
	if (LXe_extra_filling_height > 11.*mm)	
	{
	new G4LogicalBorderSurface("LXe_Spacer1_LogicalBorderSurface",
		LXe_extra_filling_phys, TPC_PTFE_spacer1_phys, pTeflonOpticalSurface);
	}
	if (LXe_extra_filling_height < 13.*mm)	
	{
	new G4LogicalBorderSurface("GXe_Spacer1_LogicalBorderSurface",
		GXe_Physical, TPC_PTFE_spacer1_phys, pGXeTeflonOpticalSurface);
	}

	// PTFE spacer 2 - "the lower one"
	if (LXe_extra_filling_height > 3.*mm)	
	{
	new G4LogicalBorderSurface("LXe_Spacer2_LogicalBorderSurface",
		LXe_extra_filling_phys, TPC_PTFE_spacer2_phys, pTeflonOpticalSurface);
	}
	if (LXe_extra_filling_height < 8.*mm)	
	{
	new G4LogicalBorderSurface("GXe_Spacer2_LogicalBorderSurface",
		GXe_Physical, TPC_PTFE_spacer2_phys, pGXeTeflonOpticalSurface);
	}
	
	// PTFE spacer 3 - added for improved position reconstruction
	if (TPC_PTFE_spacer3_height > 0)
	{
	new G4LogicalBorderSurface("LXe_Spacer3_LogicalBorderSurface",
		LXe_extra_filling_phys, TPC_PTFE_spacer3_phys, pTeflonOpticalSurface);
	new G4LogicalBorderSurface("GXe_Spacer3_LogicalBorderSurface",
		GXe_Physical, TPC_PTFE_spacer3_phys, pGXeTeflonOpticalSurface);
	}

	// PTFE pillars	-> put into for loop where implemented
	/*
	new G4LogicalBorderSurface("LXe_PTFEpillarLXe_LogicalBorderSurface",
		LXe_Physical, TPC_PTFE_pillar_LXe_phys, pTeflonOpticalSurface);
	new G4LogicalBorderSurface("GXe_PTFEpillarGXe_LogicalBorderSurface",
		GXe_Physical, TPC_PTFE_pillar_GXe_phys, pGXeTeflonOpticalSurface);
	new G4LogicalBorderSurface("LXe_PTFEpillarGXe_LogicalBorderSurface",
		LXe_extra_filling_phys, TPC_PTFE_pillar_GXe_phys, pTeflonOpticalSurface);
	*/


//**********************************************SENSITIVE DETECTORS**********************************************

	G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
	
	//Sensitive Detector: Setting all the LXe as a Sensitive Detector.
	XebraLXeSensitiveDetector *pLXeSD = new XebraLXeSensitiveDetector("Xebra/LXeSD");
	pSDManager->AddNewDetector(pLXeSD);

	// ToDo: check which volumes to make LXe SD
/*
	LXe_Logical->SetSensitiveDetector(pLXeSD);
	LXe_extra_filling_log->SetSensitiveDetector(pLXeSD);
	if (height_LXe_TPC_cylinder > 0.)	
		{
		LXe_weir_1_log->SetSensitiveDetector(pLXeSD);
		}
	if (height_LXe_GXe_cylinder > 0.)	
		{
		LXe_weir_2_log->SetSensitiveDetector(pLXeSD);
		}
*/
	LXe_ActiveVolume_Logical->SetSensitiveDetector(pLXeSD);
	//LXe_ActiveVolume_extra_filling_Logical->SetSensitiveDetector(pLXeSD);
	
	//Sensitive Detector: Setting the PMTs as sensitive detector
		// PMTs already made SDs in corresponding classes
	R11410_GetPhotocathodeLogicalVolume = r11410->GetPhotocathodeLogicalVolume();
	R8520_GetPhotocathodeLogicalVolume = r8520->GetPhotocathodeLogicalVolume();
	
	if(pSDManager->GetCollectionID("PmtHitsCollection")==-1)
	{
		XebraPmtSensitiveDetector* pPmtSD = new XebraPmtSensitiveDetector("Xebra/PmtSD");
		pSDManager->AddNewDetector(pPmtSD);
		
		R11410_GetPhotocathodeLogicalVolume->SetSensitiveDetector(pPmtSD);
		R8520_GetPhotocathodeLogicalVolume->SetSensitiveDetector(pPmtSD);
	}


//**********************************************VISUALIZATION**********************************************

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

//**********************************************

  LXeMass_TPC = LXe_Logical->GetMass(false, false)/kg + LXe_weir_1_log->GetMass(false, false)/kg + LXe_extra_filling_log->GetMass(false, false)/kg + LXe_ActiveVolume_Logical->GetMass(false, false)/kg;
  LXeVolume_TPC = LXeMass_TPC/(LXe->GetDensity()*m3/kg);

  GXeMass_TPC = GXe_Logical->GetMass(false, false)/kg + GXe_weir_1_log->GetMass(false, false)/kg + GXe_weir_2_log->GetMass(false, false)/kg;
  GXeVolume_TPC = GXeMass_TPC/(GXe->GetDensity()*m3/kg);
  
  LXeMass_ActiveVolume = LXe_ActiveVolume_Logical->GetMass(false, false)/kg;
  LXeVolume_ActiveVolume = LXeMass_ActiveVolume/(LXe->GetDensity()*m3/kg);


	return TPC_Logical;
}

G4double XebraConstructTPC::GetInnerRadiusCryostat(){
	return this->cryostat_innerRadius;
}

G4double XebraConstructTPC::GetInnerHeightCryostat(){
	return this->cryostat_innerHeight;
}

G4double XebraConstructTPC::GetLXeMass_TPC(){
  return this->LXeMass_TPC;
}

G4double XebraConstructTPC::GetLXeVolume_TPC(){
  return this->LXeVolume_TPC;
}

G4double XebraConstructTPC::GetLXeMass_ActiveVolume(){
  return this->LXeMass_ActiveVolume;
}

G4double XebraConstructTPC::GetLXeVolume_ActiveVolume(){
  return this->LXeVolume_ActiveVolume;
}

G4double XebraConstructTPC::GetGXeMass_TPC(){
  return this->GXeMass_TPC;
}

G4double XebraConstructTPC::GetGXeVolume_TPC(){
  return this->GXeVolume_TPC;
}
 
void XebraConstructTPC:: PrintGeometryInformation()
{
	//================================== Xenon =============================================================== 
	LXeMass_T = XebraConstructTPC::GetLXeMass_TPC();
	LXeMass_A = XebraConstructTPC::GetLXeMass_ActiveVolume();
	GXeMass_T = XebraConstructTPC::GetGXeMass_TPC();
	LXeVolume_T = XebraConstructTPC::GetLXeVolume_TPC();
	LXeVolume_A = XebraConstructTPC::GetLXeVolume_ActiveVolume();
	GXeVolume_T = XebraConstructTPC::GetGXeVolume_TPC();
	
	G4cout << "======================================================================================== " << G4endl;
	G4cout << "LXe:                               " << LXeMass_T << " kg " << "    =============    " << LXeVolume_T << " m3 " << G4endl;
	G4cout << "GXe:                               " << GXeMass_T << " kg " << "    =============    " << GXeVolume_T << " m3 " << G4endl;
	G4double TotalXenonMass = LXeMass_T + GXeMass_T;
	G4double TotalXenonVolume = LXeVolume_T + GXeVolume_T;
	G4cout << "                                   ===================================================== " << G4endl;
	G4cout << "Total Xenon in TPC envelope:       " << TotalXenonMass << " kg " << "    =============    " << TotalXenonVolume << " m3 " << G4endl;
	G4cout << "======================================================================================== " << G4endl;
	G4cout << "LXe in active volume:              " << LXeMass_A << " kg " << "    =============    " << LXeVolume_A << " m3 " << G4endl;
	G4cout << "======================================================================================== " << G4endl;

}


#include "XebraConstructTPC.hh"

//Detector Components
#include "XebraConstructSensors.hh"

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
  PMT_material  = G4Material::GetMaterial("PMT_material");
	Aluminium  = G4Material::GetMaterial("Aluminium");

	// General useful functions
	rmz45 = new G4RotationMatrix();
	rmz45->rotateZ(45.*deg);	
	rmz120 = new G4RotationMatrix();
	rmz120->rotateZ(120.*deg);	
	rmz165 = new G4RotationMatrix();
	rmz165->rotateZ(165.*deg);
	rmz225 = new G4RotationMatrix();
	rmz225->rotateZ(225.*deg);	
	rmz285 = new G4RotationMatrix();
	rmz285->rotateZ(285.*deg);
 
  // Parameters Cryostat, TPC and Teflon
	TPC_dimension_z = 310.0 * mm;
	TPC_dimension_r = 72.0 * mm;
	TPC_offsetOrigin_z = 0.0 * mm; // ToDo: shift origin of coordinate system from center entire setup to gate

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
  TPC_PTFE_pillar_d_dimension_z = 3.0 * mm; // repeats 6 times
  TPC_PTFE_pillar_d_position_r = 70.0*mm-(TPC_PTFE_pillar_d_dimension_x/2);
	TPC_PTFE_pillar_e_dimension_x = 14.8 * mm;
  TPC_PTFE_pillar_e_dimension_z = 10.2 * mm; // repeats 5 times
  TPC_PTFE_pillar_e_position_r = 70.0*mm-(TPC_PTFE_pillar_e_dimension_x/2);
	TPC_PTFE_pillar_f_dimension_x = 20.0 * mm;
  TPC_PTFE_pillar_f_dimension_z = 2.8 * mm;
  TPC_PTFE_pillar_f_position_r = 70.0*mm-(TPC_PTFE_pillar_f_dimension_x/2);
	//TPC_PTFE_pillar_g_dimension_x;
  //TPC_PTFE_pillar_g_dimension_z;
  //TPC_PTFE_pillar_g_position_r = 70.0*mm-(TPC_PTFE_pillar_g_dimension_x/2);
	//TPC_PTFE_pillar_h_dimension_x;
  //TPC_PTFE_pillar_h_dimension_z;
  //TPC_PTFE_pillar_h_position_r = 70.0*mm-(TPC_PTFE_pillar_h_dimension_x/2);

  // Parameters LXe and GXe
  GXe_height = 1.*mm;

  // Parameters Electrodes, Field Shaping Rings (FSR) and sensors
  

//**************************************************CONSTRUCT*********************************************************

  // Construct objects
	// Abbreviations (p...) according to https://wiki.uni-freiburg.de/app/lib/exe/fetch.php?media=start:ultimate:xebra:tpc:labtpc_assembly.pdf

	// Xenon volumes
  TPC_cylinder = new G4Tubs("TPC_cylinder", 0.*cm, cryostat_innerRadius, cryostat_innerHeight/2, 0.*deg, 360.*deg);  
  GXe_cylinder = new G4Tubs("GXe_cylinder", 0.*cm, cryostat_innerRadius, GXe_height/2, 0.*deg, 360.*deg);

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
	TPC_Al_filler_solid_5 = new G4SubtractionSolid("TPC_Al_filler_solid_5", TPC_Al_filler_solid_sub5_1, TPC_Al_filler_solid_sub5, 0, G4ThreeVector(-29.603*mm, 50.816*mm, 5.*mm / 2 - 135.*mm / 2));

	TPC_Al_filler_solid = TPC_Al_filler_solid_5;

	// Field Shaping Electrodes (p5)
	TPC_Cu_FSE_solid =  new G4Tubs("TPC_SS_PMTfixture_solid_orig", 100.0*mm / 2, 110.0*mm / 2, 10.0*mm / 2, 0.*deg, 360.*deg);

	// PTFE pillar (p2) - numbering layers from low to high z-position (excluding repetitive solids)
	TPC_PTFE_pillar_a_solid = new G4Box("TPC_PTFE_pillar_a_solid", TPC_PTFE_pillar_a_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_a_dimension_z / 2);
	TPC_PTFE_pillar_b_solid = new G4Box("TPC_PTFE_pillar_b_solid", TPC_PTFE_pillar_b_dimension_x / 2, TPC_PTFE_pillar_dimension_y / 2, TPC_PTFE_pillar_b_dimension_z / 2);


//**************************************************LOGICALVOLUMES*****************************************************

  TPC_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "TPC_Logical", 0, 0, 0);
  LXe_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "LXe_Logical", 0, 0, 0);
  GXe_Logical = new G4LogicalVolume(GXe_cylinder, GXe, "GXe_Logical", 0, 0, 0);

	TPC_SS_PMTfixture_log = new G4LogicalVolume(TPC_SS_PMTfixture_solid, SS304LSteel, "TPC_SS_PMTfixture_log");
	TPC_Al_filler_log = new G4LogicalVolume(TPC_Al_filler_solid, Aluminium, "TPC_Al_filler_log");
	TPC_Cu_FSE_log = new G4LogicalVolume(TPC_Cu_FSE_solid, Copper, "TPC_Cu_FSE_log");
	TPC_PTFE_pillar_a_log = new G4LogicalVolume(TPC_PTFE_pillar_a_solid, Teflon, "TPC_PTFE_pillar_a_log");
	TPC_PTFE_pillar_b_log = new G4LogicalVolume(TPC_PTFE_pillar_b_solid, Teflon, "TPC_PTFE_pillar_b_log");
	TPC_PTFE_pillar_c_log = new G4LogicalVolume(TPC_PTFE_pillar_c_solid, Teflon, "TPC_PTFE_pillar_c_log");
	TPC_PTFE_pillar_d_log = new G4LogicalVolume(TPC_PTFE_pillar_d_solid, Teflon, "TPC_PTFE_pillar_d_log");
	TPC_PTFE_pillar_e_log = new G4LogicalVolume(TPC_PTFE_pillar_e_solid, Teflon, "TPC_PTFE_pillar_e_log");
	TPC_PTFE_pillar_f_log = new G4LogicalVolume(TPC_PTFE_pillar_f_solid, Teflon, "TPC_PTFE_pillar_f_log");

  
//***********************************************PHYSICALVOLUME*******************************************************

  // Filling TPC Volume with LXe
  LXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., TPC_offsetOrigin_z), LXe_Logical,"LXe_TPC", TPC_Logical, false, 0);
  
  // Replacing LXe with GXe
  GXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height/2 + TPC_offsetOrigin_z), GXe_Logical,"GXe_TPC", LXe_Logical, false, 0);

  // Placing all TPC components fully emerged in LXe
	TPC_SS_PMTfixture_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, 5.*mm / 2 - TPC_dimension_z / 2 + TPC_offsetOrigin_z), TPC_SS_PMTfixture_log,"TPC_SS_PMTfixture", LXe_Logical, 0, 0);
	TPC_Al_filler_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 135.*mm / 2 + TPC_offsetOrigin_z), TPC_Al_filler_log,"TPC_Al_filler", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_1_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-1) * 13 * mm + 10.0*mm / 2 + TPC_offsetOrigin_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_1", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_2_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-2) * 13 * mm + 10.0*mm / 2 + TPC_offsetOrigin_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_2", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_3_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-3) * 13 * mm + 10.0*mm / 2 + TPC_offsetOrigin_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_3", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_4_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-4) * 13 * mm + 10.0*mm / 2 + TPC_offsetOrigin_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_4", LXe_Logical, 0, 0); 
	TPC_Cu_FSE_5_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 210.5 * mm + (1-5) * 13 * mm + 10.0*mm / 2 + TPC_offsetOrigin_z), TPC_Cu_FSE_log,"TPC_Cu_FSE_5", LXe_Logical, 0, 0); 
	
	// Placing Teflon pillars around active TPC
  for (int a=0; a < TPC_PTFE_pillar_number; ++a)
  { 
    G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);
    G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
    pillarRotation->rotateZ(rotate_angle*deg);

    G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_a_position_r; //variable for different pillar segments
    G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_a_position_r; //variable for different pillar segments

    name.str("");
    name << "TPC_PTFE_pillar_layer1_phys_" << a; //variable for different pillar segments
    TPC_PTFE_pillar_layer1_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_a_dimension_z / 2 + (0*mm) + TPC_offsetOrigin_z), TPC_PTFE_pillar_a_log, name.str(), LXe_Logical, false, 0); //variable for different pillar segments
  }
	for (int a=0; a < TPC_PTFE_pillar_number; ++a)
  { 
    G4double rotate_angle = a*(360./TPC_PTFE_pillar_number);
    G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
    pillarRotation->rotateZ(rotate_angle*deg);

    G4double pillars_XStep = cos(-rotate_angle*deg)*TPC_PTFE_pillar_b_position_r; //variable for different pillar segments
    G4double pillars_YStep = sin(-rotate_angle*deg)*TPC_PTFE_pillar_b_position_r; //variable for different pillar segments

    name.str("");
    name << "TPC_PTFE_pillar_layer2_phys_" << a; //variable for different pillar segments
    TPC_PTFE_pillar_layer2_phys = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep,-TPC_dimension_z / 2 + 140.0*mm + TPC_PTFE_pillar_b_dimension_z / 2 + (1*TPC_PTFE_pillar_a_dimension_z) + TPC_offsetOrigin_z), TPC_PTFE_pillar_b_log, name.str(), LXe_Logical, false, 0); //variable for different pillar segments
  }


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
  const G4double LXeMass = LXe_Logical->GetMass(false, false)/kg;
  const G4double LXeVolume = LXeMass/(LXe->GetDensity()*m3/kg);
  G4cout << "LXe:                               " << LXeMass << " kg " << "    =============    " << LXeVolume << " m3 " << G4endl;
  const G4double GXeMass = GXe_Logical->GetMass(false, false)/kg;
  const G4double GXeVolume = GXeMass/(GXe->GetDensity()*m3/kg);
  G4cout << "GXe:                                      " << GXeMass << " kg " << "     =============    " << GXeVolume << " m3 " << G4endl;
  const G4double TotalXenonMass = LXeMass + GXeMass;
  const G4double TotalXenonVolume = LXeVolume + GXeVolume;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total Xenon in TPC envelope:              " << TotalXenonMass << " kg " << "    =============    " << TotalXenonVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

}


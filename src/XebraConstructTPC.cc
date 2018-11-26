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
	rmz285 = new G4RotationMatrix();
	rmz285->rotateZ(285.*deg);
 
  // Parameters Cryostat, TPC and Teflon
	TPC_dimension_z = 310.0 * mm;
	TPC_dimension_r = 72.0 * mm;
	TPC_offsetOrigin_z = 0.0 * mm; // ToDo: adjust so that origin at gate

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

	TPC_Al_filler_solid = TPC_Al_filler_solid_2; //ToDo: add remaining subtractions


//**************************************************LOGICALVOLUMES*****************************************************

	//test_Logical = new G4LogicalVolume(TPC_Al_filler_solid_2, LXe, "test_Logical");

  TPC_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "TPC_Logical", 0, 0, 0);
  LXe_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "LXe_Logical", 0, 0, 0);
  GXe_Logical = new G4LogicalVolume(GXe_cylinder, GXe, "GXe_Logical", 0, 0, 0);

	TPC_SS_PMTfixture_log = new G4LogicalVolume(TPC_SS_PMTfixture_solid, SS304LSteel, "TPC_SS_PMTfixture_log");
	TPC_Al_filler_log = new G4LogicalVolume(TPC_Al_filler_solid, Aluminium, "TPC_Al_filler_log");

  
//***********************************************PHYSICALVOLUME*******************************************************

  // Filling TPC Volume with LXe
  LXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), LXe_Logical,"LXe_TPC", TPC_Logical, false, 0);
  
  // Replacing LXe with GXe
  GXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height/2), GXe_Logical,"GXe_TPC", LXe_Logical, false, 0);

  // Placing all TPC components fully emerged in LXe
	//test_phys = new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,0.), test_Logical,"test", LXe_Logical, false, 0);
	TPC_SS_PMTfixture_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, 5.*mm / 2 - TPC_dimension_z / 2), TPC_SS_PMTfixture_log,"TPC_SS_PMTfixture", LXe_Logical, 0, 0); //ToDo: change z position
	TPC_Al_filler_phys = new G4PVPlacement(nullptr,G4ThreeVector(0*cm, 0*cm, -TPC_dimension_z / 2 + 135.*mm / 2), TPC_Al_filler_log,"TPC_Al_filler", LXe_Logical, 0, 0); 
	

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


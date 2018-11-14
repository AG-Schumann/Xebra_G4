#include "XebraConstructTPC.hh"

//Detector Components
#include "XebraConstructSensors.hh"

XebraConstructTPC::XebraConstructTPC(XebraDetectorConstruction *){

  //these values will be used for the cryostat
  cryostat_innerRadius = 1.4*m;
  cryostat_innerHeight = 3.2*m;

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
 
  // Parameters Cryostat, TPC and Teflon
  activeTPC_innerRadius = 1.3*m; 
  activeTPC_height = 2.6*m;
  reflector_thickness = 2.0*mm;  
  reflector_bottom_height = 6.*cm;
  pillar_thickness = 2.*cm; 
  pillar_width = 3.*cm;
  pillar_number = 24.;

  // Parameters LXe and GXe
  GXe_height = 400.*mm;
  LXe_extra_filling = 1.*mm;

  // Parameters Electrodes, Field Shaping Rings (FSR) and sensors
  electrodes_frame_thickness = 38.*mm;
  electrodes_top_frame_height = 60.*mm;
  cathode_frame_height = 20.*mm;
  bottomscreen_frame_height = 8.*mm;
  FSR_thickness = 5.*mm;
  FSR_height = 20.*mm;
  FSR_innerRadius = activeTPC_innerRadius + 13.*mm;
  sensor_thickness = 20.*mm;

//**************************************************CONSTRUCT*********************************************************

  // Construct objects
  TPC_cylinder = new G4Tubs("TPC_cylinder", 0.*cm, cryostat_innerRadius, cryostat_innerHeight/2, 0.*deg, 360.*deg);  
  GXe_cylinder = new G4Tubs("GXe_cylinder", 0.*cm, cryostat_innerRadius, GXe_height/2, 0.*deg, 360.*deg);

  PTFE_reflector = new G4Tubs("PTFE_reflector", activeTPC_innerRadius, activeTPC_innerRadius + reflector_thickness, 
	activeTPC_height/2, 0.*deg, 360.*deg);
  PTFE_reflector_top = new G4Tubs("PTFE_reflector_top", activeTPC_innerRadius, activeTPC_innerRadius + reflector_thickness, 
	electrodes_top_frame_height/2, 0.*deg, 360.*deg);
  PTFE_reflector_bottom = new G4Tubs("PTFE_reflector_bottom", activeTPC_innerRadius, activeTPC_innerRadius + reflector_thickness, 
	reflector_bottom_height/2, 0.*deg, 360.*deg); 

  SS304_electrodes_top_frame = new G4Tubs("SS304_electrodes_top_frame", activeTPC_innerRadius + reflector_thickness,
	activeTPC_innerRadius + reflector_thickness + electrodes_frame_thickness - reflector_thickness, electrodes_top_frame_height/2, 0.*deg, 360.*deg);  
  SS304_cathode_frame = new G4Tubs("SS304_cathode_frame", activeTPC_innerRadius, activeTPC_innerRadius + electrodes_frame_thickness, 
	cathode_frame_height/2, 0.*deg, 360.*deg); 
  SS304_bottomscreen_frame = new G4Tubs("SS304_bottomscreen_frame", activeTPC_innerRadius, activeTPC_innerRadius + 
	electrodes_frame_thickness, bottomscreen_frame_height/2, 0.*deg, 360.*deg);
  
  LXe_extra_filling_inside = new G4Tubs("LXe_extra_filling_inside", 0.*cm, activeTPC_innerRadius, LXe_extra_filling/2, 0.*deg, 360.*deg);
  LXe_extra_filling_outside = new G4Tubs("LXe_extra_filling_outside", activeTPC_innerRadius + electrodes_frame_thickness, cryostat_innerRadius, LXe_extra_filling/2, 0.*deg, 360.*deg);
  LXe_sensitive = new G4Tubs("LXe_sensitive", 0.*cm, activeTPC_innerRadius, activeTPC_height/2, 0.*deg, 360.*deg);

  Cu_Fsr = new G4Tubs("Cu_Fsr", FSR_innerRadius, FSR_innerRadius + FSR_thickness, FSR_height/2, 0.*deg, 360.*deg);

  PTFE_pillar = new G4Box("PTFE_pillar", pillar_width/2, pillar_thickness/2, activeTPC_height/2);
  PTFE_pillar_bottom = new G4Box("PTFE_pillar_bottom", pillar_width/2, pillar_thickness/2, reflector_bottom_height/2);


//**************************************************LOGICALVOLUMES*****************************************************

  TPC_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "TPC_Logical", 0, 0, 0);
  LXe_Logical = new G4LogicalVolume(TPC_cylinder, LXe, "LXe_Logical", 0, 0, 0);
  GXe_Logical = new G4LogicalVolume(GXe_cylinder, GXe, "GXe_Logical", 0, 0, 0);

  PTFE_reflector_Logical = new G4LogicalVolume(PTFE_reflector, Teflon, "PTFE_reflector_Logical", 0, 0, 0);
  PTFE_reflector_top_Logical = new G4LogicalVolume(PTFE_reflector_top, Teflon, "PTFE_reflector_top_Logical", 0, 0, 0);
  PTFE_reflector_bottom_Logical = new G4LogicalVolume(PTFE_reflector_bottom, Teflon, "PTFE_reflector_bottom_Logical", 0, 0, 0);

  SS304_electrodes_top_frame_Logical = new G4LogicalVolume(SS304_electrodes_top_frame, SS304LSteel, "SS304_electrodes_top_frame_Logical", 0, 0, 0);
  SS304_cathode_frame_Logical = new G4LogicalVolume(SS304_cathode_frame, SS304LSteel, "SS304_cathode_frame_Logical", 0, 0, 0);
  SS304_bottomscreen_frame_Logical = new G4LogicalVolume(SS304_bottomscreen_frame, SS304LSteel, "SS304_bottomscreen_frame_Logical", 0, 0, 0);

  LXe_extra_filling_inside_Logical = new G4LogicalVolume(LXe_extra_filling_inside, LXe, "LXe_extra_filling_inside_Logical", 0, 0, 0);
  LXe_extra_filling_outside_Logical = new G4LogicalVolume(LXe_extra_filling_outside, LXe, "LXe_extra_filling_outside_Logical", 0, 0, 0);
  LXe_sensitive_Logical = new G4LogicalVolume(LXe_sensitive, LXe, "LXe_sensitive_Logical", 0, 0, 0);

  Cu_FSR_Logical = new G4LogicalVolume(Cu_Fsr, Copper, "Cu_FSR_Logical", 0, 0, 0);

  PTFE_pillar_Logical = new G4LogicalVolume(PTFE_pillar, Teflon, "PTFE_pillar_Logical", 0, 0, 0);
  PTFE_pillar_bottom_Logical = new G4LogicalVolume(PTFE_pillar_bottom, Teflon, "PTFE_pillar_bottom_Logical", 0, 0, 0);


  // Create Logical SensorArray Volume from corresponding class
  XebraConstructSensors *sensors = new XebraConstructSensors(this);
  PMT_sensorarray_Logical = sensors->Construct(sensor_thickness, activeTPC_innerRadius);

  
//***********************************************PHYSICALVOLUME*******************************************************

  // Filling TPC Volume with LXe
  LXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.), LXe_Logical,"LXe_TPC", TPC_Logical, false, 0);
  
  // Replacing LXe with GXe
  GXe_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height/2), GXe_Logical,"GXe_TPC", LXe_Logical, false, 0);
  

  // Placing all TPC components fully emerged in LXe
  PTFE_reflector_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height - activeTPC_height/2), PTFE_reflector_Logical, 
	"PTFE_reflector_main", LXe_Logical, false, 0);
  PTFE_reflector_bottom_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height - activeTPC_height - cathode_frame_height -
	reflector_bottom_height/2), PTFE_reflector_bottom_Logical, "PTFE_reflector_bottom", LXe_Logical, false, 0);
  SS304_cathode_frame_Physical = new G4PVPlacement(0, G4ThreeVector(0., 0., cryostat_innerHeight/2 - GXe_height - activeTPC_height - 
	cathode_frame_height/2), SS304_cathode_frame_Logical, "SS304_cathode_frame", LXe_Logical, false, 0);
  SS304_bottomscreen_frame_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height - activeTPC_height - cathode_frame_height-
	reflector_bottom_height - bottomscreen_frame_height/2), SS304_bottomscreen_frame_Logical, 
	"SS304_bottomscreen_frame", LXe_Logical, false, 0);
  PMT_sensorarray_bottom_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height - activeTPC_height - 
	cathode_frame_height - reflector_bottom_height - bottomscreen_frame_height - sensor_thickness/2), PMT_sensorarray_Logical, 
	"PMT_sensorarray_bottom", LXe_Logical, false, 0);


  // Placing Field Shaping Rings (FSR)
  FSR_number = 92.;
  FSR_separation = 28.*mm;
  FSR_offsetZ = FSR_height/2 + 12*mm;
  for(int a=0; a < FSR_number; ++a)
  {
    G4double rings_ZStep = cryostat_innerHeight/2 - GXe_height - activeTPC_height + FSR_offsetZ + a*FSR_separation;
    name.str("");
    name << "Cu_FSR_" << a;
    Cu_FSR_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,rings_ZStep), Cu_FSR_Logical, name.str(), LXe_Logical, false, 0);
  }

  // Placing Teflon pillars around active TPC
  for (int a=0; a < pillar_number; ++a)
  { 
    G4double rotate_angle = 90.0 + (a*(360./pillar_number)); //(in degrees) the offset of 90 deg is because we start rotating the pillar in the axis x (DistanceRadial,0) (PATRICIA)
    G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
    pillarRotation->rotateZ(rotate_angle*deg); //the units are SUPER IMPORTANT

    G4double DistanceRadial = FSR_innerRadius + FSR_thickness + pillar_thickness/2;
    G4double pillars_XStep = sin(rotate_angle*deg)*DistanceRadial; 
    G4double pillars_YStep = cos(rotate_angle*deg)*DistanceRadial; 

    name.str("");
    name << "PTFE_Pillar_main" << a;
    PTFE_pillar_Physical = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, cryostat_innerHeight/2 - 
	GXe_height - activeTPC_height/2), PTFE_pillar_Logical, name.str(), LXe_Logical, false, 0);
  }

  // Placing Teflon pillars around bottom part of TPC (SAME ROTATION MATRIX)
  for (int a=0; a < pillar_number; ++a)
  { 
    G4double rotate_angle = 90.0 + (a*(360./pillar_number)); //(in degrees) the offset of 90 deg is because we start rotating the pillar in the axis x (DistanceRadial,0) (PATRICIA)
    G4RotationMatrix* pillarRotation = new G4RotationMatrix; 
    pillarRotation->rotateZ(rotate_angle*deg); //the units are SUPER IMPORTANT

    G4double DistanceRadial = FSR_innerRadius + FSR_thickness + pillar_thickness/2;
    G4double pillars_XStep = sin(rotate_angle*deg)*DistanceRadial; 
    G4double pillars_YStep = cos(rotate_angle*deg)*DistanceRadial; //Coordinates X and Y should be the same for both arrays of pillars, the only difference is in the coordinate Z

    name.str("");
    name << "PTFE_Pillar_bottom_" << a;
    PTFE_pillar_bottom_Physical = new G4PVPlacement(pillarRotation, G4ThreeVector(pillars_XStep, pillars_YStep, cryostat_innerHeight/2 - 
	GXe_height - activeTPC_height - cathode_frame_height - reflector_bottom_height/2), PTFE_pillar_bottom_Logical, 
	name.str(), LXe_Logical, false, 0);
  }

  // Placing all TPC components in GXe
  PTFE_reflector_top_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., -GXe_height/2 + electrodes_top_frame_height/2), 
	PTFE_reflector_top_Logical, "PTFE_reflector_top", GXe_Logical, false, 0);
  SS304_electrodes_top_frame_Physical = new G4PVPlacement(0, G4ThreeVector(0., 0., -GXe_height/2 + electrodes_top_frame_height/2), 
	SS304_electrodes_top_frame_Logical, "SS304_topelectrodes_frame", GXe_Logical, false, 0);
  PMT_sensorarray_top_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., - GXe_height/2 + electrodes_top_frame_height + sensor_thickness/2),      
  	PMT_sensorarray_Logical,"PMT_sensorarray_top", GXe_Logical, false, 0);

  // Adding extra LXe filling above gate-level (replacing GXe) 
  LXe_extra_filling_inside_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., - GXe_height/2 + LXe_extra_filling/2), LXe_extra_filling_inside_Logical, 
	"LXe_extra_filling_inside", GXe_Logical, false, 0);
  LXe_extra_filling_inside_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., - GXe_height/2 + LXe_extra_filling/2), LXe_extra_filling_outside_Logical, 
	"LXe_extra_filling_outside", GXe_Logical, false, 0);

  // Adding sensitive volume between cathode and gate
  LXe_sensitive_Physical = new G4PVPlacement(0, G4ThreeVector(0.,0., cryostat_innerHeight/2 - GXe_height - activeTPC_height/2), LXe_sensitive_Logical, "LXe_sensitive_TPC", LXe_Logical, false, 0);

//**********************************************VISUALIZATION**********************************************

  // Visualization Settings : TeflonColor
  G4Colour TeflonColor(1.,1.,1.);
  TeflonVisAtt = new G4VisAttributes(TeflonColor);
  TeflonVisAtt->SetVisibility(true);
  PTFE_reflector_Logical->SetVisAttributes(TeflonVisAtt); 
  PTFE_reflector_top_Logical->SetVisAttributes(TeflonVisAtt);
  PTFE_reflector_bottom_Logical->SetVisAttributes(TeflonVisAtt);
  PTFE_pillar_Logical->SetVisAttributes(TeflonVisAtt);
  PTFE_pillar_bottom_Logical->SetVisAttributes(TeflonVisAtt);
  
  // Visualization Settings : LXe
  G4Colour LXeColor(0.,1.,0.);
  LXeVisAtt = new G4VisAttributes(LXeColor);
  LXeVisAtt->SetVisibility(true);
  LXe_Logical->SetVisAttributes(LXeVisAtt); 
  LXe_extra_filling_inside_Logical->SetVisAttributes(LXeVisAtt);
  LXe_extra_filling_outside_Logical->SetVisAttributes(LXeVisAtt);
  LXe_sensitive_Logical->SetVisAttributes(LXeVisAtt);

  // Visualization Settings : GXe
  G4Colour GXeColor(1.,0.,0.);
  GXeVisAtt = new G4VisAttributes(GXeColor);
  GXeVisAtt->SetVisibility(true);
  GXe_Logical->SetVisAttributes(GXeVisAtt); 

  // Visualization Settings : Electrodes_top_frame
  G4Colour ElectrodesColor(0.,1.,1.);
  ElectrodesVisAtt = new G4VisAttributes(ElectrodesColor);
  ElectrodesVisAtt->SetVisibility(true);
  SS304_electrodes_top_frame_Logical->SetVisAttributes(ElectrodesVisAtt);

  // Visualization Settings: Cathode_frame
  G4Colour CathodeColor(1.,1.,0.);
  CathodeVisAtt = new G4VisAttributes(CathodeColor);
  CathodeVisAtt->SetVisibility(true);
  SS304_cathode_frame_Logical->SetVisAttributes(CathodeVisAtt);

  // Visualization Settings: Bottomscreen_frame
  G4Colour BottomscreenColor(1.,0.,1.);
  BottomscreenVisAtt = new G4VisAttributes(BottomscreenColor);
  BottomscreenVisAtt->SetVisibility(true);
  SS304_bottomscreen_frame_Logical->SetVisAttributes(BottomscreenVisAtt);

  // Visualization Settings: Field_shaping_rings
  G4Colour RingsColor(0.,0.,1.);
  RingsVisAtt = new G4VisAttributes(RingsColor);
  RingsVisAtt->SetVisibility(true);
  Cu_FSR_Logical->SetVisAttributes(RingsVisAtt);

  //Visualization Settings: Sensor_array
  G4Colour SensorColor(0.5, 0.5,0.5);
  SensorVisAtt = new G4VisAttributes(SensorColor);
  SensorVisAtt->SetVisibility(true);
  PMT_sensorarray_Logical->SetVisAttributes(SensorVisAtt);

  //Sensitive Detector: Setting the LXe_sensitive_Logical and LXe_extra_filling_inside_Logical as a Sensitive Detector
  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
  XebraLXeSensitiveDetector *pLXeSD = new XebraLXeSensitiveDetector("Xebra/LXeSD");
  pSDManager->AddNewDetector(pLXeSD);
  LXe_sensitive_Logical->SetSensitiveDetector(pLXeSD);
  LXe_extra_filling_inside_Logical-> SetSensitiveDetector(pLXeSD);

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
  const G4double LXeSensitiveMass = LXe_sensitive_Logical->GetMass(false,false)/kg;
  const G4double LXeSensitiveVolume = LXeSensitiveMass/(LXe->GetDensity()*m3/kg);
  G4cout << "LXe sensitive:                            " << LXeSensitiveMass << " kg " << "    =============    " << LXeSensitiveVolume << " m3 " << G4endl;   
  const G4double LXeMass = LXe_Logical->GetMass(false, false)/kg;
  const G4double LXeVolume = LXeMass/(LXe->GetDensity()*m3/kg);
  G4cout << "LXe buffer:                               " << LXeMass << " kg " << "    =============    " << LXeVolume << " m3 " << G4endl;
  const G4double GXeMass = GXe_Logical->GetMass(false, false)/kg;
  const G4double GXeVolume = GXeMass/(GXe->GetDensity()*m3/kg);
  G4cout << "GXe:                                      " << GXeMass << " kg " << "     =============    " << GXeVolume << " m3 " << G4endl;
  const G4double LXeMassFillingInside = LXe_extra_filling_inside_Logical->GetMass(false, false)/kg;
  const G4double LXeVolumeFillingInside = LXeMassFillingInside/(LXe->GetDensity()*m3/kg);
  G4cout << "LXe extra filling inside:                 " << LXeMassFillingInside << " kg " << "    =============    " << LXeVolumeFillingInside << " m3 " << G4endl;
  const G4double LXeMassFillingOutside = LXe_extra_filling_outside_Logical->GetMass(false, false)/kg;
  const G4double LXeVolumeFillingOutside = LXeMassFillingOutside/(LXe->GetDensity()*m3/kg);
  G4cout << "LXe extra filling outside:                " << LXeMassFillingOutside << " kg " << "    =============    " << LXeVolumeFillingOutside << " m3 " << G4endl;
  const G4double TotalXenonMass = LXeMass + GXeMass + LXeMassFillingInside + LXeMassFillingOutside + LXeSensitiveMass;
  const G4double TotalXenonVolume = LXeVolume + GXeVolume + LXeVolumeFillingInside + LXeVolumeFillingOutside + LXeSensitiveVolume;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total Xenon in TPC envelope:              " << TotalXenonMass << " kg " << "    =============    " << TotalXenonVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

  //================================== PTFE ================================================================ 
  const G4double PTFEReflectorMassCenter = PTFE_reflector_Logical->GetMass(false, false)/kg;
  const G4double PTFEReflectorVolumeCenter = PTFEReflectorMassCenter/(Teflon->GetDensity()*m3/kg);
  G4cout << "PTFE Reflector Center:                    " << PTFEReflectorMassCenter << " kg " << "    =============    " << PTFEReflectorVolumeCenter << " m3 " << G4endl;
  const G4double PTFEReflectorMassTop = PTFE_reflector_top_Logical->GetMass(false, false)/kg;
  const G4double PTFEReflectorVolumeTop = PTFEReflectorMassTop/(Teflon->GetDensity()*m3/kg);
  G4cout << "PTFE Reflector Top:                       " << PTFEReflectorMassTop << " kg " << "    =============    " << PTFEReflectorVolumeTop << " m3 " << G4endl;
  const G4double PTFEReflectorMassBottom = PTFE_reflector_bottom_Logical->GetMass(false, false)/kg;
  const G4double PTFEReflectorVolumeBottom = PTFEReflectorMassBottom/(Teflon->GetDensity()*m3/kg);
  G4cout << "PTFE Reflector Bottom:                    " << PTFEReflectorMassBottom << " kg " << "    =============    " << PTFEReflectorVolumeBottom << " m3 " << G4endl;
  const G4double PTFELongPillarMass = PTFE_pillar_Logical->GetMass(false, false)/kg;
  const G4double PTFELongPillarVolume = PTFELongPillarMass/(Teflon->GetDensity()*m3/kg);
  G4cout << "PTFE Long Pillar (24 units):              " << 24.0*PTFELongPillarMass  << " kg " << "     =============    " << 24.0*PTFELongPillarVolume << " m3 " << G4endl;
  G4cout <<" (" << PTFELongPillarMass << " kg per unit)" << G4endl;
  const G4double PTFEShortPillarMass = PTFE_pillar_bottom_Logical->GetMass(false, false)/kg;
  const G4double PTFEShortPillarVolume = PTFEShortPillarMass/(Teflon->GetDensity()*m3/kg);
  G4cout << "PTFE Short Pillar (24 units):             " << 24.0*PTFEShortPillarMass << " kg " << "     =============    " << 24.0*PTFEShortPillarVolume << " m3 " << G4endl;
  G4cout <<" (" << PTFEShortPillarMass << " kg per unit)" << G4endl;
  const G4double TotalPTFEMass = PTFEReflectorMassCenter + PTFEReflectorMassTop + PTFEReflectorMassBottom + 24.0*(PTFELongPillarMass+PTFEShortPillarMass);
  const G4double TotalPTFEVolume = PTFEReflectorVolumeCenter + PTFEReflectorVolumeTop + PTFEReflectorVolumeBottom + 24.0*(PTFELongPillarVolume+PTFEShortPillarVolume);
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total PTFE:                               " << TotalPTFEMass << " kg " << "      =============    " << TotalPTFEVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

  //================================== SS304LSteel ========================================================= 
  const G4double SS304TopFrameMass = SS304_electrodes_top_frame_Logical->GetMass(false, false)/kg;
  const G4double SS304TopFrameVolume = SS304TopFrameMass/(SS304LSteel->GetDensity()*m3/kg);
  G4cout << "SS304LSteel Top Frame:                    " << SS304TopFrameMass << " kg " << "    =============    " << SS304TopFrameVolume << " m3 " << G4endl;
  const G4double SS304CathodeFrameMass = SS304_cathode_frame_Logical->GetMass(false, false)/kg;
  const G4double SS304CathodeFrameVolume = SS304CathodeFrameMass/(SS304LSteel->GetDensity()*m3/kg);
  G4cout << "SS304LSteel Cathode Frame:                " << SS304CathodeFrameMass << " kg " << "    =============    " << SS304CathodeFrameVolume << " m3 " << G4endl;
  const G4double SS304BottomFrameMass = SS304_bottomscreen_frame_Logical->GetMass(false, false)/kg;
  const G4double SS304BottomFrameVolume = SS304BottomFrameMass/(SS304LSteel->GetDensity()*m3/kg);
  G4cout << "SS304LSteel Bottom Frame:                 " << SS304BottomFrameMass << " kg " << "    =============    " << SS304BottomFrameVolume << " m3 " << G4endl;
  const G4double SS304TotalPMass = SS304TopFrameMass + SS304CathodeFrameMass + SS304BottomFrameMass;
  const G4double SS304TotalPVolume = SS304TopFrameVolume + SS304CathodeFrameVolume + SS304BottomFrameVolume;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total SS304LSteel:                        " << SS304TotalPMass << " kg " << "    =============    " << SS304TotalPVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

  //================================== Copper ============================================================== 
  const G4double CopperFSRMass = Cu_FSR_Logical->GetMass(false, false)/kg;
  const G4double CopperFSRVolume = CopperFSRMass/(Copper->GetDensity()*m3/kg);
  G4cout << "Copper Shaping Ring (92 units):           " << 92.0*CopperFSRMass << " kg " << "    =============    " << 92.0*CopperFSRVolume << " m3 " << G4endl;
  G4cout << " (" << CopperFSRMass << " kg per unit)" << G4endl;
  const G4double CopperTotalMass = 92.0*CopperFSRMass;
  const G4double CopperTotalVolume = 92.0*CopperFSRVolume;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total Copper:                             " << CopperTotalMass << " kg " << "    =============    " << CopperTotalVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

  //================================== PhotoSensors ======================================================== 
  const G4double PhotoSensorsMass = PMT_sensorarray_Logical->GetMass(false, false)/kg;
  const G4double PhotoSensorsVolume = PhotoSensorsMass/(PMT_material->GetDensity()*m3/kg);
  G4cout << "PhotoSensors (2 disks):                   " << 2.0*PhotoSensorsMass << " kg " << "    =============    " << 2.0*PhotoSensorsVolume << " m3 " << G4endl;
  G4cout << " (" << PhotoSensorsMass << " kg per disk)" << G4endl;
  const G4double TotalPhotoSensorsMass = 2.0*PhotoSensorsMass;
  const G4double TotalPhotoSensorsVolume = 2.0*PhotoSensorsVolume;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total PhotoSensors:                       " << TotalPhotoSensorsMass << " kg " << "    =============    " << TotalPhotoSensorsVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

}


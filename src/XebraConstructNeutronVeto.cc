#include "XebraConstructNeutronVeto.hh"

XebraConstructNeutronVeto::XebraConstructNeutronVeto( XebraDetectorConstruction *){;}

XebraConstructNeutronVeto::~XebraConstructNeutronVeto() {;}

G4LogicalVolume* XebraConstructNeutronVeto::Construct( G4double outer_RadiusCryostat, G4double outer_HeightCryostat  ){
    
    Thickness_Sensor = 50.0*mm;
    Thickness_Scintillator = 0.67*m;

    outer_RadiusSensor = outer_RadiusCryostat + Thickness_Scintillator + Thickness_Sensor;  
    outer_HeightSensor = outer_HeightCryostat + 2*Thickness_Scintillator + 2.0*Thickness_Sensor; 
    
    NeutronVetoSensorsMaterial  = G4Material::GetMaterial("PMT_material");
    NeutronVetoScintillatorMaterial  = G4Material::GetMaterial("LScint");

    //Solids
    NeutronVetoSensorsTube = new G4Tubs("NeutronVetoSensorsTube", 0.*cm, outer_RadiusSensor, outer_HeightSensor/2 , 0.*deg, 360.*deg);
    NeutronVetoScintillatorTube = new G4Tubs("NeutronVetoScintillatorTube", 0.*cm, outer_RadiusSensor-Thickness_Sensor, (outer_HeightSensor-2.0*Thickness_Sensor)/2 , 0.*deg, 360.*deg);
    
    // Logical Volume
    NeutronVetoSensorsLogicalVolume = new G4LogicalVolume(NeutronVetoSensorsTube, NeutronVetoSensorsMaterial, "NeutronVetoSensorsLogical", 0, 0, 0);
    NeutronVetoScintillatorLogicalVolume = new G4LogicalVolume(NeutronVetoScintillatorTube, NeutronVetoScintillatorMaterial, "NeutronVetoScintillatorLogical", 0, 0, 0);
    
    // Placement Volume
    NeutronVetoScintillatorPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0.,0., 0.),
                                                               NeutronVetoScintillatorLogicalVolume,"NeutronVeto_Scintillator",
                                                               NeutronVetoSensorsLogicalVolume, false, 0);
    
    // Visualization Settings
    G4Colour NeutronVetoSensorsColor(1.,0.,0.);
    NeutronVetoSensorsVisAtt = new G4VisAttributes(NeutronVetoSensorsColor);
    NeutronVetoSensorsVisAtt->SetVisibility(true);
    NeutronVetoSensorsLogicalVolume->SetVisAttributes(NeutronVetoSensorsVisAtt);
    
    G4Colour NeutronVetoScintillatorColor(1.,0.,0.);
    NeutronVetoScintillatorVisAtt = new G4VisAttributes(NeutronVetoScintillatorColor);
    NeutronVetoScintillatorVisAtt->SetVisibility(true);
    NeutronVetoScintillatorLogicalVolume->SetVisAttributes(NeutronVetoScintillatorVisAtt);

   //Sensitive Detector: Setting the LScintillator as a Sensitive Detector
   G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
   XebraLScintSensitiveDetector *pLScintSD = new XebraLScintSensitiveDetector("Xebra/LScintSD");
   pSDManager->AddNewDetector(pLScintSD);
   NeutronVetoScintillatorLogicalVolume->SetSensitiveDetector(pLScintSD); //Activate this part if you want to consider the LScintillator as a Sensitive Detector
    
   return NeutronVetoSensorsLogicalVolume;
    
}

G4LogicalVolume* XebraConstructNeutronVeto::GetMotherVolume(){
  return this->NeutronVetoScintillatorLogicalVolume;
}


void XebraConstructNeutronVeto::PrintGeometryInformation()
{
  //================================== PhotoSensor Material ================================================ 
  const G4double NeutronVetoSensorsMass = NeutronVetoSensorsLogicalVolume->GetMass(false, false)/kg;
  const G4double NeutronVetoSensorsVolume = NeutronVetoSensorsMass/(NeutronVetoSensorsMaterial->GetDensity()*m3/kg);
  G4cout << "Neutron Veto Sensors:                     " << NeutronVetoSensorsMass << " kg " << "    =============    " << NeutronVetoSensorsVolume << " m3 " << G4endl;

  const G4double TotalNeutronVetoSensorsMass =  NeutronVetoSensorsMass;
  const G4double TotalNeutronVetoSensorsVolume =  NeutronVetoSensorsVolume;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total Neutron Veto Sensors:               " << TotalNeutronVetoSensorsMass << " kg " << "    =============    " << TotalNeutronVetoSensorsVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

  //================================== Scintillator Material =============================================== 
  G4double ScintillatorInitialVolume = NeutronVetoScintillatorTube->GetCubicVolume()/m3;
  G4double CryostatVolume  = 3.14159*2.0*m*2.0*m*4.2*m/m3;
  G4double ScintillatorTotalVolume = (ScintillatorInitialVolume - CryostatVolume);
  G4double ScintillatorDensity = NeutronVetoScintillatorMaterial->GetDensity()*m3/kg;
  const G4double ScintillatorTotalMass = ScintillatorTotalVolume*ScintillatorDensity;
  G4cout << "Scintillator:                             " << ScintillatorTotalMass << " kg " << "    =============    " << ScintillatorTotalVolume << " m3 " << G4endl;
  G4cout << "                                          =================================================== " << G4endl;
  G4cout << "Total Scintillator:                       " << ScintillatorTotalMass << " kg " << "    =============    " << ScintillatorTotalVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;



}

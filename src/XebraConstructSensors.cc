#include "XebraConstructSensors.hh"

XebraConstructSensors::XebraConstructSensors(XebraConstructTPC *){;}

XebraConstructSensors::~XebraConstructSensors() {;}

G4LogicalVolume* XebraConstructSensors::Construct(G4double Sensordisk_thickness, G4double Sensordisk_radius){


    Thickness_Sensor = Sensordisk_thickness;
    outer_RadiusSensor = Sensordisk_radius;

    PMT_material  = G4Material::GetMaterial("PMT_material");

    // Objects
    Sensor_disk = new G4Tubs("Sensor_disk", 0.*cm, outer_RadiusSensor, Thickness_Sensor/2, 0.*deg, 360.*deg);

    //LogicalVolumes
    Sensor_LogicalVolume = new G4LogicalVolume(Sensor_disk, PMT_material, "Sensor_Logical", 0, 0, 0);  
    
    // initialize manager
    SDManager = G4SDManager::GetSDMpointer();
    
    if(SDManager->GetCollectionID("PmtHitsCollection")==-1)
    {
        PmtSD = new XebraPmtSensitiveDetector("Xebra/PmtSD");
        SDManager->AddNewDetector(PmtSD);
        Sensor_LogicalVolume->SetSensitiveDetector(PmtSD);
    }
        
    
    //Visualization Settings
    G4Colour SensorColor(1.,1.,1.);
    SensorVisAtt = new G4VisAttributes(SensorColor);
    SensorVisAtt->SetVisibility(true);
    Sensor_LogicalVolume->SetVisAttributes(SensorVisAtt);
    
    return Sensor_LogicalVolume;
    
}

#include "XebraDetectorConstruction.hh"

// Detector components
//a// #include "XebraConstructVeto.hh" //element 1
//a// #include "XebraConstructNeutronVeto.hh" //element 2
//a-temp// #include "XebraConstructCryostat.hh" //element 3
#include "XebraConstructTPC.hh" //element 4

//G4 Header Files
#include <G4SystemOfUnits.hh>

XebraDetectorConstruction::XebraDetectorConstruction(G4String fName) {  

  	m_pDetectorMessenger = new XebraDetectorMessenger(this);
  	detRootFile = fName;

}

XebraDetectorConstruction::~XebraDetectorConstruction(){
  	delete m_pDetectorMessenger;
}

G4VPhysicalVolume* XebraDetectorConstruction::Construct()
{
    //////////////// Define Materials //////////////////////
    XebraMaterials *Materials = new XebraMaterials();
    Materials->DefineMaterials();
    
    //////////////// Construt Laboratory ///////////////////
    ConstructLaboratory();

    G4cout << G4endl << "Laboratory constructed" << G4endl;
    
    //////////////// Construct Components //////////////////
    XebraConstructTPC *tpc = new XebraConstructTPC(this);
    TPCLogicalVolume = tpc->Construct();

    //a-temp//XebraConstructCryostat *cryostat = new XebraConstructCryostat(this);
    //a-temp//CryostatLogicalVolume = cryostat->Construct();

    //a// XebraConstructNeutronVeto *neutronveto = new XebraConstructNeutronVeto(this);
    //a// NeutronVetoScintillatorLogicalVolume = neutronveto->Construct( cryostat->GetOuterRadiusCryostat(), cryostat->GetOuterHeightCryostat() );

    //a// XebraConstructVeto *veto = new XebraConstructVeto(this);
    //a// VetoLogicalVolume = veto->Construct();

    /////////////////Place Components////////////////////

    MotherLogicalVolume = LabLogicalVolume;
    //a// VetoPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(),
    //a//                                               VetoLogicalVolume,"MuonVetoVolume",
    //a//                                               MotherLogicalVolume, false, 0);

    //a// MotherLogicalVolume = veto->GetMotherVolume();

    //a// NeutronVetoScintillatorPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(),
    //a//                                                           NeutronVetoScintillatorLogicalVolume,"NeutronVetoVolume",
    //a//                                                           MotherLogicalVolume, false, 0);

    //a// MotherLogicalVolume = neutronveto->GetMotherVolume();
    
    //a-temp//CryostatPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(),
    //a-temp//                                           CryostatLogicalVolume,"CryostatVolume",
    //a-temp//                                           MotherLogicalVolume, false, 0);
   
    //a-temp//MotherLogicalVolume = cryostat->GetMotherVolume();
    
    TPCPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(),
                                          TPCLogicalVolume,"TPCVolume",
                                          MotherLogicalVolume, false, 0);


   //////////////// Geometry Information /////////////////// 
   G4cout << "########################################################################################" << G4endl;
   //a// PrintGeometryInformation();   
   //a// neutronveto->PrintGeometryInformation();
   //a-temp//cryostat->PrintGeometryInformation();
   tpc->PrintGeometryInformation();
   G4cout << "########################################################################################" << G4endl;

   if(pCheckOverlap) SecondOverlapCheck();
   VolumesHierarchy();

   /////////////////////////////////////////////////////////
    
    return LabPhysicalVolume;

}

void XebraDetectorConstruction::ConstructLaboratory()
{
        LabHalfZ = 20*m;
        LabRadius = 20*m;
    
	Air = G4Material::GetMaterial("G4_AIR");

	LabTubs = new G4Tubs("LabTubs", 0.*cm, LabRadius, LabHalfZ, 0.*deg, 360.*deg);
  
	LabLogicalVolume = new G4LogicalVolume(LabTubs, Air, "LabVolume", 0, 0, 0);
  
	LabPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), LabLogicalVolume, "Lab", 0, false, 0);
  
	LabLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);
}

void XebraDetectorConstruction::PrintGeometryInformation()
{

  //a// //================================== Water ===============================================================
  //a// const G4double WaterMass = VetoLogicalVolume->GetMass(false, false)/kg;
  //a// const G4double WaterVolume = WaterMass*1000.0;
  //a// G4cout << "Water:                               " << WaterMass << " kg " << "     =============    " << WaterVolume << " m3 " << G4endl;
  //a// G4cout << "                                          =================================================== " << G4endl;
  //a// G4cout << "Total Water:                         " << WaterMass << " kg " << "     =============    " << WaterVolume << " m3 " << G4endl;
  //a// G4cout << "============================================================================================= " << G4endl;

}


void XebraDetectorConstruction::SecondOverlapCheck()
{
  
  G4PhysicalVolumeStore* thePVStore = G4PhysicalVolumeStore::GetInstance();
  G4cout << "\n" << "******************************" << G4endl;
  G4cout << "\n" << "CHECK FOR OVERLAPS" << G4endl;
  G4cout << "\n" << "******************************" << G4endl;
  G4cout <<"\n" << G4endl;
  
  G4cout << thePVStore->size() << " physical volumes are defined" << G4endl;
  
  G4bool overlapFlag = false;
  
  for (size_t i=0; i<thePVStore->size();i++){      
      overlapFlag = (*thePVStore)[i]->CheckOverlaps(5000) | overlapFlag;
  }


}


void XebraDetectorConstruction::VolumesHierarchy() {
  //=== Loop over all volumes and write to file list of: PhysicalVolume, LogicalVolume, MotherLogicalVolume ===

  G4PhysicalVolumeStore* thePVStore = G4PhysicalVolumeStore::GetInstance();  // get all defined volumes

  G4String n_PhysicalVolumeName;
  G4String n_LogicalVolumeName;
  G4String n_MotherVolumeName;

  std::string f_name =  "VolumesList.dat";
  std::ofstream f_volumeslist(f_name);
  G4cout << ">>> Writing list of volumes to file: " << f_name << G4endl;
  f_volumeslist << "PhysicalVolume LogicalVolume MotherLogicalVolume" << G4endl;

  // loop over all volumes in G4PhysicalVolumeStore and write to file
  for (size_t i = 1; i < thePVStore->size(); i++) {
    n_PhysicalVolumeName = (*thePVStore)[i]->GetName();
    n_LogicalVolumeName = (*thePVStore)[i]->GetLogicalVolume()->GetName();
    n_MotherVolumeName = (*thePVStore)[i]->GetMotherLogical()->GetName();
    f_volumeslist << n_PhysicalVolumeName << " " << n_LogicalVolumeName << " "
                  << n_MotherVolumeName << G4endl;
  }
  f_volumeslist.close();
}


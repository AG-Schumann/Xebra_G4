#include "XebraDetectorConstruction.hh"

// Detector components
#include "XebraConstructCryostat.hh"
#include "XebraConstructTPC.hh"


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

    XebraConstructCryostat *cryostat = new XebraConstructCryostat(this);
    CryostatLogicalVolume = cryostat->Construct();

    /////////////////Place Components////////////////////

		TPC_offset_origin = -29.5 * mm; //shift origin of coordinate system from center TPC volume to gate

    MotherLogicalVolume = LabLogicalVolume;
    
    CryostatPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0.,0.,TPC_offset_origin),
                                               CryostatLogicalVolume,"CryostatVolume",
                                               MotherLogicalVolume, false, 0);
   
    MotherLogicalVolume = cryostat->GetMotherVolume();

    TPCPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),
                                          TPCLogicalVolume,"TPCVolume",
                                          MotherLogicalVolume, false, 0);



   //////////////// Geometry Information /////////////////// 
   G4cout << "########################################################################################" << G4endl;
   cryostat->PrintGeometryInformation();
   tpc->PrintGeometryInformation();
   G4cout << "########################################################################################" << G4endl;

   if(pCheckOverlap) SecondOverlapCheck();
   VolumesHierarchy();

   /////////////////////////////////////////////////////////
    
    return LabPhysicalVolume;

}

void XebraDetectorConstruction::ConstructLaboratory()
{
        LabHalfZ = 3*m; //20*m
        LabRadius = 3*m; //20*m
    
	Air = G4Material::GetMaterial("G4_AIR");

	LabTubs = new G4Tubs("LabTubs", 0.*cm, LabRadius, LabHalfZ, 0.*deg, 360.*deg);
  
	LabLogicalVolume = new G4LogicalVolume(LabTubs, Air, "LabVolume", 0, 0, 0);
  
	LabPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), LabLogicalVolume, "Lab", 0, false, 0);
  
	LabLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);
}

void XebraDetectorConstruction::PrintGeometryInformation(){;}  //removed water from here, now empty


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


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
    
    //////////////// Construct Laboratory ///////////////////
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
   
	//PrintGeometryInformation();
	//tpc->PrintGeometryInformation();
	//cryostat->PrintGeometryInformation();
   
  G4double GXeMass_Cryostat = cryostat->GetGXeMass_Cryo_extravolume();
	G4double GXeVolume_Cryostat = cryostat->GetGXeVolume_Cryo_extravolume();
	
	G4double LXeMass_TPC = tpc->GetLXeMass_TPC();
	G4double LXeMass_ActiveVolume = tpc->GetLXeMass_ActiveVolume();
	G4double GXeMass_TPC = tpc->GetGXeMass_TPC();
	G4double LXeVolume_TPC = tpc->GetLXeVolume_TPC();
	G4double LXeVolume_ActiveVolume = tpc->GetLXeVolume_ActiveVolume();
	G4double GXeVolume_TPC = tpc->GetGXeVolume_TPC();
	
	G4double GXeMass = GXeMass_Cryostat + GXeMass_TPC;
	G4double GXeVolume = GXeVolume_Cryostat + GXeVolume_TPC;
	
	G4double TotalXenonMass = LXeMass_TPC + GXeMass_Cryostat + GXeMass_TPC;
	G4double TotalXenonVolume = LXeVolume_TPC + GXeVolume_Cryostat + GXeVolume_TPC;

	G4cout << " " << G4endl;	
	G4cout << "##################################################################################" << G4endl;	
	G4cout << "==================================================================================" << G4endl;
	G4cout << "           Xenon masses and volumes simulated in the cryostat envelope            " << G4endl;
	G4cout << "==================================================================================" << G4endl;
	G4cout << "                                 Mass                             Volume          " << G4endl;
	G4cout << "==================================================================================" << G4endl;
	G4cout << "Total LXe                        " << LXeMass_TPC << " kg " << "     =============    " << LXeVolume_TPC << " m3 " << G4endl;
	G4cout << "- active volume LXe              " << LXeMass_ActiveVolume << " kg " << "    =============    " << LXeVolume_ActiveVolume << " m3 " << G4endl;
  G4cout << "Total GXe                        " << GXeMass << " kg " << "   =============    " << GXeVolume << " m3 " << G4endl;
  G4cout << "==================================================================================" << G4endl;
  G4cout << "Total Xenon                      " << TotalXenonMass << " kg " << "     =============    " << TotalXenonVolume << " m3 " << G4endl;
  G4cout << "==================================================================================" << G4endl; 
	G4cout << "##################################################################################" << G4endl;

   /////////////////////////////////////////////////////////

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

void XebraDetectorConstruction::PrintGeometryInformation(){;}


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
  G4cout << ">>> Writing list of volumes to file: " << f_name << G4endl << G4endl;
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


//***********************************************
// Added by Alex
//***********************************************

// SetLXeAbsorbtionLength

void XebraDetectorConstruction::SetLXeAbsorbtionLength(G4double dAbsorbtionLength) {
  G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));

  if(pLXeMaterial)
    {
      G4cout << "----> Setting LXe absorbtion length to " << dAbsorbtionLength/cm << " cm" << G4endl;

      G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
			
      G4double LXe_PP[] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double LXe_ABSL[] = {dAbsorbtionLength, dAbsorbtionLength, dAbsorbtionLength};
      pLXePropertiesTable->RemoveProperty("ABSLENGTH");
      pLXePropertiesTable->AddProperty("ABSLENGTH", LXe_PP, LXe_ABSL, 3);
    }
  else
    {
      G4cout << "ls!> LXe materials not found!" << G4endl;
      exit(-1);
    }
}

// SetGXeAbsorbtionLength

void XebraDetectorConstruction::SetGXeAbsorbtionLength(G4double dAbsorbtionLength) {
  G4Material *pGXeMaterial = G4Material::GetMaterial(G4String("GXe"));
  
  if(pGXeMaterial)
    {
      G4cout << "----> Setting GXe absorbtion length to " << dAbsorbtionLength/m << " m" << G4endl;
    
      G4MaterialPropertiesTable *pGXePropertiesTable = pGXeMaterial->GetMaterialPropertiesTable();
    
      const G4int iNbEntries = 3;
    
      G4double GXe_PP[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double GXe_ABSL[iNbEntries] = {dAbsorbtionLength, dAbsorbtionLength, dAbsorbtionLength};
      pGXePropertiesTable->RemoveProperty("ABSLENGTH");
      pGXePropertiesTable->AddProperty("ABSLENGTH", GXe_PP, GXe_ABSL, iNbEntries);
    }
  else
    {
      G4cout << "ls!> GXe materials not found!" << G4endl;
      exit(-1);
    }
}

// SetTeflonReflectivity

void XebraDetectorConstruction::SetTeflonReflectivity(G4double dReflectivity) {
  G4Material *pTeflonMaterial = G4Material::GetMaterial(G4String("Teflon"));

  if(pTeflonMaterial)
    {
      G4cout << "----> Setting Teflon reflectivity to " << dReflectivity << G4endl;

      G4MaterialPropertiesTable *pTeflonPropertiesTable = pTeflonMaterial->GetMaterialPropertiesTable();
		
      G4double teflon_PP[] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
      G4double teflon_REFL[] = {dReflectivity, dReflectivity, dReflectivity};
      pTeflonPropertiesTable->RemoveProperty("REFLECTIVITY");
      pTeflonPropertiesTable->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, 3);
    }
  else
    {
      G4cout << "ls!> Teflon material not found!" << G4endl;
      exit(-1);
    }
}

// SetGXeTeflonReflectivity

void XebraDetectorConstruction::SetGXeTeflonReflectivity(G4double dGXeReflectivity)
{
  G4Material *pGXeTeflonMaterial = G4Material::GetMaterial(G4String("GXeTeflon"));
  
  if(pGXeTeflonMaterial)
    {
      G4cout << "----> Setting GXe Teflon reflectivity to " << dGXeReflectivity << G4endl;
    
      G4MaterialPropertiesTable *pGXeTeflonPropertiesTable = pGXeTeflonMaterial->GetMaterialPropertiesTable();
    
      const G4int iNbEntries = 3;
    
      G4double teflon_PP[iNbEntries] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
      G4double teflon_REFL[iNbEntries] = {dGXeReflectivity, dGXeReflectivity, dGXeReflectivity};
      pGXeTeflonPropertiesTable->RemoveProperty("REFLECTIVITY");
      pGXeTeflonPropertiesTable->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, iNbEntries);
   }
  else
   {
     G4cout << "ls!> GXe Teflon material not found!" << G4endl;
     exit(-1);
   }
}

// SetLXeRayScatterLength

void XebraDetectorConstruction::SetLXeRayScatterLength(G4double dRayScatterLength) {
  G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));
  
  if(pLXeMaterial)
    {      
      G4cout << "----> Setting LXe scattering length to " << dRayScatterLength/cm << " cm" << G4endl;
      
      G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
              
      G4double LXe_PP[] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double LXe_SCAT[] = {dRayScatterLength, dRayScatterLength, dRayScatterLength};
      pLXePropertiesTable->RemoveProperty("RAYLEIGH");
      pLXePropertiesTable->AddProperty("RAYLEIGH", LXe_PP, LXe_SCAT, 3);
    }
  else
    {
      G4cout << "ls!> LXe materials not found!" << G4endl;
      exit(-1);
    }

}

// SetLXeRefractionIndex

void XebraDetectorConstruction::SetLXeRefractionIndex(G4double dRefractionIndex)
{
  G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));
  
  if(pLXeMaterial)
    {
      G4cout << "----> Setting LXe refraction index to " << dRefractionIndex << G4endl;
    
      G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
	
      const G4int iNbEntries = 3;
    
      G4double LXe_PP[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
      G4double LXe_RI[iNbEntries] = {dRefractionIndex, dRefractionIndex, dRefractionIndex};
      pLXePropertiesTable->RemoveProperty("RINDEX");
	  pLXePropertiesTable->AddProperty("RINDEX", LXe_PP, LXe_RI, iNbEntries);
    }
  else
    {
      G4cout << "ls!> LXe materials not found!" << G4endl;
      exit(-1);
    }
}

// SetLXeScintillation

void XebraDetectorConstruction::SetLXeScintillation(G4bool bScintillation) {
  G4cout << "----> Setting LXe(GXe) scintillation to " << bScintillation << G4endl;
			
	G4Material *pLXeMaterial = G4Material::GetMaterial(G4String("LXe"));
	if(pLXeMaterial) 
	{	
		G4MaterialPropertiesTable *pLXePropertiesTable = pLXeMaterial->GetMaterialPropertiesTable();
		if(bScintillation)
		{
			//pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 10./(1.0*keV));
  		pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 1./(21.6*eV)); //ToDo: keep in mind that this changes the default value
			//pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 100000./(1.0*keV));//create 1e5 photons per keV
		}    
	}
  else
  {
  	G4cout << "ls!> LXe materials not found!" << G4endl;
    exit(-1);
  }
	
  G4Material *pGXeMaterial = G4Material::GetMaterial(G4String("GXe"));
  if(pGXeMaterial)
  {	
  	G4MaterialPropertiesTable *pGXePropertiesTable = pGXeMaterial->GetMaterialPropertiesTable();
    if(bScintillation)
		{
			//pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 1000/(1.0*keV));
			pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 1./(21.6*eV)); //ToDo: keep in mind that this changes the default value
		}  
	}
  else
  {
  	G4cout << "ls!> GXe materials not found!" << G4endl;
    exit(-1);
  }
}

//***********************End of code************************


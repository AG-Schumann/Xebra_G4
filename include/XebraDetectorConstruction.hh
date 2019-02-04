#ifndef __XEBRADETECTORCONSTRUCTION_H__
#define __XEBRADETECTORCONSTRUCTION_H__

// XEBRA header files
#include "XebraMaterials.hh"
#include "XebraDetectorMessenger.hh"
#include "XebraLScintSensitiveDetector.hh"
#include "XebraLXeSensitiveDetector.hh"

//Additional Header Files
#include <globals.hh>
#include <math.h>
#include <vector>
#include <map>
#include <vector>
#include <numeric>
#include <cassert>

//Root Header Files
#include "TFile.h"
#include "TDirectory.h"
#include <TParameter.h>

//G4 Header Files
#include <G4Material.hh>
#include <G4UnionSolid.hh>
#include <G4SubtractionSolid.hh>
#include <G4UImanager.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Orb.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SDManager.hh>
#include <G4ThreeVector.hh>
#include <G4PhysicalVolumeStore.hh>


class XebraDetectorConstruction: public G4VUserDetectorConstruction{

public:
    XebraDetectorConstruction(G4String fName);
    ~XebraDetectorConstruction();

    G4VPhysicalVolume* Construct();

    void SetCheckOverlap(G4bool dCheckOverlap)             {pCheckOverlap = dCheckOverlap;};
    
    // Added by Alex:
    
    void SetTeflonReflectivity(G4double dReflectivity);
		void SetGXeTeflonReflectivity(G4double dGXeReflectivity);
		void SetSS304LSteelReflectivity(G4double dReflectivity);
		void SetLXeScintillation(G4bool dScintillation);
		void SetLXeLevel(G4double dlevel);
		void SetMaterial (const G4String&);
		void SetLXeMeshMaterial (const G4String&);
		void SetGXeMeshMaterial (const G4String&);
		void SetLXeAbsorbtionLength(G4double dAbsorbtionLength);
		void SetGXeAbsorbtionLength(G4double dAbsorbtionLength);
		void SetLXeRayScatterLength(G4double dRayScatterLength);
		void SetLXeRefractionIndex(G4double dRefractionIndex);
	
		void SetLXeMeshTransparency(G4double dTransparency); 
		void SetGXeMeshTransparency(G4double dTransparency); 

		static G4double GetGeometryParameter(const char *szParameter);

private:
	void ConstructLaboratory();	
        void PrintGeometryInformation();
        void SecondOverlapCheck();
        void VolumesHierarchy();

private:

        // LAB 
        G4double LabHalfZ;
        G4double LabRadius;

	G4Material *Air;
	G4Tubs *LabTubs;

	G4LogicalVolume *MotherLogicalVolume;

	G4LogicalVolume *LabLogicalVolume;
	G4VPhysicalVolume *LabPhysicalVolume;

	// PARAMETERS
				G4double TPC_offset_origin; 
				G4double Cryostat_Inner_offset;
				
				static map<G4String, G4double> m_hGeometryParameters;
				void DefineGeometryParameters();

	// LOGICAL VOLUMES
        G4LogicalVolume *CryostatLogicalVolume;
        G4LogicalVolume *TPCLogicalVolume;


	// PHYSICAL VOLUMES
        G4VPhysicalVolume *CryostatPhysicalVolume;
        G4VPhysicalVolume *TPCPhysicalVolume;



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

  XebraDetectorMessenger *m_pDetectorMessenger;

  // parameters for communications with XebraGeometryMessenger ( Do we want to continue using this format?? (Patricia) )
  
  G4bool   pCheckOverlap;    

  /*G4String pNeutronSourceSurroundings;
  G4double pCryostatInnerWallThickness;
  G4double pCryostatOuterWallThickness;
  G4bool   pTPC;

  G4bool   pConstructLScintTopVessel;

  G4String pLScintNumberOfSideVessels;
  G4String pLScintVesselMaterial;*/
  
  // ROOT stuff
  //TFile      *_fGeom;
  G4String    detRootFile;
  //TDirectory *_detector;
  
};

#endif

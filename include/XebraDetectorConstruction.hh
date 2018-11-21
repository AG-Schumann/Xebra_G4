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

	//LOGICAL VOLUMES
        //a// G4LogicalVolume *VetoLogicalVolume;
        //a// G4LogicalVolume *NeutronVetoScintillatorLogicalVolume;
        //a-temp// G4LogicalVolume *CryostatLogicalVolume;
        G4LogicalVolume *TPCLogicalVolume;


	// PHYSICAL VOLUMES
	//a// G4VPhysicalVolume *VetoPhysicalVolume;	
        //a// G4VPhysicalVolume *NeutronVetoScintillatorPhysicalVolume;
        //a-temp// G4VPhysicalVolume *CryostatPhysicalVolume;
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

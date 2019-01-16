#ifndef XEBRACONSTRUCTCRYOSTAT_H
#define XEBRACONSTRUCTCRYOSTAT_H

//XEBRA header files
#include "XebraDetectorConstruction.hh"

//G4 Header Files
#include <G4SystemOfUnits.hh>
#include <G4UnionSolid.hh>
#include <G4SubtractionSolid.hh>
#include <G4UImanager.hh>
#include <G4VUserDetectorConstruction.hh>

#include <globals.hh>
#include <vector>
#include <map>


using std::vector;
using std::map;

class G4Sphere;
class G4Torus;
class G4LogicalVolume;
class G4VPhysicalVolume;


class XebraConstructCryostat{

public:
    XebraConstructCryostat( XebraDetectorConstruction* );
   ~XebraConstructCryostat();

   G4LogicalVolume* Construct();

   G4double GetOuterRadiusCryostat();
   G4double GetOuterHeightCryostat();
   G4LogicalVolume* GetMotherVolume();

  void PrintGeometryInformation();

private:

  //Parameters for the Cryostat Envelop
  G4double Cryostat_Envelop_Radius;  
  G4double Cryostat_Envelop_Height;

	// Parameters for the TPC Envelop
  G4double Cryostat_TPCEnvelop_Radius;  
  G4double Cryostat_TPCEnvelop_Height;

  //Parameters for the outer Cryostat


  //Parameters for the inner Cryostat


  //LogicalVolumes
  G4LogicalVolume* Cryostat_Envelop_log;
  G4LogicalVolume* GXe_Cryostat_TPCEnvelop_log;


  //PhysicalVolumes
	G4VPhysicalVolume* GXe_Cryostat_TPCEnvelop_phys;

  //Visualization
  G4VisAttributes *VacuumVisAtt;
  G4VisAttributes *GXeVisAtt;
  G4VisAttributes *LXeVisAtt;
};

#endif

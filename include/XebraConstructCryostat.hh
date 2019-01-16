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
  G4double Cryostat_Inner_Tube_length;
  G4double Cryostat_Inner_Tube_outerdiameter;
  G4double Cryostat_Inner_Tube_wallthickness;
  G4double Cryostat_Inner_Tube_innerdiameter;
  G4double Cryostat_Inner_BottomPlate_length;
  G4double Cryostat_Inner_BottomPlate_diameter;
  G4double Cryostat_Inner_TubeFlange_length;
  G4double Cryostat_Inner_TubeFlange_innerdiameter;
  G4double Cryostat_Inner_TubeFlange_outerdiameter;
  G4double Cryostat_TPCEnvelop_overhang;
  G4double Cryostat_Inner_UpperTubeFlange_length;
  G4double Cryostat_Inner_UpperTubeFlange_innerdiameter;
  G4double Cryostat_Inner_UpperTubeFlange_outerdiameter;
  G4double Cryostat_Inner_UpperTube_innerdiameter;
  G4double Cryostat_Inner_UpperTube_wallthickness;
  G4double Cryostat_Inner_UpperTube_outerdiameter;
  G4double Cryostat_Inner_MiddlePlate_length;
  G4double Cryostat_Inner_MiddlePlate_innerdiameter;
  G4double Cryostat_Inner_MiddlePlate_outerdiameter;
  G4double Cryostat_Inner_UpperTube_length;
  G4double Cryostat_Inner_UpperFlange_length;
  G4double Cryostat_Inner_UpperFlange_outerdiameter;


  //LogicalVolumes
  G4LogicalVolume* Cryostat_Envelop_log;
  G4LogicalVolume* GXe_Cryostat_TPCEnvelop_log;

  G4LogicalVolume* Cryostat_Inner_SS_BottomPlate_log;
  G4LogicalVolume* Cryostat_Inner_SS_Tube_log;
  G4LogicalVolume* Cryostat_Inner_SS_TubeFlange_log;


  //PhysicalVolumes
	G4VPhysicalVolume* GXe_Cryostat_TPCEnvelop_phys;

  G4VPhysicalVolume* Cryostat_Inner_SS_BottomPlate_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_Tube_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_TubeFlange_phys;

  //Visualization
  G4VisAttributes *VacuumVisAtt;
  G4VisAttributes *GXeVisAtt;
  G4VisAttributes *LXeVisAtt;
};

#endif

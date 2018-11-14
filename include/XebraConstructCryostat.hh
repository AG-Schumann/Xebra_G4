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

   G4UnionSolid * BuildVesselShape( G4double Diameter_cyl, G4double Height_cyl, G4double Thickness_Wall );
   G4SubtractionSolid * BuildFillerShape( G4double Diameter_cyl, G4double Height_cyl, G4double Thickness_Wall );

  void PrintGeometryInformation();

private:

  //Materials
  G4Material *CryostatMaterial;
  G4Material *Vacuum;
  G4Material *LXe;
  G4Material *GXe;


  //Parameters for the Cryostat Envelop
  G4double CryostatEnvelop_Radius;  
  G4double CryostatEnvelop_Height;
  //Parameters for the outer Cryostat
  G4double OuterCryo_WallThickness; 
  G4double OuterCryo_InnerCylDiameter; 
  G4double OuterCryo_InnerCylHeight; 
  G4double OuterCryo_FlangeHeight;
  G4double OuterCryo_FlangeThickness;
  G4double OuterCryo_StiffenerHeight;
  G4double OuterCryo_StiffenerThickness;
  int OuterCryo_StiffenerNumber;
  //Parameters for the inner Cryostat
  G4double InnerCryo_WallThickness; 
  G4double InnerCryo_InnerCylDiameter; 
  G4double InnerCryo_InnerCylHeight; 
  G4double InnerCryo_FlangeHeight;
  G4double InnerCryo_FlangeThickness;
  G4double InnerCryo_StiffenerHeight;
  G4double InnerCryo_StiffenerThickness;
  int InnerCryo_StiffenerNumber;

  //LogicalVolumes
  G4LogicalVolume* CryostatVolume_Logical;
  G4LogicalVolume* OuterCryostatVessel_Logical;
  G4LogicalVolume* OuterCryostatVolume_Logical;

  G4LogicalVolume* InnerCryostatVessel_Logical;
  G4LogicalVolume* InnerCryostatVolume_Logical;
  G4LogicalVolume* InnerCryostatBottomVolume_Logical;
  G4LogicalVolume* InnerCryostatBottomFillerVessel_Logical;
  G4LogicalVolume* InnerCryostatBottomFillerVolume_Logical;
  G4LogicalVolume* InnerCryostatTPCVolume_Logical;

  //PhysicalVolumes
  G4VPhysicalVolume* OuterCryostatVessel_Physical;
  G4VPhysicalVolume* OuterCryostatVolume_Physical;

  G4VPhysicalVolume* InnerCryostatVessel_Physical;
  G4VPhysicalVolume* InnerCryostatVolume_Physical;
  G4VPhysicalVolume* InnerCryostatBottomVolume_Physical;
  G4VPhysicalVolume* InnerCryostatBottomFillerVessel_Physical;
  G4VPhysicalVolume* InnerCryostatBottomFillerVolume_Physical;
  G4VPhysicalVolume* InnerCryostatTPCVolume_Physical;

  //Visualization
  G4VisAttributes *VacuumVisAtt;
  G4VisAttributes *TitaniumVisAtt;
  G4VisAttributes *GXeVisAtt;
  G4VisAttributes *LXeVisAtt;
};

#endif

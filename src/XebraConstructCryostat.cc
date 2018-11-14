#include "XebraConstructCryostat.hh"

//Additional Header Files
#include <globals.hh>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cassert>

using std::vector;
using std::stringstream;
using std::max;

//Root Header Files
#include <TFile.h>
#include <TParameter.h>

//G4 Header Files
#include <G4SystemOfUnits.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Torus.hh>
#include <G4Polyhedra.hh>
#include <G4Polycone.hh>
#include <G4Ellipsoid.hh>
#include <G4ExtrudedSolid.hh>
#include <G4UnionSolid.hh>
#include <G4GenericTrap.hh>
#include <G4SubtractionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4PVParameterised.hh>
#include <G4OpBoundaryProcess.hh>
#include <G4SDManager.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include <G4PhysicalVolumeStore.hh>


XebraConstructCryostat::XebraConstructCryostat( XebraDetectorConstruction *){

    //these values will be used as Cryostat Envelop for the neutron veto
    CryostatEnvelop_Radius = 1.75*m;  
    CryostatEnvelop_Height = 5. *m;

}

XebraConstructCryostat::~XebraConstructCryostat() {;}


G4LogicalVolume* XebraConstructCryostat::Construct(){

//**********************************************OPTION-PARAMETERS**********************************************
    
    CryostatMaterial = G4Material::GetMaterial("TiGrade1");
    //CryostatMaterial = G4Material::GetMaterial("SS304LSteel");
    OuterCryo_StiffenerNumber = 3.;
    InnerCryo_StiffenerNumber = 3.;

//**********************************************LOAD (other) MATERIALS**********************************************

    Vacuum   =  G4Material::GetMaterial("Vacuum");
    LXe = G4Material::GetMaterial("LXe");
    GXe = G4Material::GetMaterial("GXe"); 

//**********************************************DEFINE PARAMETER**********************************************    
//  Option based on NIKHEF prel. XEBRA Cryostat Study (July18) - [BucklingSafetyFactor: 3]
    if (CryostatMaterial == G4Material::GetMaterial("TiGrade1"))
	{if (OuterCryo_StiffenerNumber == 0.) {OuterCryo_WallThickness = 18.5 *mm;}
	 if (OuterCryo_StiffenerNumber == 1.) {OuterCryo_WallThickness = 14.0 *mm;}
	 if (OuterCryo_StiffenerNumber == 2.) {OuterCryo_WallThickness = 12.0 *mm;}
	 if (OuterCryo_StiffenerNumber == 3.) {OuterCryo_WallThickness = 10.5 *mm;}
	 if (InnerCryo_StiffenerNumber == 0.) {InnerCryo_WallThickness = 12.5 *mm;}
	 if (InnerCryo_StiffenerNumber == 1.) {InnerCryo_WallThickness = 9.5 *mm;}
	 if (InnerCryo_StiffenerNumber == 2.) {InnerCryo_WallThickness = 8.5 *mm;}
	 if (InnerCryo_StiffenerNumber == 3.) {InnerCryo_WallThickness = 7.5 *mm;}
	 }
    if (CryostatMaterial == G4Material::GetMaterial("SS304LSteel"))
	{if (OuterCryo_StiffenerNumber == 0.) {OuterCryo_WallThickness = 15.5 *mm;}
	 if (OuterCryo_StiffenerNumber == 1.) {OuterCryo_WallThickness = 11.5 *mm;}
	 if (OuterCryo_StiffenerNumber == 2.) {OuterCryo_WallThickness = 10.0 *mm;}
	 if (OuterCryo_StiffenerNumber == 3.) {OuterCryo_WallThickness = 9.0 *mm;}
	 if (InnerCryo_StiffenerNumber == 0.) {InnerCryo_WallThickness = 10.5 *mm;}
	 if (InnerCryo_StiffenerNumber == 1.) {InnerCryo_WallThickness = 8.0 *mm;}
	 if (InnerCryo_StiffenerNumber == 2.) {InnerCryo_WallThickness = 6.5 *mm;}
	 if (InnerCryo_StiffenerNumber == 3.) {InnerCryo_WallThickness = 6.0 *mm;}
	 }

    // Common Parameter used to build the Outer Cryostat
    OuterCryo_InnerCylDiameter = 3.0*m; 
    OuterCryo_InnerCylHeight = 3.6 *m; 
    OuterCryo_FlangeHeight = 120.0 *mm;
    OuterCryo_FlangeThickness = 120.0 *mm;
    OuterCryo_StiffenerHeight = 8.0 *mm;
    OuterCryo_StiffenerThickness = 80.0 *mm;

    // Common Parameter used to build the Inner Cryostat
    InnerCryo_InnerCylDiameter = 2.8*m; 
    InnerCryo_InnerCylHeight = 3.2 *m; 
    InnerCryo_FlangeHeight = 150.0 *mm;
    InnerCryo_FlangeThickness = 60.0 *mm;
    InnerCryo_StiffenerHeight = 30.0 *mm;
    InnerCryo_StiffenerThickness = 60.0 *mm;


//**********************************************CONSTRUCTION**********************************************

   // Constuct the outer Cryostat as solidly filled object: Top Torispheric, Cylinder, Bottom Torispheric, Flange, # of Hoop stiffener --> Solidunion OuterCryo		
   G4UnionSolid *OuterCryostatVessel_Solid = BuildVesselShape( OuterCryo_InnerCylDiameter, OuterCryo_InnerCylHeight, OuterCryo_WallThickness);
  
   G4Tubs *OuterCryostatFlange = new G4Tubs("OuterCryostatFlange", OuterCryo_InnerCylDiameter/2, 
   					OuterCryo_InnerCylDiameter/2 + OuterCryo_WallThickness + OuterCryo_FlangeThickness, OuterCryo_FlangeHeight/2 , 0.*deg, 360.*deg);
   OuterCryostatVessel_Solid = new G4UnionSolid("OuterCryostat", OuterCryostatVessel_Solid, OuterCryostatFlange, 0, G4ThreeVector(0.,0.,OuterCryo_InnerCylHeight/2-OuterCryo_FlangeHeight/2));
   G4Tubs *OuterCryostatStiffener = new G4Tubs("OuterCryostatStiffener", OuterCryo_InnerCylDiameter/2, 
   					OuterCryo_InnerCylDiameter/2 + OuterCryo_WallThickness + OuterCryo_StiffenerThickness, OuterCryo_StiffenerHeight/2 , 0.*deg, 360.*deg);   
   for (int a=0; a < OuterCryo_StiffenerNumber; ++a)
    {  
      G4double OuterCryoStiffener_ZStep = OuterCryo_InnerCylHeight/(OuterCryo_StiffenerNumber+1);
      OuterCryostatVessel_Solid = new G4UnionSolid("OuterCryostat", OuterCryostatVessel_Solid, OuterCryostatStiffener, 0, 
					    G4ThreeVector(0.,0.,-OuterCryo_InnerCylHeight/2 + (a+1) * OuterCryoStiffener_ZStep - OuterCryo_StiffenerHeight/2));
    }

   CryostatVolume_Logical = new G4LogicalVolume(OuterCryostatVessel_Solid, Vacuum, "OuterCryostat", 0, 0, 0);

   OuterCryostatVessel_Logical = new G4LogicalVolume(OuterCryostatVessel_Solid, CryostatMaterial, "OuterCryostatVessel", 0, 0, 0);
   OuterCryostatVessel_Physical = new G4PVPlacement(0, G4ThreeVector(),   OuterCryostatVessel_Logical,"CryoMat_OuterCryostatVessel", CryostatVolume_Logical, false, 0);

  // Constuct Vacuum in the Outer Cryostat, leaving the Cryostat Vessel as a shell of given thickness		
   G4UnionSolid *OuterCryostatVolume_Solid = BuildVesselShape( OuterCryo_InnerCylDiameter, OuterCryo_InnerCylHeight, 0.);
   OuterCryostatVolume_Logical = new G4LogicalVolume(OuterCryostatVolume_Solid, Vacuum, "OuterCryostatVolume", 0, 0, 0);
   OuterCryostatVolume_Physical = new G4PVPlacement(0, G4ThreeVector(), OuterCryostatVolume_Logical,"Vacuum_OuterCryostatVolume",  OuterCryostatVessel_Logical, false, 0);

  // Construct inner Cryostat as solidly filled object: Top Torispheric, Cylinder, Bottom Torispheric, Flange, # of Hoop stiffener --> Solidunion InnerCryo
   G4UnionSolid *InnerCryostatVessel_Solid = BuildVesselShape( InnerCryo_InnerCylDiameter, InnerCryo_InnerCylHeight, InnerCryo_WallThickness);
  
   G4Tubs *InnerCryostatFlange = new G4Tubs("InnerCryostatFlange", InnerCryo_InnerCylDiameter/2, 
   					InnerCryo_InnerCylDiameter/2 + InnerCryo_WallThickness + InnerCryo_FlangeThickness, InnerCryo_FlangeHeight/2 , 0.*deg, 360.*deg);
   InnerCryostatVessel_Solid = new G4UnionSolid("InnerCryostat", InnerCryostatVessel_Solid, InnerCryostatFlange, 0, G4ThreeVector(0.,0.,InnerCryo_InnerCylHeight/2-InnerCryo_FlangeHeight/2));
   G4Tubs *InnerCryostatStiffener = new G4Tubs("InnerCryostatStiffener", InnerCryo_InnerCylDiameter/2, 
   					InnerCryo_InnerCylDiameter/2 + InnerCryo_WallThickness + InnerCryo_StiffenerThickness, InnerCryo_StiffenerHeight/2 , 0.*deg, 360.*deg);   
   for (int a=0; a < InnerCryo_StiffenerNumber; ++a)
    {  
      G4double InnerCryoStiffener_ZStep = InnerCryo_InnerCylHeight/(InnerCryo_StiffenerNumber+1);
      InnerCryostatVessel_Solid = new G4UnionSolid("InnerCryostat", InnerCryostatVessel_Solid, InnerCryostatStiffener, 0, 
					    G4ThreeVector(0.,0.,-InnerCryo_InnerCylHeight/2 + (a+1) * InnerCryoStiffener_ZStep - InnerCryo_StiffenerHeight/2));
    }

   InnerCryostatVessel_Logical = new G4LogicalVolume(InnerCryostatVessel_Solid, CryostatMaterial, "InnerCryostatVessel", 0, 0, 0);
   InnerCryostatVessel_Physical = new G4PVPlacement(0, G4ThreeVector(), InnerCryostatVessel_Logical,"CryoMat_InnerCryostatVessel", OuterCryostatVolume_Logical, false, 0);
 
  // Construct GXe in the Inner Cryostat, leaving the Inner Cryostat Vessel as a shell of given thickness		
   G4UnionSolid *InnerCryostatVolume_Solid = BuildVesselShape( InnerCryo_InnerCylDiameter, InnerCryo_InnerCylHeight, 0.);
   InnerCryostatVolume_Logical = new G4LogicalVolume(InnerCryostatVolume_Solid, GXe, "InnerCryostatVolume", 0, 0, 0);
   InnerCryostatVolume_Physical = new G4PVPlacement(0, G4ThreeVector(), InnerCryostatVolume_Logical,"GXe_InnerCryostatVolume",  InnerCryostatVessel_Logical, false, 0);


  // Construct the (vacuumized) Bottom filler: Fill Bottom with LXe, Construct CryoMaterial Filler, Replace inner material with Vacuum	
   G4SubtractionSolid *InnerCryostatBottomVolume_Solid = BuildFillerShape( InnerCryo_InnerCylDiameter, InnerCryo_InnerCylHeight, 0.);
   InnerCryostatBottomVolume_Logical = new G4LogicalVolume(InnerCryostatBottomVolume_Solid, LXe, "InnerCryostatBottomVolume", 0, 0, 0);
   InnerCryostatBottomVolume_Physical = new G4PVPlacement(0, G4ThreeVector(), InnerCryostatBottomVolume_Logical,"LXe_InnerCryostatBottomVolume",  InnerCryostatVolume_Logical, false, 0);

   G4SubtractionSolid *InnerCryostatBottomFillerVessel_Solid = BuildFillerShape( InnerCryo_InnerCylDiameter, InnerCryo_InnerCylHeight, - InnerCryo_WallThickness);
   InnerCryostatBottomFillerVessel_Logical = new G4LogicalVolume(InnerCryostatBottomFillerVessel_Solid, CryostatMaterial, "InnerCryostatBottomFillerVessel", 0, 0, 0);
   InnerCryostatBottomFillerVessel_Physical = new G4PVPlacement(0, G4ThreeVector(), InnerCryostatBottomFillerVessel_Logical,"CryoMat_InnerCryostatBottomFillerVessel",  InnerCryostatBottomVolume_Logical, false, 0);

   G4SubtractionSolid *InnerCryostatBottomFillerVolume_Solid = BuildFillerShape( InnerCryo_InnerCylDiameter, InnerCryo_InnerCylHeight, - InnerCryo_WallThickness - 5. *mm);
   InnerCryostatBottomFillerVolume_Logical = new G4LogicalVolume(InnerCryostatBottomFillerVolume_Solid, Vacuum, "InnerCryostatBottomFillerVolume", 0, 0, 0);
   InnerCryostatBottomFillerVolume_Physical = new G4PVPlacement(0, G4ThreeVector(), InnerCryostatBottomFillerVolume_Logical,"Vacuum_InnerCryostatBottomFillerVolume",  InnerCryostatBottomFillerVessel_Logical, false, 0);


//**********************************************VISUALIZATION**********************************************

    // Visualization Settings for the Vacuum Cryostat
    G4Colour VacuumColor(0.500, 0., 0., 0.7);
    VacuumVisAtt = new G4VisAttributes(VacuumColor);
    VacuumVisAtt->SetVisibility(false);
    OuterCryostatVolume_Logical->SetVisAttributes(VacuumVisAtt);
    InnerCryostatBottomFillerVolume_Logical->SetVisAttributes(VacuumVisAtt);
    
    // Visualization Settings
    G4Colour TitaniumColor(0.500, 0.500, 0.500, 1.);
    TitaniumVisAtt = new G4VisAttributes(TitaniumColor);
    TitaniumVisAtt->SetVisibility(true);
    OuterCryostatVessel_Logical->SetVisAttributes(TitaniumVisAtt);
    InnerCryostatVessel_Logical->SetVisAttributes(TitaniumVisAtt);
    InnerCryostatBottomFillerVessel_Logical->SetVisAttributes(TitaniumVisAtt);

   // Visualization Settings : LXe
   G4Colour LXeColor(0.,1.,0.);
   LXeVisAtt = new G4VisAttributes(LXeColor);
   LXeVisAtt->SetVisibility(true);
   InnerCryostatBottomVolume_Logical->SetVisAttributes(LXeVisAtt); 
   
   // Visualization Settings : GXe
   G4Colour GXeColor(1.,0.,0.);
   GXeVisAtt = new G4VisAttributes(GXeColor);
   GXeVisAtt->SetVisibility(true);
   InnerCryostatVolume_Logical->SetVisAttributes(GXeVisAtt); 


//**********************************************RETURN**********************************************    

  return CryostatVolume_Logical;
}


G4double XebraConstructCryostat::GetOuterRadiusCryostat(){
  return this->CryostatEnvelop_Radius;
}

G4double XebraConstructCryostat::GetOuterHeightCryostat(){
  return this->CryostatEnvelop_Height;
}


G4LogicalVolume* XebraConstructCryostat::GetMotherVolume(){
  return this->InnerCryostatVolume_Logical;
}


void XebraConstructCryostat::PrintGeometryInformation()
{
//================================== CRYOSTAT VESSEL MASSES =========================================================
  const G4double OuterCryostatMass = OuterCryostatVessel_Logical->GetMass(false, false)/kg;
  const G4double OuterCryostatVolume = OuterCryostatMass/(CryostatMaterial->GetDensity()*m3/kg);  
  G4cout << "OuterCryostatVessel:                     " << OuterCryostatMass << " kg " << "     =============    " << OuterCryostatVolume << " m3 " << G4endl;

  const G4double InnerCryostatMass = InnerCryostatVessel_Logical->GetMass(false, false)/kg;
  const G4double InnerCryostatVolume = InnerCryostatMass/(CryostatMaterial->GetDensity()*m3/kg);  
  G4cout << "InnerCryostatVessel:                     " << InnerCryostatMass << " kg " << "     =============    " << InnerCryostatVolume << " m3 " << G4endl;

  const G4double InnerCryostatBottomFillerMass = InnerCryostatBottomFillerVessel_Logical->GetMass(false, false)/kg;
  const G4double InnerCryostatBottomFillerVolume = InnerCryostatBottomFillerMass/(CryostatMaterial->GetDensity()*m3/kg);  
  G4cout << "InnerCryostatBottomFillerVessel:         " << InnerCryostatBottomFillerMass << " kg " << "     =============    " << InnerCryostatBottomFillerVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

//================================== XENON MASSES  =========================================================
  const G4double LXeMass = InnerCryostatBottomVolume_Logical->GetMass(false, false)/kg;
  const G4double LXeVolume = LXeMass/(LXe->GetDensity()*m3/kg);  
  G4cout << "Liquid Xenon around BottomFiller:        " << LXeMass << " kg " << "     =============    " << LXeVolume << " m3 " << G4endl;

  const G4double GXeMass = InnerCryostatVolume_Logical->GetMass(false, false)/kg;
  const G4double GXeVolume = GXeMass/(LXe->GetDensity()*m3/kg);  
  G4cout << "Gaseous Xenon in TopDome:                " << GXeMass << " kg " << "     =============    " << GXeVolume << " m3 " << G4endl;
  G4cout << "============================================================================================= " << G4endl;

}




G4UnionSolid * XebraConstructCryostat::BuildVesselShape( G4double Diameter_cyl, G4double Height_cyl, G4double Thickness_Wall )
{

    // ConstructVessel: construction of a cylindrical shape with two DIN 28011 (no Straight Flange componentent; SF=0) torispheric domes 
    //                  
    // Input: Diameter_cyl = cylinder inner diameter ###   Height_cyl = cylinder length of the vessel ###   Thickness_Wall = Wall thickness of the cylinder & minimal thickness of the dome walls
    
    // Derive parameter
    G4double R_cyl = Diameter_cyl/2;	// inner radius of the cylinder
    G4double R0 = Diameter_cyl; 	// sphere inner radius (DIN 28011)
    G4double R1 = 0.1 * R0;		// toroid radius(DIN 28011)
    G4double rc0 = R_cyl-R1;
    G4double dR0 = R0-R1;
    G4double dTheta = asin(rc0/dR0);
    G4double dZ     = sqrt(dR0*dR0 - rc0*rc0);

    // Build Cylinder Body, Bottom Sphere & Torus, Top Sphere & Torus
    G4Tubs   *pCyl     = new G4Tubs("CylinderBody", 0. *cm, Diameter_cyl/2 + Thickness_Wall, Height_cyl/2 , 0.*deg, 360.*deg);

    G4Sphere *pBottom1 = new G4Sphere("Bottom1", 0.1 *mm, R0 + Thickness_Wall , 0., 2*M_PI, M_PI-dTheta, dTheta );
    G4Torus  *pBottom2 = new G4Torus("Bottom2",0.1 *mm, R1 + Thickness_Wall, rc0, 0., 2*M_PI);
         
    G4Sphere *pTop1    = new G4Sphere("Top1", 0.1 *mm, R0 + Thickness_Wall, 0., 2*M_PI, 0., dTheta );
    G4Torus  *pTop2    = new G4Torus("Top2",0.1 *mm, R1 + Thickness_Wall, rc0, 0., 2*M_PI);
    
    // Make one solid by combining the vessel components
    G4UnionSolid *pVessel;
    pVessel = new G4UnionSolid("UnionSolid", pCyl, pTop1, 0, G4ThreeVector(0.,0.,Height_cyl/2 - dZ));
    pVessel = new G4UnionSolid("UnionSolid", pVessel, pBottom1, 0, G4ThreeVector(0.,0.,-Height_cyl/2  + dZ));
    pVessel = new G4UnionSolid("UnionSolid", pVessel, pTop2, 0, G4ThreeVector(0.,0.,Height_cyl/2 ));
    pVessel = new G4UnionSolid("UnionSolid", pVessel, pBottom2, 0, G4ThreeVector(0.,0.,-Height_cyl/2 ));

    return pVessel;
}

G4SubtractionSolid * XebraConstructCryostat::BuildFillerShape( G4double Diameter_cyl, G4double Height_cyl, G4double Thickness_Wall )
{

    // ConstructFillerShape: construction of the filler volume, being placed in the bottom torispheric dome
    // Input: Diameter_cyl = cylinder inner diameter ### Height_cyl = cylinder length of the Cryosstat vessel ###  Thickness_Wall = minimal thickness of the vessel
    
    // Derive parameter
    G4double R_cyl = Diameter_cyl/2;	
    G4double R0 = Diameter_cyl; 	
    G4double R1 = 0.1 * R0;		
    G4double rc0 = R_cyl-R1;
    G4double dR0 = R0-R1;
    G4double dTheta = asin(rc0/dR0);
    G4double dZ     = sqrt(dR0*dR0 - rc0*rc0);

    // Build Cylinder Body, Bottom Sphere & Torus, Top Sphere & Torus
    G4Tubs   *pCyl     = new G4Tubs("CylinderBody", 0. *cm, Diameter_cyl/2 + Thickness_Wall, Height_cyl/2 - Thickness_Wall, 0.*deg, 360.*deg);
    G4Sphere *pBottom1 = new G4Sphere("Bottom1", 0.1 *mm, R0 + Thickness_Wall , 0., 2*M_PI, M_PI-dTheta, dTheta );
    G4Torus  *pBottom2 = new G4Torus("Bottom2",0.1 *mm, R1 + Thickness_Wall, rc0, 0., 2*M_PI);

    // Make one solid by combining the vessel components
    G4UnionSolid *pFiller;
    G4SubtractionSolid *pFiller2;
    pFiller = new G4UnionSolid("UnionSolid", pCyl, pBottom1, 0, G4ThreeVector(0.,0.,-Height_cyl/2  + dZ));
    pFiller = new G4UnionSolid("UnionSolid", pFiller, pBottom2, 0, G4ThreeVector(0.,0.,-Height_cyl/2 ));
    pFiller2 = new G4SubtractionSolid("SubtractionSolid", pFiller, pCyl, 0, G4ThreeVector(0.,0.,0.));

    return pFiller2;
}




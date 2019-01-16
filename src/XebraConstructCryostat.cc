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

    // these values will be used as Cryostat Envelop for the air voulume preliminarily containing the cryostats 
		// ToDo: change, also adjust mother volumes
    Cryostat_Envelop_Radius = 1.*m;  
    Cryostat_Envelop_Height = 2.5*m;

}

XebraConstructCryostat::~XebraConstructCryostat() {;}


G4LogicalVolume* XebraConstructCryostat::Construct(){

//**********************************************MATERIALS**********************************************

	//G4Material* Vacuum   =  G4Material::GetMaterial("Vacuum");
	//G4Material* LXe = G4Material::GetMaterial("LXe");
	//G4Material* GXe = G4Material::GetMaterial("GXe"); 
	G4Material* Air = G4Material::GetMaterial("Air");

//**********************************************DEFINE PARAMETER**********************************************    

	// Common Parameters used to build the Outer Cryostat

	// Common Parameters used to build the Inner Cryostat


//**********************************************CONSTRUCTION**********************************************

	//**************************************************
	// Cryostat Envelop
	//**************************************************

	G4Tubs* Cryostat_Envelop_solid = new G4Tubs("Cryostat_Envelop_solid", 0., Cryostat_Envelop_Radius, Cryostat_Envelop_Height/2 , 0.*deg, 360.*deg);

	Cryostat_Envelop_log = new G4LogicalVolume(Cryostat_Envelop_solid, Air, "Cryostat_Envelop_log", 0, 0, 0);


	//**************************************************
	// Outer Cryostat
	//**************************************************



	//**************************************************
	// Inner Cryostat
	//**************************************************

	// Cryostat_Inner_SS_...



//**********************************************VISUALIZATION**********************************************

	// Visualization Settings for the Vacuum Cryostat
  G4Colour VacuumColor(0.500, 0., 0., 0.7);
  VacuumVisAtt = new G4VisAttributes(VacuumColor);
  VacuumVisAtt->SetVisibility(false);

	// Visualization Settings : LXe
	G4Colour LXeColor(0.,1.,0.);
	LXeVisAtt = new G4VisAttributes(LXeColor);
	LXeVisAtt->SetVisibility(true);

	// Visualization Settings : GXe
	G4Colour GXeColor(1.,0.,0.);
	GXeVisAtt = new G4VisAttributes(GXeColor);
	GXeVisAtt->SetVisibility(true);


//**********************************************RETURN**********************************************    

  return Cryostat_Envelop_log; // ToDo: change
}


G4double XebraConstructCryostat::GetOuterRadiusCryostat(){
  return this->Cryostat_Envelop_Radius;
}

G4double XebraConstructCryostat::GetOuterHeightCryostat(){
  return this->Cryostat_Envelop_Height;
}


G4LogicalVolume* XebraConstructCryostat::GetMotherVolume(){
  return this->Cryostat_Envelop_log; //ToDo: change!!!
}



void XebraConstructCryostat::PrintGeometryInformation()
{
/*
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
*/

}


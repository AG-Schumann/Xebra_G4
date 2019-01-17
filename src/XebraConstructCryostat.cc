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

  // Parameters for the Cryostat Envelop
	// these values will be used as Cryostat Envelop for the air voulume preliminarily containing the cryostats 
	// ToDo: change, also adjust mother volumes
	Cryostat_Envelop_Radius = 1.*m;  
	Cryostat_Envelop_Height = 2.5*m;

}

XebraConstructCryostat::~XebraConstructCryostat() {;}

//ToDo: finish constrction cryos also with details

G4LogicalVolume* XebraConstructCryostat::Construct(){

//**********************************************MATERIALS**********************************************

	//G4Material* Vacuum   =  G4Material::GetMaterial("Vacuum");
	G4Material* SS304LSteel = G4Material::GetMaterial("SS304LSteel");
	G4Material* GXe = G4Material::GetMaterial("GXe"); 
	G4Material* Air = G4Material::GetMaterial("G4_AIR");;

//**********************************************DEFINE PARAMETER**********************************************    

	//**************************************************
	// Common Parameters used for the TPC Envelop
	//**************************************************

	Cryostat_TPCEnvelop_Radius = 0.15*m / 2; //ToDo: implement directly from TPC class
	Cryostat_TPCEnvelop_Height = 0.4*m;
	// Cryostat_TPCEnvelop_overhang see below

	//**************************************************
	// Common Parameters used to build the Outer Cryostat
	//**************************************************

		//ToDo: add outer cryostat, sample tube and vacuum

	//**************************************************
	// Common Parameters used to build the Inner Cryostat
	//**************************************************

		// lower part (NW 150 CF)

	Cryostat_Inner_Tube_outerdiameter = 154.*mm; // from Hositrad and order
	Cryostat_Inner_Tube_wallthickness = 2.*mm;  // from Hositrad and order
	Cryostat_Inner_Tube_innerdiameter = 150.*mm; // from Hositrad and order
	// Cryostat_Inner_Tube_length see below

	Cryostat_Inner_TubeFlange_length = 22.3*mm; // from CF Flange components data sheet for NW 150 CF
	Cryostat_Inner_TubeFlange_innerdiameter = Cryostat_Inner_Tube_innerdiameter;
	Cryostat_Inner_TubeFlange_outerdiameter = 203.*mm; // from CF Flange components data sheet for NW 150 CF, ToDo: check ambiguity

	Cryostat_Inner_BottomPlate_length = 10.*mm; // from order
	Cryostat_Inner_BottomPlate_diameter = Cryostat_Inner_Tube_outerdiameter;

	Cryostat_Inner_Tube_length = 380.*mm - Cryostat_Inner_BottomPlate_length - Cryostat_Inner_TubeFlange_length; // from order and thesis Basho

		// upper part (NW 250 CF)

	Cryostat_Inner_UpperTube_innerdiameter = 250.*mm; // from CF Flange components data sheet for NW 250 CF //ToDo:check
	Cryostat_Inner_UpperTube_wallthickness = 2.*mm; // from CF Flange components data sheet for NW 250 CF //ToDo:check
	Cryostat_Inner_UpperTube_outerdiameter = 254.*mm; // from CF Flange components data sheet for NW 250 CF //ToDo:check
	// Cryostat_Inner_UpperTube_length see below
	
	Cryostat_Inner_UpperTubeFlange_length = 26.*mm; // from CF Flange components data sheet for NW 250 CF and measurement
	Cryostat_Inner_UpperTubeFlange_innerdiameter = Cryostat_Inner_UpperTube_innerdiameter;
	Cryostat_Inner_UpperTubeFlange_outerdiameter = 304.*mm; // from CF Flange components data sheet for NW 250 CF, ToDo: check ambiguity

	Cryostat_Inner_MiddlePlate_length = 22.3*mm; //rough measurement, taken from CF Flange components data sheet for NW 150 CF, ToDo: check!!!
	Cryostat_Inner_MiddlePlate_innerdiameter = Cryostat_Inner_Tube_innerdiameter;
	Cryostat_Inner_MiddlePlate_outerdiameter = Cryostat_Inner_UpperTube_outerdiameter;

	Cryostat_Inner_UpperTube_length = 74.3*mm - Cryostat_Inner_MiddlePlate_length; //rough measurement, ToDo: check!!!

		//Temporary top part, ToDo: ckeck!!!

	Cryostat_Inner_TopFlange1_length = Cryostat_Inner_UpperTubeFlange_length;
	Cryostat_Inner_TopFlange1_outerdiameter = Cryostat_Inner_UpperTubeFlange_outerdiameter;
	Cryostat_Inner_TopFlange1_innerdiameter = 152.4*mm;  // from CF Flange components data sheet for NW 250 CF > NW 150 CF Zero Length Reducer

	Cryostat_Inner_TopFlange2_length = 22.3*mm; // from CF Flange components data sheet for NW 150 CF
	Cryostat_Inner_TopFlange2_outerdiameter = 203.*mm; // from CF Flange components data sheet for NW 150 CF, ToDo: check ambiguity
	Cryostat_Inner_TopFlange2_innerdiameter = 0.;
	
		// GXe volume

	Cryostat_TPCEnvelop_overhang = 0.4*m - (Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length);


	//ToDo: use to potentially cut or expand GXe volume
	//ToDo: add closing flange(s?) and GXe volume
	// To Do: gaps due to copper gaskets?, add details such as KF40 flanges, screw bolts,...



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
	// TPC Envelop
	//**************************************************

	Cryostat_Inner_MotherLogicalVolume = Cryostat_Envelop_log;

	G4Tubs* GXe_Cryostat_TPCEnvelop_solid = new G4Tubs("GXe_Cryostat_TPCEnvelop_solid", 0., Cryostat_TPCEnvelop_Radius, Cryostat_TPCEnvelop_Height/2 , 0.*deg, 360.*deg);

	GXe_Cryostat_TPCEnvelop_log = new G4LogicalVolume(GXe_Cryostat_TPCEnvelop_solid, GXe, "GXe_Cryostat_TPCEnvelop_log", 0, 0, 0);

	GXe_Cryostat_TPCEnvelop_phys = new G4PVPlacement(0, G4ThreeVector(), GXe_Cryostat_TPCEnvelop_log, "GXe_Cryostat_TPCEnvelop",  Cryostat_Inner_MotherLogicalVolume, false, 0);

	//**************************************************
	// Inner Cryostat
	//**************************************************

	// Bottom Plate
	G4Tubs* Cryostat_Inner_SS_BottomPlate_solid = new G4Tubs("Cryostat_Inner_SS_BottomPlate_solid", 0., Cryostat_Inner_BottomPlate_diameter/2, Cryostat_Inner_BottomPlate_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_BottomPlate_log = new G4LogicalVolume(Cryostat_Inner_SS_BottomPlate_solid, SS304LSteel, "Cryostat_Inner_SS_BottomPlate_log");

	Cryostat_Inner_SS_BottomPlate_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 - Cryostat_Inner_BottomPlate_length/2), Cryostat_Inner_SS_BottomPlate_log,"Cryostat_Inner_SS_BottomPlate", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Tube
	G4Tubs* Cryostat_Inner_SS_Tube_solid = new G4Tubs("Cryostat_Inner_SS_Tube_solid", Cryostat_Inner_Tube_innerdiameter/2, Cryostat_Inner_Tube_outerdiameter/2, Cryostat_Inner_Tube_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_Tube_log = new G4LogicalVolume(Cryostat_Inner_SS_Tube_solid, SS304LSteel, "Cryostat_Inner_SS_Tube_log");

	Cryostat_Inner_SS_Tube_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length/2), Cryostat_Inner_SS_Tube_log,"Cryostat_Inner_SS_Tube", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Tube Flange
	G4Tubs* Cryostat_Inner_SS_TubeFlange_solid = new G4Tubs("Cryostat_Inner_SS_TubeFlange_solid", Cryostat_Inner_TubeFlange_innerdiameter/2, Cryostat_Inner_TubeFlange_outerdiameter/2, Cryostat_Inner_TubeFlange_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_TubeFlange_log = new G4LogicalVolume(Cryostat_Inner_SS_TubeFlange_solid, SS304LSteel, "Cryostat_Inner_SS_TubeFlange_log");

	Cryostat_Inner_SS_TubeFlange_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length/2), Cryostat_Inner_SS_TubeFlange_log,"Cryostat_Inner_SS_TubeFlange", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Middle Plate
	G4Tubs* Cryostat_Inner_SS_MiddlePlate_solid = new G4Tubs("Cryostat_Inner_SS_MiddlePlate_solid", Cryostat_Inner_MiddlePlate_innerdiameter/2, Cryostat_Inner_MiddlePlate_outerdiameter/2, Cryostat_Inner_MiddlePlate_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_MiddlePlate_log = new G4LogicalVolume(Cryostat_Inner_SS_MiddlePlate_solid, SS304LSteel, "Cryostat_Inner_SS_MiddlePlate_log");

	Cryostat_Inner_SS_MiddlePlate_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length/2), Cryostat_Inner_SS_MiddlePlate_log,"Cryostat_Inner_SS_MiddlePlate", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Upper Tube
	G4Tubs* Cryostat_Inner_SS_UpperTube_solid = new G4Tubs("Cryostat_Inner_SS_UpperTube_solid", Cryostat_Inner_UpperTube_innerdiameter/2, Cryostat_Inner_UpperTube_outerdiameter/2, Cryostat_Inner_UpperTube_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_UpperTube_log = new G4LogicalVolume(Cryostat_Inner_SS_UpperTube_solid, SS304LSteel, "Cryostat_Inner_SS_UpperTube_log");

	Cryostat_Inner_SS_UpperTube_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length/2), Cryostat_Inner_SS_UpperTube_log,"Cryostat_Inner_SS_UpperTube", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Upper Tube Flange
	G4Tubs* Cryostat_Inner_SS_UpperTubeFlange_solid = new G4Tubs("Cryostat_Inner_SS_UpperTubeFlange_solid", Cryostat_Inner_UpperTubeFlange_innerdiameter/2, Cryostat_Inner_UpperTubeFlange_outerdiameter/2, Cryostat_Inner_UpperTubeFlange_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_UpperTubeFlange_log = new G4LogicalVolume(Cryostat_Inner_SS_UpperTubeFlange_solid, SS304LSteel, "Cryostat_Inner_SS_UpperTubeFlange_log");

	Cryostat_Inner_SS_UpperTubeFlange_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length/2), Cryostat_Inner_SS_UpperTubeFlange_log,"Cryostat_Inner_SS_UpperTubeFlange", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Top Flange 1
	G4Tubs* Cryostat_Inner_SS_TopFlange1_solid = new G4Tubs("Cryostat_Inner_SS_TopFlange1_solid", Cryostat_Inner_TopFlange1_innerdiameter/2, Cryostat_Inner_TopFlange1_outerdiameter/2, Cryostat_Inner_TopFlange1_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_TopFlange1_log = new G4LogicalVolume(Cryostat_Inner_SS_TopFlange1_solid, SS304LSteel, "Cryostat_Inner_SS_TopFlange1_log");

	Cryostat_Inner_SS_TopFlange1_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length + Cryostat_Inner_TopFlange1_length/2), Cryostat_Inner_SS_TopFlange1_log,"Cryostat_Inner_SS_TopFlange1", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Top Flange 2 (the upper closing one)
	G4Tubs* Cryostat_Inner_SS_TopFlange2_solid = new G4Tubs("Cryostat_Inner_SS_TopFlange2_solid", Cryostat_Inner_TopFlange2_innerdiameter/2, Cryostat_Inner_TopFlange2_outerdiameter/2, Cryostat_Inner_TopFlange2_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_TopFlange2_log = new G4LogicalVolume(Cryostat_Inner_SS_TopFlange2_solid, SS304LSteel, "Cryostat_Inner_SS_TopFlange2_log");

	Cryostat_Inner_SS_TopFlange2_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length + Cryostat_Inner_TopFlange1_length + Cryostat_Inner_TopFlange2_length/2), Cryostat_Inner_SS_TopFlange2_log,"Cryostat_Inner_SS_TopFlange2", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	//**************************************************
	// Extra GXe volumes
	//**************************************************



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
  return this->GXe_Cryostat_TPCEnvelop_log;
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


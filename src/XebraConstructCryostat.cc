#include "XebraConstructCryostat.hh"
#include "XebraConstructTPC.hh"

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

	Vacuum   =  G4Material::GetMaterial("Vacuum");
	SS304LSteel = G4Material::GetMaterial("SS304LSteel");
	GXe = G4Material::GetMaterial("GXe"); 
	Air = G4Material::GetMaterial("G4_AIR");
	Aluminium = G4Material::GetMaterial("Aluminium");

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
 
	Cryostat_Outer_Tube_length = 130.*cm; // temporary dimension from thesis Basho, ToDo: correct!
	Cryostat_Outer_Tube_wallthickness = 1.*cm; // guessed temporary dimension, ToDo: correct!
	Cryostat_Outer_Tube_innerdiameter = 48.*cm; // temporary dimension from thesis Basho, ToDo: correct!
	Cryostat_Outer_Tube_outerdiameter = 48.*cm + 2*Cryostat_Outer_Tube_wallthickness;

	Cryostat_Outer_TubeFlange_length = 2.*cm; // roughly measured temporary dimension, ToDo: correct!
	Cryostat_Outer_TubeFlange_innerdiameter = Cryostat_Outer_Tube_outerdiameter; // guessed temporary dimension, ToDo: correct!
	Cryostat_Outer_TubeFlange_outerdiameter = Cryostat_Outer_Tube_outerdiameter + 2*3.*cm; // roughly measured temporary dimension, ToDo: correct!

	Cryostat_Outer_BottomPlate_length = 1.*cm; // roughly measured temporary dimension, ToDo: correct!
	Cryostat_Outer_BottomPlate_diameter = Cryostat_Outer_Tube_outerdiameter;

	Cryostat_Outer_TopFlange_length = 2.3*cm; // roughly measured temporary dimension, ToDo: correct!
	Cryostat_Outer_TopFlange_outerdiameter = Cryostat_Outer_TubeFlange_outerdiameter; // guessed temporary dimension, ToDo: correct!
	Cryostat_Outer_TopFlange_innerdiameter = 0.;


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

	Cryostat_Inner_MiddlePlate_length = 16.*mm; //rough measurement
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

	Cryostat_TPCEnvelop_overhang = 0.4*m - (Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length); // 7.7 mm

	//**************************************************
	// Position shift inner in outer cryo
	//**************************************************

	// ToDo: shift inner cryostat and adjust coordinate system accordingly
	Cryostat_Inner_upperedge_unshifted = -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length + Cryostat_Inner_TopFlange1_length + Cryostat_Inner_TopFlange2_length;
	Cryostat_Outer_TopFlange_loweredge_unshifted = Cryostat_Outer_Tube_length/2; // + Cryostat_Outer_TopFlange_length
	Cryostats_dist_unshifted = Cryostat_Outer_TopFlange_loweredge_unshifted - Cryostat_Inner_upperedge_unshifted;
	Cryostats_dist_real = 21.*cm; // rough measurement
	Cryostat_Inner_offset = Cryostats_dist_unshifted - Cryostats_dist_real;
	
	
	//**************************************************
	// Orientation components in cryo vacuum
	//**************************************************
	orientation_ang_vac = -90. * deg;
	rmz_orientation_ang_vac = new G4RotationMatrix();
	rmz_orientation_ang_vac->rotateZ(-orientation_ang_vac);	
	
	rmx90 = new G4RotationMatrix();
	rmx90->rotateX(90.*deg);	
	
	rmxm90 = new G4RotationMatrix();
	rmxm90->rotateX(-90.*deg);
	
	rmy90 = new G4RotationMatrix();
	rmy90->rotateY(90.*deg);	
	
	rmym90 = new G4RotationMatrix();
	rmym90->rotateY(-90.*deg);
	
	//**************************************************
	// Common Parameters used to build the CF lines
	//**************************************************
	Cryostat_CF16lines_length        = Cryostats_dist_real;
	Cryostat_CF16lines_outerdiameter = 19.05*mm;
	Cryostat_CF16lines_wallthickness = 1.6*mm;
	Cryostat_CF16lines_innerdiameter = Cryostat_CF16lines_outerdiameter - 2*Cryostat_CF16lines_wallthickness;
	Cryostat_CF16lines_postition_r   = 12.5*cm/2;
	
	Cryostat_CF40lines_length        = Cryostats_dist_real;
	Cryostat_CF40lines_outerdiameter = 42.4*mm;
	Cryostat_CF40lines_wallthickness = 2.*mm;
	Cryostat_CF40lines_innerdiameter = Cryostat_CF40lines_outerdiameter - 2*Cryostat_CF40lines_wallthickness;
	Cryostat_CF40lines_postition_r   = 12.5*cm/2;
	
	//**************************************************
	// Common Parameters used to build the sample tube
	//**************************************************	
	Cryostat_sampletube_outerdiameter = 28.*mm;
	Cryostat_sampletube_innerdiameter = 25.*mm;
	
	// numbering tubes from high to low z
	
	Cryostat_sampletube_tube1_length      = Cryostats_dist_real + Cryostat_Inner_TopFlange1_length + Cryostat_Inner_TopFlange2_length;
	Cryostat_sampletube_tube1_postition_r = Cryostat_Outer_Tube_innerdiameter/2 - Cryostat_sampletube_outerdiameter/2 - 1.*mm; //225.*mm
	
	Cryostat_sampletube_tube3_length      = 280.*mm;
	Cryostat_sampletube_tube3_dist        = 45.*mm; // keep fixed
	Cryostat_sampletube_tube3_postition_r = Cryostat_sampletube_tube3_dist + Cryostat_Inner_Tube_outerdiameter/2;
	
	Cryostat_sampletube_tube4_length      = 107.*mm;
	Cryostat_sampletube_tube4_cap_length  = 4.*mm;
	Cryostat_sampletube_tube4_dist        = 36.*mm; // keep fixed
	
	Cryostat_sampletube_tube2_zlength     = (Cryostat_Inner_BottomPlate_length + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length) - (Cryostat_sampletube_tube3_length + (Cryostat_sampletube_tube3_dist - Cryostat_sampletube_tube4_dist));
	Cryostat_sampletube_tube2_diaglength  = std::sqrt(std::pow((Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r - Cryostat_sampletube_outerdiameter),2) + std::pow((Cryostat_sampletube_tube2_zlength),2));
	Cryostat_sampletube_tube2_length      = std::sqrt(std::pow((Cryostat_sampletube_tube2_diaglength),2) - std::pow((Cryostat_sampletube_outerdiameter),2));
	
	Cryostat_sampletube_knee1_ang = std::asin((Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r - Cryostat_sampletube_outerdiameter)/(Cryostat_sampletube_tube2_diaglength)) + std::asin(Cryostat_sampletube_outerdiameter/Cryostat_sampletube_tube2_diaglength);


//**********************************************CONSTRUCTION**********************************************

	// To Do: gaps due to copper gaskets?, add details such as KF40 flanges, screw bolts, filler,...

	//**************************************************
	// Cryostat Envelop
	//**************************************************

	G4Tubs* Cryostat_Envelop_solid = new G4Tubs("Cryostat_Envelop_solid", 0., Cryostat_Envelop_Radius, Cryostat_Envelop_Height/2 , 0.*deg, 360.*deg);

	Cryostat_Envelop_log = new G4LogicalVolume(Cryostat_Envelop_solid, Air, "Cryostat_Envelop_log", 0, 0, 0);


	//**************************************************
	// Outer Cryostat
	//**************************************************
	// very simplistic as temporary implementation, ToDo: correct later

	Cryostat_Outer_MotherLogicalVolume = Cryostat_Envelop_log;

	// Bottom Plate
	G4Tubs* Cryostat_Outer_Al_BottomPlate_solid = new G4Tubs("Cryostat_Outer_Al_BottomPlate_solid", 0., Cryostat_Outer_BottomPlate_diameter/2, Cryostat_Outer_BottomPlate_length/2 , 0.*deg, 360.*deg);

	Cryostat_Outer_Al_BottomPlate_log = new G4LogicalVolume(Cryostat_Outer_Al_BottomPlate_solid, Aluminium, "Cryostat_Outer_Al_BottomPlate_log");

	Cryostat_Outer_Al_BottomPlate_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -(Cryostat_Outer_Tube_length + Cryostat_Outer_BottomPlate_length)/2 - Cryostat_Inner_offset), Cryostat_Outer_Al_BottomPlate_log,"Cryostat_Outer_Al_BottomPlate", Cryostat_Outer_MotherLogicalVolume, 0, 0);

	// Tube
	G4Tubs* Cryostat_Outer_Al_Tube_solid = new G4Tubs("Cryostat_Outer_Al_Tube_solid", Cryostat_Outer_Tube_innerdiameter/2, Cryostat_Outer_Tube_outerdiameter/2, Cryostat_Outer_Tube_length/2 , 0.*deg, 360.*deg);

	Cryostat_Outer_Al_Tube_log = new G4LogicalVolume(Cryostat_Outer_Al_Tube_solid, Aluminium, "Cryostat_Outer_Al_Tube_log");

	Cryostat_Outer_Al_Tube_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, - Cryostat_Inner_offset), Cryostat_Outer_Al_Tube_log,"Cryostat_Outer_Al_Tube", Cryostat_Outer_MotherLogicalVolume, 0, 0);

	// Tube Flange
	G4Tubs* Cryostat_Outer_Al_TubeFlange_solid = new G4Tubs("Cryostat_Outer_Al_TubeFlange_solid", Cryostat_Outer_TubeFlange_innerdiameter/2, Cryostat_Outer_TubeFlange_outerdiameter/2, Cryostat_Outer_TubeFlange_length/2 , 0.*deg, 360.*deg);

	Cryostat_Outer_Al_TubeFlange_log = new G4LogicalVolume(Cryostat_Outer_Al_TubeFlange_solid, Aluminium, "Cryostat_Outer_Al_TubeFlange_log");

	Cryostat_Outer_Al_TubeFlange_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, Cryostat_Outer_Tube_length/2 - Cryostat_Outer_TubeFlange_length/2 - Cryostat_Inner_offset), Cryostat_Outer_Al_TubeFlange_log,"Cryostat_Outer_Al_TubeFlange", Cryostat_Outer_MotherLogicalVolume, 0, 0);

	// Top Flange
	G4Tubs* Cryostat_Outer_SS_TopFlange_solid = new G4Tubs("Cryostat_Outer_SS_TopFlange_solid", Cryostat_Outer_TopFlange_innerdiameter/2, Cryostat_Outer_TopFlange_outerdiameter/2, Cryostat_Outer_TopFlange_length/2 , 0.*deg, 360.*deg);

	Cryostat_Outer_SS_TopFlange_log = new G4LogicalVolume(Cryostat_Outer_SS_TopFlange_solid, SS304LSteel, "Cryostat_Outer_SS_TopFlange_log");

	Cryostat_Outer_SS_TopFlange_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, Cryostat_Outer_Tube_length/2 + Cryostat_Outer_TopFlange_length/2 - Cryostat_Inner_offset), Cryostat_Outer_SS_TopFlange_log,"Cryostat_Outer_SS_TopFlange", Cryostat_Outer_MotherLogicalVolume, 0, 0);


	//**************************************************
	// Vacuum
	//**************************************************

	G4Tubs* Cryostat_Vacuum_solid = new G4Tubs("Cryostat_Vacuum_solid", 0., Cryostat_Outer_Tube_innerdiameter/2, Cryostat_Outer_Tube_length/2 , 0.*deg, 360.*deg);

	Cryostat_Vacuum_log = new G4LogicalVolume(Cryostat_Vacuum_solid, Vacuum, "Cryostat_Vacuum_log");

	Cryostat_Vacuum_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, - Cryostat_Inner_offset), Cryostat_Vacuum_log,"Cryostat_Vacuum", Cryostat_Outer_MotherLogicalVolume, 0, 0);


	//**************************************************
	// TPC Envelop
	//**************************************************

	Cryostat_Inner_MotherLogicalVolume = Cryostat_Vacuum_log;

	G4Tubs* GXe_Cryostat_TPCEnvelop_solid = new G4Tubs("GXe_Cryostat_TPCEnvelop_solid", 0., Cryostat_TPCEnvelop_Radius, Cryostat_TPCEnvelop_Height/2 , 0.*deg, 360.*deg);

	GXe_Cryostat_TPCEnvelop_log = new G4LogicalVolume(GXe_Cryostat_TPCEnvelop_solid, GXe, "GXe_Cryostat_TPCEnvelop_log", 0, 0, 0);

	GXe_Cryostat_TPCEnvelop_phys = new G4PVPlacement(0, G4ThreeVector(0*cm, 0*cm, + Cryostat_Inner_offset), GXe_Cryostat_TPCEnvelop_log, "GXe_Cryostat_TPCEnvelop",  Cryostat_Inner_MotherLogicalVolume, false, 0);

	//**************************************************
	// Inner Cryostat
	//**************************************************

	// Bottom Plate
	G4Tubs* Cryostat_Inner_SS_BottomPlate_solid = new G4Tubs("Cryostat_Inner_SS_BottomPlate_solid", 0., Cryostat_Inner_BottomPlate_diameter/2, Cryostat_Inner_BottomPlate_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_BottomPlate_log = new G4LogicalVolume(Cryostat_Inner_SS_BottomPlate_solid, SS304LSteel, "Cryostat_Inner_SS_BottomPlate_log");

	Cryostat_Inner_SS_BottomPlate_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 - Cryostat_Inner_BottomPlate_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_BottomPlate_log,"Cryostat_Inner_SS_BottomPlate", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Tube
	G4Tubs* Cryostat_Inner_SS_Tube_solid = new G4Tubs("Cryostat_Inner_SS_Tube_solid", Cryostat_Inner_Tube_innerdiameter/2, Cryostat_Inner_Tube_outerdiameter/2, Cryostat_Inner_Tube_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_Tube_log = new G4LogicalVolume(Cryostat_Inner_SS_Tube_solid, SS304LSteel, "Cryostat_Inner_SS_Tube_log");

	Cryostat_Inner_SS_Tube_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_Tube_log,"Cryostat_Inner_SS_Tube", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Tube Flange
	G4Tubs* Cryostat_Inner_SS_TubeFlange_solid = new G4Tubs("Cryostat_Inner_SS_TubeFlange_solid", Cryostat_Inner_TubeFlange_innerdiameter/2, Cryostat_Inner_TubeFlange_outerdiameter/2, Cryostat_Inner_TubeFlange_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_TubeFlange_log = new G4LogicalVolume(Cryostat_Inner_SS_TubeFlange_solid, SS304LSteel, "Cryostat_Inner_SS_TubeFlange_log");

	Cryostat_Inner_SS_TubeFlange_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_TubeFlange_log,"Cryostat_Inner_SS_TubeFlange", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Middle Plate
	G4Tubs* Cryostat_Inner_SS_MiddlePlate_solid = new G4Tubs("Cryostat_Inner_SS_MiddlePlate_solid", Cryostat_Inner_MiddlePlate_innerdiameter/2, Cryostat_Inner_MiddlePlate_outerdiameter/2, Cryostat_Inner_MiddlePlate_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_MiddlePlate_log = new G4LogicalVolume(Cryostat_Inner_SS_MiddlePlate_solid, SS304LSteel, "Cryostat_Inner_SS_MiddlePlate_log");

	Cryostat_Inner_SS_MiddlePlate_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_MiddlePlate_log,"Cryostat_Inner_SS_MiddlePlate", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Upper Tube
	G4Tubs* Cryostat_Inner_SS_UpperTube_solid = new G4Tubs("Cryostat_Inner_SS_UpperTube_solid", Cryostat_Inner_UpperTube_innerdiameter/2, Cryostat_Inner_UpperTube_outerdiameter/2, Cryostat_Inner_UpperTube_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_UpperTube_log = new G4LogicalVolume(Cryostat_Inner_SS_UpperTube_solid, SS304LSteel, "Cryostat_Inner_SS_UpperTube_log");

	Cryostat_Inner_SS_UpperTube_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_UpperTube_log,"Cryostat_Inner_SS_UpperTube", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Upper Tube Flange
	G4Tubs* Cryostat_Inner_SS_UpperTubeFlange_solid = new G4Tubs("Cryostat_Inner_SS_UpperTubeFlange_solid", Cryostat_Inner_UpperTubeFlange_innerdiameter/2, Cryostat_Inner_UpperTubeFlange_outerdiameter/2, Cryostat_Inner_UpperTubeFlange_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_UpperTubeFlange_log = new G4LogicalVolume(Cryostat_Inner_SS_UpperTubeFlange_solid, SS304LSteel, "Cryostat_Inner_SS_UpperTubeFlange_log");

	Cryostat_Inner_SS_UpperTubeFlange_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_UpperTubeFlange_log,"Cryostat_Inner_SS_UpperTubeFlange", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Top Flange 1
	G4Tubs* Cryostat_Inner_SS_TopFlange1_solid = new G4Tubs("Cryostat_Inner_SS_TopFlange1_solid", Cryostat_Inner_TopFlange1_innerdiameter/2, Cryostat_Inner_TopFlange1_outerdiameter/2, Cryostat_Inner_TopFlange1_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_TopFlange1_log = new G4LogicalVolume(Cryostat_Inner_SS_TopFlange1_solid, SS304LSteel, "Cryostat_Inner_SS_TopFlange1_log");

	Cryostat_Inner_SS_TopFlange1_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length + Cryostat_Inner_TopFlange1_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_TopFlange1_log,"Cryostat_Inner_SS_TopFlange1", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	// Top Flange 2 (the upper closing one)
	G4Tubs* Cryostat_Inner_SS_TopFlange2_solid = new G4Tubs("Cryostat_Inner_SS_TopFlange2_solid", Cryostat_Inner_TopFlange2_innerdiameter/2, Cryostat_Inner_TopFlange2_outerdiameter/2, Cryostat_Inner_TopFlange2_length/2 , 0.*deg, 360.*deg);

	Cryostat_Inner_SS_TopFlange2_log = new G4LogicalVolume(Cryostat_Inner_SS_TopFlange2_solid, SS304LSteel, "Cryostat_Inner_SS_TopFlange2_log");

	Cryostat_Inner_SS_TopFlange2_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length + Cryostat_Inner_TopFlange1_length + Cryostat_Inner_TopFlange2_length/2 + Cryostat_Inner_offset), Cryostat_Inner_SS_TopFlange2_log,"Cryostat_Inner_SS_TopFlange2", Cryostat_Inner_MotherLogicalVolume, 0, 0);

	//**************************************************
	// Extra GXe volumes
	//**************************************************

	G4Tubs* GXe_Cryostat_extravolume_solid_orig = new G4Tubs("GXe_Cryostat_extravolume_solid_orig", 0., Cryostat_Inner_UpperTube_innerdiameter/2, (Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length)/2 , 0.*deg, 360.*deg);

	G4Tubs* GXe_Cryostat_extravolume_solid_union = new G4Tubs("GXe_Cryostat_extravolume_solid_union", 0., Cryostat_Inner_TopFlange1_innerdiameter/2, Cryostat_Inner_TopFlange1_length/2 , 0.*deg, 360.*deg);
	G4VSolid* GXe_Cryostat_extravolume_solid_1 = new G4UnionSolid("GXe_Cryostat_extravolume_solid_1", GXe_Cryostat_extravolume_solid_orig, GXe_Cryostat_extravolume_solid_union, 0, G4ThreeVector(0., 0., (Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length)/2 + Cryostat_Inner_TopFlange1_length/2));	

	G4Tubs* GXe_Cryostat_extravolume_solid_cut =  new G4Tubs("GXe_Cryostat_extravolume_solid_cut", 0., 0.15*m / 2, Cryostat_TPCEnvelop_overhang/2 , 0.*deg, 360.*deg);	
	G4VSolid* GXe_Cryostat_extravolume_solid = new G4SubtractionSolid("GXe_Cryostat_extravolume_solid", GXe_Cryostat_extravolume_solid_1, GXe_Cryostat_extravolume_solid_cut, 0, G4ThreeVector(0.,0.,-(Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length)/2 + Cryostat_TPCEnvelop_overhang/2));

	if (Cryostat_TPCEnvelop_overhang <= 0.)
	{
		G4cout << "########################################################################################" << G4endl;
		G4cout << "								WARNING: Cryostat_TPCEnvelop_overhang <= 0." << G4endl;
		G4cout << "########################################################################################" << G4endl;
	}

/*
	G4Tubs* GXe_Cryostat_extravolume_solid_cut =  new G4Tubs("GXe_Cryostat_extravolume_solid_cut", 0., 0.15*m / 2, -Cryostat_TPCEnvelop_overhang/2 , 0.*deg, 360.*deg);
	G4VSolid* GXe_Cryostat_extravolume_solid = new G4UnionSolid("GXe_Cryostat_extravolume_solid", GXe_Cryostat_extravolume_solid_1, GXe_Cryostat_extravolume_solid_cut, 0, G4ThreeVector(0.,0.,-(Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length)/2 - Cryostat_TPCEnvelop_overhang/2));
	if (Cryostat_TPCEnvelop_overhang >= 0.)
	{
		G4cout << "########################################################################################" << G4endl;
		G4cout << "								WARNING: Cryostat_TPCEnvelop_overhang >= 0." << G4endl;
		G4cout << "########################################################################################" << G4endl;
	}
*/
/*
	G4VSolid* GXe_Cryostat_extravolume_solid = GXe_Cryostat_extravolume_solid_1;
	if (Cryostat_TPCEnvelop_overhang != 0.)
	{
		G4cout << "########################################################################################" << G4endl;
		G4cout << "								WARNING: Cryostat_TPCEnvelop_overhang != 0." << G4endl;
		G4cout << "########################################################################################" << G4endl;
	}
*/

	GXe_Cryostat_extravolume_log = new G4LogicalVolume(GXe_Cryostat_extravolume_solid, GXe, "GXe_Cryostat_extravolume_log");

	GXe_Cryostat_extravolume_phys = new G4PVPlacement(nullptr, G4ThreeVector(0*cm, 0*cm, -Cryostat_TPCEnvelop_Height/2 + Cryostat_Inner_Tube_length + Cryostat_Inner_TubeFlange_length + Cryostat_Inner_MiddlePlate_length + (Cryostat_Inner_UpperTube_length + Cryostat_Inner_UpperTubeFlange_length)/2 + Cryostat_Inner_offset), GXe_Cryostat_extravolume_log,"GXe_Cryostat_extravolume", Cryostat_Inner_MotherLogicalVolume, 0, 0); 
	
	//**************************************************
	// CF lines
	//**************************************************
	
	G4Tubs* Cryostat_CF16lines_solid = new G4Tubs("Cryostat_CF16lines_solid", Cryostat_CF16lines_innerdiameter/2, Cryostat_CF16lines_outerdiameter/2, Cryostat_CF16lines_length/2 , 0.*deg, 360.*deg);	
	G4Tubs* Cryostat_CF40lines_solid = new G4Tubs("Cryostat_CF40lines_solid", Cryostat_CF40lines_innerdiameter/2, Cryostat_CF40lines_outerdiameter/2, Cryostat_CF40lines_length/2 , 0.*deg, 360.*deg);
	
	Cryostat_CF16lines_log = new G4LogicalVolume(Cryostat_CF16lines_solid, SS304LSteel, "Cryostat_CF16lines_log");
	Cryostat_CF40lines_log = new G4LogicalVolume(Cryostat_CF40lines_solid, SS304LSteel, "Cryostat_CF40lines_log");	

	Cryostat_CF16line_1_phys = new G4PVPlacement(nullptr, G4ThreeVector(Cryostat_CF16lines_postition_r * cos(orientation_ang_vac + 60.*deg), Cryostat_CF16lines_postition_r * sin(orientation_ang_vac + 60.*deg), Cryostat_Outer_Tube_length/2 - Cryostat_CF16lines_length/2), Cryostat_CF16lines_log,"Cryostat_CF16line_1", Cryostat_Vacuum_log, 0, 0);	
	Cryostat_CF40line_1_phys = new G4PVPlacement(nullptr, G4ThreeVector(Cryostat_CF40lines_postition_r * cos(orientation_ang_vac + 0.*deg), Cryostat_CF40lines_postition_r * sin(orientation_ang_vac + 0.*deg), Cryostat_Outer_Tube_length/2 - Cryostat_CF40lines_length/2), Cryostat_CF40lines_log,"Cryostat_CF40line_1", Cryostat_Vacuum_log, 0, 0);
	Cryostat_CF40line_2_phys = new G4PVPlacement(nullptr, G4ThreeVector(Cryostat_CF40lines_postition_r * cos(orientation_ang_vac + 120.*deg), Cryostat_CF40lines_postition_r * sin(orientation_ang_vac + 120.*deg), Cryostat_Outer_Tube_length/2 - Cryostat_CF40lines_length/2), Cryostat_CF40lines_log,"Cryostat_CF40line_2", Cryostat_Vacuum_log, 0, 0);
	Cryostat_CF40line_3_phys = new G4PVPlacement(nullptr, G4ThreeVector(Cryostat_CF40lines_postition_r * cos(orientation_ang_vac + 240.*deg), Cryostat_CF40lines_postition_r * sin(orientation_ang_vac + 240.*deg), Cryostat_Outer_Tube_length/2 - Cryostat_CF40lines_length/2), Cryostat_CF40lines_log,"Cryostat_CF40line_3", Cryostat_Vacuum_log, 0, 0);
	
	// ToDo: maybe add corresponding holes in flanges
	
	//**************************************************
	// Sample tube
	//**************************************************
	
	// tube parts
	
	G4Tubs* Cryostat_sampletube_tube1_solid = new G4Tubs("Cryostat_sampletube_tube1_solid", Cryostat_sampletube_innerdiameter/2, Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_tube1_length/2 , 0.*deg, 360.*deg);
	G4Tubs* Cryostat_sampletube_tube2_solid = new G4Tubs("Cryostat_sampletube_tube2_solid", Cryostat_sampletube_innerdiameter/2, Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_tube2_length/2 , 0.*deg, 360.*deg);
	G4Tubs* Cryostat_sampletube_tube3_solid = new G4Tubs("Cryostat_sampletube_tube3_solid", Cryostat_sampletube_innerdiameter/2, Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_tube3_length/2 , 0.*deg, 360.*deg);	
	G4Tubs* Cryostat_sampletube_tube4_orig_solid = new G4Tubs("Cryostat_sampletube_tube4_orig_solid", Cryostat_sampletube_innerdiameter/2, Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_tube4_length/2 , 0.*deg, 360.*deg);
	G4Tubs* Cryostat_sampletube_tube4_cap_solid = new G4Tubs("Cryostat_sampletube_tube4_cap_solid", 0., Cryostat_sampletube_innerdiameter/2, 4.*mm/2 , 0.*deg, 360.*deg);
	G4VSolid* Cryostat_sampletube_tube4_solid = new G4UnionSolid("Cryostat_sampletube_tube4_solid", Cryostat_sampletube_tube4_orig_solid, Cryostat_sampletube_tube4_cap_solid, 0, G4ThreeVector(0, 0, -(Cryostat_sampletube_tube4_length - 4.*mm)/2));
		
	G4Torus* Cryostat_sampletube_knee1_solid = new G4Torus("Cryostat_sampletube_knee1_solid", Cryostat_sampletube_innerdiameter/2, 0.99*Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_outerdiameter/2, 0.*deg, Cryostat_sampletube_knee1_ang); // factor 0.99 needed to avoid invalid swept radius for Solid pRtor = pRmax = 14
	G4VSolid* Cryostat_sampletube_knee2_solid = new G4Torus("Cryostat_sampletube_knee2_solid", Cryostat_sampletube_innerdiameter/2, 0.99*Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_outerdiameter/2, 180.*deg - Cryostat_sampletube_knee1_ang, Cryostat_sampletube_knee1_ang);
	G4VSolid* Cryostat_sampletube_knee3_solid = new G4Torus("Cryostat_sampletube_knee3_solid", Cryostat_sampletube_innerdiameter/2, Cryostat_sampletube_outerdiameter/2, Cryostat_sampletube_tube3_dist, 0.*deg, 90.*deg);
	
	// union solid
	
	G4VSolid* Cryostat_sampletube_union1_solid = new G4UnionSolid("Cryostat_sampletube_union1_solid", Cryostat_sampletube_tube1_solid, Cryostat_sampletube_knee1_solid, rmx90, G4ThreeVector(-Cryostat_sampletube_outerdiameter/2, 0, -Cryostat_sampletube_tube1_length/2));	
	rmy_tube2 = new G4RotationMatrix();
	rmy_tube2->rotateY(-Cryostat_sampletube_knee1_ang);	
	G4VSolid* Cryostat_sampletube_union2_solid = new G4UnionSolid("Cryostat_sampletube_union2_solid", Cryostat_sampletube_union1_solid, Cryostat_sampletube_tube2_solid, rmy_tube2, G4ThreeVector(- (Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r)/2, 0, -Cryostat_sampletube_tube1_length/2 - Cryostat_sampletube_tube2_zlength/2));	
	G4VSolid* Cryostat_sampletube_union3_solid = new G4UnionSolid("Cryostat_sampletube_union3_solid", Cryostat_sampletube_union2_solid, Cryostat_sampletube_knee2_solid, rmxm90, G4ThreeVector(- (Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r) + Cryostat_sampletube_outerdiameter/2, 0, -Cryostat_sampletube_tube1_length/2 - Cryostat_sampletube_tube2_zlength));	
	G4VSolid* Cryostat_sampletube_union4_solid = new G4UnionSolid("Cryostat_sampletube_union4_solid", Cryostat_sampletube_union3_solid, Cryostat_sampletube_tube3_solid, 0, G4ThreeVector(- (Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r), 0, -Cryostat_sampletube_tube1_length/2 - Cryostat_sampletube_tube2_zlength - Cryostat_sampletube_tube3_length/2));	
	G4VSolid* Cryostat_sampletube_union5_solid = new G4UnionSolid("Cryostat_sampletube_union5_solid", Cryostat_sampletube_union4_solid, Cryostat_sampletube_knee3_solid, rmx90, G4ThreeVector(- (Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r) -Cryostat_sampletube_tube3_dist, 0,  -Cryostat_sampletube_tube1_length/2 - Cryostat_sampletube_tube2_zlength - Cryostat_sampletube_tube3_length));	
	rmy_tube4 = new G4RotationMatrix();
	rmy_tube4->rotateY(-90.*deg);		
	G4VSolid* Cryostat_sampletube_solid = new G4UnionSolid("Cryostat_sampletube_solid", Cryostat_sampletube_union5_solid, Cryostat_sampletube_tube4_solid, rmy_tube4, G4ThreeVector(- (Cryostat_sampletube_tube1_postition_r - Cryostat_sampletube_tube3_postition_r) - Cryostat_sampletube_tube3_dist - Cryostat_sampletube_tube4_length/2, 0,  -Cryostat_sampletube_tube1_length/2 - Cryostat_sampletube_tube2_zlength - Cryostat_sampletube_tube3_length - Cryostat_sampletube_tube3_dist));
	
	// logical and physical volume
	
	Cryostat_sampletube_log = new G4LogicalVolume(Cryostat_sampletube_solid, SS304LSteel, "Cryostat_sampletube_log");
	
	Cryostat_sampletube_phys = new G4PVPlacement(rmz_orientation_ang_vac, G4ThreeVector(Cryostat_sampletube_tube1_postition_r * cos(orientation_ang_vac), Cryostat_sampletube_tube1_postition_r * sin(orientation_ang_vac), Cryostat_Outer_Tube_length/2 - Cryostat_sampletube_tube1_length/2), Cryostat_sampletube_log,"Cryostat_sampletube", Cryostat_Vacuum_log, 0, 0);	// ToDo: correct placement and rotation
	



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

  GXeMass_Cryo_extravolume = GXe_Cryostat_extravolume_log->GetMass(false, false)/kg;
  GXeVolume_Cryo_extravolume = GXeMass_Cryo_extravolume/(GXe->GetDensity()*m3/kg); 

  return Cryostat_Envelop_log; // ToDo: change
}


G4double XebraConstructCryostat::GetOuterRadiusCryostat(){
  return this->Cryostat_Envelop_Radius;
}

G4double XebraConstructCryostat::GetOuterHeightCryostat(){
  return this->Cryostat_Envelop_Height;
}

G4double XebraConstructCryostat::GetGXeMass_Cryo_extravolume(){
  return this->GXeMass_Cryo_extravolume;
}

G4double XebraConstructCryostat::GetGXeVolume_Cryo_extravolume(){
  return this->GXeVolume_Cryo_extravolume;
}


G4LogicalVolume* XebraConstructCryostat::GetMotherVolume(){
  return this->GXe_Cryostat_TPCEnvelop_log;
}



void XebraConstructCryostat::PrintGeometryInformation()
{
  GXeMass_C = XebraConstructCryostat::GetGXeMass_Cryo_extravolume();
  GXeVolume_C = XebraConstructCryostat::GetGXeVolume_Cryo_extravolume();
    
  G4cout << "GXe extra filling cryo:            " << GXeMass_C << " kg " << "     =============    " << GXeVolume_C << " m3 " << G4endl;
  G4cout << "======================================================================================== " << G4endl;
}


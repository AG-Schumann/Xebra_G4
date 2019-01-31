#ifndef XEBRACONSTRUCTCRYOSTAT_H
#define XEBRACONSTRUCTCRYOSTAT_H

//XEBRA header files
#include "XebraDetectorConstruction.hh"
#include "XebraConstructTPC.hh"

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
   G4double GetGXeMass_Cryo_extravolume();
   G4double GetGXeVolume_Cryo_extravolume();
   G4LogicalVolume* GetMotherVolume();

  void PrintGeometryInformation();

private:

	//Materials
	G4Material* Vacuum;
	G4Material* SS304LSteel;
	G4Material* GXe;
	G4Material* Air;
	G4Material* Aluminium;
	
 	G4double GXeMass_Cryo_extravolume;
	G4double GXeVolume_Cryo_extravolume;
	
	G4double GXeMass_C;
	G4double GXeVolume_C;

  //Parameters for the Cryostat Envelop
  G4double Cryostat_Envelop_Radius;  
  G4double Cryostat_Envelop_Height;

	// Parameters for the TPC Envelop
  G4double Cryostat_TPCEnvelop_Radius;  
  G4double Cryostat_TPCEnvelop_Height;

  //Parameters for the outer Cryostat
  G4double Cryostat_Outer_Tube_length;
  G4double Cryostat_Outer_Tube_outerdiameter;
  G4double Cryostat_Outer_Tube_wallthickness;
  G4double Cryostat_Outer_Tube_innerdiameter;
  G4double Cryostat_Outer_BottomPlate_length;
  G4double Cryostat_Outer_BottomPlate_diameter;
  G4double Cryostat_Outer_TubeFlange_length;
  G4double Cryostat_Outer_TubeFlange_innerdiameter;
  G4double Cryostat_Outer_TubeFlange_outerdiameter;
  G4double Cryostat_Outer_TopFlange_length;
  G4double Cryostat_Outer_TopFlange_outerdiameter;
  G4double Cryostat_Outer_TopFlange_innerdiameter;

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
  G4double Cryostat_Inner_TopFlange1_length;
  G4double Cryostat_Inner_TopFlange1_outerdiameter;
  G4double Cryostat_Inner_TopFlange1_innerdiameter;
  G4double Cryostat_Inner_TopFlange2_length;
  G4double Cryostat_Inner_TopFlange2_outerdiameter;
  G4double Cryostat_Inner_TopFlange2_innerdiameter;
  
  // Position shift inner in outer cryo
  G4double Cryostat_Inner_upperedge_unshifted;
  G4double Cryostat_Outer_TopFlange_loweredge_unshifted;
  G4double Cryostats_dist_unshifted;
  G4double Cryostats_dist_real;
  G4double Cryostat_Inner_offset;
  
  // Orientation components in cryo vacuum
  G4double orientation_ang_vac;
  G4RotationMatrix* rmz_orientation_ang_vac;
  G4RotationMatrix* rmx90;
  G4RotationMatrix* rmxm90;
  G4RotationMatrix* rmy90;
  G4RotationMatrix* rmym90;
  
  // Parameters for the CF lines
  G4double Cryostat_CF16lines_length;
  G4double Cryostat_CF16lines_outerdiameter;
  G4double Cryostat_CF16lines_wallthickness;
  G4double Cryostat_CF16lines_innerdiameter;
  G4double Cryostat_CF16lines_postition_r;
  G4double Cryostat_CF40lines_length;
  G4double Cryostat_CF40lines_outerdiameter;
  G4double Cryostat_CF40lines_wallthickness;
  G4double Cryostat_CF40lines_innerdiameter;
  G4double Cryostat_CF40lines_postition_r;
  
	// Parameters for the sample tube
	G4double Cryostat_sampletube_outerdiameter;
	G4double Cryostat_sampletube_innerdiameter;
	G4double Cryostat_sampletube_tube1_length;
	G4double Cryostat_sampletube_tube1_postition_r;
	G4double Cryostat_sampletube_tube3_length;
	G4double Cryostat_sampletube_tube3_dist;
	G4double Cryostat_sampletube_tube3_postition_r;
	G4double Cryostat_sampletube_tube4_length;
	G4double Cryostat_sampletube_tube4_cap_length;
	G4double Cryostat_sampletube_tube4_dist;
	G4double Cryostat_sampletube_tube2_zlength;
	G4double Cryostat_sampletube_tube2_diaglength;
	G4double Cryostat_sampletube_tube2_length;
	G4double Cryostat_sampletube_knee1_ang;
	

  //LogicalVolumes
  G4LogicalVolume* Cryostat_Envelop_log;
  G4LogicalVolume* GXe_Cryostat_TPCEnvelop_log;
  G4LogicalVolume* Cryostat_Inner_MotherLogicalVolume;
  G4LogicalVolume* Cryostat_Outer_MotherLogicalVolume;

  G4LogicalVolume* Cryostat_Outer_Al_BottomPlate_log;
  G4LogicalVolume* Cryostat_Outer_Al_Tube_log;
  G4LogicalVolume* Cryostat_Outer_Al_TubeFlange_log;
  G4LogicalVolume* Cryostat_Outer_SS_TopFlange_log;

  G4LogicalVolume* Cryostat_Vacuum_log;

  G4LogicalVolume* Cryostat_Inner_SS_BottomPlate_log;
  G4LogicalVolume* Cryostat_Inner_SS_Tube_log;
  G4LogicalVolume* Cryostat_Inner_SS_TubeFlange_log;
  G4LogicalVolume* Cryostat_Inner_SS_MiddlePlate_log;
  G4LogicalVolume* Cryostat_Inner_SS_UpperTube_log;
  G4LogicalVolume* Cryostat_Inner_SS_UpperTubeFlange_log;
  G4LogicalVolume* Cryostat_Inner_SS_TopFlange1_log;
  G4LogicalVolume* Cryostat_Inner_SS_TopFlange2_log;
  G4LogicalVolume* GXe_Cryostat_extravolume_log;
  
  G4LogicalVolume* Cryostat_CF16lines_log;
	G4LogicalVolume* Cryostat_CF40lines_log;
	
	G4LogicalVolume* Cryostat_sampletube_log;


  //PhysicalVolumes
	G4VPhysicalVolume* GXe_Cryostat_TPCEnvelop_phys;

  G4VPhysicalVolume* Cryostat_Outer_Al_BottomPlate_phys;
  G4VPhysicalVolume* Cryostat_Outer_Al_Tube_phys;
  G4VPhysicalVolume* Cryostat_Outer_Al_TubeFlange_phys;
  G4VPhysicalVolume* Cryostat_Outer_SS_TopFlange_phys;

  G4VPhysicalVolume* Cryostat_Vacuum_phys;

  G4VPhysicalVolume* Cryostat_Inner_SS_BottomPlate_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_Tube_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_TubeFlange_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_MiddlePlate_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_UpperTube_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_UpperTubeFlange_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_TopFlange1_phys;
  G4VPhysicalVolume* Cryostat_Inner_SS_TopFlange2_phys;
  G4VPhysicalVolume* GXe_Cryostat_extravolume_phys;
  
  G4VPhysicalVolume* Cryostat_CF16line_1_phys;
  G4VPhysicalVolume* Cryostat_CF40line_1_phys;
  G4VPhysicalVolume* Cryostat_CF40line_2_phys;
  G4VPhysicalVolume* Cryostat_CF40line_3_phys;
  
  G4VPhysicalVolume* Cryostat_sampletube_phys;


  //Visualization
  G4VisAttributes *VacuumVisAtt;
  G4VisAttributes *GXeVisAtt;
  G4VisAttributes *LXeVisAtt;
};

#endif

//XEBRA Header Files
#include "XebraPMTsR8520.hh"
#include "XebraPmtSensitiveDetector.hh"

//Additional Header Files
#include <globals.hh>

//G4 Header Files
#include <G4PVPlacement.hh>
#include <G4Material.hh>
#include <G4SDManager.hh> 
#include <G4SystemOfUnits.hh>


XebraPMTsR8520::XebraPMTsR8520(XebraConstructTPC*){;}

XebraPMTsR8520::~XebraPMTsR8520()
{;}

G4LogicalVolume* XebraPMTsR8520::Construct()
{
  //------------------------- Parameters ---------------------
	// Top PMT holder: smaller hole 21 x 21 x 2 mm with r = 2 mm, larger hole 26 x 26 x 6 mm with r = 2 mm
  const G4double R8520_body_width = 25.7 * mm;
  const G4double R8520_body_thickness = 0.4 * mm;
  const G4double R8520_photocathode_width = 20.5 * mm;
  const G4double R8520_body_cornerradius = 2. * mm;
  const G4double R8520_height = 28.25 * mm;
  const G4double R8520_window_height = 1.2 * mm;
  const G4double R8520_window_width = 24. * mm;
  const G4double R8520_ring_width = R8520_body_width;
  const G4double R8520_ring_hole_width = R8520_photocathode_width;
	const G4double R8520_ring_height = R8520_body_thickness;
  const G4double R8520_body_height = R8520_height; // without subtracted Al ring and window
  const G4double R8520_vacuum_solid_orig_height = (R8520_body_height-R8520_body_thickness-R8520_ring_height-R8520_window_height);
	const G4double R8520_photocathode_thickness = 0.1 * mm; // exact value irrelevant
	const G4double R8520_photocathode_cornerradius = 1. * mm;

  //------------------------- Materials ---------------------
  G4Material *Quartz = G4Material::GetMaterial("Quartz");
  G4Material *Kovar = G4Material::GetMaterial("Kovar");
  G4Material *Vacuum = G4Material::GetMaterial("Vacuum");
  G4Material *PhotoCathodeAluminium = G4Material::GetMaterial("PhotoCathodeAluminium");
  //G4Material *Ceramic = G4Material::GetMaterial("Ceramic");
  G4Material *Aluminium = G4Material::GetMaterial("Aluminium");

  //------------------------- PMT body ---------------------
	
	// general outer dimensions PMT
	R8520_body_solid_orig_1 = new G4Box("R8520_body_solid_orig_1", R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_width / 2, R8520_body_height / 2);
	R8520_body_solid_orig_2 = new G4Box("R8520_body_solid_orig_2", R8520_body_width / 2, R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_height / 2);
	R8520_body_solid_orig_3 = new G4Tubs("R8520_body_solid_orig_3", 0.*mm, R8520_body_cornerradius, R8520_body_height / 2, 0.*deg, 360.*deg);
	R8520_body_solid_orig_a = new G4UnionSolid("R8520_body_solid_orig_a", R8520_body_solid_orig_1, R8520_body_solid_orig_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_body_solid_orig_b = new G4UnionSolid("R8520_body_solid_orig_b", R8520_body_solid_orig_a, R8520_body_solid_orig_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig_c = new G4UnionSolid("R8520_body_solid_orig_c", R8520_body_solid_orig_b, R8520_body_solid_orig_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig_d = new G4UnionSolid("R8520_body_solid_orig_d", R8520_body_solid_orig_c, R8520_body_solid_orig_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig = new G4UnionSolid("R8520_body_solid_orig", R8520_body_solid_orig_d, R8520_body_solid_orig_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));

	// subtract edge outside of window
	R8520_body_solid_cut1 = new G4Box("R8520_body_solid_cut1", R8520_body_width / 2, R8520_body_width / 2, R8520_window_height / 2);
	R8520_body_solid_sub1 = new G4SubtractionSolid("R8520_body_solid_sub1", R8520_body_solid_orig, R8520_body_solid_cut1, 0, G4ThreeVector(0.,0.,(R8520_body_height - R8520_window_height)/2));

	R8520_body_solid_cut2_1 = new G4Box("R8520_body_solid_cut2_1", R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_width / 2, R8520_window_height / 2);
	R8520_body_solid_cut2_2 = new G4Box("R8520_body_solid_cut2_2", R8520_window_width / 2, R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_height / 2);
	R8520_body_solid_cut2_3 = new G4Tubs("R8520_body_solid_cut2_3", 0.*mm, R8520_body_cornerradius, R8520_window_height / 2, 0.*deg, 360.*deg);
	R8520_body_solid_cut2_a = new G4UnionSolid("R8520_body_solid_cut2_a", R8520_body_solid_cut2_1, R8520_body_solid_cut2_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_body_solid_cut2_b = new G4UnionSolid("R8520_body_solid_cut2_b", R8520_body_solid_cut2_a, R8520_body_solid_cut2_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut2_c = new G4UnionSolid("R8520_body_solid_cut2_c", R8520_body_solid_cut2_b, R8520_body_solid_cut2_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut2_d = new G4UnionSolid("R8520_body_solid_cut2_d", R8520_body_solid_cut2_c, R8520_body_solid_cut2_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut2 = new G4UnionSolid("R8520_body_solid_cut2", R8520_body_solid_cut2_d, R8520_body_solid_cut2_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));

	R8520_body_solid = new G4UnionSolid("R8520_body_solid", R8520_body_solid_sub1, R8520_body_solid_cut2, 0, G4ThreeVector(0., 0., (R8520_body_height - R8520_window_height)/2));

	R8520_log = new G4LogicalVolume(R8520_body_solid, Kovar, "R8520_log", 0, 0, 0);

  //------------------------ Synthetic Silica Window -----------------------
	R8520_window_solid_1 = new G4Box("R8520_window_solid_1", R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_width / 2, R8520_window_height / 2);
	R8520_window_solid_2 = new G4Box("R8520_window_solid_2", R8520_window_width / 2, R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_height / 2);
	R8520_window_solid_3 = new G4Tubs("R8520_window_solid_3", 0.*mm, R8520_body_cornerradius, R8520_window_height / 2, 0.*deg, 360.*deg);
	R8520_window_solid_a = new G4UnionSolid("R8520_window_solid_a", R8520_window_solid_1, R8520_window_solid_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_window_solid_b = new G4UnionSolid("R8520_window_solid_b", R8520_window_solid_a, R8520_window_solid_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_window_solid_c = new G4UnionSolid("R8520_window_solid_c", R8520_window_solid_b, R8520_window_solid_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_window_solid_d = new G4UnionSolid("R8520_window_solid_d", R8520_window_solid_c, R8520_window_solid_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_window_solid = new G4UnionSolid("R8520_window_solid", R8520_window_solid_d, R8520_window_solid_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));

	R8520_window_log = new G4LogicalVolume(R8520_window_solid, Quartz, "R8520_window_log", 0, 0, 0);

	R8520_window_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (R8520_body_height - R8520_window_height)/2), R8520_window_log, "PMT_R8520_Window", R8520_log, false, 0);

  //------------------------ Aluminium Ring -----------------------
	// general outer dimensions Al ring
	R8520_ring_solid_orig_1 = new G4Box("R8520_ring_solid_orig_1", R8520_ring_width / 2 - R8520_body_cornerradius, R8520_ring_width / 2, R8520_ring_height / 2);
	R8520_ring_solid_orig_2 = new G4Box("R8520_ring_solid_orig_2", R8520_ring_width / 2, R8520_ring_width / 2 - R8520_body_cornerradius, R8520_ring_height / 2);
	R8520_ring_solid_orig_3 = new G4Tubs("R8520_ring_solid_orig_3", 0.*mm, R8520_body_cornerradius, R8520_ring_height / 2, 0.*deg, 360.*deg);
	R8520_ring_solid_orig_a = new G4UnionSolid("R8520_ring_solid_orig_a", R8520_ring_solid_orig_1, R8520_ring_solid_orig_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_ring_solid_orig_b = new G4UnionSolid("R8520_ring_solid_orig_b", R8520_ring_solid_orig_a, R8520_ring_solid_orig_3, 0, G4ThreeVector((R8520_ring_width / 2 - R8520_body_cornerradius), (R8520_ring_width / 2 - R8520_body_cornerradius), 0.));
	R8520_ring_solid_orig_c = new G4UnionSolid("R8520_ring_solid_orig_c", R8520_ring_solid_orig_b, R8520_ring_solid_orig_3, 0, G4ThreeVector(-(R8520_ring_width / 2 - R8520_body_cornerradius), (R8520_ring_width / 2 - R8520_body_cornerradius), 0.));
	R8520_ring_solid_orig_d = new G4UnionSolid("R8520_ring_solid_orig_d", R8520_ring_solid_orig_c, R8520_ring_solid_orig_3, 0, G4ThreeVector((R8520_ring_width / 2 - R8520_body_cornerradius), -(R8520_ring_width / 2 - R8520_body_cornerradius), 0.));
	R8520_ring_solid_orig = new G4UnionSolid("R8520_ring_solid_orig", R8520_ring_solid_orig_d, R8520_ring_solid_orig_3, 0, G4ThreeVector(-(R8520_ring_width / 2 - R8520_body_cornerradius), -(R8520_ring_width / 2 - R8520_body_cornerradius), 0.));

	// subtract hole in ring
	R8520_ring_solid_hole_1 = new G4Box("R8520_ring_solid_hole_1", R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius, R8520_ring_hole_width / 2, R8520_ring_height / 2);
	R8520_ring_solid_hole_2 = new G4Box("R8520_ring_solid_hole_2", R8520_ring_hole_width / 2, R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius, R8520_ring_height / 2);
	R8520_ring_solid_hole_3 = new G4Tubs("R8520_ring_solid_hole_3", 0.*mm, R8520_photocathode_cornerradius, R8520_ring_height / 2, 0.*deg, 360.*deg);
	R8520_ring_solid_hole_a = new G4UnionSolid("R8520_ring_solid_hole_a", R8520_ring_solid_hole_1, R8520_ring_solid_hole_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_ring_solid_hole_b = new G4UnionSolid("R8520_ring_solid_hole_b", R8520_ring_solid_hole_a, R8520_ring_solid_hole_3, 0, G4ThreeVector((R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), (R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_ring_solid_hole_c = new G4UnionSolid("R8520_ring_solid_hole_c", R8520_ring_solid_hole_b, R8520_ring_solid_hole_3, 0, G4ThreeVector(-(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), (R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_ring_solid_hole_d = new G4UnionSolid("R8520_ring_solid_hole_d", R8520_ring_solid_hole_c, R8520_ring_solid_hole_3, 0, G4ThreeVector((R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), -(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_ring_solid_hole = new G4UnionSolid("R8520_ring_solid_hole", R8520_ring_solid_hole_d, R8520_ring_solid_hole_3, 0, G4ThreeVector(-(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), -(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));

	R8520_ring_solid = new G4SubtractionSolid("R8520_ring_solid", R8520_ring_solid_orig, R8520_ring_solid_hole, 0, G4ThreeVector(0.,0.,0.));

	R8520_ring_log = new G4LogicalVolume(R8520_ring_solid, Aluminium, "R8520_ring_log", 0, 0, 0);

	R8520_ring_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (R8520_body_height/2 - R8520_window_height - R8520_ring_height / 2)), R8520_ring_log, "PMT_R8520_Ring", R8520_log, false, 0);


  //------------------------ Inner Vacuum -----------------------
	R8520_vacuum_solid_orig_1 = new G4Box("R8520_vacuum_solid_orig_1", (R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius, (R8520_body_width-2*R8520_body_thickness) / 2, R8520_vacuum_solid_orig_height / 2);
	R8520_vacuum_solid_orig_2 = new G4Box("R8520_vacuum_solid_orig_2", (R8520_body_width-2*R8520_body_thickness) / 2, (R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius, R8520_vacuum_solid_orig_height / 2);
	R8520_vacuum_solid_orig_3 = new G4Tubs("R8520_vacuum_solid_orig_3", 0.*mm, R8520_body_cornerradius, R8520_vacuum_solid_orig_height / 2, 0.*deg, 360.*deg);
	R8520_vacuum_solid_orig_a = new G4UnionSolid("R8520_vacuum_solid_orig_a", R8520_vacuum_solid_orig_1, R8520_vacuum_solid_orig_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_vacuum_solid_orig_b = new G4UnionSolid("R8520_vacuum_solid_orig_b", R8520_vacuum_solid_orig_a, R8520_vacuum_solid_orig_3, 0, G4ThreeVector(((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), ((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), 0.));
	R8520_vacuum_solid_orig_c = new G4UnionSolid("R8520_vacuum_solid_orig_c", R8520_vacuum_solid_orig_b, R8520_vacuum_solid_orig_3, 0, G4ThreeVector(-((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), ((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), 0.));
	R8520_vacuum_solid_orig_d = new G4UnionSolid("R8520_vacuum_solid_orig_d", R8520_vacuum_solid_orig_c, R8520_vacuum_solid_orig_3, 0, G4ThreeVector(((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), -((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), 0.));
	R8520_vacuum_solid_orig = new G4UnionSolid("R8520_vacuum_solid_orig", R8520_vacuum_solid_orig_d, R8520_vacuum_solid_orig_3, 0, G4ThreeVector(-((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), -((R8520_body_width-2*R8520_body_thickness) / 2 - R8520_body_cornerradius), 0.));

	// add space in Al ring hole
	R8520_vacuum_solid_union_1 = new G4Box("R8520_vacuum_solid_union_1", R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius, R8520_ring_hole_width / 2, R8520_ring_height / 2);
	R8520_vacuum_solid_union_2 = new G4Box("R8520_vacuum_solid_union_2", R8520_ring_hole_width / 2, R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius, R8520_ring_height / 2);
	R8520_vacuum_solid_union_3 = new G4Tubs("R8520_vacuum_solid_union_3", 0.*mm, R8520_photocathode_cornerradius, R8520_ring_height / 2, 0.*deg, 360.*deg);
	R8520_vacuum_solid_union_a = new G4UnionSolid("R8520_vacuum_solid_union_a", R8520_vacuum_solid_union_1, R8520_vacuum_solid_union_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_vacuum_solid_union_b = new G4UnionSolid("R8520_vacuum_solid_union_b", R8520_vacuum_solid_union_a, R8520_vacuum_solid_union_3, 0, G4ThreeVector((R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), (R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_vacuum_solid_union_c = new G4UnionSolid("R8520_vacuum_solid_union_c", R8520_vacuum_solid_union_b, R8520_vacuum_solid_union_3, 0, G4ThreeVector(-(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), (R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_vacuum_solid_union_d = new G4UnionSolid("R8520_vacuum_solid_union_d", R8520_vacuum_solid_union_c, R8520_vacuum_solid_union_3, 0, G4ThreeVector((R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), -(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_vacuum_solid_union = new G4UnionSolid("R8520_vacuum_solid_union", R8520_vacuum_solid_union_d, R8520_vacuum_solid_union_3, 0, G4ThreeVector(-(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), -(R8520_ring_hole_width / 2 - R8520_photocathode_cornerradius), 0.));

	R8520_vacuum_solid = new G4UnionSolid("R8520_vacuum_solid", R8520_vacuum_solid_orig, R8520_vacuum_solid_union, 0, G4ThreeVector(0., 0., (R8520_vacuum_solid_orig_height/2 + R8520_ring_height / 2)));

	R8520_vacuum_log = new G4LogicalVolume(R8520_vacuum_solid, Vacuum, "R8520_vacuum_log", 0, 0, 0);

	R8520_vacuum_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (-R8520_body_height/2 + R8520_vacuum_solid_orig_height/2 + R8520_body_thickness)), R8520_vacuum_log, "PMT_R8520_Inner_Vacuum", R8520_log, false, 0);


  //------------------------ Photocathode ------------------------
	//R8520_photocathode_solid = new G4Box("R8520_photocathode_solid", R8520_photocathode_width / 2, R8520_photocathode_width / 2, R8520_photocathode_thickness / 2);

	R8520_photocathode_solid_1 = new G4Box("R8520_photocathode_solid_1", R8520_photocathode_width / 2 - R8520_photocathode_cornerradius, R8520_photocathode_width / 2, R8520_photocathode_thickness / 2);
	R8520_photocathode_solid_2 = new G4Box("R8520_photocathode_solid_2", R8520_photocathode_width / 2, R8520_photocathode_width / 2 - R8520_photocathode_cornerradius, R8520_photocathode_thickness / 2);
	R8520_photocathode_solid_3 = new G4Tubs("R8520_photocathode_solid_3", 0.*mm, R8520_photocathode_cornerradius, R8520_photocathode_thickness / 2, 0.*deg, 360.*deg);
	R8520_photocathode_solid_a = new G4UnionSolid("R8520_photocathode_solid_a", R8520_photocathode_solid_1, R8520_photocathode_solid_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_photocathode_solid_b = new G4UnionSolid("R8520_photocathode_solid_b", R8520_photocathode_solid_a, R8520_photocathode_solid_3, 0, G4ThreeVector((R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), (R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_photocathode_solid_c = new G4UnionSolid("R8520_photocathode_solid_c", R8520_photocathode_solid_b, R8520_photocathode_solid_3, 0, G4ThreeVector(-(R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), (R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_photocathode_solid_d = new G4UnionSolid("R8520_photocathode_solid_d", R8520_photocathode_solid_c, R8520_photocathode_solid_3, 0, G4ThreeVector((R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), -(R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), 0.));
	R8520_photocathode_solid = new G4UnionSolid("R8520_photocathode_solid", R8520_photocathode_solid_d, R8520_photocathode_solid_3, 0, G4ThreeVector(-(R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), -(R8520_photocathode_width / 2 - R8520_photocathode_cornerradius), 0.));

	R8520_photocathode_log = new G4LogicalVolume(R8520_photocathode_solid, PhotoCathodeAluminium, "R8520_photocathode_log", 0, 0, 0);

	R8520_photocathode_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, (R8520_vacuum_solid_orig_height/2 + R8520_ring_height - R8520_photocathode_thickness / 2)), R8520_photocathode_log, "PMT_R8520_Photocathode", R8520_vacuum_log, false, 0);


  //------------------------------- PMT sensitivity -------------------------------
  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
if(pSDManager->GetCollectionID("PmtHitsCollection")==-1)
	{
		XebraPmtSensitiveDetector* pPMT_R8520_SD = new XebraPmtSensitiveDetector("Xebra/PMT_R8520_SD");
		pSDManager->AddNewDetector(pPMT_R8520_SD);
		R8520_photocathode_log->SetSensitiveDetector(pPMT_R8520_SD);
	}
  
  //---------------------------------- attributes ---------------------------------
  
  //   R8520_vacuum_log->SetVisAttributes(G4VisAttributes::Invisible);

	G4Colour hPMTWindowColor(1., 0.757, 0.024);
  G4VisAttributes *pPMTWindowVisAtt = new G4VisAttributes(hPMTWindowColor);
  pPMTWindowVisAtt->SetVisibility(true);
  R8520_window_log->SetVisAttributes(pPMTWindowVisAtt);

  G4Colour hPMTPhotocathodeColor(1., 0.082, 0.011);
  G4VisAttributes *pPMTPhotocathodeVisAtt = new G4VisAttributes(hPMTPhotocathodeColor);
  pPMTPhotocathodeVisAtt->SetVisibility(true);
  R8520_photocathode_log->SetVisAttributes(pPMTPhotocathodeVisAtt);

  G4Colour hPMTColor(1., 0.486, 0.027);
  G4VisAttributes *pPMTVisAtt = new G4VisAttributes(hPMTColor);
  pPMTVisAtt->SetVisibility(true);
  R8520_log->SetVisAttributes(pPMTVisAtt);

  G4Colour hVacuumColor(1., 1., 1.);
  G4VisAttributes *pVacuumVisAtt = new G4VisAttributes(hVacuumColor);
  pVacuumVisAtt->SetVisibility(true);
  R8520_vacuum_log->SetVisAttributes(pVacuumVisAtt);


  return R8520_log;
}

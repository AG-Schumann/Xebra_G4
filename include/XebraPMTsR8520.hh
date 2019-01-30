#ifndef XEBRAPMTsR8520_H
#define XEBRAPMTsR8520_H

//XEBRA header files
#include "XebraConstructTPC.hh"
#include "XebraPmtSensitiveDetector.hh"

//Additional Header Files
#include <globals.hh>


//G4 Header Files
#include <G4Material.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Polyhedra.hh>
#include <G4Polycone.hh>
#include <G4Ellipsoid.hh>
#include <G4UnionSolid.hh>
#include <G4SubtractionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>


class XebraPMTsR8520
{
public:
	XebraPMTsR8520(XebraConstructTPC*);
	~XebraPMTsR8520();

	G4LogicalVolume* Construct();

private:
	// Solids:
	G4Box* R8520_body_solid_orig_1;
	G4Box* R8520_body_solid_orig_2;
	G4Tubs* R8520_body_solid_orig_3;
	G4VSolid* R8520_body_solid_orig_a;
	G4VSolid* R8520_body_solid_orig_b;
	G4VSolid* R8520_body_solid_orig_c;
	G4VSolid* R8520_body_solid_orig_d;
	G4VSolid* R8520_body_solid_orig;

	G4VSolid* R8520_body_solid_cut1;
	G4VSolid* R8520_body_solid_sub1;

	G4Box* R8520_body_solid_cut2_1;
	G4Box* R8520_body_solid_cut2_2;
	G4Tubs* R8520_body_solid_cut2_3;
	G4VSolid* R8520_body_solid_cut2_a;
	G4VSolid* R8520_body_solid_cut2_b;
	G4VSolid* R8520_body_solid_cut2_c;
	G4VSolid* R8520_body_solid_cut2_d;
	G4VSolid* R8520_body_solid_cut2;

	G4VSolid* R8520_body_solid;

	G4Box* R8520_window_solid_1;
	G4Box* R8520_window_solid_2;
	G4Tubs* R8520_window_solid_3;
	G4VSolid* R8520_window_solid_a;
	G4VSolid* R8520_window_solid_b;
	G4VSolid* R8520_window_solid_c;
	G4VSolid* R8520_window_solid_d;
	G4VSolid* R8520_window_solid;

	G4Box* R8520_ring_solid_orig_1;
	G4Box* R8520_ring_solid_orig_2;
	G4Tubs* R8520_ring_solid_orig_3;
	G4VSolid* R8520_ring_solid_orig_a;
	G4VSolid* R8520_ring_solid_orig_b;
	G4VSolid* R8520_ring_solid_orig_c;
	G4VSolid* R8520_ring_solid_orig_d;
	G4VSolid* R8520_ring_solid_orig;

	G4Box* R8520_ring_solid_hole_1;
	G4Box* R8520_ring_solid_hole_2;
	G4Tubs* R8520_ring_solid_hole_3;
	G4VSolid* R8520_ring_solid_hole_a;
	G4VSolid* R8520_ring_solid_hole_b;
	G4VSolid* R8520_ring_solid_hole_c;
	G4VSolid* R8520_ring_solid_hole_d;
	G4VSolid* R8520_ring_solid_hole;

	G4VSolid* R8520_ring_solid;

	G4Box* R8520_vacuum_solid_orig_1;
	G4Box* R8520_vacuum_solid_orig_2;
	G4Tubs* R8520_vacuum_solid_orig_3;
	G4VSolid* R8520_vacuum_solid_orig_a;
	G4VSolid* R8520_vacuum_solid_orig_b;
	G4VSolid* R8520_vacuum_solid_orig_c;
	G4VSolid* R8520_vacuum_solid_orig_d;
	G4VSolid* R8520_vacuum_solid_orig;

	G4Box* R8520_vacuum_solid_union_1;
	G4Box* R8520_vacuum_solid_union_2;
	G4Tubs* R8520_vacuum_solid_union_3;
	G4VSolid* R8520_vacuum_solid_union_a;
	G4VSolid* R8520_vacuum_solid_union_b;
	G4VSolid* R8520_vacuum_solid_union_c;
	G4VSolid* R8520_vacuum_solid_union_d;
	G4VSolid* R8520_vacuum_solid_union;

	G4VSolid* R8520_vacuum_solid;

	G4Box* R8520_photocathode_solid_1;
	G4Box* R8520_photocathode_solid_2;
	G4Tubs* R8520_photocathode_solid_3;
	G4VSolid* R8520_photocathode_solid_a;
	G4VSolid* R8520_photocathode_solid_b;
	G4VSolid* R8520_photocathode_solid_c;
	G4VSolid* R8520_photocathode_solid_d;
	G4VSolid* R8520_photocathode_solid;

	// Logical Volumes:
  G4LogicalVolume* R8520_log;
  G4LogicalVolume* R8520_window_log;
  G4LogicalVolume* R8520_ring_log;
  G4LogicalVolume* R8520_vacuum_log;
  G4LogicalVolume* R8520_photocathode_log;

  // Physical Volumes:
  G4VPhysicalVolume* R8520_window_phys;
  G4VPhysicalVolume* R8520_ring_phys;
  G4VPhysicalVolume* R8520_vacuum_phys;
  G4VPhysicalVolume* R8520_photocathode_phys;

};

#endif

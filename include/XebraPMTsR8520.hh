#ifndef XEBRAPMTsR8520_H
#define XEBRAPMTsR8520_H

//XEBRA header files
#include "XebraConstructTPC.hh"

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
    
	// Parameters:

	// Solids:
	G4Box* R8520_body_solid_orig_1;
	G4Box* R8520_body_solid_orig_2;
	G4Tubs* R8520_body_solid_orig_3;
	G4VSolid* R8520_body_solid_orig_a;
	G4VSolid* R8520_body_solid_orig_b;
	G4VSolid* R8520_body_solid_orig_c;
	G4VSolid* R8520_body_solid_orig_d;
	G4VSolid* R8520_body_solid_orig;

	G4Box* R8520_body_solid_cut1_1;
	G4Box* R8520_body_solid_cut1_2;
	G4Tubs* R8520_body_solid_cut1_3;
	G4VSolid* R8520_body_solid_cut1_a;
	G4VSolid* R8520_body_solid_cut1_b;
	G4VSolid* R8520_body_solid_cut1_c;
	G4VSolid* R8520_body_solid_cut1_d;
	G4VSolid* R8520_body_solid_cut1;
	G4VSolid* R8520_body_solid_sub1;

	G4VSolid* R8520_body_solid;

	G4Box* R8520_window_solid_1;
	G4Box* R8520_window_solid_2;
	G4Tubs* R8520_window_solid_3;
	G4VSolid* R8520_window_solid_a;
	G4VSolid* R8520_window_solid_b;
	G4VSolid* R8520_window_solid_c;
	G4VSolid* R8520_window_solid_d;
	G4VSolid* R8520_window_solid;

	// Logical Volumes:
  G4LogicalVolume* R8520_log;
  G4LogicalVolume* R8520_window_log;

  // Physical Volumes:
  G4VPhysicalVolume* R8520_window_phys;

};

#endif
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
	const G4double R8520_ring_height = R8520_body_thickness;
  const G4double R8520_body_height = R8520_height; // without subtracted Al ring and window

  //------------------------- Materials ---------------------
  G4Material *Quartz = G4Material::GetMaterial("Quartz");
  G4Material *Kovar = G4Material::GetMaterial("Kovar");
  G4Material *Vacuum = G4Material::GetMaterial("Vacuum");
  G4Material *PhotoCathodeAluminium = G4Material::GetMaterial("PhotoCathodeAluminium");
  G4Material *Ceramic = G4Material::GetMaterial("Ceramic");
  G4Material *Aluminium = G4Material::GetMaterial("Aluminium");

  //------------------------- PMT body ---------------------
	
	// general outer dimensions PMT without subtracted Al ring and window
	R8520_body_solid_orig_1 = new G4Box("R8520_body_solid_orig_1", R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_width / 2, R8520_body_height / 2);
	R8520_body_solid_orig_2 = new G4Box("R8520_body_solid_orig_2", R8520_body_width / 2, R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_height / 2);
	R8520_body_solid_orig_3 = new G4Tubs("R8520_body_solid_orig_3", 0.*mm, R8520_body_cornerradius, R8520_body_height / 2, 0.*deg, 360.*deg);
	R8520_body_solid_orig_a = new G4UnionSolid("R8520_body_solid_orig_a", R8520_body_solid_orig_1, R8520_body_solid_orig_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_body_solid_orig_b = new G4UnionSolid("R8520_body_solid_orig_b", R8520_body_solid_orig_a, R8520_body_solid_orig_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig_c = new G4UnionSolid("R8520_body_solid_orig_c", R8520_body_solid_orig_b, R8520_body_solid_orig_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig_d = new G4UnionSolid("R8520_body_solid_orig_d", R8520_body_solid_orig_c, R8520_body_solid_orig_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_orig = new G4UnionSolid("R8520_body_solid_orig", R8520_body_solid_orig_d, R8520_body_solid_orig_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));

	// subtract Al ring and window
	R8520_body_solid_cut1_1 = new G4Box("R8520_body_solid_cut1_1", R8520_body_width / 2 - R8520_body_cornerradius, R8520_body_width / 2, (R8520_window_height + R8520_ring_height) / 2);
	R8520_body_solid_cut1_2 = new G4Box("R8520_body_solid_cut1_2", R8520_body_width / 2, R8520_body_width / 2 - R8520_body_cornerradius, (R8520_window_height + R8520_ring_height) / 2);
	R8520_body_solid_cut1_3 = new G4Tubs("R8520_body_solid_cut1_3", 0.*mm, R8520_body_cornerradius, (R8520_window_height + R8520_ring_height) / 2, 0.*deg, 360.*deg);
	R8520_body_solid_cut1_a = new G4UnionSolid("R8520_body_solid_cut1_a", R8520_body_solid_cut1_1, R8520_body_solid_cut1_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_body_solid_cut1_b = new G4UnionSolid("R8520_body_solid_cut1_b", R8520_body_solid_cut1_a, R8520_body_solid_cut1_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut1_c = new G4UnionSolid("R8520_body_solid_cut1_c", R8520_body_solid_cut1_b, R8520_body_solid_cut1_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), (R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut1_d = new G4UnionSolid("R8520_body_solid_cut1_d", R8520_body_solid_cut1_c, R8520_body_solid_cut1_3, 0, G4ThreeVector((R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_cut1 = new G4UnionSolid("R8520_body_solid_cut1", R8520_body_solid_cut1_d, R8520_body_solid_cut1_3, 0, G4ThreeVector(-(R8520_body_width / 2 - R8520_body_cornerradius), -(R8520_body_width / 2 - R8520_body_cornerradius), 0.));
	R8520_body_solid_sub1 = new G4SubtractionSolid("R8520_body_solid_sub1", R8520_body_solid_orig, R8520_body_solid_cut1, 0, G4ThreeVector(0.,0.,(R8520_body_height-(R8520_window_height + R8520_ring_height))/2));

	R8520_body_solid = R8520_body_solid_sub1;

		// ToDo: remove inner vacuum

	R8520_log = new G4LogicalVolume(R8520_body_solid, Kovar, "R8520_log", 0, 0, 0); //ToDo: check material!

  //------------------------ Aluminium Ring -----------------------


  //------------------------ Inner Vacuum -----------------------


  //------------------------ Synthetic Silica Window -----------------------
	R8520_window_solid_1 = new G4Box("R8520_window_solid_1", R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_width / 2, R8520_window_height / 2);
	R8520_window_solid_2 = new G4Box("R8520_window_solid_2", R8520_window_width / 2, R8520_window_width / 2 - R8520_body_cornerradius, R8520_window_height / 2);
	R8520_window_solid_3 = new G4Tubs("R8520_window_solid_3", 0.*mm, R8520_body_cornerradius, R8520_window_height / 2, 0.*deg, 360.*deg);
	R8520_window_solid_a = new G4UnionSolid("R8520_window_solid_a", R8520_window_solid_1, R8520_window_solid_2, 0, G4ThreeVector(0., 0., 0.));
	R8520_window_solid_b = new G4UnionSolid("R8520_window_solid_b", R8520_window_solid_a, R8520_window_solid_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_window_solid_c = new G4UnionSolid("R8520_window_solid_c", R8520_window_solid_b, R8520_window_solid_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), (R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_window_solid_d = new G4UnionSolid("R8520_window_solid_d", R8520_window_solid_c, R8520_window_solid_3, 0, G4ThreeVector((R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));
	R8520_window_solid = new G4UnionSolid("R8520_window_solid", R8520_window_solid_d, R8520_window_solid_3, 0, G4ThreeVector(-(R8520_window_width / 2 - R8520_body_cornerradius), -(R8520_window_width / 2 - R8520_body_cornerradius), 0.));

	R8520_window_log = new G4LogicalVolume(R8520_window_solid, Quartz, "R8520_window_log", 0, 0, 0); //ToDo: check material!

	R8520_window_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), R8520_window_log, "PMT1_Window", R8520_log, false, 0); 
//(R8520_body_height - R8520_window_height)/2  //ToDo: correct position

  //------------------------ Photocathode ------------------------


  //------------------------ Base Stem ------------------------


  //------------------------------- PMT sensitivity -------------------------------
  /*
  G4SDManager *pSDManager = G4SDManager::GetSDMpointer(); //ToDo: make proper sensitive detector, check with sensor array and sensitvie det. files
  XebraPmtSensitiveDetector* pPmt1SD;

  if(pSDManager->GetCollectionID("PmtHitsCollection")==-1)
     {
       pPmt1SD = new XebraPmtSensitiveDetector("Xebra/PmtSD");
       pSDManager->AddNewDetector(pPmt1SD);
       PMT_Photocathode_log->SetSensitiveDetector(pPmt1SD);
     }
	*/
  
  //---------------------------------- attributes ---------------------------------
  
  //   m_pPMTInnerVacuumLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);

  /*
	G4Colour hPMTWindowColor(1., 0.757, 0.024);
  G4VisAttributes *pPMTWindowVisAtt = new G4VisAttributes(hPMTWindowColor);
  pPMTWindowVisAtt->SetVisibility(true);
  m_pPMTWindowLogicalVolume->SetVisAttributes(pPMTWindowVisAtt);

  G4Colour hPMTPhotocathodeColor(1., 0.082, 0.011);
  G4VisAttributes *pPMTPhotocathodeVisAtt = new G4VisAttributes(hPMTPhotocathodeColor);
  pPMTPhotocathodeVisAtt->SetVisibility(true);
  m_pPMTPhotocathodeLogicalVolume->SetVisAttributes(pPMTPhotocathodeVisAtt);

  G4Colour hPMTColor(1., 0.486, 0.027);
  G4VisAttributes *pPMTVisAtt = new G4VisAttributes(hPMTColor);
  pPMTVisAtt->SetVisibility(true);
  m_pPMTLogicalVolume->SetVisAttributes(pPMTVisAtt);

  G4Colour hVacuumColor(1., 1., 1.);
  G4VisAttributes *pVacuumVisAtt = new G4VisAttributes(hVacuumColor);
  pVacuumVisAtt->SetVisibility(true);
  m_pPMTInnerVacuumLogicalVolume->SetVisAttributes(pVacuumVisAtt);
	*/


  return R8520_log;
}

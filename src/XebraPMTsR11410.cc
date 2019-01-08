//XEBRA Header Files
#include "XebraPMTsR11410.hh"
#include "XebraPmtSensitiveDetector.hh"

//Additional Header Files
#include <globals.hh>

//G4 Header Files
#include <G4PVPlacement.hh>
#include <G4Material.hh>
#include <G4SDManager.hh> 
#include <G4SystemOfUnits.hh>

//ToDo: rename so that no ambiguities with other PMTs

XebraPMTsR11410::XebraPMTsR11410(XebraConstructTPC*){;}

XebraPMTsR11410::~XebraPMTsR11410()
{;}

G4LogicalVolume* XebraPMTsR11410::Construct()
{
  //pMaterials = pDetectorConstrution->GetMaterialInstance();

  dPMTOuterRadius      = 38.*mm;
  dPMTOuterRingBottomZ = 9.*mm;
  dPMTOuterRingHeight  = 5.*mm;
  dPMTOuterRingRadius  = 38.75*mm;  // 38.75*mm;

  dPMTWindowRadius    = 35.*mm;
  dPMTWindowThickness = 5.*mm;
  dPMTWindowGap       = 1.*mm;

  dPMTThickness = 1.*mm;
  dPMTHeight = 114.*mm;  // 123.*mm;
  dPMTDinodeCutZ = 11.8*mm;
  dPMTFunnelCutZ = 11.8*mm;
  dPMTBaseRadius = 26.65*mm;

  dPMTPhotocathodeRadius = 32.*mm;
  dPMTPhotocathodeThickness = 0.1*mm;

  dPMTCeramicRadius = dPMTBaseRadius-5.*mm;
  dPMTCeramicThickness = 4.*mm;

  G4Material *Quartz = G4Material::GetMaterial("Quartz");
  G4Material *Kovar = G4Material::GetMaterial("Kovar");
  G4Material *Vacuum = G4Material::GetMaterial("Vacuum");
  G4Material *PhotoCathodeAluminium = G4Material::GetMaterial("PhotoCathodeAluminium");
  G4Material *Ceramic = G4Material::GetMaterial("Ceramic");

  //------------------------- PMT body ---------------------
  const G4double dPMTZ0  = -0.5*dPMTHeight;
  const G4double dPMTZ1  = dPMTZ0+dPMTOuterRingBottomZ;
  const G4double dPMTZ2  = dPMTZ1;
  const G4double dPMTZ3  = dPMTZ2+dPMTOuterRingHeight;
  const G4double dPMTZ4  = dPMTZ3;
  const G4double dPMTZ5  = dPMTZ4+dPMTDinodeCutZ;
  const G4double dPMTZ6  = dPMTZ5+dPMTFunnelCutZ;
  const G4double dPMTZ7  = dPMTZ6+1.*cm;
  const G4double dPMTZ8  = dPMTZ7;
  const G4double dPMTZ9  = dPMTZ8+1.*mm;
  const G4double dPMTZ10 = dPMTZ9;
  const G4double dPMTZ11 = 0.5*dPMTHeight-6.*mm;
  const G4double dPMTZ12 = 0.5*dPMTHeight-6.*mm;
  const G4double dPMTZ13 = 0.5*dPMTHeight-5.*mm;
  const G4double dPMTZ14  = 0.5*dPMTHeight-5.*mm;
  const G4double dPMTZ15 = 0.5*dPMTHeight;

  const G4double dPMTR0  = dPMTOuterRadius;
  const G4double dPMTR1  = dPMTR0; 
  const G4double dPMTR2  = dPMTOuterRingRadius; 
  const G4double dPMTR3  = dPMTR2; 
  const G4double dPMTR4  = dPMTR0;
  const G4double dPMTR5  = dPMTR0;
  const G4double dPMTR6  = dPMTBaseRadius;
  const G4double dPMTR7  = dPMTR6;
  const G4double dPMTR8  = dPMTR6+0.5*mm;
  const G4double dPMTR9  = dPMTR6+0.5*mm;
  const G4double dPMTR10 = dPMTR6;
  const G4double dPMTR11 = dPMTR6;
  const G4double dPMTR12 = dPMTR6+0.5*mm;
  const G4double dPMTR13 = dPMTR6+0.5*mm;
  const G4double dPMTR14 = dPMTR6;
  const G4double dPMTR15 = dPMTR6;

  const G4double dPMTZPlane[] = {dPMTZ0,dPMTZ1,dPMTZ2,dPMTZ3,dPMTZ4,dPMTZ5,dPMTZ6,dPMTZ7,dPMTZ8,dPMTZ9,dPMTZ10,dPMTZ11,
				 dPMTZ12,dPMTZ13,dPMTZ14,dPMTZ15};
  const G4double dPMTInner[]  = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
  const G4double dPMTOuter[]  = {dPMTR0,dPMTR1,dPMTR2,dPMTR3,dPMTR4,dPMTR5,dPMTR6,dPMTR7,dPMTR8,dPMTR9,dPMTR10,dPMTR11,
				 dPMTR12,dPMTR13,dPMTR14,dPMTR15};


  G4Polycone *pPMTPolycone = new G4Polycone("pPMTPolycone", 0., 2*M_PI, 16, dPMTZPlane, dPMTInner, dPMTOuter);
  G4Tubs *pPmtCut1Tubs = new G4Tubs("pPmtCut1Tubs", dPMTWindowRadius, dPMTOuterRadius, dPMTWindowGap, 0., 2*M_PI);
  G4SubtractionSolid *pPmtSubtractionSolid = new G4SubtractionSolid("pPmtSubtractionSolid1",pPMTPolycone, pPmtCut1Tubs, 0, G4ThreeVector(0.,0.,dPMTZ0));

  G4Tubs *pPmtCut2Tubs = new G4Tubs("pPmtCut2Tubs", dPMTWindowRadius, dPMTOuterRadius-dPMTThickness, dPMTWindowThickness*0.5-dPMTThickness*0.5, 0., 2*M_PI);
  pPmtSubtractionSolid = new G4SubtractionSolid("pPmtSubtractionSolid2",pPmtSubtractionSolid, pPmtCut2Tubs, 0, G4ThreeVector(0.,0.,dPMTZ0+dPMTWindowThickness*0.5));

  m_pPMTLogicalVolume = new G4LogicalVolume(pPmtSubtractionSolid, Kovar, "PMTLogicalVolume", 0, 0, 0);

//   m_pPMTPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), m_pPMTLogicalVolume, "PMT", m_pLXeLogicalVolume, false, 0);
//ToDo important: already included via implementation in ConstructTPC?

  //------------------------ Inner Vacuum -----------------------
  const G4double dPMTCutZ0 = 0.*cm;// 0.5*GetGeometryParameter("PMTHeight")-dPMTWindowThickness;
  const G4double dPMTCutZ1 = dPMTCutZ0+dPMTDinodeCutZ+dPMTOuterRingBottomZ+dPMTOuterRingHeight-dPMTWindowThickness;
  const G4double dPMTCutZ2 = dPMTCutZ1+dPMTFunnelCutZ;
  const G4double dPMTCutZ3 = dPMTHeight-dPMTWindowThickness-dPMTThickness;

  const G4double dPMTCutR0 = dPMTOuterRadius-dPMTThickness;
  const G4double dPMTCutR1 = dPMTCutR0;
  const G4double dPMTCutR2 = dPMTBaseRadius-dPMTThickness;
  const G4double dPMTCutR3 = dPMTCutR2;

  const G4double dPMTInnerVacuumOffsetZ = -dPMTHeight*0.5+dPMTWindowThickness;

  const G4double dPMTZCutPlane[] = {dPMTCutZ0,dPMTCutZ1,dPMTCutZ2,dPMTCutZ3};
  const G4double dPMTCutInner[]  = {0.,0.,0.,0.};
  const G4double dPMTCutOuter[]  = {dPMTCutR0,dPMTCutR1,dPMTCutR2,dPMTCutR3};

  G4Polycone *pPMTInnerVacuumPolycone = new G4Polycone("pPMTInnerVacuumPolycone", 0.*deg, 360.*deg, 4, dPMTZCutPlane, dPMTCutInner, dPMTCutOuter);

  G4Tubs *pPMTVacuumCut = new G4Tubs("pPMTVacuumCut", dPMTPhotocathodeRadius, dPMTOuterRadius, dPMTThickness*0.5, 0.*deg, 360.*deg);

  G4SubtractionSolid *pPMTVacuumSubtractionSolid = new G4SubtractionSolid("pPMTVacuumSubtractionSolid", 
									  pPMTInnerVacuumPolycone, 
									  pPMTVacuumCut, 0, G4ThreeVector(0.,0.,dPMTCutZ0+dPMTThickness*0.5));

  G4Tubs* pCut = new G4Tubs("pPMTCut", 0.*mm, dPMTCeramicRadius, dPMTCeramicThickness*0.5, 0.*deg, 360.*deg);
  G4SubtractionSolid *pPMTcut1 = new G4SubtractionSolid("pPMTVacuumSubtractionSolid", pPMTVacuumSubtractionSolid, 
							pCut, 0, G4ThreeVector(0.,0.,dPMTCutZ3+dPMTThickness-dPMTCeramicThickness*0.5));
  //dPMTCutZ0+dPMTThickness*0.5));


  m_pPMTInnerVacuumLogicalVolume = new G4LogicalVolume(pPMTcut1, Vacuum, "PMTInnerVacuumLogicalVolume", 0, 0, 0);

  m_pPMTInnerVacuumPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, dPMTInnerVacuumOffsetZ), 
						      m_pPMTInnerVacuumLogicalVolume,
						      "PMT0_Inner_Vacuum", m_pPMTLogicalVolume, false, 0);

  //------------------------ Quartz window -----------------------
  const G4double dPMTWindowOffsetZ = 0.5*(dPMTWindowThickness-dPMTHeight);

  G4Tubs *pPMTWindow = new G4Tubs("pPMTWindow", 0.*mm, dPMTWindowRadius, dPMTWindowThickness*0.5, 0.*deg, 360.*deg);
  m_pPMTWindowLogicalVolume = new G4LogicalVolume(pPMTWindow, Quartz, "PMTWindowLogicalVolume", 0, 0, 0);
  m_pPMTWindowPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, dPMTWindowOffsetZ), m_pPMTWindowLogicalVolume, 
						 "PMT0_Window", m_pPMTLogicalVolume, false, 0);

  //------------------------ Photocathode ------------------------

  G4Tubs *pPMTPhotocathode = new G4Tubs("pPMTPhotocathode", 0.*mm, dPMTPhotocathodeRadius, dPMTPhotocathodeThickness*0.5, 0.*deg, 360.*deg);
  m_pPMTPhotocathodeLogicalVolume = new G4LogicalVolume(pPMTPhotocathode, PhotoCathodeAluminium, "PMTPhotocathodeLogicalVolume", 0, 0, 0);
  m_pPMTPhotocathodePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, dPMTCutZ0+dPMTPhotocathodeThickness*0.5), m_pPMTPhotocathodeLogicalVolume, 
						       "PMT0_Photocathode", m_pPMTInnerVacuumLogicalVolume, false, 0);


  //------------------------ PMTs Ceramic Stem ------------------------

  dCeramicOffsetZ = (dPMTHeight-dPMTCeramicThickness)*0.5;

  G4Tubs *pPMTCeramic = new G4Tubs("pPMTCeramic", 0.*mm, dPMTCeramicRadius, dPMTCeramicThickness*0.5, 0.*deg, 360.*deg);
  m_PMTCeramicLogicalVolume = new G4LogicalVolume(pPMTCeramic, Ceramic, "CeramicLogicalVolume", 0, 0, 0);
  m_PMTCeramicPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, dCeramicOffsetZ), m_PMTCeramicLogicalVolume,
						 "PMT0_Ceramic_Stem", m_pPMTLogicalVolume, false, 0);


  //------------------------------- PMT sensitivity -------------------------------
  // Cyril
  G4SDManager *pSDManager = G4SDManager::GetSDMpointer(); //ToDo: make proper sensitive detector, check with sensor array and sensitvie det. files
  XebraPmtSensitiveDetector* pPmtSD;

  if(pSDManager->GetCollectionID("PmtHitsCollection")==-1)
     {
       pPmtSD = new XebraPmtSensitiveDetector("Xebra/PmtSD");
       pSDManager->AddNewDetector(pPmtSD);
       m_pPMTPhotocathodeLogicalVolume->SetSensitiveDetector(pPmtSD);
     }
  
  //---------------------------------- attributes ---------------------------------
  
  //   m_pPMTInnerVacuumLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);

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


  return m_pPMTLogicalVolume;
}

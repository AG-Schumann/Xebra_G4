#ifndef XEBRAPMTsR11410_H
#define XEBRAPMTsR11410_H

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


class XebraPMTsR11410
{
public:
  XebraPMTsR11410(XebraConstructTPC*);//XebraDetectorConstruction *
  ~XebraPMTsR11410();

  G4LogicalVolume* Construct();

private:    
  G4double dPMTThickness;
  G4double dPMTHeight;
  G4double dPMTDinodeCutZ;
  G4double dPMTFunnelCutZ;
  G4double dPMTBaseRadius;

  G4double dPMTOuterRadius;
  G4double dPMTOuterRingBottomZ;
  G4double dPMTOuterRingHeight;
  G4double dPMTOuterRingRadius;

  G4double dPMTWindowRadius;
  G4double dPMTWindowThickness;
  G4double dPMTWindowGap;

  G4double dPMTPhotocathodeRadius;
  G4double dPMTPhotocathodeThickness;

  G4double dPMTCeramicRadius;
  G4double dPMTCeramicThickness;
  G4double dCeramicOffsetZ;

  G4LogicalVolume *m_pPMTLogicalVolume;

  G4LogicalVolume *m_pPMTInnerVacuumLogicalVolume;
  G4LogicalVolume *m_pPMTWindowLogicalVolume;
  G4LogicalVolume *m_pPMTPhotocathodeLogicalVolume;
  G4LogicalVolume *m_PMTCeramicLogicalVolume;

  G4VPhysicalVolume *m_pPMTInnerVacuumPhysicalVolume;
  G4VPhysicalVolume *m_pPMTWindowPhysicalVolume;
  G4VPhysicalVolume *m_pPMTPhotocathodePhysicalVolume;
  G4VPhysicalVolume *m_PMTCeramicPhysicalVolume;
};

#endif

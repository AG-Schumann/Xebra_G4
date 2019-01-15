// XENON Header Files
#include "XebraMaterials.hh"

// G4 Header Files
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>

XebraMaterials::XebraMaterials() { ; }

XebraMaterials::~XebraMaterials() { ; }

void XebraMaterials::DefineMaterials() {
    
    G4NistManager *pNistManager = G4NistManager::Instance();
    
    //================================== elements
    //===================================
    pNistManager->FindOrBuildElement("U");
    G4Element *Xe = new G4Element("Xenon", "Xe", 54., 131.293 * g / mole);
    G4Element *H = new G4Element("Hydrogen", "H", 1., 1.0079 * g / mole);
    G4Element *C = new G4Element("Carbon", "C", 6., 12.011 * g / mole);
    G4Element *N = new G4Element("Nitrogen", "N", 7., 14.007 * g / mole);
    G4Element *O = new G4Element("Oxygen", "O", 8., 15.999 * g / mole);
    G4Element *F = new G4Element("Fluorine", "F", 9., 18.998 * g / mole);
    G4Element *Al = new G4Element("Aluminium", "Al", 13., 26.982 * g / mole);
    G4Element *Si = new G4Element("Silicon", "Si", 14., 28.086 * g / mole);
    G4Element *Cr = new G4Element("Chromium", "Cr", 24., 51.996 * g / mole);
    G4Element *Mn = new G4Element("Manganese", "Mn", 25., 54.938 * g / mole);
    G4Element *Fe = new G4Element("Iron", "Fe", 26., 55.85 * g / mole);
    G4Element *Ni = new G4Element("Nickel", "Ni", 28., 58.693 * g / mole);
    G4Element *Cu = new G4Element("Copper", "Cu", 29., 63.546 * g / mole);
    // G4Element *Pb = new G4Element("Lead",      "Pb", 82., 207.2*g/mole);
    G4Element *B = pNistManager->FindOrBuildElement("B");
    G4Element *Gd = pNistManager->FindOrBuildElement("Gd");
    
    double fractionmass;
    int atomnumber;
    // elements for GSRock                                  
    G4Element *Ca = pNistManager->FindOrBuildElement("Ca");
    G4Element *Mg = pNistManager->FindOrBuildElement("Mg");
    
    G4Element *Co = pNistManager->FindOrBuildElement("Co");
    G4Element *Ti = pNistManager->FindOrBuildElement("Ti");
    G4Element *Mo = pNistManager->FindOrBuildElement("Mo");
    // G4Element *Pb = pNistManager->FindOrBuildElement("Pb");
    
    // elements for Concrete                                
    G4Element *Na = pNistManager->FindOrBuildElement("Na");
    G4Element *P = pNistManager->FindOrBuildElement("P");
    G4Element *S = pNistManager->FindOrBuildElement("S");
    G4Element *K = pNistManager->FindOrBuildElement("K");
    
    // added from calibsource
    G4Element *W = pNistManager->FindOrBuildElement("W");
    G4Element *Zr = pNistManager->FindOrBuildElement("Zr");
    G4Element *V = pNistManager->FindOrBuildElement("V");
    G4Isotope *D_Iso = new G4Isotope("D_Iso", 1, 2, 2.014102 * g / mole);
    G4Element *D = new G4Element("Deuterium", "D", 1);
    D->AddIsotope(D_Iso, 1);
    
    //================================== materials
    //==================================
    
    //------------------------------------- air
    //-------------------------------------
    pNistManager->FindOrBuildMaterial("G4_AIR");
    G4Material *Air = G4Material::GetMaterial("G4_AIR");  // moved here by Serena
    
    //----------------------------------- vacuum
    //------------------------------------
    G4Material *Vacuum = new G4Material("Vacuum", 1.e-20 * g / cm3, 2, kStateGas);
    Vacuum->AddElement(N, 0.755);
    Vacuum->AddElement(O, 0.245);
    
    //------------------------------------ water ------------------------
    G4Material *Water = new G4Material("Water", 1. * g / cm3, 2, kStateLiquid);
    Water->AddElement(H, 2);
    Water->AddElement(O, 1);
    
    //-------------------------------------G4 Aluminium
    //-------------------------------------
    pNistManager->FindOrBuildMaterial("G4_Al");
    
    //------------------------------------- G4 Molybdenum
    //-------------------------------------
    pNistManager->FindOrBuildMaterial("G4_Mo");
    
    //------------------------------------- G4 Lead
    //-------------------------------------
    pNistManager->FindOrBuildMaterial("G4_Pb");
    
    //------------------------------------- G4 Copper
    //-------------------------------------
    pNistManager->FindOrBuildMaterial("G4_Cu");
    
    //---------------------------PVC Pipe----------------------------------------
    pNistManager->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
    
    //----------------------------CollimatorAlloy-------------------------------
    G4Material *CollimatorAlloy =
    new G4Material("CollimatorAlloy", 19.25 * g / cm3, 3, kStateSolid);
    CollimatorAlloy->AddElement(W, fractionmass = 95.00 * perCent);
    CollimatorAlloy->AddElement(Ni, fractionmass = 3.50 * perCent);
    CollimatorAlloy->AddElement(Cu, fractionmass = 1.50 * perCent);
    
    //------------------------------------- steel
    //-------------------------------------
    
    G4String name;
    G4int ncomponents;
    G4double density;
    G4Material *Steel =
    new G4Material(name = "Steel", density = 7.7 * g / cm3, ncomponents = 3);
    Steel->AddElement(C, 0.04);
    Steel->AddElement(Fe, 0.88);
    Steel->AddElement(Co, 0.08);
    
    //------------------------------------ low-density polyurethane foam
    //--------------    DR 20160824
    G4Material *Foam =
    new G4Material("Foam", 0.032 * g / cm3, 4, kStateSolid);  // 2*lb/ft^3
    Foam->AddElement(C, 25);
    Foam->AddElement(H, 42);
    Foam->AddElement(N, 2);
    Foam->AddElement(O, 6);
    
    //---------------------------------------------------------------------------------
    //------------------------------------ liquid scintillator
    //------------------------
    //---------------------------------------------------------------------------------
    // DR 20160824 - Reference: Daya Bay
    // (http://dx.doi.org/10.1016/j.nima.2014.05.119)
    
    G4Material *LAB = new G4Material("LAB", 0.863 * g / cm3, 2, kStateLiquid);
    LAB->AddElement(C, 18);
    LAB->AddElement(H,
                    30);  // C(6)H(5)C(n)H(2n+1) - 'n' typically equal to 10-13.
    // 12 chosen for this case.
    
    G4Material *PPO = new G4Material("PPO", 0.882 * g / cm3, 4, kStateSolid);
    PPO->AddElement(C, 15);
    PPO->AddElement(H, 11);
    PPO->AddElement(N, 1);
    PPO->AddElement(O, 1);
    
    G4Material *LScint =
    new G4Material("LScint", 0.863 * g / cm3, 2, kStateLiquid);
    LScint->AddMaterial(LAB, 0.99654);
    LScint->AddMaterial(PPO, 0.00346);
    // Negligible contribution from bis-MSB
    LScint->GetIonisation()->SetBirksConstant(0.117 * mm / MeV);
    
    G4Material *Gd_carboxylate =
    new G4Material("Gd_carboxylate", 2.42 * g / cm3, 4, kStateSolid);
    Gd_carboxylate->AddElement(Gd, 1);
    Gd_carboxylate->AddElement(H, 51);
    Gd_carboxylate->AddElement(C, 27);
    Gd_carboxylate->AddElement(O, 6);
    
    G4Material *Gd_LScint = new G4Material("Gd_LScint", 0.863 * g / cm3, 2,
                                           kStateLiquid);  // Gd-doped
    Gd_LScint->AddMaterial(LScint, 0.996006);
    Gd_LScint->AddMaterial(Gd_carboxylate,
                           0.003994);  // Makes 0.1% of Gd in mass.
    Gd_LScint->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);
    
    G4Material *Gd_LScint_0_2 = new G4Material("Gd_LScint_0_2", 0.863 * g / cm3,
                                               2, kStateLiquid);  // Gd-doped
    Gd_LScint_0_2->AddMaterial(LScint, 0.992011);
    Gd_LScint_0_2->AddMaterial(Gd_carboxylate,
                               0.007989);  // Makes 0.2% of Gd in mass.
    Gd_LScint_0_2->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);
    
    G4Material *Gd_LScint_0_4 = new G4Material("Gd_LScint_0_4", 0.863 * g / cm3,
                                               2, kStateLiquid);  // Gd-doped
    Gd_LScint_0_4->AddMaterial(LScint, 0.984023);
    Gd_LScint_0_4->AddMaterial(Gd_carboxylate,
                               0.015977);  // Makes 0.4% of Gd in mass.
    Gd_LScint_0_4->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);
    
    G4Material *Gd_LScint_0_8 = new G4Material("Gd_LScint_0_8", 0.863 * g / cm3,
                                               2, kStateLiquid);  // Gd-doped
    Gd_LScint_0_8->AddMaterial(LScint, 0.968046);
    Gd_LScint_0_8->AddMaterial(Gd_carboxylate,
                               0.031954);  // Makes 0.8% of Gd in mass.
    Gd_LScint_0_8->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);
    
    // DR 20160623 - Printing the contents of the "pGdLScintPropertiesTable" array
    // G4MaterialPropertiesTable *pGdLScintPropertiesTable =
    // Gd_LScint->GetMaterialPropertiesTable();
    // G4cout << " test " << pGdLScintPropertiesTable << G4endl;
    
    //---------------------------------------------------
    //-- DR 20160824 - Gd_LScint optical properties table
    //---------------------------------------------------
    const G4int iNbEntries = 3;
    
    G4double pdGdLScintPhotonMomentum[iNbEntries] = {2.59 * eV, 2.88 * eV,
        3.17 * eV};
    G4double pdGdLScintScintillation[iNbEntries] = {0.1, 1.0, 0.1};
    G4double pdGdLScintRefractiveIndex[iNbEntries] = {1.5, 1.5, 1.49};
    G4double pdGdLScintAbsorbtionLength[iNbEntries] = {
        30. * m, 30. * m, 30. * m};  // With L_att = 14.5m
    G4double pdGdLScintScatteringLength[iNbEntries] = {27. * m, 27. * m, 27. * m};
    
    G4MaterialPropertiesTable *pGdLScintPropertiesTable =
    new G4MaterialPropertiesTable();
    
    pGdLScintPropertiesTable->AddProperty("FASTCOMPONENT",
                                          pdGdLScintPhotonMomentum,
                                          pdGdLScintScintillation, iNbEntries);
    pGdLScintPropertiesTable->AddProperty("SLOWCOMPONENT",
                                          pdGdLScintPhotonMomentum,
                                          pdGdLScintScintillation, iNbEntries);
    pGdLScintPropertiesTable->AddProperty("RINDEX", pdGdLScintPhotonMomentum,
                                          pdGdLScintRefractiveIndex, iNbEntries);
    pGdLScintPropertiesTable->AddProperty("ABSLENGTH", pdGdLScintPhotonMomentum,
                                          pdGdLScintAbsorbtionLength, iNbEntries);
    pGdLScintPropertiesTable->AddProperty("RAYLEIGH", pdGdLScintPhotonMomentum,
                                          pdGdLScintScatteringLength, iNbEntries);
    
    pGdLScintPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / keV);
    pGdLScintPropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
    pGdLScintPropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
    pGdLScintPropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
    pGdLScintPropertiesTable->AddConstProperty("YIELDRATIO", 1.0);
    
    Gd_LScint->SetMaterialPropertiesTable(pGdLScintPropertiesTable);
    //---------------------------------------------------
    
    //------------------------------------ liquid scintillator
    //(Borexino)------------------------
    G4Material *PC = new G4Material("PC", 0.882 * g / cm3, 2, kStateLiquid);
    PC->AddElement(C, 9);
    PC->AddElement(H, 12);
    
    G4Material *B_LScint =
    new G4Material("B_LScint", 0.882 * g / cm3, 2, kStateLiquid);  // B-doped
    B_LScint->AddMaterial(LScint, 0.999);
    B_LScint->AddElement(B, 0.001);
    
    /// implement scintillation properties
    
    //-------------------------------- liquid xenon
    //---------------------------------
    //    G4Material *LXe = new G4Material("LXe", 2.9172*g/cm3, 1, kStateLiquid,
    // 168.15*kelvin, 1.5*atmosphere);
    G4Material *LXe = new G4Material("LXe", 2.85 * g / cm3, 1, kStateLiquid,
                                     168.15 * kelvin, 1.5 * atmosphere);
    LXe->AddElement(Xe, 1);
    
    G4double pdLXePhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV, 7.05 * eV}; //178nm
    G4double pdLXeScintillation[iNbEntries] = {0.1, 1.0, 0.1};
    G4double pdLXeRefractiveIndex[iNbEntries] = {1.63, 1.61, 1.58};
    // G4double pdLXeRefractiveIndex[iNbEntries]  = {1.56,    1.56,    1.56};
    // G4double pdLXeRefractiveIndex[iNbEntries]  = {1.69,    1.69,    1.69};
    G4double pdLXeAbsorbtionLength[iNbEntries] = {100. * cm, 100. * cm,
        100. * cm};
    G4double pdLXeScatteringLength[iNbEntries] = {30. * cm, 30. * cm, 30. * cm};
    
    G4MaterialPropertiesTable *pLXePropertiesTable =
    new G4MaterialPropertiesTable();
    
    pLXePropertiesTable->AddProperty("FASTCOMPONENT", pdLXePhotonMomentum,
                                     pdLXeScintillation, iNbEntries);
    pLXePropertiesTable->AddProperty("SLOWCOMPONENT", pdLXePhotonMomentum,
                                     pdLXeScintillation, iNbEntries);
    pLXePropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum,
                                     pdLXeRefractiveIndex, iNbEntries);
    pLXePropertiesTable->AddProperty("ABSLENGTH", pdLXePhotonMomentum,
                                     pdLXeAbsorbtionLength, iNbEntries);
    pLXePropertiesTable->AddProperty("RAYLEIGH", pdLXePhotonMomentum,
                                     pdLXeScatteringLength, iNbEntries);
    
    pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / keV);
    pLXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
    pLXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
    pLXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
    pLXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);//ratio btw fast time constant and slow time constant
    
#ifdef USENEST
    // NEST
    pLXePropertiesTable->AddConstProperty(
                                          "ELECTRICFIELD", 0 * volt / cm);  // for missed nooks and crannies //NEST
    pLXePropertiesTable->AddConstProperty("ELECTRICFIELDSURFACE",
                                          0 * volt / cm);  // NEST
    //pLXePropertiesTable->AddConstProperty("ELECTRICFIELDGATE", pLXeElectricField);  // NEST
    pLXePropertiesTable->AddConstProperty("ELECTRICFIELDGATE", 0 * volt / cm);  // NEST
    
    pLXePropertiesTable->AddConstProperty("ELECTRICFIELDCATHODE",
                                          0 * volt / cm);  // NEST
    pLXePropertiesTable->AddConstProperty("ELECTRICFIELDBOTTOM",
                                          0 * volt / cm);             // NEST
    pLXePropertiesTable->AddConstProperty("TOTALNUM_INT_SITES", -1);  // NEST
#endif
    
    pLXePropertiesTable->AddConstProperty(
                                          "TOTALNUM_INT_SITES",
                                          -1);  //// initialize the number of interaction sites
    
    //______________________________________________________________________________//
    
    LXe->SetMaterialPropertiesTable(pLXePropertiesTable);
    
    //-------------------------------- gaseous xenon
    //--------------------------------
    G4Material *GXe = new G4Material("GXe", 0.005887 * g / cm3, 1, kStateGas,
                                     173.15 * kelvin, 1.5 * atmosphere); //ToDo: check density
    GXe->AddElement(Xe, 1);
    
    G4double pdGXePhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double pdGXeScintillation[iNbEntries] = {0.1, 1.0, 0.1};
    G4double pdGXeRefractiveIndex[iNbEntries] = {1.00, 1.00, 1.00};
    G4double pdGXeAbsorbtionLength[iNbEntries] = {100 * m, 100 * m, 100 * m};
    G4double pdGXeScatteringLength[iNbEntries] = {100 * m, 100 * m, 100 * m};
    
    G4MaterialPropertiesTable *pGXePropertiesTable =
    new G4MaterialPropertiesTable();
    
    pGXePropertiesTable->AddProperty("FASTCOMPONENT", pdGXePhotonMomentum,
                                     pdGXeScintillation, iNbEntries);
    pGXePropertiesTable->AddProperty("SLOWCOMPONENT", pdGXePhotonMomentum,
                                     pdGXeScintillation, iNbEntries);
    pGXePropertiesTable->AddProperty("RINDEX", pdGXePhotonMomentum,
                                     pdGXeRefractiveIndex, iNbEntries);
    pGXePropertiesTable->AddProperty("ABSLENGTH", pdGXePhotonMomentum,
                                     pdGXeAbsorbtionLength, iNbEntries);
    pGXePropertiesTable->AddProperty("RAYLEIGH", pdGXePhotonMomentum,
                                     pdGXeScatteringLength, iNbEntries);
    
    pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / (keV));
    pGXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
    pGXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
    pGXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
    pGXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);
    
#ifdef USENEST
    // NEST
    //pGXePropertiesTable->AddConstProperty("ELECTRICFIELD", pGXeElectricField);  // for missed nooks and crannies  //NEST
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELD", 0 * volt / cm);  // for missed nooks and crannies  //NEST

    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDWINDOW",
                                          0 * volt / cm);  // NEST
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDTOP",
                                          0 * volt / cm);  // NEST
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDANODE",
                                          0 * volt / cm);  // NEST
    
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDSURFACE",
                                          0 * volt / cm);  // NEST PATCH
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDGATE",
                                          0 * volt / cm);  // NEST PATCH
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDCATHODE",
                                          0 * volt / cm);  // NEST PATCH
    pGXePropertiesTable->AddConstProperty("ELECTRICFIELDBOTTOM",
                                          0 * volt / cm);  // NEST PATCH
    pGXePropertiesTable->AddConstProperty("TOTALNUM_INT_SITES",
                                          -1);  // NEST PATCH
#endif
    
    GXe->SetMaterialPropertiesTable(pGXePropertiesTable);
    
    //----------------------------------- quartz
    //------------------------------------
    // ref: http://www.sciner.com/Opticsland/FS.htm
    G4Material *Quartz = new G4Material("Quartz", 2.201 * g / cm3, 2, kStateSolid,
                                        168.15 * kelvin, 1.5 * atmosphere);
    Quartz->AddElement(Si, 1);
    Quartz->AddElement(O, 2);
    
    const G4int iNbEntriesMatch = 5;
    //    G4double pdQuartzPhotonMomentum[iNbEntriesMatch]   = {2.*eV, 6.9*eV,
    // 6.91*eV, 6.98*eV, 7.05*eV}; // Serena's comment!!!
    G4double pdQuartzPhotonMomentum[iNbEntriesMatch] = {
        1. * eV, 6.9 * eV, 6.91 * eV, 6.98 * eV,
        7.05 * eV};  // SERENA: changed  2.*eV to 1.*eV otherwise it gets stuck
    // "Out of Range - Attempt to retrieve information below
    // range!"
    G4double pdQuartzRefractiveIndex[iNbEntriesMatch] = {1.50, 1.50, 1.50, 1.56,
        1.60};
    // G4double pdQuartzRefractiveIndex[iNbEntriesMatch]  = { 1.59,   1.59,
    // 1.59,    1.59,    1.59};
    G4double pdQuartzAbsorbtionLength[iNbEntriesMatch] = {30 * m, 30 * m, 30 * m,
        30 * m, 30 * m};
    
    G4MaterialPropertiesTable *pQuartzPropertiesTable =
    new G4MaterialPropertiesTable();
    
    pQuartzPropertiesTable->AddProperty("RINDEX", pdQuartzPhotonMomentum,
                                        pdQuartzRefractiveIndex, iNbEntriesMatch);
    pQuartzPropertiesTable->AddProperty("ABSLENGTH", pdQuartzPhotonMomentum,
                                        pdQuartzAbsorbtionLength,
                                        iNbEntriesMatch);
    
    Quartz->SetMaterialPropertiesTable(pQuartzPropertiesTable);
    
    //------------------------------------ Kovar
    //-----------------------------------  ( added by RINO  6 June 2012)
    G4Material *Kovar = new G4Material("Kovar", 8.33 * g / cm3, 6, kStateSolid);
    Kovar->AddElement(Fe, 0.5358);
    Kovar->AddElement(Ni, 0.29);
    Kovar->AddElement(Co, 0.17);
    Kovar->AddElement(C, 0.0002);
    Kovar->AddElement(Si, 0.001);
    Kovar->AddElement(Mn, 0.003);
    
    //   G4MaterialPropertiesTable *pKovarPropertiesTable = new
    //   G4MaterialPropertiesTable();
    
    //   G4double pdKovarPhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
    //   G4double pdKovarReflectivity[iNbEntries]   = {0.15,    0.2,     0.15};///
    //   check
    
    //   pKovarPropertiesTable->AddProperty("REFLECTIVITY", pdKovarPhotonMomentum,
    //   pdKovarReflectivity, iNbEntries);
    
    //   Kovar->SetMaterialPropertiesTable(pKovarPropertiesTable);
    
    //------------------------- cirlex ------------------------   ( added by RINO
    // 6 June 2012)
    // imported from Xe100 code
    
    G4Material *Cirlex = new G4Material("Cirlex", 1.43 * g / cm3, 4, kStateSolid); //PMT base material
    Cirlex->AddElement(C, 22);
    Cirlex->AddElement(H, 10);
    Cirlex->AddElement(N, 2);
    Cirlex->AddElement(O, 5);
    
    G4double pdCirlexPhotonMomentum[]  = {6.91*eV, 6.98*eV, 7.05*eV};
    G4double pdCirlexReflectivity[]   = {0.5,    0.5,     0.5};
    
    G4MaterialPropertiesTable *pCirlexPropertiesTable = new G4MaterialPropertiesTable();
    
    pCirlexPropertiesTable->AddProperty("REFLECTIVITY", pdCirlexPhotonMomentum, pdCirlexReflectivity, iNbEntries);
    Cirlex->SetMaterialPropertiesTable(pCirlexPropertiesTable);
    
    //------------------------------- stainless steel
    //-------------------------------
    G4Material *SS304LSteel = new G4Material("SS304LSteel", 8.00 * g / cm3, 5, kStateSolid);
    SS304LSteel->AddElement(Fe, 0.65);
    SS304LSteel->AddElement(Cr, 0.20);
    SS304LSteel->AddElement(Ni, 0.12);
    SS304LSteel->AddElement(Mn, 0.02);
    SS304LSteel->AddElement(Si, 0.01);
    
     G4double pdSteelPhotonMomentum[] = {6.91*eV, 6.98*eV, 7.05*eV};
     G4double pdSteelReflectivity[]   = {0.15,    0.2,     0.15};
     G4MaterialPropertiesTable *pSteelPropertiesTable = new G4MaterialPropertiesTable();
     
     pSteelPropertiesTable->AddProperty("REFLECTIVITY", pdSteelPhotonMomentum,pdSteelReflectivity, iNbEntries);
     SS304LSteel->SetMaterialPropertiesTable(pSteelPropertiesTable);

		//------------------------------- stainless steel -------------------------------
		G4Material *SS316LSteel = new G4Material("SS316LSteel", 8.00*g/cm3, 6, kStateSolid);
		SS316LSteel->AddElement(Fe, 0.682);
		SS316LSteel->AddElement(Cr, 0.172);
		SS316LSteel->AddElement(Ni, 0.109);
		SS316LSteel->AddElement(Mn, 0.016);
		SS316LSteel->AddElement(C, 0.0002);
		SS316LSteel->AddElement(Mo, 0.021);

		//As defined above:
		//G4double pdSteelPhotonMomentum[] = {6.91*eV, 6.98*eV, 7.05*eV};
		//G4double pdSteelReflectivity[]   = {0.15,    0.2,     0.15};
		//G4MaterialPropertiesTable *pSteelPropertiesTable = new G4MaterialPropertiesTable();

		pSteelPropertiesTable->AddProperty("REFLECTIVITY", pdSteelPhotonMomentum, pdSteelReflectivity, iNbEntries);
		SS316LSteel->SetMaterialPropertiesTable(pSteelPropertiesTable);
     
    
    // ****** BY AUKE-PC ******
    // --------------------------------------------------------
    
    //
    // AISI 316Ti steel / UNS S 31635
    //
    // 1. Take the maximum specified fraction of each component.
    //    See http://www.atimetals.com/ludlum/Documents/316ti.pdf
    // 2. Leave out tracer elements <0.05% of Phosphor and Sulphur (justifiable?)
    //
    // A.P. Colijn 26-07-2011
    //
    // G4double fractionmass;
    G4int ncomponent;
    G4Material *SS316Ti =
    new G4Material("SS316Ti", 8.00 * g / cm3, ncomponent = 8, kStateSolid);
    SS316Ti->AddElement(Cr, fractionmass = 18.00 * perCent);
    SS316Ti->AddElement(Ni, fractionmass = 14.00 * perCent);
    SS316Ti->AddElement(Mo, fractionmass = 3.00 * perCent);
    SS316Ti->AddElement(Mn, fractionmass = 2.00 * perCent);
    SS316Ti->AddElement(C, fractionmass = 0.80 * perCent);
    SS316Ti->AddElement(Si, fractionmass = 0.75 * perCent);
    SS316Ti->AddElement(Ti, fractionmass = 0.70 * perCent);
    SS316Ti->AddElement(Fe, fractionmass = 60.75 * perCent);
    
    //------------------------------Polyethylene---------------------------------
    G4Material *Polyethylene =
    new G4Material("Polyethylene", .925 * g / cm3, 2, kStateSolid);
    Polyethylene->AddElement(H, atomnumber = 4);
    Polyethylene->AddElement(C, atomnumber = 2);
    
    //---------------------------------Delrin------------------------------------
    G4Material *Delrin =
    new G4Material("Delrin", 1.415 * g / cm3, 3, kStateSolid);
    Delrin->AddElement(C, atomnumber = 1);
    Delrin->AddElement(H, atomnumber = 2);
    Delrin->AddElement(O, atomnumber = 1);
    
    //-------------------------------Plexiglass----------------------------------
    pNistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
    
    //----------------------------1.4571 NiCrSteel-------------------------------
    // List of fractions by mass obtained from datasheets
    G4Material *NiCrSteel =
    new G4Material("NiCrSteel", 8. * g / cm3, 10, kStateSolid);
    NiCrSteel->AddElement(Fe, fractionmass = 0.5811);
    NiCrSteel->AddElement(C, fractionmass = 0.0008);
    NiCrSteel->AddElement(Si, fractionmass = 0.01);
    NiCrSteel->AddElement(Mn, fractionmass = 0.02);
    NiCrSteel->AddElement(P, fractionmass = 0.00045);
    NiCrSteel->AddElement(S, fractionmass = 0.00015);
    NiCrSteel->AddElement(Cr, fractionmass = 0.175);
    NiCrSteel->AddElement(Mo, fractionmass = 0.0225);
    NiCrSteel->AddElement(Ni, fractionmass = 0.12);
    NiCrSteel->AddElement(Ti, fractionmass = 0.070);
    
    //------------------------------- titanium alloys
    //-------------------------------
    
    // 1. Titanium grade1: UNS R50250; ASTM Grade 1
    //    See http://asm.matweb.com/search/SpecificMaterial.asp?bassnum=MTU010
    // 2. Maximum specified fraction for each component
    //
    // A.P. Colijn 26-07-2011
    //
    G4Material *TiGrade1 =
    new G4Material("TiGrade1", 4.51 * g / cm3, ncomponent = 6, kStateSolid);
    TiGrade1->AddElement(C, fractionmass = 0.10 * perCent);
    TiGrade1->AddElement(Fe, fractionmass = 0.20 * perCent);
    TiGrade1->AddElement(H, fractionmass = 0.015 * perCent);
    TiGrade1->AddElement(N, fractionmass = 0.03 * perCent);
    TiGrade1->AddElement(O, fractionmass = 0.18 * perCent);
    TiGrade1->AddElement(Ti, fractionmass = 99.475 * perCent);
    
    // As far as Geant4 is concerned grade1 and grade2 identical I would
    // think.....
    
    // 1. Titanium grade2: UNS R50400; ASTM Grade 2
    //    See http://asm.matweb.com/search/SpecificMaterial.asp?bassnum=MTU020
    // 2. Maximum specified fraction for each component
    //
    // A.P. Colijn 26-07-2011
    //
    G4Material *TiGrade2 =
    new G4Material("TiGrade2", 4.51 * g / cm3, ncomponent = 6, kStateSolid);
    TiGrade2->AddElement(C, fractionmass = 0.10 * perCent);
    TiGrade2->AddElement(Fe, fractionmass = 0.30 * perCent);
    TiGrade2->AddElement(H, fractionmass = 0.015 * perCent);
    TiGrade2->AddElement(N, fractionmass = 0.03 * perCent);
    TiGrade2->AddElement(O, fractionmass = 0.25 * perCent);
    TiGrade2->AddElement(Ti, fractionmass = 99.305 * perCent);
    
    // ****** END AUKE-PC PIECE ******
    // --------------------------------------------------------
    
    //------------------------------------ Torlon
    //-----------------------------------
    
    G4Material *Torlon = new G4Material("Torlon", 1.41 * g / cm3, 4, kStateSolid);
    Torlon->AddElement(N, 0.07862);
    Torlon->AddElement(C, 0.70784);
    Torlon->AddElement(O, 0.17960);
    Torlon->AddElement(H, 0.03394);
    
    //---------------------------- photocathode aluminium
    //---------------------------
    G4Material *PhotoCathodeAluminium =
    new G4Material("PhotoCathodeAluminium", 8.00 * g / cm3, 1, kStateSolid);
    PhotoCathodeAluminium->AddElement(Al, 1);
    
    // G4double pdPhotoCathodePhotonMomentum[]   = {2.*eV, 6.9*eV, 6.91*eV,
    // 6.98*eV, 7.05*eV};    // Serena's comment!!!
    G4double pdPhotoCathodePhotonMomentum[] = {
        1. * eV, 6.9 * eV, 6.91 * eV, 6.98 * eV,
        7.05 * eV};  // SERENA: changed  2.*eV to 1.*eV otherwise it gets stuck
    // "Out of Range - Attempt to retrieve information below
    // range!"
    G4double pdPhotoCathodeRefractiveIndex[] = {1.50, 1.50, 1.50, 1.56, 1.60};
    G4double pdPhotoCathodeAbsorbtionLength[] = {1. * nm, 1 * nm, 1. * nm,
        1. * nm, 1. * nm};
    G4MaterialPropertiesTable *pPhotoCathodePropertiesTable =
    new G4MaterialPropertiesTable();
    
    pPhotoCathodePropertiesTable->AddProperty(
                                              "RINDEX", pdPhotoCathodePhotonMomentum, pdPhotoCathodeRefractiveIndex,
                                              iNbEntriesMatch);
    pPhotoCathodePropertiesTable->AddProperty(
                                              "ABSLENGTH", pdPhotoCathodePhotonMomentum, pdPhotoCathodeAbsorbtionLength,
                                              iNbEntriesMatch);
    
    PhotoCathodeAluminium->SetMaterialPropertiesTable(
                                                      pPhotoCathodePropertiesTable);
    
    //---------------------------- QUPID aluminium
    // coating---------------------------
    G4Material *CoatingAluminium =
    new G4Material("CoatingAluminium", 2.7 * g / cm3, 1, kStateSolid);
    CoatingAluminium->AddElement(Al, 1);
    
    G4double pdCoatingAluminiumPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
        7.05 * eV};
    G4double pdCoatingAluminiumReflectivity[iNbEntries] = {0.15, 0.2,
        0.15};  /// check
    G4MaterialPropertiesTable *pCoatingAluminiumPropertiesTable =
    new G4MaterialPropertiesTable();
    
    pCoatingAluminiumPropertiesTable->AddProperty(
                                                  "REFLECTIVITY", pdCoatingAluminiumPhotonMomentum,
                                                  pdCoatingAluminiumReflectivity, iNbEntries);
    CoatingAluminium->SetMaterialPropertiesTable(
                                                 pCoatingAluminiumPropertiesTable);
    
    //----------------------------- grid mesh
    // aluminium------------------------------
    G4Material *GridMeshAluminium =
    new G4Material("GridMeshAluminium", 0.174 * g / cm3, 1, kStateSolid);
    GridMeshAluminium->AddElement(Al, 1);
    
    G4double pdGridMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double *pdGridMeshRefractiveIndex = pdLXeRefractiveIndex;
    // G4double dAbsortionLength = 2.10*mm; // exp(-GridMeshThickness/2.10) = 0.94
    // : works with thickness 0f 0.13 mm
    G4double dAbsortionLength =
    3.2323021424 * mm;  // exp(-GridMeshThickness/dAbsortionLength) = 0.94,
    // with thickness of 0.2mm
    // G4double dAbsortionLength = 6.5661590*mm; //
    // exp(-GridMeshThickness/dAbsortionLength) = 0.97, with thickness of 0.2mm
    G4double pdGridMeshAbsortionLength[] = {dAbsortionLength, dAbsortionLength,
        dAbsortionLength};
    
    G4MaterialPropertiesTable *pGridMeshPropertiesTable =
    new G4MaterialPropertiesTable();
    
    pGridMeshPropertiesTable->AddProperty("RINDEX", pdGridMeshPhotonMomentum,
                                          pdGridMeshRefractiveIndex, iNbEntries);
    pGridMeshPropertiesTable->AddProperty("ABSLENGTH", pdGridMeshPhotonMomentum,
                                          pdGridMeshAbsortionLength, iNbEntries);
    GridMeshAluminium->SetMaterialPropertiesTable(pGridMeshPropertiesTable);
    
    //
    // Treating every grid with different transparency. Cyril, June 2014
    //
    
    //----------------------------- top screening mesh
    //------------------------------
    G4Material *TopScreeningMesh =
    new G4Material("TopScreeningMesh", 0.48 * g / cm3, 1, kStateSolid);
    TopScreeningMesh->AddMaterial(SS316Ti,
                                  1);  // density is (100.-94.)/100. * 8.g/cm3
    G4double pdTopScreeningMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV,
        7.05 * eV};
    G4double *pdTopScreeningMeshRefractiveIndex = pdGXeRefractiveIndex;
    G4double dTopScreeningMeshAbsortionLength =
    3.2323021424 * mm;  // exp(-TopScreeningMeshThickness/dAbsortionLength) =
    // 0.94, with thickness of 0.2mm
    G4double pdTopScreeningMeshAbsortionLength[] = {
        dTopScreeningMeshAbsortionLength, dTopScreeningMeshAbsortionLength,
        dTopScreeningMeshAbsortionLength};
    G4MaterialPropertiesTable *pTopScreeningMeshPropertiesTable =
    new G4MaterialPropertiesTable();
    pTopScreeningMeshPropertiesTable->AddProperty(
                                                  "RINDEX", pdTopScreeningMeshPhotonMomentum,
                                                  pdTopScreeningMeshRefractiveIndex, iNbEntries);
    pTopScreeningMeshPropertiesTable->AddProperty(
                                                  "ABSLENGTH", pdTopScreeningMeshPhotonMomentum,
                                                  pdTopScreeningMeshAbsortionLength, iNbEntries);
    TopScreeningMesh->SetMaterialPropertiesTable(
                                                 pTopScreeningMeshPropertiesTable);
    
    //----------------------------- bottom screening mesh
    //------------------------------
    G4Material *BottomScreeningMesh =
    new G4Material("BottomScreeningMesh", 0.48 * g / cm3, 1, kStateSolid);
    BottomScreeningMesh->AddMaterial(SS316Ti, 1);
    G4double pdBottomScreeningMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV,
        7.05 * eV};
    G4double *pdBottomScreeningMeshRefractiveIndex = pdLXeRefractiveIndex;
    G4double dBottomScreeningMeshAbsortionLength =
    3.2323021424 * mm;  // exp(-BottomScreeningMeshThickness/dAbsortionLength)
    // = 0.94, with thickness of 0.2mm
    G4double pdBottomScreeningMeshAbsortionLength[] = {
        dBottomScreeningMeshAbsortionLength, dBottomScreeningMeshAbsortionLength,
        dBottomScreeningMeshAbsortionLength};
    G4MaterialPropertiesTable *pBottomScreeningMeshPropertiesTable =
    new G4MaterialPropertiesTable();
    pBottomScreeningMeshPropertiesTable->AddProperty(
                                                     "RINDEX", pdBottomScreeningMeshPhotonMomentum,
                                                     pdBottomScreeningMeshRefractiveIndex, iNbEntries);
    pBottomScreeningMeshPropertiesTable->AddProperty(
                                                     "ABSLENGTH", pdBottomScreeningMeshPhotonMomentum,
                                                     pdBottomScreeningMeshAbsortionLength, iNbEntries);
    BottomScreeningMesh->SetMaterialPropertiesTable(
                                                    pBottomScreeningMeshPropertiesTable);
    
    //----------------------------- cathode mesh ------------------------------
    G4Material *CathodeMesh =
    new G4Material("CathodeMesh", 0.48 * g / cm3, 1, kStateSolid);
    CathodeMesh->AddMaterial(SS316Ti, 1);
    G4double pdCathodeMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double *pdCathodeMeshRefractiveIndex = pdLXeRefractiveIndex;
    G4double dCathodeMeshAbsortionLength =
    3.2323021424 * mm;  // exp(-CathodeMeshThickness/dAbsortionLength) = 0.94,
    // with thickness of 0.2mm
    G4double pdCathodeMeshAbsortionLength[] = {dCathodeMeshAbsortionLength,
        dCathodeMeshAbsortionLength,
        dCathodeMeshAbsortionLength};
    G4MaterialPropertiesTable *pCathodeMeshPropertiesTable =
    new G4MaterialPropertiesTable();
    pCathodeMeshPropertiesTable->AddProperty(
                                             "RINDEX", pdCathodeMeshPhotonMomentum, pdCathodeMeshRefractiveIndex,
                                             iNbEntries);
    pCathodeMeshPropertiesTable->AddProperty(
                                             "ABSLENGTH", pdCathodeMeshPhotonMomentum, pdCathodeMeshAbsortionLength,
                                             iNbEntries);
    CathodeMesh->SetMaterialPropertiesTable(pCathodeMeshPropertiesTable);
    
    //----------------------------- anode mesh ------------------------------
    G4Material *AnodeMesh =
    new G4Material("AnodeMesh", 0.48 * g / cm3, 1, kStateSolid);
    AnodeMesh->AddMaterial(SS316Ti, 1);
    G4double pdAnodeMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double *pdAnodeMeshRefractiveIndex = pdGXeRefractiveIndex;
    G4double dAnodeMeshAbsortionLength =
    3.2323021424 * mm;  // exp(-AnodeMeshThickness/dAbsortionLength) = 0.94,
    // with thickness of 0.2mm
    G4double pdAnodeMeshAbsortionLength[] = {dAnodeMeshAbsortionLength,
        dAnodeMeshAbsortionLength,
        dAnodeMeshAbsortionLength};
    G4MaterialPropertiesTable *pAnodeMeshPropertiesTable =
    new G4MaterialPropertiesTable();
    pAnodeMeshPropertiesTable->AddProperty("RINDEX", pdAnodeMeshPhotonMomentum,
                                           pdAnodeMeshRefractiveIndex,
                                           iNbEntries);
    pAnodeMeshPropertiesTable->AddProperty("ABSLENGTH", pdAnodeMeshPhotonMomentum,
                                           pdAnodeMeshAbsortionLength,
                                           iNbEntries);
    AnodeMesh->SetMaterialPropertiesTable(pAnodeMeshPropertiesTable);
    
    //----------------------------- gate mesh ------------------------------
    G4Material *GateMesh =
    new G4Material("GateMesh", 0.48 * g / cm3, 1, kStateSolid);
    GateMesh->AddMaterial(SS316Ti, 1);
    G4double pdGateMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double *pdGateMeshRefractiveIndex = pdLXeRefractiveIndex;
    G4double dGateMeshAbsortionLength =
    3.2323021424 * mm;  // exp(-GateMeshThickness/dAbsortionLength) = 0.94,
    // with thickness of 0.2mm
    G4double pdGateMeshAbsortionLength[] = {dGateMeshAbsortionLength,
        dGateMeshAbsortionLength,
        dGateMeshAbsortionLength};
    G4MaterialPropertiesTable *pGateMeshPropertiesTable =
    new G4MaterialPropertiesTable();
    pGateMeshPropertiesTable->AddProperty("RINDEX", pdGateMeshPhotonMomentum,
                                          pdGateMeshRefractiveIndex, iNbEntries);
    pGateMeshPropertiesTable->AddProperty("ABSLENGTH", pdGateMeshPhotonMomentum,
                                          pdGateMeshAbsortionLength, iNbEntries);
    GateMesh->SetMaterialPropertiesTable(pGateMeshPropertiesTable);
    
    //------------------------------------ teflon
    //-----------------------------------
    G4Material *Teflon = new G4Material("Teflon", 2.2 * g / cm3, 2, kStateSolid);
    Teflon->AddElement(C, 0.240183);
    Teflon->AddElement(F, 0.759817);
    
    G4double pdTeflonPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double pdTeflonRefractiveIndex[iNbEntries] = {1.63, 1.61, 1.58};
    G4double pdTeflonReflectivity[iNbEntries] = {0.99, 0.99, 0.99};
    G4double pdTeflonSpecularLobe[iNbEntries] = {0.01, 0.01, 0.01};
    G4double pdTeflonSpecularSpike[iNbEntries] = {0.01, 0.01, 0.01};
    G4double pdTeflonBackscatter[iNbEntries] = {0.01, 0.01, 0.01};
    G4double pdTeflonEfficiency[iNbEntries] = {1.0, 1.0, 1.0};
    
    G4MaterialPropertiesTable *pTeflonPropertiesTable = new G4MaterialPropertiesTable();
    
    pTeflonPropertiesTable->AddProperty("RINDEX", pdTeflonPhotonMomentum,
                                        pdTeflonRefractiveIndex, iNbEntries);
    pTeflonPropertiesTable->AddProperty("REFLECTIVITY", pdTeflonPhotonMomentum,
                                        pdTeflonReflectivity, iNbEntries);
    pTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT",
                                        pdTeflonPhotonMomentum,
                                        pdTeflonSpecularLobe, iNbEntries);
    pTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT",
                                        pdTeflonPhotonMomentum,
                                        pdTeflonSpecularSpike, iNbEntries);
    pTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT",
                                        pdTeflonPhotonMomentum,
                                        pdTeflonBackscatter, iNbEntries);
    pTeflonPropertiesTable->AddProperty("EFFICIENCY", pdTeflonPhotonMomentum,
                                        pdTeflonEfficiency, iNbEntries);
    
    Teflon->SetMaterialPropertiesTable(pTeflonPropertiesTable);
    
    //#if GEANTVERSION>=10
    //      if(m_iVerbosityLevel >= 1){
    //        G4MaterialPropertyVector *property =
    //        pTeflonPropertiesTable->GetProperty("REFLECTIVITY");
    //        G4cout << "Default value for teflon reflectivity " << (*property)[0]
    //        << "  " << (*property)[1] << "  " << (*property)[2] << G4endl;
    //    }
    //#endif
    
    /*
     FV: this TEFLON is used for the components in the GXe.
     You can set its reflectivity from the optphot.mac
     using the command: setGXeTeflonReflectivity
     */
    //------------------------------------ GXe teflon
    //-----------------------------------
    G4Material *GXeTeflon =
    new G4Material("GXeTeflon", 2.2 * g / cm3, 2, kStateSolid);
    GXeTeflon->AddElement(C, 0.240183);
    GXeTeflon->AddElement(F, 0.759817);
    
    G4double pdGXeTeflonPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
        7.05 * eV};
    G4double pdGXeTeflonRefractiveIndex[iNbEntries] = {1.63, 1.61, 1.58};
    G4double pdGXeTeflonReflectivity[iNbEntries] = {0.99, 0.99, 0.99};
    G4double pdGXeTeflonSpecularLobe[iNbEntries] = {0.01, 0.01, 0.01};
    G4double pdGXeTeflonSpecularSpike[iNbEntries] = {0.01, 0.01, 0.01};
    G4double pdGXeTeflonBackscatter[iNbEntries] = {0.01, 0.01, 0.01};
    G4double pdGXeTeflonEfficiency[iNbEntries] = {1.0, 1.0, 1.0};
    
    G4MaterialPropertiesTable *pGXeTeflonPropertiesTable =
    new G4MaterialPropertiesTable();
    
    pGXeTeflonPropertiesTable->AddProperty("RINDEX", pdGXeTeflonPhotonMomentum,
                                           pdGXeTeflonRefractiveIndex,
                                           iNbEntries);
    pGXeTeflonPropertiesTable->AddProperty("REFLECTIVITY",
                                           pdGXeTeflonPhotonMomentum,
                                           pdGXeTeflonReflectivity, iNbEntries);
    pGXeTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT",
                                           pdGXeTeflonPhotonMomentum,
                                           pdGXeTeflonSpecularLobe, iNbEntries);
    pGXeTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT",
                                           pdGXeTeflonPhotonMomentum,
                                           pdGXeTeflonSpecularSpike, iNbEntries);
    pGXeTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT",
                                           pdGXeTeflonPhotonMomentum,
                                           pdGXeTeflonBackscatter, iNbEntries);
    pGXeTeflonPropertiesTable->AddProperty("EFFICIENCY",
                                           pdGXeTeflonPhotonMomentum,
                                           pdGXeTeflonEfficiency, iNbEntries);
    
    GXeTeflon->SetMaterialPropertiesTable(pGXeTeflonPropertiesTable);
    
    //#if GEANTVERSION>=10
    //      if(m_iVerbosityLevel >= 1){
    //          G4MaterialPropertyVector *property2 =
    // pGXeTeflonPropertiesTable->GetProperty("REFLECTIVITY");
    //        G4cout << "Default value for GXe teflon reflectivity " <<
    //        (*property2)[0] << "  " << (*property2)[1] << "  " <<
    //        (*property2)[2] << G4endl;
    //    }
    //#endif
    
    //------------------------------------ copper
    //-----------------------------------
    G4Material *Copper = new G4Material("Copper", 8.92 * g / cm3, 1);
    Copper->AddElement(Cu, 1);
    
    G4double pdCopperPhotonMomentum[iNbEntries] = {
        1.91 * eV, 6.98 * eV, 7.05 * eV};  //{6.91*eV, 6.98*eV, 7.05*eV};
    G4double pdCopperReflectivity[iNbEntries] = {0.15, 0.2, 0.15};
    G4MaterialPropertiesTable *pCopperPropertiesTable =
    new G4MaterialPropertiesTable();
    
    pCopperPropertiesTable->AddProperty("REFLECTIVITY", pdCopperPhotonMomentum,
                                        pdCopperReflectivity, iNbEntries);
    Copper->SetMaterialPropertiesTable(pCopperPropertiesTable);
    
    //------------------------------------ PMT ceramic
    //-----------------------------------
    G4Material *Ceramic = new G4Material("Ceramic", 4. * g / cm3, 2, kStateSolid,
                                         168.15 * kelvin, 1.5 * atmosphere);
    Ceramic->AddElement(Al, 2);
    Ceramic->AddElement(O, 3);
    
    //------------------------------Ethylene Glycol------------------------------
    G4Material *Glycol =
    new G4Material("Glycol", 1.11 * g / cm3, 3, kStateLiquid);
    Glycol->AddElement(C, atomnumber = 2);
    Glycol->AddElement(O, atomnumber = 2);
    Glycol->AddElement(H, atomnumber = 6);
    
    //----------------------------Water Glycol Mixture---------------------------
    G4Material *WaterGlycol =
    
    new G4Material("WaterGlycol", 1.04 * g / cm3, 2, kStateLiquid);
    WaterGlycol->AddMaterial(Water, fractionmass = 0.61855);
    WaterGlycol->AddMaterial(Glycol, fractionmass = 0.38145);
    
    //--------------------------------Deuterium Gas------------------------------
    G4Material *DeuteriumGas =
    new G4Material("DeuteriumGas", 0.08 * g / m3, 2, kStateGas,
                   308.15 * kelvin, 0.0297 * bar);
    DeuteriumGas->AddElement(D, atomnumber = 1);
    DeuteriumGas->AddElement(D, atomnumber = 1);
    
    //------------------------------Transformer Oil------------------------------
    G4Material *TransformerOil =
    new G4Material("TransformerOil", 0.89 * g / cm3, 2, kStateLiquid);
    TransformerOil->AddElement(H, atomnumber = 2);
    TransformerOil->AddElement(C, atomnumber = 1);
    
    //----------------------------Getter Disc
    // Alloy--------------------------------
    G4Material *Getter_alloy =
    new G4Material("GAlloy", 4.16 * g / cm3, 3, kStateSolid);
    Getter_alloy->AddElement(Zr, fractionmass = 0.70);
    Getter_alloy->AddElement(V, fractionmass = 0.25);
    Getter_alloy->AddElement(Fe, fractionmass = 0.05);
    
    //---------------------------------- titanium
    //----------------------------------
    //  G4Material *Titanium = pNistManager->FindOrBuildMaterial("G4_Ti");
    G4Material *Titanium =
    new G4Material("Titanium", 4.506 * g / cm3, 1, kStateSolid);
    Titanium->AddElement(Ti, 1);
    
    //------------------------------------ acrylic
    //-----------------------------------
    G4Material *Acrylic =
    new G4Material("Acrylic", 1.18 * g / cm3, 3, kStateSolid, 168.15 * kelvin,
                   1.5 * atmosphere);
    Acrylic->AddElement(C, 5);
    Acrylic->AddElement(H, 8);
    Acrylic->AddElement(O, 2);
    
    // DR 20160725 - Optical properties Acrylic;
    // const G4int iNbEntries = 3;
    G4double pdAcrylicPhotonMomentum[iNbEntries] = {2.59 * eV, 2.88 * eV,
        3.17 * eV};
    G4double pdAcrylicRefractiveIndex[iNbEntries] = {1.50, 1.50, 1.50};
    G4double pdAcrylicAbsorbtionLength[iNbEntries] = {3.5 * m, 3.5 * m, 3.5 * m};
    // G4double pdAcrylicScatteringLength[iNbEntries] = {100*m,   100*m,   100*m};
    
    G4MaterialPropertiesTable *pAcrylicPropertiesTable =
    new G4MaterialPropertiesTable();
    pAcrylicPropertiesTable->AddProperty("RINDEX", pdAcrylicPhotonMomentum,
                                         pdAcrylicRefractiveIndex, iNbEntries);
    pAcrylicPropertiesTable->AddProperty("ABSLENGTH", pdAcrylicPhotonMomentum,
                                         pdAcrylicAbsorbtionLength, iNbEntries);
    // pAcrylicPropertiesTable->AddProperty("RAYLEIGH", pdAcrylicPhotonMomentum,
    // pdAcrylicScatteringLength, iNbEntries);
    
    Acrylic->SetMaterialPropertiesTable(pAcrylicPropertiesTable);
    
    //------------------------------------ polyethilene
    //-----------------------------------
    G4Material *poly = new G4Material("poly", 0.95 * g / cm3, 2);
    poly->AddElement(C, 1);
    poly->AddElement(H, 2);
    
    G4Material *B_poly = new G4Material("B_poly", 0.93 * g / cm3, 4,
                                        kStateSolid);  // B-doped, from
    // http://lss.fnal.gov/archive/2000/fn/FN-697.pdf
    B_poly->AddElement(H, fractionmass = 0.116);
    B_poly->AddElement(C, fractionmass = 0.612);
    B_poly->AddElement(B, fractionmass = 0.05);
    B_poly->AddElement(O, fractionmass = 0.222);
    
    // if(m_iVerbosityLevel >= 1)
    // G4cout << "B_poly " << B_poly << G4endl;
    
    // ----------- optical properties of water --------------------
    const G4int nEntries = 32;
    
    G4double PhotonEnergy[nEntries] = {
        2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
        2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
        2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
        4.002 * eV, 4.136 * eV};
    //
    // Water
    //
    G4double RefractiveIndex1[nEntries] = {
        1.3435, 1.344,  1.3445, 1.345,  1.3455, 1.346,  1.3465, 1.347,
        1.3475, 1.348,  1.3485, 1.3492, 1.35,   1.3505, 1.351,  1.3518,
        1.3522, 1.3530, 1.3535, 1.354,  1.3545, 1.355,  1.3555, 1.356,
        1.3568, 1.3572, 1.358,  1.3585, 1.359,  1.3595, 1.36,   1.3608};
    
    G4double Absorption1[nEntries] = {
        3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m,  12.346 * m, 13.889 * m,
        15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,
        45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,
        52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
        30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,
        17.500 * m, 14.500 * m};
    
    for (Int_t i = 0; i < nEntries;
         ++i) {  // MS170215 to increase the absorption length in Water, to match
        // the real data
        Absorption1[i] = Absorption1[i] * 10.;
    }
    
    G4MaterialPropertiesTable *myMPT1 = new G4MaterialPropertiesTable();
    myMPT1->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex1, nEntries);
    myMPT1->AddProperty("ABSLENGTH", PhotonEnergy, Absorption1, nEntries);
    
    Water->SetMaterialPropertiesTable(myMPT1);
    
    //----------------- Gran Sasso Rock ------------------ //EDIT PAOLO
    G4Material *GSrock = new G4Material("GSrock", 2.71 * g / cm3, 6);
    G4float GSfractionmass;
    GSrock->AddElement(O, GSfractionmass = 51. * perCent);
    GSrock->AddElement(Ca, GSfractionmass = 27. * perCent);
    GSrock->AddElement(C, GSfractionmass = 12. * perCent);
    GSrock->AddElement(Mg, GSfractionmass = 8.4 * perCent);
    GSrock->AddElement(Si, GSfractionmass = 1. * perCent);
    GSrock->AddElement(Al, GSfractionmass = 0.6 * perCent);
    
    //------------------ LNGS Concrete ------------------- //EDIT PAOLO
    G4Material *Concrete = new G4Material("Concrete", 2.4 * g / cm3, 13);
    Concrete->AddElement(H, 0.89 * perCent);
    Concrete->AddElement(C, 7.99 * perCent);
    Concrete->AddElement(O, 49.64 * perCent); // changed from 48.43 in order to have sum fractional masses 1
    Concrete->AddElement(Na, 0.6 * perCent);
    Concrete->AddElement(Mg, 0.85 * perCent);
    Concrete->AddElement(Al, 0.9 * perCent);
    Concrete->AddElement(Si, 3.86 * perCent);
    Concrete->AddElement(P, 0.04 * perCent);
    Concrete->AddElement(S, 0.16 * perCent);
    Concrete->AddElement(K, 0.54 * perCent);
    Concrete->AddElement(Ca, 34.06 * perCent);
    Concrete->AddElement(Ti, 0.04 * perCent);
    Concrete->AddElement(Fe, 0.43 * perCent);
    
    // ************************* SERENA (through ExN06) *************************
    //
    // Air
    //
    G4double RefractiveIndex2[nEntries] = {
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
    
    G4MaterialPropertiesTable *myMPT2 = new G4MaterialPropertiesTable();
    myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);
    
    Air->SetMaterialPropertiesTable(myMPT2);
    // ***************************************************************************
    
    // graphite
    // G4Isotope* C12 = new G4Isotope("C12", 6, 12);
    // G4Element* C   = new G4Element("TS_C_of_Graphite","C", ncomponents=1);
    // C->AddIsotope(C12, 100.*perCent);
    G4Material *Graphite =
    new G4Material("Graphite", 2.27 * g / cm3, ncomponents = 1, kStateSolid,
                   293 * kelvin, 1 * atmosphere);
    G4int natoms;
    Graphite->AddElement(C, natoms = 1);
    
    // PMT: Values from XENON-paper: Lowering the radioactivity of the photomultiplier tubes for the XENON1T dark matter experiment
    
    G4Material *PMT_material =
    new G4Material("PMT_material", 1.6138 * g / cm3, 5, kStateSolid); //Assumes 900 PMTs per disk (radius=1300 mm, thickness=20 mm)
    PMT_material->AddMaterial(Quartz, 23.32 * perCent);
    PMT_material->AddMaterial(Kovar, 57.77 * perCent);
    PMT_material->AddMaterial(CoatingAluminium, 0.32 * perCent); //CoatingAluminium=Pure Aluminium
    PMT_material->AddMaterial(SS304LSteel, 10.19 * perCent);
    PMT_material->AddMaterial(Ceramic, 8.40 * perCent);

    //---------------------------------------------------------------------------------
    //------------------------------------ Additional Xebra Materials
    //------------------------------------ added by Alex
    //---------------------------------------------------------------------------------

    //---------------------------------- aluminium
    //----------------------------------
    G4Material *Aluminium = new G4Material("Aluminium", 2.7 * g / cm3, 1, kStateSolid); //ToDo: check density, add Reflectivity etc.
    Aluminium->AddElement(Al, 1.0);

    //---------------------------------- PEEK (polyether ether ketone, C_19 H_12 O_3)
    //----------------------------------
    G4Material *PEEK = new G4Material("PEEK", 1.32 * g / cm3, ncomponents=3, kStateSolid); //ToDo: check density, add Reflectivity etc.
    PEEK->AddElement(C, natoms=19);
    PEEK->AddElement(H, natoms=12);
    PEEK->AddElement(O, natoms=3);

    //---------------------------------- grid mesh steel
    //----------------------------------

		//----------------------------- grid mesh steel in LXe------------------------------
		G4Material *GridMeshSS316LSteelLXe = new G4Material("GridMeshSS316LSteelLXe", 8.00*g/cm3, 6, kStateSolid);
		GridMeshSS316LSteelLXe->AddElement(Fe, 0.682);
		GridMeshSS316LSteelLXe->AddElement(Cr, 0.172);
		GridMeshSS316LSteelLXe->AddElement(Ni, 0.109);
		GridMeshSS316LSteelLXe->AddElement(Mn, 0.016);
		GridMeshSS316LSteelLXe->AddElement(C, 0.0002);
		GridMeshSS316LSteelLXe->AddElement(Mo, 0.021);

		G4double pdGridMeshPhotonMomentumLXe[] = {6.91*eV, 6.98*eV, 7.05*eV};
		
		G4double *pdGridMeshRefractiveIndexLXe = pdLXeRefractiveIndex;
		G4double dAbsortionLengthLXe = 1.39*mm; // exp(-GridMeshThickness/AbsortionLength) = transparency  lambda=-thickness/ln(transparency) transparency=1-(AreadGrid/AreaVoid)=0.898
		G4double pdGridMeshAbsortionLengthLXe[] = {dAbsortionLengthLXe, dAbsortionLengthLXe, dAbsortionLengthLXe};

	 	G4MaterialPropertiesTable *pGridMeshLXePropertiesTable = new G4MaterialPropertiesTable();

	 	pGridMeshLXePropertiesTable->AddProperty("RINDEX", pdGridMeshPhotonMomentumLXe, pdGridMeshRefractiveIndexLXe, iNbEntries);
		pGridMeshLXePropertiesTable->AddProperty("ABSLENGTH", pdGridMeshPhotonMomentumLXe, pdGridMeshAbsortionLengthLXe, iNbEntries);
		GridMeshSS316LSteelLXe->SetMaterialPropertiesTable(pGridMeshLXePropertiesTable);

		//----------------------------- grid mesh steel in GXe------------------------------
		G4Material *GridMeshSS316LSteelGXe = new G4Material("GridMeshSS316LSteelGXe", 8.00*g/cm3, 6, kStateSolid);
		GridMeshSS316LSteelGXe->AddElement(Fe, 0.682);
		GridMeshSS316LSteelGXe->AddElement(Cr, 0.172);
		GridMeshSS316LSteelGXe->AddElement(Ni, 0.109);
		GridMeshSS316LSteelGXe->AddElement(Mn, 0.016);
		GridMeshSS316LSteelGXe->AddElement(C, 0.0002);
		GridMeshSS316LSteelGXe->AddElement(Mo, 0.021);

		G4double pdGridMeshPhotonMomentumGXe[] = {6.91*eV, 6.98*eV, 7.05*eV};
		G4double *pdGridMeshRefractiveIndexGXe = pdGXeRefractiveIndex;
		G4double dAbsortionLengthGXe = 1.39*mm; // exp(-GridMeshThickness/AbsortionLength) = transparency  lambda=-thickness/ln(transparency) transparency=1-(AreadGrid/AreaVoid)=0.898
		G4double pdGridMeshAbsortionLengthGXe[] = {dAbsortionLengthGXe, dAbsortionLengthGXe, dAbsortionLengthGXe};

	 	G4MaterialPropertiesTable *pGridMeshGXePropertiesTable = new G4MaterialPropertiesTable();

	 	pGridMeshGXePropertiesTable->AddProperty("RINDEX", pdGridMeshPhotonMomentumGXe, pdGridMeshRefractiveIndexGXe, iNbEntries);
		pGridMeshGXePropertiesTable->AddProperty("ABSLENGTH", pdGridMeshPhotonMomentumGXe, pdGridMeshAbsortionLengthGXe, iNbEntries);
		GridMeshSS316LSteelGXe->SetMaterialPropertiesTable(pGridMeshGXePropertiesTable);
    
}

//XENON Header Files
#include "XebraPhysicsList.hh"
#include "XebraPhysicsMessenger.hh"

//Additional Header Files
#include <globals.hh>
#include <iomanip>
#include <vector>

//Root Header Files
#include "TFile.h"
#include "TH1.h"
#include "TParameter.h"
#include "TNamed.h"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include <G4OpticalPhysics.hh>
#include <G4EmStandardPhysics.hh>
#include <G4EmPenelopePhysics.hh>
#include <G4EmExtraPhysics.hh>
#include <G4DecayPhysics.hh>
#include <G4StoppingPhysics.hh>
#include <G4NistManager.hh>
#include <G4HadronicProcessStore.hh>
#include <G4ios.hh>
#include <G4EmCalculator.hh>

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"	


//__________________________________________________________________________________________________________
XebraPhysicsList::XebraPhysicsList(G4String fName):G4VModularPhysicsList()
{
  VerboseLevel = 0;
  SetVerboseLevel(VerboseLevel);
  
  defaultCutValue = 1.0 * mm;
  cutForGamma    = defaultCutValue;
  cutForElectron = defaultCutValue;
  cutForPositron = defaultCutValue;
  //cutForPotron   = defaultCutValue;
	
  m_pMessenger = new XebraPhysicsMessenger(this);
  
  G4cout <<"XebraPhysicsList::XebraPhysicsList() EM physics: "<< m_hEMlowEnergyModel << G4endl;
  
  /// G4OpticalPhysics
  //  creates the following particles:
  //     bosons:  G4OpticalPhoton
  //
  //  and adds the following physical processes to these particles:
  //     G4OpAbsorption, G4OpRayleigh, G4OpMieHG, G4OpBoundaryProcess, G4OpWLS, G4Scintillation, G4Cerenkov
  RegisterPhysics( X1TG4OpticalPhysics = new G4OpticalPhysics(VerboseLevel) );
  ( (G4OpticalPhysics*) X1TG4OpticalPhysics )->Configure( kCerenkov, m_bCerenkov );
  
  // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysicsHP(VerboseLevel) );
  
  // Hadron Inelastic Physics
  if (m_hHadronicModel == "QGSP_BIC_HP") {
    RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(VerboseLevel) );
  } else if (m_hHadronicModel == "FTFP_BERT_HP") {
    RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(VerboseLevel));
  } else if (m_hHadronicModel == "QBBC") {
    RegisterPhysics( new G4HadronInelasticQBBC(VerboseLevel));
  } else if (m_hHadronicModel == "INCLXX") {
    RegisterPhysics( new G4HadronPhysicsINCLXX(VerboseLevel));
  } else if (m_hHadronicModel == "QGSP_BERT_HP") {
    RegisterPhysics( new G4HadronPhysicsQGSP_BERT_HP(VerboseLevel));
  } else if (m_hHadronicModel == "QGSP_BERT") {
    RegisterPhysics( new G4HadronPhysicsQGSP_BERT(VerboseLevel));
  } else {
    G4String msg = "XebraPhysicsList::XebraPhysicsList() Available choices for Hadronic Physics are: <QGSP_BIC_HP> <QGSP_BERT_HP>";
    G4Exception("XebraPhysicsList::XebraPhysicsList()","PhysicsList",FatalException,msg);
  }
  //RegisterPhysics( new G4HadronPhysicsShielding(VerboseLevel) );  
  //RegisterPhysics( new G4HadronStoppingProcess(VerboseLevel) );  
  
  // Ion Elastic scattering
  RegisterPhysics( new G4IonElasticPhysics(VerboseLevel) );  
  
  // Ion Inelastic Physics
  RegisterPhysics( new G4IonPhysics(VerboseLevel) );
  ////RegisterPhysics( new G4IonINCLXXPhysics(VerboseLevel));
    
  // Gamma-Nuclear Physics - see Hadr03
  //RegisterPhysics( new GammaPhysics("gamma") );
  
  // EM physics
  if (m_hEMlowEnergyModel == "emstandard") {
	/// G4EmStandardPhysics
	//  creates the following particles:
	//     bosons:  G4Gamma
	//     leptons: G4Electron, G4Positron, G4MuonPlus, G4MuonMinus
	//     mesons:  G4PionPlus, G4PionMinus, G4KaonPlus, G4KaonMinus
	//     baryons: G4Proton, G4AntiProton
	//     ions:    G4Deuteron, G4Triton, G4He3, G4Alpha, G4GenericIon
	//
	//  and adds the following physical processes to these particles:
	//     G4ComptonScattering, G4GammaConversion, G4PhotoElectricEffect
	//     G4eMultipleScattering, G4eIonisation, G4eBremsstrahlung, G4eplusAnnihilation
	//     G4MuMultipleScattering, G4MuIonisation, G4MuBremsstrahlung, G4MuPairProduction
	//     G4CoulombScattering
	//     G4hMultipleScattering, G4hBremsstrahlung, G4hIonisation, G4hPairProduction
	//     G4ionIonisation
    RegisterPhysics( new G4EmStandardPhysics(VerboseLevel,"") );
  } else if (m_hEMlowEnergyModel == "emlivermore"){
    RegisterPhysics( new G4EmLivermorePhysics(VerboseLevel,"") ); 
  } else if (m_hEMlowEnergyModel == "empenelope"){
	RegisterPhysics( new G4EmPenelopePhysics(VerboseLevel,"") );
  } else {
    G4cout <<"XebraPhysicsList::XebraPhysicsList() FATAL: Bad EM physics list chosen: "<<m_hEMlowEnergyModel<<G4endl;
    G4String msg = " Available choices are: <emstandard> <emlivermore (default)> <empenelope>";
    G4Exception("XebraPhysicsList::XebraPhysicsList()","PhysicsList",FatalException,msg);
  }
  
  /// G4EmExtraPhysics
  //  creates the following particles:
  //     bosons:  G4Gamma
  //     leptons: G4Electron, G4Positron, G4MuonPlus, G4MuonMinus
  //
  //  and adds the following physical processes to these particles:
  //     G4SynchrotronRadiation, G4MuNuclearInteraction, G4ElectroNuclearBuilder
  RegisterPhysics( new G4EmExtraPhysics(VerboseLevel) );
  
  // Decay
  /// G4DecayPhysics
  //  creates the following particles:
  //     bosons:     G4BosonConstructor
  //     leptons:    G4LeptonConstructor
  //     mesons:     G4MesonConstructor
  //     baryons:    G4BaryonConstructor
  //     ions:       G4IonConstructor
  //     resonances: G4ShortLivedConstructor
  //
  //  and adds the following physical processes to these particles:
  //     G4Decay
  RegisterPhysics( new G4DecayPhysics(VerboseLevel) );

  // Radioactive decay
  RegisterPhysics( new G4RadioactiveDecayPhysics(VerboseLevel) );     
  
  /// G4StoppingPhysics
  //  like G4CaptureAtRestPhysics, but uses G4MuonMinusCaptureAtRest for muons
  RegisterPhysics( new G4StoppingPhysics(VerboseLevel) );
  
  physRootFile = fName;
}

//__________________________________________________________________________________________________________

XebraPhysicsList::~XebraPhysicsList()
{
  MakePhysicsPlots();
  delete m_pMessenger;
}

//__________________________________________________________________________________________________________

void XebraPhysicsList::SetCuts()
{
  if(VerboseLevel > 1)
    G4cout << "XebraPhysicsList::SetCuts:";
  
  if(VerboseLevel > 0)
  {
    G4cout << "XebraPhysicsList::SetCuts:";
    G4cout << "CutLength : "
    << G4BestUnit(defaultCutValue, "Length") << G4endl;
  }
  
  //special for low energy physics
  G4double lowlimit = 250 * eV;
  
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowlimit, 100. * GeV);
  
  SetCutValue(1*um, "proton"),
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  SetCutValue(cutForGamma, "gamma");      
}

//__________________________________________________________________________________________________________

void
XebraPhysicsList::WriteParameter(G4String parName)
{
  char * pch     = strtok ( getenv(parName.c_str()), "/" );
  char * parVal  = pch;
  // split string to keep only last part of path.... (handling strings in c++ is not fun)
  while (pch != NULL) {
    parVal = pch;
    pch = strtok (NULL, "/");
  }
  TNamed *Parameter = new TNamed(parName.c_str(),parVal);
  Parameter->Write();
  
}

void
XebraPhysicsList::MakePhysicsPlots()
{
  G4cout <<"XebraPhysicsList:: Init directory structure for histogramming..."<<G4endl;
  TFile *_f_physics = new TFile(physRootFile,"RECREATE");
  
  TDirectory *_physics = _f_physics->mkdir("physics");
  TDirectory *_em_physics=_physics->mkdir("electromagnetic");
  TDirectory *_had_physics=_physics->mkdir("hadronic");
  
  _physics->cd();
  
  // write the names of the Geant4 external data sets to the root output
  WriteParameter("G4NEUTRONHPDATA");
  WriteParameter("G4LEDATA");
  WriteParameter("G4LEVELGAMMADATA");
  WriteParameter("G4NEUTRONXSDATA");
  WriteParameter("G4RADIOACTIVEDATA");
  WriteParameter("G4ABLADATA");
  WriteParameter("G4PIIDATA");
  WriteParameter("G4REALSURFACEDATA");
  
  
  // make a list of materials for graphs
  G4int nmaterial = G4Material::GetNumberOfMaterials(); 
  G4cout <<"MakePhysicsPlots:: Number of materials = "<<nmaterial<<G4endl;
  //
  // EM physics plots
  //
  
  //
  // plotting range on a xlog-scale
  //
  G4double emin=0.001;  // 
  G4double emax=20.00; // 20 MeV
  emin = std::log10(emin);
  emax = std::log10(emax);
  
  G4int    nstep = 1000;
  G4double de    = (emax - emin)/nstep; // 
  
  _had_physics->cd();
  TNamed *_HADmodelPar = new TNamed("HADmodel",m_hHadronicModel);
  _HADmodelPar->Write();
  
  _em_physics->cd();
  TNamed *_EMmodelPar = new TNamed("EMmodel",m_hEMlowEnergyModel);
  _EMmodelPar->Write();
  
  if(makePhysicsHistograms){
    G4EmCalculator emCalc;
    std::vector<G4String> matNames,procNames;
    
    std::vector<TH1F*> _compt;
    std::vector<TH1F*> _phot;
    std::vector<TH1F*> _conv;
    std::vector<TH1F*> _msc;
    std::vector<TH1F*> _eIoni;
    std::vector<TH1F*> _eBrem;
    
    //  for(G4int imat=0; imat<(G4int)matNames.size(); imat++){
    for(G4int imat=0; imat<nmaterial; imat++){
      // get material
      G4Material *mat = G4NistManager::Instance()->GetMaterial(imat);
      G4double    rho = mat->GetDensity()/(g/cm3);
      G4cout << "MakePhysicsPlots:: Generate EM plots for:"<< mat->GetName()<<G4endl;
      
      // book histograms
      char  hName[100], pName[100];
      sprintf(hName,"%s_compt",mat->GetName().c_str());
      _compt.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_phot",mat->GetName().c_str());
      _phot.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_conv",mat->GetName().c_str());
      _conv.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      
      sprintf(hName,"%s_msc",mat->GetName().c_str());
      _msc.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_eIoni",mat->GetName().c_str());
      _eIoni.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_eBrem",mat->GetName().c_str());
      _eBrem.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      
      // fill histograms - skip the 0 bin
      
      G4double X0 = mat->GetRadlen();
      
      sprintf(pName,"%s_X0",mat->GetName().c_str());
      TParameter<double> *Parameter = new TParameter<double>(pName,X0/cm);
      Parameter->Write();
      
      G4cout <<mat->GetName()<< " X0 = "<<X0/cm << " (cm)" << G4endl;
      for(G4int i=0; i<nstep; i++){
        G4double x=emin+i*de;
        G4double e=std::pow(10,x);
        // cross section in cm2/g!
        G4double sig_compt = emCalc.ComputeCrossSectionPerVolume(e,"gamma","compt",mat->GetName(),0)*cm / rho;
        G4double sig_phot  = emCalc.ComputeCrossSectionPerVolume(e,"gamma","phot",mat->GetName(),0)*cm / rho;
        G4double sig_conv  = emCalc.ComputeCrossSectionPerVolume(e,"gamma","conv",mat->GetName(),0)*cm / rho;
        
        G4double dedx_msc   = X0*emCalc.ComputeDEDX(e,"e-","msc",mat->GetName())/e;
        G4double dedx_eIoni = X0*emCalc.ComputeDEDX(e,"e-","eIoni",mat->GetName())/e;
        G4double dedx_eBrem = X0*emCalc.ComputeDEDX(e,"e-","eBrem",mat->GetName())/e;
        
        //G4double sig_msc   = emCalc.ComputeMeanFreePath(e,"e-","msc",mat->GetName(),0)/cm; 
        //G4double sig_eIoni = emCalc.ComputeMeanFreePath(e,"e+","eIoni",mat->GetName(),0)/cm; 
        //G4double sig_eBrem = emCalc.ComputeMeanFreePath(e,"e-","eBrem",mat->GetName(),0)/cm; 
        _compt[imat]->Fill(x,sig_compt);
        _phot[imat]->Fill(x,sig_phot);
        _conv[imat]->Fill(x,sig_conv);
        
        _msc[imat]->Fill(x,dedx_msc);
        _eIoni[imat]->Fill(x,dedx_eIoni);
        _eBrem[imat]->Fill(x,dedx_eBrem);
      }// fill histograms
    }// loop over materials
    
    //
    // Hadronic physics plots:: only neutrons.....
    //
    //
    // plotting range on a xlog-scale
    //
    emin=0.00000001;  // 
    emax=20.00; // 20 MeV
    emin = std::log10(emin);
    emax = std::log10(emax);
    
    nstep = 1000;
    de    = (emax - emin)/nstep; // 
    
    _had_physics->cd();
    
    // histograms
    std::vector<TH1F*> _neutron_elastic;
    std::vector<TH1F*> _neutron_inelastic;
    std::vector<TH1F*> _neutron_capture;
    std::vector<TH1F*> _neutron_fission;
    
    G4HadronicProcessStore* hadstore     = G4HadronicProcessStore::Instance(); 
    const G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    
    for(G4int imat=0; imat<nmaterial; imat++){
      // get material
      G4Material *mat = G4NistManager::Instance()->GetMaterial(imat);
      G4cout << "MakePhysicsPlots:: Generate neutron cross section plots for:"<< mat->GetName()<<G4endl;
      
      // book histograms
      char  hName[100];
      sprintf(hName,"%s_neutron_elastic",mat->GetName().c_str());
      _neutron_elastic.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_neutron_inelastic",mat->GetName().c_str());
      _neutron_inelastic.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_neutron_capture",mat->GetName().c_str());
      _neutron_capture.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"%s_neutron_fission",mat->GetName().c_str());
      _neutron_fission.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      
      for(G4int i=0; i<nstep; i++){
        G4double x=emin+i*de;
        G4double e=std::pow(10.,x);
        G4double xs_elastic   = hadstore->GetElasticCrossSectionPerVolume(particle,e,mat)*cm;
        G4double xs_inelastic = hadstore->GetInelasticCrossSectionPerVolume(particle,e,mat)*cm;
        G4double xs_capture   = hadstore->GetCaptureCrossSectionPerVolume(particle,e,mat)*cm;
        G4double xs_fission   = hadstore->GetFissionCrossSectionPerVolume(particle,e,mat)*cm;
        _neutron_elastic[imat]->Fill(x,xs_elastic);
        _neutron_inelastic[imat]->Fill(x,xs_inelastic);
        _neutron_capture[imat]->Fill(x,xs_capture);
        _neutron_fission[imat]->Fill(x,xs_fission);
      }
    }
    
    //
    // Neutron cross sections for elements
    //
    // histograms
    std::vector<TH1F*> _el_neutron_elastic;
    std::vector<TH1F*> _el_neutron_inelastic;
    std::vector<TH1F*> _el_neutron_capture;
    std::vector<TH1F*> _el_neutron_fission;
    
    
    G4int nelement = G4Element::GetNumberOfElements();
    G4cout <<" number of elements "<< nelement<<G4endl;
    
    for(G4int iel = 0; iel<nelement; iel++){
      G4Element *ele = G4NistManager::Instance()->GetElement(iel);
      G4cout <<"MakePhysicsPlots:: element = "<<ele->GetName()<<G4endl;
      
      // book histograms
      char  hName[100];
      sprintf(hName,"_el_%s_neutron_elastic",ele->GetName().c_str());
      _el_neutron_elastic.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"_el_%s_neutron_inelastic",ele->GetName().c_str());
      _el_neutron_inelastic.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"_el_%s_neutron_capture",ele->GetName().c_str());
      _el_neutron_capture.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      sprintf(hName,"_el_%s_neutron_fission",ele->GetName().c_str());
      _el_neutron_fission.push_back(new TH1F(hName,hName,nstep,emin-de/2,emax-de/2));
      
      //G4Material *mdummy = G4NistManager::Instance()->GetMaterial(1);
      for(G4int i=0; i<nstep; i++){
        G4double x=emin+i*de;
        G4double e=std::pow(10.,x);
        
        // G4.9.5
        //G4double xs_elastic   = hadstore->GetElasticCrossSectionPerAtom(particle,e,ele,mdummy)/barn;
        //G4double xs_inelastic = hadstore->GetInelasticCrossSectionPerAtom(particle,e,ele,mdummy)/barn;
        //G4double xs_capture   = hadstore->GetCaptureCrossSectionPerAtom(particle,e,ele,mdummy)/barn;
        //G4double xs_fission   = hadstore->GetFissionCrossSectionPerAtom(particle,e,ele,mdummy)/barn;
        
        // G4.9.4.p02
        G4double xs_elastic   = hadstore->GetElasticCrossSectionPerAtom(particle,e,ele)/barn;
        G4double xs_inelastic = hadstore->GetInelasticCrossSectionPerAtom(particle,e,ele)/barn;
        G4double xs_capture   = hadstore->GetCaptureCrossSectionPerAtom(particle,e,ele)/barn;
        G4double xs_fission   = hadstore->GetFissionCrossSectionPerAtom(particle,e,ele)/barn;
        _el_neutron_elastic[iel]->Fill(x,xs_elastic);
        _el_neutron_inelastic[iel]->Fill(x,xs_inelastic);
        _el_neutron_capture[iel]->Fill(x,xs_capture);
        _el_neutron_fission[iel]->Fill(x,xs_fission);
      }
    }
    
  } // makePhysicsHistograms
  //
  // return to root directory
  //
  _f_physics->cd();
  _f_physics->Write();
  _f_physics->Close();
  
}

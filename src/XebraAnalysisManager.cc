//XEBRA Header Files
#include "XebraDetectorConstruction.hh"
#include "XebraLXeHit.hh"
#include "XebraPmtHit.hh"
#include "XebraLScintHit.hh"
#include "XebraPrimaryGeneratorAction.hh"
#include "XebraEventData.hh"
#include "XebraAnalysisManager.hh"

//Additional Header Files
#include <numeric>
#include <vector>
#include <cmath>

//Root Header Files
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TParameter.h>
#include <TDirectory.h>
#include <TH1.h>

//G4 Header Files
#include <G4SDManager.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4EmCalculator.hh>
#include <G4Material.hh>
#include <G4HadronicProcessStore.hh>
#include <G4ParticleTable.hh>
#include <G4NistManager.hh>
#include <G4ElementTable.hh>
#include <G4Version.hh>
#include <G4SystemOfUnits.hh>


XebraAnalysisManager::XebraAnalysisManager(XebraPrimaryGeneratorAction *pPrimaryGeneratorAction)
{
  runTime = new G4Timer();
  
  // initialization of the HitsCollectionID variables 
  m_iLXeHitsCollectionID = -1;
  m_iPmtHitsCollectionID = -1;
  m_iLScintHitsCollectionID = -1;  
  
  // default output file name (which should be redifined in the main class)
  m_hDataFilename = "events.root";
  
  // reference to the initialized PrimaryGeneratorAction
  m_pPrimaryGeneratorAction = pPrimaryGeneratorAction;
  
  // declaration of the EventData class
  m_pEventData = new XebraEventData();
  //plotPhysics      = kTRUE;
  writeEmptyEvents = kFALSE;
}

XebraAnalysisManager::~XebraAnalysisManager()
{
}

void XebraAnalysisManager::BeginOfRun(const G4Run *)
{
  // start a timer for this run....
  runTime->Start();
  // do we write empty events or not?
  writeEmptyEvents = m_pPrimaryGeneratorAction->GetWriteEmpty();
  
  // create output file
  m_pTreeFile = new TFile(m_hDataFilename.c_str(), "RECREATE");//, "File containing event data for Xebra");
  // make tree structure
  TNamed *G4version = new TNamed("G4VERSION_TAG",G4VERSION_TAG);
  G4version->Write();
    
  _events = m_pTreeFile->mkdir("events");
  _events->cd();

  // create ROOT Tree for the simulation data
  G4cout <<"XebraAnalysisManager:: Init data tree ..."<<G4endl;
  m_pTree = new TTree("events", "Tree containing event data for Xebra");

  // include missing ROOT classes
  gROOT->ProcessLine("#include <vector>");
  
  // initialize all tree branches for the different data types

	//******************************************************************/	
	// branches for each main event/particle beam:
	//******************************************************************/
	// eventid:	The eventid contains the individual ID of each event. Since 'event' is used in different situations,
	//					it means, every particle created by 'beamOn' starts a detector event. All following events will be
	//					be saved within the same eventid in specific branches (see below).
	//					Acces to the eventid in ROOT: int eventid;
	//																				T1->SetBranchAddress("eventid", &eventid);
  m_pTree->Branch("eventid", &m_pEventData->m_iEventId, "eventid/I");
  // ntpmthits:	total amount of top PMT hits for a specific eventid/particle beam
	//						Acces in ROOT: 	int ntpmthits;
	//														T1->SetBranchAddress("ntpmthits", &ntpmthits);
  m_pTree->Branch("ntpmthits", &m_pEventData->m_iNbTopPmtHits, "ntpmthits/I");
  // nbpmthits:	total amount of bottom PMT hits for a specific eventid/particle beam
	//						Acces in ROOT: 	int nbpmthits;
	//														T1->SetBranchAddress("nbpmthits", &nbpmthits);
  m_pTree->Branch("nbpmthits", &m_pEventData->m_iNbBottomPmtHits, "nbpmthits/I");
  m_pTree->Branch("nLSpmthits", &m_pEventData->m_iNbLSPmtHits, "nLSpmthits/I");
  m_pTree->Branch("nWaterpmthits", &m_pEventData->m_iNbWaterPmtHits, "nWaterpmthits/I");
  // pmthits:	total amount of PMT hits for a specific eventid and for each PMT
	//						Acces in ROOT: 	vector<int> *pmthits= new vector<int>;
	//														T1->SetBranchAddress("pmthits", &pmthits);
	//						Note: Do not access pmthits without calling a specifig vector element.
  m_pTree->Branch("pmthits", "vector<int>", &m_pEventData->m_pPmtHits);
  
  // etot:	Amount of energy, which is deopsited during this eventid/particle run.
	//				Acces in ROOT: 	float etot;
	//												T1->SetBranchAddress("etot", &etot);
  m_pTree->Branch("etot", &m_pEventData->m_fTotalEnergyDeposited, "etot/F");
  m_pTree->Branch("nsteps", &m_pEventData->m_iNbSteps, "nsteps/I");
  
  //******************************************************************/	
	// branches for each event/particle which is created by the main event
	//******************************************************************/
	// trackid:	ID of the current event in the event track. All listed events are
	//					generated within the main eventid. (e.g. emitted gammas)
	//					Acces in ROOT: 	vector<int> *trackid= new vector<int>;
	//													T1->SetBranchAddress("trackid", &trackid);
  m_pTree->Branch("trackid", "vector<int>", &m_pEventData->m_pTrackId);
  // type:	type of the particles in the event track
	//				Acces in ROOT: 	vector<string> *type= new vector<string>;
	//												T1->SetBranchAddress("type", &type);
  m_pTree->Branch("type", "vector<string>", &m_pEventData->m_pParticleType);
  // parentid:	trackid of the parent track event
	//						Acces in ROOT: 	vector<int> *parentid= new vector<int>;
	//														T1->SetBranchAddress("parentid", &parentid);
  m_pTree->Branch("parentid", "vector<int>", &m_pEventData->m_pParentId);
  // parenttype:	parenttype of the parent track event
	//							Acces in ROOT: 	vector<string> *parenttype= new vector<string>;
	//															T1->SetBranchAddress("parenttype", &parenttype);
  m_pTree->Branch("parenttype", "vector<string>", &m_pEventData->m_pParentType);
  // creaproc:	name of the creation process of the track particle/trackid
	//						Acces in ROOT: 	vector<string> *creaproc= new vector<string>;
	//														T1->SetBranchAddress("creaproc", &creaproc);
  m_pTree->Branch("creaproc", "vector<string>", &m_pEventData->m_pCreatorProcess);
  // edproc:	name of the energy deposition process of the track particle/trackid
	//					Acces in ROOT: 	vector<string> *edproc= new vector<string>;
	//													T1->SetBranchAddress("edproc", &edproc);
  m_pTree->Branch("edproc", "vector<string>", &m_pEventData->m_pDepositingProcess);
  // Positions of the current particle/trackid
	// 		Acces in ROOT: 		vector<float> *xp= new vector<float>;
	//											T1->SetBranchAddress("xp", &xp);
  m_pTree->Branch("xp", "vector<float>", &m_pEventData->m_pX);
  // 		Acces in ROOT: 		vector<float> *yp= new vector<float>;
	//											T1->SetBranchAddress("yp", &yp);
  m_pTree->Branch("yp", "vector<float>", &m_pEventData->m_pY);
  // 		Acces in ROOT: 		vector<float> *zp= new vector<float>;
	//											T1->SetBranchAddress("zp", &zp);
  m_pTree->Branch("zp", "vector<float>", &m_pEventData->m_pZ);
  // ed:	energy deposition of the current particle/trackid
	// 			Acces in ROOT: 		vector<float> *ed= new vector<float>;
	//												T1->SetBranchAddress("ed", &ed);
  m_pTree->Branch("ed", "vector<float>", &m_pEventData->m_pEnergyDeposited);
  // time:	timestamp of the current particle/trackid
	// 				Acces in ROOT: 		vector<float> *time= new vector<float>;
	//													T1->SetBranchAddress("time", &time);
  m_pTree->Branch("time", "vector<float>", &m_pEventData->m_pTime);
  m_pTree->Branch("ekin", "vector<float>", &m_pEventData->m_pKineticEnergy);
  // DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
  m_pTree->Branch("pre_MomDirX", "vector<float>", &m_pEventData->m_pPreMomDirX);
  m_pTree->Branch("pre_MomDirY", "vector<float>", &m_pEventData->m_pPreMomDirY);
  m_pTree->Branch("pre_MomDirZ", "vector<float>", &m_pEventData->m_pPreMomDirZ);
  m_pTree->Branch("post_MomDirX", "vector<float>", &m_pEventData->m_pPostMomDirX);
  m_pTree->Branch("post_MomDirY", "vector<float>", &m_pEventData->m_pPostMomDirY);
  m_pTree->Branch("post_MomDirZ", "vector<float>", &m_pEventData->m_pPostMomDirZ);
  m_pTree->Branch("pre_ekin", "vector<float>", &m_pEventData->m_pPreKineticEnergy);
  m_pTree->Branch("post_ekin", "vector<float>", &m_pEventData->m_pPostKineticEnergy);
/*    
  m_pTree->Branch("LScint_etot", &m_pEventData->m_fLScintTotalEnergyDeposited, "LScint_etot/F");
  m_pTree->Branch("LScint_nsteps", &m_pEventData->m_iLScintNbSteps, "LScint_nsteps/I");
  m_pTree->Branch("LScint_trackid", "vector<int>", &m_pEventData->m_pLScintTrackId);
  m_pTree->Branch("LScint_type", "vector<string>", &m_pEventData->m_pLScintParticleType);
  m_pTree->Branch("LScint_parentid", "vector<int>", &m_pEventData->m_pLScintParentId);
  m_pTree->Branch("LScint_parenttype", "vector<string>", &m_pEventData->m_pLScintParentType);
  m_pTree->Branch("LScint_creaproc", "vector<string>", &m_pEventData->m_pLScintCreatorProcess);
  m_pTree->Branch("LScint_edproc", "vector<string>", &m_pEventData->m_pLScintDepositingProcess);
  m_pTree->Branch("LScint_xp", "vector<float>", &m_pEventData->m_pLScintX);
  m_pTree->Branch("LScint_yp", "vector<float>", &m_pEventData->m_pLScintY);
  m_pTree->Branch("LScint_zp", "vector<float>", &m_pEventData->m_pLScintZ);
  m_pTree->Branch("LScint_ed", "vector<float>", &m_pEventData->m_pLScintEnergyDeposited);
  m_pTree->Branch("LScint_ed_bCorr", "vector<float>", &m_pEventData->m_pLScintEnergyDepositedBirksCorrected);
  m_pTree->Branch("LScint_time", "vector<float>", &m_pEventData->m_pLScintTime);
  m_pTree->Branch("LScint_ekin", "vector<float>", &m_pEventData->m_pLScintKineticEnergy);
*/  
	
	//******************************************************************/	
	// branches for each event/particle which contain information about the primary particle
	//******************************************************************/
	// type_pri:	type of the primary event/main event
	//						Acces in ROOT: 	vector<string> *type_pri= new vector<string>;
	//														T1->SetBranchAddress("type_pri", &type_pri);
  m_pTree->Branch("type_pri", "vector<string>", &m_pEventData->m_pPrimaryParticleType);
  // Energy and positions of the current particle/trackid
	// 		Acces in ROOT:	vector<float> *e_pri= new vector<float>;
	//										T1->SetBranchAddress("e_pri", &e_pri);
  m_pTree->Branch("e_pri",  &m_pEventData->m_fPrimaryE, "e_pri/F");
  // 		Acces in ROOT:	vector<float> *xp_pri= new vector<float>;
	//										T1->SetBranchAddress("xp_pri", &xp_pri);
  m_pTree->Branch("xp_pri", &m_pEventData->m_fPrimaryX, "xp_pri/F");
  // 		Acces in ROOT:	vector<float> *yp_pri= new vector<float>;
	//										T1->SetBranchAddress("yp_pri", &yp_pri);
  m_pTree->Branch("yp_pri", &m_pEventData->m_fPrimaryY, "yp_pri/F");
  // 		Acces in ROOT:	vector<float> *zp_pri= new vector<float>;
	//										T1->SetBranchAddress("zp_pri", &zp_pri);
  m_pTree->Branch("zp_pri", &m_pEventData->m_fPrimaryZ, "zp_pri/F");
  m_pTree->Branch("xp_fcd", &m_pEventData->m_fForcedPrimaryX, "xp_fcd/F");
  m_pTree->Branch("yp_fcd", &m_pEventData->m_fForcedPrimaryY, "yp_fcd/F");
  m_pTree->Branch("zp_fcd", &m_pEventData->m_fForcedPrimaryZ, "zp_fcd/F");
  m_pTree->Branch("w_pri",  &m_pEventData->m_fPrimaryW, "w_pri/F");

  m_pTree->Branch("NSave", &m_pEventData->m_iNSave, "NSave/I");
  m_pTree->Branch("Save_flag", "vector<int>", &m_pEventData->m_pSave_flag);
  m_pTree->Branch("Save_type", "vector<int>", &m_pEventData->m_pSave_type);
  m_pTree->Branch("Save_x", "vector<float>", &m_pEventData->m_pSave_x);
  m_pTree->Branch("Save_y", "vector<float>", &m_pEventData->m_pSave_y);
  m_pTree->Branch("Save_z", "vector<float>", &m_pEventData->m_pSave_z);
  m_pTree->Branch("Save_cx", "vector<float>", &m_pEventData->m_pSave_cx);
  m_pTree->Branch("Save_cy", "vector<float>", &m_pEventData->m_pSave_cy);
  m_pTree->Branch("Save_cz", "vector<float>", &m_pEventData->m_pSave_cz);
  m_pTree->Branch("Save_e", "vector<float>", &m_pEventData->m_pSave_e);
  m_pTree->Branch("Save_t", "vector<float>", &m_pEventData->m_pSave_t);
  m_pTree->Branch("Save_trkid", "vector<int>", &m_pEventData->m_pSave_trkid);
  
  //m_pTree->SetMaxTreeSize(G4int(10e9));
  //m_pTree->AutoSave();
  
  // Added by Alex:
  //m_pTree->SetMaxTreeSize(1000*Long64_t(2000000000)); //2TB
	//m_pTree->AutoSave();
  
  // Write the number of events in the output file
  m_pNbEventsToSimulateParameter = new TParameter<int>("nbevents", m_iNbEventsToSimulate);
  m_pNbEventsToSimulateParameter->Write();

  m_pTreeFile->cd();

}

//******************************************************************/
// EndOfRun action/end of the simulation
//******************************************************************/
void XebraAnalysisManager::EndOfRun(const G4Run *)
{
  runTime->Stop();
  G4double dt = runTime->GetRealElapsed();
  // make tree structure
  TParameter<G4double> *dtPar = new TParameter<G4double>("G4RUNTIME",dt);
  dtPar->Write();

  m_pTreeFile->cd();

  m_pTreeFile->Write();
  m_pTreeFile->Close();
}

//******************************************************************/
//	BeginOfEvent action - for each beamed particle
//******************************************************************/
void XebraAnalysisManager::BeginOfEvent(const G4Event *)
{
	// initialize the HitCollections if needed (-1 = not initialized)
  if(m_iLXeHitsCollectionID == -1)
  {
    G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
    m_iLXeHitsCollectionID = pSDManager->GetCollectionID("LXeHitsCollection");
  } 

  if(m_iPmtHitsCollectionID == -1)
  {
    G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
    m_iPmtHitsCollectionID = pSDManager->GetCollectionID("PmtHitsCollection");
  }
/*
  if(m_iLScintHitsCollectionID == -1)
  {
    G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
    m_iLScintHitsCollectionID = pSDManager->GetCollectionID("LScintHitsCollection");
  } 
*/  
}

//******************************************************************/
// EndOfEvent action - getting all event data
//******************************************************************/
void XebraAnalysisManager::EndOfEvent(const G4Event *pEvent)
{
  _events->cd();

  G4HCofThisEvent* pHCofThisEvent = pEvent->GetHCofThisEvent();
  XebraLXeHitsCollection* pLXeHitsCollection = 0;
  XebraPmtHitsCollection* pPmtHitsCollection = 0;
  //XebraLScintHitsCollection* pLScintHitsCollection = 0;
  
  G4int iNbLXeHits = 0, iNbPmtHits = 0, iNbLScintHits = 0;
	
  if(pHCofThisEvent)
  {
      if(m_iLXeHitsCollectionID != -1)
      {
        pLXeHitsCollection = (XebraLXeHitsCollection *)(pHCofThisEvent->GetHC(m_iLXeHitsCollectionID));
        iNbLXeHits = (pLXeHitsCollection)?(pLXeHitsCollection->entries()):(0);
      }

      if(m_iPmtHitsCollectionID != -1)
	  {
        pPmtHitsCollection = (XebraPmtHitsCollection *)(pHCofThisEvent->GetHC(m_iPmtHitsCollectionID));
        iNbPmtHits = (pPmtHitsCollection)?(pPmtHitsCollection->entries()):(0);
	  }
/*
      if(m_iLScintHitsCollectionID != -1)
	  {
        pLScintHitsCollection = (XebraLScintHitsCollection *)(pHCofThisEvent->GetHC(m_iLScintHitsCollectionID));
        iNbLScintHits = (pLScintHitsCollection)?(pLScintHitsCollection->entries()):(0);
	  }
*/      
  }

  // get the event ID and primary particle information
  m_pEventData->m_iEventId = pEvent->GetEventID();
  m_pEventData->m_pPrimaryParticleType->push_back(m_pPrimaryGeneratorAction->GetParticleTypeOfPrimary());
  
  m_pEventData->m_fPrimaryX = m_pPrimaryGeneratorAction->GetPositionOfPrimary().x();
  m_pEventData->m_fPrimaryY = m_pPrimaryGeneratorAction->GetPositionOfPrimary().y();
  m_pEventData->m_fPrimaryZ = m_pPrimaryGeneratorAction->GetPositionOfPrimary().z();

  m_pEventData->m_fForcedPrimaryX = m_pPrimaryGeneratorAction->GetForcedPositionOfPrimary().x();
  m_pEventData->m_fForcedPrimaryY = m_pPrimaryGeneratorAction->GetForcedPositionOfPrimary().y();
  m_pEventData->m_fForcedPrimaryZ = m_pPrimaryGeneratorAction->GetForcedPositionOfPrimary().z();

  m_pEventData->m_fPrimaryE = m_pPrimaryGeneratorAction->GetEnergyOfPrimary() / keV;
  m_pEventData->m_fPrimaryW = pEvent->GetPrimaryVertex()->GetWeight();
 
  
  G4int iNbSteps = 0;
  G4int iLScintNbSteps = 0;
  G4float fTotalEnergyDeposited = 0.;
  G4float fLScintTotalEnergyDeposited = 0.;
  
  if(iNbLXeHits || iNbPmtHits || iNbLScintHits)
  {
		// LXe hits
    for(G4int i=0; i<iNbLXeHits; i++)
    {
	  XebraLXeHit *pHit = (*pLXeHitsCollection)[i];

	  if(pHit->GetParticleType() != "opticalphoton")
      {
        m_pEventData->m_pTrackId->push_back(pHit->GetTrackId());
        m_pEventData->m_pParentId->push_back(pHit->GetParentId());
        m_pEventData->m_pParticleType->push_back(pHit->GetParticleType());
        m_pEventData->m_pParentType->push_back(pHit->GetParentType());
        m_pEventData->m_pCreatorProcess->push_back(pHit->GetCreatorProcess());
        m_pEventData->m_pDepositingProcess->push_back(pHit->GetDepositingProcess());
        m_pEventData->m_pX->push_back(pHit->GetPosition().x()/mm);
        m_pEventData->m_pY->push_back(pHit->GetPosition().y()/mm);
        m_pEventData->m_pZ->push_back(pHit->GetPosition().z()/mm);
        fTotalEnergyDeposited += pHit->GetEnergyDeposited()/keV;
        m_pEventData->m_pEnergyDeposited->push_back(pHit->GetEnergyDeposited()/keV);
        m_pEventData->m_pKineticEnergy->push_back(pHit->GetKineticEnergy()/keV);
        m_pEventData->m_pTime->push_back(pHit->GetTime()/ns);       
        m_pEventData->m_pPreMomDirX->push_back(pHit->GetPreMomentumDir().x());
        m_pEventData->m_pPreMomDirY->push_back(pHit->GetPreMomentumDir().y());
        m_pEventData->m_pPreMomDirZ->push_back(pHit->GetPreMomentumDir().z());
        m_pEventData->m_pPostMomDirX->push_back(pHit->GetPostMomentumDir().x());
        m_pEventData->m_pPostMomDirY->push_back(pHit->GetPostMomentumDir().y());
        m_pEventData->m_pPostMomDirZ->push_back(pHit->GetPostMomentumDir().z());
        m_pEventData->m_pPreKineticEnergy->push_back(pHit->GetPreKineticEnergy()/keV);
        m_pEventData->m_pPostKineticEnergy->push_back(pHit->GetPostKineticEnergy()/keV);
            
        iNbSteps++;
      }
      
    }

    // LScint hits
/*    for(G4int i=0; i<iNbLScintHits; i++)
	{
	  XebraLScintHit *pHit = (*pLScintHitsCollection)[i];

	  if(pHit->GetParticleType() != "opticalphoton")
      {
        m_pEventData->m_pLScintTrackId->push_back(pHit->GetTrackId());
        m_pEventData->m_pLScintParentId->push_back(pHit->GetParentId());
        m_pEventData->m_pLScintParticleType->push_back(pHit->GetParticleType());
        m_pEventData->m_pLScintParentType->push_back(pHit->GetParentType());
        m_pEventData->m_pLScintCreatorProcess->push_back(pHit->GetCreatorProcess());
        m_pEventData->m_pLScintDepositingProcess->push_back(pHit->GetDepositingProcess());
        m_pEventData->m_pLScintX->push_back(pHit->GetPosition().x()/mm);
        m_pEventData->m_pLScintY->push_back(pHit->GetPosition().y()/mm);
        m_pEventData->m_pLScintZ->push_back(pHit->GetPosition().z()/mm);
        fLScintTotalEnergyDeposited += pHit->GetEnergyDeposited()/keV;
        m_pEventData->m_pLScintEnergyDeposited->push_back(pHit->GetEnergyDeposited()/keV);
        m_pEventData->m_pLScintEnergyDepositedBirksCorrected->push_back(pHit->GetEnergyDepositedBirksCorrected()/keV);
        m_pEventData->m_pLScintKineticEnergy->push_back(pHit->GetKineticEnergy()/keV);
        m_pEventData->m_pLScintTime->push_back(pHit->GetTime()/ns);

        iLScintNbSteps++;
      }
	} */


		G4int iNbTopPmts = 7;
		G4int iNbBottomPmts = 1;

		m_pEventData->m_pPmtHits->resize(iNbTopPmts+iNbBottomPmts, 0);

    // Pmt hits
    //G4cout << "Nb hits " << iNbPmtHits << G4endl;
    for(G4int i=0; i<iNbPmtHits; i++)
    {
        (*(m_pEventData->m_pPmtHits))[(*pPmtHitsCollection)[i]->GetPmtNb()]++;
        //G4cout << "PMTID " << (*pPmtHitsCollection)[i]->GetPmtNb() << G4endl;  
    }   

    //m_pEventData->m_iNbTopPmtHits = accumulate(m_pEventData->m_pPmtHits->begin(), m_pEventData->m_pPmtHits->begin()+iNbTopPmts, 0);
    //m_pEventData->m_iNbBottomPmtHits = accumulate(m_pEventData->m_pPmtHits->begin()+iNbTopPmts, m_pEventData->m_pPmtHits->begin()+iNbTopPmts+iNbBottomPmts, 0);
    
    m_pEventData->m_iNbBottomPmtHits = accumulate(m_pEventData->m_pPmtHits->begin(), m_pEventData->m_pPmtHits->begin()+iNbBottomPmts, 0);
    m_pEventData->m_iNbTopPmtHits = accumulate(m_pEventData->m_pPmtHits->begin()+iNbBottomPmts, m_pEventData->m_pPmtHits->begin()+iNbBottomPmts+iNbTopPmts, 0);

 //    //if((fTotalEnergyDeposited > 0. || iNbPmtHits > 0) && !FilterEvent(m_pEventData))
 //    //APC	if(fTotalEnergyDeposited > 0. || iNbPmtHits > 0)
 //    //APC	m_pTree->Fill();
 //    //APC	m_pEventData->Clear();
 //  }
  
 //  // also write the header information + primary vertex of the empty events....
 m_pEventData->m_iNbSteps = iNbSteps;
 m_pEventData->m_iLScintNbSteps = iLScintNbSteps;
 m_pEventData->m_fTotalEnergyDeposited = fTotalEnergyDeposited;
 m_pEventData->m_fLScintTotalEnergyDeposited = fLScintTotalEnergyDeposited;
  

  // save only energy depositing events
  if(writeEmptyEvents)
  {
    m_pTree->Fill(); // write all events to the tree
  }
  else
  {
  // if(fTotalEnergyDeposited > 0.) m_pTree->Fill();
  if(fTotalEnergyDeposited > 0. || iNbPmtHits > 0) m_pTree->Fill(); // only events with some activity are written to the tree
  }
  
  // auto save functionality to avoid data loss/ROOT can recover aborted simulations
	//if ( pEvent->GetEventID() % 10000 == 0)
		//m_pTree->AutoSave();
  
  }
  m_pEventData->Clear(); 
  m_pTreeFile->cd();
}

void XebraAnalysisManager::Step(const G4Step *)
{
}

void XebraAnalysisManager::FillParticleInSave(G4int flag, G4int partPDGcode, G4ThreeVector pos, G4ThreeVector dir,  G4float nrg, G4float time, G4int trackID)
{
    m_pEventData->m_pSave_flag->push_back(flag);
    m_pEventData->m_pSave_type->push_back(partPDGcode);
    m_pEventData->m_pSave_x->push_back(pos.x()/mm);
    m_pEventData->m_pSave_y->push_back(pos.y()/mm);
    m_pEventData->m_pSave_z->push_back(pos.z()/mm);
    m_pEventData->m_pSave_cx->push_back(dir.x());
    m_pEventData->m_pSave_cy->push_back(dir.y());
    m_pEventData->m_pSave_cz->push_back(dir.z());
    m_pEventData->m_pSave_e->push_back(nrg/keV);
    m_pEventData->m_pSave_t->push_back(time/ns);
    m_pEventData->m_pSave_trkid->push_back(trackID);
    m_pEventData->m_iNSave++;

    //G4cout <<    m_pEventData->m_iNSave << " " << partPDGcode << " " << pos << " " << nrg << G4endl;
}

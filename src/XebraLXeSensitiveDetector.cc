#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>

#include <map>

using std::map;

#include "XebraLXeSensitiveDetector.hh"

XebraLXeSensitiveDetector::XebraLXeSensitiveDetector(G4String hName): G4VSensitiveDetector(hName)
{
	collectionName.insert("LXeHitsCollection");
}

XebraLXeSensitiveDetector::~XebraLXeSensitiveDetector()
{
}

void XebraLXeSensitiveDetector::Initialize(G4HCofThisEvent* pHitsCollectionOfThisEvent)
{
	m_pLXeHitsCollection = new XebraLXeHitsCollection(SensitiveDetectorName, collectionName[0]);

	static G4int iHitsCollectionID = -1;

	if(iHitsCollectionID < 0)
		iHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	
	pHitsCollectionOfThisEvent->AddHitsCollection(iHitsCollectionID, m_pLXeHitsCollection);

	m_hParticleTypes.clear();
}

G4bool XebraLXeSensitiveDetector::ProcessHits(G4Step* pStep, G4TouchableHistory *)
{
	G4double dEnergyDeposited = pStep->GetTotalEnergyDeposit();
	G4Track *pTrack = pStep->GetTrack();

	XebraLXeHit* pHit = new XebraLXeHit();

	pHit->SetTrackId(pTrack->GetTrackID());
//        G4cout <<" Track weight = "<<pTrack->GetWeight()<<G4endl;

	if(!m_hParticleTypes.count(pTrack->GetTrackID()))
		m_hParticleTypes[pTrack->GetTrackID()] = pTrack->GetDefinition()->GetParticleName();

	pHit->SetParentId(pTrack->GetParentID());
	pHit->SetParticleType(pTrack->GetDefinition()->GetParticleName());

	if(pTrack->GetParentID())
		pHit->SetParentType(m_hParticleTypes[pTrack->GetParentID()]);
	else
		pHit->SetParentType(G4String("none"));

	if(pTrack->GetCreatorProcess())
		pHit->SetCreatorProcess(pTrack->GetCreatorProcess()->GetProcessName());
	else
		pHit->SetCreatorProcess(G4String("Null"));

	pHit->SetDepositingProcess(pStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
	pHit->SetPosition(pStep->GetPostStepPoint()->GetPosition());
	pHit->SetEnergyDeposited(dEnergyDeposited);
	pHit->SetKineticEnergy(pTrack->GetKineticEnergy());
	pHit->SetTime(pTrack->GetGlobalTime());
	
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	pHit->SetPreMomentumDir(pStep->GetPreStepPoint()->GetMomentumDirection());
	pHit->SetPostMomentumDir(pStep->GetPostStepPoint()->GetMomentumDirection());
	pHit->SetPreKineticEnergy(pStep->GetPreStepPoint()->GetKineticEnergy());
	pHit->SetPostKineticEnergy(pStep->GetPostStepPoint()->GetKineticEnergy());

	m_pLXeHitsCollection->insert(pHit);

	return true;
}

void XebraLXeSensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
//  if (verboseLevel>0) { 
//     G4int NbHits = trackerCollection->entries();
//     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
//            << " hits in the tracker chambers: " << G4endl;
//     for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
//    } 
}


//XEBRA header files
#include "XebraPmtSensitiveDetector.hh"

//Additional Header Files
#include <map>

using namespace std;

#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>
#include <G4SystemOfUnits.hh>
#include <G4HCofThisEvent.hh>

XebraPmtSensitiveDetector::XebraPmtSensitiveDetector(G4String hName): G4VSensitiveDetector(hName)
{
	collectionName.insert("PmtHitsCollection");
}

XebraPmtSensitiveDetector::~XebraPmtSensitiveDetector()
{
}

void XebraPmtSensitiveDetector::Initialize(G4HCofThisEvent* pHitsCollectionOfThisEvent)
{
	m_pPmtHitsCollection = new XebraPmtHitsCollection(SensitiveDetectorName, collectionName[0]);

	static G4int iHitsCollectionID = -1;

	if(iHitsCollectionID < 0)
		iHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	
	pHitsCollectionOfThisEvent->AddHitsCollection(iHitsCollectionID, m_pPmtHitsCollection); 
}


G4bool XebraPmtSensitiveDetector::ProcessHits(G4Step* pStep, G4TouchableHistory *)
{
	G4Track *pTrack = pStep->GetTrack();

	if(pTrack->GetDefinition()->GetParticleName() == "opticalphoton")
	{
		XebraPmtHit* pHit = new XebraPmtHit();
		//G4cout << "PMT hit" << pTrack->GetTouchable()->GetVolume(1)->GetCopyNo() << G4endl;// DR 20160720 Testing PMTs sensitivity

		pHit->SetPosition(pStep->GetPreStepPoint()->GetPosition());
		pHit->SetTime(pTrack->GetGlobalTime());
		pHit->SetPmtNb(pTrack->GetTouchable()->GetVolume(1)->GetCopyNo()); //WaterTank PMTs
                //pHit->SetPmtNb(pTrack->GetTouchable()->GetVolume(2)->GetCopyNo()); //TPC PMTs

		m_pPmtHitsCollection->insert(pHit);
		
//		pHit->Print();
//		pHit->Draw();

		return true;
	}
	else
	{
		return false;
	}
}

void XebraPmtSensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
 // if (verboseLevel>0) { 
 //    G4int NbHits = trackerCollection->entries();
 //    G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
 //           << " hits in the tracker chambers: " << G4endl;
 //    for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
 //   } 
}


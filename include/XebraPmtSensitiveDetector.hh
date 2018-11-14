#ifndef __XEBRAPMTSENSITIVEDETECTOR_H__
#define __XEBRAPMTSENSITIVEDETECTOR_H__

//XEBRA header files
#include "XebraPmtHit.hh"

//G4 header files
#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class XebraPmtSensitiveDetector: public G4VSensitiveDetector
{
public:
	XebraPmtSensitiveDetector(G4String hName);
	~XebraPmtSensitiveDetector();

	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);

private:
	XebraPmtHitsCollection* m_pPmtHitsCollection;
};

#endif

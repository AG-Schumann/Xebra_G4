#ifndef __XEBRALSCINTSENSITIVEDETECTOR_H__
#define __XEBRALSCINTSENSITIVEDETECTOR_H__

#include <G4VSensitiveDetector.hh>

#include "XebraLScintHit.hh"

class G4Step;
class G4HCofThisEvent;

class XebraLScintSensitiveDetector: public G4VSensitiveDetector
{
public:
	XebraLScintSensitiveDetector(G4String hName);
	~XebraLScintSensitiveDetector();

	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4double BirksAttenuation(const G4Step* aStep);

private:
	XebraLScintHitsCollection* m_pLScintHitsCollection;

	std::map<int,G4String> m_hParticleTypes;
};

#endif

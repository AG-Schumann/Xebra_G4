#ifndef __XEBRALXESENSITIVEDETECTOR_H__
#define __XEBRALXESENSITIVEDETECTOR_H__

#include <G4VSensitiveDetector.hh>

#include "XebraLXeHit.hh"

class G4Step;
class G4HCofThisEvent;

class XebraLXeSensitiveDetector: public G4VSensitiveDetector
{
public:
        //Constructor
	XebraLXeSensitiveDetector(G4String hName);
        //Destructor
	~XebraLXeSensitiveDetector();

        //mandatory base class
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);

        //optional functions
	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);

private:
	XebraLXeHitsCollection *m_pLXeHitsCollection;
	std::map<int,G4String> m_hParticleTypes;
};

#endif

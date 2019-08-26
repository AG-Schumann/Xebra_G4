//XEBRA header files
#include "XebraAnalysisManager.hh"
#include "XebraStackingAction.hh"

#include <G4ios.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTypes.hh>
#include <G4Track.hh>
#include <G4Event.hh>
#include <G4VProcess.hh>
#include <G4StackManager.hh>
#include <G4TransportationManager.hh>
#include <G4EventManager.hh>

#include <G4SystemOfUnits.hh>

XebraStackingAction::XebraStackingAction(XebraAnalysisManager *pAnalysisManager)
{
	m_pAnalysisManager = pAnalysisManager;
}

XebraStackingAction::~XebraStackingAction()
{
}

G4ClassificationOfNewTrack
XebraStackingAction::ClassifyNewTrack(const G4Track *pTrack)
{
	G4ClassificationOfNewTrack hTrackClassification = fUrgent;

	if(pTrack->GetDefinition()->GetParticleType() == "nucleus" && !pTrack->GetDefinition()->GetPDGStable())
	{
		if(pTrack->GetParentID() > 0 && pTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay" && pTrack->GetDefinition()->GetPDGLifeTime()/ns > 10.)
			hTrackClassification = fPostpone;
	}

	return hTrackClassification;
}

void
XebraStackingAction::NewStage()
{
}

void
XebraStackingAction::PrepareNewEvent()
{ 
}









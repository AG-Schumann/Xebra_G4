#include <G4Event.hh>
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"

#include "XebraEventAction.hh"

XebraEventAction::XebraEventAction(XebraAnalysisManager *pAnalysisManager)
{
  m_pAnalysisManager = pAnalysisManager;
}

XebraEventAction::~XebraEventAction()
{
}

void
XebraEventAction::BeginOfEventAction(const G4Event *pEvent)
{
  if(pEvent->GetEventID() % 1000 == 0)
    {
      G4cout << "------ Begin event " << pEvent->GetEventID()<< "------" << G4endl;
    }
  
  if(m_pAnalysisManager)
    m_pAnalysisManager->BeginOfEvent(pEvent);
}

void XebraEventAction::EndOfEventAction(const G4Event *pEvent)
{
  if(m_pAnalysisManager)
    m_pAnalysisManager->EndOfEvent(pEvent);
}



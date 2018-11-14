//XEBRA header files
#include "XebraAnalysisManager.hh"
#include "XebraRunAction.hh"

//Additional Header Files
#include <Randomize.hh>
#include <sys/time.h>

//G4 header files
#include "G4UImanager.hh"
#include "G4VVisManager.hh"


XebraRunAction::XebraRunAction(XebraAnalysisManager *pAnalysisManager)
{
  m_hRanSeed         = 12345; // default value
  m_pMessenger       = new XebraRunActionMessenger(this);
  
  m_pAnalysisManager = pAnalysisManager;
  
}

XebraRunAction::~XebraRunAction()
{
  delete m_pMessenger;
}

void
XebraRunAction::BeginOfRunAction(const G4Run *pRun)
{
  if(m_pAnalysisManager) {
    //    m_pAnalysisManager->SetForcedTransport(m_hForcedTransport);
    m_pAnalysisManager->BeginOfRun(pRun);
  }
  
  // random seeding of the MC
  if(m_hRanSeed > 0){
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    G4cout << "XebraRunAction::BeginOfRunAction Initialize random numbers with seed = "<<m_hRanSeed<<G4endl;
    CLHEP::HepRandom::setTheSeed(m_hRanSeed);
  } else {
    // initialize with time.....
    struct timeval hTimeValue;
    gettimeofday(&hTimeValue, NULL);
    G4cout << "XebraRunAction::BeginOfRunAction Initialize random numbers with seed = "<<hTimeValue.tv_usec<<G4endl;
    CLHEP::HepRandom::setTheSeed(hTimeValue.tv_usec);
  }
}

void
XebraRunAction::EndOfRunAction(const G4Run *pRun)
{
  if(m_pAnalysisManager)
    m_pAnalysisManager->EndOfRun(pRun);
}


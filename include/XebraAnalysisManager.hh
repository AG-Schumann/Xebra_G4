#ifndef __XEBRAANALYSISMANAGER_H__
#define __XEBRAANALYSISMANAGER_H__

//Additional Header Files
#include <globals.hh>
#include <vector>

//Root Header Files
#include <TParameter.h>
#include <TDirectory.h>

//G4 Header Files
#include <G4Timer.hh>
#include <G4ThreeVector.hh>

class G4Run;
class G4Event;
class G4Step;

class TFile;
class TTree;

class XebraEventData;
class XebraPrimaryGeneratorAction;

class XebraAnalysisManager
{
public:
  XebraAnalysisManager(XebraPrimaryGeneratorAction *pPrimaryGeneratorAction);
  virtual ~XebraAnalysisManager();

public:
  virtual void BeginOfRun(const G4Run *pRun); 
  virtual void EndOfRun(const G4Run *pRun); 
  virtual void BeginOfEvent(const G4Event *pEvent); 
  virtual void EndOfEvent(const G4Event *pEvent); 
  virtual void Step(const G4Step *pStep);	
  
  void SetDataFilename(const G4String &hFilename) { m_hDataFilename = hFilename; }
  void SetNbEventsToSimulate(G4int iNbEventsToSimulate) { m_iNbEventsToSimulate = iNbEventsToSimulate;}

  void FillParticleInSave(G4int flag, G4int partPDGcode, G4ThreeVector pos, G4ThreeVector dir, G4float nrg, G4float time, G4int trackID);

private:
  G4bool FilterEvent(XebraEventData *pEventData);

private:
  G4int m_iLXeHitsCollectionID;
  G4int m_iPmtHitsCollectionID;
  G4int m_iLScintHitsCollectionID;
  
  G4String m_hDataFilename;
  G4int m_iNbEventsToSimulate;

  TFile      *m_pTreeFile;
  TTree      *m_pTree;
  TDirectory *_events;

  TParameter<int> *m_pNbEventsToSimulateParameter;
  // TParameter<double> *nRejectParameter;
  // TParameter<double> *nAcceptParameter;

  XebraPrimaryGeneratorAction *m_pPrimaryGeneratorAction;

  XebraEventData *m_pEventData;
  G4bool            plotPhysics;

  G4Timer *runTime;
  G4bool            writeEmptyEvents;
};

#endif // __XEBRAANALYSISMANAGER_H__

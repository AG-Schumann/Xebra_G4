#ifndef __XEBRARUNACTION_H__
#define __XEBRARUNACTION_H__

#include <G4UserRunAction.hh>
#include "XebraRunActionMessenger.hh"

class G4Run;

class XebraAnalysisManager;


class XebraRunAction: public G4UserRunAction
{
public:
	XebraRunAction(XebraAnalysisManager *pAnalysisManager=0);
	~XebraRunAction();

public:
	void BeginOfRunAction(const G4Run *pRun);
	void EndOfRunAction(const G4Run *pRun);
        
	void SetRanSeed(G4int hRanSeed) { m_hRanSeed = hRanSeed; }
//	void SetForcedTransport(G4bool doit) { m_hForcedTransport = doit; }

private:
	G4int m_hRanSeed;
//        G4bool m_hForcedTransport;
	XebraAnalysisManager *m_pAnalysisManager;
	XebraRunActionMessenger *m_pMessenger;
};

#endif

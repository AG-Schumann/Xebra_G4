#ifndef __XEBRAEVENTACTION_H__
#define __XEBRAEVENTACTION_H__

#include <G4UserEventAction.hh>

#include "XebraAnalysisManager.hh"

class G4Event;

class XebraEventAction : public G4UserEventAction
{
public:
	XebraEventAction(XebraAnalysisManager *pAnalysisManager = 0);
	~XebraEventAction();

public:
	void BeginOfEventAction(const G4Event *pEvent);
	void EndOfEventAction(const G4Event *pEvent);

private:
	XebraAnalysisManager *m_pAnalysisManager;
};

#endif // __XEBRAEVENTACTION_H__


#ifndef __XEBRASTACKINGACTION_H__
#define __XEBRASTACKINGACTION_H__

//Additional Header FIles
#include <globals.hh>

//G4 Header Files
#include <G4UserStackingAction.hh>


class XebraAnalysisManager;

class XebraStackingAction: public G4UserStackingAction
{
public:
	XebraStackingAction(XebraAnalysisManager *pAnalysisManager=0);
	~XebraStackingAction();
  
	virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
	virtual void NewStage();
	virtual void PrepareNewEvent();

private:
	XebraAnalysisManager *m_pAnalysisManager;
};

#endif

#ifndef XebraSteppingAction_H
#define XebraSteppingAction_H 1

//Additional Header Files
#include "globals.hh"

//G4 Header Files
#include "G4UserSteppingAction.hh"
class XebraAnalysisManager;

class XebraSteppingAction : public G4UserSteppingAction
{
    public:
        XebraSteppingAction(XebraAnalysisManager*);
        ~XebraSteppingAction(){};

         void UserSteppingAction(const G4Step*);

    private:
        G4String particle;
        XebraAnalysisManager* myAnalysisManager;
};

#endif

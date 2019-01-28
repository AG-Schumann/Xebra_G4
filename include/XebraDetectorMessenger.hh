#ifndef XEBRADetectorMessenger_h
#define XEBRADetectorMessenger_h 1

//Additional Header Files
#include <globals.hh>

//G4 Header Files
#include <G4UImessenger.hh>

//XEBRA Classes
class XebraDetectorConstruction;

//G4 Classes
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class XebraDetectorMessenger: public G4UImessenger
{
  public:
    XebraDetectorMessenger(XebraDetectorConstruction *pXeDetector);
    ~XebraDetectorMessenger();

    void     SetNewValue(G4UIcommand *pUIcommand, G4String hString);
    //G4String GetCurrentValue(G4UIcommand *pUIcommand);
  
  private:
   XebraDetectorConstruction *m_pXeDetector;

    G4UIdirectory *m_pDetectorDir;

    G4UIcmdWithADouble *m_pTeflonReflectivityCmd;
    G4UIcmdWithABool *m_pLXeScintillationCmd;
    G4UIcmdWithABool *m_pGdLScintScintillationCmd;
    G4UIcmdWithADoubleAndUnit *m_pLXeAbsorbtionLengthCmd;
    G4UIcmdWithADoubleAndUnit *m_pLXeRayScatterLengthCmd;
  
    // SERENA.....
  
    // APC 25-07-2011
	//
	// In order to run with different materials and wall thicknesses
	//
    G4UIcmdWithAString        *m_pCryostatTypeCmd;
    G4UIcmdWithAString        *m_pCryostatMaterialCmd;
    G4UIcmdWithAString        *m_pNeutronSourceSurroundingsCmd;
    G4UIcmdWithADoubleAndUnit *m_pCryostatOuterWallCmd;
    G4UIcmdWithADoubleAndUnit *m_pCryostatInnerWallCmd;
    G4UIcmdWithADoubleAndUnit *m_pCryostatInnerODCmd;
    G4UIcmdWithADoubleAndUnit *m_pCryostatOuterODCmd;
    
    /*G4UIcmdWithAString        *m_pMuonVetoMaterialCmd;
    G4UIcmdWithABool          *m_pConstructLScintTopVesselCmd;
    G4UIcmdWithADoubleAndUnit *m_pLScintVesselThicknessSidesCmd;
    G4UIcmdWithADoubleAndUnit *m_pLScintVesselThicknessTopBottomCmd;
    G4UIcmdWithAString        *m_pLScintNumberOfSideVesselsCmd;
    G4UIcmdWithAString        *m_pLScintVesselMaterialCmd;
    G4UIcmdWithABool          *m_pSetFillBufferCmd;
    G4UIcmdWithADoubleAndUnit *m_pSetBufferThicknessCmd;
    G4UIcmdWithABool          *m_pSetTpcWithBellCmd;*/
    // do we want tot check for overlapping objects?
    G4UIcmdWithABool          *m_pCheckOverlapCmd;
    G4UIcmdWithABool          *m_pSetTPCCmd;
    
    // Added by Alex
    G4UIcmdWithADoubleAndUnit *m_pLXeLevelCmd;
		G4UIcmdWithAString	*m_pMaterCmd;
		G4UIcmdWithAString	*m_pLXeMeshMaterialCmd;
		G4UIcmdWithAString	*m_pGXeMeshMaterialCmd;
		G4UIcmdWithADouble *m_pGXeTeflonReflectivityCmd;
		G4UIcmdWithADoubleAndUnit *m_pGXeAbsorbtionLengthCmd;
		G4UIcmdWithADouble *m_pLXeRefractionIndexCmd;
		G4UIcmdWithADouble *m_pGridMeshTransparencyCmd;
		G4UIcmdWithADouble *m_pLXeMeshTransparencyCmd;
		G4UIcmdWithADouble *m_pGXeMeshTransparencyCmd;

};

#endif

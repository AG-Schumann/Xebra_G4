#ifndef __XEBRAEVENTDATA_H__
#define __XEBRAEVENTDATA_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

class XebraEventData
{
public:
	 XebraEventData();
	~XebraEventData();

public:
	void Clear();

public:
	int m_iEventId;						// the event ID
	int m_iNbTopPmtHits;					// number of top pmt hits
	int m_iNbBottomPmtHits;					// number of bottom pmt hits
	int m_iNbLSPmtHits;					// number of LS pmt hits
	int m_iNbWaterPmtHits;					// number of water pmt hits
	vector<int> *m_pPmtHits;				// number of photon hits per pmt
	float m_fTotalEnergyDeposited;				// total energy deposited in the SD
	int m_iNbSteps;						// number of energy depositing steps
	vector<int> *m_pTrackId;				// id of the particle
	vector<int> *m_pParentId;				// id of the parent particle
	vector<string> *m_pParticleType;			// type of particle
	vector<string> *m_pParentType;				// type of particle
	vector<string> *m_pCreatorProcess;			// interaction
	vector<string> *m_pDepositingProcess;			// energy depositing process
	vector<float> *m_pX;					// position of the step
	vector<float> *m_pY;
	vector<float> *m_pZ;
	vector<float> *m_pEnergyDeposited; 			// energy deposited in the step
	vector<float> *m_pKineticEnergy;			// particle kinetic energy after the step
	vector<float> *m_pTime;					// time of the step
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	vector<float> *m_pPreMomDirX;				// momentum direction before the hit
	vector<float> *m_pPreMomDirY;
	vector<float> *m_pPreMomDirZ;
	vector<float> *m_pPostMomDirX;				// momentum direction after the hit
	vector<float> *m_pPostMomDirY;
	vector<float> *m_pPostMomDirZ;
	vector<float> *m_pPreKineticEnergy;			// kinetic energy before the hit
	vector<float> *m_pPostKineticEnergy;			// kinetic energy after the hit
	
	float m_fLScintTotalEnergyDeposited;
	int m_iLScintNbSteps;
	vector<int> *m_pLScintTrackId;
	vector<int> *m_pLScintParentId;
	vector<string> *m_pLScintParticleType;
	vector<string> *m_pLScintParentType;
	vector<string> *m_pLScintCreatorProcess;
	vector<string> *m_pLScintDepositingProcess;
	vector<float> *m_pLScintX;
	vector<float> *m_pLScintY;
	vector<float> *m_pLScintZ;
	vector<float> *m_pLScintEnergyDeposited;
	vector<float> *m_pLScintEnergyDepositedBirksCorrected;
	vector<float> *m_pLScintKineticEnergy;
	vector<float> *m_pLScintTime;
	
	vector<string> *m_pPrimaryParticleType;			// type of particle
	float m_fPrimaryX;					// position of the primary particle
	float m_fPrimaryY;
	float m_fPrimaryZ;	
	float m_fForcedPrimaryX;				// position of the primary particle
	float m_fForcedPrimaryY;
	float m_fForcedPrimaryZ;	
	float m_fPrimaryE;	
	float m_fPrimaryW;	

  //MS In the following bank we save particle information in various positions, for ex. 
  //- entering the OuterCryostat from outside ... i.e. those crossing the whole shield
  //- neutron capture in the water or LS shield
  //NOT YET- optical photons when touching the tank surfaces
  //NOT YET- entering the active LXe volume (between anode and cathode)

	int	m_iNSave;        
	vector<int> *m_pSave_flag;
	vector<int> *m_pSave_type;
	vector<float> *m_pSave_x;
	vector<float> *m_pSave_y;
	vector<float> *m_pSave_z;
	vector<float> *m_pSave_cx;
	vector<float> *m_pSave_cy;
	vector<float> *m_pSave_cz;
	vector<float> *m_pSave_e;
	vector<float> *m_pSave_t;
	vector<int> *m_pSave_trkid;

};

#endif

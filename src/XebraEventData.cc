#include "XebraEventData.hh"

XebraEventData::XebraEventData()
{
	m_iEventId = 0;
	m_iNbTopPmtHits = 0;
	m_iNbBottomPmtHits = 0;
	m_iNbLSPmtHits = 0;
	m_iNbWaterPmtHits = 0;
	m_pPmtHits = new vector<int>;

	m_fTotalEnergyDeposited = 0.;
	m_iNbSteps = 0;
	m_pTrackId = new vector<int>;
	m_pParentId = new vector<int>;
	m_pParticleType = new vector<string>;
	m_pParentType = new vector<string>;
	m_pCreatorProcess = new vector<string>;
	m_pDepositingProcess = new vector<string>;
	m_pX = new vector<float>;
	m_pY = new vector<float>;
	m_pZ = new vector<float>;
	m_pEnergyDeposited = new vector<float>;
	m_pKineticEnergy = new vector<float>;
	m_pTime = new vector<float>;
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	m_pPreMomDirX = new vector<float>;
	m_pPreMomDirY = new vector<float>;
	m_pPreMomDirZ = new vector<float>;
	m_pPostMomDirX = new vector<float>;
	m_pPostMomDirY = new vector<float>;
	m_pPostMomDirZ = new vector<float>;
	m_pPreKineticEnergy = new vector<float>;
	m_pPostKineticEnergy = new vector<float>;

	// DR 20160906 - Branches for the hits in the LScint vessels
	m_fLScintTotalEnergyDeposited = 0.;
	m_iLScintNbSteps = 0;
	m_pLScintTrackId = new vector<int>;
	m_pLScintParentId = new vector<int>;
	m_pLScintParticleType = new vector<string>;
	m_pLScintParentType = new vector<string>;
	m_pLScintCreatorProcess = new vector<string>;
	m_pLScintDepositingProcess = new vector<string>;
	m_pLScintX = new vector<float>;
	m_pLScintY = new vector<float>;
	m_pLScintZ = new vector<float>;
	m_pLScintEnergyDeposited = new vector<float>;
	m_pLScintEnergyDepositedBirksCorrected = new vector<float>;
	m_pLScintKineticEnergy = new vector<float>;
	m_pLScintTime = new vector<float>;

	m_pPrimaryParticleType = new vector<string>;
	m_fPrimaryX = 0.;
	m_fPrimaryY = 0.;
	m_fPrimaryZ = 0.;
	m_fForcedPrimaryX = 0.;
	m_fForcedPrimaryY = 0.;
	m_fForcedPrimaryZ = 0.;
	m_fPrimaryE = 0.;

	m_iNSave = 0;
	m_pSave_flag = new vector<int>;
	m_pSave_type = new vector<int>;
	m_pSave_x = new vector<float>;
	m_pSave_y = new vector<float>;
	m_pSave_z = new vector<float>;
	m_pSave_cx = new vector<float>;
	m_pSave_cy = new vector<float>;
	m_pSave_cz = new vector<float>;
	m_pSave_e = new vector<float>;
	m_pSave_t = new vector<float>;
	m_pSave_trkid = new vector<int>;

}

XebraEventData::~XebraEventData()
{
	delete m_pPmtHits;

	delete m_pTrackId;
	delete m_pParentId;
	delete m_pParticleType;
	delete m_pParentType;
	delete m_pCreatorProcess;
	delete m_pDepositingProcess;
	delete m_pX;
	delete m_pY;
	delete m_pZ;
	delete m_pEnergyDeposited;
	delete m_pKineticEnergy;
	delete m_pTime;
	delete m_pPreMomDirX;
	delete m_pPreMomDirY;
	delete m_pPreMomDirZ;
	delete m_pPostMomDirX;
	delete m_pPostMomDirY;
	delete m_pPostMomDirZ;
	delete m_pPreKineticEnergy;
	delete m_pPostKineticEnergy;

	delete m_pLScintTrackId;
	delete m_pLScintParentId;
	delete m_pLScintParticleType;
	delete m_pLScintParentType;
	delete m_pLScintCreatorProcess;
	delete m_pLScintDepositingProcess;
	delete m_pLScintX;
	delete m_pLScintY;
	delete m_pLScintZ;
	delete m_pLScintEnergyDeposited;
	delete m_pLScintEnergyDepositedBirksCorrected;
	delete m_pLScintKineticEnergy;
	delete m_pLScintTime;

	delete m_pPrimaryParticleType;

	delete m_pSave_flag ;
	delete m_pSave_type ;
	delete m_pSave_x ;
	delete m_pSave_y ;
	delete m_pSave_z ;
	delete m_pSave_cx ;
	delete m_pSave_cy ;
	delete m_pSave_cz ;
	delete m_pSave_e ;
	delete m_pSave_t ;
	delete m_pSave_trkid ;

}

void
XebraEventData::Clear()
{
	m_iEventId = 0;
	m_iNbTopPmtHits = 0;
	m_iNbBottomPmtHits = 0;
	m_iNbLSPmtHits = 0;
	m_iNbWaterPmtHits = 0;
	m_pPmtHits->clear();

	m_fTotalEnergyDeposited = 0.0;
	m_iNbSteps = 0;
	m_pTrackId->clear();
	m_pParentId->clear();
	m_pParticleType->clear();
	m_pParentType->clear();
	m_pCreatorProcess->clear();
	m_pDepositingProcess->clear();
	m_pX->clear();
	m_pY->clear();
	m_pZ->clear();
	m_pEnergyDeposited->clear();
	m_pKineticEnergy->clear();
	m_pTime->clear();
	m_pPreMomDirX->clear();
	m_pPreMomDirY->clear();
	m_pPreMomDirZ->clear();
	m_pPostMomDirX->clear();
	m_pPostMomDirY->clear();
	m_pPostMomDirZ->clear();
	m_pPreKineticEnergy->clear();
	m_pPostKineticEnergy->clear();

	m_fLScintTotalEnergyDeposited = 0.0;
	m_iLScintNbSteps = 0;
	m_pLScintTrackId->clear();
	m_pLScintParentId->clear();
	m_pLScintParticleType->clear();
	m_pLScintParentType->clear();
	m_pLScintCreatorProcess->clear();
	m_pLScintDepositingProcess->clear();
	m_pLScintX->clear();
	m_pLScintY->clear();
	m_pLScintZ->clear();
	m_pLScintEnergyDeposited->clear();
	m_pLScintEnergyDepositedBirksCorrected->clear();
	m_pLScintKineticEnergy->clear();
	m_pLScintTime->clear();

	m_pPrimaryParticleType->clear();
	m_fPrimaryX = 0.;
	m_fPrimaryY = 0.;
	m_fPrimaryZ = 0.;	
	m_fPrimaryE = 0.;
	m_fPrimaryW = 0.;

	m_iNSave = 0;
	m_pSave_flag->clear();
	m_pSave_type->clear();
	m_pSave_x->clear(); 
	m_pSave_y->clear(); 
	m_pSave_z->clear(); 
	m_pSave_cx->clear(); 
	m_pSave_cy->clear(); 
	m_pSave_cz->clear(); 
	m_pSave_e->clear();
	m_pSave_t->clear();
	m_pSave_trkid->clear();
}

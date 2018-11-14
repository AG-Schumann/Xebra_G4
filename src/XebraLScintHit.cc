#include <G4SystemOfUnits.hh>

#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

#include "XebraLScintHit.hh"



G4Allocator<XebraLScintHit> XebraLScintHitAllocator;

XebraLScintHit::XebraLScintHit() {}

XebraLScintHit::~XebraLScintHit()
{
	if(m_pLScintParticleType) delete m_pLScintParticleType;
	if(m_pLScintParentType) delete m_pLScintParentType;
	if(m_pLScintCreatorProcess) delete m_pLScintCreatorProcess;
	if(m_pLScintDepositingProcess) delete m_pLScintDepositingProcess;
}

XebraLScintHit::XebraLScintHit(const XebraLScintHit &hXebraLScintHit):G4VHit()
{
	m_iLScintTrackId = hXebraLScintHit.m_iLScintTrackId;
	m_iLScintParentId = hXebraLScintHit.m_iLScintParentId;
	m_pLScintParticleType = hXebraLScintHit.m_pLScintParticleType;
	m_pLScintParentType = hXebraLScintHit.m_pLScintParentType ;
	m_pLScintCreatorProcess = hXebraLScintHit.m_pLScintCreatorProcess ;
	m_pLScintDepositingProcess = hXebraLScintHit.m_pLScintDepositingProcess ;
	m_hLScintPosition = hXebraLScintHit.m_hLScintPosition;
	m_dLScintEnergyDeposited = hXebraLScintHit.m_dLScintEnergyDeposited;
	m_dLScintKineticEnergy = hXebraLScintHit.m_dLScintKineticEnergy ;
	m_dLScintTime = hXebraLScintHit.m_dLScintTime;
}

const XebraLScintHit &
XebraLScintHit::operator=(const XebraLScintHit &hXebraLScintHit)
{
	m_iLScintTrackId = hXebraLScintHit.m_iLScintTrackId;
	m_iLScintParentId = hXebraLScintHit.m_iLScintParentId;
	m_pLScintParticleType = hXebraLScintHit.m_pLScintParticleType;
	m_pLScintParentType = hXebraLScintHit.m_pLScintParentType ;
	m_pLScintCreatorProcess = hXebraLScintHit.m_pLScintCreatorProcess ;
	m_pLScintDepositingProcess = hXebraLScintHit.m_pLScintDepositingProcess ;
	m_hLScintPosition = hXebraLScintHit.m_hLScintPosition;
	m_dLScintEnergyDeposited = hXebraLScintHit.m_dLScintEnergyDeposited;
	m_dLScintKineticEnergy = hXebraLScintHit.m_dLScintKineticEnergy ;
	m_dLScintTime = hXebraLScintHit.m_dLScintTime;
	
	return *this;
}

G4int
XebraLScintHit::operator==(const XebraLScintHit &hXebraLScintHit) const
{
	return ((this == &hXebraLScintHit) ? (1) : (0));
}

void XebraLScintHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	
	if(pVVisManager)
	{
		G4Circle hCircle(m_hLScintPosition);
		G4Colour hColour(1.000, 0.973, 0.184);
		G4VisAttributes hVisAttributes(hColour);
		
		hCircle.SetScreenSize(0.1);
		hCircle.SetFillStyle(G4Circle::filled);
		hCircle.SetVisAttributes(hVisAttributes);
		pVVisManager->Draw(hCircle);
	}
}

void XebraLScintHit::Print()
{
	G4cout << "-------------------- LScint hit --------------------" 
		<< "LScint_Id: " << m_iLScintTrackId
		<< "LScint_Particle: " << *m_pLScintParticleType
		<< "LScint_ParentId: " << m_iLScintParentId
		<< "LScint_ParentType: " << *m_pLScintParentType << G4endl
		<< "LScint_CreatorProcess: " << *m_pLScintCreatorProcess
		<< "LScint_DepositingProcess: " << *m_pLScintDepositingProcess << G4endl
		<< "LScint_Position: " << m_hLScintPosition.x()/mm
		<< " " << m_hLScintPosition.y()/mm
		<< " " << m_hLScintPosition.z()/mm
		<< " mm" << G4endl
		<< "LScint_EnergyDeposited: " << m_dLScintEnergyDeposited/keV << " keV"
		<< "LScint_KineticEnergyLeft: " << m_dLScintKineticEnergy/keV << " keV"
		<< "LScint_Time: " << m_dLScintTime/s << " s" << G4endl;
}


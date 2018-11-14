#include <G4SystemOfUnits.hh>

#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

#include "XebraLXeHit.hh"


G4Allocator<XebraLXeHit> XebraLXeHitAllocator;

XebraLXeHit::XebraLXeHit() {}

XebraLXeHit::~XebraLXeHit()
{
	if(m_pParticleType) delete m_pParticleType;
	if(m_pParentType) delete m_pParentType;
	if(m_pCreatorProcess) delete m_pCreatorProcess;
	if(m_pDepositingProcess) delete m_pDepositingProcess;
}

XebraLXeHit::XebraLXeHit(const XebraLXeHit &hXebraLXeHit):G4VHit()
{
	m_iTrackId = hXebraLXeHit.m_iTrackId;
	m_iParentId = hXebraLXeHit.m_iParentId;
	m_pParticleType = hXebraLXeHit.m_pParticleType;
	m_pParentType = hXebraLXeHit.m_pParentType;
	m_pCreatorProcess = hXebraLXeHit.m_pCreatorProcess;
	m_pDepositingProcess = hXebraLXeHit.m_pDepositingProcess;
	m_hPosition = hXebraLXeHit.m_hPosition;
	m_dEnergyDeposited = hXebraLXeHit.m_dEnergyDeposited;
	m_dKineticEnergy = hXebraLXeHit.m_dKineticEnergy;
	m_dTime = hXebraLXeHit.m_dTime;
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	m_hPreMomentumDir = hXebraLXeHit.m_hPreMomentumDir;
	m_hPostMomentumDir = hXebraLXeHit.m_hPostMomentumDir;
	m_dPreKineticEnergy = hXebraLXeHit.m_dPreKineticEnergy;
	m_dPostKineticEnergy = hXebraLXeHit.m_dPostKineticEnergy;
}

const XebraLXeHit &
XebraLXeHit::operator=(const XebraLXeHit &hXebraLXeHit)
{
	m_iTrackId = hXebraLXeHit.m_iTrackId;
	m_iParentId = hXebraLXeHit.m_iParentId;
	m_pParticleType = hXebraLXeHit.m_pParticleType;
	m_pParentType = hXebraLXeHit.m_pParentType;
	m_pCreatorProcess = hXebraLXeHit.m_pCreatorProcess;
	m_pDepositingProcess = hXebraLXeHit.m_pDepositingProcess;
	m_hPosition = hXebraLXeHit.m_hPosition;
	m_dEnergyDeposited = hXebraLXeHit.m_dEnergyDeposited;
	m_dKineticEnergy = hXebraLXeHit.m_dKineticEnergy;
	m_dTime = hXebraLXeHit.m_dTime;
	m_hPreMomentumDir = hXebraLXeHit.m_hPreMomentumDir;
	m_hPostMomentumDir = hXebraLXeHit.m_hPostMomentumDir;
	m_dPreKineticEnergy = hXebraLXeHit.m_dPreKineticEnergy;
	m_dPostKineticEnergy = hXebraLXeHit.m_dPostKineticEnergy;
	
	return *this;
}

G4int
XebraLXeHit::operator==(const XebraLXeHit &hXebraLXeHit) const
{
	return ((this == &hXebraLXeHit) ? (1) : (0));
}

void XebraLXeHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	
	if(pVVisManager)
	{
		G4Circle hCircle(m_hPosition);
		G4Colour hColour(1.000, 0.973, 0.184);
		G4VisAttributes hVisAttributes(hColour);
		
		hCircle.SetScreenSize(0.1);
		hCircle.SetFillStyle(G4Circle::filled);
		hCircle.SetVisAttributes(hVisAttributes);
		pVVisManager->Draw(hCircle);
	}
}

void XebraLXeHit::Print()
{
	 G4cout << "-------------------- LXe hit --------------------" 
		<< "Id: " << m_iTrackId
		<< " Particle: " << *m_pParticleType
		<< " ParentId: " << m_iParentId
		<< " ParentType: " << *m_pParentType << G4endl
		<< " CreatorProcess: " << *m_pCreatorProcess
		<< " DepositingProcess: " << *m_pDepositingProcess << G4endl
		<< " Position: " << m_hPosition.x()/mm
		<< " " << m_hPosition.y()/mm
		<< " " << m_hPosition.z()/mm
		<< " mm" << G4endl
		<< " EnergyDeposited: " << m_dEnergyDeposited/keV << " keV"
		<< " KineticEnergyLeft: " << m_dKineticEnergy/keV << " keV"
		<< " Time: " << m_dTime/s << " s" << G4endl
		<< " Momentum direction before hit: " << m_hPreMomentumDir.x()	// DR 20161012
		<< " " << m_hPreMomentumDir.y()
		<< " " << m_hPreMomentumDir.z() << G4endl
		<< " Momentum direction after hit: " << m_hPostMomentumDir.x()
		<< " " << m_hPostMomentumDir.y()
		<< " " << m_hPostMomentumDir.z() << G4endl
		<< " KineticEnergy before hit: " << m_dPreKineticEnergy/keV << " keV"
		<< " Kinetic Energy after hit: " << m_dPostKineticEnergy/keV << " keV" << G4endl;
}


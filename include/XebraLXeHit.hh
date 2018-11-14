#ifndef __XEBRALXEHIT_H__
#define __XEBRALXEHIT_H__

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>

class XebraLXeHit: public G4VHit
{
public:
	XebraLXeHit();
	~XebraLXeHit();
	XebraLXeHit(const XebraLXeHit &);
	const XebraLXeHit & operator=(const XebraLXeHit &);
	G4int operator==(const XebraLXeHit &) const;

	inline void* operator new(size_t);
	inline void  operator delete(void*);

	void Draw();
	void Print();

public:
	void SetTrackId(G4int iTrackId) { m_iTrackId = iTrackId; };
	void SetParentId(G4int iParentId) { m_iParentId = iParentId; };
	void SetParticleType(const G4String &hParticleType) { m_pParticleType = new G4String(hParticleType); }
	void SetParentType(const G4String &hParentType) { m_pParentType = new G4String(hParentType); }
	void SetCreatorProcess(const G4String &hProcessName) { m_pCreatorProcess = new G4String(hProcessName); }
	void SetDepositingProcess(const G4String &hProcessName) { m_pDepositingProcess = new G4String(hProcessName); }
	void SetPosition(G4ThreeVector hPosition) { m_hPosition = hPosition; };
	void SetEnergyDeposited(G4double dEnergyDeposited) { m_dEnergyDeposited = dEnergyDeposited; };
	void SetKineticEnergy(G4double dKineticEnergy) { m_dKineticEnergy = dKineticEnergy; };
	void SetTime(G4double dTime) { m_dTime = dTime; };
	// DR 20161012 - Branches to save incoming and outcoming energy in LXe. Useful for analysis of the single scatter events in the active volume.
	void SetPreMomentumDir(G4ThreeVector hPreMomentumDir) {m_hPreMomentumDir = hPreMomentumDir; };
	void SetPostMomentumDir(G4ThreeVector hPostMomentumDir) {m_hPostMomentumDir = hPostMomentumDir; };
	void SetPreKineticEnergy(G4double dPreKineticEnergy) {m_dPreKineticEnergy = dPreKineticEnergy; };
	void SetPostKineticEnergy(G4double dPostKineticEnergy) {m_dPostKineticEnergy = dPostKineticEnergy; };

	G4int GetTrackId() { return m_iTrackId; };
	G4int GetParentId() { return m_iParentId; };
	const G4String &GetParticleType() { return *m_pParticleType; }
	const G4String &GetParentType() { return *m_pParentType; }
	const G4String &GetCreatorProcess() { return *m_pCreatorProcess; }
	const G4String &GetDepositingProcess() { return *m_pDepositingProcess; }
	G4ThreeVector GetPosition() { return m_hPosition; };
	G4double GetEnergyDeposited() { return m_dEnergyDeposited; };      
	G4double GetKineticEnergy() { return m_dKineticEnergy; };      
	G4double GetTime() { return m_dTime; };      
	G4ThreeVector GetPreMomentumDir() {return m_hPreMomentumDir; };
	G4ThreeVector GetPostMomentumDir() {return m_hPostMomentumDir; };
	G4double GetPreKineticEnergy() {return m_dPreKineticEnergy; };
	G4double GetPostKineticEnergy() {return m_dPostKineticEnergy; };

private:
	G4int m_iTrackId;
	G4int m_iParentId;
	G4String *m_pParticleType;
	G4String *m_pParentType;
	G4String *m_pCreatorProcess;
	G4String *m_pDepositingProcess;
	G4ThreeVector m_hPosition;
	G4double m_dEnergyDeposited;
	G4double m_dKineticEnergy;
	G4double m_dTime;
	G4ThreeVector m_hPreMomentumDir;
	G4ThreeVector m_hPostMomentumDir;
	G4double m_dPreKineticEnergy;
	G4double m_dPostKineticEnergy;
};

typedef G4THitsCollection<XebraLXeHit> XebraLXeHitsCollection;

extern G4Allocator<XebraLXeHit> XebraLXeHitAllocator;

inline void*
XebraLXeHit::operator new(size_t)
{
	return((void *) XebraLXeHitAllocator.MallocSingle());
}

inline void
XebraLXeHit::operator delete(void *pXebraLXeHit)
{
	XebraLXeHitAllocator.FreeSingle((XebraLXeHit*) pXebraLXeHit);
}

#endif

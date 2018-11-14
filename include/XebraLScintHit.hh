#ifndef __XEBRALSCINTHIT_H__
#define __XEBRALSCINTHIT_H__

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>

class XebraLScintHit: public G4VHit
{
public:
	XebraLScintHit();
	~XebraLScintHit();
	XebraLScintHit(const XebraLScintHit &);
	const XebraLScintHit & operator=(const XebraLScintHit &);
	G4int operator==(const XebraLScintHit &) const;

	inline void* operator new(size_t);
	inline void  operator delete(void*);

	void Draw();
	void Print();

public:
	void SetTrackId(G4int iTrackId) { m_iLScintTrackId = iTrackId; };
	void SetParentId(G4int iParentId) { m_iLScintParentId = iParentId; };
	void SetParticleType(const G4String &hParticleType) { m_pLScintParticleType = new G4String(hParticleType); }
	void SetParentType(const G4String &hParentType) { m_pLScintParentType = new G4String(hParentType); }
	void SetCreatorProcess(const G4String &hProcessName) { m_pLScintCreatorProcess = new G4String(hProcessName); }
	void SetDepositingProcess(const G4String &hProcessName) { m_pLScintDepositingProcess = new G4String(hProcessName); }
	void SetPosition(G4ThreeVector hPosition) { m_hLScintPosition = hPosition; };
	void SetEnergyDeposited(G4double dEnergyDeposited) { m_dLScintEnergyDeposited = dEnergyDeposited; };
	void SetEnergyDepositedBirksCorrected(G4double dEnergyDepositedBirksCorrected) { m_dLScintEnergyDepositedBirksCorrected = dEnergyDepositedBirksCorrected; };
	void SetKineticEnergy(G4double dKineticEnergy) { m_dLScintKineticEnergy = dKineticEnergy; };
	void SetTime(G4double dTime) { m_dLScintTime = dTime; };

	G4int GetTrackId() { return m_iLScintTrackId; };
	G4int GetParentId() { return m_iLScintParentId; };
	const G4String &GetParticleType() { return *m_pLScintParticleType; }
	const G4String &GetParentType() { return *m_pLScintParentType; }
	const G4String &GetCreatorProcess() { return *m_pLScintCreatorProcess; }
	const G4String &GetDepositingProcess() { return *m_pLScintDepositingProcess; }
	G4ThreeVector GetPosition() { return m_hLScintPosition; };
	G4double GetEnergyDeposited() { return m_dLScintEnergyDeposited; };  
	G4double GetEnergyDepositedBirksCorrected() { return m_dLScintEnergyDepositedBirksCorrected; };
	G4double GetKineticEnergy() { return m_dLScintKineticEnergy; };      
	G4double GetTime() { return m_dLScintTime; };      

private:
	G4int m_iLScintTrackId;
	G4int m_iLScintParentId;
	G4String *m_pLScintParticleType;
	G4String *m_pLScintParentType;
	G4String *m_pLScintCreatorProcess;
	G4String *m_pLScintDepositingProcess;
	G4ThreeVector m_hLScintPosition;
	G4double m_dLScintEnergyDeposited;
	G4double m_dLScintEnergyDepositedBirksCorrected;
	G4double m_dLScintKineticEnergy;
	G4double m_dLScintTime;
};

typedef G4THitsCollection<XebraLScintHit> XebraLScintHitsCollection;

extern G4Allocator<XebraLScintHit> XebraLScintHitAllocator;

inline void*
XebraLScintHit::operator new(size_t)
{
	return((void *) XebraLScintHitAllocator.MallocSingle());
}

inline void
XebraLScintHit::operator delete(void *pXebraLScintHit)
{
	XebraLScintHitAllocator.FreeSingle((XebraLScintHit*) pXebraLScintHit);
}

#endif

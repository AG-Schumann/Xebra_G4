#ifndef __XEBRAPMTHIT_H__
#define __XEBRAPMTHIT_H__

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>

class XebraPmtHit: public G4VHit
{
public:
	XebraPmtHit();
	~XebraPmtHit();
	XebraPmtHit(const XebraPmtHit &);
	const XebraPmtHit & operator=(const XebraPmtHit &);
	G4int operator==(const XebraPmtHit &) const;

	inline void* operator new(size_t);
	inline void  operator delete(void*);

	void Draw();
	void Print();

public:
	void SetPosition(G4ThreeVector hPosition) { m_hPosition = hPosition; }
	void SetTime(G4double dTime) { m_dTime = dTime; }
	void SetPmtNb(G4int iPmtNb) { m_iPmtNb = iPmtNb; }

	G4ThreeVector GetPosition() { return m_hPosition; }
	G4double GetTime() { return m_dTime; }
	G4int GetPmtNb() { return m_iPmtNb; }

private:
	G4ThreeVector m_hPosition;
	G4double m_dTime;
	G4int m_iPmtNb;
};

typedef G4THitsCollection<XebraPmtHit> XebraPmtHitsCollection;

extern G4Allocator<XebraPmtHit> XebraPmtHitAllocator;

inline void*
XebraPmtHit::operator new(size_t)
{
	return((void *) XebraPmtHitAllocator.MallocSingle());
}

inline void
XebraPmtHit::operator delete(void *pXebraPmtHit)
{
	XebraPmtHitAllocator.FreeSingle((XebraPmtHit*) pXebraPmtHit);
}

#endif

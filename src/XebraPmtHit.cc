#include <G4SystemOfUnits.hh>

#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

#include "XebraPmtHit.hh"


G4Allocator<XebraPmtHit> XebraPmtHitAllocator;

XebraPmtHit::XebraPmtHit() {}

XebraPmtHit::~XebraPmtHit() {}

XebraPmtHit::XebraPmtHit(const XebraPmtHit &hXebraPmtHit):G4VHit()
{
	m_hPosition = hXebraPmtHit.m_hPosition;
	m_dTime = hXebraPmtHit.m_dTime;
	m_iPmtNb = hXebraPmtHit.m_iPmtNb;
}

const XebraPmtHit &
XebraPmtHit::operator=(const XebraPmtHit &hXebraPmtHit)
{
	m_hPosition = hXebraPmtHit.m_hPosition;
	m_dTime = hXebraPmtHit.m_dTime;
	m_iPmtNb = hXebraPmtHit.m_iPmtNb;
	
	return *this;
}

G4int
XebraPmtHit::operator==(const XebraPmtHit &hXebraPmtHit) const
{
	return ((this == &hXebraPmtHit) ? (1) : (0));
}

void XebraPmtHit::Draw()
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

void XebraPmtHit::Print()
{
	G4cout << "Pmt hit ---> " 
		<< "Pmt#" << m_iPmtNb
		<< " Position: " << m_hPosition.x()/mm
		<< " " << m_hPosition.y()/mm
		<< " " << m_hPosition.z()/mm
		<< " mm"
		<< " Time: " << m_dTime/s << " s" << G4endl;
}


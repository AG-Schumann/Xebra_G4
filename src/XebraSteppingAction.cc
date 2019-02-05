//XEBRA header files
#include "XebraSteppingAction.hh"
#include "XebraAnalysisManager.hh"

//Additional header files
#include <string.h>
#include <cmath>

//G4 header files
#include "G4SteppingManager.hh"

XebraSteppingAction::XebraSteppingAction(XebraAnalysisManager *myAM):myAnalysisManager(myAM)
{}

void XebraSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4int  trackID = aStep->GetTrack()->GetTrackID();
	particle = aStep->GetTrack()->GetDefinition()->GetParticleName();
	G4int particlePDGcode = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
	//G4float xP = aStep->GetPostStepPoint()->GetPosition().x();
	//G4float yP = aStep->GetPostStepPoint()->GetPosition().y();
	//G4float zP = aStep->GetPostStepPoint()->GetPosition().z();
	//G4float rP = sqrt(xP*xP+yP*yP+zP*zP);
	G4float eP = aStep->GetPostStepPoint()->GetKineticEnergy();
	//G4float timeP = aStep->GetPostStepPoint()->GetGlobalTime();
    G4float timeP = aStep->GetTrack()->GetGlobalTime();
	//G4float eDep = aStep->GetTotalEnergyDeposit();

	// Direction of the particle Pre
	// G4ParticleMomentum *Momentum = aStep->GetPostStepPoint()->GetMomentum();
	G4float preMomModulo = sqrt( pow(aStep->GetPreStepPoint()->GetMomentum().x(),2) +
								pow(aStep->GetPreStepPoint()->GetMomentum().y(),2) +
								pow(aStep->GetPreStepPoint()->GetMomentum().z(),2) );
	G4ThreeVector preDirection( aStep->GetPreStepPoint()->GetMomentum().x()/preMomModulo , 
								aStep->GetPreStepPoint()->GetMomentum().y()/preMomModulo , 
								aStep->GetPreStepPoint()->GetMomentum().z()/preMomModulo );

	// Direction of the particle Post
	// G4ParticleMomentum *Momentum = aStep->GetPostStepPoint()->GetMomentum();
	G4float MomModulo = sqrt( pow(aStep->GetPostStepPoint()->GetMomentum().x(),2) +
							pow(aStep->GetPostStepPoint()->GetMomentum().y(),2) +
							pow(aStep->GetPostStepPoint()->GetMomentum().z(),2) );
	G4ThreeVector direction( aStep->GetPostStepPoint()->GetMomentum().x()/MomModulo , 
							aStep->GetPostStepPoint()->GetMomentum().y()/MomModulo , 
							aStep->GetPostStepPoint()->GetMomentum().z()/MomModulo );
        
  Int_t SaveTopPmt = 0; // ToDo: experiment with this flag to see if top pmts are hit
	if (SaveTopPmt){    
		if(particle="opticalphoton" && aStep->GetTrack()->GetVolume()->GetName()=="PMT_R8520_Photocathode"){
				myAnalysisManager->FillParticleInSave(3,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									//aStep->GetPostStepPoint()->GetMomentum(),
									direction,
									eP,
									timeP,
									trackID);      
		}
	}
  
  Int_t SaveBottomPmt = 1; // ToDo: experiment with this flag to see if top pmts are hit
	if (SaveBottomPmt){ 
		if(particle="opticalphoton" && aStep->GetTrack()->GetVolume()->GetName()=="PMT_R11410_Photocathode"){
				myAnalysisManager->FillParticleInSave(4,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									//aStep->GetPostStepPoint()->GetMomentum(),
									direction,
									eP,
									timeP,
									trackID);      
		}
	}
        
	Int_t SaveCryo = 0;
	if (SaveCryo){
		// Get information when a particle cross the whole shield and hit the external part of the outer cryostat
		if(particle!="opticalphoton" &&
		aStep->GetTrack()->GetVolume()->GetName()=="Water" &&    // this is for the Water shield
		aStep->GetTrack()->GetNextVolume()->GetName()=="OuterCryostat" ){
			myAnalysisManager->FillParticleInSave(1, // 1==Particle inside the shield, hittin gthe outer cryo from outside
							  particlePDGcode,
							  aStep->GetPostStepPoint()->GetPosition(),
							  //aStep->GetPostStepPoint()->GetMomentum(),
							  direction,
							  eP,
							  timeP,
							  trackID);
                              //aStep->GetTrack()->SetTrackStatus(fStopAndKill);
		}
	}
        
	Int_t SaveCapture = 0;
	if (SaveCapture){
	
		if(trackID==1 && particle!="neutron"){
			myAnalysisManager->FillParticleInSave(2, // 2==Primary particle is not a neutron, but a secondary particle postponed from event track.
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									//aStep->GetPostStepPoint()->GetMomentum(),
									direction,
									eP,
									timeP,
									trackID);
		} 

    }

}

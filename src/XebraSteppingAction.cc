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
        


  Int_t Save_PMT0_Photocathode = 0;
	if (Save_PMT0_Photocathode){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="PMT0_Photocathode") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(1,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_PMT_R8520_Photocathode = 0;
	if (Save_PMT_R8520_Photocathode){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="PMT_R8520_Photocathode") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(2,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_SS_gate_mesh = 0;
	if (Save_TPC_SS_gate_mesh){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_SS_gate_mesh") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(3,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_SS_cathode_mesh = 0;
	if (Save_TPC_SS_cathode_mesh){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_SS_cathode_mesh") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(4,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_SS_anode_mesh = 0;
	if (Save_TPC_SS_anode_mesh){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_SS_anode_mesh") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(5,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_SS_TopMesh_mesh = 0;
	if (Save_TPC_SS_TopMesh_mesh){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_SS_TopMesh_mesh") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(6,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_LXe = 0;
	if (Save_LXe){ 
		if((particle=="opticalphoton") && ((((aStep->GetTrack()->GetNextVolume()->GetName()=="LXe_ActiveVolume")||(aStep->GetTrack()->GetNextVolume()->GetName()=="LXe_extra_filling"))||(aStep->GetTrack()->GetNextVolume()->GetName()=="LXe_TPC")) && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))){
		myAnalysisManager->FillParticleInSave(7,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_PTFE_reflector = 0;
	if (Save_TPC_PTFE_reflector){ 
		if((particle=="opticalphoton") && (((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_PTFE_reflector_LXe")||(aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_PTFE_reflector_GXe")) && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")) && (aStep->GetTrack()->GetTrackStatus()==fStopAndKill)){
		myAnalysisManager->FillParticleInSave(8,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_PTFE_TopPMTHolder = 0;
	if (Save_TPC_PTFE_TopPMTHolder){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_PTFE_TopPMTHolder") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")) && (aStep->GetTrack()->GetTrackStatus()==fStopAndKill)){
		myAnalysisManager->FillParticleInSave(9,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
	Int_t Save_TPC_PTFE_spacer = 0;
	if (Save_TPC_PTFE_spacer){ 
		if((particle=="opticalphoton") && ((((aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_PTFE_spacer1")||(aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_PTFE_spacer2"))||(aStep->GetTrack()->GetNextVolume()->GetName()=="TPC_PTFE_spacer3")) && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")) && (aStep->GetTrack()->GetTrackStatus()==fStopAndKill)){
		myAnalysisManager->FillParticleInSave(10,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}

Int_t Save_PMT0_Body = 0;
	if (Save_PMT0_Body){ 
		if((particle=="opticalphoton") && ((aStep->GetTrack()->GetNextVolume()->GetName()=="PMT0_Body") && (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")) && (aStep->GetTrack()->GetTrackStatus()==fStopAndKill)){
		myAnalysisManager->FillParticleInSave(11,
									particlePDGcode,
									aStep->GetPostStepPoint()->GetPosition(),
									direction,
									eP,
									timeP,
									trackID);
				//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;     
		}
	}
	
//G4cout << " Process " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() <<" in " << aStep->GetTrack()->GetNextVolume()->GetName() << G4endl;

/*
Legend flags:

 1  PMT0_Photocathode
 2  PMT_R8520_Photocathode
 3  TPC_SS_gate_mesh
 4  TPC_SS_cathode_mesh
 5  TPC_SS_anode_mesh
 6  TPC_SS_TopMesh_mesh
 7  LXe (LXe_ActiveVolume / LXe_extra_filling / LXe_TPC)
 8  TPC_PTFE_reflector
 9  TPC_PTFE_TopPMTHolder
10  TPC_PTFE_spacer
11  PMT0_Body // usually directly after Transportation in PMT0_Window

*/


}

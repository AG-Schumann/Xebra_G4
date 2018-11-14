//XEBRA Header Files
#include "XebraParticleSource.hh"
#include "XebraPrimaryGeneratorAction.hh"
#include "XebraPrimaryGeneratorMessenger.hh"

//Additional Header Files
#include <globals.hh>
#include <Randomize.hh>

//G4 Header Files
#include <G4RunManagerKernel.hh>
#include <G4Event.hh>
#include <G4GeneralParticleSource.hh>
#include <G4Material.hh>
#include <G4ThreeVector.hh>
#include <G4TransportationManager.hh>
#include <G4Navigator.hh>
#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4PrimaryVertex.hh>
#include <G4ParticleDefinition.hh>
#include <G4Point3D.hh>
#include <G4Vector3D.hh>
#include <G4SingleParticleSource.hh>
#include <G4SystemOfUnits.hh>


XebraPrimaryGeneratorAction::XebraPrimaryGeneratorAction(G4String fName)
{
   m_pMessenger       = new XebraPrimaryGeneratorMessenger(this);

  G4cout <<"XebraPrimaryGeneratorAction::XebraPrimaryGeneratorAction() Use XebraParticleSource "<<G4endl;
  m_pParticleSource = new XebraParticleSource();
  
  particleTable = G4ParticleTable::GetParticleTable();
  
  m_hParticleTypeOfPrimary = "";
  m_dEnergyOfPrimary = 0.;
  m_hPositionOfPrimary = G4ThreeVector(0., 0., 0.);
  
  m_lSeeds[0] = -1;
  m_lSeeds[1] = -1;
  
  G4cout <<"XebraPrimaryGeneratorAction:: MC with variance reduction = "<<VarianceReduction<<G4endl;
  G4cout <<"XebraPrimaryGeneratorAction::               survival cut = "<<p_survive_cut<<G4endl;
  // for use with ForcedTransport of gammas
  particleGun  = new G4ParticleGun();
  
  theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
  // forced transport target volume cylinder
  ft_cyl_R      = 0*cm; // set through messenger
  ft_cyl_L      = 0*cm; // set through messenger
  ft_cyl_center = G4ThreeVector(0,0,0); // set through messenger
  // maximum number of rejected primaries er event
  ntry_max = 1000;
  // number of rejected primaries
  numberOfRejectedPrimaries = 0.;
  // number of rejected primaries (double vaiables, since it counts the event weights)
  numberOfAcceptedPrimaries = 0.;
  // total run weight
  runWeight = 0;
  
  generatorRootFile = fName;
  // histograms.....
  _f_prim = new TFile(generatorRootFile,"RECREATE");
  
  _generator = _f_prim->mkdir("generator");
  
  _generator->cd();
  _log_primary_w = new TH1F("_log_primary_w","_log_primary_w",100,-20,0);
  _cost_all      = new TH1F("_cost_all","_cost_all",100,-1,1);
  _energy_all    = new TH1F("_energy_all","_energy_all",1000,0,5);
  
  _cost_accept   = new TH1F("_cost_accept","_cost_accept",100,-1,1);
  _energy_accept = new TH1F("_energy_accept","_energy_accept",1000,0,5);
  
}

XebraPrimaryGeneratorAction::~XebraPrimaryGeneratorAction()
{
  
  _f_prim->cd();
  _generator->cd();
  
  //  write the source settings to file
  TNamed *TypePar = new TNamed("SourceType", m_pParticleSource->GetParticleDefinition()->GetParticleName());
  TypePar->Write();
  TParameter<G4double> *IntensityPar = new TParameter<G4double>("SourceIntensity", -999.999);
  IntensityPar->Write();  
  
  nRejectParameter = new TParameter<double>("nreject",GetNumberOfRejectedPrimaries());
  nRejectParameter->Write();
  
  nAcceptParameter = new TParameter<double>("naccept",GetNumberOfAcceptedPrimaries());
  nAcceptParameter->Write();
  
  _f_prim->cd();
  
  _f_prim->Write();
  _f_prim->Close();
  
  delete particleGun;
 
  delete m_pParticleSource;
}

void 
XebraPrimaryGeneratorAction::GeneratePrimariesStandard(G4Event *pEvent)
{
  // generate a single particle 
  m_lSeeds[0] = *(CLHEP::HepRandom::getTheSeeds());
  m_lSeeds[1] = *(CLHEP::HepRandom::getTheSeeds()+1);
  
  // PB 06/05/2012 - Start
  G4StackManager *pStackManager = (G4RunManagerKernel::GetRunManagerKernel())->GetStackManager(); // pb added

  if(!pStackManager->GetNPostponedTrack())
    {
      m_pParticleSource->GeneratePrimaryVertex(pEvent);
      // particle name of primary
      m_hParticleTypeOfPrimary = m_pParticleSource->GetParticleDefinition()->GetParticleName();
    }
  else
    {
      pStackManager->TransferStackedTracks(fPostpone, fUrgent);
      G4VTrajectory* pTrajectory;
      G4Track *pTrack = pStackManager->PopNextTrack(&pTrajectory);
      
      m_pParticleSource->GeneratePrimaryVertexFromTrack(pTrack, pEvent);
      // particle name of primary
      m_hParticleTypeOfPrimary = pTrack->GetParticleDefinition()->GetParticleName();
  
      delete pTrack;
    }
  // PB 06/05/2012 - End

  //G4cout << " PPP now Start Tracking " <<  m_hParticleTypeOfPrimary  << G4endl;  //MS121106

  // kinetic energy of primary
   m_dEnergyOfPrimary       = m_pParticleSource->GetParticleEnergy();
  // position of primary
   m_hPositionOfPrimary     = m_pParticleSource->GetParticlePosition();
  // direction of primary
   m_hDirectionOfPrimary    = m_pParticleSource->GetParticleMomentumDirection();
  
   FillHistograms();
  
   numberOfAcceptedPrimaries += 1.0;
}


void 
XebraPrimaryGeneratorAction::FillHistograms(){
  
  _energy_accept->Fill(m_dEnergyOfPrimary);
  _cost_accept->Fill(m_hDirectionOfPrimary.z());
  
}
 

void 
//XebraPrimaryGeneratorAction::GeneratePrimariesAccelerated(G4Event *pEvent)
//{
XebraPrimaryGeneratorAction::GeneratePrimariesAccelerated(void){ //modified by Patricia 

#ifdef _use_GPS
  //
  // ForcedTransport algorithm: 
  //         - kill events that do not point to the target volume
  //         - assign a weight to each event, according to the survival probability
  //
  // A.P. Colijn - Dec 2011
  //
  
  // if we are going to forced transportation, we only generate a temporary event here with GPS
  G4int nreject    = 0;
  // a completely new event to work with.
  G4Event      *tempEvent = new G4Event();
  G4ThreeVector x0,dir;
  G4double      energy;
  G4double      weight = 1;
  G4double      p_survive;
  
  // just one primary vertex: just add particles with another direction
  m_pParticleSource->SetMultipleVertex(kFALSE);
  
  G4bool acceptEvent = kFALSE;
  G4int  nintersect  = -1;
  
  while(!acceptEvent){
    // generate the next primary vertex
    m_pParticleSource->GeneratePrimaryVertex(tempEvent);
    
    // see if track intersects with the ForceVolume target
    x0         = m_pParticleSource->GetParticlePosition();
    dir        = m_pParticleSource->GetParticleMomentumDirection();
    energy     = m_pParticleSource->GetParticleEnergy();
    
    _cost_all->Fill(dir.z()); // = cos theta wrt the (0,0,1) axis
    _energy_all->Fill(energy); // = gamma energy
    
    // 1. check if there are intersections with the target volume
    nintersect = IntersectWithTarget(x0, dir);
    // 2. if there are 2 intersections calculate the probability for a gamma to get to the target...
    if(nintersect == 2) {
      
      if(p_survive_cut>0) // if we know the gamma survives we set the p_survive to 1.
        p_survive = ComputeForcedTransportWeight(x0,dir,ft_cyl_intersect_s[0], energy);
      else
        p_survive = 1;
      
      _log_primary_w->Fill(std::log10(p_survive));
      
      if(VarianceReductionMode == KILL_ONLY    ||
         VarianceReductionMode == KILL_FT_EDGE ||
         VarianceReductionMode == KILL_FT_PATH)
      {
        if(p_survive>p_survive_cut) acceptEvent = kTRUE;
      } else {
        //	  G4Exception("Variance reduction mode not implemented.");
        G4String msg = "Variance reduction mode not implemented.";
        G4Exception("XebraPrimaryGeneratorAction::GeneratePrimariesAccelerated()","GeneratePrimary000",
                    FatalException,msg);
      }
    } 
    // did we accept the event?
    if(!acceptEvent) nreject++;
    
    // bust out if it takes too long.....
    if(nreject>ntry_max){
      G4String msg = "Too many rejected primaries. Check your (1) ForcedTransport target volume (2) Event generation";
      G4Exception("XebraPrimaryGeneratorAction::GeneratePrimariesAccelerated()","GeneratePrimary001",FatalException,msg);
    }
  }
  delete tempEvent; // to avoid a memory leak
  
  
  // particle name of primary
  m_hParticleTypeOfPrimary = m_pParticleSource->GetParticleDefinition()->GetParticleName();
  // kinetic energy of primary
  m_dEnergyOfPrimary       = m_pParticleSource->GetParticleEnergy();
  // position of primary
  m_hPositionOfPrimary     = m_pParticleSource->GetParticlePosition();
  // direction of primary
  m_hDirectionOfPrimary    = m_pParticleSource->GetParticleMomentumDirection();
  
  if(m_hParticleTypeOfPrimary != "gamma"){
    G4String msg = "PrimaryGeneratorAction:: trying ForcedTransport with particle other than gamma";
    G4Exception("XebraPrimaryGeneratorAction::GeneratePrimariesAccelerated()","GeneratePrimary002", 
                FatalException,msg);
  }
  
  // particle definition of primary
  G4ParticleDefinition *particle = m_pParticleSource->GetParticleDefinition();
  
  // ordinary particle Gun: recreate the same particle at a different location
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(m_hDirectionOfPrimary);
  particleGun->SetParticleEnergy(m_dEnergyOfPrimary);
  // change the origin of our particle
  G4double Length = 0;
  if        (VarianceReductionMode == KILL_FT_EDGE){
    //    G4cout <<"EDGE MODE"<<G4endl;
    Length       = ft_cyl_intersect_s[0];
    weight  = ComputeForcedTransportWeight(m_hPositionOfPrimary, m_hDirectionOfPrimary, 
                                           Length,m_dEnergyOfPrimary);
  } else if (VarianceReductionMode == KILL_FT_PATH){
    //G4cout <<"PATH MODE"<<G4endl;
    Length       = ft_cyl_intersect_s[0] * CLHEP::HepRandom::getTheEngine()->flat();
    weight  = ComputeForcedTransportWeight(m_hPositionOfPrimary, m_hDirectionOfPrimary, 
                                           Length,m_dEnergyOfPrimary);
  } else {
    //G4cout <<"OTHER MODE "<<VarianceReductionMode<<G4endl;
    Length       = 0;
    weight  = 1;
  }
  m_hForcedPositionOfPrimary = m_hPositionOfPrimary + L*m_hDirectionOfPrimary;
  particleGun->SetParticlePosition(m_hForcedPositionOfPrimary);
  
  // generate the primary vertex in the new location .....
  particleGun->GeneratePrimaryVertex(pEvent);
  
  // give the event a weight according to the Forced Transport weight
  pEvent->GetPrimaryVertex()->SetWeight(weight);
  
  // for accounting .....
  numberOfRejectedPrimaries += (G4double)nreject;
  numberOfAcceptedPrimaries += weight;
  
  FillHistograms();
#else
  G4Exception("XebraPrimaryGeneratorAction::GeneratePrimariesAccelerated()","Accelerate000",FatalException,
              "Accelerated primary generation only supported with _use_GPS_");
#endif
}

void
XebraPrimaryGeneratorAction::GeneratePrimaries(G4Event *pEvent)
{
  //
  // Generate the primary particles
  //
 
  if(VarianceReduction){
    // accelerated Monte Carlo generation for gamma rays
    //GeneratePrimariesAccelerated(pEvent);
      GeneratePrimariesAccelerated(); //modyfied by Patricia
  } else {
    // standard weight=1 Monte Carlo generation
    GeneratePrimariesStandard(pEvent);
  }  
  
}

G4int
XebraPrimaryGeneratorAction::IntersectWithTarget(G4ThreeVector x0, G4ThreeVector dir)
{
  // find the intersection points of a particle with the target cylinder.....
  G4int nint = 0;
  ft_cyl_intersect.clear();
  ft_cyl_intersect_s.clear();
  
  // retrieve the target cylinder information
  G4double      R  = ft_cyl_R;
  G4double      R2 = std::pow(R,2);
  G4double      Length  = ft_cyl_L;
  G4ThreeVector xc = ft_cyl_center;
  G4double      zmin = xc.z() - Length/2;
  G4double      zmax = xc.z() + Length/2;
  
  // helper variables
  G4ThreeVector dx    = x0 - xc;
  G4double A          = std::pow(dir.x(),2)+std::pow(dir.y(),2);
  G4double dx_dot_dir = dx.x()*dir.x() + dx.y()*dir.y();
  G4double dx2        = std::pow(dx.x(),2) + std::pow(dx.y(),2);
  G4double D          = std::pow(dx_dot_dir,2) - (dx2 - R2)*A;
  
  if(D>=0){ // solutions for an intersect with a straight line and cylinder
    G4double      step[2];
    G4ThreeVector pos[2];
    
    for(G4int ip=0; ip<2; ip++){
      step[ip]   = (-dx_dot_dir + (1-2*ip)*std::sqrt(D))/A;
      pos[ip] = x0 + step[ip]*dir;
      
      G4double z = pos[ip].z();
      if  (z<zmin || z>zmax){ // outside z boundaries.... see if there is an intersect on top/bottom
        G4double zplane ;
        if(z<zmin) zplane = zmin; 
        else zplane = zmax;
        if(std::fabs(dir.z()) > 1e-12){
          step[ip]   = (zplane - x0.z()) / dir.z();
          pos[ip] = x0 + step[ip]*dir;
          G4ThreeVector dxx = xc - pos[ip];
          G4double      dRR = std::sqrt(pow(dxx.x(),2) + pow(dxx.y(),2));
          if(dRR>R) step[ip] = -kInfinity; // the intersect on the top/bottom plane needs to have radius < R_cylinder
        } else {
          step[ip] = -kInfinity;
        }
      }
    }
    // only store if there are two solutions with a positive pathlength.....
    //    G4cout <<" step[0] = "<<step[0]<<" step[1] = "<<step[1]<<G4endl;
    if(step[0]>0 && step[1]>0){
      if(step[0] < step[1]){
        ft_cyl_intersect_s.push_back(step[0]);
        ft_cyl_intersect_s.push_back(step[1]);
        ft_cyl_intersect.push_back(pos[0]);
        ft_cyl_intersect.push_back(pos[1]);
      } else {
        ft_cyl_intersect_s.push_back(step[1]);
        ft_cyl_intersect_s.push_back(step[0]);
        ft_cyl_intersect.push_back(pos[1]);
        ft_cyl_intersect.push_back(pos[0]);
      }
      //      G4cout <<"INTERSECT 0 = "<<pos[0].x()<<" "<<pos[0].y()<<" "<<pos[0].z()<<G4endl;
      // G4cout <<"INTERSECT 1 = "<<pos[1].x()<<" "<<pos[1].y()<<" "<<pos[1].z()<<G4endl;
    }
    // in this case the target volume is overlapping with the source ... 
    if(step[0]*step[1]<0){
      G4String msg = "Target cylinder is overlapping with the source ....";
      G4Exception("XebraPrimaryGeneratorAction::IntersectWithTarget()","Intersect000",FatalException,msg);
    }
  }
  nint = (G4int)ft_cyl_intersect.size();
  return nint;
}

G4double 
XebraPrimaryGeneratorAction::ComputeGammaMeanFreePath(G4double e, G4String matName)
{
  //
  // mean free path for a gamma 
  //
  G4double lphot  = emCalc.ComputeMeanFreePath(e,"gamma","phot",matName,0);
  G4double lcompt = emCalc.ComputeMeanFreePath(e,"gamma","compt",matName,0);
  G4double lpair  = emCalc.ComputeMeanFreePath(e,"gamma","conv",matName,0);
  
  G4double ltot = 1./(1./lphot + 1./lcompt + 1./lpair);
  
  return ltot;
}

G4double
XebraPrimaryGeneratorAction::ComputeForcedTransportWeight(G4ThreeVector x0, G4ThreeVector dir, 
                                                            G4double Length, G4double e)
{
  G4double dx     = 1.0*cm; // too large of course
  G4double weight = 1.0;
  G4int    nstep  = (G4int) (L/dx); 
  G4double Lrest  = Length - nstep*dx;
  
  G4VPhysicalVolume *myVol;
  G4LogicalVolume  *logVol;
  G4Material       *mat;
  
  G4ThreeVector pos = x0;
  G4double      stepsize, ltot=0;
  G4String      currentMatname, previousMatname;
  //  G4cout << "x0 = "<<x0<< " direction "<<dir<<G4endl;
  // - step along the track and find the material encountered by the photon
  // - compute the survival probability
  for(G4int istep=0; istep<nstep+1; istep++){ 
    if(istep<nstep){
      pos += dir*dx;
      stepsize = dx;
    } else { // last bit of the trajectory ....
      pos += dir*Lrest;
      stepsize = Lrest;
    }
    // dig down to the material.... by getting the physical volume first
    myVol  = (G4VPhysicalVolume*)theNavigator->LocateGlobalPointAndSetup(pos);
    // derive the logical volume
    logVol = (G4LogicalVolume*)myVol->GetLogicalVolume();
    // ... and determine the material it is made of
    mat    = logVol->GetMaterial();
    previousMatname = currentMatname;
    currentMatname  = mat->GetName();
    // re-calculate the mean free pathlength only if we enter a new material type
    if(currentMatname != previousMatname) ltot = ComputeGammaMeanFreePath(e,currentMatname);
    // multiply the survival probability with the probability to survive the current step
    weight *= std::exp(-stepsize/ltot);
  }  
  //  G4cout <<" weight = "<<weight<<G4endl;
  return weight;
}


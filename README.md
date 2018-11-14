# Darwin_G4
Generic Geant4 Montecarlo for DARWIN simulation: 

- Overall G4 Structure and Physics List is based on the XENONnT Neutron Background simulation by D. Ramirez (Feb 2018)
- Detector Geometry contains a generic model of DARWIN (as of Aug 2018) by UZH + UniFr
- Cleaned up from traces of Geant4 versions <10 (code tested with G4 10.3.3.) and debugged w.r.t. G4SystemOfUnits and naming conventions (except for variables in detector construction)


## Instructions for git:
-  git clone [-b "BRANCH_NAME"] https://github.com/Darwin-DarkMatter/Darwin_G4.git 
-  cd Darwin_G4
-  git checkout -b "BRACH_NAME"
-  rsync -avP ../DIR_WITH_UPDATE/include/ include/  
-  rsync -avP ../DIR_WITH_UPDATE/src/ src/
-  git add .
-  git commit -m "ADD SOME COMMENT "
-  git push origin "BRACH_NAME"

## Compilation & Running Macros:
- make clean && make   //compiling 
- bin/Linux-g++/darwin_G4 -p macros/preinit.mac -f macros/run_geantino_all.mac -n 10000  //running the preinit + process macros
--> output in root file ("event.root", unless specified differently). 

## Simple online root visualization: 
-  TFile *pFile = new TFile(inputfile+".root");
-  TDirectoryFile *pDir = (TDirectoryFile *) pFile->Get("events");
-  TTree *pTree = (TTree *) pDir->Get("events");
-  pTree6->Draw("xp_pri:yp_pri:zp_pri");

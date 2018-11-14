#ifndef _FILEMERGER_
#define _FILEMERGER_

#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>


#define NO_NEW_FOLDER 0
#define MAKE_NEW_FOLDER 1

class fileMerger {
  
public:
  fileMerger();
  fileMerger(std::string f0, std::vector<std::string> f1);
  void Merge();
  void CleanUp();
  
private:
  void CopyDir(TDirectory *source, Int_t ilevel);
  void CopyFile(const char *fname);
  
  std::string masterfile;
  std::vector<std::string> auxfiles;
  
};

#endif


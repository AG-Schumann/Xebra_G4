#ifndef __XEBRAMATERIALS_H__
#define __XEBRAMATERIALS_H__

// Additional Header Files
#include <globals.hh>
#include <map>
#include <vector>

using std::vector;
using std::map;

// Root Header Files
#include "TDirectory.h"
#include "TFile.h"

class XebraMaterials {
 public:
  XebraMaterials();
  ~XebraMaterials();
    
  void DefineMaterials();

 private:
  //G4double pLXeElectricField;
  //G4double pGXeElectricField;
};

#endif

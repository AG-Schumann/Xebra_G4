#!/bin/bash

dst=./outputs/"$2.root"
./bin/Linux-g++/xebra_G4 -p macros/preinit.mac -f macros/src_Pointsources_DP_automated.mac -n $1 -o $dst
rm -rf ./macros/src_Pointsources_DP_automated.mac



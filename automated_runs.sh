#!/bin/bash

./bin/Linux-g++/xebra_G4 -p macros/preinit.mac -f macros/src_optPhot_DP_automated.mac -n $1 -o ./outputs/$2
rm -rf ./macros/src_optPhot_DP_automated.mac



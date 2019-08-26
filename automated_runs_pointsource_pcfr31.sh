#!/bin/bash

#SBATCH --job-name=XeBRA-G4
#SBATCH --output=job-prompt.txt
#SBATCH --ntasks=1
#SBATCH --array=1-10

#source ~/.bashrc 
#loadG4

user=$(whoami)
mkdir /scratch/$user -p
tmp=/scratch/$user/"$2_${SLURM_ARRAY_TASK_ID}.root"
dst=/sc/userdata/abismark/"$2_${SLURM_ARRAY_TASK_ID}.root"
source /opt/geant/v10.3.3/bin/geant4.sh && source /opt/geant/v10.3.3/share/Geant4-10.3.3/geant4make/geant4make.sh && export G4WORKDIR=.
./bin/Linux-g++/xebra_G4 -p macros/preinit.mac -f macros/src_Pointsources_DP_automated.mac -n $1 -o $tmp
mv $tmp $dst
rm -rf ./macros/src_Pointsources_DP_automated.mac

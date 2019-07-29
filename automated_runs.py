
#!/usr/bin/python

import sys
import os


'''
Study influence optical parameters on S1 LCE
execute with "python3 automated_runs.py" inside the Xebra_G4 directory
'''


##### Input parameters #####

## List with PTFE reflectivities
#p_PTFE_Reflectivity_list    = [0.90, 0.95, 0.99]
#p_PTFE_Reflectivity_list    = [0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.85, 0.925, 0.975, 1.0]
#p_PTFE_Reflectivity_list    = [0.95, 0.99]
p_PTFE_Reflectivity_list    = [0.95]

## List with LXe absorption lengths in cm
#p_LXe_AbsorptionLenght_list = [0, 10, 20, 30, 40, 50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000, 10000]
#p_LXe_AbsorptionLenght_list = [10, 100, 1000]
#p_LXe_AbsorptionLenght_list = [100, 1000]
p_LXe_AbsorptionLenght_list = [100]

## List with mesh transparencies
p_Mesh_Transparency_list = [0.89770509]
#p_Mesh_Transparency_list = [0.8, 0.825, 0.85, 0.875, 0.93, 0.95, 0.97, 0.999]

## Number of events to be simulated
p_EventCount = 1e4

## Signal region i.e. S1 or S2
p_SignalRegion = "S2" # 'S1' or 'S2'

## Spacer 3 in mm
p_PMTGap = 4.5

## Write empty events 'true' or 'false'
p_writeEmpty = 'false'

## Number of particles generated in one event
#p_NumberOfParticles = 1
#p_NumberOfParticles = 2500
p_NumberOfParticles = 10000


##### Iteratively create and execute macro #####

## Loop over parameter lists
for p_LXe_AbsorptionLenght in p_LXe_AbsorptionLenght_list:
    for p_PTFE_Reflectivity in p_PTFE_Reflectivity_list:
        for p_Mesh_Transparency in p_Mesh_Transparency_list:
            
            ## Create / specify save directory for macros
            PATH = "./macros"
            os.makedirs(PATH, exist_ok=True)
            
            ## Create macro
            MACRONAME = PATH + "/" + "src_optPhot_DP_automated" + ".mac"
            f = open(MACRONAME, "w")
            
            ## Write macro
            f.write('#################\n')
            f.write('# Macro to simulate optical photons in the LXe phase of a dual phase setup\n')
            f.write('#################\n')
            f.write('\n')
            f.write('##################\n')
            f.write('# optical properties\n')
            f.write('/Xe/detector/setTeflonReflectivity '+str(p_PTFE_Reflectivity)+'\n')
            f.write('/Xe/detector/setGXeTeflonReflectivity '+str(p_PTFE_Reflectivity)+'\n')
            f.write('/Xe/detector/setLXeAbsorbtionLength '+str(p_LXe_AbsorptionLenght)+' cm \n')
            f.write('/Xe/detector/setGXeAbsorbtionLength 100 m\n')    
            f.write('/Xe/detector/setLXeRayScatterLength 30 cm\n')
            f.write('/Xe/detector/setLXeRefractionIndex 1.63\n')
            f.write('/Xe/detector/setLXeMeshTransparency '+str(p_Mesh_Transparency)+'\n')
            f.write('/Xe/detector/setGXeMeshTransparency '+str(p_Mesh_Transparency)+'\n')
            f.write('\n')
            f.write('#################\n')
            f.write('# verbosity\n')
            f.write('/control/verbose 0\n')
            f.write('/run/verbose 0\n')
            f.write('/event/verbose 0\n')
            f.write('/tracking/verbose 0\n')
            f.write('/xebra/gun/verbose 0\n')
            f.write('\n')
            f.write('#################\n')
            f.write('# seed\n')
            f.write('/run/random/setRandomSeed 0\n')
            f.write('\n')
            f.write('#################\n')
            f.write('# gun\n')
            f.write('/xebra/gun/angtype iso\n')
            f.write('/xebra/gun/type    Volume \n')
            f.write('/xebra/gun/shape   Cylinder\n')
            f.write('/xebra/gun/numberofparticles '+str(p_NumberOfParticles)+'\n')
            f.write('\n')
            if p_SignalRegion == "S1":        
                f.write('### S1\n')
                f.write('## active volume (z: 0<>-71.5|r: 35)\n')
                f.write('/xebra/gun/center 0. 0. -35.75 mm\n')
                f.write('/xebra/gun/radius 35.0 mm\n')
                f.write('/xebra/gun/halfz  35.75 mm\n')
                f.write('## select the volume to confine the source\n')
                f.write('/xebra/gun/confine LXe*\n')
            if p_SignalRegion == "S2":
                f.write('### S2\n')
                f.write('## active volume (z: 2.5<>5.0|r: 35)\n')
                f.write('/xebra/gun/center 0. 0. 3.75 mm\n')
                f.write('/xebra/gun/radius 35.0 mm\n')
                f.write('/xebra/gun/halfz  1.25 mm\n')
                f.write('## select the volume to confine the source\n')
                f.write('/xebra/gun/confine GXe*\n')
            f.write('\n')
            f.write('##################\n')
            f.write('# particle type + energy spectrum\n')
            f.write('/xebra/gun/energy   6.98 eV\n')
            f.write('/xebra/gun/particle opticalphoton\n')
            f.write('\n')
            f.write('##################\n')
            f.write('# scintillation processes in the LXe\n')
            f.write('/Xe/detector/setLXeScintillation false\n')
            f.write('\n')  
            f.write('##################\n')
            f.write('# tree Filling options\n')
            f.write('/run/writeEmpty '+p_writeEmpty+'\n')
            f.write('\n')   
            
            f.close()
            
            
            # Name of output ROOT file
            #filename = "optPhot_"+p_SignalRegion+"_"+"{:.1e}".format(p_EventCount)+"_pmtGap"+str(p_PMTGap)+"_RPTFE"+str(p_PTFE_Reflectivity)+"_LXeAbs"+str(p_LXe_AbsorptionLenght)+".root"
            
            if p_writeEmpty == 'false':
                filename = "optPhot_"+p_SignalRegion+"_"+"{:.1e}".format(p_EventCount)+"_pmtGap"+str(p_PMTGap)+"_RPTFE"+str(p_PTFE_Reflectivity)+"_LXeAbs"+str(p_LXe_AbsorptionLenght)+"_Tmesh"+str(p_Mesh_Transparency)+"_writeEmptyFalse.root"
                if p_NumberOfParticles > 1:
                    filename = "optPhot_"+p_SignalRegion+"_"+"{:.1e}".format(p_EventCount)+"_pmtGap"+str(p_PMTGap)+"_RPTFE"+str(p_PTFE_Reflectivity)+"_LXeAbs"+str(p_LXe_AbsorptionLenght)+"_Tmesh"+str(p_Mesh_Transparency)+"_writeEmptyFalse_nop_"+"{:.1e}".format(p_NumberOfParticles)+".root"
            else:
                filename = "optPhot_"+p_SignalRegion+"_"+"{:.1e}".format(p_EventCount)+"_pmtGap"+str(p_PMTGap)+"_RPTFE"+str(p_PTFE_Reflectivity)+"_LXeAbs"+str(p_LXe_AbsorptionLenght)+"_Tmesh"+str(p_Mesh_Transparency)+".root"
                if p_NumberOfParticles > 1:
                    filename = "optPhot_"+p_SignalRegion+"_"+"{:.1e}".format(p_EventCount)+"_pmtGap"+str(p_PMTGap)+"_RPTFE"+str(p_PTFE_Reflectivity)+"_LXeAbs"+str(p_LXe_AbsorptionLenght)+"_Tmesh"+str(p_Mesh_Transparency)+"_nop_"+"{:.1e}".format(p_NumberOfParticles)+".root"
            
            # Create outputs folder
            os.makedirs("./outputs", exist_ok=True)
            
            # Execute macro
            #os.system("./automated_runs.sh %i %s"%(int(p_EventCount), filename))
            os.system("sbatch -o /sc/userdata/abismark/job.out automated_runs_pcfr31.sh %i %s"%(int(p_EventCount), filename))
            
            # Print feedback in terminal
            sys.stdout.write(filename+" successfully simulated.\n")
            
sys.stdout.write("Done.\n")



#!/usr/bin/python

import sys
import os


'''
Run simulation of radioactive point source with automatically named output.
Execute with "python3 automated_runs_pointsource.py" inside the Xebra_G4 directory.
'''


##### Input parameters #####

## Number of events to be simulated
p_EventCount = 1e5

## Particle type
## Select from: 'Cs137', 'Co57', 'Co60', 'K40', 'U238->Ra226', 'Ar110m', 'Rb83->Kr83', 'Kr85'
p_ParticleType_list = ['Cs137', 'Co57', 'Co60']

## Source position
## place inside sample tube assuming that centered in z-coordinate wrt to active volume
p_SourcePosition_list = ['0. -122. -35.75 mm']
## position centered in LXe outside of reflector
#p_SourcePosition_list = ['0. -45. -35.75 mm']
## other
#p_SourcePosition_list = ['0. -122. -35.75 mm']

## Scintillation processes in the LXe
## Select from: 'true', 'false'
p_SetLXeScintillation = 'false'


##### Iteratively create and execute macro #####

## Loop over parameter lists
for p_ParticleType in p_ParticleType_list:
    for p_SourcePosition in p_SourcePosition_list:
        
        ## Create / specify save directory for macros
        PATH = "./macros"
        os.makedirs(PATH, exist_ok=True)
        
        ## Create macro
        MACRONAME = PATH + "/" + "src_Pointsources_DP_automated" + ".mac"
        f = open(MACRONAME, "w")
        
        ## Write macro
        f.write('#################\n')
        f.write('# Macro to simulate external radioactive point sources\n')
        f.write('#################\n')
        f.write('\n')
        f.write('##################\n')
        f.write('# optical properties\n')
        f.write('/Xe/detector/setTeflonReflectivity 0.95\n')
        f.write('/Xe/detector/setGXeTeflonReflectivity 0.95\n')
        f.write('/Xe/detector/setLXeAbsorbtionLength 100 cm\n')
        f.write('/Xe/detector/setGXeAbsorbtionLength 100 m\n')    
        f.write('/Xe/detector/setLXeRayScatterLength 30 cm\n')
        f.write('/Xe/detector/setLXeRefractionIndex 1.63\n')
        f.write('/Xe/detector/setLXeMeshTransparency 0.89770509\n')
        f.write('/Xe/detector/setGXeMeshTransparency 0.89770509\n')
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
        f.write('/xebra/gun/type    Point \n')
        f.write('/xebra/gun/center '+p_SourcePosition+'\n')
        f.write('/xebra/gun/numberofparticles 1\n')
        f.write('\n')
        f.write('##################\n')
        f.write('# particle type + energy spectrum\n')
        f.write('/xebra/gun/energy   0 keV\n')
        f.write('/xebra/gun/particle ion\n')
        if p_ParticleType == 'Cs137':
            f.write('/xebra/gun/ion 55 137 0 0\n')
        if p_ParticleType == 'Co57':
            f.write('/xebra/gun/ion 27 57 0 0\n')
        if p_ParticleType == 'Co60':
            f.write('/xebra/gun/ion 27 60 0 0\n')
        if p_ParticleType == 'K40':
            f.write('/xebra/gun/ion 19 40 0 0\n')
        if p_ParticleType == 'U238->Ra226':
            f.write('/xebra/gun/ion 92 238 0 0\n')
            f.write('/grdm/nucleusLimits 238 230 92 90\n')
        if p_ParticleType == 'Ar110m':
            f.write('/xebra/gun/ion 47 110 0 118.\n')
        if p_ParticleType == 'Rb83->Kr83':
            f.write('/xebra/gun/ion 37 83 0 0\n')
            f.write('/grdm/nucleusLimits 83 83 37 36\n')
        if p_ParticleType == 'Kr85':
            f.write('/xebra/gun/ion 36 85 0 0\n')
        f.write('\n')
        f.write('##################\n')
        f.write('# scintillation processes in the LXe\n')
        f.write('/Xe/detector/setLXeScintillation '+p_SetLXeScintillation+'\n')
        f.write('\n')  
        f.write('##################\n')
        f.write('# tree Filling options\n')
        f.write('/run/writeEmpty false\n')
        f.write('\n')   
        
        f.close()
        
                
        # Name of output ROOT file
        p_SourcePosition_string = p_SourcePosition.replace(' ', '_')
        filename = p_ParticleType+'_'+'{:.1e}'.format(p_EventCount)+'_pos_'+p_SourcePosition_string
        if p_SetLXeScintillation == 'true':
            filename = filename + '_scint'
        elif p_SetLXeScintillation == 'false':
            filename = filename + '_noscint'
        
        # Print feedback in terminal
        sys.stdout.write('Started simulation of '+filename+'.\n')
        
        # Create outputs folder
        os.makedirs("./outputs", exist_ok=True)
        
        # Execute macro
        os.system("./automated_runs_pointsource.sh %i %s"%(int(p_EventCount), filename))
        #os.system("sbatch -o /sc/userdata/abismark/job.out automated_runs_pointsource_pcfr31.sh %i %s"%(int(p_EventCount), filename))
            
sys.stdout.write("Done.\n")


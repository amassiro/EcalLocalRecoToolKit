Preparation
====


    cmsrel CMSSW_10_4_0
    cd CMSSW_10_4_0
    cd src/
    git cms-init
    git checkout -b amassiro-ecal-cuda

    git remote add origin git@github.com:amassiro/cmssw
    
    git fetch origin
    
    git push -u origin amassiro-ecal-cuda
    
    
Prepare packages that will be changed:
    
    git-cms-addpkg  DataFormats/EcalDetId
    git-cms-addpkg  DataFormats/EcalDigi
    git-cms-addpkg  DataFormats/EcalRecHit
    git-cms-addpkg  RecoLocalCalo/EcalRecAlgos
    git-cms-addpkg  RecoLocalCalo/EcalRecProducers


copy for eigen on gpu

    cp /data/patatrack/vkhriste/cmssw_releases/CMSSW_10_5_X_2019-01-27-2300/config/toolbox/slc7_amd64_gcc700/tools/selected/eigen.xml ../config/toolbox/slc7_amd64_gcc700/tools/selected/
    
    
    
Changes
====


Test
====

    cmsRun raw2digi_ecalonly.py inputType=globalRun          year=2017      

    cmsRun raw2digi_ecalonly_dumpComparison.py inputType=globalRun          year=2017        outputFile=dump.root
    

    export CUDA_VISIBLE_DEVICES=1;    cmsRun raw2digi_ecalonly_gpuonly.py       inputType=globalRun          year=2017    
    cmsRun raw2digi_ecalonly_cpuonly.py       inputType=globalRun          year=2017    
                                                   
    
Compare two reconstructions:
====

    nvidia-smi
    export CUDA_VISIBLE_DEVICES=1 

    cmsRun raw2digi_ecalonly_dumpComparison.py  inputType=globalRun          year=2017        outputFile=dump.root
    
    export CUDA_VISIBLE_DEVICES=1; cmsRun raw2digi_ecalonly_dumpComparison.py  inputType=globalRun          year=2017        outputFile=dump.root
    
    
    
    
    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",200,0,200\)
    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"chi2\",200,0,10\)
    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,100\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,20\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,50\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",1000,-100,100,0\)
    
    
    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM1\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM2\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM3\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM4\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM5\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP1\",200,0,200\)    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP2\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP3\",200,0,200\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP4\",200,0,200\)

    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM1\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM2\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM3\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM4\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM5\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP1\",200,0,20,0\)    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP2\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP3\",200,0,20,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP4\",200,0,20,0\)

    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"jitter\",400,-200,200,0\)
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"jitter\",400,-200,200,2\)

    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"jitterError\",400,-2,2,2\)

    
    
    
    
    
    
    
    
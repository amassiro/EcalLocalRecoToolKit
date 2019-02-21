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

    
    
Changes
====


Test
====

    cmsRun raw2digi_ecalonly.py inputType=globalRun          year=2017      

    cmsRun raw2digi_ecalonly_dumpComparison.py inputType=globalRun          year=2017        outputFile=dump.root
    
    
    
Compare two reconstructions:
====

    nvidia-smi
    export CUDA_VISIBLE_DEVICES=1 

    cmsRun raw2digi_ecalonly_dumpComparison.py  inputType=globalRun          year=2017        outputFile=dump.root
    
    export CUDA_VISIBLE_DEVICES=1; cmsRun raw2digi_ecalonly_dumpComparison.py  inputType=globalRun          year=2017        outputFile=dump.root
    
    
    
    r99t dump.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",200,0,200\)
    
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"chi2\",200,0,10\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM1\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM2\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM3\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM4\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM5\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP1\",200,0,200\)    
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP2\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP3\",200,0,200\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP4\",200,0,200\)
    
    
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"jitter\",400,-200,200,0\)
    r99t dump.root    plot/drawDifferenceOne.cxx\(\"jitter\",400,-200,200,2\)

    r99t dump.root    plot/drawDifferenceOne.cxx\(\"jitterError\",400,-2,2,2\)

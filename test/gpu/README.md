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

    
# EcalLocalRecoToolKit



How to:

    mkdir ECALValidation
    cd ECALValidation/
    git clone git@github.com:amassiro/EcalLocalRecoToolKit.git
    
    cmsenv
    scramv1 b -j 20


    
    
Where:

    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/
    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/14Mar2019/CMSSW_10_5_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/
    
    
Get Branch:

    git cms-checkout-topic [<github-user>:]{<branch>|<pull-request-id>}
    
    git cms-checkout-topic vkhristenko:hcal_mahi_cuda    ---> not working
    
    git cms-checkout-topic vkhristenko:hcal_digi4cuda_10_2_0_pre3
    
    
    
    
    /data/user/vkhriste/cmssw_configs/forhcal/Collisions_cfg.py

    cmsRun Collisions_cfg.py year=2017 inputType=globalRun

    /afs/cern.ch/user/a/amassiro/work/ECAL/LocalReco/CMSSW_10_2_0/src



    
    
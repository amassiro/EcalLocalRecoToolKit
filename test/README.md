Test
====

Dump:


    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.root

         
    cmsRun runRawtoRecoAndDumpAndTime.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.root
 
Time measurement:

    cmsRun runRawtoRecoAndTime.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1  
 
      
    cmsRun runRawtoRecoAndTime.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1  | grep "reconstruction_step" &> dump.time.txt
     

    cd /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test
    cmsenv
     
    cmsRun runRawtoRecoAndTime.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1  &> dump.txt
    cat dump.txt | grep reconstruction_step &> dump.time.txt 
     
    root -l plot/drawTime.cxx\(\"dump.time.txt\"\) 

    
    cd /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test
    cmsenv
    cmsRun runRawtoRecoAndTime.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1  &> dump.2.txt
    cat dump.2.txt | grep reconstruction_step &> dump.old.time.txt 
    
    
Compare reconstructed energy:

    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.root

     
    cd /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test
    cmsenv

    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.old.root
         

Plot:



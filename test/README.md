Test
====

Dump:


    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.root

         
Check data:

    /eos/cms/store/relval/CMSSW_10_3_0_pre2/EGamma/RAW-RECO/ZElectron-103X_dataRun2_PromptLike_v2_RelVal_EGamma2018D-v1/20000/C99000C1-7257-E048-AFA4-721C5B258B39.root

    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/EGamma/RAW-RECO/ZElectron-103X_dataRun2_PromptLike_v2_RelVal_EGamma2018D-v1/20000/C99000C1-7257-E048-AFA4-721C5B258B39.root \
         maxEvents=-1   outputFile=rawtoworld-zee.data.root

         
         
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

    
    cd /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/StandardCMSSW/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test
    cmsenv
    cmsRun runRawtoRecoAndTime.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1  &> dump.2.txt
    cat dump.2.txt | grep reconstruction_step &> dump.old.time.txt 
    root -l plot/drawTime.cxx\(\"/afs/cern.ch/user/a/amassiro/work/ECAL/GPU/StandardCMSSW/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test/dump.old.time.txt\"\) 
    
    
    root -l plot/drawTimeCompare.cxx\(\"/afs/cern.ch/user/a/amassiro/work/ECAL/GPU/StandardCMSSW/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test/dump.old.time.txt\",\"dump.time.txt\"\) 


Check iterations:

    root -l plot/drawIterations.cxx\(\"dump.iter.txt\"\) 



    
Compare reconstructed energy:

    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.root

     
    cd /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test
    cmsenv
    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.root

    cd /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/StandardCMSSW/CMSSW_10_3_0_pre2/src/ECALValidation/EcalLocalRecoToolKit/test
    cmsenv
    cmsRun runRawtoRecoAndDump.py  \
         inputFiles=file:/eos/cms/store/relval/CMSSW_10_3_0_pre2/RelValZEE_13/GEN-SIM-DIGI-RAW/103X_upgrade2018_realistic_v2_resub-v1/20000/0788D0C5-6795-7C45-9548-47FD08113E24.root \
         maxEvents=-1   outputFile=rawtoworld-zee.relval.old.root
         

Plot:

    r99t rawtoworld-zee.relval.root
    r99t rawtoworld-zee.data.root
    
    TTree* tree = (TTree*) _file0->Get("TreeProducer/tree");
    tree->Draw("size_EB + size_EE >>h1(100,0,1000)");
    tree->Draw("size_EB >> h2(100,0,1000)", "", "same");
    tree->Draw("size_EE >> h3(100,0,1000)", "", "same");

    h1->SetLineColor(kBlack)
    h2->SetLineColor(kRed)
    h3->SetLineColor(kBlue)
    
    TLegend* leg = new TLegend(0.5,0.7,0.9,0.9)
    leg->AddEntry(h1, "size EB+EE")
    leg->AddEntry(h2, "size EB")
    leg->AddEntry(h3, "size EE")
    leg->Draw()
    
    
    r99t StandardPU.root  HighPU.root   plot/drawDimension.cxx
    
    
    
    
    
    
    tree->Draw("size_EB");

    tree->Draw("size_EE");
    




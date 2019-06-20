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
                                                   
    
    TimeReport   0.127262     0.127262     0.127262  ecalMultiFitUncalibRecHit
    TimeReport   0.333088     0.333088     0.333088  ecalMultiFitUncalibRecHitGpu
      

    TimeReport   0.121214     0.121214     0.121214  ecalMultiFitUncalibRecHit
    TimeReport   0.331326     0.331326     0.331326  ecalMultiFitUncalibRecHitGpu
    
    
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

    

    
    
        
Measure time and throughput
====
    
    
Prepare the cmsrun file to be run

    export CUDA_VISIBLE_DEVICES=1;    cmsRun raw2digi_ecalonly_gpuonly.py       inputType=globalRun          year=2017    
    cmsRun raw2digi_ecalonly_cpuonly.py       inputType=globalRun          year=2017    
    
    edmConfigDump raw2digi_ecalonly_gpuonly.py > dump_ecal_gpu.py
    edmConfigDump raw2digi_ecalonly_cpuonly.py > dump_ecal_cpu.py

     
Download toolkit and run:

    git clone git@github.com:cms-patatrack/patatrack-scripts.git
    
    https://github.com/cms-patatrack/patatrack-scripts/


    nvprof cmsRun ECALValidation/EcalLocalRecoToolKit/test/gpu/dump_ecal_cpu.py  
         ---> cpu, nothing
    nvprof cmsRun ECALValidation/EcalLocalRecoToolKit/test/gpu/dump_ecal_gpu.py

    
    
Results:

    https://developer.nvidia.com/nvidia-visual-profiler
    
    ==26222== Profiling application: cmsRun ECALValidation/EcalLocalRecoToolKit/test/gpu/dump_ecal_gpu.py
    ==26222== Profiling result:
                Type  Time(%)      Time     Calls       Avg       Min       Max  Name
     GPU activities:   99.78%  3.16778s        20  158.39ms  5.8279ms  1.53477s  kernel_reconstruct(float*, float*, float*, float*, float*, float*)
                        0.16%  5.0808ms        40  127.02us  19.616us  913.79us  [CUDA memcpy DtoH]
                        0.06%  1.8501ms       100  18.500us  1.0240us  105.28us  [CUDA memcpy HtoD]
          API calls:   85.10%  3.16813s        20  158.41ms  5.8317ms  1.53482s  cudaDeviceSynchronize
                       14.28%  531.47ms        27  19.684ms     469ns  524.42ms  cudaFree
                        0.32%  11.957ms       140  85.407us  8.0230us  1.1766ms  cudaMemcpy
                        0.15%  5.5429ms        20  277.15us  14.708us  5.1339ms  cudaLaunchKernel
                        0.08%  3.0042ms         9  333.80us  296.47us  383.73us  cudaMalloc
                        0.05%  1.9465ms        96  20.276us     263ns  898.34us  cuDeviceGetAttribute
                        0.01%  363.91us         1  363.91us  363.91us  363.91us  cuDeviceTotalMem
                        0.01%  215.13us         1  215.13us  215.13us  215.13us  cuDeviceGetName
                        0.00%  25.446us         1  25.446us  25.446us  25.446us  cuDeviceGetPCIBusId
                        0.00%  2.5230us         3     841ns     398ns  1.6330us  cuDeviceGetCount
                        0.00%  1.9340us         2     967ns     310ns  1.6240us  cuDeviceGet
                        0.00%     537ns         1     537ns     537ns     537ns  cuDeviceGetUuid

    
Other:
    
    ./patatrack-scripts/benchmark ECALValidation/EcalLocalRecoToolKit/test/gpu/dump_ecal_cpu.py 
    ./patatrack-scripts/benchmark ECALValidation/EcalLocalRecoToolKit/test/gpu/dump_ecal_gpu.py 

    
    CPU
 
            2 CPUs:
              0: Intel(R) Xeon(R) CPU E5-2650 v4 @ 2.20GHz (12 cores, 24 threads)
              1: Intel(R) Xeon(R) CPU E5-2650 v4 @ 2.20GHz (12 cores, 24 threads)
            
            1 visible NVIDIA GPUs:
              1: GeForce GTX 1080 Ti (UUID: GPU-6bdeda7f-79bd-709f-4635-2e8f4e32f671)
            
            Warming up
            
            
            Running 4 times over 4200 events with 1 jobs, each with 8 threads, 8 streams and 1 GPUs
 
 
     Not working? Is it due to CMSSW_10_4_0 ?
     

     
Dump only, without digi2reco, and compare
====
     

Needed for dumping:

     cmsrel CMSSW_10_5_0_pre2
     cd CMSSW_10_5_0_pre2
     cd src/
     cmsenv
     git cms-init
     git checkout -b  ecal_cpu_gpu_comp
     git cms-merge-topic vkhristenko:ecal_cpu_gpu_comp

and now also to run rereco

     git cms-merge-topic vkhristenko:dev


Run dump:
     
    cmsRun dump_ecalonly_dumpComparison.py
    
    Input:  /data/patatrack/vkhriste/data/ecal/result_2018.root
            /data/patatrack/vkhriste/cmssw_releases/ecal/CMSSW_10_5_X_2019-03-22-1100/src/test.root
            
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"size\",200,0,10000\)
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",200,0,200,0\)
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"chi2\",200,0,10,0\)
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,20\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,50\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",1000,-100,100,0\)
    
    
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM1\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM2\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM3\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM4\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM5\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP1\",200,0,200\)    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP2\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP3\",200,0,200\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP4\",200,0,200\)

    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM1\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM2\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM3\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM4\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM5\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP1\",200,0,20,0\)    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP2\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP3\",200,0,20,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP4\",200,0,20,0\)

    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitter\",400,-200,200,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitter\",400,-200,200,2\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitter\",400,-10,10,2\)

    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitterError\",400,-2,2,2\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitterError\",400,-0.001,0.5,2\)


Run also Reco:

    nvidia-smi
    
    export CUDA_VISIBLE_DEVICES=1;    cmsRun raw2digi_newFormat_ecalonly_dumpComparison.py       inputType=globalRun          year=2017    
    
    export CUDA_VISIBLE_DEVICES=1;    cmsRun raw2digi_newFormat_gpu_ecalonly.py       inputType=globalRun          year=2017    
    cmsRun raw2digi_newFormat_cpu_ecalonly.py       inputType=globalRun          year=2017    
    
    
    
Newest branch:

    git cms-merge-topic vkhristenko:ecal_cuda_refactored


ssh on cmsgpu machine:

    cmgGpu
 
     
     
Use CMSSW Patatrack

    from cmggpu machine
    
    source  /data/patatrack/cmssw/cmsset_default.sh
     
    scram list CMSSW --> see which releases are available
    
    cmsrel CMSSW_10_5_0_pre2
    
    cmsrel CMSSW_10_5_0_pre2_Patatrack
    cd    CMSSW_10_5_0_pre2_Patatrack/src/
    cmsenv

    git cms-init -x cms-patatrack

    
    
    cmsrel CMSSW_10_5_0_pre2_Patatrack_CUDA_10_0
    ----> if not 10_0 then I get: CUDA driver version is insufficient for CUDA runtime version
    
    
    
    git cms-merge-topic vkhristenko:ecal_cuda_refactored
    --> the branch from https://github.com/cms-patatrack/cmssw/pull/313
    
    scramv1 b -j 20
    
    
    
Test performance:

    git clone git@github.com:cms-patatrack/patatrack-scripts.git

    /data/patatrack/fwyzard/ecal/
    
    use ./benchmark config.py to run a single set of measurements
    use ./scan config.py to scan over the number of threads
    
    
    
    nvidia-smi
    
    export CUDA_VISIBLE_DEVICES=1;
    
    cmsRun  ../Performance/ecalOnly.py
    
    ./benchmark ../Performance/ecalOnly.py

    208.8 ±   1.7 ev/s
    
    -> last time it was 2!!
    
    
    
    ./scan ../Performance/ecalOnly.py

    ./scan ../Performance/ecalOnly_cpu.py

    -> results:
    https://swan005.cern.ch/user/amassiro/notebooks/SWAN_projects/GPUECAL/Results.ipynb#
    
    
    
    
    ok: 1) rerun gpu with the HLT configuration for GPU too!
    ok: 2) Compare cpu/gpu for consistency 100% same results on 2018 data
    
    
    
    
Idea:

    - if things changed once per IOV -> don't do it for every event!
    
    
     
     
NSight

    optimize single kernel
    
    /usr/local/cuda-10.0/NsightCompute-1.0/nv-nsight-cu-cli     
    
    CUDA_VISIBLE_DEVICES=0   \
              /usr/local/cuda-10.0/NsightCompute-1.0/nv-nsight-cu-cli \
              -o myprof    \
              /data/patatrack/cmssw/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_5_0_pre2_Patatrack_CUDA_10_0/bin/slc7_amd64_gcc700/cmsRun ecalOnly.py                 
    
    cli ----> command line
    
    
    
    /usr/local/cuda-10.0/NsightCompute-1.0/nv-nsight-cu  /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/15Apr2019/CMSSW_10_5_0_pre2_Patatrack_CUDA_10_0/src/Performance/myprof.nsight-cuprof-report
    
    
    
Nvprof

    nvprof   cmsRun ecalOnly.py
    
    
    
    
    
    
New producer:

    
    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/15Apr2019/NewProducer/CMSSW_10_6_0_pre2_Patatrack/src
    
    git cms-init -x cms-patatrack

    git cms-merge-topic vkhristenko:ecal_dev_patatrack

    /data/patatrack/vkhriste/cmssw_configs/raw2digi_ecalonly_patatrack.py
     
    ./scan ../Performance/raw2digi_ecalonly_patatrack.py

    ./scan ../Performance/ecalOnly_newProducer.py

     
     
     
     
     
     
    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/15Apr2019/NewProducer/CMSSW_10_6_0_pre2_Patatrack/src/ECALValidation/EcalLocalRecoToolKit/test/gpu
     
    /data/patatrack/vkhriste/cmssw_releases/ecal/CMSSW_10_6_0_pre2_Patatrack/src/test.root
     
    cmsRun dump_ecalonly_dumpComparison.py
     
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"size\",200,0,10000\)
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",200,0,200,0\)
     
     
    export CUDA_VISIBLE_DEVICES=0;    cmsRun ecalOnly_newProducer.py
    
    export CUDA_VISIBLE_DEVICES=0;    cmsRun ecalOnly_newProducer_and_dump.py
    
     
     
     
     
     
     
     
    source  /data/patatrack/cmssw/cmsset_default.sh
    
    cmsrel CMSSW_10_6_0_pre2_Patatrack
    
    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/25Apr2019/NewProducer/CMSSW_10_6_0_pre2_Patatrack_MESSEDUP/src

    git cms-init -x cms-patatrack

    git cms-merge-topic vkhristenko:ecal_dev_patatrack
    
    scramv1 b -j 20
    
    ------> not working
    
    
    
    
    
    
    source  /data/patatrack/cmssw/cmsset_default.sh
    
    cmsrel CMSSW_10_6_0_pre2_Patatrack_CUDA_10_1
    
    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/25Apr2019/NewProducer/CMSSW_10_6_0_pre2_Patatrack_CUDA_10_1/src

    git cms-init -x cms-patatrack

    git cms-merge-topic vkhristenko:ecal_dev_patatrack
    
    scramv1 b -j 20
    
    ------> not working
    
    
    
    
    
    
    source  /data/patatrack/cmssw/cmsset_default.sh
    
    cmsrel CMSSW_10_6_0_pre2_Patatrack
    
    /afs/cern.ch/user/a/amassiro/work/ECAL/GPU/onGPU/25Apr2019/NewProducer/CMSSW_10_6_0_pre2_Patatrack/src

    git cms-init -x cms-patatrack

    git cms-merge-topic vkhristenko:ecal_dev_patatrack_1
    
    scramv1 b -j 20
    
    
    
    export CUDA_VISIBLE_DEVICES=0;    cmsRun ecalOnly_newProducer.py
    
    export CUDA_VISIBLE_DEVICES=0;    cmsRun ecalOnly_newProducer_and_dump.py
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"onlineEnergy\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"chi2\",200,0,10,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"chi2\",1000,0,10,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"chi2\",200,0,100,0\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitter\",400,-10,10,2\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"jitterError\",400,-0.001,0.5,2\)

    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM1\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM2\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM3\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM4\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeM5\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP1\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP2\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP3\",100,0,100\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"outOfTimeAmplitudeP4\",100,0,100\)
    
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"size\",200,0,30000\)

    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"flags\",200,-100,100,0\)

    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"hashindex\",70000,0,70000\)
    r99t output.root    ../plot/drawDifferenceOne.cxx\(\"hashindex\",1000,0,70000\)
        
    /data/patatrack/vkhriste/data/ecal/test.withcheck.root
                                       test.withoutcheck.root
                                       
    cmsRun dump_ecalonly_dumpComparison.py
    
    

    
    
    export CUDA_VISIBLE_DEVICES=0;    cmsRun ecalOnly_newProducer_and_dump_regularInputs.py
    -> standard root file as input
    
    
    export CUDA_VISIBLE_DEVICES=0;    cmsRun raw2digi_ecalonly_patatrack_and_dump_Viktor.py
    
    export CUDA_VISIBLE_DEVICES=0;    cmsRun raw2digi_ecalonly_patatrack_and_dump_Viktor.py &> tmp.txt

    export CUDA_VISIBLE_DEVICES=0;    cmsRun ecalOnly_newProducer_and_dump.py
    
    
    
    TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
    tree->Scan("hashindexEE:onlineEnergyEE:second_onlineEnergyEE", "((onlineEnergyEE/second_onlineEnergyEE)>1.01 || (onlineEnergyEE/second_onlineEnergyEE)<0.99 ) && onlineEnergyEE>0 && second_onlineEnergyEE>0 ")
    tree->Scan("hashindexEE:second_hashindexEE:onlineEnergyEE:second_onlineEnergyEE", "((onlineEnergyEE/second_onlineEnergyEE)>1.01 || (onlineEnergyEE/second_onlineEnergyEE)<0.99 ) && onlineEnergyEE>0 && second_onlineEnergyEE>0 ")

    
    TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
    tree->Scan("hashindexEB:onlineEnergyEB:second_onlineEnergyEB", "((onlineEnergyEB/second_onlineEnergyEB)>1.01 || (onlineEnergyEB/second_onlineEnergyEB)<0.99 ) && onlineEnergyEB>0 && second_onlineEnergyEB>0 ")
    


Commit

    git branch amassiro-fix-matrix

    git push my-cmssw amassiro-fix-matrix

    

Dump HLT configuration


    --offline
     
    
    hltGetConfiguration  /online/collisions/2018/2e34/v3.6/HLT/V4 --full --online  --data  --unprescale --process TEST --globaltag 101X_dataRun2_Prompt_v11 \
     --input /store/relval/CMSSW_8_0_3/RelValZEE_13/GEN-SIM-DIGI-RAW-HLTDEBUG/80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/626AD45E-D8EF-E511-9BC8-0025905A6126.root  \
     > hlt_data.py 
    
    then look for: hltEcalUncalibRecHit ---> ecalMultiFitUncalibRecHit
    
    
    
//==== parameter include ====
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


//---- std include ----
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream> 


//---- ROOT
#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"


//---- ECAL
#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/EcalDigi/interface/EEDataFrame.h"
#include "DataFormats/EcalDigi/interface/EBDataFrame.h"


#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "CondFormats/EcalObjects/interface/EcalPedestals.h"
#include "CondFormats/EcalObjects/interface/EcalMGPAGainRatio.h"
#include "CondFormats/EcalObjects/interface/EcalXtalGroupId.h"
#include "CondFormats/EcalObjects/interface/EcalPulseShapes.h"
#include "CondFormats/EcalObjects/interface/EcalPulseCovariances.h"
#include "DataFormats/EcalDigi/interface/EcalDataFrame.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EigenMatrixTypes.h"


#include "CondFormats/EcalObjects/interface/EcalGainRatios.h"

// #include "RecoLocalCalo/EcalRecAlgos/interface/PulseChiSqSNNLS_gpu.h"



//---- cuda
#include <cuda.h>
#include <cuda_runtime.h>
#include <assert.h>

__global__  void kernel_print() {
  printf("Hello!\n");
}
  

__global__  void kernel_reconstruct(
  uint16_t const *digis,
  uint32_t const *ids,
  EcalPedestal const *pedestals,
  EcalMGPAGainRatio const *gains,
  EcalXtalGroupId const *xtals,
  EcalPulseShape const *shapes,
  EcalPulseCovariance const *covariances,
  EcalUncalibratedRecHit *rechits,
  SampleMatrix const *noisecors,
  unsigned int size){
  
//   int idx = threadIdx.x + blockIdx.x * blockDim.x;
//   
//   if (idx < size) {
//     uint16_t const* p_current_digi = &digis[idx*EcalDataFrame::MAXSAMPLES];
//     DetId  current_id{ids[idx]};
//     EcalDataFrame edf{edm::DataFrame{ids[idx], p_current_digi, EcalDataFrame::MAXSAMPLES}};
//     auto const* aped = &pedestals[idx];
//     auto const* aGain = &gains[idx];
//     auto const* gid = &xtals[idx];
//     auto const* aPulse = &shapes[idx];
//     auto const* aPulseCov = &covariances[idx];
//     
//     #ifdef DEBUG
//     if (idx == 0) {
//       printf("*******************\n");
//       printf("gpu debug tid = %i\n", idx);
//       for(unsigned int iSample = 0; 
//           iSample < EcalDataFrame::MAXSAMPLES; iSample++)
//           printf("tid = %i i = %d adc = %d\n", idx, iSample, 
//                  edf.sample(iSample).adc());
//           for (int i=0; i<EcalPulseShape::TEMPLATESAMPLES; ++i)
//             printf("pulseshape[%d] = %f\n", i, aPulse->pdfval[i]);
//     }
//     #endif
//     
//     FullSampleVector fullpulse(FullSampleVector::Zero());
//     FullSampleMatrix fullpulsecov(FullSampleMatrix::Zero());
//     
//     double pedVec[3]     = {aped->mean_x12, aped->mean_x6, aped->mean_x1 };
//     double pedRMSVec[3]  = {aped->rms_x12,  aped->rms_x6,  aped->rms_x1 };
//     double gainRatios[3] = {1., aGain->gain12Over6(), 
//       aGain->gain6Over1()*aGain->gain12Over6()};
//       
//       for (int i=0; i<EcalPulseShape::TEMPLATESAMPLES; ++i)
//         fullpulse(i+7) = aPulse->pdfval[i];
//       for(int i=0; i<EcalPulseShape::TEMPLATESAMPLES;i++)
//         for(int j=0; j<EcalPulseShape::TEMPLATESAMPLES;j++)
//           fullpulsecov(i+7,j+7) = aPulseCov->covval[i][j];
//         
//         int lastSampleBeforeSaturation = -2;
//       for(unsigned int iSample = 0; 
//           iSample < EcalDataFrame::MAXSAMPLES; iSample++){
//         if (edf.sample(iSample).gainId() == 0 ) {
//           lastSampleBeforeSaturation=iSample-1;
//           break;
//         }
//           }
//           
//           EcalUncalibratedRecHit rh{current_id, 4095*12, 0, 0, 0};
//           
//           // === amplitude computation ===
//           if ( lastSampleBeforeSaturation == 4 ) { 
//             // saturation on the expected max sample
//             EcalUncalibratedRecHit tmp{current_id, 4095*12, 0, 0, 0};
//             tmp.setFlagBit( EcalUncalibratedRecHit::kSaturated );
//             // do not propagate the default chi2 = -1 value 
//             // to the calib rechit (mapped to 64), set it to 0 when saturation
//             tmp.setChi2(0);
//             rechits[idx] = tmp;
//           } else if ( lastSampleBeforeSaturation >= -1 ) { 
//             // saturation on other samples: cannot extrapolate from the fourth one
//             int gainId = edf.sample(5).gainId();
//             if (gainId==0) gainId=3;
//             auto pedestal = pedVec[gainId-1];
//             auto gainratio = gainRatios[gainId-1];
//             double amplitude = ((double)(edf.sample(5).adc()) - 
//             pedestal) * gainratio;
//             EcalUncalibratedRecHit tmp{current_id, amplitude, 0, 0, 0};
//             tmp.setFlagBit( EcalUncalibratedRecHit::kSaturated );
//             // do not propagate the default chi2 = -1 value to the calib rechit (mapped to 64), set it to 0 when saturation
//             tmp.setChi2(0);
//             rechits[idx] = tmp;
//           } else {
//             // multifit
//             //result.push_back(multiFitMethod_.makeRecHit(*itdg, aped, aGain, 
//             //                 noisecors, fullpulse, fullpulsecov, activeBX));
//             BXVector activeBX;
//             activeBX.resize(10);
//             activeBX << -5,-4,-3,-2,-1,0,1,2,3,4;
//             EcalUncalibRecHitMultiFitAlgo algo{};
//             rechits[idx] = algo.makeRecHit(edf, aped, aGain, 
//                                            noisecors, fullpulse, fullpulsecov, 
//                                            activeBX);
//           }
//           
//   }
  
  }
  




int main(int argc, char** argv) {
  
  std::cout << "   ----------------------------          " << std::endl;
  std::cout << "   Single rechit reconstruction          " << std::endl;           
  std::cout << "   ----------------------------          " << std::endl;
  
  std::string fileInput     (argv[1]) ;

  
  
  std::cout << " fileInput      = " << fileInput << std::endl;
  
  //---- read file
  
  TFile* fileIn =  new TFile(fileInput.c_str(), "READ");
  TTree* tree = (TTree*) fileIn->Get("Events");
  tree->Print();
  
  std::cout << std::endl << std::endl << std::endl << std::endl;
  
  TTreeReader myReader("Events", fileIn);
  TTreeReaderValue<edm::Wrapper<EBDigiCollection> > EBdigis(myReader, "EBDigiCollection_ecalDigis_ebDigis_MyReco.");
 
  int ievent = 0;
  while (myReader.Next()) {
    const EBDigiCollection* ebDigis = nullptr;
    ebDigis = EBdigis->product();
    
    std::cout << " [ " << ievent << " ] ebDigis->size() = " << ebDigis->size() << std::endl;
    
    std::vector<EcalPedestal>        vpedestals;
    std::vector<EcalMGPAGainRatio>   vgains;
    std::vector<EcalXtalGroupId>     vxtals;
    std::vector<EcalPulseShape>      vpulses;
    std::vector<EcalPulseCovariance> vcovariances;
    SampleMatrixGainArray            noisecors;
    
    EcalUncalibratedRecHitCollection rechits;
    
    
    
    auto const& digis_data = ebDigis->data();
    using digis_type = std::vector<uint16_t>;
    digis_type::value_type *d_digis_data;
    
    auto const& ids = ebDigis->ids();
    using dids_type = std::vector<uint32_t>;
    dids_type::value_type *d_ids;
    
    EcalPedestal *d_pedestals;
    EcalMGPAGainRatio *d_gains;
    EcalXtalGroupId *d_xtals;
    EcalPulseShape *d_shapes;
    EcalPulseCovariance *d_covariances;
    EcalUncalibratedRecHit *d_rechits;
    SampleMatrix *d_noisecors;
    
    
    
    cudaMalloc((void**)&d_digis_data,    digis_data.size() * sizeof(digis_type::value_type));
    cudaMalloc((void**)&d_ids,           ids.size() * sizeof(dids_type::value_type));
    cudaMalloc((void**)&d_pedestals,     vpedestals.size() * sizeof(EcalPedestal));
    cudaMalloc((void**)&d_gains,         vgains.size() * sizeof(EcalMGPAGainRatio));
    cudaMalloc((void**)&d_xtals,         vxtals.size() * sizeof(EcalXtalGroupId));
    cudaMalloc((void**)&d_shapes,        vpulses.size() * sizeof(EcalPulseShape));
    cudaMalloc((void**)&d_covariances,   vcovariances.size() * sizeof(EcalPulseCovariance));
    cudaMalloc((void**)&d_rechits,       rechits.size() * sizeof(EcalUncalibratedRecHit));
    cudaMalloc((void**)&d_noisecors,     noisecors.size() * sizeof(SampleMatrix));
    
    //---- basic: 
    //  input:
    //       10 samples, 1 float (rms), noise covariance matrix, pulse shape, pulse shape covariance matrix
    //  output:
    //       10 amplitudes
    //
    // All additional information to ECALrechit managed by CPU
    //
    //
    
      
    // 
    // copy to the device
    // TODO: can conditions be copied only once when updated?
    //
    cudaMemcpy(d_digis_data, digis_data.data(),     digis_data.size() * sizeof(digis_type::value_type),    cudaMemcpyHostToDevice);
    cudaMemcpy(d_ids, ids.data(),                   ids.size() * sizeof(dids_type::value_type),            cudaMemcpyHostToDevice);
    cudaMemcpy(d_pedestals, vpedestals.data(),      vpedestals.size() * sizeof(EcalPedestal),              cudaMemcpyHostToDevice);
    cudaMemcpy(d_gains, vgains.data(),              vgains.size() * sizeof(EcalMGPAGainRatio),             cudaMemcpyHostToDevice);
    cudaMemcpy(d_xtals, vxtals.data(),              vxtals.size() * sizeof(EcalXtalGroupId),               cudaMemcpyHostToDevice);
    cudaMemcpy(d_shapes, vpulses.data(),            vpulses.size() * sizeof(EcalPulseShape),               cudaMemcpyHostToDevice);
    cudaMemcpy(d_covariances, vcovariances.data(),  vcovariances.size() * sizeof(EcalPulseCovariance),     cudaMemcpyHostToDevice);
    cudaMemcpy(d_rechits, &(*rechits.begin()),      rechits.size() * sizeof(EcalUncalibratedRecHit),       cudaMemcpyHostToDevice);
    cudaMemcpy(d_noisecors, noisecors.data(),       noisecors.size() * sizeof(SampleMatrix),               cudaMemcpyHostToDevice);
    
    
    std::cout << "now fit" << std::endl;
    int nthreads_per_block = 256;
    int nblocks = (ebDigis->size() + nthreads_per_block - 1) / nthreads_per_block;

    kernel_print<<<nblocks, nthreads_per_block>>>();
    
    
//     kernel_reconstruct<<<nblocks, nthreads_per_block>>>(
//       d_digis_data,
//       d_ids,
//       d_pedestals,
//       d_gains,
//       d_xtals,
//       d_shapes,
//       d_covariances,
//       d_rechits,
//       d_noisecors,
//       ebDigis->size()
//     );
    
    cudaDeviceSynchronize();
    
      //
    // transfer the results back
    // 
    cudaMemcpy(&(*rechits.begin()), d_rechits, rechits.size() * sizeof(EcalUncalibratedRecHit), cudaMemcpyDeviceToHost);
    
    // 
    // free all the device ptrs
    // TODO: remove per event dealloc
    //
    cudaFree(d_digis_data);
    cudaFree(d_ids);
    cudaFree(d_pedestals);
    cudaFree(d_gains);
    cudaFree(d_xtals);
    cudaFree(d_shapes);
    cudaFree(d_covariances);
    cudaFree(d_rechits);
    cudaFree(d_noisecors);
    
    
//     PulseChiSqSNNLS _pulsefunc;
    
    
    
    ievent++;
  }
  
  
  
//   EBDigiCollection                      "ecalDigis"              "ebDigis"         "MyReco"   
  
//   edm::EDGetTokenT<EBDigiCollection>  ebDigiCollectionToken_;
//   ebDigiCollectionToken_ = consumes<EBDigiCollection>("ecalDigis", "ebDigis");
  
  
  
  
/*  
  HcalPulseShapes shapes;
  const HcalPulseShapes::Shape & shape(shapes.hbShape());
  HcalShapeIntegrator i(&shape);
  float maxdiff = 0.;
  float maxtime = 0.;
  */
  
  
  
  
  //---- get digis
  
  //---- run multifit
  
  
  std::cout << std::endl << " --- end --- " << std::endl << std::endl;
}



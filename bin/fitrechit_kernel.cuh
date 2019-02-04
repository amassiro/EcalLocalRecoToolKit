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


//---- cuda
#include <cuda.h>
// #include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <assert.h>

__global__ void kernel_print() ;


// __global__ 
// void kernel_print() {
//   printf("Hello!\n");
// }


// __global__
// void print(const char * message, size_t length) {
//   //printf("blockIdx.x, threadIdx.x: %d, %d\n", blockIdx.x, threadIdx.x);
//   for (size_t i = blockDim.x * blockIdx.x + threadIdx.x; i < length; i += blockDim.x * gridDim.x)
//     printf("%c", message[i]);
// }

  
/*
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
  

*/


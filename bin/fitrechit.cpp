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


// #include "RecoLocalCalo/EcalRecAlgos/interface/PulseChiSqSNNLS_gpu.h"



//---- cuda
#include <cuda.h>
#include <cuda_runtime.h>


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
    
    auto const& ids = ebDigis->ids();
    auto const& digis_data = ebDigis->data();
    
    using digis_type = std::vector<uint16_t>;
    digis_type::value_type *d_digis_data;
    
    cudaMalloc((void**)&d_digis_data, digis_data.size() * sizeof(digis_type::value_type));

    //---- basic: 
    //  input:
    //       10 samples, 1 float (rms), noise covariance matrix, pulse shape, pulse shape covariance matrix
    //  output:
    //       10 amplitudes
    //
    // All additional information to ECALrechit managed by CPU
    //
    //
    
//     cudaMalloc((void**)&d_pedestals, vpedestals.size() * sizeof(EcalPedestal));
//     cudaMalloc((void**)&d_gains, vgains.size() * sizeof(EcalMGPAGainRatio));
//     cudaMalloc((void**)&d_xtals, vxtals.size() * sizeof(EcalXtalGroupId));
//     cudaMalloc((void**)&d_shapes, vpulses.size() * sizeof(EcalPulseShape));
//     cudaMalloc((void**)&d_covariances, vcovariances.size() * sizeof(EcalPulseCovariance));
//     cudaMalloc((void**)&d_rechits, rechits.size() * sizeof(EcalUncalibratedRecHit));
//     cudaMalloc((void**)&d_noisecors, noisecors.size() * sizeof(SampleMatrix));
//     cuda::assert_if_error();
    
    
//     PulseChiSqSNNLS _pulsefunc;
    
    
    
    
//     void scatter(EcalDigiCollection const& digis,
//                  EcalUncalibratedRecHitCollection& rechits,
//                  std::vector<EcalPedestal> const& vpedestals,
//                  std::vector<EcalMGPAGainRatio> const& vgains,
//                  std::vector<EcalXtalGroupId> const& vxtals,
//                  std::vector<EcalPulseShape> const& vpulses,
//                  std::vector<EcalPulseCovariance> const& vcovariances,
//                  SampleMatrixGainArray const& noisecors) {
//       auto const& ids = digis.ids();
//       auto const& digis_data = digis.data();
//       using digis_type = std::vector<uint16_t>;
//       using dids_type = std::vector<uint32_t>;
//       digis_type::value_type *d_digis_data;
//       dids_type::value_type *d_ids;
//       EcalPedestal *d_pedestals;
//       EcalMGPAGainRatio *d_gains;
//       EcalXtalGroupId *d_xtals;
//       EcalPulseShape *d_shapes;
//       EcalPulseCovariance *d_covariances;
//       EcalUncalibratedRecHit *d_rechits;
//       SampleMatrix *d_noisecors;
//       
//       //
//       // TODO: remove per event alloc/dealloc -> do once at the start
//       //
//       cudaMalloc((void**)&d_digis_data,
//                  digis_data.size() * sizeof(digis_type::value_type));
//       cudaMalloc((void**)&d_ids,
//                  ids.size() * sizeof(dids_type::value_type));
//       cudaMalloc((void**)&d_pedestals,
//                  vpedestals.size() * sizeof(EcalPedestal));
//       cudaMalloc((void**)&d_gains, 
//                  vgains.size() * sizeof(EcalMGPAGainRatio));
//       cudaMalloc((void**)&d_xtals,
//                  vxtals.size() * sizeof(EcalXtalGroupId));
//       cudaMalloc((void**)&d_shapes,
//                  vpulses.size() * sizeof(EcalPulseShape));
//       cudaMalloc((void**)&d_covariances,
//                  vcovariances.size() * sizeof(EcalPulseCovariance));
//       cudaMalloc((void**)&d_rechits,
//                  rechits.size() * sizeof(EcalUncalibratedRecHit));
//       cudaMalloc((void**)&d_noisecors,
//                  noisecors.size() * sizeof(SampleMatrix));
//       ecal::cuda::assert_if_error();
//       
//       // 
//       // copy to the device
//       // TODO: can conditions be copied only once when updated?
//       //
//       cudaMemcpy(d_digis_data, digis_data.data(),
//                  digis_data.size() * sizeof(digis_type::value_type),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_ids, ids.data(),
//                  ids.size() * sizeof(dids_type::value_type),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_pedestals, vpedestals.data(),
//                  vpedestals.size() * sizeof(EcalPedestal),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_gains, vgains.data(),
//                  vgains.size() * sizeof(EcalMGPAGainRatio),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_xtals, vxtals.data(),
//                  vxtals.size() * sizeof(EcalXtalGroupId),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_shapes, vpulses.data(),
//                  vpulses.size() * sizeof(EcalPulseShape),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_covariances, vcovariances.data(),
//                  vcovariances.size() * sizeof(EcalPulseCovariance),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_rechits, &(*rechits.begin()),
//                  rechits.size() * sizeof(EcalUncalibratedRecHit),
//                  cudaMemcpyHostToDevice);
//       cudaMemcpy(d_noisecors, noisecors.data(),
//                  noisecors.size() * sizeof(SampleMatrix),
//                  cudaMemcpyHostToDevice);
//       ecal::cuda::assert_if_error();
//       
//       #ifdef DEBUG
//       unsigned int idx = 0;
//       uint16_t const* p_current_digi = &digis_data[idx*EcalDataFrame::MAXSAMPLES];
//       DetId  current_id{ids[idx]};
//       EcalDataFrame edf{edm::DataFrame{ids[idx], p_current_digi, EcalDataFrame::MAXSAMPLES}};
//       auto const* aped = &vpedestals[idx];
//       auto const* aGain = &vgains[idx];
//       auto const* gid = &vxtals[idx];
//       auto const* aPulse = &vpulses[idx];
//       auto const* aPulseCov = &vcovariances[idx];
//       
//       if (idx == 0) {
//         printf("*******************\n");
//         printf("cpu debug tid = %i\n", idx);
//         for(unsigned int iSample = 0; 
//             iSample < EcalDataFrame::MAXSAMPLES; iSample++)
//             printf("tid = %i i = %d adc = %d\n", idx, iSample, 
//                    edf.sample(iSample).adc());
//             for (int i=0; i<EcalPulseShape::TEMPLATESAMPLES; ++i)
//               printf("pulseshape[%d] = %f\n", i, aPulse->pdfval[i]);
//       }
//       #endif
//       
//       //
//       // launch 
//       // TODO: further ntreads/nblocks optimizations...
//       //
//       std::cout << "ecal::multifit::scatter()" << std::endl;
//       int nthreads_per_block = 256;
//       int nblocks = (digis.size() + nthreads_per_block - 1) / nthreads_per_block;
//       kernel_reconstruct<<<nblocks, nthreads_per_block>>>(
//         d_digis_data,
//         d_ids,
//         /* d_rechits, */
//         d_pedestals,
//         d_gains,
//         d_xtals,
//         d_shapes,
//         d_covariances,
//         d_rechits,
//         d_noisecors,
//         digis.size()
//       );
//       cudaDeviceSynchronize();
//       ecal::cuda::assert_if_error();
//       
//       //
//       // transfer the results back
//       // 
//       cudaMemcpy(&(*rechits.begin()), d_rechits,
//                  rechits.size() * sizeof(EcalUncalibratedRecHit),
//                  cudaMemcpyDeviceToHost);
//       
//       // 
//       // free all the device ptrs
//       // TODO: remove per event dealloc
//       //
//       cudaFree(d_digis_data);
//       cudaFree(d_ids);
//       cudaFree(d_pedestals);
//       cudaFree(d_gains);
//       cudaFree(d_xtals);
//       cudaFree(d_shapes);
//       cudaFree(d_covariances);
//       cudaFree(d_rechits);
//       cudaFree(d_noisecors);
//       ecal::cuda::assert_if_error();
      
      
    
    
    
    
    
    
    
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



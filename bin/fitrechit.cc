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


#include "fitrechit_kernel.cuh"

//---- cuda
#include <cuda.h>
// #include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <assert.h>


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

    std::cout << "now fit" << std::endl;
    int nthreads_per_block = 256;
    int nblocks = (ebDigis->size() + nthreads_per_block - 1) / nthreads_per_block;

    kernel_print<<<nblocks, nthreads_per_block>>>();
    
    ievent++;
  }
  
  //---- get digis
  
  //---- run multifit
  
  
  std::cout << std::endl << " --- end --- " << std::endl << std::endl;
}



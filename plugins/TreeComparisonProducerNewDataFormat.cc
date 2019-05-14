// -*- C++ -*-
//
// Package:    AdvancedMultifitCMSSW/TreeComparisonProducerNewDataFormat
// Class:      TreeComparisonProducerNewDataFormat
// 
/**\class TreeComparisonProducerNewDataFormat TreeComparisonProducerNewDataFormat.cc ECALValidation/EcalLocalRecoToolKit/plugins/TreeComparisonProducerNewDataFormat.cc
 * 
 D escription: [one line class su*mmary]
 
 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Andrea Massironi
//         Created:  Mon, 03 Sep 2018 10:09:05 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"



// ECAL specific

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbService.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbRecord.h"
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/DataRecord/interface/EcalADCToGeVConstantRcd.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstants.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstantsMC.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsMCRcd.h"


#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"



#include "FWCore/Framework/interface/ESHandle.h"



#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"   //     ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"    ----> CLHEP/Geometry/Point3D.h issue
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
// #include "Geometry/EcalAlgo/interface/EcalBarrelGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/EcalAlgo/interface/EcalEndcapGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue




// #include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
// #include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "CondFormats/EcalObjects/interface/EcalMGPAGainRatio.h"
#include "CondFormats/EcalObjects/interface/EcalGainRatios.h"
#include "CondFormats/DataRecord/interface/EcalGainRatiosRcd.h"


#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"







//---- for TP

#include "CondFormats/EcalObjects/interface/EcalTPGLutIdMap.h"
#include "CondFormats/EcalObjects/interface/EcalTPGLutGroup.h"
#include "CondFormats/EcalObjects/interface/EcalTPGPhysicsConst.h"
#include "CondFormats/DataRecord/interface/EcalTPGLutIdMapRcd.h"
#include "CondFormats/DataRecord/interface/EcalTPGLutGroupRcd.h"
#include "CondFormats/DataRecord/interface/EcalTPGPhysicsConstRcd.h"


#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"



//---- for new DataFormats

// #include "DataFormats/EcalRecHitSoA/interface/EcalUncalibratedRecHit_soa.h"
#include "CUDADataFormats/EcalRecHitSoA/interface/EcalUncalibratedRecHit_soa.h"

// 
// ecal::UncalibratedRecHit<ecal::Tag::soa>    "ecalMultiFitUncalibRecHitgpu"   "EcalUncalibRecHitsEBgpunew"   "MyReco"   
// ecal::UncalibratedRecHit<ecal::Tag::soa>    "ecalMultiFitUncalibRecHitgpu"   "EcalUncalibRecHitsEEgpunew"   "MyReco"   
// 




#include "TTree.h"




//---- for Zee part
#include "DataFormats/PatCandidates/interface/Electron.h"





//---- ad hoc hashindex from gpu code


// namespace ecal { namespace multifit {
  
  namespace external {
    
    namespace barrel {
      
      bool positiveZ(uint32_t id) { return id & 0x10000; }
      
      uint32_t ietaAbs(uint32_t id) { return (id >> 9) & 0x7F; }
      
      uint32_t iphi(uint32_t id) { return id & 0x1FF; }
      
    }
    
  }
  
  uint32_t hashedIndexEB(uint32_t id) {
    using namespace external::barrel;
    return (EBDetId::MAX_IETA + 
    (positiveZ(id) ? ietaAbs(id)-1 : -ietaAbs(id)) ) * EBDetId::MAX_IPHI + 
    iphi(id)-1;
  }
  
  namespace external {
    
    namespace endcap {
      
      uint32_t ix(uint32_t id) { return (id >> 7) & 0x7F; }
      
      uint32_t iy(uint32_t id) { return id & 0x7F; }
      
      bool positiveZ(uint32_t id) { return id & 0x4000; }
      
      // these constants come from EE Det Id 
      const unsigned short kxf[] = {
//         41,  51,  41,  51,  41,  51,  36,  51,  36,  51,
//         26,  51,  26,  51,  26,  51,  21,  51,  21,  51,
//         21,  51,  21,  51,  21,  51,  16,  51,  16,  51, 
//         14,  51,  14,  51,  14,  51,  14,  51,  14,  51, 
//         9,  51,   9,  51,   9,  51,   9,  51,   9,  5, 
//         6,  51,   6,  51,   6,  51,   6,  51,   6,  51, 
//         6,  51,   6,  51,   6,  51,   6,  51,   6,  51, 
//         4,  51,   4,  51,   4,  51,   4,  51,   4,  56, 
//         1,  58,   1,  59,   1,  60,   1,  61,   1,  61, 
//         1,  62,   1,  62,   1,  62,   1,  62,   1,  62, 
//         1,  62,   1,  62,   1,  62,   1,  62,   1,  62, 
//         1,  61,   1,  61,   1,  60,   1,  59,   1,  58, 
//         4,  56,   4,  51,   4,  51,   4,  51,   4,  51, 
//         6,  51,   6,  51,   6,  51,   6,  51,   6,  51, 
//         6,  51,   6,  51,   6,  51,   6,  51,   6,  51, 
//         9,  51,   9,  51,   9,  51,   9,  51,   9,  51, 
//         14,  51,  14,  51,  14,  51,  14,  51,  14,  51, 
//         16,  51,  16,  51,  21,  51,  21,  51,  21,  51, 
//         21,  51,  21,  51,  26,  51,  26,  51,  26,  51, 
//         36,  51,  36,  51,  41,  51,  41,  51,  41,  51  
        
        41, 51, 41, 51, 41, 51, 36, 51, 36, 51, 26, 51, 26, 51, 26, 51, 21, 51, 21, 51, 21, 51, 21, 51, 21, 51, 16, 51, 16,
        51, 14, 51, 14, 51, 14, 51, 14, 51, 14, 51, 9,  51, 9,  51, 9,  51, 9,  51, 9,  51, 6,  51, 6,  51, 6,  51, 6,  51,
        6,  51, 6,  51, 6,  51, 6,  51, 6,  51, 6,  51, 4,  51, 4,  51, 4,  51, 4,  51, 4,  56, 1,  58, 1,  59, 1,  60, 1,
        61, 1,  61, 1,  62, 1,  62, 1,  62, 1,  62, 1,  62, 1,  62, 1,  62, 1,  62, 1,  62, 1,  62, 1,  61, 1,  61, 1,  60,
        1,  59, 1,  58, 4,  56, 4,  51, 4,  51, 4,  51, 4,  51, 6,  51, 6,  51, 6,  51, 6,  51, 6,  51, 6,  51, 6,  51, 6,
        51, 6,  51, 6,  51, 9,  51, 9,  51, 9,  51, 9,  51, 9,  51, 14, 51, 14, 51, 14, 51, 14, 51, 14, 51, 16, 51, 16, 51,
        21, 51, 21, 51, 21, 51, 21, 51, 21, 51, 26, 51, 26, 51, 26, 51, 36, 51, 36, 51, 41, 51, 41, 51, 41, 51
        
      } ;
      
      const unsigned short kdi[] = {
//         0,   10,   20,   30,   40,   50,   60,   75,   90,  105,
//         120,  145,  170,  195,  220,  245,  270,  300,  330,  360,
//         390,  420,  450,  480,  510,  540,  570,  605,  640,  675,
//         710,  747,  784,  821,  858,  895,  932,  969, 1006, 1043,
//         1080, 1122, 1164, 1206, 1248, 1290, 1332, 1374, 1416, 1458,
//         1500, 1545, 1590, 1635, 1680, 1725, 1770, 1815, 1860, 1905,
//         1950, 1995, 2040, 2085, 2130, 2175, 2220, 2265, 2310, 2355,
//         2400, 2447, 2494, 2541, 2588, 2635, 2682, 2729, 2776, 2818,
//         2860, 2903, 2946, 2988, 3030, 3071, 3112, 3152, 3192, 3232,
//         3272, 3311, 3350, 3389, 3428, 3467, 3506, 3545, 3584, 3623,
//         3662, 3701, 3740, 3779, 3818, 3857, 3896, 3935, 3974, 4013,
//         4052, 4092, 4132, 4172, 4212, 4253, 4294, 4336, 4378, 4421,
//         4464, 4506, 4548, 4595, 4642, 4689, 4736, 4783, 4830, 4877,
//         4924, 4969, 5014, 5059, 5104, 5149, 5194, 5239, 5284, 5329,
//         5374, 5419, 5464, 5509, 5554, 5599, 5644, 5689, 5734, 5779,
//         5824, 5866, 5908, 5950, 5992, 6034, 6076, 6118, 6160, 6202,
//         6244, 6281, 6318, 6355, 6392, 6429, 6466, 6503, 6540, 6577,
//         6614, 6649, 6684, 6719, 6754, 6784, 6814, 6844, 6874, 6904,
//         6934, 6964, 6994, 7024, 7054, 7079, 7104, 7129, 7154, 7179,
//         7204, 7219, 7234, 7249, 7264, 7274, 7284, 7294, 7304, 7314

        0,    10,   20,   30,   40,   50,   60,   75,   90,   105,  120,  145,  170,  195,  220,  245,  270,  300,  330,
        360,  390,  420,  450,  480,  510,  540,  570,  605,  640,  675,  710,  747,  784,  821,  858,  895,  932,  969,
        1006, 1043, 1080, 1122, 1164, 1206, 1248, 1290, 1332, 1374, 1416, 1458, 1500, 1545, 1590, 1635, 1680, 1725, 1770,
        1815, 1860, 1905, 1950, 1995, 2040, 2085, 2130, 2175, 2220, 2265, 2310, 2355, 2400, 2447, 2494, 2541, 2588, 2635,
        2682, 2729, 2776, 2818, 2860, 2903, 2946, 2988, 3030, 3071, 3112, 3152, 3192, 3232, 3272, 3311, 3350, 3389, 3428,
        3467, 3506, 3545, 3584, 3623, 3662, 3701, 3740, 3779, 3818, 3857, 3896, 3935, 3974, 4013, 4052, 4092, 4132, 4172,
        4212, 4253, 4294, 4336, 4378, 4421, 4464, 4506, 4548, 4595, 4642, 4689, 4736, 4783, 4830, 4877, 4924, 4969, 5014,
        5059, 5104, 5149, 5194, 5239, 5284, 5329, 5374, 5419, 5464, 5509, 5554, 5599, 5644, 5689, 5734, 5779, 5824, 5866,
        5908, 5950, 5992, 6034, 6076, 6118, 6160, 6202, 6244, 6281, 6318, 6355, 6392, 6429, 6466, 6503, 6540, 6577, 6614,
        6649, 6684, 6719, 6754, 6784, 6814, 6844, 6874, 6904, 6934, 6964, 6994, 7024, 7054, 7079, 7104, 7129, 7154, 7179,
        7204, 7219, 7234, 7249, 7264, 7274, 7284, 7294, 7304, 7314
        
      };
      
    }
    
  }
  
 
  uint32_t hashedIndexEE(uint32_t id) {
    using namespace external::endcap;
    
    const uint32_t jx ( ix(id) ) ;
    const uint32_t jd ( 2*( iy(id) - 1 ) + ( jx - 1 )/50 ) ;
    return (  ( positiveZ(id) ? EEDetId::kEEhalf : 0) + kdi[jd] + jx - kxf[jd] ) ;
  }
  
// }}


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TreeComparisonProducerNewDataFormat : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit TreeComparisonProducerNewDataFormat(const edm::ParameterSet&);
  ~TreeComparisonProducerNewDataFormat();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
  
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_ebrechits;
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_eerechits;

  edm::EDGetTokenT<ecal::SoAUncalibratedRecHitCollection> _token_second_ebrechits;
  edm::EDGetTokenT<ecal::SoAUncalibratedRecHitCollection> _token_second_eerechits;
  
  TTree *outTree;
  
  UInt_t _run;
  UShort_t _lumi;
  UShort_t _bx;
  UShort_t _event;      
  float _onlineEnergyEB[61200];
  float _onlineEnergyEE[14648];
  int _sizeEB;      
  int _sizeEE;      
  float _chi2EB[61200];
  float _chi2EE[14648];
  float _jitterEB[61200];
  float _jitterEE[14648];
  float _jitterErrorEB[61200];
  float _jitterErrorEE[14648];
  float _amplitudeErrorEB[61200];
  float _amplitudeErrorEE[14648];
  float _outOfTimeAmplitudeM1EB[61200];
  float _outOfTimeAmplitudeM1EE[14648];
  float _outOfTimeAmplitudeM2EB[61200];
  float _outOfTimeAmplitudeM2EE[14648];
  float _outOfTimeAmplitudeM3EB[61200];
  float _outOfTimeAmplitudeM3EE[14648];
  float _outOfTimeAmplitudeM4EB[61200];
  float _outOfTimeAmplitudeM4EE[14648];
  float _outOfTimeAmplitudeP1EB[61200];
  float _outOfTimeAmplitudeP1EE[14648];
  float _outOfTimeAmplitudeP2EB[61200];
  float _outOfTimeAmplitudeP2EE[14648];
  float _outOfTimeAmplitudeP3EB[61200];
  float _outOfTimeAmplitudeP3EE[14648];
  float _outOfTimeAmplitudeP4EB[61200];
  float _outOfTimeAmplitudeP4EE[14648];
  float _outOfTimeAmplitudeM5EB[61200];
  float _outOfTimeAmplitudeM5EE[14648];
  int   _flagsEB[61200];
  int   _flagsEE[14648];
  int   _hashindexEB[61200];
  int   _hashindexEE[14648];
  
  
  float _second_onlineEnergyEB[61200];
  float _second_onlineEnergyEE[14648];
  int _second_sizeEB;      
  int _second_sizeEE;      
  float _second_chi2EB[61200];
  float _second_chi2EE[14648];
  float _second_jitterEB[61200];
  float _second_jitterEE[14648];
  float _second_jitterErrorEB[61200];
  float _second_jitterErrorEE[14648];
  float _second_amplitudeErrorEB[61200];
  float _second_amplitudeErrorEE[14648];
  float _second_outOfTimeAmplitudeM1EB[61200];
  float _second_outOfTimeAmplitudeM1EE[14648];
  float _second_outOfTimeAmplitudeM2EB[61200];
  float _second_outOfTimeAmplitudeM2EE[14648];
  float _second_outOfTimeAmplitudeM3EB[61200];
  float _second_outOfTimeAmplitudeM3EE[14648];
  float _second_outOfTimeAmplitudeM4EB[61200];
  float _second_outOfTimeAmplitudeM4EE[14648];
  float _second_outOfTimeAmplitudeP1EB[61200];
  float _second_outOfTimeAmplitudeP1EE[14648];
  float _second_outOfTimeAmplitudeP2EB[61200];
  float _second_outOfTimeAmplitudeP2EE[14648];
  float _second_outOfTimeAmplitudeP3EB[61200];
  float _second_outOfTimeAmplitudeP3EE[14648];
  float _second_outOfTimeAmplitudeP4EB[61200];
  float _second_outOfTimeAmplitudeP4EE[14648];
  float _second_outOfTimeAmplitudeM5EB[61200];
  float _second_outOfTimeAmplitudeM5EE[14648];
  int   _second_flagsEB[61200];
  int   _second_flagsEE[14648];
  int   _second_hashindexEB[61200];
  int   _second_hashindexEE[14648];
  
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TreeComparisonProducerNewDataFormat::TreeComparisonProducerNewDataFormat(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  usesResource("TFileService");
  
  
  //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> fs;
    
  _token_ebrechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalUncalibRecHitsEBCollection"));
  _token_eerechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalUncalibRecHitsEECollection"));

  _token_second_ebrechits = consumes<ecal::SoAUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("SecondEcalUncalibRecHitsEBCollection"));
  _token_second_eerechits = consumes<ecal::SoAUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("SecondEcalUncalibRecHitsEECollection"));
  
  outTree = fs->make<TTree>("tree","tree");
  
  outTree->Branch("run",               &_run,             "run/i");
  outTree->Branch("lumi",              &_lumi,            "lumi/s");
  outTree->Branch("bx",                &_bx,              "bx/s");
  outTree->Branch("event",             &_event,           "event/i");
  outTree->Branch("onlineEnergyEB",       _onlineEnergyEB,    "onlineEnergyEB[61200]/F");
  outTree->Branch("onlineEnergyEE",       _onlineEnergyEE,    "onlineEnergyEE[14648]/F");
  outTree->Branch("chi2EB",       _chi2EB,    "chi2EB[61200]/F");
  outTree->Branch("chi2EE",       _chi2EE,    "chi2EE[14648]/F");
  outTree->Branch("jitterEB",       _jitterEB,    "jitterEB[61200]/F");
  outTree->Branch("jitterEE",       _jitterEE,    "jitterEE[14648]/F");
  outTree->Branch("jitterErrorEB",       _jitterErrorEB,    "jitterErrorEB[61200]/F");
  outTree->Branch("jitterErrorEE",       _jitterErrorEE,    "jitterErrorEE[14648]/F");
  outTree->Branch("amplitudeErrorEB",       _amplitudeErrorEB,    "amplitudeErrorEB[61200]/F");
  outTree->Branch("amplitudeErrorEE",       _amplitudeErrorEE,    "amplitudeErrorEE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeM1EB",       _outOfTimeAmplitudeM1EB,    "outOfTimeAmplitudeM1EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeM1EE",       _outOfTimeAmplitudeM1EE,    "outOfTimeAmplitudeM1EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeM2EB",       _outOfTimeAmplitudeM2EB,    "outOfTimeAmplitudeM2EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeM2EE",       _outOfTimeAmplitudeM2EE,    "outOfTimeAmplitudeM2EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeM3EB",       _outOfTimeAmplitudeM3EB,    "outOfTimeAmplitudeM3EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeM3EE",       _outOfTimeAmplitudeM3EE,    "outOfTimeAmplitudeM3EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeM4EB",       _outOfTimeAmplitudeM4EB,    "outOfTimeAmplitudeM4EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeM4EE",       _outOfTimeAmplitudeM4EE,    "outOfTimeAmplitudeM4EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeP1EB",       _outOfTimeAmplitudeP1EB,    "outOfTimeAmplitudeP1EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeP1EE",       _outOfTimeAmplitudeP1EE,    "outOfTimeAmplitudeP1EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeP2EB",       _outOfTimeAmplitudeP2EB,    "outOfTimeAmplitudeP2EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeP2EE",       _outOfTimeAmplitudeP2EE,    "outOfTimeAmplitudeP2EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeP3EB",       _outOfTimeAmplitudeP3EB,    "outOfTimeAmplitudeP3EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeP3EE",       _outOfTimeAmplitudeP3EE,    "outOfTimeAmplitudeP3EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeP4EB",       _outOfTimeAmplitudeP4EB,    "outOfTimeAmplitudeP4EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeP4EE",       _outOfTimeAmplitudeP4EE,    "outOfTimeAmplitudeP4EE[14648]/F");
  outTree->Branch("outOfTimeAmplitudeM5EB",       _outOfTimeAmplitudeM5EB,    "outOfTimeAmplitudeM5EB[61200]/F");
  outTree->Branch("outOfTimeAmplitudeM5EE",       _outOfTimeAmplitudeM5EE,    "outOfTimeAmplitudeM5EE[14648]/F");
  outTree->Branch("sizeEB",             &_sizeEB,           "sizeEB/I");
  outTree->Branch("sizeEE",             &_sizeEE,           "sizeEE/I");
  outTree->Branch("flagsEB",       _flagsEB,    "flagsEB[61200]/I");
  outTree->Branch("flagsEE",       _flagsEE,    "flagsEE[14648]/I");
  outTree->Branch("hashindexEB",       _hashindexEB,    "hashindexEB[61200]/I");
  outTree->Branch("hashindexEE",       _hashindexEE,    "hashindexEE[14648]/I");
  
  outTree->Branch("second_onlineEnergyEB",       _second_onlineEnergyEB,    "second_onlineEnergyEB[61200]/F");
  outTree->Branch("second_onlineEnergyEE",       _second_onlineEnergyEE,    "second_onlineEnergyEE[14648]/F");
  outTree->Branch("second_chi2EB",       _second_chi2EB,    "second_chi2EB[61200]/F");
  outTree->Branch("second_chi2EE",       _second_chi2EE,    "second_chi2EE[14648]/F");
  outTree->Branch("second_jitterEB",       _second_jitterEB,    "second_jitterEB[61200]/F");
  outTree->Branch("second_jitterEE",       _second_jitterEE,    "second_jitterEE[14648]/F");
  outTree->Branch("second_jitterErrorEB",       _second_jitterErrorEB,    "second_jitterErrorEB[61200]/F");
  outTree->Branch("second_jitterErrorEE",       _second_jitterErrorEE,    "second_jitterErrorEE[14648]/F");
  outTree->Branch("second_amplitudeErrorEB",       _second_amplitudeErrorEB,    "second_amplitudeErrorEB[61200]/F");
  outTree->Branch("second_amplitudeErrorEE",       _second_amplitudeErrorEE,    "second_amplitudeErrorEE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeM1EB",       _second_outOfTimeAmplitudeM1EB,    "second_outOfTimeAmplitudeM1EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeM1EE",       _second_outOfTimeAmplitudeM1EE,    "second_outOfTimeAmplitudeM1EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeM2EB",       _second_outOfTimeAmplitudeM2EB,    "second_outOfTimeAmplitudeM2EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeM2EE",       _second_outOfTimeAmplitudeM2EE,    "second_outOfTimeAmplitudeM2EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeM3EB",       _second_outOfTimeAmplitudeM3EB,    "second_outOfTimeAmplitudeM3EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeM3EE",       _second_outOfTimeAmplitudeM3EE,    "second_outOfTimeAmplitudeM3EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeM4EB",       _second_outOfTimeAmplitudeM4EB,    "second_outOfTimeAmplitudeM4EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeM4EE",       _second_outOfTimeAmplitudeM4EE,    "second_outOfTimeAmplitudeM4EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeP1EB",       _second_outOfTimeAmplitudeP1EB,    "second_outOfTimeAmplitudeP1EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeP1EE",       _second_outOfTimeAmplitudeP1EE,    "second_outOfTimeAmplitudeP1EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeP2EB",       _second_outOfTimeAmplitudeP2EB,    "second_outOfTimeAmplitudeP2EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeP2EE",       _second_outOfTimeAmplitudeP2EE,    "second_outOfTimeAmplitudeP2EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeP3EB",       _second_outOfTimeAmplitudeP3EB,    "second_outOfTimeAmplitudeP3EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeP3EE",       _second_outOfTimeAmplitudeP3EE,    "second_outOfTimeAmplitudeP3EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeP4EB",       _second_outOfTimeAmplitudeP4EB,    "second_outOfTimeAmplitudeP4EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeP4EE",       _second_outOfTimeAmplitudeP4EE,    "second_outOfTimeAmplitudeP4EE[14648]/F");
  outTree->Branch("second_outOfTimeAmplitudeM5EB",       _second_outOfTimeAmplitudeM5EB,    "second_outOfTimeAmplitudeM5EB[61200]/F");
  outTree->Branch("second_outOfTimeAmplitudeM5EE",       _second_outOfTimeAmplitudeM5EE,    "second_outOfTimeAmplitudeM5EE[14648]/F");
  outTree->Branch("second_sizeEB",             &_second_sizeEB,           "second_sizeEB/I");
  outTree->Branch("second_sizeEE",             &_second_sizeEE,           "second_sizeEE/I");
  outTree->Branch("second_flagsEB",       _second_flagsEB,    "second_flagsEB[61200]/I");
  outTree->Branch("second_flagsEE",       _second_flagsEE,    "second_flagsEE[14648]/I");
  outTree->Branch("second_hashindexEB",       _second_hashindexEB,    "second_hashindexEB[61200]/I");
  outTree->Branch("second_hashindexEE",       _second_hashindexEE,    "second_hashindexEE[14648]/I");
  
}


TreeComparisonProducerNewDataFormat::~TreeComparisonProducerNewDataFormat()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeComparisonProducerNewDataFormat::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
  _run = iEvent.eventAuxiliary().run();
  _lumi = iEvent.eventAuxiliary().luminosityBlock();
  _bx = iEvent.eventAuxiliary().bunchCrossing();
  _event = iEvent.eventAuxiliary().event();
  
  //---- rechits
  
  edm::Handle<EcalUncalibratedRecHitCollection> ebrechithandle;
  const EcalUncalibratedRecHitCollection *ebrechits = NULL;
  edm::Handle<EcalUncalibratedRecHitCollection> eerechithandle;
  const EcalUncalibratedRecHitCollection *eerechits = NULL;
  
  iEvent.getByToken(_token_ebrechits,ebrechithandle);
  ebrechits = ebrechithandle.product();
  iEvent.getByToken(_token_eerechits,eerechithandle);
  eerechits = eerechithandle.product();
  
  
  //---- rechits second collection
  
  edm::Handle<ecal::SoAUncalibratedRecHitCollection> second_ebrechithandle;
  const ecal::SoAUncalibratedRecHitCollection *second_ebrechits = NULL;
  edm::Handle<ecal::SoAUncalibratedRecHitCollection> second_eerechithandle;
  const ecal::SoAUncalibratedRecHitCollection *second_eerechits = NULL;
  
  iEvent.getByToken(_token_second_ebrechits,second_ebrechithandle);
  second_ebrechits = second_ebrechithandle.product();
  iEvent.getByToken(_token_second_eerechits,second_eerechithandle);
  second_eerechits = second_eerechithandle.product();


  
  
  //---- fill information
  
  for (int ixtal=0; ixtal < 61200; ixtal++) {
    //---- Fill flag for this crystal
    _onlineEnergyEB[ixtal] = -99;
    _chi2EB[ixtal] = -99;
    _jitterEB[ixtal] = -99;
    _jitterErrorEB[ixtal] = -99;
    _amplitudeErrorEB[ixtal] = -99;
    _outOfTimeAmplitudeM1EB[ixtal] = -99;
    _outOfTimeAmplitudeM2EB[ixtal] = -99;
    _outOfTimeAmplitudeM3EB[ixtal] = -99;
    _outOfTimeAmplitudeM4EB[ixtal] = -99;
    _outOfTimeAmplitudeM5EB[ixtal] = -99;
    _outOfTimeAmplitudeP1EB[ixtal] = -99;
    _outOfTimeAmplitudeP2EB[ixtal] = -99;
    _outOfTimeAmplitudeP3EB[ixtal] = -99;
    _outOfTimeAmplitudeP4EB[ixtal] = -99;
    _flagsEB[ixtal] = -99;
    _hashindexEB[ixtal] = -99;
    
    _second_onlineEnergyEB[ixtal] = -99;
    _second_chi2EB[ixtal] = -99;
    _second_jitterEB[ixtal] = -99;
    _second_jitterErrorEB[ixtal] = -99;
    _second_amplitudeErrorEB[ixtal] = -99;
    _second_outOfTimeAmplitudeM1EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM2EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM3EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM4EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM5EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP1EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP2EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP3EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP4EB[ixtal] = -99;  
    _second_flagsEB[ixtal] = -99;
    _second_hashindexEB[ixtal] = -99;
    
  }
  for (int ixtal=0; ixtal < 14648; ixtal++) {
    //---- Fill flag for this crystal
    _onlineEnergyEE[ixtal] = -99;
    _chi2EE[ixtal] = -99;
    _jitterEE[ixtal] = -99;
    _jitterErrorEE[ixtal] = -99;
    _amplitudeErrorEE[ixtal] = -99;
    _outOfTimeAmplitudeM1EE[ixtal] = -99;
    _outOfTimeAmplitudeM2EE[ixtal] = -99;
    _outOfTimeAmplitudeM3EE[ixtal] = -99;
    _outOfTimeAmplitudeM4EE[ixtal] = -99;
    _outOfTimeAmplitudeM5EE[ixtal] = -99;
    _outOfTimeAmplitudeP1EE[ixtal] = -99;
    _outOfTimeAmplitudeP2EE[ixtal] = -99;
    _outOfTimeAmplitudeP3EE[ixtal] = -99;
    _outOfTimeAmplitudeP4EE[ixtal] = -99;
    _flagsEE[ixtal] = -99;
    _hashindexEE[ixtal] = -99;
    
    _second_onlineEnergyEE[ixtal] = -99;
    _second_chi2EE[ixtal] = -99;
    _second_jitterEB[ixtal] = -99;
    _second_jitterErrorEB[ixtal] = -99;
    _second_amplitudeErrorEE[ixtal] = -99;
    _second_outOfTimeAmplitudeM1EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM2EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM3EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM4EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM5EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP1EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP2EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP3EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP4EE[ixtal] = -99;
    _second_flagsEE[ixtal] = -99;
    _second_hashindexEE[ixtal] = -99;
  }
  
  
//   std::cout << " ~~ " << std::endl;
//   std::cout << " > ebrechits->size() = " << ebrechits->size() << std::endl;
//   std::cout << " > eerechits->size() = " << eerechits->size() << std::endl;
//   std::cout << " ~~ " << std::endl;
  
  edm::ESHandle<CaloGeometry> pGeometry;
  iSetup.get<CaloGeometryRecord>().get(pGeometry);
  const CaloGeometry *geometry = pGeometry.product();
  
  
  edm::ESHandle<EcalTrigTowerConstituentsMap> eTTmap;
  iSetup.get<IdealGeometryRecord>().get(eTTmap);
  
  
  _sizeEB = ebrechits->size();
  _sizeEE = eerechits->size();

  

  
//   
//   _second_sizeEB = second_ebrechits->size();
//   _second_sizeEE = second_eerechits->size();
//   
  
//   
//   
//   second_XXX has only:
//   - amplitude 
//   - chi2
//   - did
//   
//   
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = ebrechits->begin(); itrechit != ebrechits->end(); itrechit++ ) {
    _onlineEnergyEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();    
    _chi2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->chi2();    
    _flagsEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->flags();    
    _hashindexEB[EBDetId(itrechit->id()).hashedIndex()] =  EBDetId(itrechit->id()).hashedIndex();    
    _jitterEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->jitter();    
    _jitterErrorEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->jitterError();    
    _amplitudeErrorEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitudeError();    
    _outOfTimeAmplitudeM1EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(4);    
    _outOfTimeAmplitudeM2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(3);    
    _outOfTimeAmplitudeM3EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(2);    
    _outOfTimeAmplitudeM4EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(1);    
    _outOfTimeAmplitudeM5EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(0);    
    _outOfTimeAmplitudeP1EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(6);    
    _outOfTimeAmplitudeP2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(7);    
    _outOfTimeAmplitudeP3EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(8);    
    _outOfTimeAmplitudeP4EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(9);    
  }
  
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = eerechits->begin(); itrechit != eerechits->end(); itrechit++ ) {
    _onlineEnergyEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();
    _chi2EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->chi2();
    _flagsEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->flags();    
    _hashindexEE[EEDetId(itrechit->id()).hashedIndex()] =  EEDetId(itrechit->id()).hashedIndex();    
    _jitterEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->jitter();  
    _jitterErrorEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->jitterError();  
    _amplitudeErrorEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitudeError();
    _outOfTimeAmplitudeM1EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(4);
    _outOfTimeAmplitudeM2EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(3);
    _outOfTimeAmplitudeM3EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(2);
    _outOfTimeAmplitudeM4EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(1);
    _outOfTimeAmplitudeM5EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(0);
    _outOfTimeAmplitudeP1EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(6);
    _outOfTimeAmplitudeP2EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(7);
    _outOfTimeAmplitudeP3EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(8);
    _outOfTimeAmplitudeP4EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(9);
    
//         std::cout << " It is ok : " << EEDetId(itrechit->id()).hashedIndex() << " != " << hashedIndexEE(itrechit->id()) << " TEST "  << std::endl;
//     if ((int) EEDetId(itrechit->id()).hashedIndex() != (int) hashedIndexEE(itrechit->id())) {
//       std::cout << " Problem: " << EEDetId(itrechit->id()).hashedIndex() << " != " << hashedIndexEE(itrechit->id())  << std::endl;
//     }
//     
//     It is ok : 1458 != 1504 TEST 
//     
    
  }

  

  _second_sizeEB = second_ebrechits->amplitude.size();
  _second_sizeEE = second_eerechits->amplitude.size();

  for (int irechit = 0; irechit < _second_sizeEB; irechit++ ) {
    _second_onlineEnergyEB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitude[irechit];    
    _second_jitterEB      [EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->jitter[irechit];    
    _second_jitterErrorEB [EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->jitterError[irechit];    
    _second_chi2EB        [EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->chi2[irechit];     
    _second_flagsEB       [EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->flags[irechit];     
    _second_hashindexEB   [EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  EBDetId(second_ebrechits->did[irechit]).hashedIndex();     
    
    
    
    _second_outOfTimeAmplitudeM5EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 0];    
    _second_outOfTimeAmplitudeM4EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 1];    
    _second_outOfTimeAmplitudeM3EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 2];    
    _second_outOfTimeAmplitudeM2EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 3];    
    _second_outOfTimeAmplitudeM1EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 4];    
//     _NOMINAL[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit](5);                    
    _second_outOfTimeAmplitudeP1EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 6];    
    _second_outOfTimeAmplitudeP2EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 7];    
    _second_outOfTimeAmplitudeP3EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 8];    
    _second_outOfTimeAmplitudeP4EB[EBDetId(second_ebrechits->did[irechit]).hashedIndex()] =  second_ebrechits->amplitudesAll[irechit*10 + 9];   
    
    
    if (fabs(second_ebrechits->amplitudesAll[irechit*10 + 5] - second_ebrechits->amplitude[irechit]) > 0.01) {
      std::cout << " different eb??? all!=single  --> " << second_ebrechits->amplitudesAll[irechit*10 + 5] << " != " << second_ebrechits->amplitude[irechit] << std::endl;
      std::cout << "           hashedIndex = " << EBDetId(second_ebrechits->did[irechit]).hashedIndex() << std::endl;
      std::cout << "                 0 = " << second_ebrechits->amplitudesAll[irechit*10 + 0] << std::endl;
      std::cout << "                 1 = " << second_ebrechits->amplitudesAll[irechit*10 + 1] << std::endl;
      std::cout << "                 2 = " << second_ebrechits->amplitudesAll[irechit*10 + 2] << std::endl;
      std::cout << "                 3 = " << second_ebrechits->amplitudesAll[irechit*10 + 3] << std::endl;
      std::cout << "                 4 = " << second_ebrechits->amplitudesAll[irechit*10 + 4] << std::endl;
      std::cout << "                 5 = " << second_ebrechits->amplitudesAll[irechit*10 + 5] << std::endl;
      std::cout << "                 6 = " << second_ebrechits->amplitudesAll[irechit*10 + 6] << std::endl;
      std::cout << "                 7 = " << second_ebrechits->amplitudesAll[irechit*10 + 7] << std::endl;
      std::cout << "                 8 = " << second_ebrechits->amplitudesAll[irechit*10 + 8] << std::endl;
      std::cout << "                 9 = " << second_ebrechits->amplitudesAll[irechit*10 + 9] << std::endl;
    }
                                                                                                                                          
  }                                                                                                                                       
                                                                                                                                          
  for (int irechit = 0; irechit < _second_sizeEE; irechit++ ) {                                                                           
    _second_onlineEnergyEE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitude[irechit];                
    _second_jitterEE      [EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->jitter[irechit];                   
    _second_jitterErrorEE [EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->jitterError[irechit];              
    _second_chi2EE        [EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->chi2[irechit];                     
    _second_flagsEE       [EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->flags[irechit];     
    _second_hashindexEE   [EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  EEDetId(second_eerechits->did[irechit]).hashedIndex();     
    
    _second_outOfTimeAmplitudeM5EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 0];    
    _second_outOfTimeAmplitudeM4EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 1];    
    _second_outOfTimeAmplitudeM3EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 2];    
    _second_outOfTimeAmplitudeM2EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 3];    
    _second_outOfTimeAmplitudeM1EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 4];    
    //     _NOMINAL[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit](5]);               
    _second_outOfTimeAmplitudeP1EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 6];    
    _second_outOfTimeAmplitudeP2EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 7];    
    _second_outOfTimeAmplitudeP3EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 8];    
    _second_outOfTimeAmplitudeP4EE[EEDetId(second_eerechits->did[irechit]).hashedIndex()] =  second_eerechits->amplitudesAll[irechit*10 + 9];    
    
    if (fabs(second_eerechits->amplitudesAll[irechit*10 + 5] - second_eerechits->amplitude[irechit]) > 0.01) {
      std::cout << " different ee??? all!=single  --> " << second_eerechits->amplitudesAll[irechit*10 + 5] << " != " << second_eerechits->amplitude[irechit] << std::endl;
      std::cout << "           hashedIndex = " << EEDetId(second_eerechits->did[irechit]).hashedIndex() << std::endl;
      std::cout << "                 0 = " << second_eerechits->amplitudesAll[irechit*10 + 0] << std::endl;
      std::cout << "                 1 = " << second_eerechits->amplitudesAll[irechit*10 + 1] << std::endl;
      std::cout << "                 2 = " << second_eerechits->amplitudesAll[irechit*10 + 2] << std::endl;
      std::cout << "                 3 = " << second_eerechits->amplitudesAll[irechit*10 + 3] << std::endl;
      std::cout << "                 4 = " << second_eerechits->amplitudesAll[irechit*10 + 4] << std::endl;
      std::cout << "                 5 = " << second_eerechits->amplitudesAll[irechit*10 + 5] << std::endl;
      std::cout << "                 6 = " << second_eerechits->amplitudesAll[irechit*10 + 6] << std::endl;
      std::cout << "                 7 = " << second_eerechits->amplitudesAll[irechit*10 + 7] << std::endl;
      std::cout << "                 8 = " << second_eerechits->amplitudesAll[irechit*10 + 8] << std::endl;
      std::cout << "                 9 = " << second_eerechits->amplitudesAll[irechit*10 + 9] << std::endl;
    }

    
  }
  
    
  outTree->Fill();
  
  
}




// ------------ method called once each job just before starting event loop  ------------
void 
TreeComparisonProducerNewDataFormat::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeComparisonProducerNewDataFormat::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeComparisonProducerNewDataFormat::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeComparisonProducerNewDataFormat);
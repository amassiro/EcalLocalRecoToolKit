// -*- C++ -*-
//
// Package:    AdvancedMultifitCMSSW/TreeComparisonProducer
// Class:      TreeComparisonProducer
// 
/**\class TreeComparisonProducer TreeComparisonProducer.cc ECALValidation/EcalLocalRecoToolKit/plugins/TreeComparisonProducer.cc
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






#include "TTree.h"




//---- for Zee part
#include "DataFormats/PatCandidates/interface/Electron.h"






//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TreeComparisonProducer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit TreeComparisonProducer(const edm::ParameterSet&);
  ~TreeComparisonProducer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
  
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_ebrechits;
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_eerechits;

  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_second_ebrechits;
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_second_eerechits;
  
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
TreeComparisonProducer::TreeComparisonProducer(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  usesResource("TFileService");
  
  
  //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> fs;
    
  _token_ebrechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalUncalibRecHitsEBCollection"));
  _token_eerechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalUncalibRecHitsEECollection"));

  _token_second_ebrechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("SecondEcalUncalibRecHitsEBCollection"));
  _token_second_eerechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("SecondEcalUncalibRecHitsEECollection"));
  
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
  
}


TreeComparisonProducer::~TreeComparisonProducer()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeComparisonProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
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
  
  edm::Handle<EcalUncalibratedRecHitCollection> second_ebrechithandle;
  const EcalUncalibratedRecHitCollection *second_ebrechits = NULL;
  edm::Handle<EcalUncalibratedRecHitCollection> second_eerechithandle;
  const EcalUncalibratedRecHitCollection *second_eerechits = NULL;
  
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
    _outOfTimeAmplitudeP1EB[ixtal] = -99;
    _outOfTimeAmplitudeP2EB[ixtal] = -99;
    _outOfTimeAmplitudeP3EB[ixtal] = -99;
    _outOfTimeAmplitudeP4EB[ixtal] = -99;
    _outOfTimeAmplitudeM5EB[ixtal] = -99;
    
    _second_onlineEnergyEB[ixtal] = -99;
    _second_chi2EB[ixtal] = -99;
    _second_jitterEB[ixtal] = -99;
    _second_jitterErrorEB[ixtal] = -99;
    _second_amplitudeErrorEB[ixtal] = -99;
    _second_outOfTimeAmplitudeM1EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM2EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM3EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM4EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP1EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP2EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP3EB[ixtal] = -99;
    _second_outOfTimeAmplitudeP4EB[ixtal] = -99;
    _second_outOfTimeAmplitudeM5EB[ixtal] = -99;
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
    _outOfTimeAmplitudeP1EE[ixtal] = -99;
    _outOfTimeAmplitudeP2EE[ixtal] = -99;
    _outOfTimeAmplitudeP3EE[ixtal] = -99;
    _outOfTimeAmplitudeP4EE[ixtal] = -99;
    _outOfTimeAmplitudeM5EE[ixtal] = -99;
    
    _second_onlineEnergyEE[ixtal] = -99;
    _second_chi2EE[ixtal] = -99;
    _second_jitterEB[ixtal] = -99;
    _second_jitterErrorEB[ixtal] = -99;
    _second_amplitudeErrorEE[ixtal] = -99;
    _second_outOfTimeAmplitudeM1EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM2EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM3EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM4EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP1EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP2EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP3EE[ixtal] = -99;
    _second_outOfTimeAmplitudeP4EE[ixtal] = -99;
    _second_outOfTimeAmplitudeM5EE[ixtal] = -99;
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

  _second_sizeEB = second_ebrechits->size();
  _second_sizeEE = second_eerechits->size();
  
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = ebrechits->begin(); itrechit != ebrechits->end(); itrechit++ ) {
    _onlineEnergyEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();    
    _chi2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->chi2();    
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
  }

  
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = second_ebrechits->begin(); itrechit != second_ebrechits->end(); itrechit++ ) {
    _second_onlineEnergyEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();    
    _second_chi2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->chi2();    
    _second_jitterEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->jitter();    
    _second_jitterErrorEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->jitterError();    
    _second_amplitudeErrorEB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitudeError();    
    _second_outOfTimeAmplitudeM1EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(4);    
    _second_outOfTimeAmplitudeM2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(3);    
    _second_outOfTimeAmplitudeM3EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(2);    
    _second_outOfTimeAmplitudeM4EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(1);    
    _second_outOfTimeAmplitudeM5EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(0);    
    _second_outOfTimeAmplitudeP1EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(6);    
    _second_outOfTimeAmplitudeP2EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(7);    
    _second_outOfTimeAmplitudeP3EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(8);    
    _second_outOfTimeAmplitudeP4EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(9);    
  }
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = second_eerechits->begin(); itrechit != second_eerechits->end(); itrechit++ ) {
    _second_onlineEnergyEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();
    _second_chi2EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->chi2();
    _second_jitterEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->jitter();
    _second_jitterErrorEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->jitterError();
    _second_amplitudeErrorEE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitudeError();
    _second_outOfTimeAmplitudeM1EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(4);
    _second_outOfTimeAmplitudeM2EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(3);
    _second_outOfTimeAmplitudeM3EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(2);
    _second_outOfTimeAmplitudeM4EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(1);
    _second_outOfTimeAmplitudeM5EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(0);
    _second_outOfTimeAmplitudeP1EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(6);
    _second_outOfTimeAmplitudeP2EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(7);
    _second_outOfTimeAmplitudeP3EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(8);
    _second_outOfTimeAmplitudeP4EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->outOfTimeAmplitude(9);
  }
  
  outTree->Fill();
  
  
}




// ------------ method called once each job just before starting event loop  ------------
void 
TreeComparisonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeComparisonProducer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeComparisonProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeComparisonProducer);
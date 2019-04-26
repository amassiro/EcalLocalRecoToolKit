import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
#from Configuration.ProcessModifiers.gpu_cff import gpu

process = cms.Process('RECO', eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
#process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('HeterogeneousCore.CUDAServices.CUDAService_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
#process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
#process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
#process.load('DQMOffline.Configuration.DQMOffline_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_HLT_v2', '')


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(4200)
    #input = cms.untracked.int32(10)
)

# load data using the DAQ source
import sys, os, inspect
sys.path.append(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))))
process.load('sourceFromRawCmggpu_cff')

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
#process.load("RecoLocalCalo.Configuration.ecalLocalRecoSequence_cff")
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("EventFilter.EcalRawToDigi.EcalUnpackerData_cfi")
process.load("RecoLuminosity.LumiProducer.bunchSpacingProducer_cfi")

# load gpu plugins
#
# ../cfipython/slc7_amd64_gcc700/RecoLocalCalo/EcalRecProducers/ecalUncalibRecHitProducerGPU_cfi.py
#
process.load("RecoLocalCalo.EcalRecProducers.ecalUncalibRecHitProducerGPU_cfi")
#

process.load("RecoLocalCalo.EcalRecProducers.ecalPedestalsGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalGainRatiosGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalPulseShapesGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalPulseCovariancesGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalSamplesCorrelationGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalTimeBiasCorrectionsGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalTimeCalibConstantsGPUESProducer_cfi")


##    
##    
##    
##    
##    
##    
    
    
    


#process.hcalDigis.silent = cms.untracked.bool(False)
#process.hcalDigis.InputLabel = rawTag
process.ecalDigis = process.ecalEBunpacker.clone()
process.ecalDigis.InputLabel = cms.InputTag('rawDataCollector')
#process.hbheprerecogpu.processQIE11 = cms.bool(True)


process.out = cms.OutputModule("AsciiOutputModule",
    outputCommands = cms.untracked.vstring(
        'keep *_ecalMultiFitUncalibRecHit_*_*', 
    ),
    verbosity = cms.untracked.uint32(0)
)
process.finalize = cms.EndPath(process.out)

process.bunchSpacing = cms.Path(
    process.bunchSpacingProducer
)

process.digiPath = cms.Path(
    #process.hcalDigis
    process.ecalDigis
)

process.recoPath = cms.Path(
#    process.horeco
#    *process.hfprereco
#    *process.hfreco
#    *process.hbheprereco
#    process.ecalMultiFitUncalibRecHit

     process.ecalUncalibRecHitProducerGPU   #  --->     std::string label = "ecalUncalibRecHitProducerGPU";
    
#    *process.ecalRecHit
#    *process.hbheprerecogpu
)

process.schedule = cms.Schedule(
    process.bunchSpacing,
    process.digiPath,
    process.recoPath,
#    process.ecalecalLocalRecoSequence
    process.finalize
)

process.options = cms.untracked.PSet(
    numberOfThreads = cms.untracked.uint32(8),
    numberOfStreams = cms.untracked.uint32(8),
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

# report CUDAService messages
process.MessageLogger.categories.append("CUDAService")

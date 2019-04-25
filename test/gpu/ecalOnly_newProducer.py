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

# load both cpu and gpu plugins
#process.load("RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_gpu_new_cfi")
#process.load("RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_gpu_new_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalUncalibRecHitProducerGPU_cfi")


process.load("RecoLocalCalo.EcalRecProducers.ecalPedestalsGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalGainRatiosGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalPulseShapesGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalPulseCovariancesGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalSamplesCorrelationGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalTimeBiasCorrectionsGPUESProducer_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalTimeCalibConstantsGPUESProducer_cfi")


#process.ecalUncalibRecHitProducerGPU.algoPSet.threads = cms.vint32(256, 1, 1)


##
## force HLT configuration for ecalMultiFitUncalibRecHit
##

#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain61pEB = cms.double( 5.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain61pEB = cms.double( 5.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EBtimeFitParameters = cms.vdouble( -2.015452, 3.130702, -12.3473, 41.88921, -82.83944, 91.01147, -50.35761, 11.05621 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.activeBXs = cms.vint32( -5, -4, -3, -2, -1, 0, 1, 2 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.amplitudeThresholdEE = cms.double( 10.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EBtimeConstantTerm = cms.double( 0.6 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EEtimeFitLimits_Lower = cms.double( 0.2 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain61pEE = cms.double( 1000.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.ebSpikeThreshold = cms.double( 1.042 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EBtimeNconst = cms.double( 28.5 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.ampErrorCalculation = cms.bool( False )   # Important!
#process.ecalUncalibRecHitProducerGPU.algoPSet.kPoorRecoFlagEB = cms.bool( True )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EBtimeFitLimits_Lower = cms.double( 0.2 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.kPoorRecoFlagEE = cms.bool( False )
#process.ecalUncalibRecHitProducerGPU.algoPSet.chi2ThreshEB_ = cms.double( 65.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EEtimeFitParameters = cms.vdouble( -2.390548, 3.553628, -17.62341, 67.67538, -133.213, 140.7432, -75.41106, 16.20277 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.useLumiInfoRunHeader = cms.bool( False )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain12mEE = cms.double( 1000.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain12mEB = cms.double( 5.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EEtimeFitLimits_Upper = cms.double( 1.4 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.prefitMaxChiSqEB = cms.double( 15.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EEamplitudeFitParameters = cms.vdouble( 1.89, 1.4 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.prefitMaxChiSqEE = cms.double( 10.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EBamplitudeFitParameters = cms.vdouble( 1.138, 1.652 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EBtimeFitLimits_Upper = cms.double( 1.4 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.timealgo = cms.string( "None" )
#process.ecalUncalibRecHitProducerGPU.algoPSet.amplitudeThresholdEB = cms.double( 10.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain12pEE = cms.double( 1000.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain12pEB = cms.double( 5.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EEtimeNconst = cms.double( 31.8 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain61mEB = cms.double( 5.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.outOfTimeThresholdGain61mEE = cms.double( 1000.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.EEtimeConstantTerm = cms.double( 1.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.chi2ThreshEE_ = cms.double( 50.0 )
#process.ecalUncalibRecHitProducerGPU.algoPSet.doPrefitEE = cms.bool( True )
#process.ecalUncalibRecHitProducerGPU.algoPSet.doPrefitEB = cms.bool( True )

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
    process.ecalUncalibRecHitProducerGPU
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

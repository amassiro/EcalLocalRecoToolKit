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
    #input = cms.untracked.int32(4200)
    #input = cms.untracked.int32(100)  # ---> very bad!
    #input = cms.untracked.int32(1) #  ---> good???
    input = cms.untracked.int32(2)  #  ---> bad
    #input = cms.untracked.int32(10)
)





# load data using the DAQ source
import sys, os, inspect
sys.path.append(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))))
#process.load('sourceFromRawCmggpu_cff')

#
# Standard course
#

GT = '100X_dataRun2_Prompt_v1'
infile = ["file:/data/patatrack/dalfonso/data/2018/Run2018E_HLTPhysics_325308/FB454F42-97B6-DC4B-88FF-0063C79B9F6C.root"]
rawTag    = cms.InputTag('rawDataCollector')
sourceTag = "PoolSource"         # for global runs

process.source = cms.Source(
    sourceTag,
    fileNames = cms.untracked.vstring(infile)
    )



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


#process.ecalUncalibRecHitProducerGPU.algoPSet.threads = cms.vint32(256, 1, 1)

# load cpu plugins
process.load("RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi")


#
# skip event
#process.source.skipEvents=cms.untracked.uint32(2)   # not doing anything!!!! Due to different "source", HLT version?
#
#


##
## force HLT configuration for ecalMultiFitUncalibRecHit
##

# process.ecalMultiFitUncalibRecHit.algoPSet = cms.PSet( 
# 
#       doPrefitEE = cms.bool( False ),
#       doPrefitEB = cms.bool( False ),
# 
#       EBtimeFitLimits_Upper = cms.double( 1.4 ),
#       EEtimeFitLimits_Upper = cms.double( 1.4 ),
# 
#       EBtimeFitLimits_Lower = cms.double( 0.2 ),
#       EEtimeFitLimits_Lower = cms.double( 0.2 ),
# 
#       EBtimeNconst = cms.double( 28.5 ),
#       EEtimeNconst = cms.double( 31.8 ),
# 
#       ebSpikeThreshold = cms.double( 1.042 ),   # AM: not used anywhere!
#       
#       timealgo = cms.string( "None" ),
#       
#       prefitMaxChiSqEE = cms.double( 10.0 ),
#       prefitMaxChiSqEB = cms.double( 25.0 ),
# 
#       outOfTimeThresholdGain12mEB = cms.double( 5.0 ),
#       outOfTimeThresholdGain12mEE = cms.double( 1000.0 ),
#      
#       outOfTimeThresholdGain12pEB = cms.double( 5.0 ),
#       outOfTimeThresholdGain12pEE = cms.double( 1000.0 ),
# 
#       EEtimeFitParameters = cms.vdouble( -2.390548, 3.553628, -17.62341, 67.67538, -133.213, 140.7432, -75.41106, 16.20277 ),
#       EBtimeFitParameters = cms.vdouble( -2.015452, 3.130702, -12.3473, 41.88921, -82.83944, 91.01147, -50.35761, 11.05621 ),
# 
#       simplifiedNoiseModelForGainSwitch = cms.bool( True ),
#       
#       selectiveBadSampleCriteriaEB = cms.bool( False ),
#       selectiveBadSampleCriteriaEE = cms.bool( False ),
# 
#       dynamicPedestalsEB = cms.bool( False ),
#       dynamicPedestalsEE = cms.bool( False ),
# 
#       useLumiInfoRunHeader = cms.bool( False ),
#       
#       EBamplitudeFitParameters = cms.vdouble( 1.138, 1.652 ),
#       EEamplitudeFitParameters = cms.vdouble( 1.89, 1.4 ),
# 
#       outOfTimeThresholdGain61pEE = cms.double( 1000.0 ),
#       outOfTimeThresholdGain61pEB = cms.double( 5.0 ),
# 
#       activeBXs = cms.vint32( -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 ),
# 
#       addPedestalUncertaintyEE = cms.double( 0.0 ),
#       addPedestalUncertaintyEB = cms.double( 0.0 ),
# 
#       gainSwitchUseMaxSampleEB = cms.bool( True ),
#       gainSwitchUseMaxSampleEE = cms.bool( False ),  # AM TEST   Set to True ---> still bad
# 
#       chi2ThreshEB_ = cms.double( 65.0 ),       # AM: never used in the code???
#       chi2ThreshEE_ = cms.double( 50.0 ),       # AM: never used in the code???
# 
#       eePulseShape = cms.vdouble( 5.2E-5, -5.26E-5, 6.66E-5, 0.1168, 0.7575, 1.0, 0.8876, 0.6732, 0.4741, 0.3194 ),         # AM: never used in the code???
#       ebPulseShape = cms.vdouble( 5.2E-5, -5.26E-5, 6.66E-5, 0.1168, 0.7575, 1.0, 0.8876, 0.6732, 0.4741, 0.3194 ),         # AM: never used in the code???
# 
#       mitigateBadSamplesEB = cms.bool( False ),
#       mitigateBadSamplesEE = cms.bool( False ),
# 
#       amplitudeThresholdEB = cms.double( 10.0 ),      # AM:  used for timing.   Consider flagging as kOutOfTime only if above noise
#       amplitudeThresholdEE = cms.double( 10.0 ),      # AM:  used for timing.   Consider flagging as kOutOfTime only if above noise
# 
#       ampErrorCalculation = cms.bool( False ),
# 
#       kPoorRecoFlagEB = cms.bool( True ),        # AM: never used in the code???
#       kPoorRecoFlagEE = cms.bool( False ),       # AM: never used in the code???
#       
#       outOfTimeThresholdGain61mEB = cms.double( 5.0 ),     # AM: used for timing
#       outOfTimeThresholdGain61mEE = cms.double( 1000.0 ),  # AM: used for timing
#       
#       EBtimeConstantTerm = cms.double( 0.6 ),
#       EEtimeConstantTerm = cms.double( 1.0 ),
#       
#       
#       EcalPulseShapeParameters = cms.PSet( 
#         EEPulseShapeTemplate = cms.vdouble( 0.116442, 0.756246, 1.0, 0.897182, 0.686831, 0.491506, 0.344111, 0.245731, 0.174115, 0.123361, 0.0874288, 0.061957 ),
#         EEdigiCollection = cms.string( "" ),
#         EcalPreMixStage2 = cms.bool( False ),
#         EcalPreMixStage1 = cms.bool( False ),
#         EBPulseShapeCovariance = cms.vdouble( 3.001E-6, 1.233E-5, 0.0, -4.416E-6, -4.571E-6, -3.614E-6, -2.636E-6, -1.286E-6, -8.41E-7, -5.296E-7, 0.0, 0.0, 1.233E-5, 6.154E-5, 0.0, -2.2E-5, -2.309E-5, -1.838E-5, -1.373E-5, -7.334E-6, -5.088E-6, -3.745E-6, -2.428E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -4.416E-6, -2.2E-5, 0.0, 8.319E-6, 8.545E-6, 6.792E-6, 5.059E-6, 2.678E-6, 1.816E-6, 1.223E-6, 8.245E-7, 5.589E-7, -4.571E-6, -2.309E-5, 0.0, 8.545E-6, 9.182E-6, 7.219E-6, 5.388E-6, 2.853E-6, 1.944E-6, 1.324E-6, 9.083E-7, 6.335E-7, -3.614E-6, -1.838E-5, 0.0, 6.792E-6, 7.219E-6, 6.016E-6, 4.437E-6, 2.385E-6, 1.636E-6, 1.118E-6, 7.754E-7, 5.556E-7, -2.636E-6, -1.373E-5, 0.0, 5.059E-6, 5.388E-6, 4.437E-6, 3.602E-6, 1.917E-6, 1.322E-6, 9.079E-7, 6.529E-7, 4.752E-7, -1.286E-6, -7.334E-6, 0.0, 2.678E-6, 2.853E-6, 2.385E-6, 1.917E-6, 1.375E-6, 9.1E-7, 6.455E-7, 4.693E-7, 3.657E-7, -8.41E-7, -5.088E-6, 0.0, 1.816E-6, 1.944E-6, 1.636E-6, 1.322E-6, 9.1E-7, 9.115E-7, 6.062E-7, 4.436E-7, 3.422E-7, -5.296E-7, -3.745E-6, 0.0, 1.223E-6, 1.324E-6, 1.118E-6, 9.079E-7, 6.455E-7, 6.062E-7, 7.217E-7, 4.862E-7, 3.768E-7, 0.0, -2.428E-6, 0.0, 8.245E-7, 9.083E-7, 7.754E-7, 6.529E-7, 4.693E-7, 4.436E-7, 4.862E-7, 6.509E-7, 4.418E-7, 0.0, 0.0, 0.0, 5.589E-7, 6.335E-7, 5.556E-7, 4.752E-7, 3.657E-7, 3.422E-7, 3.768E-7, 4.418E-7, 6.142E-7 ),
#         ESdigiCollection = cms.string( "" ),
#         EBdigiCollection = cms.string( "" ),
#         EBCorrNoiseMatrixG01 = cms.vdouble( 1.0, 0.73354, 0.64442, 0.58851, 0.55425, 0.53082, 0.51916, 0.51097, 0.50732, 0.50409 ),
#         EBCorrNoiseMatrixG12 = cms.vdouble( 1.0, 0.71073, 0.55721, 0.46089, 0.40449, 0.35931, 0.33924, 0.32439, 0.31581, 0.30481 ),
#         EBCorrNoiseMatrixG06 = cms.vdouble( 1.0, 0.70946, 0.58021, 0.49846, 0.45006, 0.41366, 0.39699, 0.38478, 0.37847, 0.37055 ),
#         EEPulseShapeCovariance = cms.vdouble( 3.941E-5, 3.333E-5, 0.0, -1.449E-5, -1.661E-5, -1.424E-5, -1.183E-5, -6.842E-6, -4.915E-6, -3.411E-6, 0.0, 0.0, 3.333E-5, 2.862E-5, 0.0, -1.244E-5, -1.431E-5, -1.233E-5, -1.032E-5, -5.883E-6, -4.154E-6, -2.902E-6, -2.128E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.449E-5, -1.244E-5, 0.0, 5.84E-6, 6.649E-6, 5.72E-6, 4.812E-6, 2.708E-6, 1.869E-6, 1.33E-6, 9.186E-7, 6.446E-7, -1.661E-5, -1.431E-5, 0.0, 6.649E-6, 7.966E-6, 6.898E-6, 5.794E-6, 3.157E-6, 2.184E-6, 1.567E-6, 1.084E-6, 7.575E-7, -1.424E-5, -1.233E-5, 0.0, 5.72E-6, 6.898E-6, 6.341E-6, 5.347E-6, 2.859E-6, 1.991E-6, 1.431E-6, 9.839E-7, 6.886E-7, -1.183E-5, -1.032E-5, 0.0, 4.812E-6, 5.794E-6, 5.347E-6, 4.854E-6, 2.628E-6, 1.809E-6, 1.289E-6, 9.02E-7, 6.146E-7, -6.842E-6, -5.883E-6, 0.0, 2.708E-6, 3.157E-6, 2.859E-6, 2.628E-6, 1.863E-6, 1.296E-6, 8.882E-7, 6.108E-7, 4.283E-7, -4.915E-6, -4.154E-6, 0.0, 1.869E-6, 2.184E-6, 1.991E-6, 1.809E-6, 1.296E-6, 1.217E-6, 8.669E-7, 5.751E-7, 3.882E-7, -3.411E-6, -2.902E-6, 0.0, 1.33E-6, 1.567E-6, 1.431E-6, 1.289E-6, 8.882E-7, 8.669E-7, 9.522E-7, 6.717E-7, 4.293E-7, 0.0, -2.128E-6, 0.0, 9.186E-7, 1.084E-6, 9.839E-7, 9.02E-7, 6.108E-7, 5.751E-7, 6.717E-7, 7.911E-7, 5.493E-7, 0.0, 0.0, 0.0, 6.446E-7, 7.575E-7, 6.886E-7, 6.146E-7, 4.283E-7, 3.882E-7, 4.293E-7, 5.493E-7, 7.027E-7 ),
#         EBPulseShapeTemplate = cms.vdouble( 0.0113979, 0.758151, 1.0, 0.887744, 0.673548, 0.474332, 0.319561, 0.215144, 0.147464, 0.101087, 0.0693181, 0.0475044 ),
#         EECorrNoiseMatrixG01 = cms.vdouble( 1.0, 0.72698, 0.62048, 0.55691, 0.51848, 0.49147, 0.47813, 0.47007, 0.46621, 0.46265 ),
#         EECorrNoiseMatrixG12 = cms.vdouble( 1.0, 0.71373, 0.44825, 0.30152, 0.21609, 0.14786, 0.11772, 0.10165, 0.09465, 0.08098 ),
#         UseLCcorrection = cms.untracked.bool( True ),
#         EECorrNoiseMatrixG06 = cms.vdouble( 1.0, 0.71217, 0.47464, 0.34056, 0.26282, 0.20287, 0.17734, 0.16256, 0.15618, 0.14443 )
#       )
#             
# )     
      
##    
    
  
    
    


#process.hcalDigis.silent = cms.untracked.bool(False)
#process.hcalDigis.InputLabel = rawTag
process.ecalDigis = process.ecalEBunpacker.clone()
process.ecalDigis.InputLabel = cms.InputTag('rawDataCollector')
#process.hbheprerecogpu.processQIE11 = cms.bool(True)



process.outRoot = cms.OutputModule(
        "PoolOutputModule",
        fileName = cms.untracked.string("test.root")
)

process.out = cms.OutputModule("AsciiOutputModule",
    outputCommands = cms.untracked.vstring(
        'keep *_ecalMultiFitUncalibRecHit_*_*', 
    ),
    verbosity = cms.untracked.uint32(0)
)
process.finalize = cms.EndPath(process.out * process.outRoot)

process.bunchSpacing = cms.Path(
    process.bunchSpacingProducer
)

process.digiPath = cms.Path(
    #process.hcalDigis
    process.ecalDigis
)

process.recoPath = cms.Path(

    process.ecalMultiFitUncalibRecHit
    *process.ecalUncalibRecHitProducerGPU   #  --->     std::string label = "ecalUncalibRecHitProducerGPU";

)



# ----------------------------------
# ---- run the dumper for ECAL
# ----------------------------------

import FWCore.ParameterSet.VarParsing as VarParsing

options = VarParsing.VarParsing('analysis')



process.TFileService = cms.Service("TFileService",
     fileName = cms.string(options.outputFile)
)

#
# NB: new ECAL uncalibrated rechit format!
#

process.TreeComparisonProducer = cms.EDAnalyzer('TreeComparisonProducerNewDataFormat',
                           EcalUncalibRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
                           EcalUncalibRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),

                           SecondEcalUncalibRecHitsEBCollection = cms.InputTag("ecalUncalibRecHitProducerGPU","EcalUncalibRecHitsEB"),
                           SecondEcalUncalibRecHitsEECollection = cms.InputTag("ecalUncalibRecHitProducerGPU","EcalUncalibRecHitsEE"),

                           #SecondEcalUncalibRecHitsEBCollection = cms.InputTag("ecalUncalibRecHitProducerGPU","EcalUncalibRecHitsEBgpunew"),
                           #SecondEcalUncalibRecHitsEECollection = cms.InputTag("ecalUncalibRecHitProducerGPU","EcalUncalibRecHitsEEgpunew"),
                           )

process.TreeComparisonProducer_step = cms.Path(process.TreeComparisonProducer)








process.schedule = cms.Schedule(
    process.bunchSpacing,
    process.digiPath,
    process.recoPath,
#    process.ecalecalLocalRecoSequence
    process.TreeComparisonProducer_step,
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

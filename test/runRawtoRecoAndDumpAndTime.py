# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --mc --eventcontent AODSIM --runUnscheduled --datatier AODSIM --conditions 92X_upgrade2017_realistic_v10 --step RAW2DIGI,RECO,EI --nThreads 4 --era Run2_2017 --fileout file:step1.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

#process = cms.Process('RECO',eras.Run2_2017)
#process = cms.Process('RECOMIO',eras.Run2_2017)
process = cms.Process('RECOMIO',eras.Run2_2018)



from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()




# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('CommonTools.ParticleFlow.EITopPAG_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(5)
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles),
    secondaryFileNames = cms.untracked.vstring(),
    # suggested by CMSSW for form EMTF errors
    inputCommands = cms.untracked.vstring (
                                           "keep *",
                                           "drop l1tEMTFHitExtras_simEmtfDigis_CSC_HLT",
                                           "drop l1tEMTFHitExtras_simEmtfDigis_RPC_HLT",
                                           "drop l1tEMTFTrackExtras_simEmtfDigis__HLT",
                                           )
                                           
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag

process.GlobalTag = GlobalTag(process.GlobalTag, '103X_upgrade2018_realistic_v2', '')




# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)


process.TFileService = cms.Service("TFileService",
     fileName = cms.string(options.outputFile)
)


process.TreeProducer = cms.EDAnalyzer('TreeProducer',

                           EcalUncalibRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
                           EcalUncalibRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),
                           
                           )


process.TreeProducer_step = cms.Path(process.TreeProducer)


#
# mah ...
process.options.SkipEvent = cms.untracked.vstring('ProductNotFound')
#
#




# Schedule definition
process.schedule = cms.Schedule(
          process.raw2digi_step,
          process.reconstruction_step,
          process.TreeProducer_step
          )
                                
                                
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(4)
process.options.numberOfStreams=cms.untracked.uint32(0)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion









############################################################################################
## FastTimerServiceClient                                                                                                                                                                                          
#process.fastTimerServiceClient = cms.EDProducer( "FastTimerServiceClient",
    #dqmPath = cms.untracked.string( "HLT/TimerService" )
#)

## DQM file saver                                                                                                                                                                                                  
#process.dqmFileSaver = cms.EDAnalyzer( "DQMFileSaver",
    #convention        = cms.untracked.string( "Offline" ),
    #workflow          = cms.untracked.string( "/HLT/FastTimerService/All" ),
    #dirName           = cms.untracked.string( "." ),
    #saveByRun         = cms.untracked.int32(1),
    #saveByLumiSection = cms.untracked.int32(-1),
    #saveByEvent       = cms.untracked.int32(-1),
    #saveByTime        = cms.untracked.int32(-1),
    #saveByMinute      = cms.untracked.int32(-1),
    #saveAtJobEnd      = cms.untracked.bool(False),
    #forceRunNumber    = cms.untracked.int32(-1),
#)

#process.TimingOutput = cms.EndPath( process.fastTimerServiceClient + process.dqmFileSaver )

## remove any instance of the FastTimerService
#if 'FastTimerService' in process.__dict__:
    #del process.FastTimerService

## instrument the menu with the FastTimerService
#process.load( "HLTrigger.Timer.FastTimerService_cfi" )

## print a text summary at the end of the job
#process.FastTimerService.printEventSummary        = False
#process.FastTimerService.printRunSummary          = False
#process.FastTimerService.printJobSummary          = True

## enable DQM plots
#process.FastTimerService.enableDQM                = True

## enable per-path DQM plots (starting with CMSSW 9.2.3-patch2)
#process.FastTimerService.enableDQMbyPath          = True

## enable per-module DQM plots
#process.FastTimerService.enableDQMbyModule        = True

## enable DQM plots vs lumisection
#process.FastTimerService.enableDQMbyLumiSection   = True
#process.FastTimerService.dqmLumiSectionsRange     = 2500    # lumisections (23.31 s)

## set the time resolution of the DQM plots
#process.FastTimerService.dqmTimeRange             = 1000.   # ms
#process.FastTimerService.dqmTimeResolution        =    5.   # ms
#process.FastTimerService.dqmPathTimeRange         =  100.   # ms
#process.FastTimerService.dqmPathTimeResolution    =    0.5  # ms
#process.FastTimerService.dqmModuleTimeRange       =   40.   # ms
#process.FastTimerService.dqmModuleTimeResolution  =    0.2  # ms

## set the base DQM folder for the plots
#process.FastTimerService.dqmPath                  = "HLT/TimerService"
#process.FastTimerService.enableDQMbyProcesses     = False

## save the DQM plots in the DQMIO format
#process.dqmOutput = cms.OutputModule("DQMRootOutputModule",
    #fileName = cms.untracked.string("DQM.root")
#)
#process.FastTimerOutput = cms.EndPath( process.dqmOutput )


process.Timing = cms.Service("Timing",
  summaryOnly = cms.untracked.bool(False),
  useJobReport = cms.untracked.bool(True)
)


############################################################################################



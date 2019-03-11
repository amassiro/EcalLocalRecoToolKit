import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
from Configuration.StandardSequences.Eras import eras
import os

#---------------
# My definitions
#---------------

sourceTag = "PoolSource"         # for global runs
rawTag    = cms.InputTag('source')
era       = eras.Run2_2018
GT        = ""
infile    = ""


options = VarParsing.VarParsing('analysis')
options.register('inputType',
                 'localRun',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "input type")

options.register('year',
                 2018,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "year")

options.parseArguments()

GT = '100X_dataRun2_Prompt_v1'
#infile = ["file:/data/patatrack/vkhriste/data/ecal/result_2018.root"]
infile = ["file:/data/patatrack/vkhriste/cmssw_releases/CMSSW_10_5_0_pre2/src/test.root"]
      
       






#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('MyDump',era)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = GT


process.load('Configuration.StandardSequences.GeometryRecoDB_cff')


#-----------
# Log output
#-----------
process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cout.threshold = "DEBUG"
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger.debugModules = cms.untracked.vstring("*")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )


#-----------------
# Files to process
#-----------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

process.source = cms.Source(
    sourceTag,
    fileNames = cms.untracked.vstring(infile)
    )
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('293765:264-293765:9999')



process.Out = cms.OutputModule(
        "PoolOutputModule",
        fileName = cms.untracked.string("test.root")
)

# ----------------------------------
# ---- run the dumper for ECAL
# ----------------------------------


process.TFileService = cms.Service("TFileService",
     fileName = cms.string(options.outputFile)
)



#
# standard format dataformats
#

#process.TreeComparisonProducer = cms.EDAnalyzer('TreeComparisonProducer',
                           #EcalUncalibRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
                           #EcalUncalibRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),

                           #SecondEcalUncalibRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHitgpu","EcalUncalibRecHitsEBgpunew"),
                           #SecondEcalUncalibRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHitgpu","EcalUncalibRecHitsEEgpunew"),
                           #)


#
# new format dataformats
#


process.TreeComparisonProducer = cms.EDAnalyzer('TreeComparisonProducerNewDataFormat',
                           EcalUncalibRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEB"),
                           EcalUncalibRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHit","EcalUncalibRecHitsEE"),

                           SecondEcalUncalibRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHitgpu","EcalUncalibRecHitsEBgpunew"),
                           SecondEcalUncalibRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHitgpu","EcalUncalibRecHitsEEgpunew"),
                           )

process.TreeComparisonProducer_step = cms.Path(process.TreeComparisonProducer)



process.schedule = cms.Schedule(
    process.TreeComparisonProducer_step
    )




process.options = cms.untracked.PSet(
    numberOfThreads = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(1),
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

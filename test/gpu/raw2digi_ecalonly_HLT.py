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

print "YEAR = ", options.year, " TYPE = ", options.inputType


if options.year == 2017:
    era = eras.Run2_2017
    if options.inputType == 'localRun':
        sourceTag = 'HcalTBSource'
        GT = "100X_dataRun2_Prompt_v1"   #use 2017 GT on 2017 local run
        infile = 'file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run304423/USC_304423.root'

    if options.inputType == 'MC':
        GT = '100X_mc2017_realistic_v1'  #use 2017 GT on 2017 MC
        infile = '/store/relval/CMSSW_10_0_0_pre3/RelValTTbar_13/GEN-SIM-DIGI-RAW/PU25ns_100X_mc2017_realistic_v1_mahiOFF-v1/20000/861B2C97-E6E8-E711-AD66-0CC47A4D7678.root'
        rawTag    = cms.InputTag('rawDataCollector')

    if options.inputType == 'globalRun':
        GT = '100X_dataRun2_Prompt_v1'
        infile = ["file:/data/patatrack/vkhriste/data/test_hcal_numEvent100.root"]
        s = """
        infile = [
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/08CF8873-F6B0-E711-ADC5-02163E011B75.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/0C2A0D6D-F6B0-E711-BE46-02163E01A400.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/1A3BE91F-F8B0-E711-A5CE-02163E0123C7.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/1A888D27-FAB0-E711-80C5-02163E014258.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/40448627-F7B0-E711-9501-02163E01372E.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/425EAEB1-FBB0-E711-B1E8-02163E011C08.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/4882F1A8-FBB0-E711-9D79-02163E019BB5.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/52B35364-F8B0-E711-A85F-02163E01425A.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/5C4C68A3-F7B0-E711-AF88-02163E013449.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/606FFE9E-F8B0-E711-A4E9-02163E013775.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/62AF9978-F6B0-E711-8871-02163E01A702.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/668E023D-FAB0-E711-8C7F-02163E011CB2.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/68891FAE-F6B0-E711-8E20-02163E01255C.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/6AF5AA64-F6B0-E711-9CB8-02163E01A3B4.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/78093231-F9B0-E711-AC48-02163E011D08.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/84BCD7C6-F9B0-E711-A719-02163E0140F7.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/8EDC3131-F7B0-E711-A8C9-02163E013903.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/961501ED-F8B0-E711-8F0C-02163E019CB8.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/9A41620E-FBB0-E711-8BA8-02163E011E3E.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/A05FF35A-F9B0-E711-B053-02163E011AB9.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/A83D9F06-F8B0-E711-8F32-02163E01454C.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/B64D5C42-FAB0-E711-924B-02163E014303.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/CC634F7B-F7B0-E711-AD5E-02163E014542.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/CCD7BC80-F7B0-E711-B9B9-02163E01A560.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/DCE5F59C-F7B0-E711-9F4C-02163E01A696.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/EC0F00E5-F7B0-E711-9E90-02163E0144E3.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/EC152EA5-F9B0-E711-BC08-02163E01A629.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/ECB0A7A3-FAB0-E711-B041-02163E01420B.root',
        '/store/data/Run2017F/ZeroBias/RAW/v1/000/305/064/00000/ECB74FD1-FAB0-E711-97FA-02163E014280.root']
        """
        rawTag    = cms.InputTag('rawDataCollector')


if options.year == 2018:
    if options.inputType == 'localRun':
        sourceTag = 'HcalTBSource'
        GT = "100X_dataRun2_Prompt_v1"   #use 2017 GT on 2018 local run
        infile = 'file:/eos/cms/store/group/dpg_hcal/comm_hcal/USC/run308144/USC_308144.root'

    if options.inputType == 'MC':
        GT = '100X_mc2017_realistic_v1'  #use 2017 GT on 2018 MC
        infile = '/store/relval/CMSSW_10_0_0_pre3/RelValTTbar_13/GEN-SIM-DIGI-RAW/PU25ns_100X_upgrade2018_realistic_v4_mahiOFF-v1/20000/2C0ABBA4-87E9-E711-B3FB-0025905A60BC.root'
        rawTag    = cms.InputTag('rawDataCollector')
    
    if options.inputType == "globalRun":
        GT = '100X_dataRun2_Prompt_v1'
        infile = ["file:/data/patatrack/dalfonso/data/2018/Run2018E_HLTPhysics_325308/FB454F42-97B6-DC4B-88FF-0063C79B9F6C.root"]
        rawTag    = cms.InputTag('rawDataCollector')



#-----------------------------------
# Standard CMSSW Imports/Definitions
#-----------------------------------
process = cms.Process('MyReco',era)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = GT


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
    input = cms.untracked.int32(100)
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
process.load("RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_gpu_new_cfi")
process.load("RecoLocalCalo.EcalRecProducers.ecalMultiFitUncalibRecHit_cfi")

#process.ecalMultiFitUncalibRecHitgpu.algoPSet.threads = cms.vint32(256, 1, 1)


##
## force HLT configuration for ecalMultiFitUncalibRecHit
##

process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain61pEB = cms.double( 5.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain61pEB = cms.double( 5.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EBtimeFitParameters = cms.vdouble( -2.015452, 3.130702, -12.3473, 41.88921, -82.83944, 91.01147, -50.35761, 11.05621 )
process.ecalMultiFitUncalibRecHit.algoPSet.activeBXs = cms.vint32( -5, -4, -3, -2, -1, 0, 1, 2 )
process.ecalMultiFitUncalibRecHit.algoPSet.amplitudeThresholdEE = cms.double( 10.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EBtimeConstantTerm = cms.double( 0.6 )
process.ecalMultiFitUncalibRecHit.algoPSet.EEtimeFitLimits_Lower = cms.double( 0.2 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain61pEE = cms.double( 1000.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.ebSpikeThreshold = cms.double( 1.042 )
process.ecalMultiFitUncalibRecHit.algoPSet.EBtimeNconst = cms.double( 28.5 )
process.ecalMultiFitUncalibRecHit.algoPSet.ampErrorCalculation = cms.bool( False )   # Important!
process.ecalMultiFitUncalibRecHit.algoPSet.kPoorRecoFlagEB = cms.bool( True )
process.ecalMultiFitUncalibRecHit.algoPSet.EBtimeFitLimits_Lower = cms.double( 0.2 )
process.ecalMultiFitUncalibRecHit.algoPSet.kPoorRecoFlagEE = cms.bool( False )
process.ecalMultiFitUncalibRecHit.algoPSet.chi2ThreshEB_ = cms.double( 65.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EEtimeFitParameters = cms.vdouble( -2.390548, 3.553628, -17.62341, 67.67538, -133.213, 140.7432, -75.41106, 16.20277 )
process.ecalMultiFitUncalibRecHit.algoPSet.useLumiInfoRunHeader = cms.bool( False )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain12mEE = cms.double( 1000.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain12mEB = cms.double( 5.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EEtimeFitLimits_Upper = cms.double( 1.4 )
process.ecalMultiFitUncalibRecHit.algoPSet.prefitMaxChiSqEB = cms.double( 15.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EEamplitudeFitParameters = cms.vdouble( 1.89, 1.4 )
process.ecalMultiFitUncalibRecHit.algoPSet.prefitMaxChiSqEE = cms.double( 10.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EBamplitudeFitParameters = cms.vdouble( 1.138, 1.652 )
process.ecalMultiFitUncalibRecHit.algoPSet.EBtimeFitLimits_Upper = cms.double( 1.4 )
process.ecalMultiFitUncalibRecHit.algoPSet.timealgo = cms.string( "None" )
process.ecalMultiFitUncalibRecHit.algoPSet.amplitudeThresholdEB = cms.double( 10.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain12pEE = cms.double( 1000.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain12pEB = cms.double( 5.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EEtimeNconst = cms.double( 31.8 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain61mEB = cms.double( 5.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.outOfTimeThresholdGain61mEE = cms.double( 1000.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.EEtimeConstantTerm = cms.double( 1.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.chi2ThreshEE_ = cms.double( 50.0 )
process.ecalMultiFitUncalibRecHit.algoPSet.doPrefitEE = cms.bool( True )
process.ecalMultiFitUncalibRecHit.algoPSet.doPrefitEB = cms.bool( True )

##    
    
    
    


#process.hcalDigis.silent = cms.untracked.bool(False)
#process.hcalDigis.InputLabel = rawTag
process.ecalDigis = process.ecalEBunpacker.clone()
process.ecalDigis.InputLabel = rawTag
#process.hbheprerecogpu.processQIE11 = cms.bool(True)

process.finalize = cms.EndPath(process.Out)

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
    process.ecalMultiFitUncalibRecHit
    *process.ecalMultiFitUncalibRecHitgpu
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

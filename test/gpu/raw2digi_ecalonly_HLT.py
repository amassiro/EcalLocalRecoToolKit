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

process.ecalMultiFitUncalibRecHit.algoPSet = cms.PSet( 
      ebSpikeThreshold = cms.double( 1.042 ),
      EBtimeFitLimits_Upper = cms.double( 1.4 ),
      EEtimeFitLimits_Lower = cms.double( 0.2 ),
      timealgo = cms.string( "None" ),
      EBtimeNconst = cms.double( 28.5 ),
      prefitMaxChiSqEE = cms.double( 10.0 ),
      outOfTimeThresholdGain12mEB = cms.double( 5.0 ),
      outOfTimeThresholdGain12mEE = cms.double( 1000.0 ),
      EEtimeFitParameters = cms.vdouble( -2.390548, 3.553628, -17.62341, 67.67538, -133.213, 140.7432, -75.41106, 16.20277 ),
      prefitMaxChiSqEB = cms.double( 25.0 ),
      simplifiedNoiseModelForGainSwitch = cms.bool( True ),
      EBtimeFitParameters = cms.vdouble( -2.015452, 3.130702, -12.3473, 41.88921, -82.83944, 91.01147, -50.35761, 11.05621 ),
      selectiveBadSampleCriteriaEB = cms.bool( False ),
      dynamicPedestalsEB = cms.bool( False ),
      useLumiInfoRunHeader = cms.bool( False ),
      EBamplitudeFitParameters = cms.vdouble( 1.138, 1.652 ),
      doPrefitEE = cms.bool( False ),
      dynamicPedestalsEE = cms.bool( False ),
      selectiveBadSampleCriteriaEE = cms.bool( False ),
      outOfTimeThresholdGain61pEE = cms.double( 1000.0 ),
      outOfTimeThresholdGain61pEB = cms.double( 5.0 ),
      activeBXs = cms.vint32( -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 ),
      EcalPulseShapeParameters = cms.PSet( 
        EEPulseShapeTemplate = cms.vdouble( 0.116442, 0.756246, 1.0, 0.897182, 0.686831, 0.491506, 0.344111, 0.245731, 0.174115, 0.123361, 0.0874288, 0.061957 ),
        EEdigiCollection = cms.string( "" ),
        EcalPreMixStage2 = cms.bool( False ),
        EcalPreMixStage1 = cms.bool( False ),
        EBPulseShapeCovariance = cms.vdouble( 3.001E-6, 1.233E-5, 0.0, -4.416E-6, -4.571E-6, -3.614E-6, -2.636E-6, -1.286E-6, -8.41E-7, -5.296E-7, 0.0, 0.0, 1.233E-5, 6.154E-5, 0.0, -2.2E-5, -2.309E-5, -1.838E-5, -1.373E-5, -7.334E-6, -5.088E-6, -3.745E-6, -2.428E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -4.416E-6, -2.2E-5, 0.0, 8.319E-6, 8.545E-6, 6.792E-6, 5.059E-6, 2.678E-6, 1.816E-6, 1.223E-6, 8.245E-7, 5.589E-7, -4.571E-6, -2.309E-5, 0.0, 8.545E-6, 9.182E-6, 7.219E-6, 5.388E-6, 2.853E-6, 1.944E-6, 1.324E-6, 9.083E-7, 6.335E-7, -3.614E-6, -1.838E-5, 0.0, 6.792E-6, 7.219E-6, 6.016E-6, 4.437E-6, 2.385E-6, 1.636E-6, 1.118E-6, 7.754E-7, 5.556E-7, -2.636E-6, -1.373E-5, 0.0, 5.059E-6, 5.388E-6, 4.437E-6, 3.602E-6, 1.917E-6, 1.322E-6, 9.079E-7, 6.529E-7, 4.752E-7, -1.286E-6, -7.334E-6, 0.0, 2.678E-6, 2.853E-6, 2.385E-6, 1.917E-6, 1.375E-6, 9.1E-7, 6.455E-7, 4.693E-7, 3.657E-7, -8.41E-7, -5.088E-6, 0.0, 1.816E-6, 1.944E-6, 1.636E-6, 1.322E-6, 9.1E-7, 9.115E-7, 6.062E-7, 4.436E-7, 3.422E-7, -5.296E-7, -3.745E-6, 0.0, 1.223E-6, 1.324E-6, 1.118E-6, 9.079E-7, 6.455E-7, 6.062E-7, 7.217E-7, 4.862E-7, 3.768E-7, 0.0, -2.428E-6, 0.0, 8.245E-7, 9.083E-7, 7.754E-7, 6.529E-7, 4.693E-7, 4.436E-7, 4.862E-7, 6.509E-7, 4.418E-7, 0.0, 0.0, 0.0, 5.589E-7, 6.335E-7, 5.556E-7, 4.752E-7, 3.657E-7, 3.422E-7, 3.768E-7, 4.418E-7, 6.142E-7 ),
        ESdigiCollection = cms.string( "" ),
        EBdigiCollection = cms.string( "" ),
        EBCorrNoiseMatrixG01 = cms.vdouble( 1.0, 0.73354, 0.64442, 0.58851, 0.55425, 0.53082, 0.51916, 0.51097, 0.50732, 0.50409 ),
        EBCorrNoiseMatrixG12 = cms.vdouble( 1.0, 0.71073, 0.55721, 0.46089, 0.40449, 0.35931, 0.33924, 0.32439, 0.31581, 0.30481 ),
        EBCorrNoiseMatrixG06 = cms.vdouble( 1.0, 0.70946, 0.58021, 0.49846, 0.45006, 0.41366, 0.39699, 0.38478, 0.37847, 0.37055 ),
        EEPulseShapeCovariance = cms.vdouble( 3.941E-5, 3.333E-5, 0.0, -1.449E-5, -1.661E-5, -1.424E-5, -1.183E-5, -6.842E-6, -4.915E-6, -3.411E-6, 0.0, 0.0, 3.333E-5, 2.862E-5, 0.0, -1.244E-5, -1.431E-5, -1.233E-5, -1.032E-5, -5.883E-6, -4.154E-6, -2.902E-6, -2.128E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.449E-5, -1.244E-5, 0.0, 5.84E-6, 6.649E-6, 5.72E-6, 4.812E-6, 2.708E-6, 1.869E-6, 1.33E-6, 9.186E-7, 6.446E-7, -1.661E-5, -1.431E-5, 0.0, 6.649E-6, 7.966E-6, 6.898E-6, 5.794E-6, 3.157E-6, 2.184E-6, 1.567E-6, 1.084E-6, 7.575E-7, -1.424E-5, -1.233E-5, 0.0, 5.72E-6, 6.898E-6, 6.341E-6, 5.347E-6, 2.859E-6, 1.991E-6, 1.431E-6, 9.839E-7, 6.886E-7, -1.183E-5, -1.032E-5, 0.0, 4.812E-6, 5.794E-6, 5.347E-6, 4.854E-6, 2.628E-6, 1.809E-6, 1.289E-6, 9.02E-7, 6.146E-7, -6.842E-6, -5.883E-6, 0.0, 2.708E-6, 3.157E-6, 2.859E-6, 2.628E-6, 1.863E-6, 1.296E-6, 8.882E-7, 6.108E-7, 4.283E-7, -4.915E-6, -4.154E-6, 0.0, 1.869E-6, 2.184E-6, 1.991E-6, 1.809E-6, 1.296E-6, 1.217E-6, 8.669E-7, 5.751E-7, 3.882E-7, -3.411E-6, -2.902E-6, 0.0, 1.33E-6, 1.567E-6, 1.431E-6, 1.289E-6, 8.882E-7, 8.669E-7, 9.522E-7, 6.717E-7, 4.293E-7, 0.0, -2.128E-6, 0.0, 9.186E-7, 1.084E-6, 9.839E-7, 9.02E-7, 6.108E-7, 5.751E-7, 6.717E-7, 7.911E-7, 5.493E-7, 0.0, 0.0, 0.0, 6.446E-7, 7.575E-7, 6.886E-7, 6.146E-7, 4.283E-7, 3.882E-7, 4.293E-7, 5.493E-7, 7.027E-7 ),
        EBPulseShapeTemplate = cms.vdouble( 0.0113979, 0.758151, 1.0, 0.887744, 0.673548, 0.474332, 0.319561, 0.215144, 0.147464, 0.101087, 0.0693181, 0.0475044 ),
        EECorrNoiseMatrixG01 = cms.vdouble( 1.0, 0.72698, 0.62048, 0.55691, 0.51848, 0.49147, 0.47813, 0.47007, 0.46621, 0.46265 ),
        EECorrNoiseMatrixG12 = cms.vdouble( 1.0, 0.71373, 0.44825, 0.30152, 0.21609, 0.14786, 0.11772, 0.10165, 0.09465, 0.08098 ),
        UseLCcorrection = cms.untracked.bool( True ),
        EECorrNoiseMatrixG06 = cms.vdouble( 1.0, 0.71217, 0.47464, 0.34056, 0.26282, 0.20287, 0.17734, 0.16256, 0.15618, 0.14443 )
      ),
      doPrefitEB = cms.bool( False ),
      addPedestalUncertaintyEE = cms.double( 0.0 ),
      addPedestalUncertaintyEB = cms.double( 0.0 ),
      gainSwitchUseMaxSampleEB = cms.bool( True ),
      EEtimeNconst = cms.double( 31.8 ),
      EEamplitudeFitParameters = cms.vdouble( 1.89, 1.4 ),
      chi2ThreshEE_ = cms.double( 50.0 ),
      eePulseShape = cms.vdouble( 5.2E-5, -5.26E-5, 6.66E-5, 0.1168, 0.7575, 1.0, 0.8876, 0.6732, 0.4741, 0.3194 ),
      outOfTimeThresholdGain12pEB = cms.double( 5.0 ),
      gainSwitchUseMaxSampleEE = cms.bool( False ),
      mitigateBadSamplesEB = cms.bool( False ),
      outOfTimeThresholdGain12pEE = cms.double( 1000.0 ),
      ebPulseShape = cms.vdouble( 5.2E-5, -5.26E-5, 6.66E-5, 0.1168, 0.7575, 1.0, 0.8876, 0.6732, 0.4741, 0.3194 ),
      ampErrorCalculation = cms.bool( False ),
      mitigateBadSamplesEE = cms.bool( False ),
      amplitudeThresholdEB = cms.double( 10.0 ),
      kPoorRecoFlagEB = cms.bool( True ),
      amplitudeThresholdEE = cms.double( 10.0 ),
      EBtimeFitLimits_Lower = cms.double( 0.2 ),
      kPoorRecoFlagEE = cms.bool( False ),
      EEtimeFitLimits_Upper = cms.double( 1.4 ),
      outOfTimeThresholdGain61mEE = cms.double( 1000.0 ),
      EEtimeConstantTerm = cms.double( 1.0 ),
      EBtimeConstantTerm = cms.double( 0.6 ),
      chi2ThreshEB_ = cms.double( 65.0 ),
      outOfTimeThresholdGain61mEB = cms.double( 5.0 )
)     
      
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

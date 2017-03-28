#import FWCore.ParameterSet.VarParsing as VarParsing
#import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
process = cms.Process("RelValTauL1")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_v20'
# process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'

#### plugin 
process.load('TauTurnOnRelVal.TauTurnOnRelVal.MCanalysis_cff')
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/90X_upgrade2017_realistic_v20-v1/00000/580B472C-CC0F-E711-8393-0CC47A7C357E.root',
        # '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/90X_upgrade2017_realistic_v20-v1/00000/2C3ED96A-CC0F-E711-B53D-0CC47A7C360E.root',
        # '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/90X_upgrade2017_realistic_v20-v1/00000/344E9376-CB0F-E711-8AF8-0025905A48E4.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/FEBC4F3B-8E98-E611-881F-0CC47A4D766C.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/4CB37ED1-8E98-E611-B36C-0CC47A7452DA.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/3C932A4B-8F98-E611-814E-0CC47A4D76B6.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/24D05AE6-8F98-E611-9F9A-0025905A60D2.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/400FA080-9198-E611-B675-0CC47A7AB7A0.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/F8FCC5DC-9198-E611-B84A-0CC47A4D768E.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/CC7D9CED-A098-E611-8F1B-0025905A608E.root',
      '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/1E8C2AEB-A098-E611-A0CC-0CC47A4C8F08.root',
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)


#print particles gen level - DEBUG purposes
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(10),
  printVertex = cms.untracked.bool(False),
  src = cms.InputTag("genParticles")
)


process.p = cms.Path(
    process.TauSeq + 
    # process.printTree
    process.NtupleSeq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string('TauL1RelVal.root'))
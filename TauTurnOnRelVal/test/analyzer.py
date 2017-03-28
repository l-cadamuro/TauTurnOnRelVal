#import FWCore.ParameterSet.VarParsing as VarParsing
#import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
process = cms.Process("RelValTauL1")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '90X_mcRun2_asymptotic_v5'
# process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'

#### plugin 
process.load('TauTurnOnRelVal.TauTurnOnRelVal.MCanalysis_cff')
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/90X_upgrade2017_realistic_v20-v1/00000/580B472C-CC0F-E711-8393-0CC47A7C357E.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/90X_upgrade2017_realistic_v20-v1/00000/2C3ED96A-CC0F-E711-B53D-0CC47A7C360E.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/90X_upgrade2017_realistic_v20-v1/00000/344E9376-CB0F-E711-8AF8-0025905A48E4.root',
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
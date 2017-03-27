import FWCore.ParameterSet.Config as cms

# ## good taus - apply analysis selection
# goodTaus = cms.EDFilter("PATTauRefSelector",
#         src = cms.InputTag("slimmedTaus"),
#         cut = cms.string(
#                 'pt > 20 && abs(eta) < 2.5 ' #kinematics
#                 '&& abs(charge) > 0 && abs(charge) < 2 ' #sometimes 2 prongs have charge != 1
#                 '&& tauID("decayModeFinding") > 0.5 ' # tau ID
#                 '&& tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits") < 1.0 ' # tau iso - NOTE: can as well use boolean discriminators with WP
#                 '&& tauID("againstMuonTight3") > 0.5 ' # anti Muon tight
#                 '&& tauID("againstElectronVLooseMVA6") > 0.5 ' # anti-Ele loose
#         ),
#         filter = cms.bool(True)
# )

goodTaus = cms.EDFilter("genMatcher",
        taus = cms.InputTag("hpsPFTauProducer", "", "RECO"),
        genp = cms.InputTag("genParticles")
)

Ntuplizer = cms.EDAnalyzer("Ntuplizer",
        taus  = cms.InputTag("goodTaus"),
        L1Tau = cms.InputTag("caloStage2Digis", "Tau", "RECO"),
)

TauSeq = cms.Sequence(
        goodTaus       
)

NtupleSeq = cms.Sequence(
        Ntuplizer
)
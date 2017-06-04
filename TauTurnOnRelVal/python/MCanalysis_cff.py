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

useGenTauHad = True

goodTaus = cms.EDFilter("genMatcher",
        taus = cms.InputTag("hpsPFTauProducer", "", "RECO"),
        genp = cms.InputTag("genParticles"),
        useGenTauHad = cms.bool(useGenTauHad),

)

Ntuplizer = cms.EDAnalyzer("Ntuplizer",
        vtx   = cms.InputTag("offlinePrimaryVertices", "", "RECO"),
        taus  = cms.InputTag("goodTaus"),
        allTaus = cms.InputTag("hpsPFTauProducer", "", "RECO"),
        tauIDDiscrDecayMode = cms.InputTag("pfTausDiscriminationByDecayModeFinding", "", "RECO"),
        tauLooseMVAIso = cms.InputTag("hpsPFTauDiscriminationByLooseIsolationMVArun2v1DBoldDMwLT", "", "RECO"),
        tauMediumMVAIso = cms.InputTag("hpsPFTauDiscriminationByMediumIsolationMVArun2v1DBoldDMwLT", "", "RECO"),
        tauTightMVAIso = cms.InputTag("hpsPFTauDiscriminationByTightIsolationMVArun2v1DBoldDMwLT", "", "RECO"),
        L1Tau = cms.InputTag("caloStage2Digis", "Tau", "RECO"),
        L1TT  = cms.InputTag("simCaloStage2Digis", "MP", "HLT"),
        saveGenTauHad  = cms.bool(useGenTauHad),
        genTauHad      = cms.InputTag("goodTaus"),
        genTauMatchIdx = cms.InputTag("goodTaus"),
        saveTT = cms.bool(True),
        etaMax = cms.int32(10),
        phiMax = cms.int32(15)
)

TauSeq = cms.Sequence(
        goodTaus       
)

NtupleSeq = cms.Sequence(
        Ntuplizer
)
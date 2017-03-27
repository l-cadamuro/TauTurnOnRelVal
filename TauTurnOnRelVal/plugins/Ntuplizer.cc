#ifndef NTUPLIZER_H
#define NTUPLIZER_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <TTree.h>
// #include <TNtuple.h>
// #include <TString.h>
// #include <bitset>


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
// #include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"



class Ntuplizer : public edm::EDAnalyzer {
    public:
        /// Constructor
        explicit Ntuplizer(const edm::ParameterSet&);
        /// Destructor
        virtual ~Ntuplizer();

    private:
        //----edm control---
        // virtual void beginJob() ;
        // virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        // virtual void endJob();
        // virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void Initialize();
        // bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);

        TTree *_tree;

        // -------------------------------------
        // variables to be filled in output tree
        float _tauPt;
        float _tauEta;
        float _tauPhi;

        float _l1tPt;
        float _l1tEta;
        float _l1tPhi;
        int _l1tIso;

        edm::EDGetTokenT<reco::PFTauRefVector>  _tauTag;
        edm::EDGetTokenT<l1t::TauBxCollection> _L1TauTag  ;
};

// ----Constructor and Destructor -----
Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig) :
_tauTag         (consumes<reco::PFTauRefVector>  (iConfig.getParameter<edm::InputTag>("taus"))),
_L1TauTag       (consumes<l1t::TauBxCollection>  (iConfig.getParameter<edm::InputTag>("L1Tau")))
{
    edm::Service<TFileService> fs;
    _tree = fs -> make<TTree>("TauRelValL1", "TauRelValL1");
    
    //Branches
    // this -> _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
    // this -> _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
    // this -> _tree -> Branch("lumi",&_lumi,"lumi/I");
    // this -> _tree -> Branch("tauTriggerBits", &_tauTriggerBits, "tauTriggerBits/l");
    this -> _tree -> Branch("tauPt",  &_tauPt,  "tauPt/F");
    this -> _tree -> Branch("tauEta", &_tauEta, "tauEta/F");
    this -> _tree -> Branch("tauPhi", &_tauPhi, "tauPhi/F");
    // this -> _tree -> Branch("muonPt",  &_muonPt,  "muonPt/F");
    // this -> _tree -> Branch("muonEta", &_muonEta, "muonEta/F");
    // this -> _tree -> Branch("muonPhi", &_muonPhi, "muonPhi/F");
    // this -> _tree -> Branch("hltPt",  &_hltPt,  "hltPt/F");
    // this -> _tree -> Branch("hltEta", &_hltEta, "hltEta/F");
    // this -> _tree -> Branch("hltPhi", &_hltPhi, "hltPhi/F");
    this -> _tree -> Branch("l1tPt",  &_l1tPt,  "l1tPt/F");
    this -> _tree -> Branch("l1tEta", &_l1tEta, "l1tEta/F");
    this -> _tree -> Branch("l1tPhi", &_l1tPhi, "l1tPhi/F");
    // this -> _tree -> Branch("l1tQual", &_l1tQual, "l1tQual/I");
    this -> _tree -> Branch("l1tIso", &_l1tIso, "l1tIso/I");
    // this -> _tree -> Branch("hasTriggerMuonType", &_hasTriggerMuonType, "hasTriggerMuonType/O");
    // this -> _tree -> Branch("hasTriggerTauType", &_hasTriggerTauType, "hasTriggerTauType/O");
    // this -> _tree -> Branch("isMatched", &_isMatched, "isMatched/O");
    // this -> _tree -> Branch("isOS", &_isOS, "isOS/O");
    // this -> _tree -> Branch("foundJet", &_foundJet, "foundJet/I");
    // this -> _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");

    Initialize();
    return;
}

Ntuplizer::~Ntuplizer()
{}

void Ntuplizer::Initialize() {

    _tauPt = -999.;
    _tauEta = -999.;
    _tauPhi = -999.;

    _l1tPt = -999.;
    _l1tEta = -999.;
    _l1tPhi = -999.;
    _l1tIso = -999;
}

void Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
    // this -> Initialize();

    // _indexevents = iEvent.id().event();
    // _runNumber = iEvent.id().run();
    // _lumi = iEvent.luminosityBlock();

    // std::auto_ptr<pat::MuonRefVector> resultMuon(new pat::MuonRefVector);

    // search for the tag in the event
    edm::Handle<reco::PFTauRefVector>  tauHandle;
    iEvent.getByToken(_tauTag,   tauHandle);

    edm::Handle< BXVector<l1t::Tau> >  L1TauHandle;
    iEvent.getByToken(_L1TauTag, L1TauHandle);

    for (uint itau = 0; itau < tauHandle->size(); ++itau)
    {
        const reco::PFTau& tau = *((*tauHandle)[itau]);

        // look for a L1 candidate
        std::vector<pair<float, int>> vMatched;
        for (l1t::TauBxCollection::const_iterator bx0TauIt = L1TauHandle->begin(0); bx0TauIt != L1TauHandle->end(0) ; bx0TauIt++)
        {
            const l1t::Tau& l1tau = *bx0TauIt;
            float dR = deltaR(l1tau.p4(), tau.p4());
            if (dR < 0.5)
            {
                vMatched.push_back(make_pair(dR, std::distance(L1TauHandle->begin(0), bx0TauIt)));
            }
        }
        
        this -> Initialize();
        
        _tauPt = tau.pt();
        _tauEta = tau.eta();
        _tauPhi = tau.phi();

        if (vMatched.size() > 0)
        {
            sort(vMatched.begin(), vMatched.end());
            const l1t::Tau& l1tauMatched = *(L1TauHandle->begin(0) + vMatched.at(0).second);

            _l1tPt =  l1tauMatched.pt();
            _l1tEta = l1tauMatched.eta();
            _l1tPhi = l1tauMatched.phi();
            _l1tIso = l1tauMatched.hwIso();
        }

        _tree->Fill();
    }

    // cout << "analizzo..." << endl;
    return;

}

#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(Ntuplizer);

#endif
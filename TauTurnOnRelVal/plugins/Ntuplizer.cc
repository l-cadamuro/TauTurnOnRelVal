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
#include <TLorentzVector.h>
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
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
// #include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "L1Trigger/L1TCalorimeter/interface/CaloTools.h"
#include "L1Trigger/L1TCalorimeter/interface/CaloStage2Nav.h"

using namespace std;
using namespace l1t;


class Ntuplizer : public edm::EDAnalyzer {
    public:
        /// Constructor
        explicit Ntuplizer(const edm::ParameterSet&);
        /// Destructor
        virtual ~Ntuplizer();

        enum decayType
        {
            kMu  = 0,
            kEle = 1,
            kHad_1PiC_0PiN = 2,
            kHad_1PiC_1PiN = 3,
            kHad_1PiC_2PiN = 4,
            kHad_1PiC_3PiN = 5,
            kHad_3PiC_0PiN = 6,
            kHad_3PiC_1PiN = 7,
            kOthers    = 8
        };

    private:
        //----edm control---
        // virtual void beginJob() ;
        // virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        // virtual void endJob();
        // virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void Initialize();
        // bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);

        int getDecayType(const reco::CompositeCandidate& cand);

        int getCaloIEta(double eta);
        int getCaloIPhi(double phi, int ieta);

        TTree *_tree;

        // -------------------------------------
        // variables to be filled in output tree

        // reco
        float _tauPt;
        float _tauEta;
        float _tauPhi;
        int   _tauDecayMode;
        int   _tauIDDiscrDecayMode;
        int   _tauLooseMVAIso;
        int   _tauMediumMVAIso;
        int   _tauTightMVAIso;


        // L1 Tau
        float _l1tPt;
        float _l1tEta;
        float _l1tPhi;
        int _l1tIso;

        short int _l1tnTT;
        short int _l1trawEt;
        short int _l1tisoEt;
        bool _l1tisMerged;
        bool _l1thasEM;
        int _l1HwPt;
        int _l1HwEta;
        int _l1HwPhi;

        // nvtx
        int _nvtx;

        // TT
        std::vector<float> _TTHwEt;
        std::vector<float> _TTEta;
        std::vector<float> _TTPhi;
        std::vector<float> _TTEtaSize;
        std::vector<float> _TTPhiSize;
        int _ieta;
        int _iphi;

        // gen taus
        TLorentzVector _tlvTauVis;
        int _genDecayType; // see enum for meaning
        std::vector<TLorentzVector> _tlvProducts;
        std::vector<int>            _pdgProducts;


        edm::EDGetTokenT<reco::PFTauRefVector>  _tauTag;
        edm::EDGetTokenT<l1t::TauBxCollection> _L1TauTag;

        edm::EDGetTokenT<std::vector<reco::PFTau>> _allTauTag;

        // discriminants
        edm::EDGetTokenT<reco::PFTauDiscriminator> _tauIDDiscrDecayModeTag;
        edm::EDGetTokenT<reco::PFTauDiscriminator> _tauLooseMVAIsoTag;
        edm::EDGetTokenT<reco::PFTauDiscriminator> _tauMediumMVAIsoTag;
        edm::EDGetTokenT<reco::PFTauDiscriminator> _tauTightMVAIsoTag;


        edm::EDGetTokenT<reco::CompositeCandidateCollection>  _genTauHadTag;
        edm::EDGetTokenT<std::vector<int>> _genTauMatchIdxTag;

        edm::EDGetTokenT<BXVector<l1t::CaloTower>> _L1TTTag;

        edm::EDGetTokenT<std::vector<reco::Vertex>> _vtxTag;


        // -------------------------------------
        // controls wheter to read and save gen tau H and their products
        bool _saveGenTauHad;

        // -------------------------------------
        // these control what is to be stored for the TT map
        bool _saveTT;
        int  _etaMax; // save from -etaMax, etaMax around the stored tau candidate
        int  _phiMax; // save from -phiMax, phiMax around the stored tau candidate

        // -------------------------------------
        // to navigate through the calo
        l1t::CaloStage2Nav _caloNav;

};

// ----Constructor and Destructor -----
Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig) :
_tauTag            (consumes<reco::PFTauRefVector>  (iConfig.getParameter<edm::InputTag>("taus"))),
_L1TauTag          (consumes<l1t::TauBxCollection>  (iConfig.getParameter<edm::InputTag>("L1Tau"))),
_allTauTag         (consumes<std::vector<reco::PFTau>>      (iConfig.getParameter<edm::InputTag>("allTaus"))),
_tauIDDiscrDecayModeTag (consumes<reco::PFTauDiscriminator> (iConfig.getParameter<edm::InputTag>("tauIDDiscrDecayMode")) ),
_tauLooseMVAIsoTag      (consumes<reco::PFTauDiscriminator> (iConfig.getParameter<edm::InputTag>("tauLooseMVAIso")) ),
_tauMediumMVAIsoTag     (consumes<reco::PFTauDiscriminator> (iConfig.getParameter<edm::InputTag>("tauMediumMVAIso")) ),
_tauTightMVAIsoTag      (consumes<reco::PFTauDiscriminator> (iConfig.getParameter<edm::InputTag>("tauTightMVAIso")) ),
_genTauHadTag      (consumes<reco::CompositeCandidateCollection>  (iConfig.getParameter<edm::InputTag>("genTauHad"))),
_genTauMatchIdxTag (consumes<std::vector<int>>                    (iConfig.getParameter<edm::InputTag>("genTauMatchIdx"))),
_L1TTTag           (consumes<BXVector<l1t::CaloTower>>            (iConfig.getParameter<edm::InputTag>("L1TT"))),
_vtxTag            (consumes<std::vector<reco::Vertex>>           (iConfig.getParameter<edm::InputTag>("vtx"))),
_saveGenTauHad     (iConfig.getParameter<bool>("saveGenTauHad")),
_saveTT            (iConfig.getParameter<bool>("saveTT")),
_etaMax            (iConfig.getParameter<int>("etaMax")),
_phiMax            (iConfig.getParameter<int>("phiMax"))
{
    edm::Service<TFileService> fs;
    _tree = fs -> make<TTree>("TauRelValL1", "TauRelValL1");
    
    //Branches
    // _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
    // _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
    // _tree -> Branch("lumi",&_lumi,"lumi/I");
    // _tree -> Branch("tauTriggerBits", &_tauTriggerBits, "tauTriggerBits/l");
    _tree -> Branch("nvtx",  &_nvtx,  "nvtx/I");

    _tree -> Branch("tauPt",  &_tauPt,  "tauPt/F");
    _tree -> Branch("tauEta", &_tauEta, "tauEta/F");
    _tree -> Branch("tauPhi", &_tauPhi, "tauPhi/F");
    _tree -> Branch ("tauDecayMode" ,        &_tauDecayMode,        "tauDecayMode/I");
    _tree -> Branch ("tauIDDiscrDecayMode" , &_tauIDDiscrDecayMode, "tauIDDiscrDecayMode/I");
    _tree -> Branch ("tauLooseMVAIso" ,      &_tauLooseMVAIso,      "tauLooseMVAIso/I");
    _tree -> Branch ("tauMediumMVAIso" ,     &_tauMediumMVAIso,     "tauMediumMVAIso/I");
    _tree -> Branch ("tauTightMVAIso" ,      &_tauTightMVAIso,      "tauTightMVAIso/I");

    // _tree -> Branch("muonPt",  &_muonPt,  "muonPt/F");
    // _tree -> Branch("muonEta", &_muonEta, "muonEta/F");
    // _tree -> Branch("muonPhi", &_muonPhi, "muonPhi/F");
    // _tree -> Branch("hltPt",  &_hltPt,  "hltPt/F");
    // _tree -> Branch("hltEta", &_hltEta, "hltEta/F");
    // _tree -> Branch("hltPhi", &_hltPhi, "hltPhi/F");
    _tree -> Branch("l1tPt",  &_l1tPt,  "l1tPt/F");
    _tree -> Branch("l1tEta", &_l1tEta, "l1tEta/F");
    _tree -> Branch("l1tPhi", &_l1tPhi, "l1tPhi/F");
    // _tree -> Branch("l1tQual", &_l1tQual, "l1tQual/I");
    _tree -> Branch("l1tIso", &_l1tIso, "l1tIso/I");
    _tree -> Branch("l1HwPt", &_l1HwPt, "_l1HwPt/I");
    _tree -> Branch("l1HwEta", &_l1HwEta, "_l1HwEta/I");
    _tree -> Branch("l1HwPhi", &_l1HwPhi, "_l1HwPhi/I");
    _tree -> Branch("l1tnTT", &_l1tnTT, "l1tnTT/S");
    _tree -> Branch("l1trawEt", &_l1trawEt, "l1trawEt/S");
    _tree -> Branch("l1tisoEt", &_l1tisoEt, "l1tisoEt/S");
    _tree -> Branch("l1tisMerged", &_l1tisMerged, "l1tisMerged/O");
    _tree -> Branch("l1thasEM", &_l1thasEM, "l1thasEM/O");

    // _tree -> Branch("hasTriggerMuonType", &_hasTriggerMuonType, "hasTriggerMuonType/O");
    // _tree -> Branch("hasTriggerTauType", &_hasTriggerTauType, "hasTriggerTauType/O");
    // _tree -> Branch("isMatched", &_isMatched, "isMatched/O");
    // _tree -> Branch("isOS", &_isOS, "isOS/O");
    // _tree -> Branch("foundJet", &_foundJet, "foundJet/I");
    // _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");

    if (_saveTT)
    {
        _tree -> Branch("ieta", &_ieta, "ieta/I");   
        _tree -> Branch("iphi", &_iphi, "iphi/I");   
        _tree -> Branch("TTHwEt", &_TTHwEt);
        _tree -> Branch("TTEta", &_TTEta);
        _tree -> Branch("TTPhi", &_TTPhi);
        _tree -> Branch("TTEtaSize", &_TTEtaSize);
        _tree -> Branch("TTPhiSize", &_TTPhiSize);
    }


    if (_saveGenTauHad)
    {
        _tree -> Branch("tlvTauVis",    &_tlvTauVis);
        _tree -> Branch("tlvProducts",  &_tlvProducts, 32000, 0);
        _tree -> Branch("pdgProducts",  &_pdgProducts);
        _tree -> Branch("genDecayType", &_genDecayType, "genDecayType/I");
    }

    Initialize();
    return;
}

Ntuplizer::~Ntuplizer()
{}

void Ntuplizer::Initialize() {

    _nvtx = -999;

    _tauPt = -999.;
    _tauEta = -999.;
    _tauPhi = -999.;
    _tauDecayMode = -999;
    _tauIDDiscrDecayMode = -999;
    _tauLooseMVAIso = -999;
    _tauMediumMVAIso = -999;
    _tauTightMVAIso = -999;

    _l1tPt = -999.;
    _l1tEta = -999.;
    _l1tPhi = -999.;
    _l1tIso = -999;

    _l1tnTT = -999;
    _l1trawEt = -999;
    _l1tisoEt = -999;
    _l1tisMerged = false;
    _l1thasEM = false;
    _l1HwPt = -999;
    _l1HwEta = -999;
    _l1HwPhi = -999;

    _TTHwEt.clear();
    _TTEta.clear();
    _TTPhi.clear();
    _TTEtaSize.clear();
    _TTPhiSize.clear();
    _ieta = -999;
    _iphi = -999;

    _tlvTauVis.SetPxPyPzE(0,0,0,0);
    _tlvProducts.clear();
    _pdgProducts.clear();
    _genDecayType = -1;

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

    edm::Handle<std::vector<reco::PFTau>> allTauHandle;
    iEvent.getByToken (_allTauTag, allTauHandle);

    edm::Handle<reco::PFTauDiscriminator> tauIDDiscrDecayModeHandle;
    edm::Handle<reco::PFTauDiscriminator> tauLooseMVAIsoHandle;
    edm::Handle<reco::PFTauDiscriminator> tauMediumMVAIsoHandle;
    edm::Handle<reco::PFTauDiscriminator> tauTightMVAIsoHandle;
    iEvent.getByToken(_tauIDDiscrDecayModeTag, tauIDDiscrDecayModeHandle);
    iEvent.getByToken(_tauLooseMVAIsoTag, tauLooseMVAIsoHandle);
    iEvent.getByToken(_tauMediumMVAIsoTag, tauMediumMVAIsoHandle);
    iEvent.getByToken(_tauTightMVAIsoTag, tauTightMVAIsoHandle);

    edm::Handle< BXVector<l1t::Tau> >  L1TauHandle;
    iEvent.getByToken(_L1TauTag, L1TauHandle);

    edm::Handle< BXVector<l1t::CaloTower> >  L1TTHandle;
    iEvent.getByToken(_L1TTTag, L1TTHandle);

    edm::Handle<reco::CompositeCandidateCollection>  genTauHadHandle;
    iEvent.getByToken(_genTauHadTag, genTauHadHandle);

    edm::Handle<std::vector<int>>  genTauMatchIdxHandle;
    iEvent.getByToken(_genTauMatchIdxTag, genTauMatchIdxHandle);

    edm::Handle<std::vector<reco::Vertex>>  vtxHandle;
    iEvent.getByToken(_vtxTag,   vtxHandle);

    _nvtx = vtxHandle->size();

    std::vector<l1t::CaloTower> towers (L1TTHandle->begin(0), L1TTHandle->end(0));
    // // debug
    // if (L1TTHandle->size() > 0) cout << "YEAHHH!!!! Size > 0: " << L1TTHandle->size() << endl;
    // cout << "INITIAL SIZE TT BX VECTOR  " << L1TTHandle->size() << endl;
    // cout << "INITIAL SIZE TAU BX VECTOR " << L1TauHandle->size() << endl;
    // cout << "COPIES VECTOR : " << towers.size() << endl;
    // for (uint i = 0; i < towers.size(); ++i)
    //     cout << towers.at(i).hwEta() << " " << towers.at(i).hwPhi() << " " << towers.at(i).hwPt() << endl;

    for (uint itau = 0; itau < tauHandle->size(); ++itau)
    {
        const reco::PFTau& tau = *((*tauHandle)[itau]);
        // const reco::PFTauRef& tauref = ((*tauHandle)[itau]);

        edm::Ref<reco::PFTauCollection> tauref(allTauHandle,itau);

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
        
        this -> Initialize(); // call here, because I fill the tree per tau
        
        _tauPt = tau.pt();
        _tauEta = tau.eta();
        _tauPhi = tau.phi();
        _tauDecayMode = tau.decayMode();
        _tauIDDiscrDecayMode = ( (*tauIDDiscrDecayModeHandle)[tauref] > 0.5 ? 1 : 0);
        _tauLooseMVAIso      = ( (*tauLooseMVAIsoHandle)[tauref]      > 0.5 ? 1 : 0);
        _tauMediumMVAIso     = ( (*tauMediumMVAIsoHandle)[tauref]     > 0.5 ? 1 : 0);
        _tauTightMVAIso      = ( (*tauTightMVAIsoHandle)[tauref]      > 0.5 ? 1 : 0);


        // cout << tau.phiAtEcalEntrance() << " " << etaAtEcalEntrance() << endl;
        const std::vector<reco::PFCandidatePtr>& signalPFCands = tau.signalPFCands();
        cout << "TAU PT: " << tau.pt() << " -- Num of PF cands: " << signalPFCands.size() << endl;
        for (uint i = 0; i < signalPFCands.size(); ++i)
        {
            reco::PFCandidatePtr pfc = signalPFCands.at(i);
            cout << pfc->px() << " " << pfc->pdgId() << " " << pfc->phi() << " " << pfc->positionAtECALEntrance().phi() << endl;
        }

        // match to L1
        if (vMatched.size() > 0)
        {
            sort(vMatched.begin(), vMatched.end());
            const l1t::Tau& l1tauMatched = *(L1TauHandle->begin(0) + vMatched.at(0).second);

            _l1tPt =  l1tauMatched.pt();
            _l1tEta = l1tauMatched.eta();
            _l1tPhi = l1tauMatched.phi();
            _l1tIso = l1tauMatched.hwIso();
            _l1HwPt  = l1tauMatched.hwPt();
            _l1HwEta = l1tauMatched.hwEta();
            _l1HwPhi = l1tauMatched.hwPhi();
            _l1tnTT = l1tauMatched.nTT();
            _l1trawEt = l1tauMatched.rawEt();
            _l1tisoEt = l1tauMatched.isoEt();
            _l1tisMerged = l1tauMatched.isMerged();
            _l1thasEM = l1tauMatched.hasEM();
        }

        // save matched gen
        if (_saveGenTauHad)
        {
            int idx = genTauMatchIdxHandle->at(itau);
            const reco::CompositeCandidate& tauhad = genTauHadHandle->at(idx);
            _tlvTauVis.SetPtEtaPhiE(tauhad.pt(), tauhad.eta(), tauhad.phi(), tauhad.energy());
            _genDecayType = getDecayType(tauhad);
            // cout << " ++++++++ the returned gen decay type is " << _genDecayType << endl;
            for (uint idau = 0; idau < tauhad.numberOfDaughters(); idau++)
            {
                const reco::Candidate * dau = tauhad.daughter(idau);
                TLorentzVector vDau;
                vDau.SetPtEtaPhiE(dau->pt(), dau->eta(), dau->phi(), dau->energy());
                _tlvProducts.push_back(vDau);
                _pdgProducts.push_back(dau->pdgId());
            }
        }

        // save TT information around the reco tau
        if (_saveTT)
        {
            // find coordinates
            _ieta = getCaloIEta(tau.eta());
            _iphi = getCaloIPhi(tau.phi(), _ieta);

            // store all TTs in a vector - 
            for (int cphi = -1*_phiMax; cphi <= _phiMax; ++cphi)
            {
                for (int ceta = -1*_etaMax; ceta <= _etaMax; ++ceta)
                {
                    int jeta = _caloNav.offsetIEta(_ieta, ceta);
                    int jphi = _caloNav.offsetIPhi(_iphi, cphi);
                    const l1t::CaloTower& TT = CaloTools::getTower(towers, jeta, jphi);
                    // cout << "~~~~~ " << TT.hwEta() << " " << TT.hwPt() << endl;
                    _TTHwEt.push_back(TT.hwPt());
                    _TTEta.push_back(CaloTools::towerEta(jeta));
                    _TTPhi.push_back(CaloTools::towerPhi(jeta, jphi));
                    _TTEtaSize.push_back(CaloTools::towerEtaSize(jeta));
                    _TTPhiSize.push_back(CaloTools::towerPhiSize(jeta));
                }
            }

            // cout << " .. done " << ieta << "  " << iphi << endl;
            // for (BXVector<l1t::CaloTower>::const_iterator bx0TTIt = L1TTHandle->begin(0); bx0TTTIt != L1TTHandle->end(0) ; bx0TTTIt++)
            // {
            //     l1t::CaloTools::getTower(towers, iEtaNeigh, iPhiNeigh);
            // }

        }

        _tree->Fill();
    }

    // cout << "analizzo..." << endl;
    return;

}

int Ntuplizer::getDecayType(const reco::CompositeCandidate& cand)
{
    int npi0  = 0;
    int npich = 0;

    // // debug
    // cout << " --- new tau of px = " << cand.p4().px() << endl;
    // for (uint idau = 0; idau < cand.numberOfDaughters(); idau++)
    // {
    //     const reco::Candidate * dau = cand.daughter(idau);
    //     cout << "  ~~~ pdgId : " << dau->pdgId() << " px = " << dau->px() << endl;
    // }
    
    for (uint idau = 0; idau < cand.numberOfDaughters(); idau++)
    {
        const reco::Candidate * dau = cand.daughter(idau);
        
        int dauId = dau->pdgId();
        int absDauId = abs(dauId);

        if (absDauId == 11)
            return (int) kEle;
        else if (absDauId == 13)
            return (int) kMu;
        else if (absDauId != 111 && absDauId != 211)
            return kOthers; // everything that contains something different from a pi0 or a pi_charged falls into others

        if (dau->charge() == 0) ++npi0;
        else ++npich;
    }

    if (npich == 1)
    {
        if      (npi0 == 0) return (int) kHad_1PiC_0PiN;
        else if (npi0 == 1) return (int) kHad_1PiC_1PiN;
        else if (npi0 == 2) return (int) kHad_1PiC_2PiN;
        else if (npi0 == 3) return (int) kHad_1PiC_3PiN;
        else                return (int) kOthers;
    }
    
    else if (npich == 3)
    {
        if      (npi0 == 0) return (int) kHad_3PiC_0PiN;
        else if (npi0 == 1) return (int) kHad_3PiC_1PiN;
        else                return (int) kOthers;
    }

    return (int) kOthers;
}

// there is no way to find the idx position of a TT via its eta/phi, so I need to scan all the possible vlues to find the right one
int Ntuplizer::getCaloIEta(double eta)
{
    int ipos = 1; // FIXME: could try to make a guess using the TT width of approx 0.087
    double detac = std::abs(CaloTools::towerEta(ipos) - eta);
    double detal = std::abs(CaloTools::towerEta(_caloNav.offsetIEta(ipos, -1)) - eta);
    double detar = std::abs(CaloTools::towerEta(_caloNav.offsetIEta(ipos,  1)) - eta);
    while (detal < detac || detar < detac)
    {
        if (detal < detac) ipos = _caloNav.offsetIEta(ipos, -1) ;
        if (detar < detac) ipos = _caloNav.offsetIEta(ipos,  1) ;
        detac = std::abs(CaloTools::towerEta(ipos) - eta);
        detal = std::abs(CaloTools::towerEta(_caloNav.offsetIEta(ipos, -1)) - eta);
        detar = std::abs(CaloTools::towerEta(_caloNav.offsetIEta(ipos,  1)) - eta);        
    }

    // // debug
    // cout << "~~ eta input : " << eta <<  " --> ipos: " << ipos << endl;
    // cout << "~~~~~~ eta ipos-1 : " << CaloTools::towerEta(_caloNav.offsetIEta(ipos, -1)) << "   delta = " << eta-CaloTools::towerEta(_caloNav.offsetIEta(ipos, -1)) << endl;
    // cout << "~~~~~~ eta ipos   : " << CaloTools::towerEta(ipos) << "   delta = " << eta-CaloTools::towerEta(ipos) << endl;
    // cout << "~~~~~~ eta ipos+1 : " << CaloTools::towerEta(_caloNav.offsetIEta(ipos,  1)) << "   delta = " << eta-CaloTools::towerEta(_caloNav.offsetIEta(ipos,  1)) << endl;

    return ipos;
}

int Ntuplizer::getCaloIPhi(double phi, int ieta) // need ieta because iphi changes with ieta
{
    int ipos = 1; // FIXME: could try to make a guess using the TT width of approx 0.087
    double dphic = std::abs(CaloTools::towerPhi(ieta, ipos) - phi);
    double dphil = std::abs(CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos, -1)) - phi);
    double dphir = std::abs(CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos,  1)) - phi);
    while (dphil < dphic || dphir < dphic)
    {
        if (dphil < dphic) ipos = _caloNav.offsetIPhi(ipos, -1) ;
        if (dphir < dphic) ipos = _caloNav.offsetIPhi(ipos,  1) ;
        dphic = std::abs(CaloTools::towerPhi(ieta, ipos) - phi);
        dphil = std::abs(CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos, -1)) - phi);
        dphir = std::abs(CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos,  1)) - phi);        
    }

    // // debug
    // cout << "~~ phi input : " << phi <<  " --> ipos: " << ipos << endl;
    // cout << "~~~~~~ phi ipos-1 : " << CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos, -1)) << "   delta = " << phi-CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos, -1))  << endl;
    // cout << "~~~~~~ phi ipos   : " << CaloTools::towerPhi(ieta, ipos) << "   delta = " << phi-CaloTools::towerPhi(ieta, ipos) << endl;
    // cout << "~~~~~~ phi ipos+1 : " << CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos,  1)) << "   delta = " << phi-CaloTools::towerPhi(ieta, _caloNav.offsetIPhi(ipos,  1)) << endl;

    return ipos;
}



#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(Ntuplizer);

#endif
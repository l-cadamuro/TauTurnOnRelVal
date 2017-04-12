#ifndef GENMATCHER_H
#define GENMATCHER_H

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include <DataFormats/Candidate/interface/CompositeCandidate.h>
#include <DataFormats/HepMCCandidate/interface/GenStatusFlags.h>
#include <CommonTools/CandUtils/interface/AddFourMomenta.h>
#include <iostream>

using namespace edm;
using namespace std;
// using namespace reco;

class genMatcher : public edm::EDFilter {

    public:
        genMatcher(const edm::ParameterSet &);
        ~genMatcher();

    private:
        bool filter(edm::Event &, edm::EventSetup const&);
        void buildHadCands (Handle<std::vector<reco::GenParticle>>& genHandle, std::vector<reco::CompositeCandidate>& vGenTauHad); // fills vGenTauHad with tauh candidates
        EDGetTokenT<std::vector<reco::PFTau>> _tauTag;
        EDGetTokenT<std::vector<reco::GenParticle>> _genTag;
        bool _useGenTauHad;

};

genMatcher::genMatcher(const edm::ParameterSet & iConfig) :
_tauTag        (consumes<std::vector<reco::PFTau>>        (iConfig.getParameter<InputTag>("taus"))),
_genTag        (consumes<std::vector<reco::GenParticle>>  (iConfig.getParameter<InputTag>("genp"))),
_useGenTauHad  (iConfig.getParameter<bool>("useGenTauHad"))
{
    produces <reco::PFTauRefVector>  ();
    if (_useGenTauHad)
    {
        produces <reco::CompositeCandidateCollection>  (); // the tau had candidates
        produces <std::vector<int>> (); // the idx in the previous collection that macthes the output PFTauRef
    }
}

genMatcher::~genMatcher()
{}

bool genMatcher::filter(edm::Event & iEvent, edm::EventSetup const& iSetup)
{
    // find the taus
    std::vector<int> genPidxs;
    Handle<std::vector<reco::GenParticle>> genHandle;
    iEvent.getByToken (_genTag, genHandle);
    for (uint ig = 0; ig < genHandle->size(); ++ig)
    {
        const reco::GenParticle& gen = (*genHandle)[ig] ;
        if (abs(gen.pdgId()) != 15) continue; // only taus
        if (gen.status() != 2) continue; // only taus before decay
        // cout << "-- " << ig << " pt=" << gen.pt() << " status=" << gen.status() << endl;
        genPidxs.push_back(ig);
    }
    // cout << endl;

    if (genPidxs.size() == 0)
    {
        cout << " ** couldn't find taus, mah" << endl;
        return false;
    }

    std::vector<reco::CompositeCandidate> vGenTauHad;
    if (_useGenTauHad)
    {
        buildHadCands(genHandle, vGenTauHad);
    }

    std::unique_ptr<reco::PFTauRefVector> result ( new reco::PFTauRefVector );
    std::vector<int> vMatchedTauHadIdx;

    // find the reco taus matched - collinear approx
    Handle<std::vector<reco::PFTau>> tauHandle;
    iEvent.getByToken (_tauTag, tauHandle);
    for (uint itau = 0; itau < tauHandle->size(); ++itau)
    {
        const reco::PFTau& tau = (*tauHandle)[itau] ;
        if (tau.pt() < 20) continue;

        if (!_useGenTauHad)
        {
            bool matches = false;
            for (uint ig = 0 ; ig < genPidxs.size(); ++ig)
            {
                // cout << "UNO" << endl;
                // cout << "TAU p4: " << tau.p4() << endl;
                // cout << "DUE" << endl;
                // cout << "GEN pr: " << (*genHandle)[genPidxs.at(ig)].p4() << endl;
                
                if (deltaR (tau.p4() , (*genHandle)[genPidxs.at(ig)].p4() ) < 0.5)
                {
                    matches = true;
                    break;
                }
            }

            if (matches)
            {
                // edm::Ref<C> myRef(const edm::Handle<C> & collection, size_type indexIntoCollection)
                reco::PFTauRef selTau (tauHandle , itau);
                result->push_back (selTau);
                // cout << "oo" << endl;
            }
        } // end of match to tau before decay

        else
        {
            int imatch = -1;
            for (uint ig = 0 ; ig < vGenTauHad.size(); ++ig)
            {
                // cout << "UNO" << endl;
                // cout << "TAU p4: " << tau.p4() << endl;
                // cout << "DUE" << endl;
                // cout << "GEN pr: " << (*genHandle)[genPidxs.at(ig)].p4() << endl;
                
                if (deltaR (tau.p4() , vGenTauHad.at(ig).p4() ) < 0.5)
                {
                    imatch = ig;
                    break;
                }
            }

            if (imatch >= 0)
            {
                // edm::Ref<C> myRef(const edm::Handle<C> & collection, size_type indexIntoCollection)
                reco::PFTauRef selTau (tauHandle , itau);
                result->push_back (selTau);
                vMatchedTauHadIdx.push_back (imatch);
                // cout << "oo" << endl;
            }
        } // end of match to gen tau had
    }

    iEvent.put(std::move(result));
    if (_useGenTauHad)
    {
        std::unique_ptr<std::vector<int>> resultMatchedIdx ( new std::vector<int>(vMatchedTauHadIdx) );
        std::unique_ptr<reco::CompositeCandidateCollection> resultTauHad ( new reco::CompositeCandidateCollection(vGenTauHad) );
        iEvent.put(std::move(resultMatchedIdx));
        iEvent.put(std::move(resultTauHad));
    }

    return true;
}

void genMatcher::buildHadCands (Handle<std::vector<reco::GenParticle>>& genHandle, std::vector<reco::CompositeCandidate>& vGenTauHad)
{
    for (uint ig = 0 ; ig < genHandle->size(); ++ig)
    {
        // look for taus that do noe produce other taus
        const reco::GenParticle& gp = (*genHandle)[ig];
        if (abs(gp.pdgId()) != 15) continue;
        const reco::GenStatusFlags& fl = gp.statusFlags();
        if (!fl.isLastCopy()) continue; // just take taus before decay

        reco::CompositeCandidate tauhad;

        // build tauh
        for (uint idau = 0; idau < gp.numberOfDaughters(); idau++)
        {
            const reco::Candidate * dau = gp.daughter(idau);
            int dauId = abs(dau->pdgId());
            if (dauId == 12 || dauId == 14 || dauId == 16) continue;
            tauhad.addDaughter(*dau);
            // cout << "--- added px " << dau->px() << endl;
        }

        AddFourMomenta addP4;
        addP4.set(tauhad); // this is needed to set the composite candidate p4

        // cout << " ==== result: px " << tauhad.px() << " == " << tauhad.p4().px() << endl;
        vGenTauHad.push_back(tauhad);
    }
    return;
}


#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(genMatcher);

#endif



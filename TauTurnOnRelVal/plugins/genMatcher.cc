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
        EDGetTokenT<std::vector<reco::PFTau>> _tauTag;
        EDGetTokenT<std::vector<reco::GenParticle>> _genTag;
};

genMatcher::genMatcher(const edm::ParameterSet & iConfig) :
_tauTag   (consumes<std::vector<reco::PFTau>>        (iConfig.getParameter<InputTag>("taus"))),
_genTag    (consumes<std::vector<reco::GenParticle>> (iConfig.getParameter<InputTag>("genp")))
{
    produces <reco::PFTauRefVector>  ();
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

    std::unique_ptr<reco::PFTauRefVector> result ( new reco::PFTauRefVector );

    // find the reco taus matched - collinear approx
    Handle<std::vector<reco::PFTau>> tauHandle;
    iEvent.getByToken (_tauTag, tauHandle);
    for (uint itau = 0; itau < tauHandle->size(); ++itau)
    {
        const reco::PFTau& tau = (*tauHandle)[itau] ;
        if (tau.pt() < 20) continue;

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
    }

    iEvent.put(std::move(result));
    return true;
}

#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(genMatcher);

#endif



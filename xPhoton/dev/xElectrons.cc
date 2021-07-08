#include "xPhoton/xPhoton/interface/xElectrons.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#include <TLorentzVector.h>
#include <map>


static std::map<const char*, TH1*> histMap;


std::vector<TLorentzCand> PreselectedElectrons(TreeReader* dataptr, int WP);
std::vector<TLorentzCand> matchedGenZee(TreeReader* dataptr, const TLorentzCand& ZCand_);
void xElectrons(
        std::vector<std::string> pathes,
        char oname[200] )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    
    rec_Electron elecand[2];
    rec_Z Zcand;
    rec_Event event;

    //RegBranch( outtree_, "electron0", &ele0cand );
    //RegBranch( outtree_, "electron1", &ele1cand );
    RegBranch( outtree_, "electron0", &elecand[0] );
    RegBranch( outtree_, "electron1", &elecand[1] );
    RegBranch( outtree_, "Z", &Zcand );
    RegBranch( outtree_, "Events", &event );

    histMap["DeltaR_GenZee"] = new TH1F("DeltaR_GenZee", "", BINNING, 0., 1.);
    histMap["DeltaR_GenEle"] = new TH1F("DeltaR_GenEle", "", BINNING, 0., 1.);
    
    // check the reason why event failed
    // 0: all event record in ROOT file
    // 1: passed if the preselected electrons >= 2
    // 2: passed if Z->ee candidate found
    histMap["ShowEventReduced"] = new TH1F("evtReduced", "", 3, 0., 3.);

    // preselection cut applied for select electron candidate
    // 0: number of electron in event.
    // 1: electron pt > 12
    // 2: |eta| < 2.5
    // 3: eta is not in barrel - endcap gap.
    // 4: pass electron id bit in data
    histMap["elePreselStats"] = new TH1F("eleReduced", "", 5, 0., 5.);

    // number of electron selected.
    histMap["Nele"] = new TH1F("Nele", "", 4, 0., 4.);

    // Filling condition to reconstruct Z->ee channel.
    // 0: number of electron pairs
    // 1: pass HLT in data
    // 2: electron pair with opposite charge
    // 3: Z candidate mass = [ 90-40, 90+40 ]
    histMap["ZRecoStatus"] = new TH1F("ZrecoStat", "", 4, 0.,4.);

    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        // 1. load data
        // 2. build electron 4mom and pass electron preselection (and HLT)
        // 3. build Z candidate and reject event.
        // 4. mc truth matching.
        // 5. fill tree
        // 6. mva
        data.GetEntry(ev);
        std::vector<TLorentzCand> selelectrons = PreselectedElectrons(&data, ELECTRONWORKINGPOINT);
        histMap["ShowEventReduced"]->Fill(0);
        
        histMap["Nele"]->Fill( selelectrons.size() );
        if ( selelectrons.size() < 2 ) continue;

        histMap["ShowEventReduced"]->Fill(1);

        TLorentzCand ZcandP4;
        for ( int idx=0; idx<selelectrons.size(); ++idx )
        {
            for ( int jdx=idx+1; jdx<selelectrons.size(); ++jdx )
            {
                const TLorentzCand& ele0 = selelectrons.at(idx);
                const TLorentzCand& ele1 = selelectrons.at(jdx);
                histMap["ZRecoStatus"]->Fill(0);
                if (!data.HasMC() )
                {
                    if ( ( (ULong64_t*)data.GetPtrLong64("eleFiredDoubleTrgs") )[ele0.idx()] == 0 ) continue; // nothing triggered.
                            
                    if ( PASS_HLTBIT > 0 ) // although ULong64_t used. but only 0~31 bits recorded in ROOT. bit larger than 31 is useless.
                    {
                        int bit = PASS_HLTBIT;
                        if ( (( (ULong64_t*)data.GetPtrLong64("eleFiredDoubleTrgs") )[ele0.idx()]>>bit)&1 == 0 ) continue; // tight ID for tag photon.
                        // need to check the validation
                        /* asdf
                        if ( ( (UShort_t*)data.GetPtrShort("eleIDbit") )[ele0.idx()] & 1<<bit == 0 ) continue; // tight ID for tag photon.
                        */
                    }
                }
                histMap["ZRecoStatus"]->Fill(1);

                if ( ele0.charge() * ele1.charge() > 0 ) continue;
                histMap["ZRecoStatus"]->Fill(2);
                ZcandP4 = ele0+ele1;
                if ( ZcandP4.M() <  MASS_Z-WINDOW_Z || ZcandP4.M() > MASS_Z+WINDOW_Z ) continue;
                histMap["ZRecoStatus"]->Fill(3);
                ZcandP4.SetAlive();
                break;
            }
            if (!ZcandP4.IsZombie() ) break;
        }

        if ( ZcandP4.IsZombie() ) continue;
        histMap["ShowEventReduced"]->Fill(2);
        LOG_DEBUG("Z candidate found, owning %d electrons", ZcandP4.daughters().size());
        
        // MC truth matching

        std::vector<TLorentzCand> matchedElectrons = matchedGenZee(&data, ZcandP4);
        LOG_DEBUG("MC matched %d", matchedElectrons.size());
        if ( matchedElectrons.size() ) histMap["ZRecoStatus"]->Fill(4);

        



        // filling events
        
        //for ( int i = 0; i < 2; ++i )
            
        /*
        {
        }
        
        Int_t* eleCharge = data.GetPtrInt("eleCharge");
        Float_t* elePt = data.GetPtrFloat("elePt");
        Float_t* eleEta = data.GetPtrFloat("eleEta");
        Float_t* elePhi = data.GetPtrFloat("elePhi");
        Float_t* eleR9  = data.GetPtrFloat("eleR9");
        Float_t* eleCalibPt = data.GetPtrFloat("eleCalibPt");
        Float_t* eleCalibEta = data.GetPtrFloat("eleCalibEta");
        



        */

        outtree_->Fill();
    }


    LOG_INFO("event looping end. Storing everything into root file");
    fout_->cd();
    LOG_DEBUG("writing tree");
    outtree_->Write();
    LOG_DEBUG("writing histograms");
    for ( auto iter = histMap.begin(); iter != histMap.end(); ++iter ) iter->second->Write();
    LOG_DEBUG("closing output ROOT file");
    fout_->Close();
    //LOG_DEBUG("deleting histograms");
    //for ( auto iter = histMap.begin(); iter != histMap.end(); ++iter ) delete iter->second;
    LOG_INFO("All %lld Events processed", data.GetEntriesFast());
}
void xElectrons(std::string ipath, int outID)
{
   char fname[200];
   std::vector<std::string> pathes;

   pathes.push_back(ipath);

   char oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   xElectrons(pathes, oname);
}

std::vector<TLorentzCand> PreselectedElectrons(TreeReader* dataptr, int WP)
{
    std::vector<int> selParticleIdxs;
    
    Int_t Size = dataptr->GetInt("nEle");
    Int_t* charge = dataptr->GetPtrInt("eleCharge");
    Float_t* pt = dataptr->GetPtrFloat("elePt");
    Float_t* eta = dataptr->GetPtrFloat("eleSCEta");
    Float_t* phi = dataptr->GetPtrFloat("eleSCPhi");
    UShort_t* idbit = (UShort_t*)dataptr->GetPtrShort("eleIDbit");
    for ( int i = 0; i < Size; ++i )
    {
        histMap["elePreselStats"]->Fill(0);
        if ( pt[i] < 12. ) continue;
        histMap["elePreselStats"]->Fill(1);
        float abseta = fabs(eta[i]);
        if ( abseta > 2.5 ) continue;
        histMap["elePreselStats"]->Fill(2);
        if ( abseta > 1.4442 && abseta < 1.566 ) continue;
        histMap["elePreselStats"]->Fill(3);
        if (!dataptr->HasMC() ) if (!((idbit[i] >> WP) & 1) ) continue;
        histMap["elePreselStats"]->Fill(4);
        selParticleIdxs.push_back(i);
    }

    std::vector<TLorentzCand> outputs;
    for ( int idx : selParticleIdxs )
        outputs.emplace_back( recoInfo::BuildSelectedParticles(idx, pt[idx], eta[idx], phi[idx], MASS_ELECTRON, charge[idx]) );
    return outputs;
}
std::vector<TLorentzCand> matchedGenZee(TreeReader* dataptr, const TLorentzCand& ZCand_)
{
    #define DELTARCUT 0.4
    #define FINALSTATE_STATUSCUT 3
    #define PID_Z 23
    #define PID_ELECTRON 11
    
    if (!dataptr->HasMC() ) return std::vector<TLorentzCand>();

    Int_t  nMC_         = dataptr->GetInt("nMC");
    Int_t* mcPID_       = dataptr->GetPtrInt("mcPID");
    Int_t* mcMomPID_    = dataptr->GetPtrInt("mcMomPID");
    Int_t* mcStatus_    = dataptr->GetPtrInt("mcStatus");



    std::vector<Int_t> genElectronIdxs;
    std::vector<Int_t> genZElectronIdxs;
    for ( Int_t iMC = 0; iMC < nMC_; ++iMC )
        if ( fabs(mcPID_[iMC]) == PID_ELECTRON && mcStatus_[iMC] <= FINALSTATE_STATUSCUT )
        {
            genElectronIdxs.emplace_back(iMC);
            if ( mcMomPID_[iMC] == PID_Z )
                genZElectronIdxs.emplace_back(iMC);
        }
    
    Float_t* pt_        = dataptr->GetPtrFloat("elePt");
    Float_t* eta_       = dataptr->GetPtrFloat("eleEta");
    Float_t* phi_       = dataptr->GetPtrFloat("elePhi");
    Int_t  * charge_    = dataptr->GetPtrInt("eleCharge");
    Float_t* genpt_     = dataptr->GetPtrFloat("mcPt");
    Float_t* geneta_    = dataptr->GetPtrFloat("mcEta");
    Float_t* genphi_    = dataptr->GetPtrFloat("mcPhi");
    


    TLorentzCand recoEle0( ZCand_.daughters().at(0), charge_[ZCand_.daughters().at(0)] );
    TLorentzCand recoEle1( ZCand_.daughters().at(1), charge_[ZCand_.daughters().at(1)] );
    recoEle0.SetPtEtaPhiM(pt_[ZCand_.daughters().at(0)], eta_[ZCand_.daughters().at(0)], phi_[ZCand_.daughters().at(0)], MASS_ELECTRON );
    recoEle1.SetPtEtaPhiM(pt_[ZCand_.daughters().at(1)], eta_[ZCand_.daughters().at(1)], phi_[ZCand_.daughters().at(1)], MASS_ELECTRON );
    
    bool matched_signal = false;
    bool matched_background = false;
    
    
    LOG_DEBUG("Got %d Z electrons in gen level, and %d gen electrons", genZElectronIdxs.size(), genElectronIdxs.size() );
    const std::vector<Int_t>& genIdxsContainer = (genZElectronIdxs.size()>1) ? genZElectronIdxs : genElectronIdxs;
    for ( Int_t geleIdx0 : genIdxsContainer )
        for ( Int_t geleIdx1 : genIdxsContainer )
        {
            LOG_DEBUG("starting matching");
            if ( geleIdx0 == geleIdx1 ) continue;
            LOG_DEBUG("selection1");
            if ( genpt_[geleIdx0] < genpt_[geleIdx1] ) continue;
            LOG_DEBUG("selection2");
            if ( mcMomPID_[geleIdx0] != mcMomPID_[geleIdx1] ) continue;
            LOG_DEBUG("selection3");
            TLorentzCand genEle0(geleIdx0, mcPID_[geleIdx0] > 0 ? -1 : 1 );
            TLorentzCand genEle1(geleIdx1, mcPID_[geleIdx1] > 0 ? -1 : 1 );
            genEle0.SetPtEtaPhiM(genpt_[geleIdx0], geneta_[geleIdx0], genphi_[geleIdx0], MASS_ELECTRON );
            genEle1.SetPtEtaPhiM(genpt_[geleIdx1], geneta_[geleIdx1], genphi_[geleIdx1], MASS_ELECTRON );

            if ( genEle0.charge() != recoEle0.charge() || genEle1.charge() != recoEle1.charge() ) continue;
            LOG_DEBUG("selection4");
            double deltaR0 = genEle0.DeltaR(recoEle0);
            double deltaR1 = genEle1.DeltaR(recoEle1);
            LOG_DEBUG("Calculating delta R value : %.3f -- %.3f", deltaR0, deltaR1);
            if ( genZElectronIdxs.size() > 1 )
            {
                histMap["DeltaR_GenZee"]->Fill(deltaR0);
                histMap["DeltaR_GenZee"]->Fill(deltaR1);
                if ( deltaR0 < DELTARCUT && deltaR1 < DELTARCUT )
                    return std::vector<TLorentzCand>( {genEle0,genEle1} );
            }
            else
            {
                histMap["DeltaR_GenEle"]->Fill(deltaR0);
                histMap["DeltaR_GenEle"]->Fill(deltaR1);
            }
        }
    

    return std::vector<TLorentzCand>();
}
std::vector<int>  findMatchedRecoElectron(TreeReader* dataptr)
{
    
    if (!dataptr->HasMC() ) return std::vector<int>();

    Int_t  nMC_         = dataptr->GetInt("nMC");
    Int_t* genPID_      = dataptr->GetPtrInt("mcPID");
    Int_t* genMomPID_   = dataptr->GetPtrInt("mcMomPID");
    Int_t* genStatus_   = dataptr->GetPtrInt("mcStatus");

    Float_t* genpt_     = dataptr->GetPtrFloat("mcPt");
    Float_t* geneta_    = dataptr->GetPtrFloat("mcEta");
    Float_t* genphi_    = dataptr->GetPtrFloat("mcPhi");

    Int_t  nEle_        = dataptr->GetInt("nEle");
    Float_t* pt_        = dataptr->GetPtrFloat("elePt");
    Float_t* eta_       = dataptr->GetPtrFloat("eleEta");
    Float_t* phi_       = dataptr->GetPtrFloat("elePhi");
    Int_t  * charge_    = dataptr->GetPtrInt("eleCharge");


    std::vector<TLorentzCand> genZElectrons;
    for ( Int_t iMC = 0; iMC < nMC_; ++iMC )
        if ( fabs(genPID_[iMC]) == PID_ELECTRON && genStatus_[iMC] <= FINALSTATE_STATUSCUT && genMomPID_[iMC] == PID_Z )
            genZElectrons.emplace_back(iMC,
                    genPID_[iMC] == PID_ELECTRON ? -1 : 1, // charge
                    genpt_[iMC], geneta_[iMC], genphi_[iMC], MASS_ELECTRON );
    
    

    std::sort(genZElectrons.begin(), genZElectrons.end(), recoInfo::cmpPt);


    /*
    TLorentzCand recoEle0( ZCand_.daughters().at(0), charge_[ZCand_.daughters().at(0)] );
    recoEle0.SetPtEtaPhiM(pt_[ZCand_.daughters().at(0)], eta_[ZCand_.daughters().at(0)], phi_[ZCand_.daughters().at(0)], MASS_ELECTRON );
    
    
    for ( const TLorentzCand&  genElectron : genZElectrons )
        for ( Int_t geleIdx1 : genIdxsContainer )
        {
            if ( geleIdx0 == geleIdx1 ) continue;
            if ( genpt_[geleIdx0] < genpt_[geleIdx1] ) continue;
            if ( genMomPID_[geleIdx0] != genMomPID_[geleIdx1] ) continue;
            TLorentzCand genEle0(geleIdx0, genPID_[geleIdx0] > 0 ? -1 : 1 );
            TLorentzCand genEle1(geleIdx1, genPID_[geleIdx1] > 0 ? -1 : 1 );
            genEle0.SetPtEtaPhiM(genpt_[geleIdx0], geneta_[geleIdx0], genphi_[geleIdx0], MASS_ELECTRON );
            genEle1.SetPtEtaPhiM(genpt_[geleIdx1], geneta_[geleIdx1], genphi_[geleIdx1], MASS_ELECTRON );

            if ( genEle0.charge() != recoEle0.charge() || genEle1.charge() != recoEle1.charge() ) continue;
            double deltaR0 = genEle0.DeltaR(recoEle0);
            double deltaR1 = genEle1.DeltaR(recoEle1);
            if ( genZElectronIdxs.size() > 1 )
            {
                histMap["DeltaR_GenZee"]->Fill(deltaR0);
                histMap["DeltaR_GenZee"]->Fill(deltaR1);
                if ( deltaR0 < DELTARCUT && deltaR1 < DELTARCUT )
                    return std::vector<TLorentzCand>( {genEle0,genEle1} );
            }
            else
            {
                histMap["DeltaR_GenEle"]->Fill(deltaR0);
                histMap["DeltaR_GenEle"]->Fill(deltaR1);
            }
        }
        */
    return std::vector<int>();

}

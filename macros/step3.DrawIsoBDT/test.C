#include <iostream>
#include <stdio.h>

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
// target : 
//    input data / sigMC / bkgMC and return binning histogram with all and sideband BDT distribution.
//    which all distribution is 2D histogram. But sideband is 1D.



struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        ebee        = root.get<int>("phoEtaBin"  , 0 );
        jetbin      = root.get<int>("jetEtaBin"  , 0 );
        ptbin       = root.get<int>("phoPtBin"   , 0 );
        rebinoption = root.get<int>("rebinOption", 5 );
        sb1         = root.get<int>("sidebandlower", 14);
        sb2         = root.get<int>("sidebandupper", 20);

        datafile    = root.get<std::string>("data", "");
        sig_file    = root.get<std::string>("sig" , "");
        bkg_file    = root.get<std::string>("bkg" , "");
        out_template= root.get<std::string>("out_template" , "");

    }
    int ebee, jetbin, ptbin, rebinoption, sb1, sb2;
    std::string datafile, sig_file, bkg_file;
    std::string out_template;

    const char* Data()  const { return datafile.c_str(); }
    const char* SigMC() const { return sig_file.c_str(); }
    const char* BkgMC() const { return bkg_file.c_str(); }
};

struct BinInfo
{
    BinInfo( const JsonInfo& args )
    {
        ebee        = args.ebee        ;
        jetbin      = args.jetbin      ;
        ptbin       = args.ptbin       ;
        rebinoption = args.rebinoption ;
        sb1         = args.sb1         ;
        sb2         = args.sb2         ;
        tag="";
        file=nullptr;
    }
    BinInfo(const BinInfo& input)
    {
        this->ebee =          input.ebee ;
        this->jetbin =        input.jetbin ;
        this->ptbin =         input.ptbin ;
        this->rebinoption =   input.rebinoption ;
        this->sb1 =           input.sb1 ;
        this->sb2 =           input.sb2 ;
        this->tag =           input.tag;
        this->file =          input.file;
    }
    BinInfo() {} 
    int ebee, jetbin, ptbin, rebinoption, sb1, sb2;
    std::string tag;
    TFile* file;


    const char* BinnedName(const char* nTemplate) const { return Form(nTemplate, ebee, jetbin, ptbin); }
    TObject* Get(const char* varTemplate) { if ( tag=="") throw std::runtime_error("TFile not loaded!\n"); return file->Get( BinnedName(varTemplate) ); }
    void SetTagAndFile(const std::string& t, TFile* f) { tag=t; file=f; }
};
std::vector<float> ptbin_ranges()
{
    // for 2016
    //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
    std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
    return vec_ptcut;
}
bool IsPhoBarrel( int phoEtaBin )
{ return phoEtaBin == 0; }
bool IsPhoEndcap( int phoEtaBin )
{ return phoEtaBin == 1; }
bool IsJetBarrel( int jetEtaBin )
{ return jetEtaBin == 0; ;}
bool IsJetEndcap( int jetEtaBin )
{ return jetEtaBin == 1; ;}

TH2F* GetHist(BinInfo args, const char* histNameTemplate )
{
    const int EXCLUSIVE_PHOTON = 2;
    TH2F* hout = (TH2F*) args.Get( histNameTemplate );
    if ( args.jetbin != EXCLUSIVE_PHOTON ) return hout;

    while ( args.jetbin-- )
    {
        TH2F* htemp = (TH2F*) args.Get(histNameTemplate);
        hout->Add(htemp);
    }
    return hout;
}

struct HistsNeedStored
{
    TH1D* hpx0;
    TH1D* hpx1;
    TH2F* hall;

    void Write( TDirectory* dir = nullptr )
    {
        if ( dir ) dir->cd();
        hpx0->Write();
        hpx1->Write();
        hall->Write();
    }
};


void PrintSigAndSideBandBasicInfo( const HistsNeedStored& hists )
{
    printf("In hist %s\n", hists.hall->GetName());
    printf("sig fraction : %5.2f %% and fake fraction %5.2f %%\n", 100.*hists.hpx0->Integral()/hists.hall->Integral(), 100.*hists.hpx1->Integral()/hists.hall->Integral() );
}

HistsNeedStored SigAndSidebandHistCalc( const BinInfo& args, const char* histNameTemplate)
{
    TH2F* hdata = GetHist( args, histNameTemplate );

    TH2F* hdata_all = (TH2F*) hdata->Clone(); 
    std::string allname = args.tag + "_all_%d_%d_%d";
    hdata_all->SetName( args.BinnedName(allname.c_str()) );
    hdata->Rebin2D(args.rebinoption,2);

    int nbinx = hdata->GetNbinsX();

    int zone1_low = 1;
    int zone1_high = 4; 
    //if(args.ebee>=2) { //EE
    int IsoOption=0; //0 chIso, 1 phoIso, 2 combIso, 3 chWorst
    if( IsPhoEndcap(args.ebee) ) { //EE
        if     (IsoOption==0) zone1_high=3;
        else if(IsoOption==1) zone1_high=5;
        else if(IsoOption==2) zone1_high=7;
        else if(IsoOption==3) zone1_high=6;
    }

    int zone2_low = args.sb1;
    int zone2_high = args.sb2;
    //for production 
    //if(args.ebee<=1) {zone2_low=14; zone2_high=26;} //EB
    //else {zone2_low=12; zone2_high=24;}
    if( IsPhoBarrel(args.ebee) ) {zone2_low=7; zone2_high=20;} //EB //asdf need to redefine EBEE 
    //else if(args.ebee==2) {zone2_low=7; zone2_high=20;}
    else {zone2_low=6; zone2_high=20;}

    //for chIso SB

    std::string zone1name = args.tag + "_%d_%d_%d_px1_chIso";
    TH1D *h_data_zone1 = (TH1D*)hdata->ProjectionX(args.BinnedName(zone1name.c_str()),zone1_low, zone1_high);
    std::string zone2name = args.tag + "_%d_%d_%d_px2_chIso";
    TH1D *h_data_zone2 = (TH1D*)hdata->ProjectionX(args.BinnedName(zone2name.c_str()),zone2_low, zone2_high);


    HistsNeedStored out;
    out.hpx0 = h_data_zone1;
    out.hpx1 = h_data_zone2;
    out.hall = hdata_all;

    PrintSigAndSideBandBasicInfo(out);
    return out;
}


void Draw_IsovsBDT(const char* jsonName){
    JsonInfo args(jsonName);

    TFile *fdata = TFile::Open( args.Data()  );
    TFile *fqcd  = TFile::Open( args.BkgMC() );
    TFile *fgjet = TFile::Open( args.SigMC() );

    BinInfo arg_data(args), arg_gjet(args), arg_qcd(args);
    arg_data.SetTagAndFile("data",fdata);
    arg_gjet.SetTagAndFile("gjet",fgjet);
    arg_qcd .SetTagAndFile("qcd" ,fqcd );

    std::vector<HistsNeedStored> outputHists;
    outputHists.push_back(SigAndSidebandHistCalc(arg_gjet, "IsovsBDT/IsovsBDT.%d_%d_%d_0_0"));
    outputHists.push_back(SigAndSidebandHistCalc(arg_data, "IsovsBDT/IsovsBDT.%d_%d_%d_0_0"));
    outputHists.push_back(SigAndSidebandHistCalc(arg_qcd , "IsovsBDT/IsovsBDT.%d_%d_%d_1_0"));

    TFile* fout = new TFile( arg_data.BinnedName("iso_%d_%d_%d.root"), "RECREATE" );
    for ( auto outhists : outputHists )
        outhists.Write(fout);

    fout->Close();
}


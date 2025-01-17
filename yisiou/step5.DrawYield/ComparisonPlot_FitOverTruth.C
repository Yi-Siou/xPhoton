#include <cstdlib>

//#define MESG(format, args...)     fprintf(stderr, "MESG:%s -> " format "\n", __PRETTY_FUNCTION__,  ##args)
#define MESG(format, args...)
#define MAXPTBIN 25
void ck();
double sumEntries( TH1* h );
double Chi2(TH1* hFit, TH1* hTruth);
static void Visualization( TH1* h, int color=2, int fillstyle=0, int markersize=0 );
TTree* datReader( const char* filename );
double FindMaximum(TH1*);
double FindMinimum(TH1*);
void ENVSetup();


TPad* UpperPad();
TPad* LowerPad();


struct MyBin
{
public:
    MyBin( int phoeta, int jeteta, int phopt )
        : phoEbin(phoeta), jetEbin(jeteta), phoPbin(phopt) {}
    const char* naming( const char* nametemplate )
    { return Form(nametemplate, phoEbin, jetEbin, phoPbin); }
    int EncodedBin()
    { return MAXPTBIN * 2 * jetEbin + MAXPTBIN * phoEbin + phoPbin; }
    static int EncodedBin( int phoeta, int jeteta, int phopt )
    { return MAXPTBIN * 2 * jeteta + MAXPTBIN * phoeta + phopt; }

    int phoEbin, jetEbin, phoPbin;
};
struct FitVal
{
    FitVal() : val(0),err(0){}
    FitVal( float v, float e ) : val(v), err(e) {}
    FitVal( const FitVal& rhs )
    { val = rhs.val; err = rhs.err; }
    float val, err;
};
std::map<int,FitVal> LoadFittedVals( const char* fname );

class MyRatioPlot
{
public:
    MyRatioPlot( TH1* numeratorhist, TH1* denominatorhist, TLegend* legend = nullptr ) :
        _numeratorHist(numeratorhist),_denominatorHist(denominatorhist),_leg(legend),
        _upperpad( UpperPad() ), _lowerpad( LowerPad() ),
        logy(false)
    {
        _numeratorHist->SetStats(false);
        _denominatorHist->SetStats(false);
        GetDividedHist();
    }
    ~MyRatioPlot()
    {
        delete _ratioHist;
        delete _upperpad;
        delete _lowerpad;
        delete _centerline;
    }
    void UseLogy(bool val = true)
    {
        logy=val;

        float M0 = FindMaximum(_numeratorHist);
        float M1 = FindMaximum(_denominatorHist);
        float MVal = M0 > M1 ? M0 * 1000. : M1 * 1000.;
        _denominatorHist->SetMinimum(1e-1);
        _denominatorHist->SetMaximum(MVal);

        _numeratorHist->SetMinimum(1e-1);
        _numeratorHist->SetMaximum(MVal);
    }

    void PlotOn(TPad* p)
    {
        p->cd();

        float M0 = FindMaximum(_numeratorHist);
        float M1 = FindMaximum(_denominatorHist);
        float maxScaler = logy ? 1000. : 1.5;
        float MVal = M0 > M1 ? M0 * maxScaler : M1 * maxScaler;
        if ( MVal < 1. ) MVal = 2.;
        _denominatorHist->SetMinimum(1e-1);
        _denominatorHist->SetMaximum(MVal);

        _numeratorHist->SetMinimum(1e-1);
        _numeratorHist->SetMaximum(MVal);

        _denominatorHist->GetXaxis()->SetLabelSize(0);
        _denominatorHist->GetYaxis()->SetTitleOffset(0.95);
        _denominatorHist->GetYaxis()->SetTitleSize(0.06);

        _numeratorHist->GetXaxis()->SetLabelSize(0);
        _numeratorHist->GetYaxis()->SetTitleOffset(0.95);
        _numeratorHist->GetYaxis()->SetTitleSize(0.06);

        _centerline = GetLine(1.00);
        _upperpad->Draw();
        _lowerpad->Draw();

        _upperpad->cd();
        _numeratorHist->Draw("axis");
        _denominatorHist->Draw("hist same");
        _numeratorHist->Draw("ep same");
        if ( _leg ) _leg->Draw();
        _upperpad->SetLogy(1);

        _lowerpad->cd();
        _ratioHist->Draw("e0p");
        _centerline->Draw();
        p->Modified();
    }
private:
    TH1* _numeratorHist;
    TH1* _denominatorHist;
    TLegend* _leg;
    TH1*   _ratioHist;
    TPad*  _upperpad;
    TPad*  _lowerpad;
    TLine* _centerline;
    bool logy;

    void GetDividedHist()
    {
        _ratioHist = (TH1*) _numeratorHist->Clone();
        int ibin = _ratioHist->GetNbinsX() + 1;

        double maxVal = 0.;
        double minVal = 1.;
        while ( --ibin )
        {
            double val_nu = _numeratorHist->GetBinContent(ibin);
            double val_de = _denominatorHist->GetBinContent(ibin);
            double err_nu = _numeratorHist->GetBinError(ibin);

            if ( val_de < 1e-3 )
            {
                _ratioHist->SetBinContent(ibin, 0.);
                _ratioHist->SetBinError  (ibin, 0.);
            }
            else
            {
                _ratioHist->SetBinContent(ibin, val_nu/val_de);
                _ratioHist->SetBinError  (ibin, err_nu/val_de);
            }
            
            double _v = val_de > 1e-3 ? val_nu / val_de : 0.;
            if ( _v > maxVal ) maxVal = _v;
            if ( _v < minVal ) minVal = _v;
        }

        auto yranges = findSuitableYrange(minVal,maxVal);
        _ratioHist->SetMinimum(yranges.first );
        _ratioHist->SetMaximum(yranges.second);

        // _ratioHist->SetMarkerColor(1);
        // _ratioHist->SetLineColor(1);
        // _ratioHist->SetMarkerSize(2);
        _ratioHist->GetXaxis()->SetLabelSize(0.1);
        _ratioHist->GetXaxis()->SetTitleSize(0.2);
        _ratioHist->GetXaxis()->SetTitleOffset(0.70);

        _ratioHist->GetYaxis()->SetNdivisions(505);
        _ratioHist->GetYaxis()->SetLabelSize(0.1);
        _ratioHist->GetYaxis()->SetTitle("ratio");
        _ratioHist->GetYaxis()->SetTitleOffset(0.3);
        _ratioHist->GetYaxis()->SetTitleSize(0.2);
    }
    TLine* GetLine(double yval_ = 1.0, int color_ = 1, int width_ = 1)
    {
        TLine* line = new TLine(
                _numeratorHist->GetBinLowEdge(1), yval_,
                _numeratorHist->GetBinLowEdge(_numeratorHist->GetNbinsX()+1), yval_ );
        line->SetLineColor(color_);
        line->SetLineWidth(width_);
        line->SetLineStyle(7);

        return line;
    }
    std::pair<float,float> findSuitableYrange(float minVal, float maxVal)
    {
        bool keepgoingon = true;
        if ( minVal > maxVal ) keepgoingon = false;
        if ( maxVal < 1e-3 || maxVal > 100. ) keepgoingon = false;
        if ( minVal < 1e-3 || minVal > 100. ) keepgoingon = false;
        if (!keepgoingon ) return std::pair<float,float>(0.,1.);

        float separator = 20.;

        float Mval = float(int(separator*maxVal)+2)/separator - 0.1/separator; // to avoid upper y label at lower pad
        float mval = float(int(separator*minVal)  )/separator;
        return std::pair<float,float>(mval,Mval);
    }
};
class MyLegend : public TLegend
{
public :
    MyLegend(float p0x, float p0y, float p1x, float p1y) : TLegend(p0x,p0y,p1x,p1y,"", "brNDC")
    {
        this->SetFillColor(4000);
        this->SetFillStyle(4000);
        this->SetBorderSize(0);
    }
    TLegend* PassLegend() { return this; }
};


void DrawRatio_withScaleFactor( TH1* hNumerator, TH1* hDenominator, float fitVal, TCanvas* c1, const char* oname )
{
    c1->cd();
    TH1* hFit   = (TH1*) hNumerator  ->Clone();
    TH1* hTruth = (TH1*) hDenominator->Clone();
    Visualization( hFit  , 2, 0, 4 );
    Visualization( hTruth, 34, 1001 );
    double histEntries = sumEntries( hFit );
    double scaleFactor = fitVal / histEntries;
    hFit->Scale( scaleFactor );
    double chi2val = Chi2(hFit,hDenominator);

    MESG( "fit entries : %.1f and truth entries : %.1f", fitVal, sumEntries(hTruth) );
    MESG( "Plot chi2/nDoF value is : %.2f / %d", chi2val, hFit->GetNbinsX()-1 );

    MyLegend leg(0.3,0.5,0.7,0.85);
    double absval = fabs( fitVal - sumEntries(hDenominator) ) / sqrt(fitVal);

    leg.SetHeader( Form("#chi^{2}/nDoF = %.2f / %d. Significance = %.1f", chi2val,hFit->GetNbinsX()-1, absval) );
    leg.AddEntry(hFit  , Form("Fitted val %.1f", fitVal), "lp");
    leg.AddEntry(hTruth, Form("Truth val %.1f", sumEntries(hDenominator)), "f");
    MyRatioPlot totalPlot( hFit, hTruth, leg.PassLegend() );
    totalPlot.PlotOn(c1);
    c1->SaveAs(oname);

    delete hFit;
    delete hTruth;
}




void ComparisonPlot_FitOverTruth()
{
    // ENVSetup();
    TFile* truthsigFile=TFile::Open("isovsbdt_fragments.sig.root");
    TFile* truthbkgFile=TFile::Open("isovsbdt_fragments.bkg.root");
    TFile* origfragFile=TFile::Open("isovsbdt_template.root");

    std::map<int,FitVal> sigPool = LoadFittedVals("data_yield.dat");
    std::map<int,FitVal> bkgPool = LoadFittedVals("data_bkg.dat");

    TCanvas* c1 = new TCanvas("c1", "", 1200,1000);
    c1->SetFillColor(4000);
    c1->SetFillStyle(4000);

    
    const int numPhoEta = 2;
    const int numJetEta = 2;
    const int numPhoPt = 20;
    for ( int phoEbin = 0 ; phoEbin < numPhoEta ; ++ phoEbin )
        for ( int jetEbin = 0 ; jetEbin < numJetEta ; ++ jetEbin )
            for ( int phoPbin = 0; phoPbin < numPhoPt ; ++ phoPbin )
    {
        MyBin binning( phoEbin, jetEbin, phoPbin );

        DrawRatio_withScaleFactor(
                (TH1*) origfragFile->Get( binning.naming("gjet_%d_%d_%d_px1_chIso") ),
                (TH1*) truthsigFile->Get( binning.naming("data_%d_%d_%d_px1_chIso") ),
                sigPool[ binning.EncodedBin() ].val,
                c1,
                binning.naming("plots/fragments/plot_sig_%d_%d_%d.pdf"));
        DrawRatio_withScaleFactor(
                (TH1*) origfragFile->Get( binning.naming("data_%d_%d_%d_px2_chIso") ),
                (TH1*) truthbkgFile->Get( binning.naming("data_%d_%d_%d_px1_chIso") ),
                bkgPool[ binning.EncodedBin() ].val,
                c1,
                binning.naming("plots/fragments/plot_bkg_%d_%d_%d.pdf"));
    }
}

// function definitions {{{
double sumEntries( TH1* h )
{
    double integral = 0;
    for ( int ibin=0; ibin < h->GetNbinsX(); ++ibin )
        integral += h->GetBinContent(ibin+1);
    return integral;
}

static
void Visualization( TH1* h, int color, int fillstyle, int markersize )
{
    h->Rebin(10);
    h->SetStats(false);
    //h->GetXaxis()->SetLabelSize(0);
    h->SetTitle("");
    if ( markersize != 0 )
    {
        h->SetMarkerSize(markersize);
        h->SetLineWidth(4);
        h->SetLineColor(color);
        h->SetMarkerColor(color);
        return;
    }
    if ( fillstyle != 0 )
    {
        h->SetFillColor(color);
        h->SetFillStyle(fillstyle);
        return;
    }
    std::cerr << "nothing setup in " << h->GetName() << std::endl;
    return;
}

TTree* datReader(const char* filename)
{
    TTree* t = new TTree();
    t->ReadFile(filename);
    t->SetDirectory(0);
    return t;
}

std::map<int,FitVal> LoadFittedVals( const char* fname ) {
    TTree* tdat = datReader(fname);
    int ptbin, etabin, jetbin;
    float val, err;
    
    tdat->SetBranchAddress("ptbin", &ptbin);
    tdat->SetBranchAddress("EBEE",  &etabin);
    tdat->SetBranchAddress("jetbin",&jetbin);
    if ( tdat->GetListOfBranches()->FindObject("bkg") )
    {
        tdat->SetBranchAddress("bkg"       , &val);
        tdat->SetBranchAddress("bkg_err"   , &err);
    }
    else
    {
        tdat->SetBranchAddress("yields"    , &val);
        tdat->SetBranchAddress("yields_err", &err);
    }

    std::map<int,FitVal> output;
    int ievt = 0;
    int Nevt = tdat->GetEntries();
    while ( ievt != Nevt )
    {
        tdat->GetEntry(ievt++);
        MyBin binning( etabin, jetbin, ptbin );
        output.insert( std::make_pair( binning.EncodedBin(), FitVal(val,err) ) );
    }
    return output;
}
double Chi2(TH1* hFit, TH1* hTruth)
{
    double chi2 = 0.;

    int ibin = hFit->GetNbinsX() + 1;
    while ( --ibin )
    {
        if ( hTruth->GetBinContent(ibin) < 1e-3 ) continue;
        chi2 += ( hFit->GetBinContent(ibin) - hTruth->GetBinContent(ibin) ) / hFit->GetBinError(ibin);
    }

    return TMath::Sqrt(chi2);
}
TPad* UpperPad()
{
    TPad* pad = new TPad("Pad","Pad",0.,0.245,1.,0.98);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.05);
    //pad->SetBottomMargin(0.019);
    pad->SetBottomMargin(0.021);
    pad->SetLeftMargin(0.135);//0.12
    pad->SetRightMargin(0.06);//0.12

    return pad;
}


TPad* LowerPad()
{
    TPad* pad = new TPad("Pad1","Pad1",0.,0.0,1.,0.250);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.0);
    pad->SetBottomMargin(0.35);
    pad->SetLeftMargin(0.135);
    pad->SetRightMargin(0.06);

    return pad;
}
double FindMinimum(TH1* h)
{
    double val = h->GetBinContent(1);
    int ibin = h->GetNbinsX()+1;
    while (--ibin)
        if ( val > h->GetBinContent(ibin) ) val = h->GetBinContent(ibin);
    return val;
}
        

double FindMaximum(TH1* h)
{
    double val = h->GetBinContent(1);
    int ibin = h->GetNbinsX()+1;
    while (--ibin)
        if ( val < h->GetBinContent(ibin) ) val = h->GetBinContent(ibin);
    return val;
}

void ENVSetup()
{
    MESG("Cleaning 'plots/fragments' folder");
    system("touch plots/fragments && /bin/rm -r plots/fragments && mkdir plots/fragments ");
}

// function definitions end }}}

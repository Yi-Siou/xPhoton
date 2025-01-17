void h_truthCompSig_barrelPho_endcapJet()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Dec 10 15:01:42 2021) by ROOT version6.10/09
   TCanvas *c1 = new TCanvas("c1", "",0,0,1200,1000);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: upperpad
   TPad *upperpad = new TPad("upperpad", "",0,0.245,1,0.98);
   upperpad->Draw();
   upperpad->cd();
   upperpad->Range(-29.50311,-1554.031,374.2236,80237.05);
   upperpad->SetFillColor(0);
   upperpad->SetBorderMode(0);
   upperpad->SetBorderSize(2);
   upperpad->SetTickx(1);
   upperpad->SetTicky(1);
   upperpad->SetLeftMargin(0.135);
   upperpad->SetRightMargin(0.06);
   upperpad->SetTopMargin(0.05);
   upperpad->SetBottomMargin(0.019);
   upperpad->SetFrameBorderMode(0);
   upperpad->SetFrameBorderMode(0);
   Double_t xAxis29[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *sig__29 = new TH1F("sig__29","",16, xAxis29);
   sig__29->SetBinContent(1,29968);
   sig__29->SetBinContent(2,22010);
   sig__29->SetBinContent(3,50765);
   sig__29->SetBinContent(4,36701);
   sig__29->SetBinContent(5,25210);
   sig__29->SetBinContent(6,17421);
   sig__29->SetBinContent(7,12637);
   sig__29->SetBinContent(8,11410);
   sig__29->SetBinContent(9,7589);
   sig__29->SetBinContent(10,5189);
   sig__29->SetBinContent(11,2969);
   sig__29->SetBinContent(12,1679);
   sig__29->SetBinContent(13,2689);
   sig__29->SetBinContent(14,2735);
   sig__29->SetBinContent(15,2493);
   sig__29->SetBinContent(16,1227);
   sig__29->SetBinContent(17,698);
   sig__29->SetMaximum(76147.5);
   sig__29->SetEntries(19);
   sig__29->SetStats(0);
   sig__29->SetFillColor(48);
   sig__29->SetLineColor(48);
   sig__29->GetXaxis()->SetLabelFont(42);
   sig__29->GetXaxis()->SetLabelSize(0.035);
   sig__29->GetXaxis()->SetTitleSize(0.035);
   sig__29->GetXaxis()->SetTitleFont(42);
   sig__29->GetYaxis()->SetLabelFont(42);
   sig__29->GetYaxis()->SetLabelSize(0.035);
   sig__29->GetYaxis()->SetTitleSize(0.035);
   sig__29->GetYaxis()->SetTitleOffset(0);
   sig__29->GetYaxis()->SetTitleFont(42);
   sig__29->GetZaxis()->SetLabelFont(42);
   sig__29->GetZaxis()->SetLabelSize(0.035);
   sig__29->GetZaxis()->SetTitleSize(0.035);
   sig__29->GetZaxis()->SetTitleFont(42);
   sig__29->Draw("hist");
   Double_t xAxis30[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *sig__30 = new TH1F("sig__30","",16, xAxis30);
   sig__30->SetBinContent(1,29968);
   sig__30->SetBinContent(2,22010);
   sig__30->SetBinContent(3,50765);
   sig__30->SetBinContent(4,36701);
   sig__30->SetBinContent(5,25210);
   sig__30->SetBinContent(6,17421);
   sig__30->SetBinContent(7,12637);
   sig__30->SetBinContent(8,11410);
   sig__30->SetBinContent(9,7589);
   sig__30->SetBinContent(10,5189);
   sig__30->SetBinContent(11,2969);
   sig__30->SetBinContent(12,1679);
   sig__30->SetBinContent(13,2689);
   sig__30->SetBinContent(14,2735);
   sig__30->SetBinContent(15,2493);
   sig__30->SetBinContent(16,1227);
   sig__30->SetBinContent(17,698);
   sig__30->SetMaximum(76147.5);
   sig__30->SetEntries(19);
   sig__30->SetStats(0);
   sig__30->SetFillColor(48);
   sig__30->SetLineColor(48);
   sig__30->GetXaxis()->SetLabelFont(42);
   sig__30->GetXaxis()->SetLabelSize(0.035);
   sig__30->GetXaxis()->SetTitleSize(0.035);
   sig__30->GetXaxis()->SetTitleFont(42);
   sig__30->GetYaxis()->SetLabelFont(42);
   sig__30->GetYaxis()->SetLabelSize(0.035);
   sig__30->GetYaxis()->SetTitleSize(0.035);
   sig__30->GetYaxis()->SetTitleOffset(0);
   sig__30->GetYaxis()->SetTitleFont(42);
   sig__30->GetZaxis()->SetLabelFont(42);
   sig__30->GetZaxis()->SetLabelSize(0.035);
   sig__30->GetZaxis()->SetTitleSize(0.035);
   sig__30->GetZaxis()->SetTitleFont(42);
   sig__30->Draw("hist same");
   Double_t xAxis31[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *bkg__31 = new TH1F("bkg__31","",16, xAxis31);
   bkg__31->SetBinContent(1,4289);
   bkg__31->SetBinContent(2,2227);
   bkg__31->SetBinContent(3,4398);
   bkg__31->SetBinContent(4,3064);
   bkg__31->SetBinContent(5,2186);
   bkg__31->SetBinContent(6,1637);
   bkg__31->SetBinContent(7,1188);
   bkg__31->SetBinContent(8,1007);
   bkg__31->SetBinContent(9,698);
   bkg__31->SetBinContent(10,501);
   bkg__31->SetBinContent(11,299);
   bkg__31->SetBinContent(12,153);
   bkg__31->SetBinContent(13,291);
   bkg__31->SetBinContent(14,300);
   bkg__31->SetBinContent(15,288);
   bkg__31->SetBinContent(16,123);
   bkg__31->SetBinContent(17,55);
   bkg__31->SetMaximum(76147.5);
   bkg__31->SetEntries(19);
   bkg__31->SetStats(0);
   bkg__31->SetFillColor(38);
   bkg__31->SetLineColor(38);
   bkg__31->GetXaxis()->SetLabelFont(42);
   bkg__31->GetXaxis()->SetLabelSize(0.035);
   bkg__31->GetXaxis()->SetTitleSize(0.035);
   bkg__31->GetXaxis()->SetTitleFont(42);
   bkg__31->GetYaxis()->SetLabelFont(42);
   bkg__31->GetYaxis()->SetLabelSize(0.035);
   bkg__31->GetYaxis()->SetTitleSize(0.035);
   bkg__31->GetYaxis()->SetTitleOffset(0);
   bkg__31->GetYaxis()->SetTitleFont(42);
   bkg__31->GetZaxis()->SetLabelFont(42);
   bkg__31->GetZaxis()->SetLabelSize(0.035);
   bkg__31->GetZaxis()->SetTitleSize(0.035);
   bkg__31->GetZaxis()->SetTitleFont(42);
   bkg__31->Draw("hist same");
   Double_t xAxis32[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *fitsig__32 = new TH1F("fitsig__32","",16, xAxis32);
   fitsig__32->SetBinContent(1,29858.1);
   fitsig__32->SetBinContent(2,21933.9);
   fitsig__32->SetBinContent(3,50655.6);
   fitsig__32->SetBinContent(4,36622);
   fitsig__32->SetBinContent(5,25210.9);
   fitsig__32->SetBinContent(6,17509.1);
   fitsig__32->SetBinContent(7,12732.2);
   fitsig__32->SetBinContent(8,11477.3);
   fitsig__32->SetBinContent(9,7597.8);
   fitsig__32->SetBinContent(10,5227.7);
   fitsig__32->SetBinContent(11,2993.8);
   fitsig__32->SetBinContent(12,1706.4);
   fitsig__32->SetBinContent(13,2693.9);
   fitsig__32->SetBinContent(14,2763.3);
   fitsig__32->SetBinContent(15,2486.2);
   fitsig__32->SetBinContent(16,1238.5);
   fitsig__32->SetBinContent(17,683.5);
   fitsig__32->SetBinError(1,180.5);
   fitsig__32->SetBinError(2,153.1);
   fitsig__32->SetBinError(3,230.5);
   fitsig__32->SetBinError(4,195.3);
   fitsig__32->SetBinError(5,162.1);
   fitsig__32->SetBinError(6,135);
   fitsig__32->SetBinError(7,114.8);
   fitsig__32->SetBinError(8,109.1);
   fitsig__32->SetBinError(9,89.4);
   fitsig__32->SetBinError(10,74.1);
   fitsig__32->SetBinError(11,56.1);
   fitsig__32->SetBinError(12,42.2);
   fitsig__32->SetBinError(13,53.6);
   fitsig__32->SetBinError(14,54.3);
   fitsig__32->SetBinError(15,52);
   fitsig__32->SetBinError(16,36.8);
   fitsig__32->SetBinError(17,27.4);
   fitsig__32->SetMaximum(76147.5);
   fitsig__32->SetEntries(19);
   fitsig__32->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   fitsig__32->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   fitsig__32->SetMarkerColor(ci);
   fitsig__32->SetMarkerStyle(20);
   fitsig__32->SetMarkerSize(2);
   fitsig__32->GetXaxis()->SetLabelFont(42);
   fitsig__32->GetXaxis()->SetLabelSize(0.035);
   fitsig__32->GetXaxis()->SetTitleSize(0.035);
   fitsig__32->GetXaxis()->SetTitleFont(42);
   fitsig__32->GetYaxis()->SetLabelFont(42);
   fitsig__32->GetYaxis()->SetLabelSize(0.035);
   fitsig__32->GetYaxis()->SetTitleSize(0.035);
   fitsig__32->GetYaxis()->SetTitleOffset(0);
   fitsig__32->GetYaxis()->SetTitleFont(42);
   fitsig__32->GetZaxis()->SetLabelFont(42);
   fitsig__32->GetZaxis()->SetLabelSize(0.035);
   fitsig__32->GetZaxis()->SetTitleSize(0.035);
   fitsig__32->GetZaxis()->SetTitleFont(42);
   fitsig__32->Draw("p same");
   Double_t xAxis33[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *fitbkg__33 = new TH1F("fitbkg__33","",16, xAxis33);
   fitbkg__33->SetBinContent(1,4398.7);
   fitbkg__33->SetBinContent(2,2302.9);
   fitbkg__33->SetBinContent(3,4505.9);
   fitbkg__33->SetBinContent(4,3142.2);
   fitbkg__33->SetBinContent(5,2184.6);
   fitbkg__33->SetBinContent(6,1548.5);
   fitbkg__33->SetBinContent(7,1092.4);
   fitbkg__33->SetBinContent(8,939.6);
   fitbkg__33->SetBinContent(9,688.9);
   fitbkg__33->SetBinContent(10,462.1);
   fitbkg__33->SetBinContent(11,274.1);
   fitbkg__33->SetBinContent(12,125.6);
   fitbkg__33->SetBinContent(13,286.2);
   fitbkg__33->SetBinContent(14,271.7);
   fitbkg__33->SetBinContent(15,294.9);
   fitbkg__33->SetBinContent(16,111.5);
   fitbkg__33->SetBinContent(17,69.5);
   fitbkg__33->SetBinError(2,84.4);
   fitbkg__33->SetBinError(3,61.8);
   fitbkg__33->SetBinError(4,83.6);
   fitbkg__33->SetBinError(5,68.2);
   fitbkg__33->SetBinError(6,56.9);
   fitbkg__33->SetBinError(7,47.7);
   fitbkg__33->SetBinError(8,39.4);
   fitbkg__33->SetBinError(9,37.1);
   fitbkg__33->SetBinError(10,32.8);
   fitbkg__33->SetBinError(11,27);
   fitbkg__33->SetBinError(12,20.8);
   fitbkg__33->SetBinError(13,14.2);
   fitbkg__33->SetBinError(14,21.5);
   fitbkg__33->SetBinError(15,21.5);
   fitbkg__33->SetBinError(16,22.7);
   fitbkg__33->SetBinError(17,15);
   fitbkg__33->SetMaximum(76147.5);
   fitbkg__33->SetEntries(19);
   fitbkg__33->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   fitbkg__33->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   fitbkg__33->SetMarkerColor(ci);
   fitbkg__33->SetMarkerStyle(34);
   fitbkg__33->SetMarkerSize(2);
   fitbkg__33->GetXaxis()->SetLabelFont(42);
   fitbkg__33->GetXaxis()->SetLabelSize(0.035);
   fitbkg__33->GetXaxis()->SetTitleSize(0.035);
   fitbkg__33->GetXaxis()->SetTitleFont(42);
   fitbkg__33->GetYaxis()->SetLabelFont(42);
   fitbkg__33->GetYaxis()->SetLabelSize(0.035);
   fitbkg__33->GetYaxis()->SetTitleSize(0.035);
   fitbkg__33->GetYaxis()->SetTitleOffset(0);
   fitbkg__33->GetYaxis()->SetTitleFont(42);
   fitbkg__33->GetZaxis()->SetLabelFont(42);
   fitbkg__33->GetZaxis()->SetLabelSize(0.035);
   fitbkg__33->GetZaxis()->SetTitleSize(0.035);
   fitbkg__33->GetZaxis()->SetTitleFont(42);
   fitbkg__33->Draw("p same");
   
   TLegend *leg = new TLegend(0.2,0.7,0.89,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("sig","Signal truth","lf");
   entry->SetFillColor(48);
   entry->SetFillStyle(1001);
   entry->SetLineColor(48);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("bkg","Background truth","lf");
   entry->SetFillColor(38);
   entry->SetFillStyle(1001);
   entry->SetLineColor(38);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("fitsig","Signal fitted","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("fitbkg","Background fitted","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   leg->Draw();
   upperpad->Modified();
   c1->cd();
  
// ------------>Primitives in pad: lowerpad
   TPad *lowerpad = new TPad("lowerpad", "",0,0,1,0.25);
   lowerpad->Draw();
   lowerpad->cd();
   lowerpad->Range(-29.50311,-1.615385,374.2236,3);
   lowerpad->SetFillColor(0);
   lowerpad->SetBorderMode(0);
   lowerpad->SetBorderSize(2);
   lowerpad->SetTickx(1);
   lowerpad->SetTicky(1);
   lowerpad->SetLeftMargin(0.135);
   lowerpad->SetRightMargin(0.06);
   lowerpad->SetTopMargin(0);
   lowerpad->SetBottomMargin(0.35);
   lowerpad->SetFrameBorderMode(0);
   lowerpad->SetFrameBorderMode(0);
   Double_t xAxis34[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *fitsig__34 = new TH1F("fitsig__34","",16, xAxis34);
   fitsig__34->SetBinContent(1,0.6088665);
   fitsig__34->SetBinContent(2,0.4970582);
   fitsig__34->SetBinContent(3,0.4746136);
   fitsig__34->SetBinContent(4,0.4045059);
   fitsig__34->SetBinContent(5,0.005554538);
   fitsig__34->SetBinContent(6,0.6525897);
   fitsig__34->SetBinContent(7,0.8292699);
   fitsig__34->SetBinContent(8,0.6168635);
   fitsig__34->SetBinContent(9,0.09843182);
   fitsig__34->SetBinContent(10,0.5222698);
   fitsig__34->SetBinContent(11,0.4420686);
   fitsig__34->SetBinContent(12,0.6492897);
   fitsig__34->SetBinContent(13,0.09141609);
   fitsig__34->SetBinContent(14,0.5211796);
   fitsig__34->SetBinContent(15,0.1307702);
   fitsig__34->SetBinContent(16,0.3125);
   fitsig__34->SetBinContent(17,683.5);
   fitsig__34->SetBinError(17,27.4);
   fitsig__34->SetMinimum(0);
   fitsig__34->SetMaximum(3);
   fitsig__34->SetEntries(35);
   fitsig__34->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   fitsig__34->SetLineColor(ci);
   fitsig__34->SetLineWidth(0);

   ci = TColor::GetColor("#ff0000");
   fitsig__34->SetMarkerColor(ci);
   fitsig__34->SetMarkerStyle(20);
   fitsig__34->SetMarkerSize(2);
   fitsig__34->GetXaxis()->SetLabelFont(42);
   fitsig__34->GetXaxis()->SetLabelSize(0.1);
   fitsig__34->GetXaxis()->SetTitleSize(0.035);
   fitsig__34->GetXaxis()->SetTitleFont(42);
   fitsig__34->GetYaxis()->SetTitle("Significance");
   fitsig__34->GetYaxis()->SetNdivisions(505);
   fitsig__34->GetYaxis()->SetLabelFont(42);
   fitsig__34->GetYaxis()->SetLabelSize(0.1);
   fitsig__34->GetYaxis()->SetTitleSize(0.15);
   fitsig__34->GetYaxis()->SetTitleOffset(0.3);
   fitsig__34->GetYaxis()->SetTitleFont(42);
   fitsig__34->GetZaxis()->SetLabelFont(42);
   fitsig__34->GetZaxis()->SetLabelSize(0.035);
   fitsig__34->GetZaxis()->SetTitleSize(0.035);
   fitsig__34->GetZaxis()->SetTitleFont(42);
   fitsig__34->Draw("p");
   Double_t xAxis35[17] = {25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350}; 
   
   TH1F *fitbkg__35 = new TH1F("fitbkg__35","",16, xAxis35);
   fitbkg__35->SetBinContent(1,-1);
   fitbkg__35->SetBinContent(2,0.8992879);
   fitbkg__35->SetBinContent(3,1.745953);
   fitbkg__35->SetBinContent(4,0.9354061);
   fitbkg__35->SetBinContent(5,0.02052643);
   fitbkg__35->SetBinContent(6,1.55536);
   fitbkg__35->SetBinContent(7,2.004192);
   fitbkg__35->SetBinContent(8,1.71066);
   fitbkg__35->SetBinContent(9,0.2452824);
   fitbkg__35->SetBinContent(10,1.185975);
   fitbkg__35->SetBinContent(11,0.922222);
   fitbkg__35->SetBinContent(12,1.317308);
   fitbkg__35->SetBinContent(13,0.3380273);
   fitbkg__35->SetBinContent(14,1.316278);
   fitbkg__35->SetBinContent(15,0.3209299);
   fitbkg__35->SetBinContent(16,0.5066079);
   fitbkg__35->SetBinContent(17,69.5);
   fitbkg__35->SetBinError(17,15);
   fitbkg__35->SetMinimum(0);
   fitbkg__35->SetMaximum(3);
   fitbkg__35->SetEntries(35);
   fitbkg__35->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   fitbkg__35->SetLineColor(ci);
   fitbkg__35->SetLineWidth(0);

   ci = TColor::GetColor("#0000ff");
   fitbkg__35->SetMarkerColor(ci);
   fitbkg__35->SetMarkerStyle(34);
   fitbkg__35->SetMarkerSize(2);
   fitbkg__35->GetXaxis()->SetLabelFont(42);
   fitbkg__35->GetXaxis()->SetLabelSize(0.1);
   fitbkg__35->GetXaxis()->SetTitleSize(0.035);
   fitbkg__35->GetXaxis()->SetTitleFont(42);
   fitbkg__35->GetYaxis()->SetTitle("Significance");
   fitbkg__35->GetYaxis()->SetNdivisions(505);
   fitbkg__35->GetYaxis()->SetLabelFont(42);
   fitbkg__35->GetYaxis()->SetLabelSize(0.1);
   fitbkg__35->GetYaxis()->SetTitleSize(0.15);
   fitbkg__35->GetYaxis()->SetTitleOffset(0.3);
   fitbkg__35->GetYaxis()->SetTitleFont(42);
   fitbkg__35->GetZaxis()->SetLabelFont(42);
   fitbkg__35->GetZaxis()->SetLabelSize(0.035);
   fitbkg__35->GetZaxis()->SetTitleSize(0.035);
   fitbkg__35->GetZaxis()->SetTitleFont(42);
   fitbkg__35->Draw("p same");
   lowerpad->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}

void uncert_2()
{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Mar 26 08:25:40 2018) by ROOT version6.08/07
   TCanvas *c1 = new TCanvas("c1", "c1",1,1,600,576);
   gStyle->SetOptStat(0);
   c1->Range(0.06249997,-0.025,4.4375,0.225);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   Double_t xAxis3[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_2__1027 = new TH1D("uncert_2__1027","",32, xAxis3);
   uncert_2__1027->SetBinContent(1,0.01212776);
   uncert_2__1027->SetBinContent(2,0.008364141);
   uncert_2__1027->SetBinContent(3,0.002395511);
   uncert_2__1027->SetBinContent(4,0.001615763);
   uncert_2__1027->SetBinContent(5,0.002874732);
   uncert_2__1027->SetBinContent(6,0.002485216);
   uncert_2__1027->SetBinContent(7,0.003041565);
   uncert_2__1027->SetBinContent(8,0.002901971);
   uncert_2__1027->SetBinContent(9,0.002935648);
   uncert_2__1027->SetBinContent(10,0.002915323);
   uncert_2__1027->SetBinContent(11,0.002957463);
   uncert_2__1027->SetBinContent(12,0.002682567);
   uncert_2__1027->SetBinContent(13,0.00311619);
   uncert_2__1027->SetBinContent(14,0.00280875);
   uncert_2__1027->SetBinContent(15,0.002093315);
   uncert_2__1027->SetBinContent(16,0.001348317);
   uncert_2__1027->SetMinimum(0);
   uncert_2__1027->SetMaximum(0.2);
   uncert_2__1027->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_2__1027->SetLineColor(ci);
   uncert_2__1027->SetMarkerStyle(8);
   uncert_2__1027->GetXaxis()->SetTitle("p_{T}");
   uncert_2__1027->GetXaxis()->SetRange(1,15);
   uncert_2__1027->GetXaxis()->SetLabelFont(42);
   uncert_2__1027->GetXaxis()->SetLabelSize(0.035);
   uncert_2__1027->GetXaxis()->SetTitleSize(0.035);
   uncert_2__1027->GetXaxis()->SetTitleFont(42);
   uncert_2__1027->GetYaxis()->SetTitle("Uncertainty");
   uncert_2__1027->GetYaxis()->SetLabelFont(42);
   uncert_2__1027->GetYaxis()->SetLabelSize(0.035);
   uncert_2__1027->GetYaxis()->SetTitleSize(0.035);
   uncert_2__1027->GetYaxis()->SetTitleOffset(1.3);
   uncert_2__1027->GetYaxis()->SetTitleFont(42);
   uncert_2__1027->GetZaxis()->SetLabelFont(42);
   uncert_2__1027->GetZaxis()->SetLabelSize(0.035);
   uncert_2__1027->GetZaxis()->SetTitleSize(0.035);
   uncert_2__1027->GetZaxis()->SetTitleFont(42);
   uncert_2__1027->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","10-30%","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}

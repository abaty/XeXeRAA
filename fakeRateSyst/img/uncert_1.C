void uncert_1()
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
   Double_t xAxis2[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_1__1026 = new TH1D("uncert_1__1026","",32, xAxis2);
   uncert_1__1026->SetBinContent(1,0.1365994);
   uncert_1__1026->SetBinContent(2,0.04902059);
   uncert_1__1026->SetBinContent(3,0.007329702);
   uncert_1__1026->SetBinContent(4,0.004171193);
   uncert_1__1026->SetBinContent(5,0.007328868);
   uncert_1__1026->SetBinContent(6,0.005410075);
   uncert_1__1026->SetBinContent(7,0.005522668);
   uncert_1__1026->SetBinContent(8,0.005457461);
   uncert_1__1026->SetBinContent(9,0.004779935);
   uncert_1__1026->SetBinContent(10,0.004885614);
   uncert_1__1026->SetBinContent(11,0.00426507);
   uncert_1__1026->SetBinContent(12,0.005260646);
   uncert_1__1026->SetBinContent(13,0.004767001);
   uncert_1__1026->SetBinContent(14,0.003827512);
   uncert_1__1026->SetBinContent(15,0.003338337);
   uncert_1__1026->SetBinContent(16,0.001608789);
   uncert_1__1026->SetMinimum(0);
   uncert_1__1026->SetMaximum(0.2);
   uncert_1__1026->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_1__1026->SetLineColor(ci);
   uncert_1__1026->SetMarkerStyle(8);
   uncert_1__1026->GetXaxis()->SetTitle("p_{T}");
   uncert_1__1026->GetXaxis()->SetRange(1,15);
   uncert_1__1026->GetXaxis()->SetLabelFont(42);
   uncert_1__1026->GetXaxis()->SetLabelSize(0.035);
   uncert_1__1026->GetXaxis()->SetTitleSize(0.035);
   uncert_1__1026->GetXaxis()->SetTitleFont(42);
   uncert_1__1026->GetYaxis()->SetTitle("Uncertainty");
   uncert_1__1026->GetYaxis()->SetLabelFont(42);
   uncert_1__1026->GetYaxis()->SetLabelSize(0.035);
   uncert_1__1026->GetYaxis()->SetTitleSize(0.035);
   uncert_1__1026->GetYaxis()->SetTitleOffset(1.3);
   uncert_1__1026->GetYaxis()->SetTitleFont(42);
   uncert_1__1026->GetZaxis()->SetLabelFont(42);
   uncert_1__1026->GetZaxis()->SetLabelSize(0.035);
   uncert_1__1026->GetZaxis()->SetTitleSize(0.035);
   uncert_1__1026->GetZaxis()->SetTitleFont(42);
   uncert_1__1026->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","5-10%","");
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

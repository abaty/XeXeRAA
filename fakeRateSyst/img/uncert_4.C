void uncert_4()
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
   Double_t xAxis5[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_4__1029 = new TH1D("uncert_4__1029","",32, xAxis5);
   uncert_4__1029->SetBinContent(1,1.865625e-05);
   uncert_4__1029->SetBinContent(2,0.0004914999);
   uncert_4__1029->SetBinContent(3,0.0003061891);
   uncert_4__1029->SetBinContent(4,0.0004602075);
   uncert_4__1029->SetBinContent(5,0.001046062);
   uncert_4__1029->SetBinContent(6,0.001355588);
   uncert_4__1029->SetBinContent(7,0.001155257);
   uncert_4__1029->SetBinContent(8,0.001613379);
   uncert_4__1029->SetBinContent(9,0.001800954);
   uncert_4__1029->SetBinContent(10,0.001958013);
   uncert_4__1029->SetBinContent(11,0.001495481);
   uncert_4__1029->SetBinContent(12,0.001894593);
   uncert_4__1029->SetBinContent(13,0.00158149);
   uncert_4__1029->SetBinContent(14,0.0016734);
   uncert_4__1029->SetBinContent(15,0.001192033);
   uncert_4__1029->SetBinContent(16,0.0007687211);
   uncert_4__1029->SetMinimum(0);
   uncert_4__1029->SetMaximum(0.2);
   uncert_4__1029->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_4__1029->SetLineColor(ci);
   uncert_4__1029->SetMarkerStyle(8);
   uncert_4__1029->GetXaxis()->SetTitle("p_{T}");
   uncert_4__1029->GetXaxis()->SetRange(1,15);
   uncert_4__1029->GetXaxis()->SetLabelFont(42);
   uncert_4__1029->GetXaxis()->SetLabelSize(0.035);
   uncert_4__1029->GetXaxis()->SetTitleSize(0.035);
   uncert_4__1029->GetXaxis()->SetTitleFont(42);
   uncert_4__1029->GetYaxis()->SetTitle("Uncertainty");
   uncert_4__1029->GetYaxis()->SetLabelFont(42);
   uncert_4__1029->GetYaxis()->SetLabelSize(0.035);
   uncert_4__1029->GetYaxis()->SetTitleSize(0.035);
   uncert_4__1029->GetYaxis()->SetTitleOffset(1.3);
   uncert_4__1029->GetYaxis()->SetTitleFont(42);
   uncert_4__1029->GetZaxis()->SetLabelFont(42);
   uncert_4__1029->GetZaxis()->SetLabelSize(0.035);
   uncert_4__1029->GetZaxis()->SetTitleSize(0.035);
   uncert_4__1029->GetZaxis()->SetTitleFont(42);
   uncert_4__1029->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","50-70%","");
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

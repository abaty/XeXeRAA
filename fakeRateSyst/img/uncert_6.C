void uncert_6()
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
   Double_t xAxis7[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_6__1031 = new TH1D("uncert_6__1031","",32, xAxis7);
   uncert_6__1031->SetBinContent(1,0.1460575);
   uncert_6__1031->SetBinContent(2,0.0802331);
   uncert_6__1031->SetBinContent(3,0.01306486);
   uncert_6__1031->SetBinContent(4,0.006178916);
   uncert_6__1031->SetBinContent(5,0.009879529);
   uncert_6__1031->SetBinContent(6,0.007172406);
   uncert_6__1031->SetBinContent(7,0.007167637);
   uncert_6__1031->SetBinContent(8,0.007306457);
   uncert_6__1031->SetBinContent(9,0.006555557);
   uncert_6__1031->SetBinContent(10,0.005798876);
   uncert_6__1031->SetBinContent(11,0.005263448);
   uncert_6__1031->SetBinContent(12,0.005851984);
   uncert_6__1031->SetBinContent(13,0.005340755);
   uncert_6__1031->SetBinContent(14,0.004342556);
   uncert_6__1031->SetBinContent(15,0.003561795);
   uncert_6__1031->SetBinContent(16,0.00236088);
   uncert_6__1031->SetMinimum(0);
   uncert_6__1031->SetMaximum(0.2);
   uncert_6__1031->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_6__1031->SetLineColor(ci);
   uncert_6__1031->SetMarkerStyle(8);
   uncert_6__1031->GetXaxis()->SetTitle("p_{T}");
   uncert_6__1031->GetXaxis()->SetRange(1,15);
   uncert_6__1031->GetXaxis()->SetLabelFont(42);
   uncert_6__1031->GetXaxis()->SetLabelSize(0.035);
   uncert_6__1031->GetXaxis()->SetTitleSize(0.035);
   uncert_6__1031->GetXaxis()->SetTitleFont(42);
   uncert_6__1031->GetYaxis()->SetTitle("Uncertainty");
   uncert_6__1031->GetYaxis()->SetLabelFont(42);
   uncert_6__1031->GetYaxis()->SetLabelSize(0.035);
   uncert_6__1031->GetYaxis()->SetTitleSize(0.035);
   uncert_6__1031->GetYaxis()->SetTitleOffset(1.3);
   uncert_6__1031->GetYaxis()->SetTitleFont(42);
   uncert_6__1031->GetZaxis()->SetLabelFont(42);
   uncert_6__1031->GetZaxis()->SetLabelSize(0.035);
   uncert_6__1031->GetZaxis()->SetTitleSize(0.035);
   uncert_6__1031->GetZaxis()->SetTitleFont(42);
   uncert_6__1031->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","0-10%","");
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

void uncert_7()
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
   Double_t xAxis8[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_7__1032 = new TH1D("uncert_7__1032","",32, xAxis8);
   uncert_7__1032->SetBinContent(1,0.03100449);
   uncert_7__1032->SetBinContent(2,0.01747024);
   uncert_7__1032->SetBinContent(3,0.003885627);
   uncert_7__1032->SetBinContent(4,0.002483666);
   uncert_7__1032->SetBinContent(5,0.004276037);
   uncert_7__1032->SetBinContent(6,0.0035941);
   uncert_7__1032->SetBinContent(7,0.003875434);
   uncert_7__1032->SetBinContent(8,0.003908515);
   uncert_7__1032->SetBinContent(9,0.00378412);
   uncert_7__1032->SetBinContent(10,0.003705442);
   uncert_7__1032->SetBinContent(11,0.003440678);
   uncert_7__1032->SetBinContent(12,0.003381431);
   uncert_7__1032->SetBinContent(13,0.003454864);
   uncert_7__1032->SetBinContent(14,0.003014922);
   uncert_7__1032->SetBinContent(15,0.00242728);
   uncert_7__1032->SetBinContent(16,0.001693547);
   uncert_7__1032->SetMinimum(0);
   uncert_7__1032->SetMaximum(0.2);
   uncert_7__1032->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_7__1032->SetLineColor(ci);
   uncert_7__1032->SetMarkerStyle(8);
   uncert_7__1032->GetXaxis()->SetTitle("p_{T}");
   uncert_7__1032->GetXaxis()->SetRange(1,15);
   uncert_7__1032->GetXaxis()->SetLabelFont(42);
   uncert_7__1032->GetXaxis()->SetLabelSize(0.035);
   uncert_7__1032->GetXaxis()->SetTitleSize(0.035);
   uncert_7__1032->GetXaxis()->SetTitleFont(42);
   uncert_7__1032->GetYaxis()->SetTitle("Uncertainty");
   uncert_7__1032->GetYaxis()->SetLabelFont(42);
   uncert_7__1032->GetYaxis()->SetLabelSize(0.035);
   uncert_7__1032->GetYaxis()->SetTitleSize(0.035);
   uncert_7__1032->GetYaxis()->SetTitleOffset(1.3);
   uncert_7__1032->GetYaxis()->SetTitleFont(42);
   uncert_7__1032->GetZaxis()->SetLabelFont(42);
   uncert_7__1032->GetZaxis()->SetLabelSize(0.035);
   uncert_7__1032->GetZaxis()->SetTitleSize(0.035);
   uncert_7__1032->GetZaxis()->SetTitleFont(42);
   uncert_7__1032->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","0-100%","");
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

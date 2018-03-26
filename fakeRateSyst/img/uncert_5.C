void uncert_5()
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
   Double_t xAxis6[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_5__1030 = new TH1D("uncert_5__1030","",32, xAxis6);
   uncert_5__1030->SetBinContent(1,0.001207352);
   uncert_5__1030->SetBinContent(2,0.002779007);
   uncert_5__1030->SetBinContent(3,0.001006007);
   uncert_5__1030->SetBinContent(4,0.001452208);
   uncert_5__1030->SetBinContent(5,0.0004277825);
   uncert_5__1030->SetBinContent(6,0.000967145);
   uncert_5__1030->SetBinContent(7,0.002634406);
   uncert_5__1030->SetBinContent(8,0.001477957);
   uncert_5__1030->SetBinContent(9,0.001838624);
   uncert_5__1030->SetBinContent(10,0.003217101);
   uncert_5__1030->SetBinContent(11,0.002840877);
   uncert_5__1030->SetBinContent(12,0.002369285);
   uncert_5__1030->SetBinContent(13,0.002068162);
   uncert_5__1030->SetBinContent(14,0.001160622);
   uncert_5__1030->SetBinContent(15,0.00218147);
   uncert_5__1030->SetBinContent(16,0.007894218);
   uncert_5__1030->SetMinimum(0);
   uncert_5__1030->SetMaximum(0.2);
   uncert_5__1030->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_5__1030->SetLineColor(ci);
   uncert_5__1030->SetMarkerStyle(8);
   uncert_5__1030->GetXaxis()->SetTitle("p_{T}");
   uncert_5__1030->GetXaxis()->SetRange(1,15);
   uncert_5__1030->GetXaxis()->SetLabelFont(42);
   uncert_5__1030->GetXaxis()->SetLabelSize(0.035);
   uncert_5__1030->GetXaxis()->SetTitleSize(0.035);
   uncert_5__1030->GetXaxis()->SetTitleFont(42);
   uncert_5__1030->GetYaxis()->SetTitle("Uncertainty");
   uncert_5__1030->GetYaxis()->SetLabelFont(42);
   uncert_5__1030->GetYaxis()->SetLabelSize(0.035);
   uncert_5__1030->GetYaxis()->SetTitleSize(0.035);
   uncert_5__1030->GetYaxis()->SetTitleOffset(1.3);
   uncert_5__1030->GetYaxis()->SetTitleFont(42);
   uncert_5__1030->GetZaxis()->SetLabelFont(42);
   uncert_5__1030->GetZaxis()->SetLabelSize(0.035);
   uncert_5__1030->GetZaxis()->SetTitleSize(0.035);
   uncert_5__1030->GetZaxis()->SetTitleFont(42);
   uncert_5__1030->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","70-90%","");
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

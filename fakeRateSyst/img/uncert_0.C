void uncert_0()
{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Mar 26 08:25:40 2018) by ROOT version6.08/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,600);
   gStyle->SetOptStat(0);
   c1->Range(0.06249997,-0.025,4.4375,0.225);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   Double_t xAxis1[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_0__1025 = new TH1D("uncert_0__1025","",32, xAxis1);
   uncert_0__1025->SetBinContent(1,0.1558393);
   uncert_0__1025->SetBinContent(2,0.1125697);
   uncert_0__1025->SetBinContent(3,0.01974744);
   uncert_0__1025->SetBinContent(4,0.008180916);
   uncert_0__1025->SetBinContent(5,0.01214069);
   uncert_0__1025->SetBinContent(6,0.008772731);
   uncert_0__1025->SetBinContent(7,0.008654475);
   uncert_0__1025->SetBinContent(8,0.009112656);
   uncert_0__1025->SetBinContent(9,0.008365452);
   uncert_0__1025->SetBinContent(10,0.006527424);
   uncert_0__1025->SetBinContent(11,0.006192207);
   uncert_0__1025->SetBinContent(12,0.006280839);
   uncert_0__1025->SetBinContent(13,0.005766511);
   uncert_0__1025->SetBinContent(14,0.004763126);
   uncert_0__1025->SetBinContent(15,0.003739178);
   uncert_0__1025->SetBinContent(16,0.003119886);
   uncert_0__1025->SetMinimum(0);
   uncert_0__1025->SetMaximum(0.2);
   uncert_0__1025->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_0__1025->SetLineColor(ci);
   uncert_0__1025->SetMarkerStyle(8);
   uncert_0__1025->GetXaxis()->SetTitle("p_{T}");
   uncert_0__1025->GetXaxis()->SetRange(1,15);
   uncert_0__1025->GetXaxis()->SetLabelFont(42);
   uncert_0__1025->GetXaxis()->SetLabelSize(0.035);
   uncert_0__1025->GetXaxis()->SetTitleSize(0.035);
   uncert_0__1025->GetXaxis()->SetTitleFont(42);
   uncert_0__1025->GetYaxis()->SetTitle("Uncertainty");
   uncert_0__1025->GetYaxis()->SetLabelFont(42);
   uncert_0__1025->GetYaxis()->SetLabelSize(0.035);
   uncert_0__1025->GetYaxis()->SetTitleSize(0.035);
   uncert_0__1025->GetYaxis()->SetTitleOffset(1.3);
   uncert_0__1025->GetYaxis()->SetTitleFont(42);
   uncert_0__1025->GetZaxis()->SetLabelFont(42);
   uncert_0__1025->GetZaxis()->SetLabelSize(0.035);
   uncert_0__1025->GetZaxis()->SetTitleSize(0.035);
   uncert_0__1025->GetZaxis()->SetTitleFont(42);
   uncert_0__1025->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","0-5%","");
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

void uncert_3()
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
   Double_t xAxis4[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *uncert_3__1028 = new TH1D("uncert_3__1028","",32, xAxis4);
   uncert_3__1028->SetBinContent(1,0.0005944371);
   uncert_3__1028->SetBinContent(2,0.0008146167);
   uncert_3__1028->SetBinContent(3,0.0003944039);
   uncert_3__1028->SetBinContent(4,0.0008614063);
   uncert_3__1028->SetBinContent(5,0.001285911);
   uncert_3__1028->SetBinContent(6,0.001505733);
   uncert_3__1028->SetBinContent(7,0.001562536);
   uncert_3__1028->SetBinContent(8,0.001873076);
   uncert_3__1028->SetBinContent(9,0.001948237);
   uncert_3__1028->SetBinContent(10,0.002282262);
   uncert_3__1028->SetBinContent(11,0.001923621);
   uncert_3__1028->SetBinContent(12,0.00191766);
   uncert_3__1028->SetBinContent(13,0.00188899);
   uncert_3__1028->SetBinContent(14,0.001671255);
   uncert_3__1028->SetBinContent(15,0.001507103);
   uncert_3__1028->SetBinContent(16,0.001405358);
   uncert_3__1028->SetMinimum(0);
   uncert_3__1028->SetMaximum(0.2);
   uncert_3__1028->SetEntries(16);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   uncert_3__1028->SetLineColor(ci);
   uncert_3__1028->SetMarkerStyle(8);
   uncert_3__1028->GetXaxis()->SetTitle("p_{T}");
   uncert_3__1028->GetXaxis()->SetRange(1,15);
   uncert_3__1028->GetXaxis()->SetLabelFont(42);
   uncert_3__1028->GetXaxis()->SetLabelSize(0.035);
   uncert_3__1028->GetXaxis()->SetTitleSize(0.035);
   uncert_3__1028->GetXaxis()->SetTitleFont(42);
   uncert_3__1028->GetYaxis()->SetTitle("Uncertainty");
   uncert_3__1028->GetYaxis()->SetLabelFont(42);
   uncert_3__1028->GetYaxis()->SetLabelSize(0.035);
   uncert_3__1028->GetYaxis()->SetTitleSize(0.035);
   uncert_3__1028->GetYaxis()->SetTitleOffset(1.3);
   uncert_3__1028->GetYaxis()->SetTitleFont(42);
   uncert_3__1028->GetZaxis()->SetLabelFont(42);
   uncert_3__1028->GetZaxis()->SetLabelSize(0.035);
   uncert_3__1028->GetZaxis()->SetTitleSize(0.035);
   uncert_3__1028->GetZaxis()->SetTitleFont(42);
   uncert_3__1028->Draw("HIST p");
   
   TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","30-50%","");
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

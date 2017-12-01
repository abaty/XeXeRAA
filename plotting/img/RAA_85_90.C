void RAA_85_90()
{
//=========Macro generated from canvas: RAA/RAA
//=========  (Fri Dec  1 16:27:05 2017) by ROOT version6.08/07
   TCanvas *RAA = new TCanvas("RAA", "RAA",1,1,800,676);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   RAA->Range(-0.7299911,-0.24,2.129749,1.76);
   RAA->SetFillColor(0);
   RAA->SetBorderMode(0);
   RAA->SetBorderSize(2);
   RAA->SetLogx();
   RAA->SetTickx(1);
   RAA->SetTicky(1);
   RAA->SetLeftMargin(0.15);
   RAA->SetRightMargin(0.04);
   RAA->SetTopMargin(0.08);
   RAA->SetBottomMargin(0.12);
   RAA->SetFrameFillStyle(0);
   RAA->SetFrameBorderMode(0);
   RAA->SetFrameFillStyle(0);
   RAA->SetFrameBorderMode(0);
   Double_t xAxis52[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *RAA_85_90__52 = new TH1D("RAA_85_90__52","HI_TaaWeighted_85_90",32, xAxis52);
   RAA_85_90__52->SetBinContent(1,0.005707526);
   RAA_85_90__52->SetBinContent(2,0.008629515);
   RAA_85_90__52->SetBinContent(3,0.01129669);
   RAA_85_90__52->SetBinContent(4,0.01271204);
   RAA_85_90__52->SetBinContent(5,0.01005571);
   RAA_85_90__52->SetBinContent(6,0.01298643);
   RAA_85_90__52->SetBinContent(7,0.01050518);
   RAA_85_90__52->SetBinContent(8,0.01009391);
   RAA_85_90__52->SetBinContent(9,0.009253768);
   RAA_85_90__52->SetBinContent(10,0.009709952);
   RAA_85_90__52->SetBinContent(11,0.007623132);
   RAA_85_90__52->SetBinContent(12,0.005528009);
   RAA_85_90__52->SetBinContent(13,0.00776994);
   RAA_85_90__52->SetBinContent(14,0.01085869);
   RAA_85_90__52->SetBinContent(15,0.001577009);
   RAA_85_90__52->SetBinContent(16,0.002121874);
   RAA_85_90__52->SetBinError(1,0.0003848122);
   RAA_85_90__52->SetBinError(2,0.0005372735);
   RAA_85_90__52->SetBinError(3,0.000706084);
   RAA_85_90__52->SetBinError(4,0.0008346453);
   RAA_85_90__52->SetBinError(5,0.0008468922);
   RAA_85_90__52->SetBinError(6,0.001074848);
   RAA_85_90__52->SetBinError(7,0.001083595);
   RAA_85_90__52->SetBinError(8,0.0008720358);
   RAA_85_90__52->SetBinError(9,0.001034662);
   RAA_85_90__52->SetBinError(10,0.001275057);
   RAA_85_90__52->SetBinError(11,0.00136922);
   RAA_85_90__52->SetBinError(12,0.00138205);
   RAA_85_90__52->SetBinError(13,0.001942579);
   RAA_85_90__52->SetBinError(14,0.001656046);
   RAA_85_90__52->SetBinError(15,0.001115125);
   RAA_85_90__52->SetBinError(16,0.0021219);
   RAA_85_90__52->SetMinimum(0);
   RAA_85_90__52->SetMaximum(1.6);
   RAA_85_90__52->SetEntries(769.6952);
   RAA_85_90__52->SetDirectory(0);
   RAA_85_90__52->SetMarkerStyle(8);
   RAA_85_90__52->SetMarkerSize(1.3);
   RAA_85_90__52->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_85_90__52->GetXaxis()->SetRange(1,32);
   RAA_85_90__52->GetXaxis()->CenterTitle(true);
   RAA_85_90__52->GetXaxis()->SetLabelFont(42);
   RAA_85_90__52->GetXaxis()->SetLabelOffset(-0.005);
   RAA_85_90__52->GetXaxis()->SetLabelSize(0.035);
   RAA_85_90__52->GetXaxis()->SetTitleSize(0.1);
   RAA_85_90__52->GetXaxis()->SetTitleOffset(1.2);
   RAA_85_90__52->GetXaxis()->SetTitleFont(42);
   RAA_85_90__52->GetYaxis()->SetTitle("R*_{AA}");
   RAA_85_90__52->GetYaxis()->CenterTitle(true);
   RAA_85_90__52->GetYaxis()->SetLabelFont(42);
   RAA_85_90__52->GetYaxis()->SetLabelSize(0.035);
   RAA_85_90__52->GetYaxis()->SetTitleSize(0.1);
   RAA_85_90__52->GetYaxis()->SetTitleOffset(1.2);
   RAA_85_90__52->GetYaxis()->SetTitleFont(42);
   RAA_85_90__52->GetZaxis()->SetLabelFont(42);
   RAA_85_90__52->GetZaxis()->SetLabelSize(0.035);
   RAA_85_90__52->GetZaxis()->SetTitleSize(0.035);
   RAA_85_90__52->GetZaxis()->SetTitleFont(42);
   RAA_85_90__52->Draw("");
   TLine *line = new TLine(0.5,1,103.6,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(0.9,0.1,"85-90%");
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.8,1.03,"T_{AA} and lumi. uncertainty");
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.8,0.93,"|#eta|<1");
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   TBox *box = new TBox(0.5,0.005136774,0.6,0.006278279);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.6,0.007766563,0.7,0.009492466);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.7,0.01016702,0.8,0.01242636);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.8,0.01144084,0.9,0.01398324);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.9,0.009050142,1,0.01106128);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1,0.01168779,1.1,0.01428508);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.1,0.009454661,1.2,0.0115557);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.2,0.009084516,1.4,0.0111033);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.4,0.008328392,1.6,0.01017915);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.6,0.008738957,1.8,0.01068095);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.8,0.006860819,2,0.008385445);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(2,0.004975208,2.2,0.00608081);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(2.2,0.006992946,2.4,0.008546934);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(2.4,0.009772819,3.2,0.01194456);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(3.2,0.001419308,4,0.00173471);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(4,0.001909687,4.8,0.002334061);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(4.8,0,5.6,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(5.6,0,6.4,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(6.4,0,7.2,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(7.2,0,9.6,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(9.6,0,12,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(12,0,14.4,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(14.4,0,19.2,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(19.2,0,24,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(24,0,28.8,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(28.8,0,35.2,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(35.2,0,41.6,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(41.6,0,48,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(48,0,60.8,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(60.8,0,73.6,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(73.6,0,86.4,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   Double_t xAxis53[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *RAA_85_90__53 = new TH1D("RAA_85_90__53","HI_TaaWeighted_85_90",32, xAxis53);
   RAA_85_90__53->SetBinContent(1,0.005707526);
   RAA_85_90__53->SetBinContent(2,0.008629515);
   RAA_85_90__53->SetBinContent(3,0.01129669);
   RAA_85_90__53->SetBinContent(4,0.01271204);
   RAA_85_90__53->SetBinContent(5,0.01005571);
   RAA_85_90__53->SetBinContent(6,0.01298643);
   RAA_85_90__53->SetBinContent(7,0.01050518);
   RAA_85_90__53->SetBinContent(8,0.01009391);
   RAA_85_90__53->SetBinContent(9,0.009253768);
   RAA_85_90__53->SetBinContent(10,0.009709952);
   RAA_85_90__53->SetBinContent(11,0.007623132);
   RAA_85_90__53->SetBinContent(12,0.005528009);
   RAA_85_90__53->SetBinContent(13,0.00776994);
   RAA_85_90__53->SetBinContent(14,0.01085869);
   RAA_85_90__53->SetBinContent(15,0.001577009);
   RAA_85_90__53->SetBinContent(16,0.002121874);
   RAA_85_90__53->SetBinError(1,0.0003848122);
   RAA_85_90__53->SetBinError(2,0.0005372735);
   RAA_85_90__53->SetBinError(3,0.000706084);
   RAA_85_90__53->SetBinError(4,0.0008346453);
   RAA_85_90__53->SetBinError(5,0.0008468922);
   RAA_85_90__53->SetBinError(6,0.001074848);
   RAA_85_90__53->SetBinError(7,0.001083595);
   RAA_85_90__53->SetBinError(8,0.0008720358);
   RAA_85_90__53->SetBinError(9,0.001034662);
   RAA_85_90__53->SetBinError(10,0.001275057);
   RAA_85_90__53->SetBinError(11,0.00136922);
   RAA_85_90__53->SetBinError(12,0.00138205);
   RAA_85_90__53->SetBinError(13,0.001942579);
   RAA_85_90__53->SetBinError(14,0.001656046);
   RAA_85_90__53->SetBinError(15,0.001115125);
   RAA_85_90__53->SetBinError(16,0.0021219);
   RAA_85_90__53->SetMinimum(0);
   RAA_85_90__53->SetMaximum(1.6);
   RAA_85_90__53->SetEntries(769.6952);
   RAA_85_90__53->SetDirectory(0);
   RAA_85_90__53->SetMarkerStyle(8);
   RAA_85_90__53->SetMarkerSize(1.3);
   RAA_85_90__53->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_85_90__53->GetXaxis()->SetRange(1,32);
   RAA_85_90__53->GetXaxis()->CenterTitle(true);
   RAA_85_90__53->GetXaxis()->SetLabelFont(42);
   RAA_85_90__53->GetXaxis()->SetLabelOffset(-0.005);
   RAA_85_90__53->GetXaxis()->SetLabelSize(0.035);
   RAA_85_90__53->GetXaxis()->SetTitleSize(0.1);
   RAA_85_90__53->GetXaxis()->SetTitleOffset(1.2);
   RAA_85_90__53->GetXaxis()->SetTitleFont(42);
   RAA_85_90__53->GetYaxis()->SetTitle("R*_{AA}");
   RAA_85_90__53->GetYaxis()->CenterTitle(true);
   RAA_85_90__53->GetYaxis()->SetLabelFont(42);
   RAA_85_90__53->GetYaxis()->SetLabelSize(0.035);
   RAA_85_90__53->GetYaxis()->SetTitleSize(0.1);
   RAA_85_90__53->GetYaxis()->SetTitleOffset(1.2);
   RAA_85_90__53->GetYaxis()->SetTitleFont(42);
   RAA_85_90__53->GetZaxis()->SetLabelFont(42);
   RAA_85_90__53->GetZaxis()->SetLabelSize(0.035);
   RAA_85_90__53->GetZaxis()->SetTitleSize(0.035);
   RAA_85_90__53->GetZaxis()->SetTitleFont(42);
   RAA_85_90__53->Draw("same");
      tex = new TLatex(0.96,0.936,"??? #mub^{-1} (5.44 TeV XeXe)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18645,0.892,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18645,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.0456);
   tex->SetLineWidth(2);
   tex->Draw();
   Double_t xAxis54[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *RAA_85_90_copy__54 = new TH1D("RAA_85_90_copy__54","HI_TaaWeighted_85_90",32, xAxis54);
   RAA_85_90_copy__54->SetBinContent(1,0.005707526);
   RAA_85_90_copy__54->SetBinContent(2,0.008629515);
   RAA_85_90_copy__54->SetBinContent(3,0.01129669);
   RAA_85_90_copy__54->SetBinContent(4,0.01271204);
   RAA_85_90_copy__54->SetBinContent(5,0.01005571);
   RAA_85_90_copy__54->SetBinContent(6,0.01298643);
   RAA_85_90_copy__54->SetBinContent(7,0.01050518);
   RAA_85_90_copy__54->SetBinContent(8,0.01009391);
   RAA_85_90_copy__54->SetBinContent(9,0.009253768);
   RAA_85_90_copy__54->SetBinContent(10,0.009709952);
   RAA_85_90_copy__54->SetBinContent(11,0.007623132);
   RAA_85_90_copy__54->SetBinContent(12,0.005528009);
   RAA_85_90_copy__54->SetBinContent(13,0.00776994);
   RAA_85_90_copy__54->SetBinContent(14,0.01085869);
   RAA_85_90_copy__54->SetBinContent(15,0.001577009);
   RAA_85_90_copy__54->SetBinContent(16,0.002121874);
   RAA_85_90_copy__54->SetBinError(1,0.0003848122);
   RAA_85_90_copy__54->SetBinError(2,0.0005372735);
   RAA_85_90_copy__54->SetBinError(3,0.000706084);
   RAA_85_90_copy__54->SetBinError(4,0.0008346453);
   RAA_85_90_copy__54->SetBinError(5,0.0008468922);
   RAA_85_90_copy__54->SetBinError(6,0.001074848);
   RAA_85_90_copy__54->SetBinError(7,0.001083595);
   RAA_85_90_copy__54->SetBinError(8,0.0008720358);
   RAA_85_90_copy__54->SetBinError(9,0.001034662);
   RAA_85_90_copy__54->SetBinError(10,0.001275057);
   RAA_85_90_copy__54->SetBinError(11,0.00136922);
   RAA_85_90_copy__54->SetBinError(12,0.00138205);
   RAA_85_90_copy__54->SetBinError(13,0.001942579);
   RAA_85_90_copy__54->SetBinError(14,0.001656046);
   RAA_85_90_copy__54->SetBinError(15,0.001115125);
   RAA_85_90_copy__54->SetBinError(16,0.0021219);
   RAA_85_90_copy__54->SetMinimum(0);
   RAA_85_90_copy__54->SetMaximum(1.6);
   RAA_85_90_copy__54->SetEntries(769.6952);
   RAA_85_90_copy__54->SetDirectory(0);
   RAA_85_90_copy__54->SetMarkerStyle(8);
   RAA_85_90_copy__54->SetMarkerSize(1.3);
   RAA_85_90_copy__54->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_85_90_copy__54->GetXaxis()->SetRange(1,32);
   RAA_85_90_copy__54->GetXaxis()->CenterTitle(true);
   RAA_85_90_copy__54->GetXaxis()->SetLabelFont(42);
   RAA_85_90_copy__54->GetXaxis()->SetLabelOffset(-0.005);
   RAA_85_90_copy__54->GetXaxis()->SetLabelSize(0.035);
   RAA_85_90_copy__54->GetXaxis()->SetTitleSize(0.1);
   RAA_85_90_copy__54->GetXaxis()->SetTitleOffset(1.2);
   RAA_85_90_copy__54->GetXaxis()->SetTitleFont(42);
   RAA_85_90_copy__54->GetYaxis()->SetTitle("R*_{AA}");
   RAA_85_90_copy__54->GetYaxis()->CenterTitle(true);
   RAA_85_90_copy__54->GetYaxis()->SetLabelFont(42);
   RAA_85_90_copy__54->GetYaxis()->SetLabelSize(0.035);
   RAA_85_90_copy__54->GetYaxis()->SetTitleSize(0.1);
   RAA_85_90_copy__54->GetYaxis()->SetTitleOffset(1.2);
   RAA_85_90_copy__54->GetYaxis()->SetTitleFont(42);
   RAA_85_90_copy__54->GetZaxis()->SetLabelFont(42);
   RAA_85_90_copy__54->GetZaxis()->SetLabelSize(0.035);
   RAA_85_90_copy__54->GetZaxis()->SetTitleSize(0.035);
   RAA_85_90_copy__54->GetZaxis()->SetTitleFont(42);
   RAA_85_90_copy__54->Draw("sameaxis");
   RAA->Modified();
   RAA->cd();
   RAA->SetSelected(RAA);
}

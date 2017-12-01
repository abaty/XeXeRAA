void RAA_90_95()
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
   Double_t xAxis55[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *RAA_90_95__55 = new TH1D("RAA_90_95__55","HI_TaaWeighted_90_95",32, xAxis55);
   RAA_90_95__55->SetBinContent(1,0.002917649);
   RAA_90_95__55->SetBinContent(2,0.006002579);
   RAA_90_95__55->SetBinContent(3,0.00638817);
   RAA_90_95__55->SetBinContent(4,0.006489965);
   RAA_90_95__55->SetBinContent(5,0.004607522);
   RAA_90_95__55->SetBinContent(6,0.004788831);
   RAA_90_95__55->SetBinContent(7,0.006417956);
   RAA_90_95__55->SetBinContent(8,0.004686383);
   RAA_90_95__55->SetBinContent(9,0.005258867);
   RAA_90_95__55->SetBinContent(10,0.004406479);
   RAA_90_95__55->SetBinContent(11,0.003530473);
   RAA_90_95__55->SetBinContent(12,0.004960322);
   RAA_90_95__55->SetBinContent(13,0.00581002);
   RAA_90_95__55->SetBinContent(14,0.001812759);
   RAA_90_95__55->SetBinContent(15,0.002830124);
   RAA_90_95__55->SetBinContent(17,0.006016917);
   RAA_90_95__55->SetBinError(1,0.0003009361);
   RAA_90_95__55->SetBinError(2,0.0004901209);
   RAA_90_95__55->SetBinError(3,0.0005807587);
   RAA_90_95__55->SetBinError(4,0.0006522857);
   RAA_90_95__55->SetBinError(5,0.0006270181);
   RAA_90_95__55->SetBinError(6,0.0007138937);
   RAA_90_95__55->SetBinError(7,0.0009263822);
   RAA_90_95__55->SetBinError(8,0.0006499003);
   RAA_90_95__55->SetBinError(9,0.000853124);
   RAA_90_95__55->SetBinError(10,0.0009394863);
   RAA_90_95__55->SetBinError(11,0.001019178);
   RAA_90_95__55->SetBinError(12,0.001431959);
   RAA_90_95__55->SetBinError(13,0.001837345);
   RAA_90_95__55->SetBinError(14,0.0007400627);
   RAA_90_95__55->SetBinError(15,0.001633996);
   RAA_90_95__55->SetBinError(17,0.006017073);
   RAA_90_95__55->SetMinimum(0);
   RAA_90_95__55->SetMaximum(1.6);
   RAA_90_95__55->SetEntries(116.5423);
   RAA_90_95__55->SetDirectory(0);
   RAA_90_95__55->SetMarkerStyle(8);
   RAA_90_95__55->SetMarkerSize(1.3);
   RAA_90_95__55->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_90_95__55->GetXaxis()->SetRange(1,32);
   RAA_90_95__55->GetXaxis()->CenterTitle(true);
   RAA_90_95__55->GetXaxis()->SetLabelFont(42);
   RAA_90_95__55->GetXaxis()->SetLabelOffset(-0.005);
   RAA_90_95__55->GetXaxis()->SetLabelSize(0.035);
   RAA_90_95__55->GetXaxis()->SetTitleSize(0.1);
   RAA_90_95__55->GetXaxis()->SetTitleOffset(1.2);
   RAA_90_95__55->GetXaxis()->SetTitleFont(42);
   RAA_90_95__55->GetYaxis()->SetTitle("R*_{AA}");
   RAA_90_95__55->GetYaxis()->CenterTitle(true);
   RAA_90_95__55->GetYaxis()->SetLabelFont(42);
   RAA_90_95__55->GetYaxis()->SetLabelSize(0.035);
   RAA_90_95__55->GetYaxis()->SetTitleSize(0.1);
   RAA_90_95__55->GetYaxis()->SetTitleOffset(1.2);
   RAA_90_95__55->GetYaxis()->SetTitleFont(42);
   RAA_90_95__55->GetZaxis()->SetLabelFont(42);
   RAA_90_95__55->GetZaxis()->SetLabelSize(0.035);
   RAA_90_95__55->GetZaxis()->SetTitleSize(0.035);
   RAA_90_95__55->GetZaxis()->SetTitleFont(42);
   RAA_90_95__55->Draw("");
   TLine *line = new TLine(0.5,1,103.6,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(0.9,0.1,"90-95%");
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
   TBox *box = new TBox(0.5,0.002625884,0.6,0.003209414);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.6,0.005402321,0.7,0.006602836);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.7,0.005749353,0.8,0.007026988);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.8,0.005840969,0.9,0.007138962);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(0.9,0.00414677,1,0.005068275);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1,0.004309948,1.1,0.005267714);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.1,0.005776161,1.2,0.007059752);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.2,0.004217744,1.4,0.005155021);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.4,0.00473298,1.6,0.005784753);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.6,0.003965831,1.8,0.004847127);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(1.8,0.003177426,2,0.00388352);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(2,0.00446429,2.2,0.005456355);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(2.2,0.005229018,2.4,0.006391022);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(2.4,0.001631483,3.2,0.001994035);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(3.2,0.002547111,4,0.003113136);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(4,0,4.8,0);

   ci = TColor::GetColor("#ff6666");
   box->SetFillColor(ci);
   box->Draw();
   box = new TBox(4.8,0.005415225,5.6,0.006618608);

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
   Double_t xAxis56[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *RAA_90_95__56 = new TH1D("RAA_90_95__56","HI_TaaWeighted_90_95",32, xAxis56);
   RAA_90_95__56->SetBinContent(1,0.002917649);
   RAA_90_95__56->SetBinContent(2,0.006002579);
   RAA_90_95__56->SetBinContent(3,0.00638817);
   RAA_90_95__56->SetBinContent(4,0.006489965);
   RAA_90_95__56->SetBinContent(5,0.004607522);
   RAA_90_95__56->SetBinContent(6,0.004788831);
   RAA_90_95__56->SetBinContent(7,0.006417956);
   RAA_90_95__56->SetBinContent(8,0.004686383);
   RAA_90_95__56->SetBinContent(9,0.005258867);
   RAA_90_95__56->SetBinContent(10,0.004406479);
   RAA_90_95__56->SetBinContent(11,0.003530473);
   RAA_90_95__56->SetBinContent(12,0.004960322);
   RAA_90_95__56->SetBinContent(13,0.00581002);
   RAA_90_95__56->SetBinContent(14,0.001812759);
   RAA_90_95__56->SetBinContent(15,0.002830124);
   RAA_90_95__56->SetBinContent(17,0.006016917);
   RAA_90_95__56->SetBinError(1,0.0003009361);
   RAA_90_95__56->SetBinError(2,0.0004901209);
   RAA_90_95__56->SetBinError(3,0.0005807587);
   RAA_90_95__56->SetBinError(4,0.0006522857);
   RAA_90_95__56->SetBinError(5,0.0006270181);
   RAA_90_95__56->SetBinError(6,0.0007138937);
   RAA_90_95__56->SetBinError(7,0.0009263822);
   RAA_90_95__56->SetBinError(8,0.0006499003);
   RAA_90_95__56->SetBinError(9,0.000853124);
   RAA_90_95__56->SetBinError(10,0.0009394863);
   RAA_90_95__56->SetBinError(11,0.001019178);
   RAA_90_95__56->SetBinError(12,0.001431959);
   RAA_90_95__56->SetBinError(13,0.001837345);
   RAA_90_95__56->SetBinError(14,0.0007400627);
   RAA_90_95__56->SetBinError(15,0.001633996);
   RAA_90_95__56->SetBinError(17,0.006017073);
   RAA_90_95__56->SetMinimum(0);
   RAA_90_95__56->SetMaximum(1.6);
   RAA_90_95__56->SetEntries(116.5423);
   RAA_90_95__56->SetDirectory(0);
   RAA_90_95__56->SetMarkerStyle(8);
   RAA_90_95__56->SetMarkerSize(1.3);
   RAA_90_95__56->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_90_95__56->GetXaxis()->SetRange(1,32);
   RAA_90_95__56->GetXaxis()->CenterTitle(true);
   RAA_90_95__56->GetXaxis()->SetLabelFont(42);
   RAA_90_95__56->GetXaxis()->SetLabelOffset(-0.005);
   RAA_90_95__56->GetXaxis()->SetLabelSize(0.035);
   RAA_90_95__56->GetXaxis()->SetTitleSize(0.1);
   RAA_90_95__56->GetXaxis()->SetTitleOffset(1.2);
   RAA_90_95__56->GetXaxis()->SetTitleFont(42);
   RAA_90_95__56->GetYaxis()->SetTitle("R*_{AA}");
   RAA_90_95__56->GetYaxis()->CenterTitle(true);
   RAA_90_95__56->GetYaxis()->SetLabelFont(42);
   RAA_90_95__56->GetYaxis()->SetLabelSize(0.035);
   RAA_90_95__56->GetYaxis()->SetTitleSize(0.1);
   RAA_90_95__56->GetYaxis()->SetTitleOffset(1.2);
   RAA_90_95__56->GetYaxis()->SetTitleFont(42);
   RAA_90_95__56->GetZaxis()->SetLabelFont(42);
   RAA_90_95__56->GetZaxis()->SetLabelSize(0.035);
   RAA_90_95__56->GetZaxis()->SetTitleSize(0.035);
   RAA_90_95__56->GetZaxis()->SetTitleFont(42);
   RAA_90_95__56->Draw("same");
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
   Double_t xAxis57[33] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 3.2, 4, 4.8, 5.6, 6.4, 7.2, 9.6, 12, 14.4, 19.2, 24, 28.8, 35.2, 41.6, 48, 60.8, 73.6, 86.4, 103.6}; 
   
   TH1D *RAA_90_95_copy__57 = new TH1D("RAA_90_95_copy__57","HI_TaaWeighted_90_95",32, xAxis57);
   RAA_90_95_copy__57->SetBinContent(1,0.002917649);
   RAA_90_95_copy__57->SetBinContent(2,0.006002579);
   RAA_90_95_copy__57->SetBinContent(3,0.00638817);
   RAA_90_95_copy__57->SetBinContent(4,0.006489965);
   RAA_90_95_copy__57->SetBinContent(5,0.004607522);
   RAA_90_95_copy__57->SetBinContent(6,0.004788831);
   RAA_90_95_copy__57->SetBinContent(7,0.006417956);
   RAA_90_95_copy__57->SetBinContent(8,0.004686383);
   RAA_90_95_copy__57->SetBinContent(9,0.005258867);
   RAA_90_95_copy__57->SetBinContent(10,0.004406479);
   RAA_90_95_copy__57->SetBinContent(11,0.003530473);
   RAA_90_95_copy__57->SetBinContent(12,0.004960322);
   RAA_90_95_copy__57->SetBinContent(13,0.00581002);
   RAA_90_95_copy__57->SetBinContent(14,0.001812759);
   RAA_90_95_copy__57->SetBinContent(15,0.002830124);
   RAA_90_95_copy__57->SetBinContent(17,0.006016917);
   RAA_90_95_copy__57->SetBinError(1,0.0003009361);
   RAA_90_95_copy__57->SetBinError(2,0.0004901209);
   RAA_90_95_copy__57->SetBinError(3,0.0005807587);
   RAA_90_95_copy__57->SetBinError(4,0.0006522857);
   RAA_90_95_copy__57->SetBinError(5,0.0006270181);
   RAA_90_95_copy__57->SetBinError(6,0.0007138937);
   RAA_90_95_copy__57->SetBinError(7,0.0009263822);
   RAA_90_95_copy__57->SetBinError(8,0.0006499003);
   RAA_90_95_copy__57->SetBinError(9,0.000853124);
   RAA_90_95_copy__57->SetBinError(10,0.0009394863);
   RAA_90_95_copy__57->SetBinError(11,0.001019178);
   RAA_90_95_copy__57->SetBinError(12,0.001431959);
   RAA_90_95_copy__57->SetBinError(13,0.001837345);
   RAA_90_95_copy__57->SetBinError(14,0.0007400627);
   RAA_90_95_copy__57->SetBinError(15,0.001633996);
   RAA_90_95_copy__57->SetBinError(17,0.006017073);
   RAA_90_95_copy__57->SetMinimum(0);
   RAA_90_95_copy__57->SetMaximum(1.6);
   RAA_90_95_copy__57->SetEntries(116.5423);
   RAA_90_95_copy__57->SetDirectory(0);
   RAA_90_95_copy__57->SetMarkerStyle(8);
   RAA_90_95_copy__57->SetMarkerSize(1.3);
   RAA_90_95_copy__57->GetXaxis()->SetTitle("p_{T} (GeV)");
   RAA_90_95_copy__57->GetXaxis()->SetRange(1,32);
   RAA_90_95_copy__57->GetXaxis()->CenterTitle(true);
   RAA_90_95_copy__57->GetXaxis()->SetLabelFont(42);
   RAA_90_95_copy__57->GetXaxis()->SetLabelOffset(-0.005);
   RAA_90_95_copy__57->GetXaxis()->SetLabelSize(0.035);
   RAA_90_95_copy__57->GetXaxis()->SetTitleSize(0.1);
   RAA_90_95_copy__57->GetXaxis()->SetTitleOffset(1.2);
   RAA_90_95_copy__57->GetXaxis()->SetTitleFont(42);
   RAA_90_95_copy__57->GetYaxis()->SetTitle("R*_{AA}");
   RAA_90_95_copy__57->GetYaxis()->CenterTitle(true);
   RAA_90_95_copy__57->GetYaxis()->SetLabelFont(42);
   RAA_90_95_copy__57->GetYaxis()->SetLabelSize(0.035);
   RAA_90_95_copy__57->GetYaxis()->SetTitleSize(0.1);
   RAA_90_95_copy__57->GetYaxis()->SetTitleOffset(1.2);
   RAA_90_95_copy__57->GetYaxis()->SetTitleFont(42);
   RAA_90_95_copy__57->GetZaxis()->SetLabelFont(42);
   RAA_90_95_copy__57->GetZaxis()->SetLabelSize(0.035);
   RAA_90_95_copy__57->GetZaxis()->SetTitleSize(0.035);
   RAA_90_95_copy__57->GetZaxis()->SetTitleFont(42);
   RAA_90_95_copy__57->Draw("sameaxis");
   RAA->Modified();
   RAA->cd();
   RAA->SetSelected(RAA);
}

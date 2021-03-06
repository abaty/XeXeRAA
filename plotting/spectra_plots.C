#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TPad.h"
#include "TFile.h"
#include "TAttPad.h"
#include "TGraph.h"
#include "TAttMarker.h"
#include "TLine.h"
#include "TAttLine.h"
#include "TColor.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TAttAxis.h"
#include "TAttText.h"
#include "TCanvas.h"
#include "TAttCanvas.h"
#include "TBox.h"
#include "TAttFill.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TFrame.h"
#include <vector>
#include <string>
#include <fstream>
#include "../Settings.h"

void spectra_plots(){
  TH1::SetDefaultSumw2();
 
  Settings s = Settings();

  TH1D * h[s.nCentBins];
  TH1D * ppSpec;
  TH1D * pp_totSyst;
  TH1D * nVtx;
  TFile * fpp = TFile::Open(Form("../%s",s.ppRefFile.c_str()),"read");
  ppSpec = (TH1D*)fpp->Get("ppScaled_WithFit");
  ppSpec->SetDirectory(0);
  pp_totSyst = (TH1D*)fpp->Get("ppScaledSyst_NoLumi");
  pp_totSyst->SetLineColor(kBlack);
  pp_totSyst->SetLineWidth(2);
  pp_totSyst->SetFillStyle(3003);
  pp_totSyst->SetFillColor(kBlack);
  pp_totSyst->SetDirectory(0);
  TFile * f = TFile::Open("../output_0.root","read");
  nVtx = (TH1D*)f->Get("nVtxMoreBin");
  for(int c = 0; c<s.nCentBins; c++){
    h[c] = (TH1D*)f->Get(Form("HI_%d_%d",s.lowCentBin[c]*5,s.highCentBin[c]*5));
    h[c]->Scale(1.0/nVtx->GetBinContent(nVtx->GetXaxis()->FindBin(c)));
    h[c]->SetDirectory(0);
    h[c]->Print("All");
    /*XeXe_totSyst[c] = (TH1D*)h[c]->Clone(Form("spectra_syst_%d_%d",s.lowCentBin[c]*5,s.highCentBin[c]*5));
    XeXe_totSyst[c]->Reset();
    XeXe_totSyst[c]->SetDirectory(0);
    XeXe_totSyst[c]->SetLineColor(kBlack);
    XeXe_totSyst[c]->SetLineWidth(2);*/
  }
  f->Close();

  TFile * sysFile = TFile::Open("../systematics.root","read");
  TH1D * XeXe_totSyst[s.nCentBins];
  TH1D * evtSelSyst[s.nCentBins];
  //XeXe systematic
  for(int c = 0; c<s.nCentBins; c++){
    XeXe_totSyst[c] = (TH1D*)sysFile->Get(Form("spec_Total_%d",c));
    XeXe_totSyst[c]->SetDirectory(0);
    XeXe_totSyst[c]->SetLineColor(kBlack);
    XeXe_totSyst[c]->SetLineWidth(2);
    evtSelSyst[c] = (TH1D*)sysFile->Get(Form("spec_EventSelection_%d",c));
    evtSelSyst[c]->SetDirectory(0);
  }
  
  //pp systematic
  for(int i = 1; i<pp_totSyst->GetSize()-1; i++){
    pp_totSyst->SetBinError(i,0);
    if(i>ppSpec->GetSize()-1){
      pp_totSyst->SetBinContent(i,0);
    }
  }

  setTDRStyle();

  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  
  TCanvas * canv2 = new TCanvas("canv2","canv2",700,800);
  canv2->SetBorderSize(0);
  TPad * pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0,0);
  TPad * pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.25,0);
  canv2->SetLineWidth(0);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.15);
  pad1->SetTopMargin(0.07);
  pad1->SetBorderSize(0);
  pad1->Draw();
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.3);
  pad2->SetBorderSize(0);
  pad2->Draw();
  pad1->cd();
  pad1->SetLogx();
  pad1->SetLogy();
  //pbpbSpec[0]->GetXaxis()->SetRangeUser(0.7,150);
  TH1D * ppSpecD = new TH1D("specDummy1","",3,0.4,150);
  ppSpecD->GetXaxis()->SetRangeUser(0.4,150);
  ppSpecD->GetYaxis()->SetTitle("#frac{1}{N_{evt}} E #frac{d^{3}N}{dp^{3}} (GeV^{-2})");
  ppSpecD->GetYaxis()->SetTitleOffset(1.4);
  ppSpecD->GetYaxis()->SetTitleSize(0.045);
  ppSpecD->GetYaxis()->SetLabelSize(0.04);
  ppSpecD->GetYaxis()->CenterTitle();
  ppSpecD->GetYaxis()->SetLabelOffset(0.002);
  ppSpecD->GetYaxis()->SetRangeUser(1.1e-14,1e7);
  ppSpecD->GetXaxis()->SetRangeUser(0.4,150);
  ppSpecD->Draw();

  ppSpec->SetMarkerStyle(5);
  ppSpec->Scale(1/70.0);//scaled by inelastic xsection of 70 mb
  ppSpec->Draw("same");

  h[0]->SetMarkerStyle(5);
  h[0]->Draw("same");
  h[0]->GetXaxis()->SetRangeUser(0.5,150);
  h[0]->SetMarkerStyle(24);
  h[0]->Scale(10);
  h[0]->Draw("same");
  h[1]->SetMarkerColor(kBlue);
  h[1]->SetLineColor(kBlue);
  h[1]->SetMarkerStyle(25);
  h[1]->Scale(3);
  h[1]->GetXaxis()->SetRangeUser(0.5,150);
  h[1]->Draw("same");
  h[23]->SetMarkerColor(kRed);
  h[23]->SetLineColor(kRed);
  h[23]->SetMarkerStyle(28);
  h[23]->GetXaxis()->SetRangeUser(0.5,150);
  h[23]->Draw("same");
  h[24]->SetMarkerStyle(20);
  h[24]->GetXaxis()->SetRangeUser(0.5,150);
  h[25]->SetMarkerColor(kBlue);
  h[25]->SetLineColor(kBlue);
  h[24]->Draw("same");
  h[25]->SetMarkerStyle(21);
  h[25]->GetXaxis()->SetRangeUser(0.5,150);
  h[25]->Draw("same");

  //zero out two high-pt points with poor errors
  h[25]->SetBinContent(29,0);
  h[25]->SetBinContent(29,0);
  
  h[30]->SetBinContent(28,0);
  h[30]->SetBinContent(29,0);
  h[30]->SetBinContent(30,0);
  h[30]->SetBinContent(31,0);
  h[30]->SetBinContent(32,0);
  h[30]->SetBinContent(28,0);
  h[30]->SetBinError(29,0);
  h[30]->SetBinError(30,0);
  h[30]->SetBinError(31,0);
  h[30]->SetBinError(32,0);

  h[30]->SetMarkerColor(kRed);
  h[30]->SetLineColor(kRed);
  h[30]->SetMarkerStyle(34);
  h[30]->GetXaxis()->SetRangeUser(0.5,150);
  h[30]->Draw("same");


  TLegend * specLeg = new TLegend(0.6,0.52,1,0.9);
  //specLeg->SetFillStyle(0);
  specLeg->AddEntry((TObject*)0,"|#eta| < 1",""); 
  specLeg->AddEntry(h[0],Form("0-5%s (x10)","%"),"p");  
  specLeg->AddEntry(h[1],Form("5-10%s (x3)","%"),"p");  
  specLeg->AddEntry(h[23],Form("10-30%s","%"),"p");  
  specLeg->AddEntry(h[24],Form("30-50%s","%"),"p");  
  specLeg->AddEntry(h[25],Form("50-70%s","%"),"p");  
  specLeg->AddEntry(h[30],Form("70-80%s","%"),"p");  
  specLeg->AddEntry(ppSpec,"Extrapolated pp","p"); 
  specLeg->SetFillStyle(0);
  specLeg->Draw("same"); 
  TLegend * specLeg_norm = new TLegend(0.28,0.03,0.63,0.43);
  //specLeg->SetFillStyle(0);
 
  pad2->cd();
  pad2->SetLogx();
  TH1D * ppSpecD2 = new TH1D("specDummy2","",3,0.4,150);
  ppSpecD2->GetYaxis()->SetRangeUser(0.0,19.999);
  ppSpecD2->GetYaxis()->SetNdivisions(4,4,0,kTRUE);
  ppSpecD2->GetYaxis()->SetTitleOffset(0.4);
  ppSpecD2->GetYaxis()->SetTitleFont(42);
  ppSpecD2->GetYaxis()->SetTitleSize(0.095*1.2);
  ppSpecD2->GetYaxis()->SetLabelSize(0.095*1.2);
  ppSpecD2->GetXaxis()->SetTitleFont(42);
  ppSpecD2->GetYaxis()->SetTitle(Form("Syst. uncert. (%s)","%"));
  ppSpecD2->GetXaxis()->SetRangeUser(0.4,150);
  ppSpecD2->GetXaxis()->SetTitle("p_{T} (GeV)");
  ppSpecD2->GetXaxis()->SetTitleSize(0.1*1.2);
  ppSpecD2->GetXaxis()->SetLabelSize(0.1*1.2);
  ppSpecD2->GetXaxis()->SetTitleOffset(1.2);
  ppSpecD2->GetXaxis()->CenterTitle();
  ppSpecD2->GetXaxis()->SetTickLength(0.06);
  ppSpecD2->Draw();

  XeXe_totSyst[0]->Scale(100);
  XeXe_totSyst[0]->SetFillColor(kRed-7);
  XeXe_totSyst[0]->GetXaxis()->SetRangeUser(0.5,150);
  XeXe_totSyst[0]->Print("All");
  XeXe_totSyst[0]->Draw("same hist");
  XeXe_totSyst[30]->SetFillColor(kBlue);
  XeXe_totSyst[30]->SetFillStyle(3004);
  XeXe_totSyst[30]->Scale(100);
  XeXe_totSyst[30]->GetXaxis()->SetRangeUser(0.5,150);
  XeXe_totSyst[30]->Draw("same hist");

  XeXe_totSyst[25]->SetBinContent(29,0);
  XeXe_totSyst[25]->SetBinContent(29,0);
  
  XeXe_totSyst[30]->SetBinContent(28,0);
  XeXe_totSyst[30]->SetBinError(28,0);

  XeXe_totSyst[30]->SetBinContent(29,0);  
  XeXe_totSyst[30]->SetBinContent(30,0);  
  XeXe_totSyst[30]->SetBinContent(31,0);  
  XeXe_totSyst[30]->SetBinContent(32,0);  
  XeXe_totSyst[30]->SetBinError(29,0);  
  XeXe_totSyst[30]->SetBinError(30,0);  
  XeXe_totSyst[30]->SetBinError(31,0);  
  XeXe_totSyst[30]->SetBinError(32,0);  

  pp_totSyst->SetFillColor(kBlack);
  pp_totSyst->SetFillStyle(3003);
  pp_totSyst->GetXaxis()->SetRangeUser(0.5,150);
  pp_totSyst->Scale(100);
  pp_totSyst->Draw("same");

  //normalization
  /*TH1D * ppNorm = new TH1D("ppNorm","",2,110,140);
  ppNorm->SetBinContent(1,2.3);
  ppNorm->SetBinContent(2,0);
  ppNorm->SetFillColor(kBlack);
  ppNorm->SetFillStyle(3003);
  ppNorm->SetLineWidth(2);
  ppNorm->Draw("same hist");
  TH1D * centNorm = new TH1D("centNorm","",2,125,165);
  centNorm->SetBinContent(1,evtSelSyst[0]->GetBinContent(2)*100);
  centNorm->SetBinContent(2,0);
  centNorm->SetFillColor(kRed-7);
  centNorm->SetLineWidth(2);
  centNorm->Draw("same hist");
  TH1D * periNorm = new TH1D("periNorm","",2,145,195);
  periNorm->SetBinContent(1,evtSelSyst[30]->GetBinContent(2)*100);
  periNorm->SetBinContent(2,0);
  periNorm->SetFillColor(kBlue);
  periNorm->SetLineWidth(2);
  periNorm->SetFillStyle(3004);
  periNorm->Draw("same hist");
  TLatex * lat = new TLatex();
  lat->SetTextSize(0.06);
  lat->DrawLatex(54,15,"Normalization");
  lat->DrawLatex(55,12,"uncertainties");
  */

  /*TLegend * systLeg = new TLegend(0.3,0.75,0.95,0.87);
  systLeg->SetNColumns(3);*/
  pad1->cd(); 
  TLegend * systLeg = new TLegend(0.2,0.03,0.6,0.27);
  systLeg->SetFillStyle(0);
  systLeg->AddEntry((TObject*)0,"","");
  systLeg->AddEntry(XeXe_totSyst[0],Form("0-5%s","%"),"f");
  systLeg->AddEntry(XeXe_totSyst[30],Form("70-80%s","%"),"f");
  systLeg->AddEntry(pp_totSyst,"pp","f");
  systLeg->SetFillStyle(0);
  systLeg->SetLineColor(kBlack);
  gStyle->SetPadTickY(1);
  systLeg->Draw("same");
  TLegend * systLeg2 = new TLegend(0.15,0.03,0.7,0.27);
  systLeg2->SetFillStyle(0);
  systLeg2->SetTextAlign(22);
  systLeg2->AddEntry((TObject*)0,"Normalization uncertainty","");
  systLeg2->AddEntry((TObject*)0,Form("%.1f%%",evtSelSyst[0]->GetBinContent(2)*100),"");
  systLeg2->AddEntry((TObject*)0,Form("%.0f%%",evtSelSyst[30]->GetBinContent(2)*100),"");
  systLeg2->AddEntry((TObject*)0,"2.3%","");
  systLeg2->SetFillStyle(0);
  systLeg2->Draw("same");
  pad2->cd();

  ppSpecD2->Draw("sameaxis");
  ppSpecD2->GetXaxis()->Draw("same");
  

  int iPeriod = 0;
  lumi_sqrtS = "27.4 pb^{-1} (5.02 TeV pp) + 3.42 #mub^{-1} (5.44 TeV XeXe)";
  writeExtraText = false;  
  //extraText  = "Preliminary";
  //extraText  = "Unpublished";
  CMS_lumi( canv2, 0,11);

  canv2->SaveAs("img/spectra_XeXe.pdf");
  canv2->SaveAs("img/spectra_XeXe.png");
  canv2->SaveAs("img/spectra_XeXe.C");

}


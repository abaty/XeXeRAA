#include "../Settings.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TPad.h"
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

void ppRefAnalyzer(){
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);

  Settings s;


  TFile * f = TFile::Open("pp5TeV_FromRAA.root","read");
  TH1D * ppSpec = (TH1D*) f->Get("Table 7/Hist1D_y1");
  TH1D * ppSpec_stat = (TH1D*) f->Get("Table 7/Hist1D_y1_e1");
  TH1D * ppSpec_syst = (TH1D*) f->Get("Table 7/Hist1D_y1_e2plus");
  TH1D * ppSpec_lumi = (TH1D*) f->Get("Table 7/Hist1D_y1_e3");

  TFile * fpythia = TFile::Open("MCFiles/Pythia8Spectra.root","read");
  TH1D * pythia8_fromFile = (TH1D*)fpythia->Get("pythia8");

  TH1D * pp5 = new TH1D("pp5","pp5",s.ntrkBins,s.xtrkbins);
  TH1D * pp5Syst = new TH1D("pp5Syst","pp5Syst",s.ntrkBins,s.xtrkbins);
  TH1D * pp5relSyst = new TH1D("pp5relSyst","pp5relSyst",s.ntrkBins,s.xtrkbins);
  TH1D * pp5relSyst_plus1 = new TH1D("pp5relSyst_plus1","pp5relSyst_plus1",s.ntrkBins,s.xtrkbins);
  TH1D * pp5relSyst_minus1 = new TH1D("pp5relSyst_minus1","pp5relSyst_minus1",s.ntrkBins,s.xtrkbins);

  TH1D * pythia8_5 = new TH1D("pythia8_5","pythia8_5",s.ntrkBins,s.xtrkbins);
  TH1D * EPOS5 = new TH1D("EPOS_5","EPOS_5",s.ntrkBins,s.xtrkbins);
  TH1D * pythia8_5rat;
  TH1D * EPOS5rat;

  for(int i = 1; i<pp5->GetSize()-1; i++){
    pp5->SetBinContent(i,ppSpec->GetBinContent(i));
    pp5Syst->SetBinContent(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5));
    pp5relSyst->SetBinContent(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5)/pp5->GetBinContent(i));
    pp5relSyst_plus1->SetBinContent(i,1.+TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5)/pp5->GetBinContent(i));
    pp5relSyst_minus1->SetBinContent(i,1.-TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5)/pp5->GetBinContent(i));
  
    pythia8_5->SetBinContent(i,pythia8_fromFile->GetBinContent(i));
    pythia8_5->SetBinError(i,pythia8_fromFile->GetBinError(i));
    EPOS5->SetBinContent(i,70*0.8*pp5->GetBinContent(i));//FIXME
    EPOS5->SetBinError(i,70*0.05*pp5->GetBinContent(i));//FIXME
  }

  pp5->Scale(70);
  pp5Syst->Scale(70);
  pythia8_5rat = (TH1D*)pythia8_5->Clone("pythia8_5rat");
  pythia8_5rat->Divide(pp5);
  EPOS5rat = (TH1D*)EPOS5->Clone("EPOS5rat");
  EPOS5rat->Divide(pp5);

  TCanvas * canv2 = new TCanvas("canv2","canv2",700,800);
  canv2->SetBorderSize(0);

  TPad * pad1 = new TPad("pad1","pad1",0.0,0.3,1.0,1.0,0);
  TPad * pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.3,0);
  canv2->SetLineWidth(0);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.15);
  pad1->SetTopMargin(0.08);
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
  
  TH1D * ppSpecD = new TH1D("specDummy1","",3,0.4,130);
  ppSpecD->GetXaxis()->SetRangeUser(0.4,130);
  ppSpecD->GetYaxis()->SetTitle("E #frac{d^{3}#sigma}{dp^{3}} (mb/GeV^{2})");
  ppSpecD->GetYaxis()->SetTitleOffset(1.4);
  ppSpecD->GetYaxis()->SetTitleSize(0.045);
  ppSpecD->GetYaxis()->SetLabelSize(0.04);
  ppSpecD->GetYaxis()->CenterTitle();
  ppSpecD->GetYaxis()->SetLabelOffset(0.002);
  ppSpecD->GetYaxis()->SetRangeUser(1.1e-12,1e4);
  ppSpecD->GetXaxis()->SetRangeUser(0.4,130);
  ppSpecD->Draw();
  pp5->SetMarkerStyle(5);
  pp5->Draw("same p");
  pythia8_5->Scale(3);
  pythia8_5->SetMarkerStyle(4);
  pythia8_5->SetMarkerColor(kRed);
  pythia8_5->SetLineColor(kRed);
  pythia8_5->Draw("same p");
  EPOS5->Scale(10);
  EPOS5->SetMarkerStyle(25);
  EPOS5->SetMarkerColor(kBlue);
  EPOS5->SetLineColor(kBlue);
  EPOS5->Draw("same p"); 
 
  TLegend * specLeg = new TLegend(0.25,0.1,0.45,0.5);
  specLeg->AddEntry((TObject*)0,"|#eta|<1",""); 
  specLeg->AddEntry(pp5,"pp 5 TeV Data","p"); 
  specLeg->AddEntry(pythia8_5,"Pythia 8 (x3)","p"); 
  specLeg->AddEntry(EPOS5,"EPOS LHC (x10)","p"); 
  specLeg->Draw("same"); 

  pad2->cd();
  pad2->SetLogx();
  TH1D * ppSpecD2 = new TH1D("specDummy2","",3,0.4,130);
  ppSpecD2->GetYaxis()->SetRangeUser(0,2.0);
  ppSpecD2->GetYaxis()->SetNdivisions(4,4,0,kTRUE);
  ppSpecD2->GetYaxis()->SetTitleOffset(0.6);
  ppSpecD2->GetYaxis()->SetTitleFont(42);
  ppSpecD2->GetYaxis()->SetTitleSize(0.095);
  ppSpecD2->GetYaxis()->SetLabelSize(0.095);
  ppSpecD2->GetXaxis()->SetTitleFont(42);
  ppSpecD2->GetYaxis()->SetTitle(Form("MC/Data"));
  ppSpecD2->GetYaxis()->CenterTitle();
  ppSpecD2->GetXaxis()->SetRangeUser(0.4,130);
  ppSpecD2->GetXaxis()->SetTitle("p_{T} (GeV)");
  ppSpecD2->GetXaxis()->SetTitleSize(0.1);
  ppSpecD2->GetXaxis()->SetLabelSize(0.1);
  ppSpecD2->GetXaxis()->SetTitleOffset(1.2);
  ppSpecD2->GetXaxis()->CenterTitle();
  ppSpecD2->GetXaxis()->SetTickLength(0.06);
  ppSpecD2->Draw();
  pp5relSyst_plus1->SetFillColor(kGray);
  pp5relSyst_plus1->SetLineWidth(0);
  //pp5relSyst->SetFillStyle(3003);
  pp5relSyst_plus1->GetXaxis()->SetRangeUser(0.4,130);
  pp5relSyst_minus1->SetFillColor(10);
  pp5relSyst_minus1->SetFillStyle(1001);
  pp5relSyst_minus1->SetLineWidth(0);
  pp5relSyst_minus1->GetXaxis()->SetRangeUser(0.4,130);
  pp5relSyst_plus1->Draw("same hist ][");
  pp5relSyst_minus1->Draw("same hist ][");
  pythia8_5rat->SetLineColor(kRed);
  pythia8_5rat->SetMarkerSize(0);
  pythia8_5rat->SetLineWidth(2);
  EPOS5rat->SetLineColor(kBlue);
  EPOS5rat->SetLineStyle(2);
  EPOS5rat->SetLineWidth(2);
  EPOS5rat->SetMarkerSize(0);


  TLegend * systLeg = new TLegend(0.6,0.75,0.9,0.98);
  //systLeg->SetFillStyle(0);
  systLeg->AddEntry(pp5relSyst_plus1,"Data Uncertainty","f");
  systLeg->Draw("same");
  ppSpecD2->Draw("sameaxis");
  ppSpecD2->GetXaxis()->Draw("same");
  pythia8_5rat->Draw("h same ][");
  EPOS5rat->Draw("hist same c");

  TLine * line3 = new TLine(0.4,1,130,1);
  line3->SetLineWidth(1);
  line3->SetLineStyle(3);
  line3->Draw("same");
  
  /*
  lumi_sqrtS = "27.4 pb^{-1} (5.02 TeV pp)";
  writeExtraText = true;  
  extraText  = "Preliminary";
  //extraText  = "Unpublished";
  CMS_lumi(pad1, 0,33);
  canv2->Update();
  */

  canv2->SaveAs("img/Spectra_perEventYield.png");
  canv2->SaveAs("img/Spectra_perEventYield.pdf");
  canv2->SaveAs("img/Spectra_perEventYield.C");

}

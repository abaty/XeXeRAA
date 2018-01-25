#include "../Settings.h"
#include "HIN1515HyperonCorr/hyperonCorrection.C"
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

void ppRefAnalyzer(bool doRemoveHyperonCorr = false){
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

  TFile * fpythia = TFile::Open("PythiaMCFiles/Pythia8Spectra.root","read");
  TH1D * pythia8_fromFile = (TH1D*)fpythia->Get("pythia8");
  TH1D * pythia8_544 = (TH1D*)fpythia->Get("pythia8_544");
  TH1D * pythia8_7 = (TH1D*)fpythia->Get("pythia8_7");

  TFile * fEPOS = TFile::Open("EPOSMCFiles/EPOSSpectra.root","read");
  TH1D * EPOS5 = (TH1D*)fEPOS->Get("EPOS_5");
  TH1D * EPOS544 = (TH1D*)fEPOS->Get("EPOS_544");
  TH1D * EPOS7 = (TH1D*)fEPOS->Get("EPOS_7");
  
  TFile * fHerw = TFile::Open("HerwigMCFiles/HerwigppSpectra.root","read");
  //TFile * fHerw = TFile::Open("HerwigMCFiles/HerwigppSpectra_Dec205TeVMBOnly.root","read");
  TH1D * Herw5 = (TH1D*)fHerw->Get("Herwigpp_5");
  TH1D * Herw544 = (TH1D*)fHerw->Get("Herwigpp_544");

  TFile * output = TFile::Open("ppRef_Extrapolated.root","recreate");

  TH1D * pp5 = new TH1D("pp5","pp5",s.ntrkBins,s.xtrkbins);
  TH1D * pp5NoError = new TH1D("pp5","pp5",s.ntrkBins,s.xtrkbins);
  TH1D * pp5Syst = new TH1D("pp5Syst","pp5Syst",s.ntrkBins,s.xtrkbins);
  TH1D * pp5relSyst = new TH1D("pp5relSyst","pp5relSyst",s.ntrkBins,s.xtrkbins);
  TH1D * pp5relSyst_plus1 = new TH1D("pp5relSyst_plus1","pp5relSyst_plus1",s.ntrkBins,s.xtrkbins);
  TH1D * pp5relSyst_minus1 = new TH1D("pp5relSyst_minus1","pp5relSyst_minus1",s.ntrkBins,s.xtrkbins);

  TH1D * pythia8_5 = new TH1D("pythia8_5","pythia8_5",s.ntrkBins,s.xtrkbins);
  //TH1D * pythia8_544 = new TH1D("pythia8_544","pythia8_544",s.ntrkBins,s.xtrkbins);
  //TH1D * EPOS5 = new TH1D("EPOS_5","EPOS_5",s.ntrkBins,s.xtrkbins);
  TH1D * pythia8_5rat;
  TH1D * EPOS5rat;
  TH1D * EPOS5scaled;
  TH1D * Herw5rat;
  TH1D * Herw5scaled;

  TH1D * extrapFactorPythia;
  TH1D * extrapFactorEPOS;
  TH1D * extrapFactorHerw;

  for(int i = 1; i<pp5->GetSize()-1; i++){
    pp5->SetBinContent(i,ppSpec->GetBinContent(i));
    pp5->SetBinError(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5));
    pp5NoError->SetBinContent(i,ppSpec->GetBinContent(i));
    pp5Syst->SetBinContent(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5));
    pp5relSyst->SetBinContent(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5)/pp5->GetBinContent(i));
    pp5relSyst_plus1->SetBinContent(i,1.+TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5)/pp5->GetBinContent(i));
    pp5relSyst_minus1->SetBinContent(i,1.-TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2)+TMath::Power(ppSpec_stat->GetBinContent(i),2),0.5)/pp5->GetBinContent(i));
  
    pythia8_5->SetBinContent(i,pythia8_fromFile->GetBinContent(i));
    pythia8_5->SetBinError(i,pythia8_fromFile->GetBinError(i));
    //pythia8_544->SetBinError(i,pythia8_544->GetBinError(i));
    //pythia8_544->SetBinError(i,pythia8_544->GetBinError(i));
    //EPOS5->SetBinContent(i,70*0.8*pp5->GetBinContent(i));//FIXME
    //EPOS5->SetBinError(i,70*0.05*pp5->GetBinContent(i));//FIXME
  }

  pp5->Scale(70);
  pp5Syst->Scale(70);
  pp5NoError->Scale(70);
  pythia8_5rat = (TH1D*)pythia8_5->Clone("pythia8_5rat");
  pythia8_5rat->Divide(pp5NoError);
  EPOS5scaled = (TH1D*)EPOS5->Clone("EPOS5scaled");
  EPOS5rat = (TH1D*)EPOS5->Clone("EPOS5rat");
  EPOS5rat->Divide(pp5NoError);
  Herw5scaled = (TH1D*)Herw5->Clone("Herw5scaled");
  Herw5rat = (TH1D*)Herw5->Clone("Herw5rat");
  Herw5rat->Divide(pp5NoError);

  TH1D * hyperonCorr;
  if(doRemoveHyperonCorr){
    hyperonCorr = (TH1D*)pp5->Clone("hyperonPbPb");
    returnHyperonCorrection(1,hyperonCorr,1,"HIN1515HyperonCorr/");
    pp5->Divide(hyperonCorr);
    pp5NoError->Divide(hyperonCorr);
    for(int i = 1; i<pp5->GetSize()-1; i++){
      pp5relSyst->SetBinContent(i,TMath::Power(pp5relSyst->GetBinContent(i)*pp5relSyst->GetBinContent(i)-(hyperonCorr->GetBinContent(i)-1)*(hyperonCorr->GetBinContent(i)-1),0.5));
      pp5Syst->SetBinContent(i,TMath::Power(pp5Syst->GetBinContent(i)*pp5Syst->GetBinContent(i)-(hyperonCorr->GetBinContent(i)-1)*(hyperonCorr->GetBinContent(i)-1)*pp5->GetBinContent(i)*pp5->GetBinContent(i),0.5));
    }
  }

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
  EPOS5scaled->Scale(10);
  EPOS5scaled->SetMarkerStyle(25);
  EPOS5scaled->SetMarkerColor(kBlue);
  EPOS5scaled->SetLineColor(kBlue);
  EPOS5scaled->Draw("same p"); 
  Herw5scaled->Scale(30);
  Herw5scaled->SetMarkerStyle(28);
  Herw5scaled->SetMarkerColor(kMagenta);
  Herw5scaled->SetLineColor(kMagenta);
  Herw5scaled->Draw("same p"); 
 
  TLegend * specLeg = new TLegend(0.25,0.1,0.45,0.5);
  specLeg->AddEntry((TObject*)0,"|#eta|<1",""); 
  specLeg->AddEntry(pp5,"pp 5 TeV Data","p"); 
  specLeg->AddEntry(pythia8_5,"Pythia 8 (x3)","p"); 
  specLeg->AddEntry(EPOS5scaled,"EPOS LHC (x10)","p"); 
  specLeg->AddEntry(Herw5scaled,"Herwig++ (x30)","p"); 
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
  EPOS5rat->SetLineStyle(1);
  EPOS5rat->SetLineWidth(2);
  EPOS5rat->SetMarkerSize(0);
  Herw5rat->SetLineColor(kMagenta);
  Herw5rat->SetLineStyle(1);
  Herw5rat->SetLineWidth(2);
  Herw5rat->SetMarkerSize(0);

  TLegend * systLeg = new TLegend(0.3,0.75,0.6,0.98);
  //systLeg->SetFillStyle(0);
  systLeg->AddEntry(pp5relSyst_plus1,"Data Uncertainty","f");
  systLeg->Draw("same");
  ppSpecD2->Draw("sameaxis");
  ppSpecD2->GetXaxis()->Draw("same");
  EPOS5rat->Draw("h same ][");
  Herw5rat->Draw("h same ][");
  pythia8_5rat->Draw("h same ][");

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

  
  TCanvas * c3 = new TCanvas("c3","c3",800,600);
  extrapFactorPythia = (TH1D*)pythia8_544->Clone("extrapFactorPythia");
  extrapFactorPythia->Divide(pythia8_fromFile);
  extrapFactorPythia->SetLineColor(kRed);
  extrapFactorPythia->SetMarkerColor(kRed);
  extrapFactorPythia->SetMarkerStyle(8);
  extrapFactorPythia->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorPythia->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorPythia->GetXaxis()->SetTitle("p_{T}");
  extrapFactorPythia->SetTitle("");
  //extrapFactorPythia->Draw();
  extrapFactorEPOS = (TH1D*)EPOS544->Clone("extrapFactorEPOS");
  extrapFactorEPOS->Divide(EPOS5);
  extrapFactorEPOS->SetLineColor(kBlue);
  extrapFactorEPOS->SetMarkerColor(kBlue);
  extrapFactorEPOS->SetMarkerStyle(8);
  extrapFactorEPOS->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorEPOS->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorEPOS->GetXaxis()->SetTitle("p_{T}");
  extrapFactorEPOS->SetTitle("");
  extrapFactorEPOS->Draw("same");
  
  extrapFactorHerw = (TH1D*)Herw544->Clone("extrapFactorHerw");
  extrapFactorHerw->Divide(Herw5);
  extrapFactorHerw->SetLineColor(kMagenta);
  extrapFactorHerw->SetMarkerColor(kMagenta);
  extrapFactorHerw->SetMarkerStyle(28);
  extrapFactorHerw->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorHerw->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorHerw->GetXaxis()->SetTitle("p_{T}");
  extrapFactorHerw->SetTitle("");
  extrapFactorHerw->Draw("same");

  extrapFactorPythia->Draw("same");

  TLegend * specLeg2 = new TLegend(0.2,0.7,0.4,0.85);
  specLeg2->AddEntry(extrapFactorPythia,"Pythia 8","p");
  specLeg2->AddEntry(extrapFactorEPOS,"EPOS LHC","p");
  specLeg2->AddEntry(extrapFactorHerw,"Herwig++","p");
  specLeg2->Draw("same");
  
  c3->SaveAs("img/extrapolationFactorPythia8.png");
  c3->SaveAs("img/extrapolationFactorPythia8.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8.C");
  c3->SetLogx();
  c3->SaveAs("img/extrapolationFactorPythia8Logx.png");
  c3->SaveAs("img/extrapolationFactorPythia8Logx.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8Logx.C");

  //******************************************************************************************
  //******************************************************************************************
  //plots for 7 TeV comparisons
  TFile * pp7TeVFile = TFile::Open("interpolation/binned7TeV.root","read");
  TH1D * pp7 = (TH1D*)pp7TeVFile->Get("pp7");
  TH1D * pp7NoError = (TH1D*)pp7->Clone("pp7NoError");
  for(int i = 0; i<pp7NoError->GetSize(); i++) pp7NoError->SetBinError(i,0);
  TH1D * pp7relSyst_plus1 = new TH1D("pp7relSyst_plus1","pp7relSyst_plus1",s.ntrkBins,s.xtrkbins);
  TH1D * pp7relSyst_minus1 = new TH1D("pp7relSyst_minus1","pp7relSyst_minus1",s.ntrkBins,s.xtrkbins);
  for(int i = 0; i<pp7->GetSize()-2;i++){
    pp7relSyst_plus1->SetBinContent(i+1,1+pp7->GetBinError(i+1)/pp7->GetBinContent(i+1));
    pp7relSyst_minus1->SetBinContent(i+1,1-pp7->GetBinError(i+1)/pp7->GetBinContent(i+1));
  }


  TH1D* pythia8_7scaled = (TH1D*)pythia8_7->Clone("pythia8_7scaled");
  TH1D* pythia8_7rat = (TH1D*)pythia8_7->Clone("pythia8_7rat");
  pythia8_7rat->Divide(pp7NoError);
  TH1D* EPOS7scaled = (TH1D*)EPOS7->Clone("EPOS7scaled");
  TH1D* EPOS7rat = (TH1D*)EPOS7->Clone("EPOS7rat");
  EPOS7rat->Divide(pp7NoError);
  /*Herw7scaled = (TH1D*)Herw7->Clone("Herw7scaled");
  Herw7rat = (TH1D*)Herw7->Clone("Herw7rat");
  Herw7rat->Divide(pp7);*/
  
  pad1->cd(); 
  ppSpecD->Draw();
  pp7->SetMarkerStyle(5);
  pp7->Draw("same p");
  pythia8_7scaled->Scale(3);
  pythia8_7scaled->SetMarkerStyle(4);
  pythia8_7scaled->SetMarkerColor(kRed);
  pythia8_7scaled->SetLineColor(kRed);
  pythia8_7scaled->Draw("same p");
  EPOS7scaled->Scale(10); 
  EPOS7scaled->SetMarkerStyle(25);
  EPOS7scaled->SetMarkerColor(kBlue);
  EPOS7scaled->SetLineColor(kBlue);
  EPOS7scaled->Draw("same p");
  TLegend * specLeg3 = new TLegend(0.25,0.1,0.45,0.5);
  specLeg3->AddEntry((TObject*)0,"|#eta|<1",""); 
  specLeg3->AddEntry(pp7,"binned pp 7 TeV Data","p"); 
  specLeg3->AddEntry(pythia8_7scaled,"Pythia 8 (x3)","p"); 
  specLeg3->AddEntry(EPOS7scaled,"EPOS LHC (x10)","p"); 
  //specLeg3->AddEntry(Herw5scaled,"Herwig++ (x30)","p"); 
  specLeg3->Draw("same"); 

  pad2->cd();
  ppSpecD2->Draw(); 
  pp7relSyst_plus1->SetFillColor(kGray);
  pp7relSyst_plus1->SetLineWidth(0);
  pp7relSyst_plus1->GetXaxis()->SetRangeUser(0.4,130);
  pp7relSyst_minus1->SetFillColor(10);
  pp7relSyst_minus1->SetFillStyle(1001);
  pp7relSyst_minus1->SetLineWidth(0);
  pp7relSyst_minus1->GetXaxis()->SetRangeUser(0.4,130);
  pp7relSyst_plus1->Draw("same hist ][");
  pp7relSyst_minus1->Draw("same hist ][");
  pythia8_7rat->SetLineColor(kRed);
  pythia8_7rat->SetMarkerSize(0);
  pythia8_7rat->SetLineWidth(2);
  pythia8_7rat->Draw("h same ][");
  EPOS7rat->SetLineColor(kBlue);
  EPOS7rat->SetLineStyle(1);
  EPOS7rat->SetLineWidth(2);
  EPOS7rat->SetMarkerSize(0);
  EPOS7rat->Draw("h same ][");
  line3->Draw("same");
  TLegend * systLeg2 = new TLegend(0.3,0.75,0.6,0.98);
  systLeg2->AddEntry(pp5relSyst_plus1,"Data Uncertainty","f");
  systLeg2->Draw("same");
  ppSpecD2->Draw("sameaxis");

  canv2->SaveAs("img/Spectra7TeV_perEventYield.png");
  canv2->SaveAs("img/Spectra7TeV_perEventYield.pdf");
  canv2->SaveAs("img/Spectra7TeV_perEventYield.C");

  TCanvas * c4 = new TCanvas("c4","c4",800,600);
  
  TH1D * extrapFactorPythia7 = (TH1D*)pythia8_544->Clone("extrapFactorPythia_from7TeV");
  extrapFactorPythia7->Divide(pythia8_7);
  extrapFactorPythia7->SetLineColor(kRed);
  extrapFactorPythia7->SetMarkerColor(kRed);
  extrapFactorPythia7->SetMarkerStyle(8);
  extrapFactorPythia7->GetYaxis()->SetTitle("5.44 TeV/7 TeV");
  extrapFactorPythia7->GetYaxis()->SetRangeUser(0.5,1.1);
  extrapFactorPythia7->GetXaxis()->SetTitle("p_{T}");
  extrapFactorPythia7->SetTitle("");
  //extrapFactorPythia->Draw();
  TH1D * extrapFactorEPOS7 = (TH1D*)EPOS544->Clone("extrapFactorEPOS_from7TeV");
  extrapFactorEPOS7->Divide(EPOS7);
  extrapFactorEPOS7->SetLineColor(kBlue);
  extrapFactorEPOS7->SetMarkerColor(kBlue);
  extrapFactorEPOS7->SetMarkerStyle(8);
  extrapFactorEPOS7->GetYaxis()->SetTitle("5.44 TeV/7 TeV");
  extrapFactorEPOS7->GetYaxis()->SetRangeUser(0.5,1.1);
  extrapFactorEPOS7->GetXaxis()->SetTitle("p_{T}");
  extrapFactorEPOS7->SetTitle("");
  extrapFactorEPOS7->Draw("same");
  
  /*extrapFactorHerw = (TH1D*)Herw544->Clone("extrapFactorHerw");
  extrapFactorHerw->Divide(Herw5);
  extrapFactorHerw->SetLineColor(kMagenta);
  extrapFactorHerw->SetMarkerColor(kMagenta);
  extrapFactorHerw->SetMarkerStyle(28);
  extrapFactorHerw->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorHerw->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorHerw->GetXaxis()->SetTitle("p_{T}");
  extrapFactorHerw->SetTitle("");
  extrapFactorHerw->Draw("same");*/
  extrapFactorPythia7->Draw("same");

  TLegend * specLeg5 = new TLegend(0.2,0.7,0.4,0.85);
  specLeg5->AddEntry(extrapFactorPythia,"Pythia 8","p");
  specLeg5->AddEntry(extrapFactorEPOS,"EPOS LHC","p");
  //specLeg2->AddEntry(extrapFactorHerw,"Herwig++","p");
  specLeg5->Draw("same");
  
  c4->SaveAs("img/extrapolationFactorPythia8_from7TeV.png");
  c4->SaveAs("img/extrapolationFactorPythia8_from7TeV.pdf");
  c4->SaveAs("img/extrapolationFacotrPythia8_from7TeV.C");
  c4->SetLogx();
  c4->SaveAs("img/extrapolationFactorPythia8Logx_from7TeV.png");
  c4->SaveAs("img/extrapolationFactorPythia8Logx_from7TeV.pdf");
  c4->SaveAs("img/extrapolationFacotrPythia8Logx_from7TeV.C");

  output->cd();
  pp5->SetDirectory(output);
  pp5->Write();
  pp7->SetDirectory(output);
  pp7->Write();
  extrapFactorPythia->SetDirectory(output);
  extrapFactorPythia->Write();
  extrapFactorPythia7->SetDirectory(output);
  extrapFactorPythia7->Write();
  TH1D * ppScaled = (TH1D*)pp5->Clone("ppScaled");
  ppScaled->Multiply(extrapFactorPythia);
  ppScaled->SetDirectory(output);
  ppScaled->Write();
  TH1D * ppScaled_from7 = (TH1D*)pp7->Clone("ppScaled_from7");
  ppScaled_from7->Multiply(extrapFactorPythia7);
  ppScaled_from7->SetDirectory(output);
  ppScaled_from7->Write();
  
  TH1D * ppScaledRatio = (TH1D*)ppScaled->Clone("ppScaledRatio");
  ppScaledRatio->Divide(ppScaled_from7);

  //set error bars to only have data uncertainties (for splitting data vs MC uncerts)
  TH1D * ppScaledRatio_MCUncert = (TH1D*)ppScaledRatio->Clone("ppScaledRatio_DataUncert");
  for(int i = 1; i<ppScaledRatio_MCUncert->GetSize()-1; i++){
    ppScaledRatio_MCUncert->SetBinError(i,TMath::Power(TMath::Power(ppScaledRatio->GetBinError(i)/ppScaledRatio->GetBinContent(i),2)-TMath::Power(pp5->GetBinError(i)/pp5->GetBinContent(i),2)-TMath::Power(pp7->GetBinError(i)/pp7->GetBinContent(i),2),0.5)*ppScaledRatio_MCUncert->GetBinContent(i)); 
  }

  TCanvas * c5 = new TCanvas("c5","c5",800,600);
  c5->SetLogx();
  ppScaledRatio->SetTitle("");
  ppScaledRatio->GetXaxis()->SetTitle("p_{T}");
  ppScaledRatio->GetYaxis()->SetTitle("(Extrap from 5 TeV)/(Extrap. from 7 TeV)");
  ppScaledRatio->GetYaxis()->SetRangeUser(0.5,1.5);
  ppScaledRatio->SetMarkerStyle(8);
  ppScaledRatio->SetLineColor(kBlack);
  ppScaledRatio->Draw("");

  ppScaledRatio_MCUncert->SetMarkerStyle(8);
  ppScaledRatio_MCUncert->SetLineColor(kBlack);
  ppScaledRatio_MCUncert->SetLineWidth(3);

  ppScaledRatio_MCUncert->Draw("same");

  TLegend * systLeg6 = new TLegend(0.3,0.7,0.6,0.85);
  systLeg6->AddEntry(ppScaledRatio,"Data+MC Uncertainty","l");
  systLeg6->AddEntry(ppScaledRatio_MCUncert,"MC Uncertainty","l");
  systLeg6->Draw("same");

  c5->SaveAs("img/5vs7TeVExtrap.C");
  c5->SaveAs("img/5vs7TeVExtrap.png");
  c5->SaveAs("img/5vs7TeVExtrap.pdf");

  TH1D * data5To7Ratio = (TH1D*)pp5->Clone("data5To7Ratio");
  data5To7Ratio->Divide(pp7);
  data5To7Ratio->GetYaxis()->SetRangeUser(0.5,1.0);
  data5To7Ratio->SetMarkerStyle(8);
  data5To7Ratio->SetLineColor(kBlack);
  data5To7Ratio->GetXaxis()->SetTitle("p_{T}");
  data5To7Ratio->GetYaxis()->SetTitle("5 TeV / 7 TeV");
  data5To7Ratio->Draw();
  TH1D * pythia5To7Ratio = (TH1D*)pythia8_fromFile->Clone("pythia5To7Ratio");
  pythia5To7Ratio->Divide(pythia8_7);
  pythia5To7Ratio->SetMarkerStyle(24);
  pythia5To7Ratio->SetMarkerColor(kRed);
  pythia5To7Ratio->SetLineColor(kRed);
  pythia5To7Ratio->Draw("same");
  TH1D * EPOS5To7Ratio = (TH1D*)EPOS5->Clone("EPOS5To7Ratio");
  EPOS5To7Ratio->Divide(EPOS7);
  EPOS5To7Ratio->SetMarkerStyle(21);
  EPOS5To7Ratio->SetMarkerColor(kBlue);
  EPOS5To7Ratio->SetLineColor(kBlue);
  EPOS5To7Ratio->Draw("same");
  TLegend * systLeg7 = new TLegend(0.6,0.65,0.85,0.85);
  systLeg7->AddEntry(data5To7Ratio,"Data","l");
  systLeg7->AddEntry(pythia5To7Ratio,"Pythia 8","l");
  systLeg7->AddEntry(EPOS5To7Ratio,"EPOS LHC","l");
  systLeg7->Draw("same");
 
  c5->SaveAs("img/5To7Ratio.C");
  c5->SaveAs("img/5To7Ratio.png");
  c5->SaveAs("img/5To7Ratio.pdf");

  //alpha = (5.44-5)/(7-5) in MC
  TH1D * alphaNum = (TH1D*) pythia8_544->Clone("relPlacement_alphaNum");
  alphaNum->Add(pythia8_fromFile,-1);
  TH1D * alphaDenom = (TH1D*) pythia8_7->Clone("relPlacement_alphaDenom");
  alphaDenom->Add(pythia8_fromFile,-1);
  TH1D * alpha = (TH1D*) alphaNum->Clone("alpha");
  alpha->Divide(alphaDenom);
  TH1D * alphaTimes7Data = (TH1D*)alpha->Clone("alphaTimes7Data");
  alphaTimes7Data->Multiply(pp7);
  TH1D * oneMinusalphaTimes5Data = (TH1D*)alpha->Clone("oneMinusalphaTimes5Data");
  for(int i = 0; i<oneMinusalphaTimes5Data->GetSize(); i++){
    oneMinusalphaTimes5Data->SetBinContent(i,1);
    oneMinusalphaTimes5Data->SetBinError(i,0);
  }
  oneMinusalphaTimes5Data->Add(alpha,-1);
  oneMinusalphaTimes5Data->Multiply(pp5);
  
  TH1D * relPlacement544 = (TH1D*) alphaTimes7Data->Clone("relPlacement544");
  relPlacement544->Add(oneMinusalphaTimes5Data);
  relPlacement544->Write();   

  TH1D * relPlacement544VSextrap5 = (TH1D*)ppScaled->Clone("relPlacement544VSextrap5");
  relPlacement544VSextrap5->Divide(relPlacement544);
  
  c5->SetLogx();
  relPlacement544VSextrap5->SetTitle("");
  relPlacement544VSextrap5->GetXaxis()->SetTitle("p_{T}");
  relPlacement544VSextrap5->GetYaxis()->SetTitle("(Extrap from 5 TeV)/(Relative Placement)");
  relPlacement544VSextrap5->GetYaxis()->SetRangeUser(0.5,1.5);
  relPlacement544VSextrap5->SetMarkerStyle(8);
  relPlacement544VSextrap5->SetLineColor(kBlack);
  relPlacement544VSextrap5->Draw("");

  c5->SaveAs("img/5vsRelativePlacement.C");
  c5->SaveAs("img/5vsRelativePlacement.png");
  c5->SaveAs("img/5vsRelativePlacement.pdf");
} 



 

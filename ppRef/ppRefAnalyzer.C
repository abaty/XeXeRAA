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
#include "TF1.h"

void ppRefAnalyzer(bool doRemoveHyperonCorr = false){
  setTDRStyle();
  gStyle->SetOptFit(0);
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

  TFile * xtFile = TFile::Open("x_t_check/xtScaling.root");
  TH1D * xtScaled = (TH1D*)xtFile->Get("xtPPRef544");

  TFile * output = TFile::Open("ppRef_Extrapolated.root","recreate");

  TH1D * pp5 = new TH1D("pp5","pp5",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp5plusStat = new TH1D("pp5plusStat","pp5plusStat",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp5NoError = new TH1D("pp5","pp5",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp5Syst = new TH1D("pp5Syst","pp5Syst",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp5relSyst = new TH1D("pp5relSyst","pp5relSyst",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp5relSyst_plus1 = new TH1D("pp5relSyst_plus1","pp5relSyst_plus1",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp5relSyst_minus1 = new TH1D("pp5relSyst_minus1","pp5relSyst_minus1",s.ntrkBins_ppana,s.xtrkbins_ppana);

  TH1D * pythia8_5 = new TH1D("pythia8_5","pythia8_5",s.ntrkBins_ppana,s.xtrkbins_ppana);
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
    pp5plusStat->SetBinContent(i,ppSpec->GetBinContent(i));
    pp5plusStat->SetBinError(i,ppSpec_stat->GetBinContent(i));

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
  pp5plusStat->Scale(70);
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
  Herw5scaled->SetMarkerColor(kViolet);
  Herw5scaled->SetLineColor(kViolet);
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
  Herw5rat->SetLineColor(kViolet);
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

  
  TCanvas * c3 = new TCanvas("c3","c3",800,800);
  extrapFactorPythia = (TH1D*)pythia8_544->Clone("extrapFactorPythia");
  extrapFactorPythia->Divide(pythia8_fromFile);
  extrapFactorPythia->SetLineColor(kRed);
  extrapFactorPythia->SetMarkerColor(kRed);
  extrapFactorPythia->SetMarkerStyle(8);
  extrapFactorPythia->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorPythia->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorPythia->GetXaxis()->SetTitle("p_{T}");
  extrapFactorPythia->SetTitle("");
  extrapFactorPythia->Draw();
  extrapFactorEPOS = (TH1D*)EPOS544->Clone("extrapFactorEPOS");
  extrapFactorEPOS->Divide(EPOS5);
  extrapFactorEPOS->SetLineColor(kBlue);
  extrapFactorEPOS->SetMarkerColor(kBlue);
  extrapFactorEPOS->SetMarkerStyle(8);
  extrapFactorEPOS->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorEPOS->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorEPOS->GetXaxis()->SetTitle("p_{T}");
  extrapFactorEPOS->SetTitle("");
  
  extrapFactorHerw = (TH1D*)Herw544->Clone("extrapFactorHerw");
  extrapFactorHerw->Divide(Herw5);
  extrapFactorHerw->SetLineColor(kViolet);
  extrapFactorHerw->SetMarkerColor(kViolet);
  extrapFactorHerw->SetMarkerStyle(28);
  extrapFactorHerw->GetYaxis()->SetTitle("5.44 TeV/5.02 TeV");
  extrapFactorHerw->GetYaxis()->SetRangeUser(0.9,1.4);
  extrapFactorHerw->GetXaxis()->SetTitle("p_{T}");
  extrapFactorHerw->SetTitle("");

  TLegend * specLeg2 = new TLegend(0.2,0.7,0.4,0.85);
  specLeg2->AddEntry(extrapFactorPythia,"PYTHIA 8","pl");
  specLeg2->AddEntry(extrapFactorEPOS,"EPOS LHC","pl");
  specLeg2->AddEntry(extrapFactorHerw,"HERWIG++","pl");
  
  TF1 * extrapFuncLogistic = new TF1("extrapLogistic","[0]+[3]*TMath::Log(x)+[1]*((TMath::Log(x)-[2])/TMath::Power(1+TMath::Power(TMath::Log(x)-[2],2),0.5))",0.5,103.6);
  extrapFuncLogistic->SetParameter(0,1.1);
  extrapFuncLogistic->SetParameter(1,0.1);
  extrapFuncLogistic->SetParameter(2,50);
  extrapFuncLogistic->SetParameter(3,0);
  extrapFuncLogistic->SetLineColor(kCyan+1);
  extrapFactorPythia->Fit(extrapFuncLogistic,"EMR");
  std::cout << extrapFuncLogistic->GetChisquare()/(float)extrapFuncLogistic->GetNDF() << std::endl;
  extrapFuncLogistic->Write();  
  
  TF1 * extrapFuncLogistic2 = new TF1("extrapLogistic2","[0]+[4]*TMath::Log(x)+[1]*TMath::Log(x)*TMath::Log(x)+[2]*TMath::TanH(TMath::Log(x)-[3])",0.5,103.6);
  //TF1 * extrapFuncLogistic2 = new TF1("extrapLogistic2","[0]+[2]*TMath::Log(x)+[1]*TMath::Log(x)*TMath::Log(x)",0.5,103.6);
  extrapFuncLogistic2->SetParameter(0,1.1);
  extrapFuncLogistic2->SetParameter(1,0.1);
  extrapFuncLogistic2->SetParameter(2,1);
  extrapFuncLogistic2->SetLineColor(kBlue);
  extrapFactorPythia->Fit(extrapFuncLogistic2,"EMR");
  std::cout << extrapFuncLogistic2->GetChisquare()/(float)extrapFuncLogistic2->GetNDF() << std::endl;
  extrapFuncLogistic2->Write();  
 
  TF1 * extrapFuncPoly3 = new TF1("extrapFuncPoly3","[0]+[1]*TMath::Log(x)+[2]*TMath::Power(TMath::Log(x),2)+[3]*TMath::Power(TMath::Log(x),3)",0.5,103.6);
  extrapFuncPoly3->SetParameter(0,1);
  extrapFuncPoly3->SetParameter(1,0);
  extrapFuncPoly3->SetParameter(2,0);
  extrapFuncPoly3->SetParameter(3,0);
  extrapFuncPoly3->SetLineColor(kGreen);
  extrapFactorPythia->Fit(extrapFuncPoly3,"EMR");
  std::cout << extrapFuncPoly3->GetChisquare()/(float)extrapFuncPoly3->GetNDF() << std::endl;
  extrapFuncPoly3->Write();
  
  TF1 * extrapFuncPoly5 = new TF1("extrapFuncPoly5","[0]+[1]*TMath::Log(x)+[2]*TMath::Power(TMath::Log(x),2)+[3]*TMath::Power(TMath::Log(x),3)+[4]*TMath::Power(TMath::Log(x),4)+[5]*TMath::Power(TMath::Log(x),5)",0.5,103.6);
  extrapFuncPoly5->SetParameter(0,1);
  extrapFuncPoly5->SetParameter(1,0);
  extrapFuncPoly5->SetParameter(2,0);
  extrapFuncPoly5->SetParameter(3,0);
  extrapFuncPoly5->SetLineColor(kGreen+2);
  extrapFactorPythia->Fit(extrapFuncPoly5,"EMR");
  std::cout << extrapFuncPoly5->GetChisquare()/(float)extrapFuncPoly5->GetNDF() << std::endl;
  extrapFuncPoly5->Write();

  TF1 * extrapFuncPoly4 = new TF1("extrapFuncPoly4","[0]+[1]*TMath::Log(x)+[2]*TMath::Power(TMath::Log(x),2)+[3]*TMath::Power(TMath::Log(x),3)+[4]*TMath::Power(TMath::Log(x),4)",0.5,103.6);
  extrapFuncPoly4->SetParameter(0,1);
  extrapFuncPoly4->SetParameter(1,0);
  extrapFuncPoly4->SetParameter(2,0);
  extrapFuncPoly4->SetParameter(3,0);
  extrapFuncPoly4->SetParameter(4,0);
  extrapFuncPoly4->SetLineColor(kBlack);
  extrapFactorPythia->Fit(extrapFuncPoly4,"EMR");
  std::cout << extrapFuncPoly4->GetChisquare()/(float)extrapFuncPoly4->GetNDF() << std::endl;
  extrapFuncPoly4->Write();  
  
  extrapFuncPoly4->Draw("same");

  extrapFactorEPOS->Draw("same");
  extrapFactorHerw->Draw("same");
  extrapFactorPythia->SetLineWidth(2);
  extrapFactorPythia->Draw("same");
  specLeg2->AddEntry(extrapFuncPoly4,"Fit to PYTHIA 8","l");
  specLeg2->Draw("same"); 

  c3->SaveAs("img/extrapolationFactorPythia8.png");
  c3->SaveAs("img/extrapolationFactorPythia8.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8.C");
  c3->SetLogx();
  c3->SaveAs("img/extrapolationFactorPythia8Logx.png");
  c3->SaveAs("img/extrapolationFactorPythia8Logx.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8Logx.C");

  //clean up c3 a bit
  for(int i = 1; i<extrapFactorHerw->GetSize()-1;i++){
    if(extrapFactorHerw->GetBinCenter(i)<25){
      extrapFactorHerw->SetBinContent(i,0);
      extrapFactorHerw->SetBinError(i,0);
    }
    if(extrapFactorEPOS->GetBinError(i)/extrapFactorEPOS->GetBinContent(i)>0.15){
      extrapFactorEPOS->SetBinContent(i,0);
      extrapFactorEPOS->SetBinError(i,0);
    }
  }
  extrapFactorPythia->GetYaxis()->CenterTitle();
  extrapFactorPythia->GetYaxis()->SetTitle("Extrapolation Factor");
  extrapFactorPythia->GetXaxis()->SetTitle("p_{T} (GeV)");
  extrapFactorPythia->GetXaxis()->CenterTitle();
  extrapFactorPythia->GetYaxis()->SetTitleOffset(1.1);
  extrapFactorPythia->GetYaxis()->SetTitleSize(0.07);
  extrapFactorPythia->GetYaxis()->SetLabelSize(0.05);
  extrapFactorPythia->GetXaxis()->SetTitleOffset(0.8);
  extrapFactorPythia->GetXaxis()->SetLabelOffset(-0.015);
  extrapFactorPythia->GetXaxis()->SetTitleSize(0.0675);
  extrapFactorPythia->GetXaxis()->SetLabelSize(0.05);
  extrapFactorPythia->SetLineColor(kBlack);
  extrapFactorPythia->SetLineWidth(2);
  extrapFactorPythia->SetMarkerColor(kBlack);
  extrapFactorPythia->GetYaxis()->SetRangeUser(0.95,1.4);


  c3->SetRightMargin(0.03);
  extrapFactorPythia->SetMarkerSize(1.3);
  extrapFactorPythia->Draw("");
  extrapFuncPoly4->SetLineColor(kRed);
  extrapFuncPoly4->SetLineWidth(2);
  extrapFuncPoly4->Draw("same");
  extrapFactorEPOS->SetMarkerStyle(24);
  extrapFactorEPOS->SetMarkerSize(1.3);
  extrapFactorEPOS->SetLineWidth(1);
  extrapFactorEPOS->Draw("same");
  extrapFactorHerw->SetLineWidth(1);
  extrapFactorHerw->SetMarkerSize(1.3);
  extrapFactorHerw->Draw("same");
  //TH1D * extrapFactorPythiaClone = (TH1D*)extrapFactorPythia->Clone("extraFactorPythiaClone");
  //extrapFactorPythiaClone->Draw("same");
  specLeg2->SetX1NDC(0.2); 
  specLeg2->SetX2NDC(0.7); 
  specLeg2->SetY1NDC(0.5); 
  specLeg2->SetY2NDC(0.75); 
  specLeg2->SetFillStyle(0); 
  specLeg2->Draw("same"); 
  c3->SetLogx(0);
  
  int iPeriod = 0;
  lumi_sqrtS = "";
  writeExtraText = true;  
  //extraText  = "Simulation Preliminary";
  extraText  = "Simulation";
  //extraText  = "Unpublished";
  CMS_lumi( c3, iPeriod, 11 );

  c3->SaveAs("img/extrapolationFactorPythia8_cleaned.png");
  c3->SaveAs("img/extrapolationFactorPythia8_cleaned.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8_cleaned.C");
  c3->SetLogx();
  c3->SaveAs("img/extrapolationFactorPythia8Logx_cleaned.png");
  c3->SaveAs("img/extrapolationFactorPythia8Logx_cleaned.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8Logx_cleaned.C");

  //showfits
  extrapFactorPythia->GetYaxis()->SetRangeUser(1,1.25);;
  extrapFactorPythia->Draw("");
  extrapFuncPoly4->Draw("same");
  extrapFuncPoly3->Draw("same");
  extrapFuncPoly5->Draw("same");
  extrapFuncLogistic->Draw("same");
  extrapFuncLogistic2->Draw("same");
  
  TLegend * specLegFit = new TLegend(0.2,0.5,0.4,0.85);
  specLegFit->AddEntry(extrapFactorPythia,"Pythia 8","pl");
  specLegFit->AddEntry((TObject*)0,"x = log(p_{T})","");
  specLegFit->AddEntry(extrapFuncPoly4,"a+bx+cx^{2}+dx^{3}+ex^{4}","l");
  specLegFit->AddEntry(extrapFuncPoly3,"a+bx+cx^{2}+dx^{3}","l");
  specLegFit->AddEntry(extrapFuncPoly5,"a+bx+cx^{2}+dx^{3}+ex^{4}+fx^{5}","l");
  specLegFit->AddEntry(extrapFuncLogistic,"a+bx+#frac{c(x-d)}{#sqrt{1+(x-d)^{2}}}","l");
  specLegFit->AddEntry(extrapFuncLogistic2,"a+bx+cx^{2}+d(Tanh(x-e))","l");
  specLegFit->SetFillStyle(0);
  specLegFit->Draw("same");

  c3->SetLogx(0);
  c3->SaveAs("img/extrapolationFactorPythia8_Fits.png");
  c3->SaveAs("img/extrapolationFactorPythia8_Fits.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8_Fits.C");
  c3->SetLogx();
  c3->SaveAs("img/extrapolationFactorPythia8Logx_Fits.png");
  c3->SaveAs("img/extrapolationFactorPythia8Logx_Fits.pdf");
  c3->SaveAs("img/extrapolationFacotrPythia8Logx_Fits.C");

  TH1D * extrapPythiaFitUncert = (TH1D*) extrapFactorPythia->Clone("extrapFactorPythiaFitUncert");
  for(int i = 1; i<extrapPythiaFitUncert->GetSize()-1; i++){
    float uncert = 0;
    float b = extrapPythiaFitUncert->GetBinCenter(i);
    float fit1 = extrapFuncPoly4->Eval(b);
    float fit2 = TMath::Abs(extrapFuncPoly3->Eval(b)-fit1)/fit1;
    float fit3 = TMath::Abs(extrapFuncPoly5->Eval(b)-fit1)/fit1;
    float fit4 = TMath::Abs(extrapFuncLogistic->Eval(b)-fit1)/fit1;
    float fit5 = TMath::Abs(extrapFuncLogistic2->Eval(b)-fit1)/fit1;
    uncert = TMath::Max(TMath::Max(TMath::Max(fit2,fit3),fit4),fit5);
    extrapPythiaFitUncert->SetBinContent(i,uncert);
  }
  extrapPythiaFitUncert->Write();

  //******************************************************************************************
  //******************************************************************************************
  //plots for 7 TeV comparisons
  TFile * pp7TeVFile = TFile::Open("interpolation/binned7TeV.root","read");
  TH1D * pp7 = (TH1D*)pp7TeVFile->Get("pp7");
  TH1D * pp7NoError = (TH1D*)pp7->Clone("pp7NoError");
  for(int i = 0; i<pp7NoError->GetSize(); i++) pp7NoError->SetBinError(i,0);
  TH1D * pp7relSyst_plus1 = new TH1D("pp7relSyst_plus1","pp7relSyst_plus1",s.ntrkBins_ppana,s.xtrkbins_ppana);
  TH1D * pp7relSyst_minus1 = new TH1D("pp7relSyst_minus1","pp7relSyst_minus1",s.ntrkBins_ppana,s.xtrkbins_ppana);
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
  extrapFactorHerw->SetLineColor(kViolet);
  extrapFactorHerw->SetMarkerColor(kViolet);
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

  TH1D * ppScaledWithFit = (TH1D*)pp5plusStat->Clone("ppScaled_WithFit_noRebin");
  TH1D * ppScaledSyst_NoLumi = (TH1D*)ppSpec_syst->Clone("ppScaledSyst_NoLumi_noRebin");
  TH1D * ppScaledSyst = (TH1D*)ppSpec_syst->Clone("ppScaledSyst_noRebin");

  for(int i = 1; i<ppScaledWithFit->GetSize()-1; i++){
    ppScaledWithFit->SetBinContent(i,ppScaledWithFit->GetBinContent(i)*extrapFuncPoly4->Eval(ppScaledWithFit->GetBinCenter(i)));
    ppScaledWithFit->SetBinError(i,ppScaledWithFit->GetBinError(i)*extrapFuncPoly4->Eval(ppScaledWithFit->GetBinCenter(i)));

    ppScaledSyst_NoLumi->SetBinContent(i,TMath::Power(TMath::Power(ppScaledSyst_NoLumi->GetBinContent(i)/ppSpec->GetBinContent(i),2)+TMath::Power(extrapPythiaFitUncert->GetBinContent(i),2),0.5));
    ppScaledSyst->SetBinContent(i,TMath::Power(TMath::Power(ppScaledSyst_NoLumi->GetBinContent(i),2)+0.023*0.023,0.5));
  }
  ppScaledWithFit->SetDirectory(output);
  ppScaledWithFit->Write();
  ppScaledSyst_NoLumi->SetDirectory(output);
  ppScaledSyst_NoLumi->Write();
  ppScaledSyst->SetDirectory(output);
  ppScaledSyst->Write();

  static const int ntrkBins = 29;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 48.0,73.6,103.6};
  TH1D * ppScaledWithFit_Rebin = new TH1D("ppScaled_WithFit","",ntrkBins,xtrkbins);
  TH1D * ppScaledSyst_NoLumi_Rebin = new TH1D("ppScaledSyst_NoLumi","",ntrkBins,xtrkbins);
  TH1D * ppScaledSyst_Rebin = new TH1D("ppScaledSyst","",ntrkBins,xtrkbins);
  for(int i = 1; i<ppScaledWithFit_Rebin->GetSize()-1; i++){
    if(i<27){
      ppScaledWithFit_Rebin->SetBinContent(i,pp5plusStat->GetBinContent(i)*extrapFuncPoly4->Eval(pp5plusStat->GetBinCenter(i)));
      ppScaledWithFit_Rebin->SetBinError(i,pp5plusStat->GetBinError(i)*extrapFuncPoly4->Eval(pp5plusStat->GetBinCenter(i)));
      ppScaledSyst_NoLumi_Rebin->SetBinContent(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i)/ppSpec->GetBinContent(i),2)+TMath::Power(extrapPythiaFitUncert->GetBinContent(i),2),0.5));
    }
    if(i==27){
      float yield1 = pp5plusStat->GetBinContent(i)*pp5plusStat->GetBinWidth(i)*pp5plusStat->GetBinCenter(i);
      float yield2 = pp5plusStat->GetBinContent(i+1)*pp5plusStat->GetBinWidth(i+1)*pp5plusStat->GetBinCenter(i+1);
      float net = (yield1+yield2)/ppScaledWithFit_Rebin->GetBinWidth(i)/ppScaledWithFit_Rebin->GetBinCenter(i);
      float error1 = TMath::Power(pp5plusStat->GetBinError(i)*pp5plusStat->GetBinWidth(i)*pp5plusStat->GetBinCenter(i),2);
      float error2 = TMath::Power(pp5plusStat->GetBinError(i+1)*pp5plusStat->GetBinWidth(i+1)*pp5plusStat->GetBinCenter(i+1),2);
      float err = TMath::Power(error1+error2,0.5)/ppScaledWithFit_Rebin->GetBinWidth(i)/ppScaledWithFit_Rebin->GetBinCenter(i);
      ppScaledWithFit_Rebin->SetBinContent(i,net*extrapFuncPoly4->Eval(ppScaledWithFit_Rebin->GetBinCenter(i)));
      ppScaledWithFit_Rebin->SetBinError(i,err*extrapFuncPoly4->Eval(ppScaledWithFit_Rebin->GetBinCenter(i)));
      float syst = TMath::Power(ppSpec_syst->GetBinContent(i)/ppSpec->GetBinContent(i)*yield1/(yield1+yield2) + ppSpec_syst->GetBinContent(i+1)/ppSpec->GetBinContent(i+1)*yield2/(yield1+yield2),2);
      ppScaledSyst_NoLumi_Rebin->SetBinContent(i,TMath::Power(syst+TMath::Power(extrapPythiaFitUncert->GetBinContent(i),2),0.5));
    }
    if(i==28){
      float yield1 = pp5plusStat->GetBinContent(i+1)*pp5plusStat->GetBinWidth(i+1)*pp5plusStat->GetBinCenter(i+1);
      float yield2 = pp5plusStat->GetBinContent(i+2)*pp5plusStat->GetBinWidth(i+2)*pp5plusStat->GetBinCenter(i+2);
      float net = (yield1+yield2)/ppScaledWithFit_Rebin->GetBinWidth(i)/ppScaledWithFit_Rebin->GetBinCenter(i);
      float error1 = TMath::Power(pp5plusStat->GetBinError(i+1)*pp5plusStat->GetBinWidth(i+1)*pp5plusStat->GetBinCenter(i+1),2);
      float error2 = TMath::Power(pp5plusStat->GetBinError(i+2)*pp5plusStat->GetBinWidth(i+2)*pp5plusStat->GetBinCenter(i+2),2);
      float err = TMath::Power(error1+error2,0.5)/ppScaledWithFit_Rebin->GetBinWidth(i)/ppScaledWithFit_Rebin->GetBinCenter(i);
      ppScaledWithFit_Rebin->SetBinContent(i,net*extrapFuncPoly4->Eval(ppScaledWithFit_Rebin->GetBinCenter(i)));
      ppScaledWithFit_Rebin->SetBinError(i,err*extrapFuncPoly4->Eval(ppScaledWithFit_Rebin->GetBinCenter(i)));
      float syst = TMath::Power(ppSpec_syst->GetBinContent(i+1)/ppSpec->GetBinContent(i+1)*yield1/(yield1+yield2) + ppSpec_syst->GetBinContent(i+2)/ppSpec->GetBinContent(i+2)*yield2/(yield1+yield2),2);
      ppScaledSyst_NoLumi_Rebin->SetBinContent(i,TMath::Power(syst+TMath::Power(extrapPythiaFitUncert->GetBinContent(i+1),2),0.5));
    }
    if(i==29){
      float yield1 = pp5plusStat->GetBinContent(i+2)*pp5plusStat->GetBinWidth(i+2)*pp5plusStat->GetBinCenter(i+2);
      float yield2 = pp5plusStat->GetBinContent(i+3)*pp5plusStat->GetBinWidth(i+3)*pp5plusStat->GetBinCenter(i+3);
      float net = (yield1+yield2)/ppScaledWithFit_Rebin->GetBinWidth(i)/ppScaledWithFit_Rebin->GetBinCenter(i);
      float error1 = TMath::Power(pp5plusStat->GetBinError(i+2)*pp5plusStat->GetBinWidth(i+2)*pp5plusStat->GetBinCenter(i+2),2);
      float error2 = TMath::Power(pp5plusStat->GetBinError(i+3)*pp5plusStat->GetBinWidth(i+3)*pp5plusStat->GetBinCenter(i+3),2);
      float err = TMath::Power(error1+error2,0.5)/ppScaledWithFit_Rebin->GetBinWidth(i)/ppScaledWithFit_Rebin->GetBinCenter(i);
      ppScaledWithFit_Rebin->SetBinContent(i,net*extrapFuncPoly4->Eval(ppScaledWithFit_Rebin->GetBinCenter(i)));
      ppScaledWithFit_Rebin->SetBinError(i,err*extrapFuncPoly4->Eval(ppScaledWithFit_Rebin->GetBinCenter(i)));
      float syst = TMath::Power(ppSpec_syst->GetBinContent(i+2)/ppSpec->GetBinContent(i+2)*yield1/(yield1+yield2) + ppSpec_syst->GetBinContent(i+3)/ppSpec->GetBinContent(i+3)*yield2/(yield1+yield2),2);
      ppScaledSyst_NoLumi_Rebin->SetBinContent(i,TMath::Power(syst+TMath::Power(extrapPythiaFitUncert->GetBinContent(i+2),2),0.5));
    }


    ppScaledSyst_Rebin->SetBinContent(i,TMath::Power(TMath::Power(ppScaledSyst_NoLumi_Rebin->GetBinContent(i),2)+0.023*0.023,0.5));
  }

  ppScaledWithFit_Rebin->SetDirectory(output);
  ppScaledWithFit_Rebin->Write();
  ppScaledSyst_NoLumi_Rebin->SetDirectory(output);
  ppScaledSyst_NoLumi_Rebin->Write();
  ppScaledSyst_Rebin->SetDirectory(output);
  ppScaledSyst_Rebin->Write();



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

  TH1D * xt544VSextrap5 = (TH1D*)ppScaled->Clone("xt544VSextrap5");
  xt544VSextrap5->Divide(xtScaled);
  xt544VSextrap5->GetXaxis()->SetRangeUser(15,105);
  xt544VSextrap5->GetXaxis()->SetTitle("p_{T}");
  xt544VSextrap5->GetYaxis()->SetTitle("(Extrap from 5 TeV)/(x_{T} scaling)");
  xt544VSextrap5->GetYaxis()->SetRangeUser(0.9,1.1);
  xt544VSextrap5->SetMarkerStyle(8);
  xt544VSextrap5->SetLineColor(kBlack);
  xt544VSextrap5->Draw("");
  
  c5->SaveAs("img/5vsXTScaled.C");
  c5->SaveAs("img/5vsXTScaled.png");
  c5->SaveAs("img/5vsXTScaled.pdf");
  
  
} 



 

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
  Settings s;


  TFile * f = TFile::Open("pp5TeV_FromRAA.root","read");
  TH1D * ppSpec = (TH1D*) f->Get("Table 7/Hist1D_y1");
  TH1D * ppSpec_stat = (TH1D*) f->Get("Table 7/Hist1D_y1_e1");
  TH1D * ppSpec_syst = (TH1D*) f->Get("Table 7/Hist1D_y1_e2plus");
  TH1D * ppSpec_lumi = (TH1D*) f->Get("Table 7/Hist1D_y1_e3");

  TH1D * pp5 = new TH1D("pp5","pp5",s.ntrkBins,s.xtrkbins);
  TH1D * pp5Syst = new TH1D("pp5Syst","pp5Syst",s.ntrkBins,s.xtrkbins);
  for(int i = 1; i<pp5->GetSize()-1; i++){
    pp5->SetBinContent(i,ppSpec->GetBinContent(i));
    pp5->SetBinError(i,ppSpec_stat->GetBinContent(i));
    pp5Syst->SetBinContent(i,TMath::Power(TMath::Power(ppSpec_syst->GetBinContent(i),2)+TMath::Power(ppSpec_lumi->GetBinContent(i),2),0.5));
  }
  pp5->Print("All");
  pp5Syst->Print("All");


  /*
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
  
  TH1D * ppSpecD = new TH1D("specDummy1","",3,0.4,450);
  ppSpecD->GetXaxis()->SetRangeUser(0.4,390);
  ppSpecD->GetYaxis()->SetTitle("#frac{1}{N_{evt}} E #frac{d^{3}N}{dp^{3}} (GeV^{-2})");
  ppSpecD->GetYaxis()->SetTitleOffset(1.4);
  ppSpecD->GetYaxis()->SetTitleSize(0.045);
  ppSpecD->GetYaxis()->SetLabelSize(0.04);
  ppSpecD->GetYaxis()->CenterTitle();
  ppSpecD->GetYaxis()->SetLabelOffset(0.002);
  ppSpecD->GetYaxis()->SetRangeUser(1.1e-17,1e4);
  ppSpecD->GetXaxis()->SetRangeUser(0.4,390);
  ppSpecD->Draw();
  ppSpec->SetMarkerStyle(5);
  ppSpec->Scale(1/70.0);//scaled by inelastic xsection of 70 mb
  ppSpec->Draw("same");
  
  pbpbSpec[0]->GetXaxis()->SetRangeUser(0.7,390);
  pbpbSpec[0]->SetMarkerStyle(24);
  pbpbSpec[0]->Scale(10);
  pbpbSpec[0]->Draw("same");
  pbpbSpec[1]->SetMarkerColor(kBlue);
  pbpbSpec[1]->SetLineColor(kBlue);
  pbpbSpec[1]->SetMarkerStyle(25);
  pbpbSpec[1]->Scale(3);
  pbpbSpec[1]->GetXaxis()->SetRangeUser(0.7,390);
  pbpbSpec[1]->Draw("same");
  pbpbSpec[23]->SetMarkerColor(kRed);
  pbpbSpec[23]->SetLineColor(kRed);
  pbpbSpec[23]->SetMarkerStyle(28);
  pbpbSpec[23]->GetXaxis()->SetRangeUser(0.7,390);
  pbpbSpec[23]->Draw("same");
  pbpbSpec[24]->SetMarkerStyle(20);
  pbpbSpec[24]->GetXaxis()->SetRangeUser(0.7,390);
  pbpbSpec[25]->SetMarkerColor(kBlue);
  pbpbSpec[25]->SetLineColor(kBlue);
  pbpbSpec[24]->Draw("same");
  pbpbSpec[25]->SetMarkerStyle(21);
  pbpbSpec[25]->GetXaxis()->SetRangeUser(0.7,390);
  pbpbSpec[25]->Draw("same");
  pbpbSpec[30]->SetMarkerColor(kRed);
  pbpbSpec[30]->SetLineColor(kRed);
  pbpbSpec[30]->SetMarkerStyle(34);
  pbpbSpec[30]->GetXaxis()->SetRangeUser(0.7,390);
  pbpbSpec[30]->Draw("same");
  TLegend * specLeg = new TLegend(0.25,0.1,0.45,0.5);
  //specLeg->SetFillStyle(0);
  specLeg->AddEntry((TObject*)0,"|#eta|<1",""); 
  specLeg->AddEntry(pbpbSpec[0],Form("0-5%s (x10)","%"),"p");  
  specLeg->AddEntry(pbpbSpec[1],Form("5-10%s (x3)","%"),"p");  
  specLeg->AddEntry(pbpbSpec[23],Form("10-30%s","%"),"p");  
  specLeg->AddEntry(pbpbSpec[24],Form("30-50%s","%"),"p");  
  specLeg->AddEntry(pbpbSpec[25],Form("50-70%s","%"),"p");  
  specLeg->AddEntry(pbpbSpec[30],Form("70-90%s","%"),"p");  
  specLeg->AddEntry(ppSpec,"pp","p"); 
  specLeg->Draw("same"); 
 
  pad2->cd();
  pad2->SetLogx();
  TH1D * ppSpecD2 = new TH1D("specDummy2","",3,0.4,450);
  ppSpecD2->GetYaxis()->SetRangeUser(0.0,19.99);
  ppSpecD2->GetYaxis()->SetNdivisions(4,4,0,kTRUE);
  ppSpecD2->GetYaxis()->SetTitleOffset(0.6);
  ppSpecD2->GetYaxis()->SetTitleFont(42);
  ppSpecD2->GetYaxis()->SetTitleSize(0.095);
  ppSpecD2->GetYaxis()->SetLabelSize(0.095);
  ppSpecD2->GetXaxis()->SetTitleFont(42);
  ppSpecD2->GetYaxis()->SetTitle(Form("Syst. uncert. (%s)","%"));
  ppSpecD2->GetXaxis()->SetRangeUser(0.4,390);
  ppSpecD2->GetXaxis()->SetTitle("p_{T} (GeV)");
  ppSpecD2->GetXaxis()->SetTitleSize(0.1);
  ppSpecD2->GetXaxis()->SetLabelSize(0.1);
  ppSpecD2->GetXaxis()->SetTitleOffset(1.2);
  ppSpecD2->GetXaxis()->CenterTitle();
  ppSpecD2->GetXaxis()->SetTickLength(0.06);
  ppSpecD2->Draw();
  s.PbPb_totSyst[0]->SetFillColor(kOrange);
  s.PbPb_totSyst[0]->SetBinContent(1,0);
  s.PbPb_totSyst[0]->SetBinError(1,0);
  s.PbPb_totSyst[0]->SetBinContent(2,0);
  s.PbPb_totSyst[0]->SetBinError(2,0);
  s.PbPb_totSyst[0]->Scale(100);
  s.PbPb_totSyst[0]->GetXaxis()->SetRangeUser(0.7,400);
  s.PbPb_totSyst[0]->Draw("same");
  s.PbPb_totSyst[30]->SetFillColor(kRed);
  s.PbPb_totSyst[30]->SetFillStyle(3004);
  s.PbPb_totSyst[30]->Scale(100);
  s.PbPb_totSyst[30]->SetBinContent(1,0);
  s.PbPb_totSyst[30]->SetBinError(1,0);
  s.PbPb_totSyst[30]->SetBinContent(2,0);
  s.PbPb_totSyst[30]->SetBinError(2,0);
  s.PbPb_totSyst[30]->GetXaxis()->SetRangeUser(0.7,400);
  s.PbPb_totSyst[30]->Draw("same");
  s.pp_totSyst->SetFillColor(kBlack);
  s.pp_totSyst->SetFillStyle(3003);
  s.pp_totSyst->GetXaxis()->SetRangeUser(0.5,400);
  s.pp_totSyst->Scale(100);
  s.pp_totSyst->Draw("same");
  TLegend * systLeg = new TLegend(0.6,0.6,0.9,0.98);
  //systLeg->SetFillStyle(0);
  systLeg->AddEntry(s.PbPb_totSyst[0],Form("0-5%s","%"),"f");
  systLeg->AddEntry(s.PbPb_totSyst[30],Form("70-90%s","%"),"f");
  systLeg->AddEntry(s.pp_totSyst,"pp","f");
  gStyle->SetPadTickY(1);
  systLeg->Draw("same");
  ppSpecD2->Draw("sameaxis");
  ppSpecD2->GetXaxis()->Draw("same");

  CMS_lumi( canv2, 0,33);
  //canv2->Update();
  //canv2->RedrawAxis();
  //canv2->GetFrame()->Draw();    
  canv2->SaveAs("plots/prettyPlots/Spectra_perEventYield.png");
  canv2->SaveAs("plots/prettyPlots/Spectra_perEventYield.pdf");
  canv2->SaveAs("plots/prettyPlots/Spectra_perEventYield.C");
  */

}

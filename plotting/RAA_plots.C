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

void RAA_plots(){
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
 
  Settings s = Settings();

  TH1D * h[s.nCentBins];
  TFile * f = TFile::Open("../output_0.root","read");
  for(int c = 0; c<s.nCentBins; c++){
    h[c] = (TH1D*)f->Get(Form("RAA_%d_%d",s.lowCentBin[c]*5,s.highCentBin[c]*5));
    h[c]->SetDirectory(0);
  }
  f->Close();

  setTDRStyle();
  TLine * line1;
  TLatex * tex = new TLatex(0.1,0.1,"cent");
  TLatex * tex2 = new TLatex(0.1,0.1,"cent");
  TBox* bLumi = new TBox(0.1,0.1,0.15,0.2); 
  TBox* bTAA = new TBox(0.15,0.1,0.2,0.2); 
  TBox* b[s.ntrkBins];
  for(int i = 0; i<s.ntrkBins; i++) b[i] = new TBox(0.1,0.1,0.2,0.2); 

  int W = 800;
  int H = 700;//700
  int H_ref = 700;//700
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.15*W_ref;
  float R = 0.04*W_ref;
    
  TCanvas* canv = new TCanvas("RAA","RAA",50,50,W,H);
  canv->SetLogx();
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(1);
  canv->SetTicky(1);
 
  gStyle->SetErrorX(0);
  

  for(int c = 0; c<s.nCentBins; c++){
    //plotting
    canv->Clear();
    h[c]->SetLineColor(kBlack);
    h[c]->SetMarkerStyle(8);
    h[c]->GetXaxis()->SetTitle("p_{T} (GeV)");
    h[c]->GetXaxis()->CenterTitle();
    h[c]->GetYaxis()->SetTitle("R*_{AA}");
    h[c]->GetYaxis()->SetTitleOffset(1.2);
    h[c]->GetXaxis()->SetTitleOffset(1.2);
    h[c]->GetYaxis()->CenterTitle();
    h[c]->GetXaxis()->SetRangeUser(0.5,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2));
    h[c]->GetXaxis()->SetLabelOffset(-0.005);
    h[c]->GetYaxis()->SetRangeUser(0,1.6);
    h[c]->SetMarkerSize(1.3);
    h[c]->Draw();

    /* 
    TAAUncert = s.TAAuncert[c]/100.0;
    lumiUncert = 0.023;//12% for pp lumi
    bLumi->SetFillColor(kGray);
    bTAA->SetFillColor(kBlue-9);
    bLumi->SetLineWidth(0);
    bTAA->SetLineWidth(0);
    bTAA->DrawBox(0.9,1-TAAUncert,TMath::Power(10,TMath::Log10(0.9)+(TMath::Log10(1.5)-TMath::Log10(0.9))/2.0),1+TAAUncert);
    bLumi->DrawBox(TMath::Power(10,TMath::Log10(0.9)+(TMath::Log10(1.5)-TMath::Log10(0.9))/2.0),1-lumiUncert,1.5,1+lumiUncert);
    */  

    line1 = new TLine(h[c]->GetXaxis()->GetBinLowEdge(1),1,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2),1);
    line1->SetLineWidth(2);
    line1->SetLineStyle(2);
    line1->Draw("same");
  
    tex2->DrawLatex(0.9,0.1,Form("%d-%d%s",5*s.lowCentBin[c],5*s.highCentBin[c],"%"));
    tex->SetTextFont(42);
    tex->SetTextSize(lumiTextSize*0.08);
    tex->DrawLatex(0.8,1.03,"T_{AA} and lumi. uncertainty");
    tex->DrawLatex(0.8,0.93,"|#eta|<1");
  
    for(int i = 1; i< (h[0]->GetSize()-1); i++){
      b[i-1]->SetFillColor(kRed-7);
      b[i-1]->SetX1(h[c]->GetXaxis()->GetBinLowEdge(i));
      b[i-1]->SetX2(h[c]->GetXaxis()->GetBinUpEdge(i));
      //b[i-1]->SetY1((h[c]->GetBinContent(i))*(1-s.RAA_totSyst[c]->GetBinContent(i)));
      //b[i-1]->SetY2(h[c]->GetBinContent(i)*(1+s.RAA_totSyst[c]->GetBinContent(i)));
      b[i-1]->SetY1((h[c]->GetBinContent(i))*(1-0.1));
      b[i-1]->SetY2(h[c]->GetBinContent(i)*(1+0.1));
      b[i-1]->Draw("same");
    }
    h[c]->SetMarkerSize(1.3);
    h[c]->Draw("same");
  
    int iPeriod = 0;
    lumi_sqrtS = "??? #mub^{-1} (5.44 TeV XeXe)";
    writeExtraText = true;  
    extraText  = "Preliminary";
    //extraText  = "Unpublished";
    CMS_lumi( canv, iPeriod, 11 );
 
    gStyle->SetPadTickY(1);
    canv->Update();
    canv->RedrawAxis();
    canv->GetFrame()->Draw();    
    canv->SaveAs(Form("img/RAA_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
    canv->SaveAs(Form("img/RAA_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
    canv->SaveAs(Form("img/RAA_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c])); 
  }
}

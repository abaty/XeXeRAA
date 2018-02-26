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
#include "TF1.h"

void XeXevsPbPb_plots(){
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
 
  Settings s = Settings();

  TFile * ppFit = TFile::Open("../ppRef_Feb26_Pythia.root","read");
  TF1 * extrapFunc = (TF1*)ppFit->Get("extrapFuncPoly4");
  
  TH1D * h[s.nCentBins];
  TH1D * nVtx;
  TFile * f = TFile::Open("../output_0.root","read");
  nVtx = (TH1D*)f->Get("nVtxMoreBin");
  for(int c = 0; c<s.nCentBins; c++){
    h[c] = (TH1D*)f->Get(Form("HI_TaaWeighted_%d_%d",s.lowCentBin[c]*5,s.highCentBin[c]*5));
    h[c]->Scale(1.0/nVtx->GetBinContent(nVtx->GetXaxis()->FindBin(c)));
    h[c]->SetDirectory(0);
    h[c]->Print("All");
  }
  f->Close();

  TH1D * PbPb[6];
  TH1D * PbPb_stat[6];
  TH1D * PbPb_syst[6];

  float TAA[6] = {26.0,20.5,11.5,3.82,0.934,0.152};
  TFile * f1 = TFile::Open("PbPbRAAs/HEPData-ins1496050-v2-root.root","read"); 

  for(int i = 1; i<7; i++){
    PbPb[i-1] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1",i));
    PbPb_stat[i-1] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e1",i));
    PbPb_syst[i-1] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e2plus",i));

    //manual patch for a missing data point
    //if(i==3){
    //  PbPb[i-1]->SetBinContent(PbPb[i-1]->FindBin(80),1.244e-9);
    //  PbPb_stat[i-1]->SetBinContent(PbPb[i-1]->FindBin(80),2e-11);
    //  PbPb_syst[i-1]->SetBinContent(PbPb[i-1]->FindBin(80),1.e-10);
    //}

    //put stat errors in right spot and scale by TAA
    for(int j = 0; j<PbPb[i-1]->GetSize(); j++){
      PbPb[i-1]->SetBinError(j,PbPb_stat[i-1]->GetBinContent(j));
    }
    
    if(i==1){
      PbPb[i-1]->Scale(1.0/(10.*TAA[i-1]));
      PbPb_syst[i-1]->Scale(1.0/(10.*TAA[i-1]));
    }
    else if(i==2){
      PbPb[i-1]->Scale(1.0/(3.*TAA[i-1]));
      PbPb_syst[i-1]->Scale(1.0/(3.*TAA[i-1]));
    }
    else {
      PbPb[i-1]->Scale(1.0/TAA[i-1]);
      PbPb_syst[i-1]->Scale(1.0/TAA[i-1]);
    }

    PbPb[i-1]->SetDirectory(0);
    PbPb_stat[i-1]->SetDirectory(0);
    PbPb_syst[i-1]->SetDirectory(0);
    PbPb[i-1]->Print("All");
    //PbPb_stat[i-1]->Print("All");
    //PbPb_syst[i-1]->Print("All");
  } 
  f1->Close();

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
    if(c!=0 && c!=1 && c!= 23 && c!=24 && c!= 25 && c!=30) continue;
    int PbPbBin = c;
    if(c==23) PbPbBin = 2;
    if(c==24) PbPbBin = 3;
    if(c==25) PbPbBin = 4;
    if(c==30) PbPbBin = 5;
    
    for(int i = 1; i<h[c]->GetSize(); i++){
      if(i==1 || i==2){
        h[c]->SetBinContent(i,0);
        h[c]->SetBinError(i,0);
        continue;
      }

      float relErr = h[c]->GetBinError(i)/h[c]->GetBinContent(i);
      float PbPbContent = PbPb[PbPbBin]->GetBinContent(PbPb[PbPbBin]->FindBin(h[c]->GetBinCenter(i)));
      float PbPbRelErr = PbPb[PbPbBin]->GetBinError(PbPb[PbPbBin]->FindBin(h[c]->GetBinCenter(i)))/PbPbContent;
 
      h[c]->SetBinContent(i,h[c]->GetBinContent(i)/PbPbContent);
      h[c]->SetBinError(i,TMath::Power(relErr*relErr+PbPbRelErr*PbPbRelErr,0.5));

      if(h[c]->GetBinContent(i)==0){
        h[c]->SetBinContent(i,0);
        h[c]->SetBinError(i,0);
      }
    }    

    canv->Clear();
    h[c]->SetLineColor(kBlack);
    h[c]->SetMarkerStyle(8);
    h[c]->GetXaxis()->SetTitle("p_{T} (GeV)");
    h[c]->GetXaxis()->CenterTitle();
    h[c]->GetYaxis()->SetTitle("R^{Xe}_{Pb}");
    h[c]->GetYaxis()->SetTitleOffset(1.5);
    h[c]->GetXaxis()->SetTitleOffset(1.2);
    h[c]->GetYaxis()->CenterTitle();
    h[c]->GetXaxis()->SetRangeUser(0.5,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2));
    h[c]->GetXaxis()->SetLabelOffset(-0.005);
    h[c]->GetYaxis()->SetRangeUser(0.4,2);
    h[c]->SetMarkerSize(1.3);
    h[c]->Draw();

     
    TAAUncert = 0.05;//placeholder
    bTAA->SetFillColor(kBlue-9);
    bTAA->SetLineWidth(0);
    bTAA->DrawBox(0.575,1-TAAUncert,TMath::Power(10,TMath::Log10(0.575)+(TMath::Log10(0.675)-TMath::Log10(0.575))/2.0),1+TAAUncert);
    bTAA->DrawBox(0.7,0.675,0.85,0.725);
      

    line1 = new TLine(h[c]->GetXaxis()->GetBinLowEdge(1),1,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2),1);
    line1->SetLineWidth(2);
    line1->SetLineStyle(2);
    line1->Draw("same");
  
    tex2->DrawLatex(0.7,0.55,Form("%d-%d%s",5*s.lowCentBin[c],5*s.highCentBin[c],"%"));
    tex->SetTextFont(42);
    tex->SetTextSize(lumiTextSize*0.08);
    tex->DrawLatex(0.9,0.675,"T_{AA} uncertainty");
    tex->DrawLatex(0.7,0.8,"|#eta|<1");
  
    for(int i = 1; i< (h[0]->GetSize()-1); i++){
      b[i-1]->SetFillColor(kRed-7);
      b[i-1]->SetX1(h[c]->GetXaxis()->GetBinLowEdge(i));
      b[i-1]->SetX2(h[c]->GetXaxis()->GetBinUpEdge(i));
      //b[i-1]->SetY1((h[c]->GetBinContent(i))*(1-s.RAA_totSyst[c]->GetBinContent(i)));
      //b[i-1]->SetY2(h[c]->GetBinContent(i)*(1+s.RAA_totSyst[c]->GetBinContent(i)));
      b[i-1]->SetY1((h[c]->GetBinContent(i))*(1-0.03));
      b[i-1]->SetY2(h[c]->GetBinContent(i)*(1+0.03));
      b[i-1]->Draw("same");
    }

    extrapFunc->SetLineStyle(10); 
    extrapFunc->SetLineWidth(2); 
    extrapFunc->SetLineColor(kBlue); 
    extrapFunc->SetRange(0.65,103.6); 
    extrapFunc->Draw("same");
    
    h[c]->SetMarkerSize(1.3);
    h[c]->Draw("same");
 
    int iPeriod = 0;
    lumi_sqrtS = "404 #mub^{-1} (5.02 TeV PbPb) + 3.42 #mub^{-1} (5.44 TeV XeXe)";
    writeExtraText = true;  
    extraText  = "Preliminary";
    //extraText  = "Unpublished";
    CMS_lumi( canv, iPeriod, 11 );
 
    gStyle->SetPadTickY(1);
    canv->Update();
    canv->RedrawAxis();
    canv->GetFrame()->Draw();    
    canv->SaveAs(Form("img/XeXevsPbPb_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
    canv->SaveAs(Form("img/XeXevsPbPb_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
    canv->SaveAs(Form("img/XeXevsPbPb_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c])); 
  }
}


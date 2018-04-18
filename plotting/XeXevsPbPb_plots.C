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

  float TAAU_05_1030 = 0;
  float TAAD_05_1030 = 0;
  float TAAU_510_1030 = 0;
  float TAAD_510_1030 = 0;
 
  Settings s = Settings();

  TFile * ppFit = TFile::Open(Form("../%s",s.ppRefFile.c_str()),"read");
  TF1 * extrapFunc = (TF1*)ppFit->Get("extrapFuncPoly4");
  
  TH1D * h[s.nCentBins];
  TH1D * XePb05vs1030, * XePb510vs1030;
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

  TFile * sysFile = TFile::Open("../systematics.root","read");
  TH1D * RXP_totSyst[s.nCentBins];
  TH1D * RXP_NPart_totSyst[2];
  TH1D * evtSelSyst[s.nCentBins];
  //XeXe systematic
  for(int c = 0; c<s.nCentBins; c++){
    if(c==0 || c==1) RXP_NPart_totSyst[c] = (TH1D*)sysFile->Get(Form("RXP_Total_NPart_%d",c));
    RXP_totSyst[c] = (TH1D*)sysFile->Get(Form("RXP_Total_%d",c));
    RXP_totSyst[c]->SetDirectory(0);
    evtSelSyst[c] = (TH1D*)sysFile->Get(Form("RXP_EventSelection_%d",c));
    evtSelSyst[c]->SetDirectory(0);
  }

  TH1D * PbPb[6];
  TH1D * PbPb_stat[6];
  TH1D * PbPb_syst[6];

  //
  float TAA[6] = {26.0,20.5,11.5,3.82,0.934,0.152};
  float PbPbTAAUncertU[6] = {0.5,0.4,0.3,0.21,0.096,0.024};
  float PbPbTAAUncertD[6] = {0.8,0.6,0.4,0.21,0.089,0.021};
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
    if(c==0)  XePb05vs1030 = new TH1D("XePb05vs1030","",s.ntrkBins,s.xtrkbins);
    if(c==1)  XePb510vs1030 = new TH1D("XePb510vs1030","",s.ntrkBins,s.xtrkbins);
 
    for(int i = 1; i<h[c]->GetSize(); i++){
      if(i==1 || i==2){
        h[c]->SetBinContent(i,0);
        h[c]->SetBinError(i,0);
        continue;
      }

      float relErr = h[c]->GetBinError(i)/h[c]->GetBinContent(i);
      float PbPbContent = PbPb[PbPbBin]->GetBinContent(PbPb[PbPbBin]->FindBin(h[c]->GetBinCenter(i)));
      float PbPbRelErr = PbPb[PbPbBin]->GetBinError(PbPb[PbPbBin]->FindBin(h[c]->GetBinCenter(i)))/PbPbContent;

      if(i==27 || i==28 || i==29){
        int bin = PbPb[0]->FindBin(h[c]->GetBinLowEdge(i));
        PbPbContent = PbPb[PbPbBin]->GetBinContent(bin)*PbPb[PbPbBin]->GetBinCenter(bin)*PbPb[PbPbBin]->GetBinWidth(bin)+PbPb[PbPbBin]->GetBinContent(bin+1)*PbPb[PbPbBin]->GetBinCenter(bin+1)*PbPb[PbPbBin]->GetBinWidth(bin+1);
        PbPbContent = PbPbContent/h[c]->GetBinWidth(i)/h[c]->GetBinCenter(i);
        PbPbRelErr = TMath::Power(TMath::Power(PbPb[PbPbBin]->GetBinError(bin)*PbPb[PbPbBin]->GetBinCenter(bin)*PbPb[PbPbBin]->GetBinWidth(bin),2)+TMath::Power(PbPb[PbPbBin]->GetBinError(bin+1)*PbPb[PbPbBin]->GetBinCenter(bin+1)*PbPb[PbPbBin]->GetBinWidth(bin+1),2),0.5)/h[c]->GetBinWidth(i)/h[c]->GetBinCenter(i);
        PbPbRelErr = PbPbRelErr/PbPbContent;
      }
 
      float temphc = h[c]->GetBinContent(i);

      h[c]->SetBinContent(i,h[c]->GetBinContent(i)/PbPbContent);
      h[c]->SetBinError(i,TMath::Power(relErr*relErr+PbPbRelErr*PbPbRelErr,0.5));

      if(c==0){ 
        PbPbContent = PbPb[2]->GetBinContent(PbPb[2]->FindBin(h[c]->GetBinCenter(i))); 
        PbPbRelErr = PbPb[2]->GetBinError(PbPb[2]->FindBin(h[c]->GetBinCenter(i)))/PbPbContent;
        if(i==27 || i==28 || i==29){
          int bin = PbPb[0]->FindBin(h[c]->GetBinLowEdge(i));
          PbPbContent = PbPb[2]->GetBinContent(bin)*PbPb[2]->GetBinCenter(bin)*PbPb[2]->GetBinWidth(bin)+PbPb[2]->GetBinContent(bin+1)*PbPb[2]->GetBinCenter(bin+1)*PbPb[2]->GetBinWidth(bin+1);
          PbPbContent = PbPbContent/h[c]->GetBinWidth(i)/h[c]->GetBinCenter(i);
          PbPbRelErr = TMath::Power(TMath::Power(PbPb[2]->GetBinError(bin)*PbPb[2]->GetBinCenter(bin)*PbPb[2]->GetBinWidth(bin),2)+TMath::Power(PbPb[2]->GetBinError(bin+1)*PbPb[2]->GetBinCenter(bin+1)*PbPb[2]->GetBinWidth(bin+1),2),0.5)/h[c]->GetBinWidth(i)/h[c]->GetBinCenter(i);
          PbPbRelErr = PbPbRelErr/PbPbContent;
        }
        XePb05vs1030->SetBinContent(i,temphc/PbPbContent);
        XePb05vs1030->SetBinError(i,TMath::Power(relErr*relErr+PbPbRelErr*PbPbRelErr,0.5));
      }
      if(c==1){ 
        PbPbContent = PbPb[2]->GetBinContent(PbPb[2]->FindBin(h[c]->GetBinCenter(i))); 
        PbPbRelErr = PbPb[2]->GetBinError(PbPb[2]->FindBin(h[c]->GetBinCenter(i)))/PbPbContent;
        if(i==27 || i==28 || i==29){
          int bin = PbPb[0]->FindBin(h[c]->GetBinLowEdge(i));
          PbPbContent = PbPb[2]->GetBinContent(bin)*PbPb[2]->GetBinCenter(bin)*PbPb[2]->GetBinWidth(bin)+PbPb[2]->GetBinContent(bin+1)*PbPb[2]->GetBinCenter(bin+1)*PbPb[2]->GetBinWidth(bin+1);
          PbPbContent = PbPbContent/h[c]->GetBinWidth(i)/h[c]->GetBinCenter(i);
          PbPbRelErr = TMath::Power(TMath::Power(PbPb[2]->GetBinError(bin)*PbPb[2]->GetBinCenter(bin)*PbPb[2]->GetBinWidth(bin),2)+TMath::Power(PbPb[2]->GetBinError(bin+1)*PbPb[2]->GetBinCenter(bin+1)*PbPb[2]->GetBinWidth(bin+1),2),0.5)/h[c]->GetBinWidth(i)/h[c]->GetBinCenter(i);
          PbPbRelErr = PbPbRelErr/PbPbContent;
        }
        XePb510vs1030->SetBinContent(i,temphc/PbPbContent);
        XePb510vs1030->SetBinError(i,TMath::Power(relErr*relErr+PbPbRelErr*PbPbRelErr,0.5));
      }

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
    h[c]->GetYaxis()->SetRangeUser(0,2);

    h[c]->GetXaxis()->SetTitleSize(0.06);
    h[c]->GetYaxis()->SetTitleSize(0.06);
    h[c]->GetYaxis()->SetTitleOffset(1.0);
    h[c]->GetXaxis()->SetTitleOffset(0.87);
    h[c]->GetYaxis()->SetLabelSize(0.055);
    h[c]->GetXaxis()->SetLabelSize(0.055);
    h[c]->GetXaxis()->SetLabelOffset(-0.017);

    h[c]->SetMarkerSize(1.3);
    h[c]->Draw();


    TAAUncert = s.TAAuncert[c];    

    double PbPbU=0;
    double PbPbD=0;
    PbPbU = PbPbTAAUncertU[PbPbBin]/TAA[PbPbBin];
    PbPbD = PbPbTAAUncertD[PbPbBin]/TAA[PbPbBin];
    double evtSel = evtSelSyst[c]->GetBinContent(2);
    double TAAUncertU = TMath::Sqrt(TMath::Power(s.TAAuncert[c]/100.0,2)+PbPbU*PbPbU+evtSel*evtSel);
    double TAAUncertD = TMath::Sqrt(TMath::Power(s.TAAuncert[c]/100.0,2)+PbPbD*PbPbD+evtSel*evtSel);
    
    if(c==0){    
      PbPbU = PbPbTAAUncertU[2]/TAA[2];
      PbPbD = PbPbTAAUncertD[2]/TAA[2];
      TAAU_05_1030 = TMath::Sqrt(TMath::Power(s.TAAuncert[c]/100.0,2)+PbPbU*PbPbU+evtSel*evtSel);
      TAAD_05_1030 = TMath::Sqrt(TMath::Power(s.TAAuncert[c]/100.0,2)+PbPbD*PbPbD+evtSel*evtSel);
    }
    if(c==1){
      PbPbU = PbPbTAAUncertU[2]/TAA[2];
      PbPbD = PbPbTAAUncertD[2]/TAA[2];
      TAAU_510_1030 = TMath::Sqrt(TMath::Power(s.TAAuncert[c]/100.0,2)+PbPbU*PbPbU+evtSel*evtSel);
      TAAD_510_1030 = TMath::Sqrt(TMath::Power(s.TAAuncert[c]/100.0,2)+PbPbD*PbPbD+evtSel*evtSel);
    }

    bTAA->SetFillColor(kRed+1);
    bTAA->SetLineWidth(0);
    bTAA->DrawBox(0.575,1-TAAUncertD,TMath::Power(10,TMath::Log10(0.575)+(TMath::Log10(0.675)-TMath::Log10(0.575))/2.0),1+TAAUncertU);
    bTAA->DrawBox(0.7,0.475,0.85,0.55);
      
    line1 = new TLine(h[c]->GetXaxis()->GetBinLowEdge(1),1,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2),1);
    line1->SetLineWidth(2);
    line1->SetLineStyle(2);
    line1->Draw("same");
  
    tex2->SetTextSize(lumiTextSize*0.15);
    if(c==30) tex2->DrawLatex(0.7,0.1,"70-80% / 70-90%");
    else tex2->DrawLatex(0.7,0.1,Form("%d-%d%s",5*s.lowCentBin[c],5*s.highCentBin[c],"%"));
    tex->SetTextFont(42);
    tex->SetTextSize(lumiTextSize*0.095);
    tex->DrawLatex(0.9,0.47,"Normalization uncertainty");
    tex->DrawLatex(0.9,0.35,"Expectation from #sqrt{s_{NN}} difference ");
    bTAA->SetFillColor(kBlue);
    bTAA->DrawBox(0.7,0.395,0.85,0.405);
    tex->DrawLatex(0.7,0.6,"|#eta| < 1");
 
    for(int i = 3; i<(h[0]->GetSize()-1); i++){ 
      b[i-1]->SetFillColor(kRed-7);
      float error = RXP_totSyst[c]->GetBinContent(i);
      b[i-1]->SetX1(h[c]->GetXaxis()->GetBinLowEdge(i));
      b[i-1]->SetX2(h[c]->GetXaxis()->GetBinUpEdge(i));
      b[i-1]->SetY1((h[c]->GetBinContent(i))*(1-error));
      b[i-1]->SetY2(h[c]->GetBinContent(i)*(1+error));
      if(c==30 && i>=28) continue;
      if(c==25 && i>=29) continue;
      b[i-1]->Draw("same");
    }

    extrapFunc->SetLineStyle(1); 
    extrapFunc->SetLineWidth(2); 
    extrapFunc->SetLineColor(kBlue); 
    extrapFunc->SetRange(0.65,103.6); 
    extrapFunc->Draw("same");
    
    h[c]->SetMarkerSize(1.3);
    h[c]->SetLineWidth(2);

    if(c==25){
      h[25]->SetBinError(29,0);
      h[25]->SetBinContent(29,0);  
    } 
    if(c==30){
      h[30]->SetBinContent(28,0);
      h[30]->SetBinError(28,0);
      h[30]->SetBinContent(29,0);  
      h[30]->SetBinContent(30,0);  
      h[30]->SetBinContent(31,0);  
      h[30]->SetBinContent(32,0);  
      h[30]->SetBinError(29,0);  
      h[30]->SetBinError(30,0);  
      h[30]->SetBinError(31,0);  
      h[30]->SetBinError(32,0);  
    }

    h[c]->Draw("same");
 
    int iPeriod = 0;
    lumi_sqrtS = "404 #mub^{-1} (5.02 TeV PbPb) + 3.42 #mub^{-1} (5.44 TeV XeXe)";
    writeExtraText = false;  
    //extraText  = "Preliminary";
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

  XePb05vs1030->GetYaxis()->SetRangeUser(0,2);
  XePb05vs1030->SetMarkerSize(1.3);
  XePb05vs1030->SetLineWidth(2);
  XePb05vs1030->GetYaxis()->SetTitleOffset(1.5);
  XePb05vs1030->GetXaxis()->SetTitleOffset(1.2);
  XePb05vs1030->GetYaxis()->CenterTitle();
  XePb05vs1030->GetXaxis()->SetTitle("p_{T} (GeV)");
  XePb05vs1030->GetXaxis()->CenterTitle();
  XePb05vs1030->GetXaxis()->SetLabelOffset(-0.005);
  XePb05vs1030->GetXaxis()->SetTitleSize(0.06);
  XePb05vs1030->GetYaxis()->SetTitleSize(0.06);
  XePb05vs1030->GetYaxis()->SetTitleOffset(1.0);
  XePb05vs1030->GetXaxis()->SetTitleOffset(0.87);
  XePb05vs1030->GetYaxis()->SetLabelSize(0.055);
  XePb05vs1030->GetXaxis()->SetLabelSize(0.055);
  XePb05vs1030->GetXaxis()->SetLabelOffset(-0.017);
  XePb05vs1030->Draw();
  line1 = new TLine(h[0]->GetXaxis()->GetBinLowEdge(1),1,h[0]->GetXaxis()->GetBinUpEdge(h[0]->GetSize()-2),1);
  line1->SetLineWidth(2);
  line1->SetLineStyle(2);
  line1->Draw("same");
  XePb05vs1030->GetYaxis()->SetTitle("R^{Xe}_{Pb}");
  for(int i = 3; i<(h[0]->GetSize()-1); i++){ 
    b[i-1]->SetFillColor(kRed-7);
    float error = RXP_NPart_totSyst[0]->GetBinContent(i);
    b[i-1]->SetX1(h[0]->GetXaxis()->GetBinLowEdge(i));
    b[i-1]->SetX2(h[0]->GetXaxis()->GetBinUpEdge(i));
    b[i-1]->SetY1((XePb05vs1030->GetBinContent(i))*(1-error));
    b[i-1]->SetY2(XePb05vs1030->GetBinContent(i)*(1+error));
    b[i-1]->Draw("same");
  }
  extrapFunc->Draw("same");
  XePb05vs1030->Draw("same");
    tex->DrawLatex(0.9,0.47,"Normalization uncertainty");
    tex->DrawLatex(0.9,0.35,"Expectation from #sqrt{s_{NN}} difference ");
    bTAA->SetFillColor(kBlue);
    bTAA->DrawBox(0.7,0.395,0.85,0.405);
    bTAA->SetFillColor(kRed+1);
    bTAA->DrawBox(0.575,1-TAAD_05_1030,TMath::Power(10,TMath::Log10(0.575)+(TMath::Log10(0.675)-TMath::Log10(0.575))/2.0),1+TAAU_05_1030);
    bTAA->DrawBox(0.7,0.475,0.85,0.55);
    tex->DrawLatex(0.7,0.6,"|#eta| < 1");
  tex2->DrawLatex(0.7,0.1,"0-5% / 10-30%");
    int iPeriod = 0;
    lumi_sqrtS = "404 #mub^{-1} (5.02 TeV PbPb) + 3.42 #mub^{-1} (5.44 TeV XeXe)";
    writeExtraText = false;  
    //extraText  = "Preliminary";
    //extraText  = "Unpublished";
    CMS_lumi( canv, iPeriod, 11 );
  canv->SaveAs("img/XeXevsPbPb_samenPart05.png");
  canv->SaveAs("img/XeXevsPbPb_samenPart05.pdf");
  canv->SaveAs("img/XeXevsPbPb_samenPart05.C");
  XePb510vs1030->GetYaxis()->SetRangeUser(0,2);
  XePb510vs1030->SetMarkerSize(1.3);
  XePb510vs1030->SetLineWidth(2);
  XePb510vs1030->GetYaxis()->SetTitleOffset(1.5);
  XePb510vs1030->GetXaxis()->SetTitleOffset(1.2);
  XePb510vs1030->GetYaxis()->CenterTitle();
  XePb510vs1030->GetXaxis()->SetTitle("p_{T} (GeV)");
  XePb510vs1030->GetXaxis()->CenterTitle();
  XePb510vs1030->GetXaxis()->SetLabelOffset(-0.005);
  XePb510vs1030->GetXaxis()->SetTitleSize(0.06);
  XePb510vs1030->GetYaxis()->SetTitleSize(0.06);
  XePb510vs1030->GetYaxis()->SetTitleOffset(1.0);
  XePb510vs1030->GetXaxis()->SetTitleOffset(0.87);
  XePb510vs1030->GetYaxis()->SetLabelSize(0.055);
  XePb510vs1030->GetXaxis()->SetLabelSize(0.055);
  XePb510vs1030->GetXaxis()->SetLabelOffset(-0.017);
  XePb510vs1030->Draw();
  line1->Draw("same");
  XePb510vs1030->GetYaxis()->SetTitle("R^{Xe}_{Pb}");
  for(int i = 3; i<(h[0]->GetSize()-1); i++){ 
    b[i-1]->SetFillColor(kRed-7);
    float error = RXP_NPart_totSyst[1]->GetBinContent(i);
    b[i-1]->SetX1(h[0]->GetXaxis()->GetBinLowEdge(i));
    b[i-1]->SetX2(h[0]->GetXaxis()->GetBinUpEdge(i));
    b[i-1]->SetY1((XePb510vs1030->GetBinContent(i))*(1-error));
    b[i-1]->SetY2(XePb510vs1030->GetBinContent(i)*(1+error));
    b[i-1]->Draw("same");
  }
  extrapFunc->Draw("same");
  XePb510vs1030->Draw("same");
    tex->DrawLatex(0.9,0.47,"Normalization uncertainty");
    tex->DrawLatex(0.9,0.35,"Expectation from #sqrt{s_{NN}} difference ");
    bTAA->SetFillColor(kBlue);
    bTAA->DrawBox(0.7,0.395,0.85,0.405);
    bTAA->SetFillColor(kRed+1);
    bTAA->DrawBox(0.575,1-TAAD_510_1030,TMath::Power(10,TMath::Log10(0.575)+(TMath::Log10(0.675)-TMath::Log10(0.575))/2.0),1+TAAU_510_1030);
    bTAA->DrawBox(0.7,0.475,0.85,0.55);
    tex->DrawLatex(0.7,0.6,"|#eta| < 1");
  tex2->DrawLatex(0.7,0.1,"5-10% / 10-30%");

    writeExtraText = true;
    extraText = "Supplementary";
    CMS_lumi( canv, iPeriod, 11 );
  canv->SaveAs("img/XeXevsPbPb_samenPart510.png");
  canv->SaveAs("img/XeXevsPbPb_samenPart510.pdf");
  canv->SaveAs("img/XeXevsPbPb_samenPart510.C");

}


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

void getTheoryXinNian(TGraph * xinnian, int cent = 0){
  //Vitev**********************************************************************************************************
  float temp_x;
  float temp_y;
  vector<float> x;
  vector<float> y_d;
  std::string inputFile;
  if(cent==0) inputFile = "../theory/for_XeXe/RAA_XeXe5440_cen-00-10.dat";
  if(cent==1) inputFile = "../theory/for_XeXe/RAA_XeXe5440_cen-30-50.dat";
  ifstream input_file_d(inputFile);
  //get datai
  std::cout << "reading theory prediction data" << std::endl;
  while(!input_file_d.eof()){ 
    input_file_d>>temp_x;
    input_file_d>>temp_y;
    std::cout << temp_x << " " << temp_y << std::endl;
    x.push_back(temp_x);
    y_d.push_back(temp_y);
  }
  
  //put data in histograms
  const int graphPts = 24;
  //vitev = TGraph(2*graphPts);
  for (int i=0;i<graphPts;i++) {
    //std::cout << x[i] << " " << y_d[i] << " " << y_u[i] << std::endl;
    xinnian->SetPoint(i,x[i],y_d[i]);
  }
  xinnian->SetLineColor(kViolet);
  xinnian->SetLineWidth(2);
}
void getTheoryVitev(TGraph * vitev){
  //Vitev**********************************************************************************************************
  float temp_x;
  float temp_y;
  vector<float> x;
  vector<float> y_d;
  vector<float> y_u;
  ifstream input_file_d("../theory/XeXe010chDN.txt");
  ifstream input_file_u("../theory/XeXe010chUP.txt");
  //get datai
  std::cout << "reading theory prediction data" << std::endl;
  while(!input_file_d.eof()){ 
    input_file_d>>temp_x;
    input_file_d>>temp_y;
    std::cout << temp_x << " " << temp_y << std::endl;
    x.push_back(temp_x);
    y_d.push_back(temp_y);
  }
  while(!input_file_u.eof()){ 
    input_file_u>>temp_x;
    input_file_u>>temp_y;
    std::cout << temp_y << std::endl;
    y_u.push_back(temp_y);
  }
  std::cout << "done reading " << x.size() << " Points"  << std::endl;
  
  //put data in histograms
  const int graphPts = 950;
  //vitev = TGraph(2*graphPts);
  for (int i=0;i<graphPts;i++) {
    //std::cout << x[i] << " " << y_d[i] << " " << y_u[i] << std::endl;
    vitev->SetPoint(i,x[i],y_d[i]);
    vitev->SetPoint(graphPts+i,x[graphPts-i-1],y_u[graphPts-i-1]);
  }
  gStyle->SetHatchesLineWidth(2);
  gStyle->SetHatchesSpacing(1);
  vitev->SetFillStyle(3335);
  //vitev->SetFillStyle(3002);
  //vitev->SetFillColor(kRed);
  vitev->SetFillColor(kGreen+1);
  vitev->SetLineWidth(0);
}
void getTheoryCUJET(TGraph * cujet, int cent){
  //Vitev**********************************************************************************************************
  float temp_x;
  float temp_y_u, temp_y_d;
  float temp;
  vector<float> x;
  vector<float> y_d;
  vector<float> y_u;
  ifstream input_file("../theory/CUJET/CUJET_5440_XeXe_RAA_parsed.dat");
  //get datai
  std::cout << "reading theory prediction data" << std::endl;
  while(!input_file.eof()){ 
    input_file>>temp_x;
    if(cent==1){
      input_file>>temp;
      input_file>>temp;
    }
    input_file>>temp_y_u;
    input_file>>temp_y_d;
    if(cent==0){
      input_file>>temp;
      input_file>>temp;
    }
    std::cout << temp_x << " " << temp_y_u << " " << temp_y_d << std::endl;
    x.push_back(temp_x);
    y_d.push_back(temp_y_d);
    y_u.push_back(temp_y_u);
  }
  std::cout << "done reading " << x.size() << " Points"  << std::endl;
  
  //put data in histograms
  const int graphPts = 180;
  //vitev = TGraph(2*graphPts);
  for (int i=0;i<graphPts;i++) {
    //std::cout << x[i] << " " << y_d[i] << " " << y_u[i] << std::endl;
    cujet->SetPoint(i,x[i],y_d[i]);
    cujet->SetPoint(graphPts+i,x[graphPts-i-1],y_u[graphPts-i-1]);
  }
  gStyle->SetHatchesLineWidth(2);
  gStyle->SetHatchesSpacing(1);
  //cujet->SetFillStyle(3013);
  cujet->SetFillStyle(3359);
  cujet->SetFillColor(kBlue);
  cujet->SetLineWidth(0);
}
//***************************************************************************************************8

//0 vitev
//1 CUJET
//2 Xin-Nian LBT
void makeThRatio(TGraph * g, TGraph * rat, TH1D * h, int prediction){
  int graphPts, ratPts;
  graphPts = g->GetN()/2;
  ratPts = rat->GetN()/2;
  if(prediction==2){
    graphPts = g->GetN();
    ratPts = rat->GetN();
  }
  
  int setPoints = 0;

  for(int i=1;i<h->GetXaxis()->GetNbins()+1; i++){
    double x = h->GetXaxis()->GetBinCenter(i);
    double xg, yg;
    double xg2, yg2;
    for(int j = 0; j<graphPts; j++){
      g->GetPoint(j,xg,yg);
      g->GetPoint(j+1,xg2,yg2);
      if(x>=xg && x<xg2){
        //first edge
        double interp = yg+(yg2-yg)*(x-xg)/(xg2-xg);
        rat->SetPoint(setPoints, x, interp/h->GetBinContent(i)); 

        //other edge
        if(prediction!=2){
          g->GetPoint((2*graphPts-1)-j,xg,yg);
          g->GetPoint((2*graphPts-1)-(j+1),xg2,yg2);
          interp = yg+(yg2-yg)*(x-xg)/(xg2-xg);
          rat->SetPoint(2*ratPts-1-setPoints, x, interp/h->GetBinContent(i)); 
        }

        setPoints++;
        break;
      } 
    }
  } 
  if(prediction==0){
    gStyle->SetHatchesLineWidth(2);
    gStyle->SetHatchesSpacing(1);
    rat->SetFillStyle(3335);
    rat->SetFillColor(kGreen+1);
    rat->SetLineWidth(0);
  } 
  if(prediction==1){
    gStyle->SetHatchesLineWidth(2);
    gStyle->SetHatchesSpacing(1);
    rat->SetFillStyle(3359);
    rat->SetFillColor(kBlue);
    rat->SetLineWidth(0);
  } 
  if(prediction==2){
    rat->SetLineColor(kViolet);
    rat->SetLineWidth(2);
  } 
}

void RAA_plots(){
  TH1::SetDefaultSumw2();
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
 
  Settings s = Settings();
  TGraphAsymmErrors * sumNcoll[2][s.ntrkBins];
  TGraphAsymmErrors * sumNpart[2][s.ntrkBins];
  TGraphAsymmErrors * sumNcollPb[2][s.ntrkBins];
  TGraphAsymmErrors * sumNpartPb[2][s.ntrkBins];
  for(int i = 0; i<s.ntrkBins; i++){
    sumNcoll[0][i] = new TGraphAsymmErrors(6);
    sumNpart[0][i] = new TGraphAsymmErrors(6);
    sumNcollPb[0][i] = new TGraphAsymmErrors(6);
    sumNpartPb[0][i] = new TGraphAsymmErrors(6);
    sumNcoll[1][i] = new TGraphAsymmErrors(6);
    sumNpart[1][i] = new TGraphAsymmErrors(6);
    sumNcollPb[1][i] = new TGraphAsymmErrors(6);
    sumNpartPb[1][i] = new TGraphAsymmErrors(6);
  }

  //loading 5.02 TeV PbPb
  TFile * f1 = TFile::Open("PbPbRAAs/HEPData-ins1496050-v2-root.root","read"); 
  TH1D * PbPb[8];
  TH1D * PbPb_stat[8];
  TH1D * PbPb_syst[8];
  TH1D * PbPb_systTAAU[8];
  TH1D * PbPb_systTAAD[8];
  TH1D * PbPb_systLumi[8];
  for(int i = 0; i<8; i++){
    PbPb[i] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1",i+8));
    PbPb_stat[i] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e1",i+8));
    PbPb_syst[i] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e2",i+8));
    PbPb_systTAAU[i] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e3plus",i+8));
    PbPb_systTAAD[i] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e3minus",i+8));
    PbPb_systLumi[i] = (TH1D*) f1->Get(Form("Table %d/Hist1D_y1_e4",i+8));
    for(int j = 1; j<PbPb[i]->GetSize(); j++){
      PbPb[i]->SetBinError(j,PbPb_stat[i]->GetBinContent(j));
      if(i>5) continue;
      float err2U = TMath::Power(PbPb_systLumi[i]->GetBinContent(j),2)+TMath::Power(PbPb_syst[i]->GetBinContent(j),2)+TMath::Power(PbPb_systTAAU[i]->GetBinContent(j),2);
      float err2D = TMath::Power(PbPb_systLumi[i]->GetBinContent(j),2)+TMath::Power(PbPb_syst[i]->GetBinContent(j),2)+TMath::Power(PbPb_systTAAD[i]->GetBinContent(j),2);

      if(j>s.ntrkBins-3) continue;
      sumNcollPb[0][j+1]->SetPoint(i,s.PbPbNcoll[i],PbPb[i]->GetBinContent(j));
      sumNcollPb[0][j+1]->SetPointError(i,s.PbPbNcollErrD[i],s.PbPbNcollErrU[i],TMath::Sqrt(err2D),TMath::Sqrt(err2U));
      sumNpartPb[0][j+1]->SetPoint(i,s.PbPbNpart[i],PbPb[i]->GetBinContent(j));
      sumNpartPb[0][j+1]->SetPointError(i,s.PbPbNpartErrD[i],s.PbPbNpartErrU[i],TMath::Sqrt(err2D),TMath::Sqrt(err2U));
      sumNcollPb[1][j+1]->SetPoint(i,s.PbPbNcoll[i],PbPb[i]->GetBinContent(j));
      sumNcollPb[1][j+1]->SetPointError(i,0,0,PbPb_stat[i]->GetBinContent(j),PbPb_stat[i]->GetBinContent(j));
      sumNpartPb[1][j+1]->SetPoint(i,s.PbPbNpart[i],PbPb[i]->GetBinContent(j));
      sumNpartPb[1][j+1]->SetPointError(i,0,0,PbPb_stat[i]->GetBinContent(j),PbPb_stat[i]->GetBinContent(j));
    }
  }//done loading PbPb

  TH1D * h[s.nCentBins];
  TH1D * ppSpec;
  TH1D * nVtx;
  TFile * f = TFile::Open("../output_0.root","read");
  ppSpec = (TH1D*)f->Get("ppScaled_WithFit");
  nVtx = (TH1D*)f->Get("nVtxMoreBin");

  for(int c = 0; c<s.nCentBins; c++){
    h[c] = (TH1D*)f->Get(Form("HI_TaaWeighted_%d_%d",s.lowCentBin[c]*5,s.highCentBin[c]*5));
    h[c]->Divide(ppSpec);
    h[c]->Scale(1.0/nVtx->GetBinContent(nVtx->GetXaxis()->FindBin(c)));
    h[c]->SetDirectory(0);
    //h[c]->Print("All");
    
    //filling Graph
    if(c!=0 && c!=1 && c!= 23 && c!=24 && c!= 25 && c!=30) continue;
    int cc = c;
    if(c==23) cc=2;
    if(c==24) cc=3;
    if(c==25) cc=4;
    if(c==30) cc=5;
    for(int i = 1; i<h[c]->GetSize()-1; i++){
      sumNcoll[0][i-1]->SetPoint(cc,s.XeXeNcoll[cc],h[c]->GetBinContent(i));
      sumNpart[0][i-1]->SetPoint(cc,s.XeXeNpart[cc],h[c]->GetBinContent(i));
      sumNcoll[1][i-1]->SetPoint(cc,s.XeXeNcoll[cc],h[c]->GetBinContent(i));
      sumNpart[1][i-1]->SetPoint(cc,s.XeXeNpart[cc],h[c]->GetBinContent(i));
    }
  }
  f->Close();
  
  TFile * sysFile = TFile::Open("../systematics.root","read");
  TH1D * XeXeRAA_totSyst[s.nCentBins];
  TH1D * evtSelSyst[s.nCentBins];
  //XeXe systematic
  for(int c = 0; c<s.nCentBins; c++){
    XeXeRAA_totSyst[c] = (TH1D*)sysFile->Get(Form("RAA_Total_%d",c));
    XeXeRAA_totSyst[c]->SetDirectory(0);
    evtSelSyst[c] = (TH1D*)sysFile->Get(Form("RAA_EventSelection_%d",c));
    evtSelSyst[c]->SetDirectory(0);
  }

  setTDRStyle();
  TLine * line1;
  TLatex * tex = new TLatex(0.1,0.1,"cent");
  TLatex * tex2 = new TLatex(0.1,0.1,"cent");
  TBox* bLumi = new TBox(0.1,0.1,0.15,0.2); 
  TBox* bTAA = new TBox(0.15,0.1,0.2,0.2); 
  TBox* b[s.ntrkBins];
  TBox* bPbPb[s.ntrkBins+3];
  for(int i = 0; i<s.ntrkBins+3; i++){
    b[i] = new TBox(0.1,0.1,0.2,0.2); 
    bPbPb[i] = new TBox(0.1,0.1,0.2,0.2); 
  }

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
  

  bool isFirstLoop = true;
  for(int c = 0; c<s.nCentBins; c++){
    //plotting
    TCanvas* canvTh = new TCanvas("RAATh","RAATh",50,50,W,H*1.25);
    TPad * pad1 = new TPad("pad1","pad1",0.0,0.2,1.0,1.0,0);
    TPad * pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.2,0);
    if(!isFirstLoop){
      canvTh->SetLogx();
      canvTh->SetFillColor(0);
      canvTh->SetBorderMode(0);
      canvTh->SetFrameFillStyle(0);
      canvTh->SetFrameBorderMode(0);
      canvTh->SetLeftMargin( L/W );
      canvTh->SetRightMargin( R/W );
      canvTh->SetTopMargin( T/(H*1.25) );
      canvTh->SetBottomMargin( B/(H*1.25) );
      canvTh->SetTickx(1);
      canvTh->SetTicky(1);
     
      gStyle->SetErrorX(0);

      canvTh->SetLineWidth(0);
      pad1->SetRightMargin( R/W );
      pad1->SetBottomMargin(0);
      pad1->SetLogx();
      pad1->SetLeftMargin(0.15);
      pad1->SetTopMargin(0.07);
      pad1->SetBorderSize(0);
      pad1->Draw();
      pad2->SetLogx();
      pad2->SetRightMargin( R/W );
      pad2->SetTopMargin(0);
      pad2->SetLeftMargin(0.15);
      pad2->SetBottomMargin(0.4);
      pad2->SetBorderSize(0);
      pad2->Draw();
      pad1->cd();
    }
    else{
      canv->Clear();
      canv->cd();
    }


    h[c]->SetLineColor(kBlack);
    h[c]->SetMarkerStyle(8);
    h[c]->GetXaxis()->SetTitle("p_{T} (GeV)");
    h[c]->GetXaxis()->CenterTitle();
    h[c]->GetYaxis()->SetTitle("R*_{AA}, R_{AA}");
    h[c]->GetXaxis()->SetTitleSize(0.06);
    h[c]->GetYaxis()->SetTitleSize(0.06);
    h[c]->GetYaxis()->SetTitleOffset(1.0);
    h[c]->GetXaxis()->SetTitleOffset(0.87);
    h[c]->GetYaxis()->SetLabelSize(0.055);
    h[c]->GetXaxis()->SetLabelSize(0.055);
    h[c]->GetXaxis()->SetLabelOffset(-0.017);
    h[c]->GetYaxis()->CenterTitle();
    h[c]->GetXaxis()->SetRangeUser(0.5,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2));
    h[c]->GetYaxis()->SetRangeUser(0,1.6);
    if(!isFirstLoop) h[c]->GetYaxis()->SetRangeUser(0.001,1.6);
    h[c]->SetMarkerSize(1.3);
   
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
    h[c]->Draw();

    
    float lumiUncert = 0.023;//2.3% for pp lumi
    float TAAUncert = s.TAAuncert[c]/100.0;
    float evtSel = evtSelSyst[c]->GetBinContent(2);
    float totUncert = TMath::Power(lumiUncert*lumiUncert+TAAUncert*TAAUncert+evtSel*evtSel,0.5);
    bLumi->SetFillColor(kGray);
    bTAA->SetFillColor(kRed+1);
    bLumi->SetLineWidth(0);
    bTAA->SetLineWidth(0);
    bTAA->DrawBox(0.55,1-totUncert,TMath::Power(10,TMath::Log10(0.55)+(TMath::Log10(0.75)-TMath::Log10(0.55))/2.0),1+totUncert);
    //bLumi->DrawBox(TMath::Power(10,TMath::Log10(0.55)+(TMath::Log10(0.75)-TMath::Log10(0.55))/2.0),1-lumiUncert,0.75,1+lumiUncert);
      

    line1 = new TLine(h[c]->GetXaxis()->GetBinLowEdge(1),1,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2),1);
    line1->SetLineWidth(2);
    line1->SetLineStyle(2);
    line1->Draw("same");
  
    tex2->SetTextSize(lumiTextSize*0.15);
    tex2->DrawLatex(0.9,0.1,Form("%d-%d%s",5*s.lowCentBin[c],5*s.highCentBin[c],"%"));
    tex->SetTextFont(42);
    tex->SetTextSize(lumiTextSize*0.095);
    //tex->DrawLatex(0.8,1.04,"XeXe T_{AA} and pp lumi. uncertainty");
    tex->DrawLatex(0.7,1.04,"Normalization uncertainty");
    tex->DrawLatex(0.7,0.92,"|#eta| < 1");
  
    for(int i = 1; i< (h[0]->GetSize()-1); i++){
      b[i-1]->SetFillColor(kRed-7);
      b[i-1]->SetX1(h[c]->GetXaxis()->GetBinLowEdge(i));
      b[i-1]->SetX2(h[c]->GetXaxis()->GetBinUpEdge(i));
      b[i-1]->SetY1((h[c]->GetBinContent(i))*(1-XeXeRAA_totSyst[c]->GetBinContent(i)));
      b[i-1]->SetY2((h[c]->GetBinContent(i))*(1+XeXeRAA_totSyst[c]->GetBinContent(i)));
      if(c==30 && i>=29) continue;
      b[i-1]->Draw("same");
      
      if(c!=0 && c!=1 && c!= 23 && c!=24 && c!= 25 && c!=30) continue;
      int cc = c;
      if(c==23) cc=2;
      if(c==24) cc=3;
      if(c==25) cc=4;
      if(c==30) cc=5;
      float err2 = TMath::Power(XeXeRAA_totSyst[c]->GetBinContent(i),2)+TMath::Power(totUncert,2);
      float err = TMath::Sqrt(err2)*h[c]->GetBinContent(i);
      sumNcoll[0][i-1]->SetPointError(cc,s.XeXeNcollErr[cc],s.XeXeNcollErr[cc],err,err);
      sumNpart[0][i-1]->SetPointError(cc,s.XeXeNpartErr[cc],s.XeXeNpartErr[cc],err,err);
      sumNcoll[1][i-1]->SetPointError(cc,0,0,h[c]->GetBinError(i),h[c]->GetBinError(i));
      sumNpart[1][i-1]->SetPointError(cc,0,0,h[c]->GetBinError(i),h[c]->GetBinError(i));

    }
    for(int i = 1; i< (h[0]->GetSize()-1)+3; i++){
      //PbPb syst error boxes    
      //31 is 0-10%, removed for now  
      if(c!=0 && c!=1 && c!= 23 && c!=24 && c!= 25 && c!=30 && c!=20) continue;
      int cc = c;
      if(c==23) cc=2;
      if(c==24) cc=3;
      if(c==25) cc=4;
      if(c==30) cc=5;
      if(c==31) cc=6;
      if(c==20) cc=7;
      if(i>2){
        bPbPb[i-3]->SetFillStyle(0);
        bPbPb[i-3]->SetLineColor(kBlue);
        bPbPb[i-3]->SetX1(PbPb_syst[0]->GetXaxis()->GetBinLowEdge(i-2));
        bPbPb[i-3]->SetX2(PbPb_syst[0]->GetXaxis()->GetBinUpEdge(i-2));
        float errU = TMath::Power(TMath::Power(PbPb_syst[cc]->GetBinContent(i-2),2)+TMath::Power(PbPb_systTAAU[cc]->GetBinContent(i-2),2)+TMath::Power(PbPb_systLumi[cc]->GetBinContent(i-2),2),0.5);
        float errD = TMath::Power(TMath::Power(PbPb_syst[cc]->GetBinContent(i-2),2)+TMath::Power(PbPb_systTAAD[cc]->GetBinContent(i-2),2)+TMath::Power(PbPb_systLumi[cc]->GetBinContent(i-2),2),0.5);
        bPbPb[i-3]->SetY1(PbPb[cc]->GetBinContent(i-2)+errU);
        bPbPb[i-3]->SetY2(PbPb[cc]->GetBinContent(i-2)-errD);
        bPbPb[i-3]->Draw("same");
      }
    }

    TLegend * leg = new TLegend(0.4,0.7,0.95,0.9);
    leg->SetFillStyle(0);
    //31 is 0-10%, removed for now
    if(!(c!=0 && c!=1 && c!= 23 && c!=24 && c!= 25 && c!=30 && c!=20)){
      int cc = c;
      if(c==23) cc=2;
      if(c==24) cc=3;
      if(c==25) cc=4;
      if(c==30) cc=5;
      if(c==31) cc=6;
      if(c==20) cc=7;
      PbPb[cc]->SetMarkerColor(kBlue);
      PbPb[cc]->SetLineColor(kBlue);
      PbPb[cc]->SetMarkerStyle(24);
      PbPb[cc]->SetMarkerSize(1.3);
      PbPb[cc]->Draw("same");
      
      h[c]->SetFillColor(kRed-7);
      h[c]->SetFillStyle(1001);
      leg->AddEntry(h[c],"CMS 5.44 TeV XeXe","plf");
      if(c==30) leg->AddEntry(PbPb[cc],"CMS 5.02 TeV PbPb (70-90%)","pl");
      if(c==20) leg->AddEntry(PbPb[cc],"CMS 5.02 TeV PbPb (0-100%)","pl");
      if(c!=20 && c!=30) leg->AddEntry(PbPb[cc],"CMS 5.02 TeV PbPb","pl");
      leg->SetBorderSize(0);
      leg->Draw("same");
    }
    h[c]->SetMarkerSize(1.3);
    h[c]->SetLineWidth(2);
    h[c]->Draw("same");
 
    int iPeriod = 0;
    lumi_sqrtS = " 27.4 pb^{-1} (5.02 TeV pp) + 3.42 #mub^{-1} (5.44 TeV XeXe)";
    writeExtraText = false;  
    //extraText  = "Preliminary";
    if(c==20){writeExtraText = true; extraText = "Supplementary";}
    //extraText  = "Unpublished";
    CMS_lumi( canv, iPeriod, 11 );
    writeExtraText = false;  
 
    gStyle->SetPadTickY(1);
    canv->Update();
    canv->RedrawAxis();
    canv->GetFrame()->Draw();    
    if(isFirstLoop){
      canv->SaveAs(Form("img/RAA_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
      canv->SaveAs(Form("img/RAA_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
      canv->SaveAs(Form("img/RAA_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c])); 
    }

    delete leg;
    //stuff with theory
    TLegend * legTh;
    if(5*s.lowCentBin[c]==0 && 5*s.highCentBin[c] == 10) legTh = new TLegend(0.4,0.7,0.95,0.9);
    else legTh = new TLegend(0.4,0.7666,0.95,0.9);
    legTh->SetFillStyle(0);
    gStyle->SetLegendBorderSize(0);
    legTh->SetTextSize(0.05);
    h[c]->SetFillColor(kRed-7);
    h[c]->SetFillStyle(1001);

    if(5*s.lowCentBin[c]==0 && 5*s.highCentBin[c] == 10 && !isFirstLoop){
      float lumiUncert = 0.023;//2.3% for pp lumi
      float TAAUncert = s.TAAuncert[c]/100.0;
      float evtSel = evtSelSyst[c]->GetBinContent(2);
      float totUncert = TMath::Power(lumiUncert*lumiUncert+TAAUncert*TAAUncert+evtSel*evtSel,0.5);
      TH1D * uncert = (TH1D*)XeXeRAA_totSyst[c]->Clone("histTemp");
      uncert->Print("All");
      TH1D * uncert2 = (TH1D*)XeXeRAA_totSyst[c]->Clone("histTemp2");
      for(int i = 1; i<uncert->GetSize()-1; i++){
        uncert->SetBinContent(i,1+TMath::Power(TMath::Power(uncert->GetBinContent(i),2)+TMath::Power(totUncert,2)+TMath::Power(h[c]->GetBinError(i),2),0.5));
        uncert->SetLineWidth(0);
        uncert->SetFillStyle(1001);
        uncert->SetFillColor(18);
        uncert2->SetBinContent(i,1-TMath::Power(TMath::Power(uncert2->GetBinContent(i),2)+TMath::Power(totUncert,2)+TMath::Power(h[c]->GetBinError(i),2),0.5));
        uncert2->SetLineWidth(0);
        uncert2->SetFillStyle(1001);
        uncert2->SetFillColor(10);
      }

      pad1->cd();
      const int graphPts = 950;
      TGraph * vitev = new TGraph(2*graphPts);
      getTheoryVitev(vitev);
      vitev->Draw("same f");

      TGraph * vitevRatio = new TGraph(2*13);
      makeThRatio(vitev, vitevRatio, h[c], 0);
      //vitev->Print("All");
      h[c]->Print("All");
      vitevRatio->Print("All");
     
      const int graphPtsXinNian = 24;
      TGraph * xinNian = new TGraph(graphPtsXinNian);
      getTheoryXinNian(xinNian,0);
      xinNian->Draw("same l");     
      
      TGraph * xinNianRatio = new TGraph(9);
      makeThRatio(xinNian, xinNianRatio, h[c], 2);
 
      const int graphPtsCUJET = 180;
      TGraph * cujet = new TGraph(2*graphPtsCUJET);
      getTheoryCUJET(cujet,0);
      cujet->Draw("same f");
     
 
      TGraph * cujetRatio = new TGraph(2*9);
      makeThRatio(cujet, cujetRatio, h[c], 1);
      cujetRatio->Print("All");
      
      legTh->AddEntry(h[c],"CMS 5.44 TeV XeXe","plf");
      legTh->AddEntry(xinNian,"LBT","l");
      legTh->AddEntry(cujet,"CUJET3.1/CIBJET","f");
      legTh->AddEntry(vitev,"SCET_{G}","f");
      legTh->Draw("same");    
      h[c]->Draw("same");     
 
      pad2->cd();
      canvTh->SetLogx();
      vitevRatio->GetXaxis()->SetTickLength(0.08);
      vitevRatio->GetYaxis()->SetNdivisions(2,2,0,kTRUE);
      pad2->SetLogx();
      vitevRatio->SetMinimum(0);
      vitevRatio->SetMaximum(1.999);
      vitevRatio->GetXaxis()->SetLimits(0.5,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2));
      //vitevRatio->GetYaxis()->SetTitle("Theory/Data");
      vitevRatio->GetXaxis()->SetTitle("p_{T} (GeV)");
      vitevRatio->GetYaxis()->CenterTitle();
      vitevRatio->GetXaxis()->CenterTitle();
      vitevRatio->GetYaxis()->SetTitleSize(0.14);
      vitevRatio->GetYaxis()->SetTitleOffset(0.3);
      vitevRatio->GetYaxis()->SetLabelSize(0.23);
      vitevRatio->GetXaxis()->SetTitleSize(0.2);
      vitevRatio->GetXaxis()->SetLabelSize(0.18);
      vitevRatio->GetXaxis()->SetLabelOffset(-0.05);
      vitevRatio->Draw("Af");
      uncert->Draw("HIST  same");
      uncert2->Draw("HIST  same");
      line1->Draw("same");
      vitevRatio->Draw("same f");
      cujetRatio->Draw("same f");
      xinNianRatio->Draw("same l");
    
      TLegend * legTh3 = new TLegend(0.15,0.75,0.45,0.95);
      legTh3->SetFillStyle(0);
      legTh3->SetLineColor(kBlack);
      legTh3->SetLineWidth(1);
      legTh3->SetTextFont(42);
      gStyle->SetLegendBorderSize(1);
      legTh3->SetTextSize(0.18);
      legTh3->AddEntry(uncert,"Total data uncertainty","F");
      legTh3->Draw("same");
 
      canvTh->cd(); 
      tex->SetTextAngle(90);
      tex->SetTextSize(0.04);
      tex->DrawLatexNDC(0.08,0.04,"Theory/Data");    
      tex->SetTextAngle(0);
      tex->SetTextSize(0.05);
      tex->DrawLatexNDC(0.12,0.185,"0");    
      
      canvTh->RedrawAxis();
      pad1->RedrawAxis();  
      pad2->RedrawAxis();  
      
 
      CMS_lumi( canvTh, iPeriod, 11 );

      canvTh->SaveAs(Form("img/TheoryRAA_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
      canvTh->SaveAs(Form("img/TheoryRAA_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
      canvTh->SaveAs(Form("img/TheoryRAA_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c]));
      isFirstLoop = true;
      delete legTh;
      continue;
    }
    if(5*s.lowCentBin[c]==30 && 5*s.highCentBin[c] == 50 && !isFirstLoop){
      float lumiUncert = 0.023;//2.3% for pp lumi
      float TAAUncert = s.TAAuncert[c]/100.0;
      float evtSel = evtSelSyst[c]->GetBinContent(2);
      float totUncert = TMath::Power(lumiUncert*lumiUncert+TAAUncert*TAAUncert+evtSel*evtSel,0.5);
      TH1D * uncert = (TH1D*)XeXeRAA_totSyst[c]->Clone("histTemp");
      uncert->Print("All");
      TH1D * uncert2 = (TH1D*)XeXeRAA_totSyst[c]->Clone("histTemp2");
      for(int i = 1; i<uncert->GetSize()-1; i++){
        uncert->SetBinContent(i,1+TMath::Power(TMath::Power(uncert->GetBinContent(i),2)+TMath::Power(totUncert,2)+TMath::Power(h[c]->GetBinError(i),2),0.5));
        uncert->SetLineWidth(0);
        uncert->SetFillStyle(1001);
        uncert->SetFillColor(18);
        uncert2->SetBinContent(i,1-TMath::Power(TMath::Power(uncert2->GetBinContent(i),2)+TMath::Power(totUncert,2)+TMath::Power(h[c]->GetBinError(i),2),0.5));
        uncert2->SetLineWidth(0);
        uncert2->SetFillStyle(1001);
        uncert2->SetFillColor(10);
      }
      pad1->cd();
      delete PbPb[3];
      for(int i = 0; i<s.ntrkBins+3; i++) delete bPbPb[i];
      for(int i = 0; i<s.ntrkBins+3; i++) bPbPb[i] = new TBox(0.1,0.1,0.2,0.2); 

      const int graphPtsXinNian = 24;
      TGraph * xinNian = new TGraph(graphPtsXinNian);
      getTheoryXinNian(xinNian,1);
      xinNian->Draw("same l");     
      
      TGraph * xinNianRatio = new TGraph(9);
      makeThRatio(xinNian, xinNianRatio, h[c], 2);
      
      const int graphPtsCUJET = 180;
      TGraph * cujet = new TGraph(2*graphPtsCUJET);
      getTheoryCUJET(cujet,1);
      cujet->Draw("same f");
      
      TGraph * cujetRatio = new TGraph(2*9);
      makeThRatio(cujet, cujetRatio, h[c], 1);
      cujetRatio->Print("All");
      
      legTh->AddEntry(h[c],"CMS 5.44 TeV XeXe","plf");
      legTh->AddEntry(xinNian,"LBT","l");
      legTh->AddEntry(cujet,"CUJET3.1/CIBJET","f");
      legTh->Draw("same");    
      
      pad2->cd();
      canvTh->SetLogx();
      cujetRatio->GetXaxis()->SetTickLength(0.08);
      cujetRatio->GetYaxis()->SetNdivisions(2,2,0,kTRUE);
      cujetRatio->GetYaxis()->CenterTitle();
      cujetRatio->GetXaxis()->CenterTitle();
      cujetRatio->GetYaxis()->SetTitleSize(0.14);
      cujetRatio->GetYaxis()->SetTitleOffset(0.3);
      cujetRatio->GetYaxis()->SetLabelSize(0.23);
      cujetRatio->GetXaxis()->SetTitleSize(0.2);
      cujetRatio->GetXaxis()->SetLabelSize(0.18);
      cujetRatio->GetXaxis()->SetLabelOffset(-0.05);
  
      pad2->SetLogx();
      cujetRatio->SetMinimum(0);
      cujetRatio->SetMaximum(1.999);
      //cujetRatio->GetYaxis()->SetTitle("Theory/Data");
      cujetRatio->GetXaxis()->SetTitle("p_{T} (GeV)");
      cujetRatio->GetXaxis()->SetLimits(0.5,h[c]->GetXaxis()->GetBinUpEdge(h[c]->GetSize()-2));
      cujetRatio->Draw("Af");
      uncert->Draw("HIST  same");
      uncert2->Draw("HIST  same");
      line1->Draw("same");
      cujetRatio->Draw("same f");
      xinNianRatio->Draw("same l");     
 
      TLegend * legTh3 = new TLegend(0.15,0.75,0.45,0.95);
      legTh3->SetFillStyle(0);
      legTh3->SetLineColor(kBlack);
      legTh3->SetLineWidth(1);
      legTh3->SetTextFont(42);
      gStyle->SetLegendBorderSize(1);
      legTh3->SetTextSize(0.18);
      legTh3->AddEntry(uncert,"Total data uncertainty","F");
      legTh3->Draw("same");

      canvTh->cd(); 
      tex->SetTextSize(0.04);
      tex->SetTextAngle(90);
      tex->DrawLatexNDC(0.08,0.04,"Theory/Data");    
      tex->SetTextAngle(0);
      tex->SetTextSize(0.05);
      tex->DrawLatexNDC(0.12,0.185,"0");    

      canvTh->RedrawAxis();
      pad1->RedrawAxis();  
      pad2->RedrawAxis();  
     
 
      CMS_lumi( canvTh, iPeriod, 11 );
      
      canvTh->SaveAs(Form("img/TheoryRAA_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
      canvTh->SaveAs(Form("img/TheoryRAA_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
      canvTh->SaveAs(Form("img/TheoryRAA_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c]));
      isFirstLoop = true;
      delete legTh;
      continue;
    }
    if(5*s.lowCentBin[c]==0 && 5*s.highCentBin[c] == 10 && isFirstLoop){ isFirstLoop = false; c--;}
    if(5*s.lowCentBin[c]==30 && 5*s.highCentBin[c] == 50 && isFirstLoop){ isFirstLoop = 0; c--;}

    delete legTh;
  }

  for(int i = 2; i<s.ntrkBins; i++){ 
    TCanvas * c5 = new TCanvas("c5","c5",650,600);
    sumNcoll[0][i]->SetFillColor(kRed-7);
    sumNcoll[0][i]->SetLineWidth(1);
    sumNcoll[0][i]->SetMarkerStyle(8);
    sumNcoll[0][i]->SetMarkerSize(1.3);

    sumNcoll[1][i]->SetLineWidth(1);
    sumNcoll[1][i]->SetMarkerStyle(8);
    sumNcoll[1][i]->SetMarkerSize(1.3);

    sumNcollPb[0][i]->GetYaxis()->SetRangeUser(0,1.2);
    sumNcollPb[0][i]->GetXaxis()->SetRangeUser(-500,2100);
    sumNcollPb[0][i]->GetYaxis()->CenterTitle();
    sumNcollPb[0][i]->GetYaxis()->SetTitle("R*_{AA}, R_{AA}");
    sumNcollPb[0][i]->GetXaxis()->SetTitle("#LTN_{coll}#GT");
    sumNcollPb[0][i]->GetXaxis()->CenterTitle();
    sumNcollPb[0][i]->GetXaxis()->SetNdivisions(505);
    sumNcollPb[0][i]->SetLineColor(kBlue);
    sumNcollPb[0][i]->SetFillColor(kBlue);
    sumNcollPb[0][i]->SetFillStyle(0);
    sumNcollPb[0][i]->SetLineWidth(1);
    sumNcollPb[0][i]->SetFillStyle(0);
    sumNcollPb[0][i]->SetMarkerStyle(24);
    sumNcollPb[0][i]->SetMarkerColor(kBlue);
    sumNcollPb[0][i]->SetMarkerSize(1.3);
    sumNcollPb[1][i]->SetLineWidth(1);
    sumNcollPb[1][i]->SetLineColor(kBlue);
    sumNcollPb[1][i]->SetMarkerColor(kBlue);
    sumNcollPb[1][i]->SetMarkerStyle(24);
    sumNcollPb[1][i]->SetMarkerSize(1.3);

    sumNcollPb[0][i]->Draw("A2");
    sumNcoll[0][i]->Draw("same 2");
    sumNcollPb[0][i]->Draw("same 2");
    sumNcoll[1][i]->Draw("same PZ");
    sumNcollPb[1][i]->Draw("same PZ");

    gStyle->SetLegendBorderSize(0);
    TLegend * leg5 = new TLegend(0.4,0.6,0.9,0.9);
    leg5->SetTextSize(0.05);
    leg5->AddEntry(sumNcoll[0][i],"5.44 TeV XeXe R*_{AA}","pf");
    leg5->AddEntry(sumNcollPb[0][i],"5.02 TeV PbPb R_{AA}","pf");
    leg5->AddEntry((TObject*)0,"|#eta| < 1","");
    leg5->AddEntry((TObject*)0,Form("%.1f #leq p_{T} < %.1f GeV",h[0]->GetXaxis()->GetBinLowEdge(i+1),h[0]->GetXaxis()->GetBinLowEdge(i+2)),"");
    leg5->SetFillStyle(0);
    leg5->Draw("same");

    lumi_sqrtS = "27.4 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb) + 3.42 #mub^{-1} (5.44 TeV XeXe)";
    CMS_lumi( c5, 0, 11 );
    c5->SaveAs(Form("img/Summary_NColl_%d.png",i));
    c5->SaveAs(Form("img/Summary_NColl_%d.pdf",i));
    c5->SaveAs(Form("img/Summary_NColl_%d.C",i));
    //sumNpart[15]->Print("All");
    //sumNpart[15]->Print("All");
    delete c5;
  }
  for(int i = 2; i<s.ntrkBins; i++){ 
    TCanvas * c5 = new TCanvas("c5","c5",650,600);
    c5->SetTopMargin(0.07);
    sumNpart[0][i]->SetFillColor(kRed-7);
    sumNpart[0][i]->SetLineWidth(1);
    sumNpart[0][i]->SetMarkerStyle(8);
    sumNpart[0][i]->SetMarkerSize(1.3);

    sumNpart[1][i]->SetLineWidth(1);
    sumNpart[1][i]->SetMarkerStyle(8);
    sumNpart[1][i]->SetMarkerSize(1.3);

    sumNpartPb[0][i]->GetYaxis()->SetRangeUser(0,1.2);
    sumNpartPb[0][i]->GetXaxis()->SetRangeUser(-500,2100);
    sumNpartPb[0][i]->GetYaxis()->CenterTitle();
    sumNpartPb[0][i]->GetYaxis()->SetTitle("R*_{AA}, R_{AA}");
    sumNpartPb[0][i]->GetXaxis()->SetTitle("#LTN_{part}#GT");
    sumNpartPb[0][i]->GetXaxis()->CenterTitle();
    sumNpartPb[0][i]->GetXaxis()->SetNdivisions(505);
    sumNpartPb[0][i]->SetLineColor(kBlue);
    sumNpartPb[0][i]->SetFillColor(kBlue);
    sumNpartPb[0][i]->SetFillStyle(0);
    sumNpartPb[0][i]->SetLineWidth(1);
    sumNpartPb[0][i]->SetFillStyle(0);
    sumNpartPb[0][i]->SetMarkerStyle(24);
    sumNpartPb[0][i]->SetMarkerColor(kBlue);
    sumNpartPb[0][i]->SetMarkerSize(1.3);
    sumNpartPb[1][i]->SetLineWidth(1);
    sumNpartPb[1][i]->SetLineColor(kBlue);
    sumNpartPb[1][i]->SetMarkerColor(kBlue);
    sumNpartPb[1][i]->SetMarkerStyle(24);
    sumNpartPb[1][i]->SetMarkerSize(1.3);

    sumNpartPb[0][i]->Draw("A2");
    sumNpart[0][i]->Draw("same 2");
    sumNpartPb[0][i]->Draw("same 2");
    sumNpart[1][i]->Draw("same PZ");
    sumNpartPb[1][i]->Draw("same PZ");

    gStyle->SetLegendBorderSize(0);
    TLegend * leg5 = new TLegend(0.4,0.6,0.9,0.9);
    leg5->SetTextSize(0.05);
    leg5->AddEntry(sumNpart[0][i],"5.44 TeV XeXe R*_{AA}","pf");
    leg5->AddEntry(sumNpartPb[0][i],"5.02 TeV PbPb R_{AA}","pf");
    leg5->AddEntry((TObject*)0,"|#eta| < 1","");
    leg5->AddEntry((TObject*)0,Form("%.1f #leq p_{T} < %.1f GeV",h[0]->GetXaxis()->GetBinLowEdge(i+1),h[0]->GetXaxis()->GetBinLowEdge(i+2)),"");
    leg5->SetFillStyle(0);
    leg5->Draw("same");

    lumi_sqrtS = "27.4 pb^{-1} (pp) + 404 #mub^{-1} (PbPb) + 3.42 #mub^{-1} (XeXe)";

    if(i>22){writeExtraText = true; extraText = "Supplementary";};
    CMS_lumi( c5, 0, 11,false,false,1.0 );
    c5->SaveAs(Form("img/Summary_NPart_%d.png",i));
    c5->SaveAs(Form("img/Summary_NPart_%d.pdf",i));
    c5->SaveAs(Form("img/Summary_NPart_%d.C",i));
    writeExtraText = false;
    //sumNpart[15]->Print("All");
    //sumNpart[15]->Print("All");
    delete c5;
  }
}


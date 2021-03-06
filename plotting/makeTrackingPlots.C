#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TColor.h"
#include "TPad.h"
#include <string>

void makeVzCent(TH1D * vz, TH1D * hiBin,TH1D * MCvz, TH1D * MChiBin, TCanvas * c1){
  c1->SetLeftMargin(0.12);
  vz->GetXaxis()->SetTitle("v_{z}");
  vz->GetYaxis()->SetTitle("normalized to unity");
  vz->Scale(1.0/vz->Integral(0,vz->GetSize()-1));
  vz->SetMarkerColor(kBlack);
  vz->SetLineColor(kBlack);
  vz->SetMarkerStyle(8);
  vz->GetYaxis()->SetTitleOffset(1.2);
  vz->Draw("");
  MCvz->Scale(1.0/MCvz->Integral(0,MCvz->GetSize()-1));
  MCvz->SetMarkerColor(kRed);
  MCvz->SetLineColor(kRed);
  MCvz->SetMarkerStyle(25);
  MCvz->Draw("same");

  TLegend * l = new TLegend(0.15,0.65,0.45,0.85);
  l->AddEntry((TObject*)0,"Event Selections Applied","");
  l->AddEntry(vz,"Data","p");
  l->AddEntry(MCvz,"MB Hydjet","p");
  l->Draw("same");
  c1->SaveAs("trkPlots/vz.png");
  c1->SaveAs("trkPlots/vz.pdf");
  c1->SaveAs("trkPlots/vz.C");

  hiBin->GetXaxis()->SetTitle("hiBin");
  hiBin->GetYaxis()->SetTitle("normalized to unity");
  hiBin->Rebin(4);
  hiBin->Scale(1.0/hiBin->Integral(1,200));
  hiBin->SetMarkerColor(kBlack);
  hiBin->SetLineColor(kBlack);
  hiBin->SetMarkerStyle(8);
  hiBin->GetYaxis()->SetTitleOffset(1.2);
  hiBin->GetYaxis()->SetRangeUser(0,0.025);
  hiBin->Draw("");
  MChiBin->Rebin(4);
  MChiBin->Scale(1.0/MChiBin->Integral(0,MChiBin->GetSize()-1));
  MChiBin->SetMarkerColor(kRed);
  MChiBin->SetLineColor(kRed);
  MChiBin->SetMarkerStyle(25);
  MChiBin->Draw("same");
  l->SetY1NDC(0.12);
  l->SetY2NDC(0.4);
  l->Draw("same");
  hiBin->Draw("same");

  c1->SaveAs("trkPlots/hiBin.png");
  c1->SaveAs("trkPlots/hiBin.pdf");
  c1->SaveAs("trkPlots/hiBin.C");
  delete l;
}

void makeTrkDistInclusive(TH1D * h, TH1D * mc[17][3],TCanvas * c1, std::string Xlabel, std::string fileLabel, bool doLogy = 0, float yMin = 0, float yMax = 1, std::string MCLabel = "MB Hydjet", int cuts = 2){
  c1->SetLeftMargin(0.2);
  if(doLogy==1) c1->SetLogy();
  h->SetTitle("");
  h->Scale(1.0/h->Integral(0,h->GetSize()-1));
  h->GetXaxis()->SetTitle(Xlabel.c_str());
  h->GetYaxis()->SetRangeUser(yMin,yMax);
  h->GetYaxis()->SetTitle("Normalized to unity");
  h->SetMarkerColor(kBlack);
  h->SetLineColor(kBlack);
  h->SetMarkerStyle(8);
  h->SetMarkerSize(0.5);
  h->GetYaxis()->SetTitleOffset(2);
  h->Draw("");

  float tempScale = mc[0][0]->Integral(0,mc[0][0]->GetSize()-1);
  mc[0][0]->Scale(1.0/tempScale);
  mc[0][0]->SetLineColor(kBlack);
  mc[0][1]->Scale(1.0/tempScale);
  mc[0][1]->SetLineColor(kRed);
  mc[0][2]->Scale(1.0/tempScale);
  mc[0][2]->SetLineColor(kBlue);
  mc[0][2]->Draw("same hist");
  mc[0][1]->Draw("same hist");
  mc[0][0]->Draw("same hist");
  h->Draw("same");

  TLegend * l = new TLegend(0.7,0.55,0.88,0.875);
  l->AddEntry((TObject*)0,"highPurity Tracks","");
  if(strcmp(fileLabel.c_str(),"eta")!=0) l->AddEntry((TObject*)0,"|#eta|<1.0","");
  if(cuts>0) l->AddEntry((TObject*)0,"|#delta_{z}/#sigma_{z}|<3","");
  if(cuts>0) l->AddEntry((TObject*)0,"|#delta_{xy}/#sigma_{xy}|<3","");
  if(cuts>0) l->AddEntry((TObject*)0,"#sigma_{p_{T}}/p_{T}<0.1","");
  if(cuts>1) l->AddEntry((TObject*)0,"nHits>=11","");
  if(cuts>1) l->AddEntry((TObject*)0,"#chi^{2}/ndof/nLayers<0.15","");
  if(cuts>1) l->AddEntry((TObject*)0,"E_{T}^{calo}/p_{T}>0.5","");
  l->AddEntry(h,"Data","p");
  l->AddEntry(mc[0][0],MCLabel.c_str(),"l");
  l->AddEntry(mc[0][1],"MC Real Fraction","l");
  l->AddEntry(mc[0][2],"MC Fake Fraction","l");
  l->SetFillStyle(0);
  //leg->AddEntry((TObject*)0,"highPurity Tracks","");
  //leg->AddEntry((TObject*)0,"highPurity Tracks","");
  //leg->AddEntry((TObject*)0,"highPurity Tracks","");
  l->Draw("same");
  c1->SaveAs(Form("trkPlots/%s_Inclusive_cuts%d.png",fileLabel.c_str(),cuts));
  c1->SaveAs(Form("trkPlots/%s_Inclusive_cuts%d.pdf",fileLabel.c_str(),cuts));
  c1->SaveAs(Form("trkPlots/%s_Inclusive_cuts%d.C",fileLabel.c_str(),cuts));
  
  delete l;
  
}

float getLowPt(int i){
  if((i-1)%4==0) return 0.5;
  if((i-1)%4==1) return 1;
  if((i-1)%4==2) return 8;
  if((i-1)%4==3) return 20;
  return -1;
}
float getHighPt(int i){
  if((i-1)%4==0) return 1;
  if((i-1)%4==1) return 8;
  if((i-1)%4==2) return 20;
  if((i-1)%4==3) return 999;
  return -1;
}
int getLowCent(int i){
  if((i-1)/4==0) return 0;
  if((i-1)/4==1) return 10;
  if((i-1)/4==2) return 30;
  if((i-1)/4==3) return 50;
  return -1;
}
int getHighCent(int i){
  if((i-1)/4==0) return 10;
  if((i-1)/4==1) return 30;
  if((i-1)/4==2) return 50;
  if((i-1)/4==3) return 100;
  return -1;
}

void makeTrkDistArray(TH1D ** h,TH1D * mc[17][3], TCanvas * c2, std::string Xlabel, std::string fileLabel, bool doLogy = 0, float yMin = 0, float yMax = 1, std::string MCLabel = "MB Hydjet", int cuts = 2){
  TLegend * l[16]; 
  for(int i = 1; i<17; i++){
    c2->cd(i+4);
    if(strcmp(fileLabel.c_str(),"pterror")==0) c2->cd(i+4)->SetLogy();
    l[i-1] = new TLegend(0.55,0.65,0.875,0.85);
    l[i-1]->AddEntry((TObject*)0,Form("%1.1f<p_{T}<%1.0f",getLowPt(i),getHighPt(i)),"");
    l[i-1]->AddEntry((TObject*)0,Form("%d-%d%%",getLowCent(i),getHighCent(i)),"");
    if(doLogy==1) c2->SetLogy();
    h[i]->SetTitle("");
    h[i]->Scale(1.0/h[i]->Integral(0,h[i]->GetSize()-1));
    h[i]->GetXaxis()->SetTitle(Xlabel.c_str());
    h[i]->GetYaxis()->SetRangeUser(yMin,yMax);
    h[i]->GetYaxis()->SetTitle("Normalized to unity");
    h[i]->SetMarkerColor(kBlack);
    h[i]->SetMarkerStyle(8);
    h[i]->SetMarkerSize(0.5);
    h[i]->SetLineColor(kBlack);
    //h[i]->SetMarkerStyle(8);
    h[i]->GetYaxis()->SetTitleOffset(2);
    h[i]->Draw(""); 

    float tempScale = mc[i][0]->Integral(0,mc[i][0]->GetSize()-1);  
    mc[i][0]->Scale(1.0/tempScale);
    mc[i][0]->SetLineColor(kBlack);
    mc[i][1]->Scale(1.0/tempScale);
    mc[i][1]->SetLineColor(kRed);
    mc[i][2]->Scale(1.0/tempScale);
    mc[i][2]->SetLineColor(kBlue);
    mc[i][2]->Draw("same hist");
    mc[i][1]->Draw("same hist");
    mc[i][0]->Draw("same hist");
    h[i]->Draw("same");

    l[i-1]->SetFillStyle(0);
    l[i-1]->Draw("same");
    h[i]->Draw("same"); 
  }

  c2->cd(1);
  TLegend * leg = new TLegend(0,0,1,1);
  leg->AddEntry((TObject*)0,"Plots Normalized to Unity","");
  leg->AddEntry(h[1],"Data","p");
  leg->AddEntry(mc[1][0],MCLabel.c_str(),"l");
  leg->AddEntry(mc[1][1],"MC Real Fraction","l");
  leg->AddEntry(mc[1][2],"MC Fake+Secondary","l");
  leg->SetFillStyle(0);
  leg->Draw("same");

  c2->cd(2);
  TLegend * leg2 = new TLegend(0,0,1,1);
  leg2->AddEntry((TObject*)0,"highPurity Tracks","");
  if(strcmp(fileLabel.c_str(),"eta")!=0) leg2->AddEntry((TObject*)0,"|#eta|<1.0","");
  if(cuts>0) leg2->AddEntry((TObject*)0,"|#delta_{z}/#sigma_{z}|<3","");
  if(cuts>0) leg2->AddEntry((TObject*)0,"|#delta_{xy}/#sigma_{xy}|<3","");
  if(cuts>0) leg2->AddEntry((TObject*)0,"#sigma_{p_{T}}/p_{T}<0.1","");
  if(cuts>1) leg2->AddEntry((TObject*)0,"nHits>=11","");
  if(cuts>1) leg2->AddEntry((TObject*)0,"#chi^{2}/ndof/nLayers<0.15","");
  if(cuts>1) leg2->AddEntry((TObject*)0,"E_{T}^{calo}/p_{T}>0.5","");
  leg2->SetFillStyle(0);
  leg2->Draw("same");

  c2->SaveAs(Form("trkPlots/%s_array_cuts%d.png",fileLabel.c_str(),cuts));
  c2->SaveAs(Form("trkPlots/%s_array_cuts%d.pdf",fileLabel.c_str(),cuts));
  c2->SaveAs(Form("trkPlots/%s_array_cuts%d.C",fileLabel.c_str(),cuts));
  for(int i = 1; i<17; i++) delete l[i-1];
  delete leg;
  delete leg2;
}

void makeTrackingPlots_Cuts(int cuts = 2){
  TH1::SetDefaultSumw2();
  gStyle->SetLegendBorderSize(0);
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
 
  std::string generator = "MB Hydjet";
  //std::string generator = "MB EPOS";
  //std::string generator = "Pythia + Hydjet";
 
  TFile * f = TFile::Open("../output_0.root","read");
  //TFile * mc = TFile::Open("MCTrackingRootFiles/Pythia_March3.root","read"); 
  TFile * mc = TFile::Open("MCTrackingRootFiles/Hydjet_March7.root","read"); 
  //TFile * mc = TFile::Open("MCTrackingRootFiles/EPOS_Feb26.root","read"); 
  //etaLT2p5 below 
  //TFile * f = TFile::Open("MCTrackingRootFiles/output_Feb6_etaLT2p5_Data.root","read");
  //TFile * mc = TFile::Open("MCTrackingRootFiles/output_Feb6_etaLT2p5.root","read"); 
 
  TH1D *nHit[17], *chi2[17], *DCAz[17], *DCAxy[17], *ptErr[17], *eta[17], *phi[17], *caloMatch[17];
  TH1D *MCnHit[17][3], *MCchi2[17][3], *MCDCAz[17][3], *MCDCAxy[17][3], *MCptErr[17][3], *MCeta[17][3], *MCphi[17][3], *MCcaloMatch[17][3];
  for(int c = 0; c<17; c++){
    nHit[c] = (TH1D*)f->Get(Form("nHit%d_cut%d",c,cuts));
    chi2[c] = (TH1D*)f->Get(Form("chi2%d_cut%d",c,cuts));
    ptErr[c] = (TH1D*)f->Get(Form("ptErr%d_cut%d",c,cuts));
    DCAz[c] = (TH1D*)f->Get(Form("DCAz%d_cut%d",c,cuts));
    DCAxy[c] = (TH1D*)f->Get(Form("DCAxy%d_cut%d",c,cuts));
    eta[c] = (TH1D*)f->Get(Form("eta%d_cut%d",c,cuts));
    phi[c] = (TH1D*)f->Get(Form("phi%d_cut%d",c,cuts));
    caloMatch[c] = (TH1D*)f->Get(Form("caloMatch%d_cut%d",c,cuts));
    
    for(int c2 = 0; c2<3; c2++){
      MCnHit[c][c2] = (TH1D*)mc->Get(Form("nHit%d_%d_cut%d",c,c2,cuts));
      MCchi2[c][c2] = (TH1D*)mc->Get(Form("chi2%d_%d_cut%d",c,c2,cuts));
      MCptErr[c][c2] = (TH1D*)mc->Get(Form("ptErr%d_%d_cut%d",c,c2,cuts));
      MCDCAz[c][c2] = (TH1D*)mc->Get(Form("DCAz%d_%d_cut%d",c,c2,cuts));
      MCDCAxy[c][c2] = (TH1D*)mc->Get(Form("DCAxy%d_%d_cut%d",c,c2,cuts));
      MCeta[c][c2] = (TH1D*)mc->Get(Form("eta%d_%d_cut%d",c,c2,cuts));
      MCphi[c][c2] = (TH1D*)mc->Get(Form("phi%d_%d_cut%d",c,c2,cuts));
      MCcaloMatch[c][c2] = (TH1D*)mc->Get(Form("caloMatch%d_%d_cut%d",c,c2,cuts));
    }
  }
  TH1D * vz = (TH1D*)f->Get("vz");
  TH1D * hiBin = (TH1D*)f->Get("hiBin");
  TH1D * MCvz = (TH1D*)mc->Get("vz");
  TH1D * MChiBin = (TH1D*)mc->Get("hiBin");

  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  makeVzCent(vz,hiBin,MCvz,MChiBin,c1);

  makeTrkDistInclusive(nHit[0],MCnHit,c1,"nHits","nHits",0,0,0.3,generator,cuts);
  makeTrkDistInclusive(chi2[0],MCchi2,c1,"#chi^{2}/ndof/nLayers","chi2",0,0,0.1,generator,cuts);
  makeTrkDistInclusive(DCAz[0],MCDCAz,c1,"d_{z}/#sigma_{z}","DCAz",0,0,0.1,generator,cuts);
  makeTrkDistInclusive(DCAxy[0],MCDCAxy,c1,"d_{xy}/#sigma_{xy}","DCAxy",0,0,0.1,generator,cuts);
  makeTrkDistInclusive(eta[0],MCeta,c1,"#eta","eta",0,0,0.04,generator,cuts);
  makeTrkDistInclusive(phi[0],MCphi,c1,"#phi","phi",0,0,0.04,generator,cuts);
  makeTrkDistInclusive(caloMatch[0],MCcaloMatch,c1,"E_{T}/p_{T}","caloMatch",0,0,0.1,generator,cuts);
  c1->SetLogy();
  makeTrkDistInclusive(ptErr[0],MCptErr,c1,"#sigma_{p_{T}}/p_{T}","pterror",0,0.001,0.6,generator,cuts);
  delete c1;

  //split by cent and pt
  TCanvas * c2 = new TCanvas("c2","c2",1000,1250);
  c2->Divide(4,5); 
  makeTrkDistArray(nHit,MCnHit,c2,"nHits","nHits",0,0,0.3,generator,cuts);
  makeTrkDistArray(chi2,MCchi2,c2,"#chi^{2}/ndof/nLayers","chi2",0,0,0.1,generator,cuts);
  makeTrkDistArray(DCAz,MCDCAz,c2,"d_{z}/#sigma_{z}","DCAz",0,0,0.1,generator,cuts);     
  makeTrkDistArray(DCAxy,MCDCAxy,c2,"d_{xy}/#sigma_{xy}","DCAxy",0,0,0.1,generator,cuts);  
  makeTrkDistArray(phi,MCphi,c2,"#phi","phi",0,0,0.04,generator,cuts);                
  makeTrkDistArray(eta,MCeta,c2,"#eta","eta",0,0,0.04,generator,cuts);             
  makeTrkDistArray(caloMatch,MCcaloMatch,c2,"E_{T}/p_{T}","caloMatch",0,0,0.1,generator,cuts);
  for(int i = 1; i<21; i++){ c2->cd(i); c2->SetLogy();}
  makeTrkDistArray(ptErr,MCptErr,c2,"#sigma_{p_{T}}/p_{T}","pterror",0,0.001,0.6,generator,cuts);

  delete c2; 
}

void resolutionSyst(){
  TFile * f = TFile::Open("../output_0.root","read");
  TH1D * smeared[8];
  TH1D * nominal[8];
  nominal[0] = (TH1D*)f->Get("HI_0_5");
  smeared[0] = (TH1D*)f->Get("HIsmeared_0_5");
  smeared[0]->Divide(nominal[0]);
  nominal[1] = (TH1D*)f->Get("HI_5_10");
  smeared[1] = (TH1D*)f->Get("HIsmeared_5_10");
  smeared[1]->Divide(nominal[1]);
  nominal[2] = (TH1D*)f->Get("HI_10_30");
  smeared[2] = (TH1D*)f->Get("HIsmeared_10_30");
  smeared[2]->Divide(nominal[2]);
  nominal[3] = (TH1D*)f->Get("HI_30_50");
  smeared[3] = (TH1D*)f->Get("HIsmeared_30_50");
  smeared[3]->Divide(nominal[3]);
  nominal[4] = (TH1D*)f->Get("HI_50_70");
  smeared[4] = (TH1D*)f->Get("HIsmeared_50_70");
  smeared[4]->Divide(nominal[4]);
  nominal[5] = (TH1D*)f->Get("HI_70_90");
  smeared[5] = (TH1D*)f->Get("HIsmeared_70_90");
  smeared[5]->Divide(nominal[5]);
  nominal[6] = (TH1D*)f->Get("HI_0_10");
  smeared[6] = (TH1D*)f->Get("HIsmeared_0_10");
  smeared[6]->Divide(nominal[6]);
  nominal[7] = (TH1D*)f->Get("HI_0_100");
  smeared[7] = (TH1D*)f->Get("HIsmeared_0_100");
  smeared[7]->Divide(nominal[7]);

  TCanvas * c1 = new TCanvas("c1","",800,600);
  TLegend * l = new TLegend(0.3,0.7,0.6,0.9);
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  c1->SetLogx();
  for(int c = 0; c<8; c++){
    smeared[c]->GetYaxis()->SetTitle("smeared/nominal");
    smeared[c]->GetYaxis()->SetRangeUser(0.9,1.1);
    smeared[c]->GetXaxis()->SetTitle("p_{T}");
    smeared[c]->SetMarkerStyle(8);
    smeared[c]->SetLineColor(kBlack);
    smeared[c]->SetMarkerColor(kBlack);
    smeared[c]->SetTitle("");
    smeared[c]->Draw();
    l->Clear();
    if(c==0)l->AddEntry((TObject*)0,"0-5%","");
    if(c==1)l->AddEntry((TObject*)0,"5-10%","");
    if(c==2)l->AddEntry((TObject*)0,"10-30%","");
    if(c==3)l->AddEntry((TObject*)0,"30-50%","");
    if(c==4)l->AddEntry((TObject*)0,"50-70%","");
    if(c==5)l->AddEntry((TObject*)0,"70-90%","");
    if(c==6)l->AddEntry((TObject*)0,"0-10%","");
    if(c==7)l->AddEntry((TObject*)0,"0-100%","");
    l->Draw("same");
    c1->SaveAs(Form("trkPlots/trkResoSyst_%d.png",c));
    c1->SaveAs(Form("trkPlots/trkResoSyst_%d.pdf",c));
    c1->SaveAs(Form("trkPlots/trkResoSyst_%d.C",c));
  }
  delete c1;
}

void makeTrackingPlots(){
  makeTrackingPlots_Cuts(0);
  makeTrackingPlots_Cuts(1);
  makeTrackingPlots_Cuts(2);
//  makeTrackingPlots_Cuts(3);
  resolutionSyst();
}

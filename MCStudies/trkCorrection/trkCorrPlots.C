#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <string>
#include <cstring>

void makeArray(TCanvas * c1, TH1D ** eff, std::string yTitle, std::string outTitle){
  TLegend * l[6];
  for(int i = 0; i<6; i++){
    c1->cd(i+1);
    c1->cd(i+1)->SetLogx();
    eff[i]->SetMarkerStyle(8);
    eff[i]->SetMarkerColor(kBlack);
    eff[i]->SetLineColor(kBlack);
    eff[i]->GetXaxis()->SetTitle("p_{T}");
    eff[i]->GetYaxis()->SetTitle(yTitle.c_str());
 
    if(strcmp(yTitle.c_str(),"efficiency")==0) eff[i]->GetYaxis()->SetRangeUser(0,1.2);
    if(strcmp(yTitle.c_str(),"misreconstruction rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.35);
    if(strcmp(yTitle.c_str(),"secondary rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.01);
    if(strcmp(yTitle.c_str(),"multiple reco rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.0001);
 
    eff[i]->Draw();
    l[i] = new TLegend(0.1,0.7,0.7,0.89);
    l[i]->SetBorderSize(0);
    l[i]->SetFillStyle(0);
    if(i==0) l[i]->AddEntry((TObject*)0,"0-5%","");
    if(i==1) l[i]->AddEntry((TObject*)0,"5-10%","");
    if(i==2) l[i]->AddEntry((TObject*)0,"10-30%","");
    if(i==3) l[i]->AddEntry((TObject*)0,"30-50%","");
    if(i==4) l[i]->AddEntry((TObject*)0,"50-70%","");
    if(i==5) l[i]->AddEntry((TObject*)0,"70-100%","");
    l[i]->AddEntry((TObject*)0,"Analysis Cuts","");
    l[i]->AddEntry(eff[i],"Hydjet MB","p");
    l[i]->Draw("same");
  }
  c1->SaveAs(Form("img/%s.png",outTitle.c_str()));
  c1->SaveAs(Form("img/%s.pdf",outTitle.c_str()));
  c1->SaveAs(Form("img/%s.C",outTitle.c_str()));
}


void trkCorrPlots(){
  TFile * f1 = TFile::Open("trkCorr_Hydjet_Feb6.root","read");
  gStyle->SetOptStat(0);

  TH1D * efficiency[6], *fake[6], *secondary[6], *multiple[6];
  for(int c = 0; c<6; c++){
    efficiency[c] = (TH1D*)f1->Get(Form("efficiency_%d",c));  
    fake[c] = (TH1D*)f1->Get(Form("fake_%d",c));  
    secondary[c] = (TH1D*)f1->Get(Form("secondary_%d",c));  
    multiple[c] = (TH1D*)f1->Get(Form("multiple_%d",c));  
  }

  TCanvas * c1 = new TCanvas("c1","c1",700,900);
  c1->Divide(2,3);

  makeArray(c1, efficiency, "efficiency","efficiency");
  makeArray(c1, fake, "misreconstruction rate","fake");
  makeArray(c1, secondary, "secondary rate","secondary");
  makeArray(c1, multiple, "multiple reco rate","multiple");
}



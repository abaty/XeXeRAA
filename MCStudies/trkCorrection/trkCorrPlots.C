#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <string>

void makeArray(TCanvas * c1, TH1D ** eff, std::string yTitle, std::string outTitle){
  for(int i = 0; i<6; i++){
    c1->cd(i);
    eff[i]->SetMarkerStyle(8);
    eff[i]->SetMarkerColor(kBlack);
    eff[i]->SetLineColor(kBlack);
    eff[i]->GetXaxis()->SetTitle("p_{T}");
    eff[i]->GetYaxis()->SetTitle(yTitle.c_str());
 
    if(strcmp(yTitle,"efficiency")==0) eff[i]->GetYaxis()->SetRangeUser(0,1);
    if(strcmp(yTitle,"misreconstruction rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.5);
    if(strcmp(yTitle,"secondary rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.02);
    if(strcmp(yTitle,"multiple reco rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.001);
 
    eff[i]->Draw();
  }
  c1->SaveAs(Form("img/%s.png",outTitle.c_str()));
  c1->SaveAs(Form("img/%s.pdf",outTitle.c_str()));
  c1->SaveAs(Form("img/%s.C",outTitle.c_str()));
}


void trkCorrPlots(){
  TFile * f1 = TFile::Open("trkCorr_Hydjet_Feb6.root","read");

  TH1D * efficiency[6], fake[6], secondary[6], multiple[6];
  for(int c = 0; c<6; c++){
    efficiency[c] = (TH1D*)f1->Get(Form("efficiency_%d",c));  
    fake[c] = (TH1D*)f1->Get(Form("fake_%d",c));  
    secondary[c] = (TH1D*)f1->Get(Form("secondary_%d",c));  
    multiple[c] = (TH1D*)f1->Get(Form("multiple_%d",c));  
  }

  TCanvas * c1 = new TCanvas("c1","c1",600,900);
  c1->SetLogx();
  c1->Divide(2,3);

  makeArray(c1, efficiency, "efficiency","efficiency");
  makeArray(c1, fake, "misreconstruction rate","fake");
  makeArray(c1, secondary, "secondary rate","secondary");
  makeArray(c1, multiple, "multiple reco rate","multiple");
}



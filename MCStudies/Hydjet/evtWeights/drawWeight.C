#include "TFile.h"
#include "TH1D.h"
#include <string>

void drawWeight(){
  TFile * i = TFile::Open("evtWeights_Hydjet.root","read");
  TH1D * vz_weight = (TH1D*)i->Get("vz_weight"); 
  TH1D * hiBin_weight = (TH1D*)i->Get("hiBin_weight"); 

  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  vz_weight->GetXaxis()->SetRangeUser(-15,15);
  vz_weight->SetTitle(";v_{z};weight");
  vz_weight->Draw();
  c1->SaveAs("img/HydjetWeightvz.png");
  c1->SaveAs("img/HydjetWeightvz.pdf");
  c1->SaveAs("img/HydjetWeightvz.C");
  c1->SetLogy();
  hiBin_weight->GetXaxis()->SetRangeUser(0,199);
  hiBin_weight->SetTitle(";hiBin;weight");
  hiBin_weight->Draw();
  c1->SaveAs("img/HydjetWeighthiBin.png");
  c1->SaveAs("img/HydjetWeighthiBin.pdf");
  c1->SaveAs("img/HydjetWeighthiBin.C");
}

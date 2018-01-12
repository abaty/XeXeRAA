#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TColor.h"
#include "TPad.h"

void makeTrackingPlots(){
  TH1::SetDefaultSumw2();
  
  TFile * f = TFile::Open("../output_0.root","read");
  
  TH1D *nHit[17], *chi2[17], *DCAz[17], *DCAxy[17], *ptErr[17], *eta[17], *phi[17], *caloMatch[17];
  if(s.doTrackDists){
    for(int c = 0; c<17; c++){
      nHit[c] = (TH1D*)f->Get(Form("nHit%d",c));
      chi2[c] = (TH1D*)f->Get(Form("chi2%d",c));
      ptErr[c] = (TH1D*)f->Get(Form("ptErr%d",c));
      DCAz[c] = (TH1D*)f->Get(Form("DCAz%d",c));
      DCAxy[c] = (TH1D*)f->Get(Form("DCAxy%d",c));
      eta[c] = (TH1D*)f->Get(Form("eta%d",c));
      phi[c] = (TH1D*)f->Get(Form("phi%d",c));
      caloMatch[c] = (TH1D*)f->Get(Form("caloMatch%d",c));
    }
  }
  TH1D * vz = (TH1D*)f->Get("vz");
  TH1D * hiBin = (TH1D*)f->Get("hibin");


}

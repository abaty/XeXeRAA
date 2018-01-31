#include "TH1D.h"
#include "TH1.h"
#include "TFile.h"
#include "../../../Settings.h"
#include <string>
#include <iostream>

void fillResoPoint(TH1D * r, int bin, std::string name){
  TFile * f = TFile::Open("output_0.root","read");
  TH1D * h = (TH1D*)f->Get(Form("%s_%d",name.c_str(),bin));
  h->Print("All");

  f->Close();
}


void trkReso(){
  Settings s = Settings();
 
  TFile * r = new TFile("resolutions.root","recreate"); 
  TH1D * recoRes = new TH1D("recoRes","",s.ntrkBins,s.xtrkbins);
  for(int c = 0; c<s.ntrkBins; c++){
    fillResoPoint(recoRes, c, "reso_reco");
  }

}

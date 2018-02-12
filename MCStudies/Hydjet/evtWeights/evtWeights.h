#ifndef EVTW
#define EVTW
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>

class EventWeight {
  public:
    EventWeight();
    ~EventWeight();

    float getEvtWeight(float vz, int hiBin);

    TFile * evtWeightFile;
    TH1D * vzWeight;
    TH1D * hiBinWeight;
};

float EventWeight::getEvtWeight(float vz, int hiBin){
  if(TMath::Abs(vz)>15){
    std::cout << "vz>15cm, returning 0" << std::endl;
    return 0;
  }
  if(hiBin<0 || hiBin>199){
    std::cout << "hiBin not in valid range, returning 0" << std::endl;
    return 0;
  }
  float vzW = vzWeight->GetBinContent(vzWeight->FindBin(vz));
  float hiBinW = hiBinWeight->GetBinContent(hiBinWeight->FindBin(hiBin));
  return vzW*hiBinW;
}

EventWeight::EventWeight(){
  evtWeightFile = TFile::Open("evtWeights.root","read");
  vzWeight = (TH1D*)evtWeightFile->Get("vz_weight");
  hiBinWeight = (TH1D*)evtWeightFile->Get("hiBin_weight");
}

EventWeight::~EventWeight(){
  evtWeightFile->Close();
}

void makeEvtWeights(){
  TFile * data = TFile::Open("data.root","read");
  TH1D * d_vz = (TH1D*)data->Get("vz");
  d_vz->Scale(1./d_vz->GetEntries());
  TH1D * d_hiBin = (TH1D*)data->Get("hiBin");
  d_hiBin->Rebin(2);
  d_hiBin->Scale(1./d_hiBin->GetEntries());

  TFile * mc = TFile::Open("mc.root","read");
//  TFile * mc = TFile::Open("EPOS_mc.root","read");
  TH1D * mc_vz = (TH1D*)mc->Get("vz");
  mc_vz->Scale(1./mc_vz->GetEntries());
  TH1D * mc_hiBin = (TH1D*)mc->Get("hiBin");
  mc_hiBin->Rebin(2);
  mc_hiBin->Scale(1./mc_hiBin->GetEntries());

  TFile * weights = TFile::Open("../evtWeights_EPOS.root","recreate");
  TH1D * vz_w = (TH1D*)d_vz->Clone("vz_weight");
  vz_w->Divide(mc_vz);
  TH1D * hiBin_w = (TH1D*)d_hiBin->Clone("hiBin_weight");
  hiBin_w->Divide(mc_hiBin);
  vz_w->Write();
  hiBin_w->Write();
  weights->Close();
  mc->Close();
  data->Close();
}

#endif

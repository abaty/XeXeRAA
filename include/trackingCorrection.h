#ifndef TRKCORR
#define TRKCORR
#include "TH2D.h"
#include "TFile.h"
#include <string>

class TrackingCorrection{

  public:
    TrackingCorrection(std::string file);
    ~TrackingCorrection();

    float getTrkCorr(float pt, int cent);

  private:
    TFile * corr;
    TH2D * eff;
    TH2D * fake;
    TH2D * sec;

    int centBin(int b);
};

int TrackingCorrection::centBin(int b){
  if(b<10) return 0;
  else if(b<20) return 1;
  else if(b<60) return 2;
  else if(b<100) return 3;
  else if(b<140) return 4;
  else return 5;
}

float TrackingCorrection::getTrkCorr(float pt, int cent){
  if(pt<0.5 || pt> 103.6) return 1;
  if(cent<0 || cent>199) return 1;

  int bin = centBin(cent);
  int p = eff->GetXaxis()->FindBin(pt);
  int c = eff->GetYaxis()->FindBin(bin);

  float f = fake->GetBinContent(p,c);
  if(f==1) f=0;//protection against zeroes
  float s = sec->GetBinContent(p,c);
  if(s==1) s=0;//protection against zeroes
  float e = eff->GetBinContent(p,c);
  if(e==0) e=1;//protection against nans

  return (1-f)*(1-s)/(e);
}

TrackingCorrection::TrackingCorrection(std::string file){
  TFile * corr = TFile::Open(file.c_str(),"read");
  eff = (TH2D*)corr->Get("efficiency2d");
  fake = (TH2D*)corr->Get("fake2d");
  sec = (TH2D*)corr->Get("secondary2d");
}

TrackingCorrection::~TrackingCorrection(){
  corr->Close();
}


#endif

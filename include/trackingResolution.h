#ifndef TRKRESO
#define TRKRESO
#include "TH2D.h"
#include "TFile.h"
#include <string>
#include "TH1D.h"
#include "TRandom3.h"

class TrackingResolution{

  public:
    TrackingResolution(std::string file);
    ~TrackingResolution();

    float getSmearing(float pt);

  private:
    TH1D * reso;
   
    TRandom3 * r;
};

float TrackingResolution::getSmearing(float pt){
  float sigma = 0.015;
  if(pt>0.5 && pt<103.6) sigma = reso->GetBinContent(reso->FindBin(pt));
  return pt*r->Gaus(1,sigma);
}

TrackingResolution::TrackingResolution(std::string file){
  TFile * corr = TFile::Open(file.c_str(),"read");
  reso = (TH1D*)corr->Get("recoCutRes");
  
  r = new TRandom3();
}

TrackingResolution::~TrackingResolution(){
}


#endif

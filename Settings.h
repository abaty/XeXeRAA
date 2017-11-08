#ifndef SKIM
#define SKIM
#include <iostream>

class Settings{
  public:
    Settings();

  float caloMatchValue = 0.5;
  //float caloMatchStart = 5;//FIXME
  float caloMatchStart = 20;

  float etaCut = 1.0;

  static const int ntrkBins = 34;
  double xtrkbins[ntrkBins+1] = { 0.3,0.4,0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};

  static const int nCentBins = 33;
  int lowCentBin[nCentBins] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,6,10,2,6,10,14,16,0,0,14,0,10};
  int highCentBin[nCentBins] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,20,20,20,6,10,14,16,18,6,10,18,2,18};

  TH1D * HI[nCentBins]; 
  TH1D * HI_NCollWeighted[nCentBins]; 
  TH1D * nVtx;
  int nVtx_int[nCentBins];

  private:

};

Settings::Settings(){
  std::cout << "Initialiing Settings!" << std::endl;
}

#endif



#ifndef SKIM
#define SKIM
#include <iostream>
#include <string>

class Settings{
  public:
    Settings();

  float caloMatchValue = 0.5;
  //float caloMatchStart = 5;//FIXME
  float caloMatchStart = 20;

  float etaCut = 1.0;

  std::string ppRefFile = "ppRef_March3_Pythia.root";
  std::string trkResFile = "resolutions_March3.root";
  std::string trkCorrFile = "trkCorr_April9_wSpeciesCorr.root";
  std::string trkCorrFile_noSpec = "trkCorr_Pythia_April9_CutIndex0.root";
  std::string trkCorrFile_noSpecCut1 = "trkCorr_Pythia_April9_CutIndex1.root";
  std::string trkCorrFile_noSpecCut2 = "trkCorr_Pythia_April9_CutIndex2.root";
  std::string trkCorrFile_noSpecCut3 = "trkCorr_Pythia_April9_CutIndex3.root";


  static const int ntrkBins = 32;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};
  static const int ntrkBins_extra = 18;
  double xtrkbins_extra[ntrkBins_extra+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 2.0 , 2.4  , 4.0 , 5.6  , 7.2 , 12.0, 24.0, 41.6,103.6};
  static const int ntrkBins_extra_D = 19;//dummy for plotting efficiency, should be same as above with 1 extra small bin
  double xtrkbins_extra_D[ntrkBins_extra_D+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 2.0 , 2.4  , 4.0 , 5.6  , 7.2 , 12.0, 24.0, 41.6,103.6,103.61};

  static const int nCentBins = 33;
  int lowCentBin[nCentBins] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,6,10,2,6,10,14,16,0,0,14,0,10};
  int highCentBin[nCentBins] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,16,20,20,6,10,14,18,18,6,10,16,2,18};
  float TAAuncert[nCentBins]   = {6.1,6.6,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,8.6,0.1,0.1,8.9,14,16.7,0.1,0.1,0.1,0.1,14.3,6.3,0.1};
  float Ncolluncert[nCentBins] = {6.1,6.6,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,8.8,0.1,0.1,9,14,17,0.1,0.1,0.1,0.1,14.2,6.3,0.1};

  float XeXeNcoll[6] = {922, 724.1, 399.4, 131.7, 34.4, 9.568};//Ncoll for 0-5,5-10,10-30,30-50,50-70,70-90
  float XeXeNcollErr[6] = {57.1, 48.3, 36, 18.4, 5.75, 1.36};//NcollErr for 0-5,5-10,10-30,30-50,50-70,70-90
  float XeXeNpart[6] = {236.5, 206.6, 140.8, 68.04, 26.85, 10.4};//Npart for 0-5,5-10,10-30,30-50,50-70,70-90
  float XeXeNpartErr[6] = {1.74, 1.54, 2.41, 3.07, 2.09, 0.834};//NpartErr for 0-5,5-10,10-30,30-50,50-70,70-90

  //from https://twiki.cern.ch/twiki/pub/CMS/HiCentrality2017/TAA_Uncert_Jason_2017-02-23.pdf
  float PbPbNcoll[6] = {1820, 1430, 805, 267, 65.4, 10.7};//Ncoll for 0-5,5-10,10-30,30-50,50-70,70-90
  float PbPbNcollErrU[6] = {130, 100, 55, 20, 7, 1.7};//NcollErr for 0-5,5-10,10-30,30-50,50-70,70-90
  float PbPbNcollErrD[6] = {140, 110, 58, 20, 6.6, 1.5};//NcollErr for 0-5,5-10,10-30,30-50,50-70,70-90
  float PbPbNpart[6] = {384.3, 333.3, 226.7, 109.2, 42.22, 11.11};//Npart for 0-5,5-10,10-30,30-50,50-70,70-90
  float PbPbNpartErrU[6] = {1.8, 3, 5.2, 4.3, 3, 1.3};//NpartErr for 0-5,5-10,10-30,30-50,50-70,70-90
  float PbPbNpartErrD[6] = {2, 3.2, 5.3, 4.2, 2.9, 1.2};//NpartErr for 0-5,5-10,10-30,30-50,50-70,70-90
  
  bool doTrackDists = true;
  bool doRejectPU = false;

  TH1D * HI_smeared[nCentBins]; 
  TH1D * HI_UpSpecCorr[nCentBins]; 
  TH1D * HI_UpFakeCorr[nCentBins]; 
  TH1D * HI_NoSpec[nCentBins]; 
  TH1D * HI_NoSpecCut1[nCentBins]; 
  TH1D * HI_NoSpecCut2[nCentBins]; 
  TH1D * HI_NoSpecCut3[nCentBins]; 
  TH1D * HI_NoSpecCut1_copy[nCentBins]; 
  TH1D * HI_NoSpecCut2_copy[nCentBins]; 
  TH1D * HI_NoSpecCut3_copy[nCentBins]; 
  TH1D * HI_NoSpec_EffUp1Sig[nCentBins]; 

  TH1D * HI[nCentBins]; 
  TH1D * HI_TaaWeighted[nCentBins]; 
  TH1D * HI_NcollWeighted[nCentBins]; 
  TH1D * nVtx;
  float nVtx_float[nCentBins];

  private:

};

Settings::Settings(){
  std::cout << "Initialiing Settings!" << std::endl;
}

#endif



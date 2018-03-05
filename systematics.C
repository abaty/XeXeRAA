#include "Settings.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "include/trackingCorrection.h"

void systematics(){
  Settings s = Settings();
  TFile * ppInput = new TFile(s.ppRefFile.c_str(),"read");
  TH1D * ppSyst_NoLumi = (TH1D*)ppInput->Get("ppScaledSyst_NoLumi");
  TH1D * ppSyst = (TH1D*)ppInput->Get("ppScaledSyst");
  
  TFile * input = new TFile("output_0.root","read");

  TFile * output = new TFile("systematics.root","recreate");
  ppSyst_NoLumi->SetDirectory(output);
  ppSyst_NoLumi->Write();
  ppSyst->SetDirectory(output);
  ppSyst->Write();

  //definitions
  TH1D * spec_reso[s.nCentBins]; 
  for(int i = 0; i<s.nCentBins; i++){
    spec_reso[i] = new TH1D(Form("spec_reso_%d",i),"",s.ntrkBins,s.xtrkbins);
  }
   

  //spectra

  for(int i = 0; i<s.nCentBins; i++){
    for(int j = 1; j<s.ntrkBins+1; j++){
      //resolution is a flat 0.5%
      spec_reso[i]->SetBinContent(j,0.005);
    }
  }

  output->Write(); 

}

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
  for(int c = 0; c<s.nCentBins; c++){
    s.HI[c] = (TH1D*)input->Get(Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_UpSpecCorr[c] = (TH1D*)input->Get(Form("HI_UpSpecCorr_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_UpSpecCorr[c]->Divide(s.HI[c]);
    s.HI_UpFakeCorr[c] = (TH1D*)input->Get(Form("HI_UpFakeCorr_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_UpFakeCorr[c]->Divide(s.HI[c]);
  }

  TFile * output = new TFile("systematics.root","recreate");
  ppSyst_NoLumi->SetDirectory(output);
  //ppSyst_NoLumi->Write();
  ppSyst->SetDirectory(output);
  //ppSyst->Write();

  //definitions
  TH1D * spec_reso[s.nCentBins]; 
  TH1D * spec_MCvsDataEff[s.nCentBins]; 
  TH1D * spec_SpecCorr[s.nCentBins]; 
  TH1D * spec_FakeCorr[s.nCentBins]; 
  TH1D * spec_Total[s.nCentBins]; 
  for(int i = 0; i<s.nCentBins; i++){
    spec_reso[i] = new TH1D(Form("spec_reso_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_MCvsDataEff[i] = new TH1D(Form("spec_MCvsDataEff_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_SpecCorr[i] = new TH1D(Form("spec_specCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_FakeCorr[i] = new TH1D(Form("spec_fakeCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_Total[i] = new TH1D(Form("spec_Total_%d",i),"",s.ntrkBins,s.xtrkbins);
  }
   

  //spectra
  for(int i = 0; i<s.nCentBins; i++){
    for(int j = 1; j<s.ntrkBins+1; j++){
      double total2 = 0; 
      //species correction
      spec_SpecCorr[i]->SetBinContent(j,TMath::Abs(s.HI_UpSpecCorr[i]->GetBinContent(j)-1));
      total2 += TMath::Power(s.HI_UpSpecCorr[i]->GetBinContent(j)-1,2);

      //fake correction
      spec_FakeCorr[i]->SetBinContent(j,TMath::Abs(s.HI_UpFakeCorr[i]->GetBinContent(j)-1));
      total2 += TMath::Power(s.HI_UpFakeCorr[i]->GetBinContent(j)-1,2);

      //resolution is a flat 0.5%
      spec_reso[i]->SetBinContent(j,0.005);
      total2 += 0.005*0.005;

      //resolution is a flat 5%
      spec_MCvsDataEff[i]->SetBinContent(j,0.05);
      total2 += 0.05*0.05;

      //total
      spec_Total[i]->SetBinContent(j,TMath::Sqrt(total2));
    }
  }

  output->Write(); 

}

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include <iostream>

void pythia8MCAnalyzer(){
  TH1::SetDefaultSumw2();


  TFile * input = TFile::Open("EPOS5TeV_Nov16.root","read");
  TH1D * weightSumMB = (TH1D*)input->Get("weightSumMB");
  TH1D * pythia8MB = (TH1D*)input->Get("pythia8MB");
  pythia8MB->Scale(1.0/(float)weightSumMB->GetBinContent(1));
  
  TFile * input544 = TFile::Open("EPOS544TeV_Nov16.root","read");
  TH1D * weightSumMB544 = (TH1D*)input544->Get("weightSumMB");
  TH1D * pythia8MB544 = (TH1D*)input544->Get("pythia8MB");
  pythia8MB544->Scale(1.0/(float)weightSumMB544->GetBinContent(1));
  
  TFile * output = TFile::Open("EPOSSpectra.root","recreate");
  output->cd();
  TH1D * pythia8 = (TH1D*)pythia8MB->Clone("EPOS_5");
  //pythia8->Add(pythia8Hard);
  
  TH1D * pythia8_544 = (TH1D*)pythia8MB544->Clone("EPOS_544");
  //pythia8_544->Add(pythia8Hard544);

  for(int i = 1; i<pythia8->GetSize()-1; i++){
    pythia8->SetBinContent(i,pythia8->GetBinContent(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
    pythia8->SetBinError(i,pythia8->GetBinError(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
    
    pythia8_544->SetBinContent(i,pythia8_544->GetBinContent(i)/(2.0*2.0*TMath::Pi()*(pythia8_544->GetBinLowEdge(i+1)-pythia8_544->GetBinLowEdge(i))*pythia8_544->GetBinCenter(i)));
    pythia8_544->SetBinError(i,pythia8_544->GetBinError(i)/(2.0*2.0*TMath::Pi()*(pythia8_544->GetBinLowEdge(i+1)-pythia8_544->GetBinLowEdge(i))*pythia8_544->GetBinCenter(i)));
  }

  output->Write();
  output->Close();
}


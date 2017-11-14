#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include <iostream>

void pythia8MCAnalyzer(){

  TFile * input = TFile::Open("pythia8_5TeV_Nov14_2017.root","read");
  TH1D * weightSumHard = (TH1D*)input->Get("weightSumHard");
  TH1D * weightSumMB = (TH1D*)input->Get("weightSumMB");
  TH1D * pythia8MB = (TH1D*)input->Get("pythia8MB");
  TH1D * pythia8Hard = (TH1D*)input->Get("pythia8Hard");
  pythia8MB->Scale(1.0/(float)weightSumMB->GetBinContent(1));
  pythia8Hard->Scale(1.0/(float)weightSumHard->GetBinContent(1));
  
  TFile * output = TFile::Open("Pythia8Spectra.root","recreate");
  output->cd();
  TH1D * pythia8 = (TH1D*)pythia8MB->Clone("pythia8");
  pythia8->Add(pythia8Hard);

  for(int i = 1; i<pythia8->GetSize()-1; i++){
    pythia8->SetBinContent(i,pythia8->GetBinContent(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
    pythia8->SetBinError(i,pythia8->GetBinError(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
  }

  output->Write();
  output->Close();
}


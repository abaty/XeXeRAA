#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include <iostream>

void pythia8MCAnalyzer(){

  const int ntrkBins = 32;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};

  float MB5TeVPythia_xsection = 67.89;//given in mb
  float pthat155TeVPythia_xsection = 5.232e-01;

  TFile * input_pythiaHard = TFile::Open("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia85TeV/pthat15/Pythia8pthat15_5TeV/Pythia8pthat15_5TeV/171109_204504/0000/output_1.root","read");
  TTree * e_hard = (TTree*)input_pythiaHard->Get("Events");
  TH1D * weightSum = new TH1D("weightSum","weightSum",1,0,2);
  e_hard->Draw("1>>weightSum","GenEventInfoProduct_generator__VALIDATION.obj.weight()");

  TFile * output = TFile::Open("Pythia8Spectra.root","recreate");
  TH1D * pythia8 = new TH1D("pythia8","pythia8",ntrkBins,xtrkbins);
  
  for(int f = 1; f<3; f++){
    std::cout << f << std::endl;
    TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia85TeV/MB/Pythia8MB_5TeV/Pythia8MB_5TeV/171109_193621/0000/output_%d.root",f),"read");
    TTree * e = (TTree*)input_pythiaMB->Get("Events");

    //MB contribution
    e->Draw("recoGenParticles_genParticles__VALIDATION.obj->pt()>>+pythia8",Form("%f/%f*(recoGenParticles_genParticles__VALIDATION.obj->pt()<15 && TMath::Abs(recoGenParticles_genParticles__VALIDATION.obj->eta())<1.0 && recoGenParticles_genParticles__VALIDATION.obj->charge()!=0 && recoGenParticles_genParticles__VALIDATION.obj->status()==1 && GenEventInfoProduct_generator__VALIDATION.obj.qScale()<15)",MB5TeVPythia_xsection,(float)e->GetEntries()));
    e_hard->Draw("recoGenParticles_genParticles__VALIDATION.obj->pt()>>+pythia8",Form("%f/%f*GenEventInfoProduct_generator__VALIDATION.obj.weight()*(TMath::Abs(recoGenParticles_genParticles__VALIDATION.obj->eta())<1.0 && recoGenParticles_genParticles__VALIDATION.obj->charge()!=0 && recoGenParticles_genParticles__VALIDATION.obj->status()==1)",pthat155TeVPythia_xsection,weightSum->GetBinContent(1)));
    input_pythiaMB->Close(); 
  }

  for(int i = 1; i<pythia8->GetSize()-1; i++){
    pythia8->SetBinContent(i,pythia8->GetBinContent(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
    pythia8->SetBinError(i,pythia8->GetBinError(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
  }

  output->Write();
  output->Close();

}


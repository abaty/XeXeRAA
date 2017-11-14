#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void pythia8MCAnalyzer(int job, int nEvtPerFile = 1000000000){

  const int ntrkBins = 32;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};

  float MB5TeVPythia_xsection = 67.89;//given in mb
  float pthat155TeVPythia_xsection = 5.232e-01;

  TFile * output = TFile::Open(Form("output_%d.root",job),"recreate");
  TH1D * weightSumHard = new TH1D("weightSumHard","weightSumHard",1,0,2);
  TH1D * weightSumMB = new TH1D("weightSumMB","weightSumMB",1,0,2);
  TH1D * pythia8MB = new TH1D("pythia8MB","pythia8MB",ntrkBins,xtrkbins);
  TH1D * pythia8Hard = new TH1D("pythia8Hard","pythia8Hard",ntrkBins,xtrkbins);
 
  for(int f = job+1; f<job+2; f++){
    std::cout << f << std::endl;
    TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia85TeV/MB/Pythia8MB_5TeV/Pythia8MB_5TeV/171109_193621/0000/output_%d.root",f),"read");
    TTree * e = (TTree*)input_pythiaMB->Get("Events");

    TFile * input_pythiaHard = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia85TeV/pthat15/Pythia8pthat15_5TeV/Pythia8pthat15_5TeV/171109_204504/0000/output_%d.root",f),"read");
    TTree * e_hard = (TTree*)input_pythiaHard->Get("Events");
   
    output->cd(); 
    e_hard->Draw("1>>+weightSumHard","GenEventInfoProduct_generator__VALIDATION.obj.weight()","",TMath::Min(nEvtPerFile,(int)e_hard->GetEntries()));
    weightSumMB->Fill(1,(int)e->GetEntries());   

    //MB contribution
    e->Draw("recoGenParticles_genParticles__VALIDATION.obj->pt()>>+pythia8MB",Form("%f*(recoGenParticles_genParticles__VALIDATION.obj->pt()>0.5 && recoGenParticles_genParticles__VALIDATION.obj->pt()<15 && TMath::Abs(recoGenParticles_genParticles__VALIDATION.obj->eta())<1.0 && recoGenParticles_genParticles__VALIDATION.obj->charge()!=0 && recoGenParticles_genParticles__VALIDATION.obj->status()==1 && GenEventInfoProduct_generator__VALIDATION.obj.qScale()<15)",MB5TeVPythia_xsection),"",TMath::Min(nEvtPerFile,(int)e->GetEntries()));

   e_hard->Draw("recoGenParticles_genParticles__VALIDATION.obj->pt()>>+pythia8Hard",Form("%f*GenEventInfoProduct_generator__VALIDATION.obj.weight()*(recoGenParticles_genParticles__VALIDATION.obj->pt()>0.5 && TMath::Abs(recoGenParticles_genParticles__VALIDATION.obj->eta())<1.0 && recoGenParticles_genParticles__VALIDATION.obj->charge()!=0 && recoGenParticles_genParticles__VALIDATION.obj->status()==1)",pthat155TeVPythia_xsection),"",TMath::Min(nEvtPerFile,(int)e_hard->GetEntries()));
   
    
    input_pythiaMB->Close(); 
    input_pythiaHard->Close(); 
  }

  output->cd();
  pythia8MB->Scale(1.0/(float)weightSumMB->GetBinContent(1));
  pythia8Hard->Scale(1.0/(float)weightSumHard->GetBinContent(1));
  
  TH1D * pythia8 = (TH1D*)pythia8MB->Clone("pythia8");
  pythia8->Add(pythia8Hard);

  for(int i = 1; i<pythia8->GetSize()-1; i++){
    pythia8->SetBinContent(i,pythia8->GetBinContent(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
    pythia8->SetBinError(i,pythia8->GetBinError(i)/(2.0*2.0*TMath::Pi()*(pythia8->GetBinLowEdge(i+1)-pythia8->GetBinLowEdge(i))*pythia8->GetBinCenter(i)));
  }

  output->Write();
  output->Close();
}


int main(int argc, const char* argv[])
{
  if(argc != 5)
  {
    std::cout << "Usage: <job> <totalJobs> <fileList> <dummyVar>" << std::endl;
    return 1;
  }  

  int job = std::atoi(argv[1]);
  int totalJobs = std::atoi(argv[2]);
  std::string fList = argv[3];
  int dummy = std::atoi(argv[4]);
  std::string buffer;
  std::vector<std::string> listOfFiles;
  std::ifstream inFile(fList.data());

  if(!inFile.is_open())
  {
    std::cout << "Error opening jet file. Exiting." <<std::endl;
    return 1;
  }
  else
  {
    int line = 0;
    while(true)
    {
      inFile >> buffer;
      if(inFile.eof()) break;
      if(line%totalJobs==job) listOfFiles.push_back(buffer);
      line++;
    }
  }

  dummy = dummy+1;

  pythia8MCAnalyzer(job);

  return 0; 
}

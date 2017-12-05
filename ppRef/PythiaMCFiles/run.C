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

  //5.02 TeV numbers
  //float MB5TeVPythia_xsection = 67.89;//given in mb
  //float pthat155TeVPythia_xsection = 5.232e-01;
  //5.44TeV numbers
  //float MB5TeVPythia_xsection = 68.72;//given in mb
  //float pthat155TeVPythia_xsection = 5.952e-01;
  //7TeV numbers
  float MB5TeVPythia_xsection = 71.39;//given in mb
  float pthat155TeVPythia_xsection = 8.430e-01;
  

  TFile * output = TFile::Open(Form("output_%d.root",job),"recreate");
  TH1D * weightSumHard = new TH1D("weightSumHard","weightSumHard",1,0,2);
  TH1D * weightSumMB = new TH1D("weightSumMB","weightSumMB",1,0,2);
  TH1D * pythia8MB = new TH1D("pythia8MB","pythia8MB",ntrkBins,xtrkbins);
  TH1D * pythia8Hard = new TH1D("pythia8Hard","pythia8Hard",ntrkBins,xtrkbins);
 
  for(int f = job+1; f<job+2; f++){
    std::cout << f << std::endl;
    //TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia85TeV/MB/Pythia8MB_5TeV/Pythia8MB_5TeV/171109_193621/0000/output_%d.root",f),"read");
    //TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia8544TeV/MB/Pythia8MB_544TeV/Pythia8MB_544TeV/171109_200101/0000/output_%d.root",f),"read");
    TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia87TeV/MB/Pythia8MB_5TeV/Pythia8MB_5TeV/171123_162808/0000/output_%d.root",f),"read");
    TTree * e = (TTree*)input_pythiaMB->Get("Events");

    //TFile * input_pythiaHard = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia85TeV/pthat15/Pythia8pthat15_5TeV/Pythia8pthat15_5TeV/171109_204504/0000/output_%d.root",f),"read");
    //TFile * input_pythiaHard = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia8544TeV/pthat15/Pythia8pthat15_544TeV/Pythia8pthat15_544TeV/171109_204613/0000/output_%d.root",f),"read");
    TFile * input_pythiaHard = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/Pythia87TeV/pthat15/Pythia8pthat15_5TeV/Pythia8pthat15_5TeV/171123_163123/0000/output_%d.root",f),"read");
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

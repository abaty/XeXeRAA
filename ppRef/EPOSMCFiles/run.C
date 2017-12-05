#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void pythia8MCAnalyzer(int job, int nEvtPerFile = 10000000){

  const int ntrkBins = 32;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};

  //5.02 TeV numbers
  //float MB5TeVPythia_xsection = 68.52;//given in mb
  //5.44TeV numbers
  //float MB5TeVPythia_xsection = 69.46;//given in mb
  //7TeV numbers
  float MB5TeVPythia_xsection = 72.46;//given in mb
  

  TFile * output = TFile::Open(Form("output_%d.root",job),"recreate");
  TH1D * weightSumMB = new TH1D("weightSumMB","weightSumMB",1,0,2);
  TH1D * pythia8MB = new TH1D("pythia8MB","pythia8MB",ntrkBins,xtrkbins);
 
  for(int f = job+1; f<job+2; f++){
    std::cout << f << std::endl;
    //TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/EPOS5_v2/EPOSMB_5TeV/EPOS_5TeV/171123_152554/0000/output_%d.root",f),"read");
    //TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/EPOS544_v2/EPOSMB_544TeV/EPOS_544TeV/171123_153356/0000/output_%d.root",f),"read");
    TFile * input_pythiaMB = TFile::Open(Form("/mnt/hadoop/cms/store/user/abaty/XeXeRAAMC/EPOS7/EPOSMB_7TeV/EPOS_7TeV/171122_212453/0000/output_%d.root",f),"read");
    TTree * e = (TTree*)input_pythiaMB->Get("Events");

   
    output->cd(); 
    weightSumMB->Fill(1,(int)e->GetEntries());   

    //MB contribution
    e->Draw("recoGenParticles_genParticles__VALIDATION.obj->pt()>>+pythia8MB",Form("%f*(recoGenParticles_genParticles__VALIDATION.obj->pt()>0.5 && TMath::Abs(recoGenParticles_genParticles__VALIDATION.obj->eta())<1.0 && recoGenParticles_genParticles__VALIDATION.obj->charge()!=0 && recoGenParticles_genParticles__VALIDATION.obj->status()==1)",MB5TeVPythia_xsection),"",TMath::Min(nEvtPerFile,(int)e->GetEntries()));
    
    input_pythiaMB->Close(); 
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

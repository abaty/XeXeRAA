#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../../Settings.h"
#include "../../include/trackingBinMap.h"


void countTracks(std::vector<std::string> fileList, int jobNumber){
  Settings s = Settings();


  TFile * output = TFile::Open(Form("output_%d.root",jobNumber),"recreate");
  TH1D * hiBin_h = new TH1D("hiBin","hiBin",200,0,200);
  TH1D * vz_h = new TH1D("vz","vz",120,-30,30);
  TH1D * hiBin_Weighted_h = new TH1D("hiBin","hiBin",200,0,200);
  TH1D * vz_Weighted_h = new TH1D("vz","vz",120,-30,30);
  TH1D * noVtxCent_h = new TH1D("noVtxCent_h","noVtxCent_h",200,0,200);


  TH1D *nHit[17], *chi2[17], *DCAz[17], *DCAxy[17], *ptErr[17], *eta[17], *phi[17], *caloMatch[17];
  for(int c = 0; c<17; c++){
    nHit[c] = new TH1D(Form("nHit%d",c),Form("nHit%d",c),30,0,30);
    chi2[c] = new TH1D(Form("chi2%d",c),Form("chi2%d",c),50,0,0.3);
    ptErr[c] = new TH1D(Form("ptErr%d",c),Form("ptErr%d",c),50,0,0.2);
    DCAz[c] = new TH1D(Form("DCAz%d",c),Form("DCAz%d",c),50,-5,5);
    DCAxy[c] = new TH1D(Form("DCAxy%d",c),Form("DCAxy%d",c),50,-5,5);
    eta[c] = new TH1D(Form("eta%d",c),Form("eta%d",c),50,-3,3);
    phi[c] = new TH1D(Form("phi%d",c),Form("phi%d",c),50,-TMath::Pi(),TMath::Pi());
    caloMatch[c] = new TH1D(Form("caloMatch%d",c),Form("caloMatch%d",c),50,0,2);
  }

  int nTrk;
  int hiBin;
  float vz;
  int vtx;
  int beam;
  int hfCoinc;
  float trkPt[50000];
  float trkPtError[50000];
  float trkEta[50000];
  float trkPhi[50000];
  float pfEcal[50000];
  float pfHcal[50000];
  float trkDxy1[50000];//with respect to highest Pt Vertex
  float trkDxyError1[50000];
  float trkDz1[50000];
  float trkDzError1[50000];
  bool highPurity[50000];
  unsigned char trkNHit[50000];
  unsigned char trkNlayer[50000];
  unsigned char trkNdof[50000];
  float trkChi2[50000];

  for(unsigned int f = 0; f<fileList.size(); f++){
  //for(unsigned int f = 0; f<10; f++){
    std::cout << "File: " << f << std::endl;
    TFile * input = TFile::Open(fileList.at(f).c_str(),"read");
    TTree * skim = (TTree*)input->Get("skimanalysis/HltTree");
    TTree * evt = (TTree*)input->Get("hiEvtAnalyzer/HiTree");
    TTree * trk = (TTree*)input->Get("ppTrack/trackTree");

    evt->SetBranchAddress("hiBin",&hiBin);
    evt->SetBranchAddress("vz",&vz);  

    skim->SetBranchAddress("pPAprimaryVertexFilter",&vtx);
    skim->SetBranchAddress("pBeamScrapingFilter",&beam);
    skim->SetBranchAddress("phfCoincFilter2",&hfCoinc);
    trk->SetBranchAddress("nTrk",&nTrk);
    trk->SetBranchAddress("trkPt",trkPt);
    trk->SetBranchAddress("trkPhi",trkPhi);
    trk->SetBranchAddress("trkEta",trkEta);
    trk->SetBranchAddress("highPurity",&highPurity);
    trk->SetBranchAddress("trkPtError",trkPtError);
    trk->SetBranchAddress("trkDxy1",trkDxy1);
    trk->SetBranchAddress("trkDxyError1",trkDxyError1);
    trk->SetBranchAddress("trkDz1",trkDz1);
    trk->SetBranchAddress("trkDzError1",trkDzError1);
    trk->SetBranchAddress("trkChi2",&trkChi2);
    trk->SetBranchAddress("trkNlayer",&trkNlayer);
    trk->SetBranchAddress("trkNdof",&trkNdof);
    trk->SetBranchAddress("trkNHit",&trkNHit);

    trk->SetBranchAddress("pfEcal",pfEcal);
    trk->SetBranchAddress("pfHcal",pfHcal);
    
    for(int i = 0; i<trk->GetEntries(); i++){
      skim->GetEntry(i);
      evt->GetEntry(i);
      if(!vtx) noVtxCent_h->Fill(hiBin);
      if(!beam || !vtx || !hfCoinc) continue;
      vz_h->Fill(vz);
      if(TMath::Abs(vz)>15) continue;
      if(hiBin<0 || hiBin>199) continue;//protection
      hiBin_h->Fill(hiBin);

      trk->GetEntry(i);
      //for tracking
      if(s.doTrackDists){
        for(int j = 0; j<nTrk; j++){
          if(!highPurity[j]) continue;     
          if(trkPt[j]<0.5) continue;
          if(TMath::Abs(trkDz1[j]/trkDzError1[j])>3 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>3) continue;
          if(trkPtError[j]/trkPt[j]>0.1) continue;
          if(trkNHit[j]<11) continue;
          if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;
          float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
          if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
          
          eta[0]->Fill(trkEta[j]);
          eta[trkBinMap(hiBin,trkPt[j])]->Fill(trkEta[j]);
          if(TMath::Abs(trkEta[j])>s.etaCut) continue;
          
          phi[0]->Fill(trkPhi[j]);
          phi[trkBinMap(hiBin,trkPt[j])]->Fill(trkPhi[j]);
          DCAz[0]->Fill(trkDz1[j]/trkDzError1[j]);
          DCAz[trkBinMap(hiBin,trkPt[j])]->Fill(trkDz1[j]/trkDzError1[j]);
          DCAxy[0]->Fill(trkDxy1[j]/trkDxyError1[j]);
          DCAxy[trkBinMap(hiBin,trkPt[j])]->Fill(trkDxy1[j]/trkDxyError1[j]);
          nHit[0]->Fill(trkNHit[j]);
          nHit[trkBinMap(hiBin,trkPt[j])]->Fill(trkNHit[j]);
          chi2[0]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]);
          chi2[trkBinMap(hiBin,trkPt[j])]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]);
          ptErr[0]->Fill(trkPtError[j]/trkPt[j]);
          ptErr[trkBinMap(hiBin,trkPt[j])]->Fill(trkPtError[j]/trkPt[j]);
          //float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
          caloMatch[0]->Fill(Et/trkPt[j]);
          caloMatch[trkBinMap(hiBin,trkPt[j])]->Fill(Et/trkPt[j]);
        }
      }//end of tracking stuff
    }
  }
  output->Write();
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

  countTracks(listOfFiles,job);

  return 0; 
}

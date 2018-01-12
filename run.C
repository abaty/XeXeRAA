#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "Settings.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//FIXME preliminary
double findTaaAverage(int L, int H) {
  if(L==0 && H==10) return 13.9;
  if(L==10 && H==20) return 10.8;
  if(L==20 && H==30) return 8.47;
  if(L==30 && H==40) return 6.60;
  if(L==40 && H==50) return 5.1;
  if(L==50 && H==60) return 3.89;
  if(L==60 && H==80) return 2.56;
  if(L==80 && H==100) return 1.37;
  if(L==100 && H==120) return 0.69;
  if(L==120 && H==140) return 0.328;
  if(L==140 && H==160) return 0.151;
  if(L==160 && H==200) return 0.053;
  if(L==0 && H==20) return 12.3;
  if(L==20 && H==60) return 6.01;
  if(L==60 && H==100) return 1.96;
  if(L==100 && H==200) return 0.255;
  if(L==0 && H==200) return 2.96;
  if(L==100 && H==140) return 0.509;
  if(L==140 && H==180) return 0.111;
  if(L==100 && H==180) return 0.310;
  return 1.0;
}

void countTracks(std::vector<std::string> fileList, int jobNumber){
  Settings s = Settings();

  TFile * output = TFile::Open(Form("output_%d.root",jobNumber),"recreate");
  for(int c = 0; c<s.nCentBins; c++){
    s.HI[c] = new TH1D(Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_TaaWeighted[c] = new TH1D(Form("HI_TaaWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_TaaWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
  }
  s.nVtx = new TH1D("nVtx","nVtx",20,0,20);
  TH1D * hiBin_h = new TH1D("hiBin","hiBin",200,0,200);
  TH1D * scaledPP;
  TFile * ppFile = TFile::Open("ppRef_Dec1_Pythia.root","read");
  scaledPP = (TH1D*)ppFile->Get("ppScaled");
  scaledPP->SetDirectory(output);
  ppFile->Close();
  output->cd();

  int nTrk;
  int hiBin;
  float vz;
  int vtx;
  int beam;
  int hfCoinc;//FIXME
  float trkPt[50000];
  float trkPtError[50000];
  float trkEta[50000];
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
  int MB[21];

  for(unsigned int f = 0; f<fileList.size(); f++){
  //for(unsigned int f = 0; f<10; f++){
    std::cout << "File: " << f << std::endl;
    TFile * input = TFile::Open(fileList.at(f).c_str(),"read");
    TTree * hlt = (TTree*)input->Get("hltanalysisReco/HltTree");
    TTree * skim = (TTree*)input->Get("skimanalysis/HltTree");
    TTree * evt = (TTree*)input->Get("hiEvtAnalyzer/HiTree");
    TTree * trk = (TTree*)input->Get("ppTrack/trackTree");

    hlt->SetBranchAddress("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1",&(MB[0]));
    for(int i = 1; i<21; i++) hlt->SetBranchAddress(Form("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_part%d_v1",i),&(MB[i]));
    evt->SetBranchAddress("hiBin",&hiBin);
    evt->SetBranchAddress("vz",&vz);  

    skim->SetBranchAddress("pPAprimaryVertexFilter",&vtx);
    skim->SetBranchAddress("pBeamScrapingFilter",&beam);
    skim->SetBranchAddress("phfCoincFilter2",&hfCoinc);
    trk->SetBranchAddress("nTrk",&nTrk);
    trk->SetBranchAddress("trkPt",trkPt);
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
    trk->SetBranchAddress("trkEta",trkEta);
    trk->SetBranchAddress("highPurity",&highPurity);


    for(int i = 0; i<trk->GetEntries(); i++){
      hlt->GetEntry(i);
      bool MinBias = false;
      for(int x = 0; x<21; x++) MinBias = MinBias || MB[x];
      if(!MinBias) continue;

      skim->GetEntry(i);
      if(!beam || !vtx || !hfCoinc) continue;

      evt->GetEntry(i);
      if(TMath::Abs(vz)>15) continue;
      for(int c = 0; c<s.nCentBins; c++){
        if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;
        if(c<20) s.nVtx->Fill(c);
        s.nVtx_int[c]++;
      }
      hiBin_h->Fill(hiBin);
 
      trk->GetEntry(i); 
      //for tracking
      if(s.fillTrackDistribuutions){
        for(int j = 0; j<nTrk; j++){
           

          }
      }//end of tracking stuff

      for(int j = 0; j<nTrk; j++){
        if(TMath::Abs(trkEta[j])>s.etaCut) continue;
        if(TMath::Abs(trkDz1[j]/trkDzError1[j])>3 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>3) continue;
        if(!highPurity[j]) continue;
        if(trkPtError[j]/trkPt[j]>0.1) continue;
        if(trkNHit[j]<11) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;
        float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
        if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
 
        float weight = 1./0.7;
        for(int c = 0; c<s.nCentBins; c++){
          if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;

          float binCenter = s.HI[0]->GetXaxis()->GetBinCenter(s.HI[0]->GetXaxis()->FindBin(trkPt[j]));
          s.HI[c]->Fill(trkPt[j],weight/binCenter);
        }//cent bin loop
      }//trk loop
    }//event loop
    input->Close();
  }//file loop

  output->cd();
  TH1D * RAA[s.nCentBins];
  for(int c = 0; c<s.nCentBins; c++)
  {
    double Taa = findTaaAverage(s.lowCentBin[c]*10,s.highCentBin[c]*10);
    for(int i = 1; i<s.HI[c]->GetSize()+1; i++)
    { 
      s.HI_TaaWeighted[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/((float)s.nVtx_int[c]*2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Taa)); 
      s.HI_TaaWeighted[c]->SetBinError(i,s.HI[c]->GetBinError(i)/((float)s.nVtx_int[c]*2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Taa));
      s.HI[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/((float)s.nVtx_int[c]*2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI[c]->SetBinError(i,s.HI[c]->GetBinError(i)/((float)s.nVtx_int[c]*2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
    }
    //RAA
    RAA[c] = (TH1D*) s.HI_TaaWeighted[c]->Clone(Form("RAA_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    RAA[c]->Divide(scaledPP);
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

  countTracks(listOfFiles, job);

  return 0; 
}

#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "Settings.h"
#include "include/trackingBinMap.h"
#include "include/fillTrkDists.h"
#include "include/trackingCorrection.h"
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
  TrackingCorrection trkCorr = TrackingCorrection("trkCorr_Hydjet_Feb6.root");
  TF1 * evtSelEff = new TF1("evtSelEff","0.5*(1+TMath::Erf((x-13.439)/(TMath::Sqrt(x)*0.811)))",0,100000);

  TFile * output = TFile::Open(Form("output_%d.root",jobNumber),"recreate");
  TH1D * hiBin_h = new TH1D("hiBin","hiBin",200,0,200);
  TH1D * hiBinNoWeight_h = new TH1D("hiBinNoWeight","hiBinNoWeight",200,0,200);
  TH1D * noVtxCent_h = new TH1D("noVtxCent_h","noVtxCent_h",200,0,200);
  TH1D * vz_h = new TH1D("vz","vz",120,-30,30);
  TH1D * nVtxMoreBin = new TH1D("nVtxMoreBin","nVtxMoreBin",50,0,50);
  TH1D *nHit[17][3], *chi2[17][3], *DCAz[17][3], *DCAxy[17][3], *ptErr[17][3], *eta[17][3], *phi[17][3], *caloMatch[17][3];
  if(s.doTrackDists){
    for(int c = 0; c<17; c++){
      for(int c2 = 0; c2<3; c2++){
        nHit[c][c2] = new TH1D(Form("nHit%d_cut%d",c,c2),Form("nHit%d_cut%d",c,c2),30,0,30);
        chi2[c][c2] = new TH1D(Form("chi2%d_cut%d",c,c2),Form("chi2%d_cut%d",c,c2),50,0,0.3);
        ptErr[c][c2] = new TH1D(Form("ptErr%d_cut%d",c,c2),Form("ptErr%d_cut%d",c,c2),50,0,0.2);
        DCAz[c][c2] = new TH1D(Form("DCAz%d_cut%d",c,c2),Form("DCAz%d_cut%d",c,c2),50,-5,5);
        DCAxy[c][c2] = new TH1D(Form("DCAxy%d_cut%d",c,c2),Form("DCAxy%d_cut%d",c,c2),50,-5,5);
        eta[c][c2] = new TH1D(Form("eta%d_cut%d",c,c2),Form("eta%d_cut%d",c,c2),50,-3,3);
        phi[c][c2] = new TH1D(Form("phi%d_cut%d",c,c2),Form("phi%d_cut%d",c,c2),50,-TMath::Pi(),TMath::Pi());
        caloMatch[c][c2] = new TH1D(Form("caloMatch%d_cut%d",c,c2),Form("caloMatch%d_cut%d",c,c2),50,0,2);
      }
    }
  }

  s.nVtx = new TH1D("nVtx","nVtx",20,0,20);
  for(int c = 0; c<s.nCentBins; c++){
    s.HI[c] = new TH1D(Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_TaaWeighted[c] = new TH1D(Form("HI_TaaWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_TaaWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
  }


  TH1D * scaledPP;
  if(jobNumber==0){
    TFile * ppFile = TFile::Open("ppRef_Feb10_Pythia.root","read");
    scaledPP = (TH1D*)ppFile->Get("ppScaled_WithFit");
    scaledPP->SetDirectory(output);
    ppFile->Close();
  }
  output->cd();

  int nTrk;
  int hiBin;
  float hiHF;
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
    evt->SetBranchAddress("hiHF",&hiHF);
    evt->SetBranchAddress("vz",&vz);  

    skim->SetBranchAddress("pPAprimaryVertexFilter",&vtx);
    skim->SetBranchAddress("pBeamScrapingFilter",&beam);
    skim->SetBranchAddress("phfCoincFilter3",&hfCoinc);
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
      if(i%100==0) std::cout << i << "/" << trk->GetEntries() << std::endl;
      hlt->GetEntry(i);
      bool MinBias = false;
      for(int x = 0; x<21; x++) MinBias = MinBias || MB[x];
      if(!MinBias) continue;

      skim->GetEntry(i);
      evt->GetEntry(i);
      if(!vtx) noVtxCent_h->Fill(hiBin);
      if(!beam || !vtx || !hfCoinc) continue;

      float evtW = 1.0/evtSelEff->Eval(hiHF);

      vz_h->Fill(vz,evtW);
      if(TMath::Abs(vz)>15) continue;
      for(int c = 0; c<s.nCentBins; c++){
        if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;
        if(c<20) s.nVtx->Fill(c,evtW);
        nVtxMoreBin->Fill(c,evtW);
        s.nVtx_float[c] += evtW;
      }
      if(hiBin<0 || hiBin>199) continue;//protection
      hiBin_h->Fill(hiBin,evtW);
      hiBinNoWeight_h->Fill(hiBin,evtW);

      trk->GetEntry(i);
      //for tracking
      if(s.doTrackDists){
        for(int j = 0; j<nTrk; j++){
          if(!highPurity[j]) continue;     
          if(trkPt[j]<0.5) continue;
          float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
          int bin = trkBinMap(hiBin,trkPt[j]);
          
          eta[0][0]->Fill(trkEta[j],evtW);
          eta[trkBinMap(hiBin,trkPt[j])][0]->Fill(trkEta[j],evtW);
          if(TMath::Abs(trkEta[j])<=s.etaCut) fillTrkDists(phi[0][0],phi[bin][0],trkPhi[j],DCAz[0][0],DCAz[bin][0],trkDz1[j]/trkDzError1[j],DCAxy[0][0],DCAxy[bin][0],trkDxy1[j]/trkDxyError1[j],nHit[0][0],nHit[bin][0],trkNHit[j],chi2[0][0],chi2[bin][0],trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],ptErr[0][0],ptErr[bin][0],trkPtError[j]/trkPt[j],caloMatch[0][0],caloMatch[bin][0],Et/trkPt[j],evtW); 
          
          if(TMath::Abs(trkDz1[j]/trkDzError1[j])>3 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>3) continue;
          if(trkPtError[j]/trkPt[j]>0.1) continue;
          
          eta[0][1]->Fill(trkEta[j],evtW);
          eta[trkBinMap(hiBin,trkPt[j])][1]->Fill(trkEta[j],evtW);
          if(TMath::Abs(trkEta[j])<=s.etaCut) fillTrkDists(phi[0][1],phi[bin][1],trkPhi[j],DCAz[0][1],DCAz[bin][1],trkDz1[j]/trkDzError1[j],DCAxy[0][1],DCAxy[bin][1],trkDxy1[j]/trkDxyError1[j],nHit[0][1],nHit[bin][1],trkNHit[j],chi2[0][1],chi2[bin][1],trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],ptErr[0][1],ptErr[bin][1],trkPtError[j]/trkPt[j],caloMatch[0][1],caloMatch[bin][1],Et/trkPt[j],evtW); 

          if(trkNHit[j]<11) continue;
          if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;
          if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
          
          eta[0][2]->Fill(trkEta[j],evtW);
          eta[trkBinMap(hiBin,trkPt[j])][2]->Fill(trkEta[j],evtW);
          if(TMath::Abs(trkEta[j])>s.etaCut) continue;
          fillTrkDists(phi[0][2],phi[bin][2],trkPhi[j],DCAz[0][2],DCAz[bin][2],trkDz1[j]/trkDzError1[j],DCAxy[0][2],DCAxy[bin][2],trkDxy1[j]/trkDxyError1[j],nHit[0][2],nHit[bin][2],trkNHit[j],chi2[0][2],chi2[bin][2],trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],ptErr[0][2],ptErr[bin][2],trkPtError[j]/trkPt[j],caloMatch[0][2],caloMatch[bin][2],Et/trkPt[j],evtW); 
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
 
        float weight = trkCorr.getTrkCorr(trkPt[j],hiBin)*evtW;

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
      s.HI_TaaWeighted[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Taa)); 
      s.HI_TaaWeighted[c]->SetBinError(i,s.HI[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Taa));
      s.HI[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI[c]->SetBinError(i,s.HI[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
    }
    //RAA
    if(jobNumber==0){
      RAA[c] = (TH1D*) s.HI_TaaWeighted[c]->Clone(Form("RAA_SingleThreadDEBUGONLY_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
      RAA[c]->Scale(1.0/(float)s.nVtx_float[c]);
      RAA[c]->Divide(scaledPP);
    }
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

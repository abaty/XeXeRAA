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
#include "evtWeights/evtWeights.h"
#include "TMath.h"

int centBin(int b){
  if(b<10) return 0;
  else if(b<20) return 1;
  else if(b<60) return 2;
  else if(b<100) return 3;
  else if(b<140) return 4;
  else return 5;
}

void countTracks(std::vector<std::string> fileList, int jobNumber){
  Settings s = Settings();
  EventWeight evtW = EventWeight();

  TFile * output = TFile::Open(Form("output_%d.root",jobNumber),"recreate");
  TH1D * hiBin_h = new TH1D("hiBin","hiBin",200,0,200);
  TH1D * vz_h = new TH1D("vz","vz",120,-30,30);
  TH1D * hiBin_Weighted_h = new TH1D("hiBin_weight",";hiBin",200,0,200);
  TH1D * vz_Weighted_h = new TH1D("vz_weight",";vz",120,-30,30);
  TH1D * noVtxCent_h = new TH1D("noVtxCent_h","noVtxCent_h",200,0,200);

  TH1D *nHit[17][3][3], *chi2[17][3][3], *DCAz[17][3][3], *DCAxy[17][3][3], *ptErr[17][3][3], *eta[17][3][3], *phi[17][3][3], *caloMatch[17][3][3];


  for(int c = 0; c<17; c++){
    for(int c2 = 0; c2<3; c2++){
      for(int c3 = 0; c3<3; c3++){
        nHit[c][c2][c3] = new TH1D(Form("nHit%d_%d_cut%d",c,c2,c3),Form("nHit%d_%d_cut%d",c,c2,c3),30,0,30);
        chi2[c][c2][c3] = new TH1D(Form("chi2%d_%d_cut%d",c,c2,c3),Form("chi2%d_%d_cut%d",c,c2,c3),50,0,0.3);
        ptErr[c][c2][c3] = new TH1D(Form("ptErr%d_%d_cut%d",c,c2,c3),Form("ptErr%d_%d_cut%d",c,c2,c3),50,0,0.2);
        DCAz[c][c2][c3] = new TH1D(Form("DCAz%d_%d_cut%d",c,c2,c3),Form("DCAz%d_%d_cut%d",c,c2,c3),50,-5,5);
        DCAxy[c][c2][c3] = new TH1D(Form("DCAxy%d_%d_cut%d",c,c2,c3),Form("DCAxy%d_%d_cut%d",c,c2,c3),50,-5,5);
        eta[c][c2][c3] = new TH1D(Form("eta%d_%d_cut%d",c,c2,c3),Form("eta%d_%d_cut%d",c,c2,c3),50,-3,3);
        phi[c][c2][c3] = new TH1D(Form("phi%d_%d_cut%d",c,c2,c3),Form("phi%d_%d_cut%d",c,c2,c3),50,-TMath::Pi(),TMath::Pi());
        caloMatch[c][c2][c3] = new TH1D(Form("caloMatch%d_%d_cut%d",c,c2,c3),Form("caloMatch%d_%d_cut%d",c,c2,c3),50,0,2);
      }
    }
  }
  //resolution plots
  TH1D *reso_reco[s.ntrkBins], *reso_gen[s.ntrkBins], *reso_recoCut[s.ntrkBins], *reso_genCut[s.ntrkBins];
  TH1D * dummy = new TH1D("dummy","",s.ntrkBins,s.xtrkbins);
  for(int c = 0; c<s.ntrkBins; c++){
    reso_reco[c] = new TH1D(Form("reso_reco_%d",c),"",30,0.9,1.1);
    reso_gen[c] = new TH1D(Form("reso_gen_%d",c),"",30,0.9,1.1);
    reso_recoCut[c] = new TH1D(Form("reso_recoCut_%d",c),"",30,0.9,1.1);
    reso_genCut[c] = new TH1D(Form("reso_genCut_%d",c),"",30,0.9,1.1);
  }

  //eff and fake plots
  TH2D *gen2d, *reco2d, *recoNoFake2d, *recoMatched2d, *genMatched2d, *genMatchedMult2d;
  gen2d = new TH2D("gen2d","",s.ntrkBins,s.xtrkbins,6,0,6);
  reco2d = new TH2D("reco2d","",s.ntrkBins,s.xtrkbins,6,0,6);
  recoNoFake2d = new TH2D("recoNoFake2d","",s.ntrkBins,s.xtrkbins,6,0,6);
  recoMatched2d = new TH2D("recoMatched2d","",s.ntrkBins,s.xtrkbins,6,0,6);
  genMatched2d = new TH2D("genMatched2d","",s.ntrkBins,s.xtrkbins,6,0,6);
  genMatchedMult2d = new TH2D("genMatchedMult2d","",s.ntrkBins,s.xtrkbins,6,0,6);
  TH1D *gen[6], *reco[6], *recoNoFake[6], *recoMatched[6], *genMatched[6], *genMatchedMult[6];
  for(int c = 0; c<6; c++){
    gen[c] = new TH1D(Form("gen_%d",c),"",s.ntrkBins,s.xtrkbins); 
    reco[c] = new TH1D(Form("reco_%d",c),"",s.ntrkBins,s.xtrkbins);
    recoNoFake[c] = new TH1D(Form("recoNoFake_%d",c),"",s.ntrkBins,s.xtrkbins); 
    recoMatched[c] = new TH1D(Form("recoMatched_%d",c),"",s.ntrkBins,s.xtrkbins); 
    genMatched[c] = new TH1D(Form("genMatched_%d",c),"",s.ntrkBins,s.xtrkbins); 
    genMatchedMult[c] = new TH1D(Form("genMatchedMult_%d",c),"",s.ntrkBins,s.xtrkbins); 
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
  float trkStatus[50000];
  //gen
  int nParticle;
  float pPt[100000];
  float pEta[100000];
  float mtrkPt[100000];
  float mtrkPtError[100000];
  bool mhighPurity[100000];
  float mtrkChi2[100000];
  int mtrkNdof[100000];
  int mtrkNHit[100000];
  int mtrkNlayer[100000];
  float mtrkDz1[100000];
  float mtrkDzError1[100000];
  float mtrkDxy1[100000];
  float mtrkDxyError1[100000];
  float mtrkPfEcal[100000];
  float mtrkPfHcal[100000];
  int pNRec[100000];

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
    trk->SetBranchAddress("trkStatus",&trkStatus);
    trk->SetBranchAddress("pfEcal",pfEcal);
    trk->SetBranchAddress("pfHcal",pfHcal);

    trk->SetBranchAddress("nParticle",&nParticle);   
    trk->SetBranchAddress("pPt",pPt);   
    trk->SetBranchAddress("pEta",pEta);   
    trk->SetBranchAddress("mtrkPt",mtrkPt);
    trk->SetBranchAddress("mtrkPtError",mtrkPtError);
    trk->SetBranchAddress("mhighPurity",mhighPurity);
    trk->SetBranchAddress("mtrkChi2",mtrkChi2);
    trk->SetBranchAddress("mtrkNdof",mtrkNdof);
    trk->SetBranchAddress("mtrkNHit",mtrkNHit);
    trk->SetBranchAddress("mtrkNlayer",mtrkNlayer);
    trk->SetBranchAddress("mtrkDz1",mtrkDz1);
    trk->SetBranchAddress("mtrkDzError1",mtrkDzError1);
    trk->SetBranchAddress("mtrkDxy1",mtrkDxy1);
    trk->SetBranchAddress("mtrkDxyError1",mtrkDxyError1);
    trk->SetBranchAddress("mtrkPfEcal",mtrkPfEcal);
    trk->SetBranchAddress("mtrkPfHcal",mtrkPfHcal);
    trk->SetBranchAddress("pNRec",pNRec);
 
    for(int i = 0; i<trk->GetEntries(); i++){
      if(i%100==0) std::cout << i << "/" << trk->GetEntries() << std::endl;
      skim->GetEntry(i);
      evt->GetEntry(i);
      if(!vtx) noVtxCent_h->Fill(hiBin);
      if(!beam || !vtx || !hfCoinc) continue;
      vz_h->Fill(vz);
      if(TMath::Abs(vz)>15) continue;
      if(hiBin<0 || hiBin>199) continue;//protection
      hiBin_h->Fill(hiBin);

      float w = evtW.getEvtWeight(vz,hiBin);
      vz_Weighted_h->Fill(vz,w);
      hiBin_Weighted_h->Fill(hiBin,w);

      trk->GetEntry(i);
      //for tracking
      for(int j = 0; j<nTrk; j++){
        if(!highPurity[j]) continue;     
        if(trkPt[j]<0.5) continue;
        
        float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
        int statusIndex = 0;
        if(trkStatus[j]==1) statusIndex=1;
        else                statusIndex=2;       

        eta[0][0][0]->Fill(trkEta[j],w);
        eta[0][statusIndex][0]->Fill(trkEta[j],w);
        eta[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkEta[j],w);
        eta[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkEta[j],w);
        if(TMath::Abs(trkEta[j])<s.etaCut){
          phi[0][0][0]->Fill(trkPhi[j],w);
          phi[0][statusIndex][0]->Fill(trkPhi[j],w);
          phi[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkPhi[j],w);
          phi[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkPhi[j],w);
          DCAz[0][0][0]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAz[0][statusIndex][0]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAz[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAz[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAxy[0][0][0]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          DCAxy[0][statusIndex][0]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          DCAxy[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          DCAxy[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          nHit[0][0][0]->Fill(trkNHit[j],w);
          nHit[0][statusIndex][0]->Fill(trkNHit[j],w);
          nHit[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkNHit[j],w);
          nHit[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkNHit[j],w);
          chi2[0][0][0]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          chi2[0][statusIndex][0]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          chi2[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          chi2[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          ptErr[0][0][0]->Fill(trkPtError[j]/trkPt[j],w);
          ptErr[0][statusIndex][0]->Fill(trkPtError[j]/trkPt[j],w);
          ptErr[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(trkPtError[j]/trkPt[j],w);
          ptErr[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(trkPtError[j]/trkPt[j],w);
          caloMatch[0][0][0]->Fill(Et/trkPt[j],w);
          caloMatch[0][statusIndex][0]->Fill(Et/trkPt[j],w);
          caloMatch[trkBinMap(hiBin,trkPt[j])][0][0]->Fill(Et/trkPt[j],w);
          caloMatch[trkBinMap(hiBin,trkPt[j])][statusIndex][0]->Fill(Et/trkPt[j],w);
        }

        if(TMath::Abs(trkDz1[j]/trkDzError1[j])>3 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>3) continue;
        if(trkPtError[j]/trkPt[j]>0.1) continue;

        eta[0][0][1]->Fill(trkEta[j],w);
        eta[0][statusIndex][1]->Fill(trkEta[j],w);
        eta[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkEta[j],w);
        eta[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkEta[j],w);
        if(TMath::Abs(trkEta[j])<s.etaCut){
          phi[0][0][1]->Fill(trkPhi[j],w);
          phi[0][statusIndex][1]->Fill(trkPhi[j],w);
          phi[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkPhi[j],w);
          phi[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkPhi[j],w);
          DCAz[0][0][1]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAz[0][statusIndex][1]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAz[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAz[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkDz1[j]/trkDzError1[j],w);
          DCAxy[0][0][1]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          DCAxy[0][statusIndex][1]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          DCAxy[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          DCAxy[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkDxy1[j]/trkDxyError1[j],w);
          nHit[0][0][1]->Fill(trkNHit[j],w);
          nHit[0][statusIndex][1]->Fill(trkNHit[j],w);
          nHit[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkNHit[j],w);
          nHit[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkNHit[j],w);
          chi2[0][0][1]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          chi2[0][statusIndex][1]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          chi2[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          chi2[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
          ptErr[0][0][1]->Fill(trkPtError[j]/trkPt[j],w);
          ptErr[0][statusIndex][1]->Fill(trkPtError[j]/trkPt[j],w);
          ptErr[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(trkPtError[j]/trkPt[j],w);
          ptErr[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(trkPtError[j]/trkPt[j],w);
          caloMatch[0][0][1]->Fill(Et/trkPt[j],w);
          caloMatch[0][statusIndex][1]->Fill(Et/trkPt[j],w);
          caloMatch[trkBinMap(hiBin,trkPt[j])][0][1]->Fill(Et/trkPt[j],w);
          caloMatch[trkBinMap(hiBin,trkPt[j])][statusIndex][1]->Fill(Et/trkPt[j],w);
        }

        if(trkNHit[j]<11) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;
        if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
 
        eta[0][0][2]->Fill(trkEta[j],w);
        eta[0][statusIndex][2]->Fill(trkEta[j],w);
        eta[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkEta[j],w);
        eta[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkEta[j],w);
        if(TMath::Abs(trkEta[j])>s.etaCut) continue;
        
        phi[0][0][2]->Fill(trkPhi[j],w);
        phi[0][statusIndex][2]->Fill(trkPhi[j],w);
        phi[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkPhi[j],w);
        phi[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkPhi[j],w);
        DCAz[0][0][2]->Fill(trkDz1[j]/trkDzError1[j],w);
        DCAz[0][statusIndex][2]->Fill(trkDz1[j]/trkDzError1[j],w);
        DCAz[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkDz1[j]/trkDzError1[j],w);
        DCAz[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkDz1[j]/trkDzError1[j],w);
        DCAxy[0][0][2]->Fill(trkDxy1[j]/trkDxyError1[j],w);
        DCAxy[0][statusIndex][2]->Fill(trkDxy1[j]/trkDxyError1[j],w);
        DCAxy[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkDxy1[j]/trkDxyError1[j],w);
        DCAxy[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkDxy1[j]/trkDxyError1[j],w);
        nHit[0][0][2]->Fill(trkNHit[j],w);
        nHit[0][statusIndex][2]->Fill(trkNHit[j],w);
        nHit[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkNHit[j],w);
        nHit[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkNHit[j],w);
        chi2[0][0][2]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
        chi2[0][statusIndex][2]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
        chi2[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
        chi2[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],w);
        ptErr[0][0][2]->Fill(trkPtError[j]/trkPt[j],w);
        ptErr[0][statusIndex][2]->Fill(trkPtError[j]/trkPt[j],w);
        ptErr[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(trkPtError[j]/trkPt[j],w);
        ptErr[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(trkPtError[j]/trkPt[j],w);
        caloMatch[0][0][2]->Fill(Et/trkPt[j],w);
        caloMatch[0][statusIndex][2]->Fill(Et/trkPt[j],w);
        caloMatch[trkBinMap(hiBin,trkPt[j])][0][2]->Fill(Et/trkPt[j],w);
        caloMatch[trkBinMap(hiBin,trkPt[j])][statusIndex][2]->Fill(Et/trkPt[j],w);

        reco2d->Fill(trkPt[j],centBin(hiBin),w);
        reco[centBin(hiBin)]->Fill(trkPt[j],w);
        if(trkStatus[j]!=-999){
          recoNoFake2d->Fill(trkPt[j],centBin(hiBin),w);
          recoNoFake[centBin(hiBin)]->Fill(trkPt[j],w);
        }
        if(trkStatus[j]==1){
          recoMatched2d->Fill(trkPt[j],centBin(hiBin),w);
          recoMatched[centBin(hiBin)]->Fill(trkPt[j],w);
        }
      }//end of reco tracking stuff

      //gen particle loop
      for(int j = 0; j<nParticle; j++){
        if(TMath::Abs(pEta[j])>s.etaCut) continue;
        gen2d->Fill(pPt[j],centBin(hiBin),w);
        gen[centBin(hiBin)]->Fill(pPt[j],w);
        
        if(mtrkPt[j]<=0) continue;//only matched gen particles
        if(!mhighPurity[j]) continue;
        if(pPt[j]>0.5) reso_gen[dummy->FindBin(pPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);
        if(mtrkPt[j]>0.5) reso_reco[dummy->FindBin(mtrkPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);
        
        if(TMath::Abs(mtrkDz1[j]/mtrkDzError1[j])>3 || TMath::Abs(mtrkDxy1[j]/mtrkDxyError1[j])>3) continue;
        if(mtrkPtError[j]/mtrkPt[j]>0.1) continue;
        if(mtrkNHit[j]<11) continue;
        if(mtrkChi2[j]/(float)mtrkNdof[j]/(float)mtrkNlayer[j]>0.15) continue;
        float Et = (mtrkPfHcal[j]+mtrkPfEcal[j])/TMath::CosH(pEta[j]);
        if(!(mtrkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*mtrkPt[j]))) continue; //Calo Matchin
  
        if(pPt[j]>0.5) reso_genCut[dummy->FindBin(pPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);
        if(mtrkPt[j]>0.5) reso_recoCut[dummy->FindBin(mtrkPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);

        genMatched2d->Fill(pPt[j],centBin(hiBin),w);
        genMatched[centBin(hiBin)]->Fill(pPt[j],w);
        if(pNRec[j]>1){
          genMatchedMult2d->Fill(pPt[j],centBin(hiBin),w);
          genMatchedMult[centBin(hiBin)]->Fill(pPt[j],w);
        }
      }//end of gen particle loop
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

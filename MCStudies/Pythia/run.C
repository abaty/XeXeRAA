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
#include "../Hydjet/evtWeights/evtWeights.h"
#include "TMath.h"
#include "TEfficiency.h"

bool isPrimary(float p){
  p = TMath::Abs(p);
  if(TMath::Abs(p-221)<0.1) return true;
  if(TMath::Abs(p-223)<0.1) return true;
  if(TMath::Abs(p-333)<0.1) return true;
  if(TMath::Abs(p-113)<0.1) return true;
  if(TMath::Abs(p-213)<0.1) return true;
  if(TMath::Abs(p-313)<0.1) return true;
  if(TMath::Abs(p-323)<0.1) return true;
  if(TMath::Abs(p-331)<0.1) return true;
  return false;
}

int centBin(int b){
  if(b<10) return 0;
  else if(b<20) return 1;
  else if(b<60) return 2;
  else if(b<100) return 3;
  else if(b<140) return 4;
  else return 5;
}

void countTracks(std::vector<std::string> fileList, int jobNumber){
  float qScaleCutoff = 0.4;
  float qScaleGap = 30;

  Settings s = Settings();
  EventWeight evtW = EventWeight();

  TFile * output = TFile::Open(Form("output_Pythia_%d.root",jobNumber),"recreate");
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
    reso_reco[c] = new TH1D(Form("reso_reco_%d",c),"",51,0.9,1.1);
    reso_gen[c] = new TH1D(Form("reso_gen_%d",c),"",51,0.9,1.1);
    reso_recoCut[c] = new TH1D(Form("reso_recoCut_%d",c),"",51,0.9,1.1);
    reso_genCut[c] = new TH1D(Form("reso_genCut_%d",c),"",51,0.9,1.1);
  }

  //eff and fake plots

  TH2D *gen2d[4], *reco2d[4], *recoNoFake2d[4], *recoNoFake2d_sig[4], *recoMatched2d[4], *genMatched2d[4], *genMatchedMult2d[4];
  for(int cut = 3; cut>=0; cut--){
    gen2d[cut] = new TH2D(Form("gen2d_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
    reco2d[cut] = new TH2D(Form("reco2d_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
    recoNoFake2d[cut] = new TH2D(Form("recoNoFake2d_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
    recoNoFake2d_sig[cut] = new TH2D(Form("recoNoFake2d_sig_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
    recoMatched2d[cut] = new TH2D(Form("recoMatched2d_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
    genMatched2d[cut] = new TH2D(Form("genMatched2d_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
    genMatchedMult2d[cut] = new TH2D(Form("genMatchedMult2d_%d",cut),"",s.ntrkBins_extra,s.xtrkbins_extra,6,0,6);
  }
  TH1D *gen[6][4], *reco[6][4], *recoNoFake[6][4], *recoNoFake_sig[6][4], *recoMatched[6][4], *genMatched[6][4], *genMatchedMult[6][4];
  for(int cut = 3; cut>=0; cut--){
    for(int c = 0; c<6; c++){
      gen[c][cut] = new TH1D(Form("gen_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra); 
      reco[c][cut] = new TH1D(Form("reco_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra);
      recoNoFake[c][cut] = new TH1D(Form("recoNoFake_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra); 
      recoNoFake_sig[c][cut] = new TH1D(Form("recoNoFake_sig_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra); 
      recoMatched[c][cut] = new TH1D(Form("recoMatched_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra); 
      genMatched[c][cut] = new TH1D(Form("genMatched_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra); 
      genMatchedMult[c][cut] = new TH1D(Form("genMatchedMult_%d_%d",c,cut),"",s.ntrkBins_extra,s.xtrkbins_extra); 
    }
  }
  TH2D * qScaleVsPt[6];
  for(int c = 0; c<6; c++){
    qScaleVsPt[c] = new TH2D(Form("qScaleVsPt_%d",c),"",s.ntrkBins_extra,s.xtrkbins_extra,30,0,1.5);
  }

  int nTrk;
  int hiBin;
  float vz;
  int vtx;
  int beam;
  float weight;
  float pthat;
  int hfCoinc;
  float trkPt[50000];
  float trkMPId[50000];
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
  int pStatus[100000];
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
  int trkEventId[100000];
  int pNRec[100000];

  for(unsigned int f = 0; f<fileList.size(); f++){
  //for(unsigned int f = 0; f<10; f++){
    std::cout << "File: " << f << std::endl;
    std::cout << f << " " << fileList.size() << std::endl;
    TFile * input = TFile::Open(fileList.at(f).c_str(),"read");
    TTree * skim = (TTree*)input->Get("skimanalysis/HltTree");
    TTree * evt = (TTree*)input->Get("hiEvtAnalyzer/HiTree");
    TTree * trk = (TTree*)input->Get("ppTrack/trackTree");

    evt->SetBranchAddress("hiBin",&hiBin);
    evt->SetBranchAddress("vz",&vz);  
    evt->SetBranchAddress("weight",&weight);  
    evt->SetBranchAddress("pthat",&pthat);  

    skim->SetBranchAddress("pPAprimaryVertexFilter",&vtx);
    skim->SetBranchAddress("pBeamScrapingFilter",&beam);
    skim->SetBranchAddress("phfCoincFilter3",&hfCoinc);
    trk->SetBranchAddress("nTrk",&nTrk);
    trk->SetBranchAddress("trkPt",trkPt);
    trk->SetBranchAddress("trkPhi",trkPhi);
    trk->SetBranchAddress("trkMPId",trkMPId);
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
    trk->SetBranchAddress("trkEventId",trkEventId);

    trk->SetBranchAddress("nParticle",&nParticle);   
    trk->SetBranchAddress("pPt",pPt);   
    trk->SetBranchAddress("pEta",pEta);   
    trk->SetBranchAddress("pStatus",pStatus);
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
      vz_h->Fill(vz,weight);
      if(TMath::Abs(vz)>15) continue;
      if(hiBin<0 || hiBin>199) continue;//protection
      hiBin_h->Fill(hiBin,weight);

      float w = evtW.getEvtWeight(vz,hiBin);
      //there are basically no events iwth hiBin>186, so remove them to avoid huge weights
      //if(hiBin>180) continue;
      if(hiBin>=160) continue;//don't analyze 80-100%

      w=w*weight;
      vz_Weighted_h->Fill(vz,w);
      hiBin_Weighted_h->Fill(hiBin,w);

      trk->GetEntry(i);
      //for tracking
      for(int j = 0; j<nTrk; j++){
        if(!highPurity[j]) continue;     
        if(trkPt[j]<0.5) continue;
       
        //cut to keep weights reasonable
        if(trkPt[j]>qScaleCutoff*pthat && pthat-pPt[j]<qScaleGap) continue;
 
        float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
        int statusIndex = 0;
        if(trkStatus[j]==1 || trkEventId[j]==1) statusIndex=1;
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

        if(trkPtError[j]/trkPt[j]<0.015){
          if((trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))){ //Calo Matchin
            reco2d[1]->Fill(trkPt[j],centBin(hiBin),w);
            reco[centBin(hiBin)][1]->Fill(trkPt[j],w);
            if(trkStatus[j]!=-999){
              recoNoFake2d[1]->Fill(trkPt[j],centBin(hiBin),w);
              recoNoFake[centBin(hiBin)][1]->Fill(trkPt[j],w);
              if(trkEventId[j]==0){
                recoNoFake2d_sig[1]->Fill(trkPt[j],centBin(hiBin),w);
                recoNoFake_sig[centBin(hiBin)][1]->Fill(trkPt[j],w);
              }
            }
            if(((trkStatus[j]==-99 && isPrimary(trkMPId[j])) || trkStatus[j]==1) && trkEventId[j]==0){
              recoMatched2d[1]->Fill(trkPt[j],centBin(hiBin),w);
              recoMatched[centBin(hiBin)][1]->Fill(trkPt[j],w);
            }
          }
        }
        
        if(!(trkPt[j]<s.caloMatchStart || (Et>(s.caloMatchValue-0.1)*trkPt[j]))) continue; //Calo Matchin
        if(trkNHit[j]<10) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.18) continue;
          
        reco2d[3]->Fill(trkPt[j],centBin(hiBin),w);
        reco[centBin(hiBin)][3]->Fill(trkPt[j],w);
        if(trkStatus[j]!=-999){
          recoNoFake2d[3]->Fill(trkPt[j],centBin(hiBin),w);
          recoNoFake[centBin(hiBin)][3]->Fill(trkPt[j],w);
          if(trkEventId[j]==0){
            recoNoFake2d_sig[3]->Fill(trkPt[j],centBin(hiBin),w);
            recoNoFake_sig[centBin(hiBin)][3]->Fill(trkPt[j],w);
          }
        }
        if(((trkStatus[j]==-99 && isPrimary(trkMPId[j])) || trkStatus[j]==1) && trkEventId[j]==0){
          recoMatched2d[3]->Fill(trkPt[j],centBin(hiBin),w);
          recoMatched[centBin(hiBin)][3]->Fill(trkPt[j],w);
        }

        if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
        if(trkNHit[j]<11) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;
 
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

        reco2d[0]->Fill(trkPt[j],centBin(hiBin),w);
        reco[centBin(hiBin)][0]->Fill(trkPt[j],w);
        if(trkStatus[j]!=-999){
          recoNoFake2d[0]->Fill(trkPt[j],centBin(hiBin),w);
          recoNoFake[centBin(hiBin)][0]->Fill(trkPt[j],w);
          if(trkEventId[j]==0){
            recoNoFake2d_sig[0]->Fill(trkPt[j],centBin(hiBin),w);
            recoNoFake_sig[centBin(hiBin)][0]->Fill(trkPt[j],w);
          }
        }
        if(((trkStatus[j]==-99 && isPrimary(trkMPId[j])) || trkStatus[j]==1) && trkEventId[j]==0){
          recoMatched2d[0]->Fill(trkPt[j],centBin(hiBin),w);
          recoMatched[centBin(hiBin)][0]->Fill(trkPt[j],w);
        }
        

        if(!(trkPt[j]<s.caloMatchStart || (Et>(s.caloMatchValue+0.1)*trkPt[j]))) continue; //Calo Matchin
        if(TMath::Abs(trkDz1[j]/trkDzError1[j])>2 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>2) continue;
        if(trkPtError[j]/trkPt[j]>0.05) continue;
        if(trkNHit[j]<12) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.12) continue;
        
        reco2d[2]->Fill(trkPt[j],centBin(hiBin),w);
        reco[centBin(hiBin)][2]->Fill(trkPt[j],w);
        if(trkStatus[j]!=-999){
          recoNoFake2d[2]->Fill(trkPt[j],centBin(hiBin),w);
          recoNoFake[centBin(hiBin)][2]->Fill(trkPt[j],w);
          if(trkEventId[j]==0){
            recoNoFake2d_sig[2]->Fill(trkPt[j],centBin(hiBin),w);
            recoNoFake_sig[centBin(hiBin)][2]->Fill(trkPt[j],w);
          }
        }
        if(((trkStatus[j]==-99 && isPrimary(trkMPId[j])) || trkStatus[j]==1) && trkEventId[j]==0){
          recoMatched2d[2]->Fill(trkPt[j],centBin(hiBin),w);
          recoMatched[centBin(hiBin)][2]->Fill(trkPt[j],w);
        }
      }//end of reco tracking stuff


      //gen particle loop
      for(int j = 0; j<nParticle; j++){
        if(TMath::Abs(pEta[j])>s.etaCut) continue;

        //cut to keep weights reasonable
        if(pPt[j]>qScaleCutoff*pthat && pthat-pPt[j]<qScaleGap) continue;
        if(pStatus[j]>1) continue;

        gen2d[0]->Fill(pPt[j],centBin(hiBin),w);
        gen[centBin(hiBin)][0]->Fill(pPt[j],w);
        gen2d[1]->Fill(pPt[j],centBin(hiBin),w);
        gen[centBin(hiBin)][1]->Fill(pPt[j],w);
        gen2d[2]->Fill(pPt[j],centBin(hiBin),w);
        gen[centBin(hiBin)][2]->Fill(pPt[j],w);
        gen2d[3]->Fill(pPt[j],centBin(hiBin),w);
        gen[centBin(hiBin)][3]->Fill(pPt[j],w);
        qScaleVsPt[centBin(hiBin)]->Fill(pPt[j],pPt[j]/pthat,w);    
    
        if(mtrkPt[j]<=0) continue;//only matched gen particles
        if(!mhighPurity[j]) continue;
        if(pPt[j]>0.5) reso_gen[dummy->FindBin(pPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);
        if(mtrkPt[j]>0.5) reso_reco[dummy->FindBin(mtrkPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);
        
        if(TMath::Abs(mtrkDz1[j]/mtrkDzError1[j])>3 || TMath::Abs(mtrkDxy1[j]/mtrkDxyError1[j])>3) continue;
        if(mtrkPtError[j]/mtrkPt[j]>0.1) continue;

        float Et = (mtrkPfHcal[j]+mtrkPfEcal[j])/TMath::CosH(pEta[j]);
        if(mtrkPtError[j]/mtrkPt[j]<0.015){
          if((mtrkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*mtrkPt[j]))){ //Calo Matchin
            genMatched2d[1]->Fill(pPt[j],centBin(hiBin),w);
            genMatched[centBin(hiBin)][1]->Fill(pPt[j],w);
            if(pNRec[j]>1){
              genMatchedMult2d[1]->Fill(pPt[j],centBin(hiBin),w);
              genMatchedMult[centBin(hiBin)][1]->Fill(pPt[j],w);
            }
          }
        }
        
        if(!(mtrkPt[j]<s.caloMatchStart || (Et>(s.caloMatchValue-0.1)*mtrkPt[j]))) continue; //Calo Matchin
        if(mtrkNHit[j]<10) continue;  
        if(mtrkChi2[j]/(float)mtrkNdof[j]/(float)mtrkNlayer[j]>0.18) continue;
        
        genMatched2d[3]->Fill(pPt[j],centBin(hiBin),w);
        genMatched[centBin(hiBin)][3]->Fill(pPt[j],w);
        if(pNRec[j]>1){
          genMatchedMult2d[3]->Fill(pPt[j],centBin(hiBin),w);
          genMatchedMult[centBin(hiBin)][3]->Fill(pPt[j],w);
        }

        if(!(mtrkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*mtrkPt[j]))) continue; //Calo Matchin
        if(mtrkNHit[j]<11) continue;
        if(mtrkChi2[j]/(float)mtrkNdof[j]/(float)mtrkNlayer[j]>0.15) continue;
  
        if(pPt[j]>0.5) reso_genCut[dummy->FindBin(pPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);
        if(mtrkPt[j]>0.5) reso_recoCut[dummy->FindBin(mtrkPt[j])-1]->Fill(mtrkPt[j]/pPt[j],w);

        genMatched2d[0]->Fill(pPt[j],centBin(hiBin),w);
        genMatched[centBin(hiBin)][0]->Fill(pPt[j],w);
        if(pNRec[j]>1){
          genMatchedMult2d[0]->Fill(pPt[j],centBin(hiBin),w);
          genMatchedMult[centBin(hiBin)][0]->Fill(pPt[j],w);
        }
        
        if(!(mtrkPt[j]<s.caloMatchStart || (Et>(s.caloMatchValue+0.1)*mtrkPt[j]))) continue; //Calo Matchin
        if(TMath::Abs(mtrkDz1[j]/mtrkDzError1[j])>2 || TMath::Abs(mtrkDxy1[j]/mtrkDxyError1[j])>2) continue;
        if(mtrkPtError[j]/mtrkPt[j]>0.05) continue;
        if(mtrkNHit[j]<12) continue;
        if(mtrkChi2[j]/(float)mtrkNdof[j]/(float)mtrkNlayer[j]>0.12) continue;
        
        genMatched2d[2]->Fill(pPt[j],centBin(hiBin),w);
        genMatched[centBin(hiBin)][2]->Fill(pPt[j],w);
        if(pNRec[j]>1){
          genMatchedMult2d[2]->Fill(pPt[j],centBin(hiBin),w);
          genMatchedMult[centBin(hiBin)][2]->Fill(pPt[j],w);
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

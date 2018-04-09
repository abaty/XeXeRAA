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
#include "include/trackingResolution.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//FIXME preliminary
double findTaaAverage(int L, int H) {
  //v2
  if(L==0    && H==200 ) return         2.88;
  if(L==0    && H==5*2 ) return 	13.5;	
  if(L==5*2  && H==10*2) return 	10.6;	
  if(L==10*2 && H==15*2) return 	8.24;	
  if(L==15*2 && H==20*2) return 	6.41;	
  if(L==20*2 && H==25*2) return 	4.93;	
  if(L==25*2 && H==30*2) return 	3.77;	
  if(L==30*2 && H==35*2) return 	2.85;	
  if(L==35*2 && H==40*2) return 	2.13;	
  if(L==40*2 && H==45*2) return 	1.57;	
  if(L==45*2 && H==50*2) return 	1.14;	
  if(L==50*2 && H==55*2) return 	0.807;	
  if(L==55*2 && H==60*2) return 	0.561;	
  if(L==60*2 && H==65*2) return 	0.386;	
  if(L==65*2 && H==70*2) return 	0.258;	
  if(L==70*2 && H==75*2) return 	0.17;	
  if(L==75*2 && H==80*2) return 	0.11;	
  if(L==80*2 && H==85*2) return 	0.0726;	
  if(L==85*2 && H==90*2) return 	0.0476;	
  if(L==90*2 && H==95*2) return 	0.0258;	
  if(L==95*2 && H==100*2) return 	0.0235;	
  if(L==0*2  && H==10*2) return 	12;	
  if(L==10*2 && H==20*2) return 	7.33;	
  if(L==20*2 && H==30*2) return 	4.35;	
  if(L==30*2 && H==40*2) return 	2.49;	
  if(L==40*2 && H==50*2) return 	1.36;	
  if(L==50*2 && H==60*2) return 	0.684;	
  if(L==60*2 && H==70*2) return 	0.322;	
  if(L==70*2 && H==80*2) return 	0.14;	
  if(L==80*2 && H==90*2) return 	0.0601;	
  if(L==90*2 && H==100*2) return 	0.0247;	
  if(L==0*2  && H==20*2) return 	9.68;	
  if(L==20*2 && H==40*2) return 	3.42;	
  if(L==40*2 && H==60*2) return 	1.02;	
  if(L==60*2 && H==80*2) return 	0.231;	
  if(L==80*2 && H==100*2) return 	0.0424;	
  if(L==0*2  && H==50*2) return 	5.51;	
  if(L==50*2 && H==100*2) return 	0.246;	
  if(L==0*2  && H==30*2) return 	7.9;	
  if(L==30*2 && H==50*2) return 	1.92;	
  if(L==50*2 && H==70*2) return 	0.503;	
  if(L==70*2 && H==90*2) return 	0.1;	
  if(L==70*2 && H==100*2) return 	0.0749;	
  if(L==10*2 && H==30*2) return 	5.84;	
  if(L==30*2 && H==100*2) return 	0.726;	
  if(L==50*2 && H==80*2) return 	0.382;	
  if(L==40*2 && H==100*2) return 	0.431;	
  if(L==50*2 && H==90*2) return 	0.301;	
  if(L==50*2 && H==80*2) return 	0.382;	

  return 1.0;
}
double findNcollAverage(int L, int H) {
  //v2
  if(L==0    && H==200 ) return         197;
  if(L==0    && H==5*2 ) return 	935.9;	
  if(L==5*2  && H==10*2) return 	727.7;	
  if(L==0*2  && H==10*2) return 	831.8;	
  if(L==30*2 && H==50*2) return 	128.3;	
  if(L==50*2 && H==70*2) return 	33.06;	
  if(L==70*2 && H==90*2) return 	7.328;	
  if(L==10*2 && H==30*2) return 	399.3;	
  return 1.0;
}

void countTracks(std::vector<std::string> fileList, int jobNumber){
  Settings s = Settings();
  TrackingResolution trkReso = TrackingResolution(s.trkResFile);
  TrackingCorrection trkCorr = TrackingCorrection(s.trkCorrFile,true,true,false);
  TrackingCorrection trkCorr_NoSpec = TrackingCorrection(s.trkCorrFile_noSpec,true,false,false);
  TrackingCorrection trkCorr_NoSpecCut1 = TrackingCorrection(s.trkCorrFile_noSpecCut1,false,false,false,false);
  TrackingCorrection trkCorr_NoSpecCut2 = TrackingCorrection(s.trkCorrFile_noSpecCut2,true,false,false,true);
  TrackingCorrection trkCorr_NoSpecCut3 = TrackingCorrection(s.trkCorrFile_noSpecCut3,true,false,false,true);
  TF1 * evtSelEff = new TF1("evtSelEff","0.5*(1+TMath::Erf((x-13.439)/(TMath::Sqrt(x)*0.811)))",0,100000);


  TFile * output = TFile::Open(Form("output_data_%d.root",jobNumber),"recreate");
  TH1D * evtCount = new TH1D("evtCount","evtCount",10,0,10);
  TH1D * evtCount_weight = new TH1D("evtCount_weight","evtCount_weight",10,0,10);

  TH1D * hiBin_h = new TH1D("hiBin","hiBin",200,0,200);
  TH1D * hiHF_h = new TH1D("hiHF_h","hiHF_h",3500,0,7000);
  TH1D * hiBinNoWeight_h = new TH1D("hiBinNoWeight","hiBinNoWeight",200,0,200);
  TH1D * noVtxCent_h = new TH1D("noVtxCent_h","noVtxCent_h",200,0,200);
  TH1D * vz_h = new TH1D("vz","vz",120,-30,30);
  TH1D * nVtxMoreBin = new TH1D("nVtxMoreBin","nVtxMoreBin",50,0,50);
  TH1D *nHit[17][4], *chi2[17][4], *DCAz[17][4], *DCAxy[17][4], *ptErr[17][4], *eta[17][4], *phi[17][4], *caloMatch[17][4];
  TH1D * eta_hist[20];
  TH1D * dz_expanded[s.ntrkBins][8], * d0_expanded[s.ntrkBins][8];
  if(s.doTrackDists){
    for(int c = 0; c<17; c++){
      for(int c2 = 0; c2<4; c2++){
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
    for(int c = 0; c<s.ntrkBins; c++){
      if(c<20) eta_hist[c] = new TH1D(Form("eta_hist_%d",c),Form("eta_hist_%d",c),50,-1,1);
      for(int i = 0; i<8; i++){
        dz_expanded[c][i] = new TH1D(Form("dz_expanded_%d_%d",i,c),";#delta z",150,-30,30);
        d0_expanded[c][i] = new TH1D(Form("d0_expanded_%d_%d",i,c),";#delta z",150,-30,30);
      }
    }
  }

  s.nVtx = new TH1D("nVtx","nVtx",20,0,20);
  for(int c = 0; c<s.nCentBins; c++){
    s.HI_UpFakeCorr[c] = new TH1D(Form("HI_UpFakeCorr_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_UpSpecCorr[c] = new TH1D(Form("HI_UpSpecCorr_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_NoSpec[c] = new TH1D(Form("HI_NoSpec_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_NoSpecCut1[c] = new TH1D(Form("HI_NoSpecCut1_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_NoSpecCut2[c] = new TH1D(Form("HI_NoSpecCut2_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_NoSpecCut3[c] = new TH1D(Form("HI_NoSpecCut3_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_NoSpec_EffUp1Sig[c] = new TH1D(Form("HI_NoSpec_EffUp1Sig_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_NoSpec_EffUp1Sig_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_smeared[c] = new TH1D(Form("HIsmeared_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HIsmeared_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);

    s.HI[c] = new TH1D(Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);

    s.HI_TaaWeighted[c] = new TH1D(Form("HI_TaaWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_TaaWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
    s.HI_NcollWeighted[c] = new TH1D(Form("HI_NcollWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),Form("HI_NcollWeighted_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]),s.ntrkBins,s.xtrkbins);
  }

  TH1D * scaledPP;
  if(jobNumber==0){
    TFile * ppFile = TFile::Open(s.ppRefFile.c_str(),"read");
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
      if(i%1000==0) std::cout << i << "/" << trk->GetEntries() << std::endl;
      hlt->GetEntry(i);
      skim->GetEntry(i);
      evt->GetEntry(i);
      bool MinBias = false;
      //float evtW = 1.0/evtSelEff->Eval(hiHF);//removed from analysis after moving to 0-80%
      float evtW = 1.0;
      if(hiHF>3300 && s.doRejectPU) continue;
      
      evtCount->Fill(1);
      evtCount_weight->Fill(1,evtW);

      for(int x = 0; x<21; x++) MinBias = MinBias || MB[x];
      if(!MinBias) continue;
      evtCount->Fill(2);
      evtCount_weight->Fill(2,evtW);

      if(!vtx) noVtxCent_h->Fill(hiBin);
      if(!beam) continue;
      evtCount->Fill(3);
      evtCount_weight->Fill(3,evtW);
      if(!vtx) continue;
      evtCount->Fill(4);
      evtCount_weight->Fill(4,evtW);
      if(!hfCoinc) continue;
      evtCount->Fill(5);
      evtCount_weight->Fill(5,evtW);


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
      hiBinNoWeight_h->Fill(hiBin);
      hiHF_h->Fill(hiHF,evtW);

      trk->GetEntry(i);
      //for tracking
      if(s.doTrackDists){
        for(int j = 0; j<nTrk; j++){
          if(!highPurity[j]) continue;     
          if(trkPt[j]<0.5) continue;
          if(trkPt[j]>=103.6) continue;
          float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
          int bin = trkBinMap(hiBin,trkPt[j]);
        
          //extended dca histograms
          if(TMath::Abs(trkEta[j])<=s.etaCut && trkPtError[j]/trkPt[j]<0.1 && trkNHit[j]>=11 && trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]<=0.15 && (trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))){
            int centBin = 0;
            if(hiBin>=10 && hiBin<20) centBin=1;
            if(hiBin>=20 && hiBin<60) centBin=2;
            if(hiBin>=60 && hiBin<100) centBin=3;
            if(hiBin>=100 && hiBin<140) centBin=4;
            if(hiBin>=140 && hiBin<200) centBin=5;
            if(TMath::Abs(trkDxy1[j]/trkDxyError1[j])<3){
              dz_expanded[s.HI[0]->FindBin(trkPt[j])-1][centBin]->Fill(trkDz1[j]/trkDzError1[j],evtW);
              if(centBin<2) dz_expanded[s.HI[0]->FindBin(trkPt[j])-1][6]->Fill(trkDz1[j]/trkDzError1[j],evtW);
              dz_expanded[s.HI[0]->FindBin(trkPt[j])-1][7]->Fill(trkDz1[j]/trkDzError1[j],evtW);
            }
            if(TMath::Abs(trkDz1[j]/trkDzError1[j])<3){
              d0_expanded[s.HI[0]->FindBin(trkPt[j])-1][centBin]->Fill(trkDxy1[j]/trkDxyError1[j],evtW);
              if(centBin<2) d0_expanded[s.HI[0]->FindBin(trkPt[j])-1][6]->Fill(trkDxy1[j]/trkDxyError1[j],evtW);
              d0_expanded[s.HI[0]->FindBin(trkPt[j])-1][7]->Fill(trkDxy1[j]/trkDxyError1[j],evtW);
            }
          }
  
          eta[0][0]->Fill(trkEta[j],evtW);
          eta[trkBinMap(hiBin,trkPt[j])][0]->Fill(trkEta[j],evtW);
          if(TMath::Abs(trkEta[j])<=s.etaCut) fillTrkDists(phi[0][0],phi[bin][0],trkPhi[j],DCAz[0][0],DCAz[bin][0],trkDz1[j]/trkDzError1[j],DCAxy[0][0],DCAxy[bin][0],trkDxy1[j]/trkDxyError1[j],nHit[0][0],nHit[bin][0],trkNHit[j],chi2[0][0],chi2[bin][0],trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],ptErr[0][0],ptErr[bin][0],trkPtError[j]/trkPt[j],caloMatch[0][0],caloMatch[bin][0],Et/trkPt[j],evtW); 
          
          if(TMath::Abs(trkDz1[j]/trkDzError1[j])>3 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>3) continue;
          if(trkPtError[j]/trkPt[j]>0.1) continue;
          
          eta[0][1]->Fill(trkEta[j],evtW);
          eta[trkBinMap(hiBin,trkPt[j])][1]->Fill(trkEta[j],evtW);
          if(TMath::Abs(trkEta[j])<=s.etaCut) fillTrkDists(phi[0][1],phi[bin][1],trkPhi[j],DCAz[0][1],DCAz[bin][1],trkDz1[j]/trkDzError1[j],DCAxy[0][1],DCAxy[bin][1],trkDxy1[j]/trkDxyError1[j],nHit[0][1],nHit[bin][1],trkNHit[j],chi2[0][1],chi2[bin][1],trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],ptErr[0][1],ptErr[bin][1],trkPtError[j]/trkPt[j],caloMatch[0][1],caloMatch[bin][1],Et/trkPt[j],evtW); 

          if(trkPtError[j]/trkPt[j]<0.015){
            eta[0][3]->Fill(trkEta[j],evtW);
            eta[trkBinMap(hiBin,trkPt[j])][3]->Fill(trkEta[j],evtW);
            if(TMath::Abs(trkEta[j])<=s.etaCut) fillTrkDists(phi[0][3],phi[bin][3],trkPhi[j],DCAz[0][3],DCAz[bin][3],trkDz1[j]/trkDzError1[j],DCAxy[0][3],DCAxy[bin][3],trkDxy1[j]/trkDxyError1[j],nHit[0][3],nHit[bin][3],trkNHit[j],chi2[0][3],chi2[bin][3],trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j],ptErr[0][3],ptErr[bin][3],trkPtError[j]/trkPt[j],caloMatch[0][3],caloMatch[bin][3],Et/trkPt[j],evtW); 
          }

          if(trkNHit[j]<11) continue;
          if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;
          if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
          
          eta[0][2]->Fill(trkEta[j],evtW);
          if(trkPt[j]>0.5 && trkPt[j]<0.6) eta_hist[hiBin/5]->Fill(trkEta[j],evtW);
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

        float Et = (pfHcal[j]+pfEcal[j])/TMath::CosH(trkEta[j]);
 
        //lighter cuts
        if(trkPtError[j]/trkPt[j]<0.015){
          if((trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))){ //Calo Matchin
          float weight_NoSpecCut1 = trkCorr_NoSpecCut1.getTrkCorr(trkPt[j],hiBin)*evtW;
            for(int c = 0; c<s.nCentBins; c++){
              if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;
              float binCenter = s.HI[0]->GetXaxis()->GetBinCenter(s.HI[0]->GetXaxis()->FindBin(trkPt[j]));
              s.HI_NoSpecCut1[c]->Fill(trkPt[j],weight_NoSpecCut1/binCenter);
            }
          }
        }

        if(!(trkPt[j]<s.caloMatchStart || (Et>(s.caloMatchValue-0.1)*trkPt[j]))) continue; //Calo Matchin
        if(trkNHit[j]<10) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.18) continue;
      
        float weight_NoSpecCut3 = trkCorr_NoSpecCut3.getTrkCorr(trkPt[j],hiBin)*evtW;
        for(int c = 0; c<s.nCentBins; c++){
          if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;
          float binCenter = s.HI[0]->GetXaxis()->GetBinCenter(s.HI[0]->GetXaxis()->FindBin(trkPt[j]));
          s.HI_NoSpecCut3[c]->Fill(trkPt[j],weight_NoSpecCut3/binCenter);
        }

        if(!(trkPt[j]<s.caloMatchStart || (Et>s.caloMatchValue*trkPt[j]))) continue; //Calo Matchin
        if(trkNHit[j]<11) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.15) continue;

        float weight = trkCorr.getTrkCorr(trkPt[j],hiBin)*evtW;
        float weight_NoSpec = trkCorr_NoSpec.getTrkCorr(trkPt[j],hiBin)*evtW;
        float weight_NoSpec_EffUp1Sig = trkCorr_NoSpec.getTrkCorr(trkPt[j],hiBin)*(1+trkCorr_NoSpec.getEffStatErr(trkPt[j],hiBin))*evtW;
        float smearPt = trkReso.getSmearing(trkPt[j]);
        float smearWeight = trkCorr.getTrkCorr(smearPt,hiBin)*evtW;

        for(int c = 0; c<s.nCentBins; c++){
          if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;

          float binCenter = s.HI[0]->GetXaxis()->GetBinCenter(s.HI[0]->GetXaxis()->FindBin(trkPt[j]));
          s.HI[c]->Fill(trkPt[j],weight/binCenter);
          s.HI_NoSpec[c]->Fill(trkPt[j],weight_NoSpec/binCenter);
          
          s.HI_UpSpecCorr[c]->Fill(trkPt[j],(1.0/(1+trkCorr.getSpecCorrSyst(trkPt[j],hiBin)))*weight/binCenter);
          s.HI_UpFakeCorr[c]->Fill(trkPt[j],(1.0/(1-trkCorr.getFakeCorr(trkPt[j],hiBin)))*weight/binCenter);
 
          s.HI_NoSpec_EffUp1Sig[c]->Fill(trkPt[j],weight_NoSpec_EffUp1Sig/binCenter);   
      
          s.HI_smeared[c]->Fill(smearPt,smearWeight/binCenter);
        }//cent bin loop

        if(!(trkPt[j]<s.caloMatchStart || (Et>(s.caloMatchValue+0.1)*trkPt[j]))) continue; //Calo Matchin
        if(TMath::Abs(trkDz1[j]/trkDzError1[j])>2 || TMath::Abs(trkDxy1[j]/trkDxyError1[j])>2) continue;
        if(trkPtError[j]/trkPt[j]>0.05) continue;
        if(trkNHit[j]<12) continue;
        if(trkChi2[j]/(float)trkNdof[j]/(float)trkNlayer[j]>0.12) continue;

        float weight_NoSpecCut2 = trkCorr_NoSpecCut2.getTrkCorr(trkPt[j],hiBin)*evtW;
        for(int c = 0; c<s.nCentBins; c++){
          if(hiBin/10<s.lowCentBin[c] || hiBin/10>=s.highCentBin[c]) continue;
          float binCenter = s.HI[0]->GetXaxis()->GetBinCenter(s.HI[0]->GetXaxis()->FindBin(trkPt[j]));
          s.HI_NoSpecCut2[c]->Fill(trkPt[j],weight_NoSpecCut2/binCenter);
        }

      }//trk loop
    }//event loop
    input->Close();
  }//file loop

  output->cd();
  TH1D * RAA[s.nCentBins];
  for(int c = 0; c<s.nCentBins; c++)
  {
    double Taa = findTaaAverage(s.lowCentBin[c]*10,s.highCentBin[c]*10);
    double Ncoll = findNcollAverage(s.lowCentBin[c]*10,s.highCentBin[c]*10);
    for(int i = 1; i<s.HI[c]->GetSize()+1; i++)
    { 
      s.HI_TaaWeighted[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Taa)); 
      s.HI_TaaWeighted[c]->SetBinError(i,s.HI[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Taa));

      s.HI_NcollWeighted[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Ncoll)); 
      s.HI_NcollWeighted[c]->SetBinError(i,s.HI[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])*Ncoll));

      s.HI[c]->SetBinContent(i,s.HI[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI[c]->SetBinError(i,s.HI[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));

      s.HI_NoSpec[c]->SetBinContent(i,s.HI_NoSpec[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_NoSpec[c]->SetBinError(i,s.HI_NoSpec[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));

      s.HI_NoSpecCut1[c]->SetBinContent(i,s.HI_NoSpecCut1[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_NoSpecCut1[c]->SetBinError(i,s.HI_NoSpecCut1[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
      
      s.HI_NoSpecCut2[c]->SetBinContent(i,s.HI_NoSpecCut2[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_NoSpecCut2[c]->SetBinError(i,s.HI_NoSpecCut2[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
      
      s.HI_NoSpecCut3[c]->SetBinContent(i,s.HI_NoSpecCut3[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_NoSpecCut3[c]->SetBinError(i,s.HI_NoSpecCut3[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
      
      s.HI_NoSpec_EffUp1Sig[c]->SetBinContent(i,s.HI_NoSpec_EffUp1Sig[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_NoSpec_EffUp1Sig[c]->SetBinError(i,s.HI_NoSpec_EffUp1Sig[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
      
      s.HI_UpSpecCorr[c]->SetBinContent(i,s.HI_UpSpecCorr[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_UpSpecCorr[c]->SetBinError(i,s.HI_UpSpecCorr[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
      
      s.HI_UpFakeCorr[c]->SetBinContent(i,s.HI_UpFakeCorr[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_UpFakeCorr[c]->SetBinError(i,s.HI_UpFakeCorr[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
      
      s.HI_smeared[c]->SetBinContent(i,s.HI_smeared[c]->GetBinContent(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1]))); 
      s.HI_smeared[c]->SetBinError(i,s.HI_smeared[c]->GetBinError(i)/(2*s.etaCut*2*TMath::Pi()*(s.xtrkbins[i]-s.xtrkbins[i-1])));
    }
    //RAA
    if(jobNumber==0){
      RAA[c] = (TH1D*) s.HI_TaaWeighted[c]->Clone(Form("RAA_SingleThreadDEBUGONLY_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
      RAA[c]->Scale(1.0/(float)s.nVtx_float[c]);
      RAA[c]->Divide(scaledPP);
    }
  }
  
  TH1D * jobsFinished = new TH1D("jobsFinished","jobsFinished",1,0,2);
  jobsFinished->Fill(1);
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

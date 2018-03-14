#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "TF1.h"

void makeTrkCorr(int cutsToUse = 0 ,bool isEmbedded = true){
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  //TFile * f = new TFile("../Hydjet/output_Feb26.root","read");
  //TFile * f = new TFile("../EPOS/output_0_Feb26.root","read");
  TFile * f = new TFile("../Pythia/output_0.root","read");

  
  TH2D *gen2d, *reco2d, *recoNoFake2d, *recoNoFake2d_sig, *recoMatched2d, *genMatched2d, *genMatchedMult2d;
  gen2d = (TH2D*)f->Get(Form("gen2d_%d",cutsToUse));
  reco2d = (TH2D*)f->Get(Form("reco2d_%d",cutsToUse));
  recoNoFake2d = (TH2D*)f->Get(Form("recoNoFake2d_%d",cutsToUse));
  if(isEmbedded) recoNoFake2d_sig = (TH2D*)f->Get(Form("recoNoFake2d_sig_%d",cutsToUse));
  else           recoNoFake2d_sig = (TH2D*)f->Get(Form("recoNoFake2d_%d",cutsToUse));
  recoMatched2d = (TH2D*)f->Get(Form("recoMatched2d_%d",cutsToUse));
  genMatched2d = (TH2D*)f->Get(Form("genMatched2d_%d",cutsToUse));
  genMatchedMult2d = (TH2D*)f->Get(Form("genMatchedMult2d_%d",cutsToUse));
  
  TH1D *gen[6], *reco[6], *recoNoFake[6], * recoNoFake_sig[6], *recoMatched[6], *genMatched[6], *genMatchedMult[6];
  for(int c = 0; c<6; c++){
    gen[c] = (TH1D*)f->Get(Form("gen_%d_%d",c,cutsToUse));
    reco[c] = (TH1D*)f->Get(Form("reco_%d_%d",c,cutsToUse));
    recoNoFake[c] = (TH1D*)f->Get(Form("recoNoFake_%d_%d",c,cutsToUse));
    if(isEmbedded) recoNoFake_sig[c] = (TH1D*)f->Get(Form("recoNoFake_sig_%d_%d",c,cutsToUse));
    else           recoNoFake_sig[c] = (TH1D*)f->Get(Form("recoNoFake_%d_%d",c,cutsToUse));
    recoMatched[c] = (TH1D*)f->Get(Form("recoMatched_%d_%d",c,cutsToUse));
    genMatched[c] = (TH1D*)f->Get(Form("genMatched_%d_%d",c,cutsToUse));
    genMatchedMult[c] = (TH1D*)f->Get(Form("genMatchedMult_%d_%d",c,cutsToUse));
  }

  //TFile * output = new TFile("trkCorr_Hydjet_Feb26.root","recreate");
 //TFile * output = new TFile("trkCorr_EPOS_Feb26.root","recreate");
 TFile * output = new TFile(Form("trkCorr_Pythia_March5_CutIndex%d.root",cutsToUse),"recreate");

  //efficiency
  TH2D * efficiency2d = (TH2D*)genMatched2d->Clone("efficiency2d");  
  efficiency2d->Divide(gen2d);  
  efficiency2d->Write();

  TH1D * efficiency[6];
  TGraphAsymmErrors * effGraph[6];
  for(int c = 0; c<6; c++){
    efficiency[c] = (TH1D*)genMatched[c]->Clone(Form("efficiency_%d",c));  
    efficiency[c]->Divide(gen[c]);  
    efficiency[c]->Write();
    effGraph[c] = new TGraphAsymmErrors();
    effGraph[c]->SetName(Form("effGraph_%d",c));
    effGraph[c]->BayesDivide(genMatched[c],gen[c]);
  }

  //fake rate
  TH2D * fake2d = (TH2D*)recoNoFake2d->Clone("fake2d");  
  fake2d->Divide(reco2d);  
  for(int i = 1; i<fake2d->GetXaxis()->GetNbins()+1; i++){
    for(int j = 1; j<fake2d->GetYaxis()->GetNbins()+1; j++){
      fake2d->SetBinContent(i,j,1-fake2d->GetBinContent(i,j));
    }
  }
  fake2d->Write();

  TH1D * fake[6];
  TGraphAsymmErrors * fakeGraph[6];
  for(int c = 0; c<6; c++){
    fake[c] = (TH1D*)recoNoFake[c]->Clone(Form("fake_%d",c));  
    fake[c]->Divide(reco[c]);  
    for(int i = 1; i<fake[c]->GetXaxis()->GetNbins()+1; i++){
      fake[c]->SetBinContent(i,1-fake[c]->GetBinContent(i));
    }
    fake[c]->Write();
    fakeGraph[c] = new TGraphAsymmErrors();
    fakeGraph[c]->SetName(Form("fakeGraph_%d",c));
    fakeGraph[c]->BayesDivide(recoNoFake[c],reco[c]);
  }

  //secondary
  TH2D * secondary2d = (TH2D*)recoMatched2d->Clone("secondary2d");  
  secondary2d->Divide(recoNoFake2d_sig);  
  for(int i = 1; i<secondary2d->GetXaxis()->GetNbins()+1; i++){
    for(int j = 1; j<secondary2d->GetYaxis()->GetNbins()+1; j++){
      secondary2d->SetBinContent(i,j,1-secondary2d->GetBinContent(i,j));
    }
  }
  secondary2d->Write();

  TH1D * secondary[6];
  TGraphAsymmErrors * secGraph[6];
  for(int c = 0; c<6; c++){
    secondary[c] = (TH1D*)recoMatched[c]->Clone(Form("secondary_%d",c));  
    secondary[c]->Divide(recoNoFake_sig[c]);  
    for(int i = 1; i<secondary[c]->GetXaxis()->GetNbins()+1; i++){
      secondary[c]->SetBinContent(i,1-secondary[c]->GetBinContent(i));
    }
    secondary[c]->Write();
    secGraph[c] = new TGraphAsymmErrors();
    secGraph[c]->SetName(Form("secGraph_%d",c));
    secGraph[c]->BayesDivide(recoMatched[c],recoNoFake_sig[c]);
  }
 
  //multiple reco 
  TH2D * multiple2d = (TH2D*)genMatchedMult2d->Clone("multiple2d");  
  multiple2d->Divide(gen2d);  
  for(int i = 1; i<multiple2d->GetXaxis()->GetNbins()+1; i++){
    for(int j = 1; j<multiple2d->GetYaxis()->GetNbins()+1; j++){
      multiple2d->SetBinContent(i,j,multiple2d->GetBinContent(i,j));
    }
  }
  multiple2d->Write();

  TH1D * multiple[6];
  for(int c = 0; c<6; c++){
    multiple[c] = (TH1D*)genMatchedMult[c]->Clone(Form("multiple_%d",c));  
    multiple[c]->Divide(gen[c]);  
    for(int i = 1; i<multiple[c]->GetXaxis()->GetNbins()+1; i++){
      multiple[c]->SetBinContent(i,multiple[c]->GetBinContent(i));
    }
    multiple[c]->Write();
  }

  TF1 * effFit[6], *fakeFit[6], *secFit[6];
  for(int c = 0; c<6; c++){
    std::cout << "Fitting iteration " << c << std::endl;
    effFit[c] = new TF1(Form("effFit_%d",c),"[0]+[1]*TMath::Log(x)+[2]*TMath::Power(TMath::Log(x),2)+[3]*TMath::Power(TMath::Log(x),3)+[4]*TMath::Power(TMath::Log(x),4)",1.0,180);
    effFit[c]->SetParameters(0.6,0.1,0,0,0);
    effGraph[c]->Fit(Form("effFit_%d",c),"0ERM");
 
    fakeFit[c] = new TF1(Form("fakeFit_%d",c),"[0]+[1]*TMath::Log(x)+[2]*TMath::Power(TMath::Log(x),2)",3.2,180);
    fakeFit[c]->SetParameters(1,0,0);
    fakeGraph[c]->Fit(Form("fakeFit_%d",c),"0ERM");
    
    secFit[c] = new TF1(Form("secFit_%d",c),"[0]",0.5,180);
    secFit[c]->SetParameter(0,1);
    secGraph[c]->Fit(Form("secFit_%d",c),"0ERM");
    
    effGraph[c]->Write();
    effFit[c]->Write();
    fakeGraph[c]->Write(); 
    fakeFit[c]->Write(); 
    secGraph[c]->Write();
    secFit[c]->Write();  
  }
 
  TH2D * efficiency2d_Smoothed = (TH2D*)efficiency2d->Clone("efficiency2d_Smoothed");
  TH2D * fake2d_Smoothed = (TH2D*)fake2d->Clone("fake2d_Smoothed");
  TH2D * secondary2d_Smoothed = (TH2D*)secondary2d->Clone("secondary2d_Smoothed");
  TH1D * efficiency_smooth[6], * fake_smooth[6], * secondary_smooth[6];
  for(int c = 0; c<6; c++){
    efficiency_smooth[c] = (TH1D*)efficiency[c]->Clone(Form("efficiency_smooth_%d",c));
    fake_smooth[c] = (TH1D*)fake[c]->Clone(Form("fake_smooth_%d",c));
    secondary_smooth[c] = (TH1D*)secondary[c]->Clone(Form("secondary_smooth_%d",c));
  }
  for(int i = 0; i<efficiency2d_Smoothed->GetXaxis()->GetNbins(); i++){
    for(int j = 0; j<6; j++){
      float pt = efficiency2d_Smoothed->GetXaxis()->GetBinCenter(i+1);
      secondary2d_Smoothed->SetBinContent(i+1,j+1,1-secFit[j]->Eval(pt));
      secondary_smooth[j]->SetBinContent(i+1,1-secFit[j]->Eval(pt));
      if(pt>1.0){
        efficiency2d_Smoothed->SetBinContent(i+1,j+1,effFit[j]->Eval(pt));
        efficiency_smooth[j]->SetBinContent(i+1,effFit[j]->Eval(pt));
      }  
      if(pt>3.2){
        fake2d_Smoothed->SetBinContent(i+1,j+1,1-fakeFit[j]->Eval(pt));
        fake_smooth[j]->SetBinContent(i+1,1-fakeFit[j]->Eval(pt));
      }
      secondary_smooth[j]->SetBinError(i+1,0);
      fake_smooth[j]->SetBinError(i+1,0);
      efficiency_smooth[j]->SetBinError(i+1,0);
    }
  }
  secondary2d_Smoothed->Write();
  efficiency2d_Smoothed->Write();
  fake2d_Smoothed->Write();
  for(int c = 0; c<6; c++){
    efficiency_smooth[c]->Write();
    fake_smooth[c]->Write();
    secondary_smooth[c]->Write();
  }
  f->Close();
  output->Close();
}

void makeSpeciesCorr(bool makeTotalCorrectionPlots = true){
  //primary correction
  TFile * f1 = TFile::Open("trkCorr_Pythia_March5_CutIndex0.root","read");
  //secondary correction
  TFile * f2 = TFile::Open("trkCorr_EPOS_Feb26.root","read");

  TFile * f3;
  if(makeTotalCorrectionPlots) f3 = TFile::Open("trkCorr_Hydjet_Feb26.root","read");

  TH2D * eff, *fake, *sec, *multiple;
  TH2D * eff2, *fake2, *eff3, *fake3;
  TH1D * eff1d;

  eff = (TH2D*)f1->Get("efficiency2d_Smoothed");
  eff2 = (TH2D*)f2->Get("efficiency2d");
  if(makeTotalCorrectionPlots) eff3 = (TH2D*)f3->Get("efficiency2d");
  fake = (TH2D*)f1->Get("fake2d_Smoothed");
  fake2 = (TH2D*)f2->Get("fake2d");
  if(makeTotalCorrectionPlots) fake3 = (TH2D*)f3->Get("fake2d");
  sec = (TH2D*)f1->Get("secondary2d_Smoothed");
  multiple = (TH2D*)f1->Get("multiple2d");
  
  eff1d = (TH1D*)f1->Get("efficiency_0");

  TFile * output = TFile::Open("trkCorr_March5_wSpeciesCorr.root","recreate");
  eff->SetDirectory(output);
  fake->SetDirectory(output);
  sec->SetDirectory(output);
  multiple->SetDirectory(output);
  eff->Write();
  fake->Write();
  sec->Write();
  multiple->Write();

  TH2D * speciesCorr = (TH2D*)eff->Clone("speciesCorr");
  TH2D * speciesCorrSyst = (TH2D*)eff->Clone("speciesCorrSyst");

  TH1D * speciesCorrSyst1D[6];
  for(int i = 0; i<6; i++){
    speciesCorrSyst1D[i] = (TH1D*)eff1d->Clone(Form("speciesCorrSyst1D_ForPlots_%d",i));
    speciesCorrSyst1D[i]->Reset();
  }

  for(int i = 1; i<speciesCorr->GetXaxis()->GetNbins()+1;i++){
    for(int j = 1; j<speciesCorr->GetYaxis()->GetNbins()+1;j++){
      float e1 = eff->GetBinContent(i,j);
      float e2 = eff2->GetBinContent(i,j);
      e1 = e1/(1-fake->GetBinContent(i,j));
      e2 = e2/(1-fake2->GetBinContent(i,j));
      speciesCorr->SetBinContent(i,j,1);
      speciesCorr->SetBinError(i,j,0);

      //default uncertainty
      speciesCorrSyst->SetBinContent(i,j,0.03);
      speciesCorrSyst->SetBinError(i,j,0);
      if(speciesCorr->GetXaxis()->GetBinCenter(i)>14) continue;
      //if(speciesCorr->GetXaxis()->GetBinCenter(i)<1) continue;
      speciesCorr->SetBinContent(i,j,2*e1/(e1+e2));    
      speciesCorr->SetBinError(i,j,TMath::Power(TMath::Power(2*eff2->GetBinContent(i,j)/TMath::Power((eff->GetBinContent(i,j)+eff2->GetBinContent(i,j)),2)*eff->GetBinError(i,j),2)+TMath::Power(2*eff->GetBinContent(i,j)/TMath::Power((eff->GetBinContent(i,j)+eff2->GetBinContent(i,j)),2)*eff2->GetBinError(i,j),2),0.5));    
      speciesCorrSyst->SetBinContent(i,j,speciesCorr->GetBinContent(i,j)-1);
      speciesCorrSyst->SetBinError(i,j,speciesCorr->GetBinError(i,j));
      
      speciesCorrSyst1D[j-1]->SetBinContent(i,speciesCorrSyst->GetBinContent(i,j));
      speciesCorrSyst1D[j-1]->SetBinError(i,speciesCorrSyst->GetBinError(i,j));
      
      //removing negative high-pt points
      //reset to default uncertainty here
      if(speciesCorr->GetXaxis()->GetBinCenter(i)>3 && speciesCorr->GetBinContent(i,j)<1){
        speciesCorr->SetBinContent(i,j,1);    
        speciesCorr->SetBinError(i,j,0);    
        speciesCorrSyst->SetBinContent(i,j,0.03);
        speciesCorrSyst->SetBinError(i,j,0);
      }
    }
  }
  speciesCorr->Write();
  speciesCorrSyst->Write();

  for(int i = 0; i<6; i++){
    speciesCorrSyst1D[i]->Write();
  }

  TH1D * totalCorrection[3][6];
  if(makeTotalCorrectionPlots){
    for(int c = 0; c<6; c++){
      totalCorrection[0][c] = (TH1D*)eff1d->Clone(Form("TotalCorrection_Pythia_%d",c));
      totalCorrection[0][c]->Reset();
      totalCorrection[1][c] = (TH1D*)eff1d->Clone(Form("TotalCorrection_EPOS_%d",c));
      totalCorrection[1][c]->Reset();
      totalCorrection[2][c] = (TH1D*)eff1d->Clone(Form("TotalCorrection_Hydjet_%d",c));
      totalCorrection[2][c]->Reset();
      for(int i = 1; i< eff1d->GetSize()-1; i++){
        if(eff1d->GetBinCenter(i)>20) continue;
        totalCorrection[0][c]->SetBinContent(i,(1-fake->GetBinContent(i,c+1))/eff->GetBinContent(i,c+1));
        float err2 = TMath::Power(eff->GetBinError(i,c+1)/eff->GetBinContent(i,c+1),2)+TMath::Power(fake->GetBinError(i,c+1)/(1-fake->GetBinContent(i,c+1)),2);
        totalCorrection[0][c]->SetBinError(i,TMath::Sqrt(err2));
        totalCorrection[1][c]->SetBinContent(i,(1-fake2->GetBinContent(i,c+1))/eff2->GetBinContent(i,c+1));
        err2 = TMath::Power(eff2->GetBinError(i,c+1)/eff2->GetBinContent(i,c+1),2)+TMath::Power(fake2->GetBinError(i,c+1)/(1-fake2->GetBinContent(i,c+1)),2);
        totalCorrection[1][c]->SetBinError(i,TMath::Sqrt(err2));
        totalCorrection[2][c]->SetBinContent(i,(1-fake3->GetBinContent(i,c+1))/eff3->GetBinContent(i,c+1));
        err2 = TMath::Power(eff3->GetBinError(i,c+1)/eff3->GetBinContent(i,c+1),2)+TMath::Power(fake3->GetBinError(i,c+1)/(1-fake3->GetBinContent(i,c+1)),2);
        totalCorrection[2][c]->SetBinError(i,TMath::Sqrt(err2));
      }
 
      gStyle->SetOptStat(0);
      gStyle->SetErrorX(0);
      TCanvas * c1 = new TCanvas("c1","",800,600);
      c1->SetLogx();
      totalCorrection[0][c]->GetXaxis()->SetTitle("p_{T}");
      totalCorrection[0][c]->GetXaxis()->SetRangeUser(0.5,20);
      totalCorrection[0][c]->GetYaxis()->SetTitle("Total Tracking Correction");
      totalCorrection[0][c]->GetYaxis()->SetRangeUser(1,6);
      totalCorrection[0][c]->SetLineColor(kRed);  
      totalCorrection[0][c]->SetMarkerColor(kRed);  
      totalCorrection[0][c]->SetMarkerStyle(28);  
      totalCorrection[1][c]->SetLineColor(kBlue);  
      totalCorrection[1][c]->SetMarkerColor(kBlue);  
      totalCorrection[1][c]->SetMarkerStyle(24);  
      totalCorrection[2][c]->SetLineColor(kBlack);  
      totalCorrection[2][c]->SetMarkerColor(kBlack);  
      totalCorrection[2][c]->SetMarkerStyle(8); 
      totalCorrection[0][c]->Draw("p"); 
      totalCorrection[1][c]->Draw("p same"); 
      totalCorrection[2][c]->Draw("p same"); 

      TLegend * l = new TLegend(0.3,0.4,0.7,0.7);
      l->SetBorderSize(0);
      l->AddEntry(totalCorrection[0][c],"Pythia 8 + Hydjet","p");
      l->AddEntry(totalCorrection[1][c],"MB EPOS","p");
      l->AddEntry(totalCorrection[2][c],"MB Hydjet","p");
      int a, b;
      if(c==0) a=0; b=5;
      if(c==1) a=5; b=10;
      if(c==2) a=10; b=30;
      if(c==3) a=30; b=50;
      if(c==4) a=50; b=70;
      if(c==5) a=70; b=100;
      l->AddEntry((TObject*)0,Form("%d-%d %%",a,b),"");
      l->Draw("same");

      c1->SaveAs(Form("img/TotalCorrection_%d.pdf",c));
      c1->SaveAs(Form("img/TotalCorrection_%d.png",c));
      c1->SaveAs(Form("img/TotalCorrection_%d.C",c));

      delete c1;
    }
  }
}

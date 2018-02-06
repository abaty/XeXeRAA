#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include <iostream>

void makeTrkCorr(){
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TFile * f = new TFile("../Hydjet/output_Feb6.root","read");

  
  TH2D *gen2d, *reco2d, *recoNoFake2d, *recoMatched2d, *genMatched2d, *genMatchedMult2d;
  gen2d = (TH2D*)f->Get("gen2d");
  reco2d = (TH2D*)f->Get("reco2d");
  recoNoFake2d = (TH2D*)f->Get("recoNoFake2d");
  recoMatched2d = (TH2D*)f->Get("recoMatched2d");
  genMatched2d = (TH2D*)f->Get("genMatched2d");
  genMatchedMult2d = (TH2D*)f->Get("genMatchedMult2d");
  
  TH1D *gen[6], *reco[6], *recoNoFake[6], *recoMatched[6], *genMatched[6], *genMatchedMult[6];
  for(int c = 0; c<6; c++){
    gen[c] = (TH1D*)f->Get(Form("gen_%d",c));
    reco[c] = (TH1D*)f->Get(Form("reco_%d",c));
    recoNoFake[c] = (TH1D*)f->Get(Form("recoNoFake_%d",c));
    recoMatched[c] = (TH1D*)f->Get(Form("recoMatched_%d",c));
    genMatched[c] = (TH1D*)f->Get(Form("genMatched_%d",c));
    genMatchedMult[c] = (TH1D*)f->Get(Form("genMatchedMult_%d",c));
  }

  TFile * output = new TFile("trkCorr_Hydjet_Feb6.root","recreate");

  //efficiency
  TH2D * efficiency2d = (TH2D*)genMatched2d->Clone("efficiency2d");  
  efficiency2d->Divide(gen2d);  
  efficiency2d->Write();

  TH1D * efficiency[6];
  for(int c = 0; c<6; c++){
    efficiency[c] = (TH1D*)genMatched[c]->Clone(Form("efficiency_%d",c));  
    efficiency[c]->Divide(gen[c]);  
    efficiency[c]->Write();
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
  for(int c = 0; c<6; c++){
    fake[c] = (TH1D*)recoNoFake[c]->Clone(Form("fake_%d",c));  
    fake[c]->Divide(reco[c]);  
    for(int i = 1; i<fake[c]->GetXaxis()->GetNbins()+1; i++){
      fake[c]->SetBinContent(i,1-fake[c]->GetBinContent(i));
    }
    fake[c]->Write();
  }

  //secondary
  TH2D * secondary2d = (TH2D*)recoMatched2d->Clone("secondary2d");  
  secondary2d->Divide(recoNoFake2d);  
  for(int i = 1; i<secondary2d->GetXaxis()->GetNbins()+1; i++){
    for(int j = 1; j<secondary2d->GetYaxis()->GetNbins()+1; j++){
      secondary2d->SetBinContent(i,j,1-secondary2d->GetBinContent(i,j));
    }
  }
  secondary2d->Write();

  TH1D * secondary[6];
  for(int c = 0; c<6; c++){
    secondary[c] = (TH1D*)recoMatched[c]->Clone(Form("secondary_%d",c));  
    secondary[c]->Divide(recoNoFake[c]);  
    for(int i = 1; i<secondary[c]->GetXaxis()->GetNbins()+1; i++){
      secondary[c]->SetBinContent(i,1-secondary[c]->GetBinContent(i));
    }
    secondary[c]->Write();
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
  


}

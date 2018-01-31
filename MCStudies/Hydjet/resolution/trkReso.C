#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "../../../Settings.h"
#include <string>
#include <iostream>
#include "TCanvas.h"

void fillResoPoint(TH1D * r, int bin, std::string name){
  TFile * f = TFile::Open("output_0.root","read");
  TH1D * h = (TH1D*)f->Get(Form("%s_%d",name.c_str(),bin));

  TF1 *f1 = new TF1("f1","gaus",-0.9,1.1);
  f1->SetParameter(0,h->GetEntries()/10.0);
  f1->SetParameter(1,1);
  f1->SetParameter(2,0.02);

  TCanvas * c = new TCanvas("c","c",400,400);
  h->Draw();
  h->Fit("f1","WLEMR");

  std::cout << f1->GetParameter(1) << " " << f1->GetParameter(2) << std::endl;
  std::cout << f1->GetParError(1) << " " << f1->GetParError(2) << std::endl;

  r->SetBinContent(bin+1,f1->GetParameter(2));
  r->SetBinError(bin+1,f1->GetParError(2));

  c->SaveAs(Form("fits/%s_%d.png",name.c_str(),bin));

  delete c;
  delete f1;
  f->Close();
}


void trkReso(){
  TH1::SetDefaultSumw2();

  Settings s = Settings();
 
  TFile * r = new TFile("resolutions.root","recreate"); 
  TH1D * recoRes = new TH1D("recoRes","",s.ntrkBins,s.xtrkbins);
  TH1D * recoCutRes = new TH1D("recoCutRes","",s.ntrkBins,s.xtrkbins);
  TH1D * genRes = new TH1D("genRes","",s.ntrkBins,s.xtrkbins);
  TH1D * genCutRes = new TH1D("genCutRes","",s.ntrkBins,s.xtrkbins);
  for(int c = 0; c<s.ntrkBins; c++){
    fillResoPoint(recoRes, c, "reso_reco");
    fillResoPoint(recoCutRes, c, "reso_recoCut");
    fillResoPoint(genRes, c, "reso_gen");
    fillResoPoint(genCutRes, c, "reso_genCut");
  }
  r->cd();
  recoRes->Write();
  recoCutRes->Write();
  genRes->Write();
  genCutRes->Write();


}

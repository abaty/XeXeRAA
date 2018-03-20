#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "../../../Settings.h"
#include <string>
#include <iostream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TAttLine.h"
#include "TColor.h"
#include "TAttMarker.h"


void fillResoPoint(TH1D * r, int bin, std::string name){
  TFile * f = TFile::Open("output_0.root","read");
  TH1D * h = (TH1D*)f->Get(Form("%s_%d",name.c_str(),bin));

  TF1 *f1 = new TF1("f1","gaus",0.97,1.03);
  //TF1 *f1 = new TF1("f1","[0]*TMath::Exp(-TMath::Power((x-[1]),2)/(2*[2]*[2]))+[3]*TMath::Exp(-TMath::Power((x-[1]),2)/(2*[4]*[4]))",0.97,1.03);
  f1->SetParameter(0,h->GetEntries()/20.0);
  f1->SetParameter(1,1);
  f1->SetParameter(2,0.01);
  //f1->SetParameter(3,h->GetEntries()/20.0);
  //f1->SetParameter(4,0.005);
  f1->SetParLimits(0,0,9999999);
  f1->SetParLimits(1,0.99,1.01);
  f1->SetParLimits(2,0.009,0.02);
  //f1->SetParLimits(3,0,9999999);
  //f1->SetParLimits(4,0.005,0.009);

  gStyle->SetOptFit(1);
  TCanvas * c = new TCanvas("c","c",400,400);
  h->Draw("p");
  h->Fit("f1","IEMR");

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
  gStyle->SetLegendBorderSize(0);
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

  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  c1->SetLogx();
  c1->SetLeftMargin(0.2);
  recoRes->SetStats(0);
  recoRes->SetMarkerStyle(8);
  recoRes->SetMarkerColor(kBlack);
  recoRes->SetLineColor(kBlack);
  recoRes->GetYaxis()->SetRangeUser(0,0.03);
  recoRes->GetXaxis()->SetTitle("p_{T}^{reco}");
  recoRes->GetYaxis()->SetTitle("#sigma_{p_{T}}/p_{T}");
  recoRes->GetYaxis()->SetTitleOffset(1.2);
  recoRes->GetXaxis()->SetTitleOffset(1.2);
  recoRes->Draw();
  recoCutRes->SetMarkerStyle(25);
  recoCutRes->SetMarkerColor(kRed);
  recoCutRes->SetLineColor(kRed);
  recoCutRes->Draw("same");

  TLegend * canv = new TLegend(0.3,0.6,0.8,0.85);
  canv->AddEntry((TObject*)0,"Pythia+Hydjet","");
  canv->AddEntry((TObject*)0,"|#eta|<1","");
  canv->AddEntry(recoRes,"HighPurity Only","p");
  canv->AddEntry(recoCutRes,"All Trk Selections","p");
  canv->Draw("same");
  c1->SaveAs("img/recoResolution.png");
  c1->SaveAs("img/recoResolution.pdf");
  c1->SaveAs("img/recoResolution.C");
  delete c1;
  delete canv;
  
  c1 = new TCanvas("c1","c1",800,600);
  c1->SetLogx();
  c1->SetLeftMargin(0.2);
  genRes->SetStats(0);
  genRes->SetMarkerStyle(8);
  genRes->SetMarkerColor(kBlack);
  genRes->SetLineColor(kBlack);
  genRes->GetYaxis()->SetRangeUser(0,0.03);
  genRes->GetXaxis()->SetTitle("p_{T}^{gen}");
  genRes->GetYaxis()->SetTitle("#sigma_{p_{T}}/p_{T}");
  genRes->GetYaxis()->SetTitleOffset(1.2);
  genRes->GetXaxis()->SetTitleOffset(1.2);
  genRes->Draw();
  genCutRes->SetMarkerStyle(25);
  genCutRes->SetMarkerColor(kRed);
  genCutRes->SetLineColor(kRed);
  genCutRes->Draw("same");

  canv = new TLegend(0.3,0.6,0.8,0.85);
  canv->AddEntry((TObject*)0,"Pythia+Hydjet MB","");
  canv->AddEntry((TObject*)0,"|#eta|<1","");
  canv->AddEntry(genRes,"HighPurity Only","p");
  canv->AddEntry(genCutRes,"All Trk Selections","p");
  canv->Draw("same");
  c1->SaveAs("img/genResolution.png");
  c1->SaveAs("img/genResolution.pdf");
  c1->SaveAs("img/genResolution.C");

}

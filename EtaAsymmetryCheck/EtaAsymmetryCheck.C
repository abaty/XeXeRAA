#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"

void EtaAsymmetryCheck(){
  TFile * f = TFile::Open("../output_0.root","read");
  TH1D * h[20];
  TH1D * asym[20];
  gStyle->SetOptStat(0);
  TFile * mc = TFile::Open("Hydjet.root","read");
  TH1D * mch[20];
  TH1D * mcasym[20];

  TCanvas * c1 = new TCanvas("c1","",600,600);

  for(int c = 0; c<20; c++){
    h[c] = (TH1D*)f->Get(Form("eta_hist_%d",c));
    asym[c] = new TH1D(Form("asym_%d",c),"",25,0,1);
    mch[c] = (TH1D*)mc->Get(Form("eta_hist_%d",c));
    mcasym[c] = new TH1D(Form("mcasym_%d",c),"",25,0,1);
    for(int i=1; i<26; i++){
      float eta = asym[c]->GetBinCenter(i);
      asym[c]->SetBinContent(i,(h[c]->GetBinContent(h[c]->FindBin(eta))-h[c]->GetBinContent(h[c]->FindBin(-eta)))/(2*TMath::Abs(h[c]->GetBinContent(h[c]->FindBin(eta))+h[c]->GetBinContent(h[c]->FindBin(-eta)))));
      mcasym[c]->SetBinContent(i,(mch[c]->GetBinContent(mch[c]->FindBin(eta))-mch[c]->GetBinContent(mch[c]->FindBin(-eta)))/(2*TMath::Abs(mch[c]->GetBinContent(mch[c]->FindBin(eta))+mch[c]->GetBinContent(mch[c]->FindBin(-eta)))));
    }
    asym[c]->Draw("p");
    asym[c]->GetYaxis()->SetTitle("Y^{+}-Y^{-}/|Y^{avg}|");
    asym[c]->GetYaxis()->CenterTitle();
    asym[c]->GetXaxis()->SetTitle("|#eta|");
    asym[c]->GetYaxis()->SetRangeUser(-0.1,0.1);
    asym[c]->SetMarkerStyle(8);
    
    mcasym[c]->SetLineColor(kBlue);
    mcasym[c]->Draw("h same");

   TLatex * lat = new TLatex();
   lat->DrawLatex(0.2,-0.08,Form("%d%%-%d%%",c*5,(c+1)*5));

   TLegend * l = new TLegend(0.5,0.7,0.9,0.9);
   l->AddEntry(asym[c],"Data","p");
   l->AddEntry(mcasym[c],"MB Hydjet","l");
   l->AddEntry((TObject*)0,"0.5-0.6 GeV","");
   l->Draw("same");

    c1->SaveAs(Form("img/asym%d.png",c));
    c1->SaveAs(Form("img/asym%d.pdf",c));
    c1->SaveAs(Form("img/asym%d.C",c));
  }

}

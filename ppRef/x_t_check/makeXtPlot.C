#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TH1D.h"

void makeXtPlot(){
  const int xtBins = 8;

  //high and low end of error bars of each xt point for 0.9 CMS, 1.96 CDF, 2.76 CMS, 7 CMS, 13 CMS prelim
  float h0[xtBins] = {404.4, 337.6, 268.7, 47.1, 17.3, 4.61, 2.51, 1.23 };
  float l0[xtBins] = {321.2, 269.7, 213.6, 37.7, 13.8, 3.587, 2.00, 0.956};
  float h1[xtBins] = {281.5, 248.4, 191.4, 37.3, 13.96, 3.91, 2.43, 1.157};
  float l1[xtBins] = {236.7, 211.67, 158.5, 30.9, 10.57, 1.96, 1.52, 0.629};
  float h2[xtBins] = {252.2, 229.88, 172.9, 35.7, 13.09, 3.16, 2.23, 1.017};
  float l2[xtBins] = {201.6, 188.7, 139.4, 29.6, 10.57, 2.39, 1.84, 0.801};
  float h7[xtBins] = {280.99, 264.11, 196.1, 43.6, 15.94, 3.68, 2.82, 1.251};
  float l7[xtBins] = {246.33, 237.6, 171.5, 39.11, 14.09, 3.09, 2.51, 1.084};
  float h13[xtBins] = {379, 352.75, 261.3, 58, 21.96, 5.65, 4.05, 1.781};
  float l13[xtBins] = {317.21, 302.77, 219.6, 50.2, 18.74, 4.57, 3.5, 1.468 };

  float sqrts[5] = {0.9,1.96,2.76,7,13};

  float yMax[xtBins] = {900,600,600,90,50,13,7,2.7};

  float xtValue[xtBins] = {0.0094, 0.0097, 0.0100, 0.0130, 0.0150, 0.0180, 0.0200, 0.0220};

  gStyle->SetOptStat(0);
  TH1D * dummy = new TH1D("dummy",";#sqrt{s} (TeV);(#sqrt{s}/GeV)^{4.9}Ed^{3}#sigma/dp^{3} [Mb GeV^{-2}c^{3}]",10,0.4,20);
  dummy->GetYaxis()->SetTitleOffset(1.3);
  dummy->GetYaxis()->CenterTitle();
  dummy->GetXaxis()->CenterTitle();

  TCanvas * c = new TCanvas("c","",800,600);
  c->SetLogx();

  TGraphErrors *g0, *g1, *g2, *g7, *g13;

  //for(int i = 0; i<xtBins; i++){
  for(int i = 0; i<xtBins; i++){
    c->Clear();
    dummy->GetYaxis()->SetRangeUser(0,yMax[i]);

    //CMS 0.9
    g0 = new TGraphErrors(0);
    g0->SetTitle("");
    float y = (h0[i]+l0[i])/2.0;
    g0->SetPoint(i,sqrts[0],y);
    g0->SetPointError(i,0,h0[i]-y);
    g0->SetMarkerColor(kRed);
    g0->SetLineColor(kRed);
    g0->SetMarkerStyle(8);
    g0->SetMarkerSize(1.5);

    //CDF 1.96
    g1 = new TGraphErrors(0);
    y = (h1[i]+l1[i])/2.0;
    g1->SetPoint(i,sqrts[1],y);
    g1->SetPointError(i,0,h1[i]-y);
    g1->SetMarkerColor(kOrange);
    g1->SetLineColor(kOrange);
    g1->SetMarkerStyle(30);
    g1->SetMarkerSize(1.5);
    

    //CMS 2.76
    g2 = new TGraphErrors(0);
    y = (h2[i]+l2[i])/2.0;
    g2->SetPoint(i,sqrts[2],y);
    g2->SetPointError(i,0,h2[i]-y);
    g2->SetMarkerColor(kViolet+3);
    g2->SetLineColor(kViolet+3);
    g2->SetMarkerStyle(21);
    g2->SetMarkerSize(1.5);
    

    //CMS 7
    g7 = new TGraphErrors(0);
    y = (h7[i]+l7[i])/2.0;
    g7->SetPoint(i,sqrts[3],y);
    g7->SetPointError(i,0,h7[i]-y);
    g7->SetMarkerColor(kBlack);
    g7->SetLineColor(kBlack);
    g7->SetMarkerStyle(29);
    g7->SetMarkerSize(1.5);
 
    //CMS 13 
    g13 = new TGraphErrors(0);
    y = (h13[i]+l13[i])/2.0;
    g13->SetPoint(i,sqrts[4],y);
    g13->SetPointError(i,0,h13[i]-y);
    g13->SetMarkerColor(kGreen+1);
    g13->SetLineColor(kGreen+1);
    g13->SetMarkerStyle(8);
    g13->SetMarkerSize(1.5);

    dummy->Draw();
    g0->Draw("PZ same"); 
    g1->Draw("PZ same"); 
    g2->Draw("PZ same"); 
    g7->Draw("PZ same"); 
    g13->Draw("PZ same"); 
 
    TLegend * l = new TLegend(0.1,0.6,0.8,0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->AddEntry(g0,"CMS 0.90 TeV","p");
    l->AddEntry(g1,"CDF 1.96 TeV","p");
    l->AddEntry(g2,"CMS 2.76 TeV","p");
    l->AddEntry(g7,"CMS 7.00 TeV","p");
    l->AddEntry(g13,"CMS 13.0 TeV (Unpublished)","p");
    l->Draw("same");

    TLegend * l2 = new TLegend(0.55,0.1,0.8,0.3);
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    l2->AddEntry((TObject*)0,Form("x_{T} = %1.4f",xtValue[i]),"");
    l2->Draw("same");

    c->SaveAs(Form("img/xtPlot_%d.pdf",i));
    c->SaveAs(Form("img/xtPlot_%d.png",i));
    c->SaveAs(Form("img/xtPlot_%d.C",i));
    c->Clear();
    delete l;
    delete l2;
    delete g0;
    delete g1;
    delete g2;
    delete g7;
    delete g13;
  }


}

#include "TFile.h"
#include "TH1D.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <iostream>

void graphToHist7TeV(){
  TFile * f = TFile::Open("7000TeV_CMS_TGraph_xt.root","read");
  TGraphAsymmErrors * g = (TGraphAsymmErrors*)f->Get("Table 3/Graph1D_y1");

  for(int i = 0; i<g->GetN(); i++){
    double x, y;
    g->GetPoint(i,x,y);
    g->SetPoint(i,x*7000/2,y*2*TMath::Power(10,15)/TMath::Power(7000,4.9));//scale xt to pt, factor of 2 to account for average of + and - charges
    g->SetPointEYhigh(i,g->GetErrorYhigh(i)*2*TMath::Power(10,15)/TMath::Power(7000,4.9));
    g->SetPointEYlow(i,g->GetErrorYlow(i)*2*TMath::Power(10,15)/TMath::Power(7000,4.9));

    g->Print("All");
  }

  
  
}

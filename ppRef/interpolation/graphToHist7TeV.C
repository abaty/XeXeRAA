
#include "TH1D.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "TF1.h"
#include "TCanvas.h"
#include "TSpline.h"

Double_t spline_3nodes(Double_t *x, Double_t *par)
{

   /*Fit parameters:
    par[0-3]=X of nodes (to be fixed in the fit!)
    par[4-7]=Y of nodes
    par[8-9]=first derivative at begin and end (to be fixed in the fit!)
    */
   Double_t xx = x[0];
   Double_t xn[4] = { par[0], par[1], par[2] , par[3]};
   Double_t yn[4] = { par[4], par[5], par[6] , par[7]};
   Double_t b1 = par[8];
   Double_t e1 = 0;//par[9];
   TSpline3 sp3("sp3", xn, yn, 4, "b1e1", b1, e1);
   return sp3.Eval(xx);
}

void graphToHist7TeV(){
  TFile * f = TFile::Open("7000TeV_CMS_TGraph_xt.root","read");
  TGraphAsymmErrors * g = (TGraphAsymmErrors*)f->Get("Table 3/Graph1D_y1");
  
  const int ntrkBins = 32;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};
  TH1D * pp7 = new TH1D("pp7","",ntrkBins,xtrkbins);


  for(int i = 0; i<g->GetN(); i++){
    double x, y;
    g->GetPoint(i,x,y);
    g->SetPoint(i,x*7000/2,y*2*TMath::Power(10,15)/TMath::Power(7000,4.9));//scale xt to pt, factor of 2 to account for average of + and - charges
    g->SetPointEYhigh(i,g->GetErrorYhigh(i)*2*TMath::Power(10,15)/TMath::Power(7000,4.9));
    g->SetPointEYlow(i,g->GetErrorYlow(i)*2*TMath::Power(10,15)/TMath::Power(7000,4.9));
  }
  g->Print("All");

  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  c1->SetLogx();
  c1->SetLogy();
  g->Draw();

  TF1 *cms_7000_fit = new TF1("cms_7000_fit","[0]*pow(1.0+(x/[1]),[2])",0.5,120);
  cms_7000_fit->SetLineWidth(1);
  cms_7000_fit->SetParameters(2000,0.85,-7);
  TFitResultPtr r = g->Fit(cms_7000_fit,"REMEX0S");
  std::cout << "Chi2/ndof: " << r->Chi2()/r->Ndf() << std::endl;
  
  c1->SaveAs("img/7TeV_PowerLawFit.C");
  c1->SaveAs("img/7TeV_PowerLawFit.png");
  c1->SaveAs("img/7TeV_PowerLawFit.pdf");
  //residuals
   
  TGraphErrors * residuals = new TGraphErrors(g->GetN());
  for(int i = 0; i<g->GetN(); i++){
    double x, y;
    g->GetPoint(i,x,y);
    residuals->SetPoint(i,x,y/cms_7000_fit->Eval(x));//scale xt to pt, factor of 2 to account for average of + and - charges
    residuals->SetPointError(i,0,(g->GetErrorYhigh(i)/y)*(y/cms_7000_fit->Eval(x)));
  }
  residuals->Print("All");
  TCanvas * c2 = new TCanvas("c2","c2",800,600);
  c2->SetLogx();
  residuals->SetMarkerStyle(8);
  residuals->Draw("AP");

  //TF1 *res_fit = new TF1("cms_7000_fit","[0]+[1]*log(x)+[2]*log(x)*log(x)+[3]*pow(log(x),3)+[4]*pow(log(x),4)",0.5,200);
  TF1 *res_fit = new TF1("cms_7000_fit",spline_3nodes,0.5,120,9);
  res_fit->SetLineWidth(1);
  res_fit->SetParameters(1,5,10,30,1,1,1,1,0);
  TFitResultPtr r2 = residuals->Fit(res_fit,"REMEX0S");
  std::cout << "Chi2/ndof: " << r2->Chi2()/r2->Ndf() << std::endl;  
  c2->SaveAs("img/7TeV_Residuals.C");
  c2->SaveAs("img/7TeV_Residuals.png");
  c2->SaveAs("img/7TeV_Residuals.pdf");


  double parameters[9] = {r2->GetParams()[0],r2->GetParams()[1],r2->GetParams()[2],r2->GetParams()[3],r2->GetParams()[4],r2->GetParams()[5],r2->GetParams()[6],r2->GetParams()[7],r2->GetParams()[8]};
  double x1 = 5.0;
  std::cout << spline_3nodes(&x1,parameters) << std::endl;;


  //numeric integration with the spline
  for(int i = 0; i<ntrkBins; i++){
    double step = (xtrkbins[i+1]-xtrkbins[i])/50.0;
    double total = 0;
    for(int j = 0; j<50; j++){
      double x = xtrkbins[i]+(0.5+j)*step;
      //first term corrects for divding by bin center of pt or just the pt of a track
      //second is spline fit
      //third is lo power law fit
      //last one averages over the bin width
      total += (x/((xtrkbins[i]+xtrkbins[i+1])/2))*spline_3nodes(&x,parameters)*cms_7000_fit->Eval(x)*(step/(xtrkbins[i+1]-xtrkbins[i]));
    }
    pp7->SetBinContent(i+1,total);

    double dist = 999;
    double relError = 100;
    for(int j = 0; j<g->GetN(); j++){
      double x, y;
      g->GetPoint(j,x,y);
      if(TMath::Abs(x-pp7->GetXaxis()->GetBinCenter(i+1))<dist){
        dist = TMath::Abs(x-pp7->GetXaxis()->GetBinCenter(i+1));
        relError = g->GetErrorYhigh(j)/y;
      }
    }
    std::cout << relError << std::endl;
    pp7->SetBinError(i+1,relError*pp7->GetBinContent(i+1));
  }
  pp7->Print("All");

  TFile * out = TFile::Open("binned7TeV.root","recreate");
  pp7->SetDirectory(out);
  pp7->SetTitle("binned7TeVpp");
  pp7->Write(); 
}


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


  double parameters[9] = {r2->GetParams()[0],r2->GetParams()[1],r2->GetParams()[2],r2->GetParams()[3],r2->GetParams()[4],r2->GetParams()[5],r2->GetParams()[6],r2->GetParams()[7],r2->GetParams()[8]};
  double x1 = 5.0;
  std::cout << spline_3nodes(&x1,parameters) << std::endl;;
}

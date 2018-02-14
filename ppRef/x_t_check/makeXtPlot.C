#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TH1D.h"
#include "TMath.h"
#include "TF1.h"

void globalPoly2Fit(int i, TF1 * f, TGraphErrors * g0, TGraphErrors * g1, TGraphErrors * g2, TGraphErrors * g5, TGraphErrors * g7, TGraphErrors * g13){
  TGraphErrors * g = new TGraphErrors(6);
  double x, y;
  g0->GetPoint(0,x,y);
  std::cout << x << " " << y << std::endl;
  g->SetPoint(0,0.9,y);
  g->SetPointError(0,0,g0->GetErrorY(0));
  g1->GetPoint(0,x,y);
  g->SetPoint(1,1.96,y);
  g->SetPointError(1,0,g1->GetErrorY(0));
  g2->GetPoint(0,x,y);
  g->SetPoint(2,2.76,y);
  g->SetPointError(2,0,g2->GetErrorY(0));
  g5->GetPoint(0,x,y);
  g->SetPoint(3,5.02,y);
  g->SetPointError(3,0,g5->GetErrorY(0));
  g7->GetPoint(0,x,y);
  g->SetPoint(4,7,y);
  g->SetPointError(4,0,g7->GetErrorY(0));
  g13->GetPoint(0,x,y);
  g->SetPoint(5,13,y);
  g->SetPointError(5,0,g13->GetErrorY(0));
  g->Print("All");

  g->Fit(Form("f%d",i),"EMR0");
  f->Draw("same");
}

void makeXtPlot(){
  const int xtBins = 8;

  //5TeV data from hepdata
  TFile * file = TFile::Open("../pp5TeV_FromRAA.root","read");
  TH1D * ppSpec = (TH1D*) file->Get("Table 7/Hist1D_y1");
  TH1D * ppSpec_stat = (TH1D*) file->Get("Table 7/Hist1D_y1_e1");
  TH1D * ppSpec_syst = (TH1D*) file->Get("Table 7/Hist1D_y1_e2plus");
  TH1D * ppSpec_lumi = (TH1D*) file->Get("Table 7/Hist1D_y1_e3");
  for(int i = 1; i<ppSpec->GetSize()-1;i++){
    ppSpec->SetBinError(i,TMath::Power(ppSpec_stat->GetBinContent(i)*ppSpec_stat->GetBinContent(i)+ppSpec_syst->GetBinContent(i)*ppSpec_syst->GetBinContent(i)+ppSpec_lumi->GetBinContent(i)*ppSpec_lumi->GetBinContent(i),0.5));
  }

  //ignore 7000 here, i's for 5020 GeV
  TCanvas * c1 = new TCanvas("c1","",800,600);
  c1->SetLogx();
  c1->SetLogy();
  ppSpec->GetXaxis()->SetRangeUser(10,80);
  ppSpec->GetYaxis()->SetTitle("");
  ppSpec->Draw();
  

  float xLow = 10;
  float xHigh = 100;
  TF1 *cms_5020_fit = new TF1("cms_5020_fit","[0]*pow(1.0+(x/[1]),[2])",xLow,xHigh);
  cms_5020_fit->SetLineWidth(1);
  cms_5020_fit->SetParameters(3,1,-6.5);
  TFitResultPtr r = ppSpec->Fit(cms_5020_fit,"REMEXSI");
  std::cout << "Chi2/ndof: " << r->Chi2()/r->Ndf() << std::endl;
  
  c1->SaveAs("img/5TeV_PowerLawFit.C");
  c1->SaveAs("img/5TeV_PowerLawFit.png");
  c1->SaveAs("img/5TeV_PowerLawFit.pdf");
  
  //residuals 
  int nResidPoints = 0;
  for(int i = 1; i<ppSpec->GetSize()-1; i++){
    if(ppSpec->GetXaxis()->GetBinCenter(i)>xLow && ppSpec->GetXaxis()->GetBinCenter(i)<xHigh) nResidPoints++;
  } 
  
  TGraphErrors * residuals = new TGraphErrors(nResidPoints);
  int t = 0;
  for(int i = 1; i<ppSpec->GetSize()-1; i++){
    if(ppSpec->GetXaxis()->GetBinCenter(i)<xLow || ppSpec->GetXaxis()->GetBinCenter(i)>xHigh) continue;
    
    residuals->SetPoint(t,ppSpec->GetBinCenter(i),ppSpec->GetBinContent(i)*ppSpec->GetBinWidth(i)/cms_5020_fit->Integral(ppSpec->GetXaxis()->GetBinLowEdge(i),ppSpec->GetXaxis()->GetBinLowEdge(i+1)));//scale xt to pt, factor of 2 to account for average of + and - charges
    residuals->SetPointError(t,0,ppSpec->GetBinError(i)*ppSpec->GetBinWidth(i)/cms_5020_fit->Integral(ppSpec->GetXaxis()->GetBinLowEdge(i),ppSpec->GetXaxis()->GetBinLowEdge(i+1)));
    t++;
  }
  residuals->Print("All");
  TCanvas * c2 = new TCanvas("c2","c2",800,600);
  c2->SetLogx();
  residuals->SetMarkerStyle(8);
  residuals->GetXaxis()->SetRangeUser(xLow,xHigh);
  residuals->Draw("AP");
  c2->SaveAs("img/5TeV_Residuals.C");
  c2->SaveAs("img/5TeV_Residuals.png");
  c2->SaveAs("img/5TeV_Residuals.pdf");
  

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

  TGraphErrors *g0, *g1, *g2, *g5, *g7, *g13;
  TF1 * f[xtBins];

  //for(int i = 0; i<xtBins; i++){
  for(int i = 0; i<xtBins; i++){
    c->Clear();
    dummy->GetYaxis()->SetRangeUser(0,yMax[i]);

    //CMS 0.9
    g0 = new TGraphErrors(1);
    g0->SetTitle("");
    float y = (h0[i]+l0[i])/2.0;
    g0->SetPoint(0,sqrts[0],y);
    g0->SetPointError(0,0,h0[i]-y);
    g0->SetMarkerColor(kRed);
    g0->SetLineColor(kRed);
    g0->SetMarkerStyle(8);
    g0->SetMarkerSize(1.5);

    //CDF 1.96
    g1 = new TGraphErrors(1);
    y = (h1[i]+l1[i])/2.0;
    g1->SetPoint(0,sqrts[1],y);
    g1->SetPointError(0,0,h1[i]-y);
    g1->SetMarkerColor(kOrange);
    g1->SetLineColor(kOrange);
    g1->SetMarkerStyle(30);
    g1->SetMarkerSize(1.5);
    

    //CMS 2.76
    g2 = new TGraphErrors(1);
    y = (h2[i]+l2[i])/2.0;
    g2->SetPoint(0,sqrts[2],y);
    g2->SetPointError(0,0,h2[i]-y);
    g2->SetMarkerColor(kViolet+3);
    g2->SetLineColor(kViolet+3);
    g2->SetMarkerStyle(21);
    g2->SetMarkerSize(2.0);
    
    //CMS 5
    g5 = new TGraphErrors(1);
    //get the y value
    y = cms_5020_fit->Eval(xtValue[i]*5020.0/2.0);
    y = y*TMath::Power(5020,4.9)*TMath::Power(10,-9)*70./2.0;
    int closestBin = ppSpec->GetXaxis()->FindBin(xtValue[i]*5020.0/2.0);
    float yRelErr = ppSpec->GetBinError(closestBin)/ppSpec->GetBinContent(closestBin);
    float yErr = cms_5020_fit->Eval(xtValue[i]*5020.0/2.0)*yRelErr;
    yErr = yErr*TMath::Power(5020,4.9)*TMath::Power(10,-9)*70./2.0;
    //10-9 is for mb to Mb, 2 is for average of + and - hadrons, 70 is for 70 mb scale factor in 5 TeV data, the 4.9 is for the xt scaling phenomological stuff
    g5->SetPoint(0,5.020,y);
    g5->SetPointError(0,0,yErr);//todo
    g5->SetMarkerColor(kBlue);
    g5->SetLineColor(kBlue);    
    g5->SetMarkerStyle(33);
    g5->SetMarkerSize(1.5);

    //CMS 7
    g7 = new TGraphErrors(1);
    y = (h7[i]+l7[i])/2.0;
    g7->SetPoint(0,sqrts[3],y);
    g7->SetPointError(0,0,h7[i]-y);
    g7->SetMarkerColor(kBlack);
    g7->SetLineColor(kBlack);
    g7->SetMarkerStyle(29);
    g7->SetMarkerSize(1.5);
 
    //CMS 13 
    g13 = new TGraphErrors(1);
    y = (h13[i]+l13[i])/2.0;
    g13->SetPoint(0,sqrts[4],y);
    g13->SetPointError(0,0,h13[i]-y);
    g13->SetMarkerColor(kGreen+1);
    g13->SetLineColor(kGreen+1);
    g13->SetMarkerStyle(8);
    g13->SetMarkerSize(1.5);

    dummy->Draw();
    g0->Draw("PZ same"); 
    g1->Draw("PZ same"); 
    g2->Draw("PZ same"); 
    g5->Draw("PZ same"); 
    g7->Draw("PZ same"); 
    g13->Draw("PZ same"); 
 
    TLegend * l = new TLegend(0.1,0.6,0.8,0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->AddEntry(g0,"CMS 0.90 TeV","p");
    l->AddEntry(g1,"CDF 1.96 TeV","p");
    l->AddEntry(g2,"CMS 2.76 TeV","p");
    l->AddEntry(g5,"CMS 5.02 TeV","p");
    l->AddEntry(g7,"CMS 7.00 TeV","p");
    l->AddEntry(g13,"CMS 13.0 TeV (Unpublished)","p");
    l->Draw("same");

    TLegend * l2 = new TLegend(0.55,0.1,0.8,0.3);
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    l2->AddEntry((TObject*)0,Form("x_{T} = %1.4f",xtValue[i]),"");
    l2->Draw("same");

    f[i] = new TF1(Form("f%d",i),"[0]+[1]*TMath::Log(x)+[2]*TMath::Log(x)*TMath::Log(x)",0.8,14);
    f[i]->SetLineWidth(1);
    f[i]->SetLineColor(kBlack);
    f[i]->SetParameters(5,0,0);
    globalPoly2Fit(i,f[i],g0,g1,g2,g5,g7,g13);

    c->SaveAs(Form("img/xtPlot_%d.pdf",i));
    c->SaveAs(Form("img/xtPlot_%d.png",i));
    c->SaveAs(Form("img/xtPlot_%d.C",i));
    c->Clear();
    
    delete f[i];
    delete l;
    delete l2;
    delete g0;
    delete g1;
    delete g2;
    delete g5;
    delete g7;
    delete g13;
  }


}

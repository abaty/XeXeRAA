#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TH1D.h"
#include "TMath.h"
#include "TF1.h"

void globalPoly2Fit(int i, TF1 * f, TF1 * fErr, TGraphErrors * g0, TGraphErrors * g1, TGraphErrors * g2, TGraphErrors * g5, TGraphErrors * g7, TGraphErrors * g13){
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

  TFitResultPtr t = g->Fit(Form("f%d",i),"SEMR0");
  t->Print("V");
  TMatrixDSym m = t->GetCovarianceMatrix();
  fErr->SetParameter(0,m(0,0));
  fErr->SetParameter(1,2*m(0,1));
  fErr->SetParameter(2,2*m(0,2)+m(1,1));
  fErr->SetParameter(3,2*m(1,2));
  fErr->SetParameter(4,m(2,2));
  //std::cout << TMath::Power(m(0,0),2) << " " << 2*m(0,1)*TMath::Log(5.44) << " " << (2*m(0,2)+TMath::Power(m(1,1),2))*TMath::Power(TMath::Log(5.44),2) << " " << 2*m(1,2)*TMath::Power(TMath::Log(5.44),3) << " " << TMath::Power(m(2,2),2)*TMath::Power(TMath::Log(5.44),4)  << std::endl;
  //std::cout << fErr->Eval(5.44) << " " << f->Eval(5.44) <<  std::endl;
  //std::cout << TMath::Power(TMath::Abs(fErr->Eval(5.44)),0.5)/f->Eval(5.44) << std::endl;
  f->Draw("same");
}

void makeXtPlot(){
  TFile * output = TFile::Open("xtScaling.root","recreate");
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

  output->cd();

  //ignore 7000 here, i's for 5020 GeV
  TCanvas * c1 = new TCanvas("c1","",800,600);
  c1->SetLogx();
  c1->SetLogy();
  //ppSpec->GetXaxis()->SetRangeUser(0.5,105);
  ppSpec->GetXaxis()->SetRangeUser(20,105);
  ppSpec->GetYaxis()->SetTitle("");
  ppSpec->GetXaxis()->SetTitle("p_{T} GeV");
  ppSpec->Draw();
  

  //float xLow = 0.5;
  //float xHigh = 105;

  float xLow = 20;
  float xHigh = 105;
  TF1 *cms_5020_fit = new TF1("cms_5020_fit","[0]*pow(1.0+(x/[1]),[2])",xLow,xHigh);
  cms_5020_fit->SetLineWidth(1);
  cms_5020_fit->SetParameters(3.3,1.11,-6.58);
  TFitResultPtr r = ppSpec->Fit(cms_5020_fit,"REMIS");
  std::cout << "Chi2/ndof: " << r->Chi2()/r->Ndf() << std::endl;
  std::cout << cms_5020_fit->GetParameter(0) << " " << cms_5020_fit->GetParameter(1) << " " << cms_5020_fit->GetParameter(2) << std::endl;
  
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
  residuals->SetTitle("");
  residuals->GetXaxis()->SetTitle("p_{T} (GeV)");
  residuals->GetYaxis()->SetTitle("Fit Residuals");
  residuals->Draw("AP");
  //TF1 * residFit = new TF1("residFit","[0]+[1]*TMath::Log(x)+[2]*TMath::Power(TMath::Log(x),2)+[3]*TMath::Power(TMath::Log(x),3)+[4]*TMath::Power(TMath::Log(x),4)+[5]*TMath::Power(TMath::Log(x),5)+[6]*TMath::Power(TMath::Log(x),6)+[7]*TMath::Power(TMath::Log(x),7)",0.5,120);
  //residFit->SetParameters(1,0,0,0,0,0,0,0);
  //residuals->Fit("residFit","REMIS");

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
  TGraphErrors *xt544 = new TGraphErrors(xtBins);
  TGraph *errU[xtBins];
  TGraph *errD[xtBins];
  TF1 * f[xtBins];
  TF1 * fErr[xtBins];

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
    
    f[i] = new TF1(Form("f%d",i),"[0]+[1]*TMath::Log(x)+[2]*TMath::Log(x)*TMath::Log(x)",0.8,14);
    fErr[i] = new TF1(Form("fErr%d",i),"[0]+[1]*TMath::Log(x)+[2]*TMath::Log(x)*TMath::Log(x)+[3]*TMath::Power(TMath::Log(x),3)+[4]*TMath::Power(TMath::Log(x),4)",0.8,14);
    f[i]->SetLineWidth(1);
    f[i]->SetLineColor(kBlack);
    f[i]->SetParameters(5,0,0);
    globalPoly2Fit(i,f[i],fErr[i],g0,g1,g2,g5,g7,g13);

    errU[i] = new TGraph(2000);
    errU[i]->SetFillColor(kGray);
    for(int j = 0; j<1000; j++){
      float x = 0.8+(float)j/1000.0*(14-0.8);
      float err = TMath::Power(fErr[i]->Eval(5.44),0.5);
      errU[i]->SetPoint(j,x,f[i]->Eval(x)+err);
      errU[i]->SetPoint(1999-j,x,f[i]->Eval(x)-err);
    }

    TLegend * l = new TLegend(0.1,0.6,0.8,0.9);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->AddEntry(g0,"CMS 0.90 TeV","p");
    l->AddEntry(g1,"CDF 1.96 TeV","p");
    l->AddEntry(g2,"CMS 2.76 TeV","p");
    l->AddEntry(g5,"CMS 5.02 TeV","p");
    l->AddEntry(g7,"CMS 7.00 TeV","p");
    l->AddEntry(g13,"CMS 13.0 TeV (Unpublished)","p");
    l->AddEntry(f[i],"Parabola fit in #sqrt{s}","l");
    l->Draw("same");

    TLegend * l2 = new TLegend(0.55,0.1,0.8,0.3);
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    l2->AddEntry((TObject*)0,Form("x_{T} = %1.4f",xtValue[i]),"");
    l2->Draw("same");

    errU[i]->Draw("F same");
    f[i]->Draw("same"); 
    g0->Draw("PZ same"); 
    g1->Draw("PZ same"); 
    g2->Draw("PZ same"); 
    g5->Draw("PZ same"); 
    g7->Draw("PZ same"); 
    g13->Draw("PZ same"); 

    xt544->SetPoint(i,xtValue[i]*5440./2.0,f[i]->Eval(5.44)*TMath::Power(5440.,-4.9)*2*TMath::Power(10,9));
    //std::cout << getErrorFromFit(f[i],5.440) << std::endl;
    float fitError = TMath::Power(fErr[i]->Eval(5.44),0.5)/f[i]->Eval(5.44);
    xt544->SetPointError(i,0,f[i]->Eval(5.44)*TMath::Power(5440.,-4.9)*2*TMath::Power(10,9)*fitError);

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
  xt544->Print("All");

  TCanvas * c3 = new TCanvas("c3","c3",800,600);
  c3->SetLogy();
  c3->SetLogx();
  xt544->SetTitle("");
  xt544->GetXaxis()->SetRangeUser(8,110);
  xt544->GetXaxis()->SetMoreLogLabels(1);
  xt544->GetXaxis()->SetTitle("p_{T} (GeV)");
  xt544->GetYaxis()->SetTitle("E#frac{d^{3}#sigma}{d^{3}p} (mb GeV^{2})");
  xt544->Draw("AP");
  TF1 *f544_fit = new TF1("f544_fit","[0]*pow(1.0+(x/[1]),[2])",xLow,xHigh);
  f544_fit->SetLineWidth(1);
  f544_fit->SetParameters(0.7,3,-7);
  TFitResultPtr xtFitResult = xt544->Fit("f544_fit","REMS");
  std::cout << "Chi2/ndof: " << xtFitResult->Chi2()/xtFitResult->Ndf() << std::endl;
  c3->SaveAs("img/544Fit.png");
  c3->SaveAs("img/544Fit.pdf");
  c3->SaveAs("img/544Fit.C");


  const int ntrkBins = 32;
  double xtrkbins[ntrkBins+1] = {0.5,0.6, 0.7 , 0.8 , 0.9 , 1.0 , 1.1 , 1.2 , 1.4 , 1.6 , 1.8 , 2.0 , 2.2 , 2.4 , 3.2 , 4.0 , 4.8 , 5.6 , 6.4 , 7.2 , 9.6 , 12.0, 14.4,19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8,73.6,86.4,103.6};
  TH1D * ppRef544 = new TH1D("xtPPRef544",";p_{T};",ntrkBins,xtrkbins);
  for(int i = 1; i<ppRef544->GetSize()-1; i++){
    if(ppRef544->GetBinCenter(i)<xLow || ppRef544->GetBinCenter(i)>xHigh){
      ppRef544->SetBinContent(i,0);
      ppRef544->SetBinError(i,0);
      continue;
    }
    float bw = ppRef544->GetBinWidth(i);
    float center = ppRef544->GetBinCenter(i);
    ppRef544->SetBinContent(i,f544_fit->Integral(ppRef544->GetBinLowEdge(i),ppRef544->GetBinLowEdge(i+1))/bw);
    float relativeError = 0;
    float dist = 1000;
    for(int j = 0; j<xt544->GetN(); j++){
      double x, y;
      xt544->GetPoint(j,x,y);
      if(TMath::Abs(x-center)<dist){
        dist = TMath::Abs(x-center);
        relativeError = xt544->GetErrorY(j)/y;
      }
    }

    ppRef544->SetBinError(i,ppRef544->GetBinContent(i)*relativeError);
  }
  ppRef544->Print("All");
  output->Write();
}

#include "TLegend.h"
#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <string>
#include <cstring>
#include "TGraphAsymmErrors.h"

void speciesCorrPlots(){
  gStyle->SetErrorX(0);
  gStyle->SetOptStat(0);
  TFile * f = TFile::Open("trkCorr_March5_wSpeciesCorr.root","read");
  TH1D * speciesCorr[6];
  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  TLegend * l = new TLegend(0.6,0.7,0.9,0.9);
  for(int i = 0; i<6; i++){
    speciesCorr[i] = (TH1D*)f->Get(Form("speciesCorrSyst1D_ForPlots_%d",i));
    speciesCorr[i]->GetXaxis()->SetRangeUser(0.5,14);
    speciesCorr[i]->SetMarkerStyle(8);
    speciesCorr[i]->SetMarkerColor(kBlack);
    speciesCorr[i]->SetLineColor(kBlack);
    speciesCorr[i]->GetXaxis()->SetTitle("p_{T}");
    speciesCorr[i]->GetYaxis()->SetTitle("Correction factor");
    speciesCorr[i]->SetLineColor(kBlack);
    speciesCorr[i]->Draw();
    l->Clear();
    l->SetLineWidth(0);
    l->SetFillStyle(0);
    if(i==0) l->AddEntry((TObject*)0,"0-5%","");
    if(i==1) l->AddEntry((TObject*)0,"5-10%","");
    if(i==2) l->AddEntry((TObject*)0,"10-30%","");
    if(i==3) l->AddEntry((TObject*)0,"30-50%","");
    if(i==4) l->AddEntry((TObject*)0,"50-70%","");
    if(i==5) l->AddEntry((TObject*)0,"70-100%","");
    l->Draw("same");

    TLine * line1 = new TLine();
    line1->SetLineColor(kRed);
    line1->SetLineWidth(2);
    for(int j = 1; j<speciesCorr[i]->GetSize()-1; j++){
      if(speciesCorr[i]->GetBinContent(j)<0 && speciesCorr[i]->GetBinCenter(j)>3){
        line1->SetX1(speciesCorr[i]->GetBinCenter(j)-0.3);
        line1->SetX2(speciesCorr[i]->GetBinCenter(j)-0.3);
        line1->SetY1(-0.07);
        line1->SetY2(0.07);
        break;
      }
    }
    line1->Draw("same");

    c1->SaveAs(Form("img/speciesCorr_%d.png",i));
    c1->SaveAs(Form("img/speciesCorr_%d.pdf",i));
    c1->SaveAs(Form("img/speciesCorr_%d.C",i));
    delete line1;
  } 
}

void makeTGraphArray(TCanvas * c1, TGraphAsymmErrors ** eff, TGraphAsymmErrors ** eff2, TGraphAsymmErrors ** eff3, std::string yTitle, std::string outTitle, TF1 ** fit, bool doFit = false ,bool isZoom = false){

  gStyle->SetErrorX(0);
  TLegend * l[6];
  for(int i = 0; i<6; i++){
    c1->cd(i+1);
    c1->cd(i+1)->SetLogx();
    eff[i]->SetMarkerStyle(8);
    eff[i]->SetMarkerColor(kBlack);
    eff[i]->SetLineColor(kBlack);
    eff3[i]->GetXaxis()->SetTitle("p_{T}");
    eff3[i]->GetXaxis()->SetRangeUser(0.5,180);
    if(doFit) eff3[i]->GetXaxis()->SetRangeUser(1,180);
    eff3[i]->GetYaxis()->SetTitle(yTitle.c_str());
    eff3[i]->GetYaxis()->SetTitleOffset(1.3);
    if(strcmp(yTitle.c_str(),"misreconstruction rate")==0) eff3[i]->GetYaxis()->SetTitle("(1-misreconstruction rate)");
    if(strcmp(yTitle.c_str(),"secondary rate")==0) eff3[i]->GetYaxis()->SetTitle("(1-secondary rate)");
    
    eff2[i]->SetMarkerStyle(24);
    eff2[i]->SetMarkerColor(kBlue);
    eff2[i]->SetLineColor(kBlue);
    
    eff3[i]->SetMarkerStyle(34);
    eff3[i]->SetMarkerColor(kRed);
    eff3[i]->SetLineColor(kRed);
 
    if(strcmp(yTitle.c_str(),"efficiency")==0) eff3[i]->GetYaxis()->SetRangeUser(0,1.2);
    if(strcmp(yTitle.c_str(),"misreconstruction rate")==0) eff3[i]->GetYaxis()->SetRangeUser(0.65,1.05);
    if(strcmp(yTitle.c_str(),"secondary rate")==0) eff3[i]->GetYaxis()->SetRangeUser(0.95,1.05);
    if(strcmp(yTitle.c_str(),"multiple reco rate")==0) eff3[i]->GetYaxis()->SetRangeUser(0,0.0001);
    
    if(isZoom && strcmp(yTitle.c_str(),"efficiency")==0) eff3[i]->GetYaxis()->SetRangeUser(0.5,0.9);
    if(isZoom && strcmp(yTitle.c_str(),"misreconstruction rate")==0) eff3[i]->GetYaxis()->SetRangeUser(0.95,1.05);
    if(isZoom && strcmp(yTitle.c_str(),"secondary rate")==0) eff3[i]->GetYaxis()->SetRangeUser(0.97,1.03);
    if(isZoom && strcmp(yTitle.c_str(),"multiple reco rate")==0) eff3[i]->GetYaxis()->SetRangeUser(0,0.0001);
 
    for(int j = 0; j<eff[i]->GetN();j++){
      eff[i]->SetPointError(j,0,0,eff[i]->GetErrorYlow(j),eff[i]->GetErrorYhigh(j));
    }
    for(int j = 0; j<eff2[i]->GetN();j++){
      eff2[i]->SetPointError(j,0,0,eff2[i]->GetErrorYlow(j),eff2[i]->GetErrorYhigh(j));
    }
    for(int j = 0; j<eff3[i]->GetN();j++){
      eff3[i]->SetPointError(j,0,0,eff3[i]->GetErrorYlow(j),eff3[i]->GetErrorYhigh(j));
    }
   
    eff3[i]->Draw("AP");
    if(!doFit) eff[i]->Draw("P same");
    if(!doFit) eff2[i]->Draw("P same");
    eff3[i]->Draw("P same");
   
    if(doFit){
      if(isZoom) gStyle->SetOptFit();
      else gStyle->SetOptFit(0);
      fit[i]->SetLineColor(kBlack);
      fit[i]->SetLineWidth(2);
      fit[i]->Draw("sames");
    }
 
    if(!isZoom && strcmp(yTitle.c_str(),"misreconstruction rate")==0) l[i] = new TLegend(0.1,0.3,0.7,0.5);
    else l[i] = new TLegend(0.1,0.7,0.7,0.89);
    l[i]->SetBorderSize(0);
    l[i]->SetFillStyle(0);
    if(i==0) l[i]->AddEntry((TObject*)0,"0-5%","");
    if(i==1) l[i]->AddEntry((TObject*)0,"5-10%","");
    if(i==2) l[i]->AddEntry((TObject*)0,"10-30%","");
    if(i==3) l[i]->AddEntry((TObject*)0,"30-50%","");
    if(i==4) l[i]->AddEntry((TObject*)0,"50-70%","");
    if(i==5) l[i]->AddEntry((TObject*)0,"70-100%","");
    l[i]->AddEntry((TObject*)0,"Analysis Cuts","");
    if(!doFit) l[i]->AddEntry(eff[i],"Hydjet MB","p");
    if(!doFit) l[i]->AddEntry(eff2[i],"EPOS MB","p");
    l[i]->AddEntry(eff3[i],"Pythia+Hydjet","p");
    l[i]->Draw("same");
  }
  if(isZoom){
    if(doFit){
      c1->SaveAs(Form("img/%s_Zoom_Fit.png",outTitle.c_str()));
      c1->SaveAs(Form("img/%s_Zoom_Fit.pdf",outTitle.c_str()));
      c1->SaveAs(Form("img/%s_Zoom_Fit.C",outTitle.c_str()));
    }else{
      c1->SaveAs(Form("img/%s_Zoom.png",outTitle.c_str()));
      c1->SaveAs(Form("img/%s_Zoom.pdf",outTitle.c_str()));
      c1->SaveAs(Form("img/%s_Zoom.C",outTitle.c_str()));
    }
  }else{
    if(doFit){  
      c1->SaveAs(Form("img/%s_Fit.png",outTitle.c_str()));
      c1->SaveAs(Form("img/%s_Fit.pdf",outTitle.c_str()));
      c1->SaveAs(Form("img/%s_Fit.C",outTitle.c_str()));
    }else{
      c1->SaveAs(Form("img/%s.png",outTitle.c_str()));
      c1->SaveAs(Form("img/%s.pdf",outTitle.c_str()));
      c1->SaveAs(Form("img/%s.C",outTitle.c_str()));
    }
  }
}
void makeTH1Array(TCanvas * c1, TH1D ** eff, TH1D ** eff2, TH1D ** eff3, std::string yTitle, std::string outTitle){
  TLegend * l[6];
  for(int i = 0; i<6; i++){
    c1->cd(i+1);
    c1->cd(i+1)->SetLogx();
    eff[i]->SetMarkerStyle(8);
    eff[i]->SetMarkerColor(kBlack);
    eff[i]->SetLineColor(kBlack);
    eff[i]->GetXaxis()->SetTitle("p_{T}");
    eff[i]->GetYaxis()->SetTitle(yTitle.c_str());
    
    eff2[i]->SetMarkerStyle(24);
    eff2[i]->SetMarkerColor(kBlue);
    eff2[i]->SetLineColor(kBlue);
    
    eff3[i]->SetMarkerStyle(34);
    eff3[i]->SetMarkerColor(kRed);
    eff3[i]->SetLineColor(kRed);
 
    if(strcmp(yTitle.c_str(),"efficiency")==0) eff[i]->GetYaxis()->SetRangeUser(0,1.2);
    if(strcmp(yTitle.c_str(),"misreconstruction rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.35);
    if(strcmp(yTitle.c_str(),"secondary rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.01);
    if(strcmp(yTitle.c_str(),"multiple reco rate")==0) eff[i]->GetYaxis()->SetRangeUser(0,0.0001);
 
    eff[i]->Draw();
    eff2[i]->Draw("same");
    eff3[i]->Draw("same");
    l[i] = new TLegend(0.1,0.7,0.7,0.89);
    l[i]->SetBorderSize(0);
    l[i]->SetFillStyle(0);
    if(i==0) l[i]->AddEntry((TObject*)0,"0-5%","");
    if(i==1) l[i]->AddEntry((TObject*)0,"5-10%","");
    if(i==2) l[i]->AddEntry((TObject*)0,"10-30%","");
    if(i==3) l[i]->AddEntry((TObject*)0,"30-50%","");
    if(i==4) l[i]->AddEntry((TObject*)0,"50-70%","");
    if(i==5) l[i]->AddEntry((TObject*)0,"70-100%","");
    l[i]->AddEntry((TObject*)0,"Analysis Cuts","");
    l[i]->AddEntry(eff[i],"Hydjet MB","p");
    l[i]->AddEntry(eff2[i],"EPOS MB","p");
    l[i]->AddEntry(eff3[i],"Pythia+Hydjet","p");
    l[i]->Draw("same");
  }
  c1->SaveAs(Form("img/%s.png",outTitle.c_str()));
  c1->SaveAs(Form("img/%s.pdf",outTitle.c_str()));
  c1->SaveAs(Form("img/%s.C",outTitle.c_str()));
}


void trkCorrPlots(){
  TFile * f1 = TFile::Open("trkCorr_Hydjet_Feb26.root","read");
  TFile * f2 = TFile::Open("trkCorr_EPOS_Feb26.root","read");
  TFile * f3 = TFile::Open("trkCorr_Pythia_March5.root","read");
  gStyle->SetOptStat(0);

  TGraphAsymmErrors * efficiency[6], *fake[6], *secondary[6];
  TGraphAsymmErrors * efficiency2[6], *fake2[6], *secondary2[6];
  TGraphAsymmErrors * efficiency3[6], *fake3[6], *secondary3[6];
  TH1D * multiple[6], * multiple2[6], * multiple3[6];
  for(int c = 0; c<6; c++){
    efficiency[c] = (TGraphAsymmErrors*)f1->Get(Form("effGraph_%d",c));  
    fake[c] = (TGraphAsymmErrors*)f1->Get(Form("fakeGraph_%d",c));  
    secondary[c] = (TGraphAsymmErrors*)f1->Get(Form("secGraph_%d",c));  
    multiple[c] = (TH1D*)f1->Get(Form("multiple_%d",c));  
    
    efficiency2[c] = (TGraphAsymmErrors*)f2->Get(Form("effGraph_%d",c));  
    fake2[c] = (TGraphAsymmErrors*)f2->Get(Form("fakeGraph_%d",c));  
    secondary2[c] = (TGraphAsymmErrors*)f2->Get(Form("secGraph_%d",c));  
    multiple2[c] = (TH1D*)f2->Get(Form("multiple_%d",c));  
    
    efficiency3[c] = (TGraphAsymmErrors*)f3->Get(Form("effGraph_%d",c));  
    fake3[c] = (TGraphAsymmErrors*)f3->Get(Form("fakeGraph_%d",c));  
    secondary3[c] = (TGraphAsymmErrors*)f3->Get(Form("secGraph_%d",c));  
    multiple3[c] = (TH1D*)f3->Get(Form("multiple_%d",c));  
  }

  TF1 * effFit[6], *fakeFit[6], *secFit[6];
  for(c = 0; c<6; c++){
    effFit[c] = (TF1*)f3->Get(Form("effFit_%d",c));
    fakeFit[c] = (TF1*)f3->Get(Form("fakeFit_%d",c));
    secFit[c] = (TF1*)f3->Get(Form("secFit_%d",c));
  }

  TCanvas * c1 = new TCanvas("c1","c1",1000,1300);
  c1->Divide(2,3);

  makeTGraphArray(c1, efficiency, efficiency2, efficiency3, "efficiency","efficiency", effFit);
  makeTGraphArray(c1, fake, fake2, fake3, "misreconstruction rate","fake", fakeFit);
  makeTGraphArray(c1, secondary, secondary2, secondary3, "secondary rate","secondary",secFit);
  makeTGraphArray(c1, efficiency, efficiency2, efficiency3, "efficiency","efficiency",effFit,false,true);
  makeTGraphArray(c1, fake, fake2, fake3, "misreconstruction rate","fake",effFit,false,true);
  makeTGraphArray(c1, secondary, secondary2, secondary3, "secondary rate","secondary",fakeFit,false,true);
  makeTH1Array(c1, multiple, multiple2, multiple3, "multiple reco rate","multiple");
  
  makeTGraphArray(c1, efficiency, efficiency2, efficiency3, "efficiency","efficiency",effFit,true,false);
  makeTGraphArray(c1, efficiency, efficiency2, efficiency3, "efficiency","efficiency",effFit,true,true);
  makeTGraphArray(c1, fake, fake2, fake3, "misreconstruction rate","fake",fakeFit,true,false);
  makeTGraphArray(c1, fake, fake2, fake3, "misreconstruction rate","fake",fakeFit,true,true);
  makeTGraphArray(c1, secondary, secondary2, secondary3, "secondary rate","secondary",secFit,true,true);
  makeTGraphArray(c1, secondary, secondary2, secondary3, "secondary rate","secondary",secFit,true,false);


  setTDRStyle();
  TCanvas * c2 = new TCanvas("c2","c2",800,700);
  c2->SetLogx();
  c2->SetTickx(1);
  c2->SetTicky(1);
  TH1D * dummy = new TH1D("dummy","",10,0.5,103.6);
  dummy->GetXaxis()->SetTitle("p_{T} (GeV)");
  dummy->GetXaxis()->CenterTitle();
  dummy->GetYaxis()->SetTitle("XeXe Tracking Efficiency");
  dummy->GetYaxis()->CenterTitle();
  dummy->GetYaxis()->SetRangeUser(0,1);
  dummy->GetYaxis()->SetTitleOffset(1.2);
  dummy->Draw();
  TH1D * efficiencySmooth[6];
  for(int i = 0; i<6; i++){
    efficiencySmooth[i] = (TH1D*)f3->Get(Form("efficiency_smooth_%d",i));
    if(i==0) efficiencySmooth[i]->SetLineColor(kBlack);
    if(i==1) efficiencySmooth[i]->SetLineColor(kBlack);
    if(i==2) efficiencySmooth[i]->SetLineColor(kBlue);
    if(i==3) efficiencySmooth[i]->SetLineColor(kBlue);
    if(i==4) efficiencySmooth[i]->SetLineColor(kRed);
    if(i==5) efficiencySmooth[i]->SetLineColor(kRed);
    if(i==1 || i==3 || i==5) efficiencySmooth[i]->SetLineStyle(3);
    efficiencySmooth[i]->SetLineWidth(2);
    efficiencySmooth[i]->SetMarkerStyle(1);
    efficiencySmooth[i]->Draw("same C");
  } 
  TLegend * trkEffLeg = new TLegend(0.3,0.15,0.85,0.6);
  trkEffLeg->AddEntry((TObject*)0,"|#eta|<1",""); 
  trkEffLeg->AddEntry((TObject*)0,"Pythia 8 + Hydjet",""); 
  trkEffLeg->AddEntry(efficiencySmooth[0],"0-5%","l"); 
  trkEffLeg->AddEntry(efficiencySmooth[1],"5-10%","l"); 
  trkEffLeg->AddEntry(efficiencySmooth[2],"10-30%","l"); 
  trkEffLeg->AddEntry(efficiencySmooth[3],"30-50%","l"); 
  trkEffLeg->AddEntry(efficiencySmooth[4],"50-70%","l"); 
  trkEffLeg->AddEntry(efficiencySmooth[5],"70-100%","l"); 
  trkEffLeg->SetBorderSize(0);
  trkEffLeg->Draw("same");
  
  setTDRStyle();
  int iPeriod = 0;
  lumi_sqrtS = "";
  writeExtraText = true;  
  extraText  = "Preliminary";
  //extraText  = "Unpublished";
  CMS_lumi( c2, iPeriod, 11 );

  c2->SaveAs("img/effFitsStacked.png");
  c2->SaveAs("img/effFitsStacked.pdf");
  c2->SaveAs("img/effFitsStacked.C");

  
  speciesCorrPlots();
}


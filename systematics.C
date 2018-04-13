#include "Settings.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "include/isRelevant.h"
#include "include/trackingCorrection.h"
#include "include/trackingDataMCDiffUncert.h"

void modErrorsForCorrelation(TH1D * division, TH1D* a, TH1D * b, int larger = 1){
  for(int i = 1; i<division->GetSize()-2; i++){
    float error2 = TMath::Power(a->GetBinError(i)/a->GetBinContent(i),2) + TMath::Power(b->GetBinError(i)/b->GetBinContent(i),2);
    if(larger ==1){
      error2 -= 2*TMath::Power(a->GetBinError(i),2)/a->GetBinContent(i)/b->GetBinContent(i);
    }
    if(larger==2) {
      error2 -= 2*TMath::Power(b->GetBinError(i),2)/a->GetBinContent(i)/b->GetBinContent(i);
    }   
 
    if(error2<0){
      if(larger ==1){
        error2 += 2*TMath::Power(a->GetBinError(i),2)/a->GetBinContent(i)/b->GetBinContent(i);
        error2 -= 2*TMath::Power(b->GetBinError(i),2)/a->GetBinContent(i)/b->GetBinContent(i);
      }
      if(larger ==2) {
        error2 += 2*TMath::Power(b->GetBinError(i),2)/a->GetBinContent(i)/b->GetBinContent(i);
        error2 -= 2*TMath::Power(a->GetBinError(i),2)/a->GetBinContent(i)/b->GetBinContent(i);
      }   
    }
    if(error2<0) error2 = TMath::Power(a->GetBinError(i)/a->GetBinContent(i),2) + TMath::Power(b->GetBinError(i)/b->GetBinContent(i),2);

    division->SetBinError(i,TMath::Sqrt(error2)*division->GetBinContent(i));
  }
}

void plotRXP(TH1D * h1, TH1D * h2, TH1D * h3, TH1D * h4, TH1D * h5, TH1D * h6, TH1D * h7, TH1D * h8, TH1D * h9, TH1D * h10, int c, Settings s){
  if(!isRelevent(c)) return;
  TCanvas * c1 = new TCanvas("c1","",1100,500);
  c1->Divide(2,1);
  c1->cd(1);
  c1->cd(1)->SetLogx();
  h1->GetXaxis()->SetRangeUser(0.7,120); 
  h1->GetXaxis()->SetTitle("p_{T}"); 
  //h1->GetYaxis()->SetRangeUser(0,0.4); 
  h1->GetYaxis()->SetTitle("Systematic Uncertainty"); 
  h1->GetYaxis()->SetTitleOffset(1.3); 
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  h1->Draw("L");
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->Draw("same L");
  h3->SetLineColor(kBlue);
  h3->SetLineWidth(2);
  h3->Draw("same L");
  h4->SetLineColor(kViolet);
  h4->SetLineWidth(2);
  h4->Draw("same L");
  h5->SetLineColor(kTeal);
  h5->SetLineWidth(2);
  h5->SetLineStyle(2);
  h5->Draw("same L");
  h6->SetLineColor(kGreen);
  h6->SetLineWidth(2);
  //h6->Draw("same L");
  h7->SetLineColor(kGray+2);
  h7->SetLineWidth(2);
  h7->Draw("same L");
  h8->SetLineColor(kOrange);
  h8->SetLineWidth(2);
  h8->Draw("same L");
  h9->SetLineColor(kMagenta-4);
  h9->SetLineWidth(2);
  h9->SetLineStyle(2);
  h9->Draw("same L");
  h10->SetLineColor(kYellow+1);
  h10->SetLineWidth(2);
  h10->Draw("same L");
  c1->cd(2);
  TLegend * l = new TLegend(0.1,0.1,0.9,0.9);
  l->SetBorderSize(0);
  l->AddEntry((TObject*)0,"R^{Xe}_{Pb} Uncertainties","");
  l->AddEntry((TObject*)0,Form("%d-%d %%",5*s.lowCentBin[c],5*s.highCentBin[c]),"");
  l->AddEntry(h1,"Total Uncertainty","l");
  l->AddEntry(h2,"Species Correction","l");
  l->AddEntry(h3,"Xe Misreconstruction","l");
  l->AddEntry(h4,"Xe Efficiency Method","l");
  l->AddEntry(h5,"Xe Track Selection","l");
  //l->AddEntry(h6,"Xe Event Selection","l");
  l->AddEntry(h7,"Pb Misreconstruction","l");
  l->AddEntry(h8,"Pb Efficiency Method","l");
  l->AddEntry(h9,"Pb Track Selection","l");
  l->AddEntry(h10,"Pb Trigger Combination","l");
  l->AddEntry((TObject*)0,"Pb uncertainties from HIN-15-015 tables.","");
  l->Draw("same");
  c1->SaveAs(Form("systPlots/RXPSystematics_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/RXPSystematics_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/RXPSystematics_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c]));
  delete c1;
  delete l;
}
void plotRAA(TH1D * h1, TH1D * h2, TH1D * h3, TH1D * h4, TH1D * h5, TH1D * h6, TH1D * h7, TH1D * h8, TH1D * h9, int c, Settings s){
  if(!isRelevent(c)) return;
  TCanvas * c1 = new TCanvas("c1","",1100,500);
  c1->Divide(2,1);
  c1->cd(1);
  c1->cd(1)->SetLogx();
  h1->GetXaxis()->SetRangeUser(0.5,120); 
  h1->GetXaxis()->SetTitle("p_{T}"); 
  //h1->GetYaxis()->SetRangeUser(0,0.4); 
  h1->GetYaxis()->SetTitle("Systematic Uncertainty"); 
  h1->GetYaxis()->SetTitleOffset(1.3); 
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  h1->Draw("L");
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->Draw("same L");
  h3->SetLineColor(kBlue);
  h3->SetLineWidth(2);
  h3->Draw("same L");
  h4->SetLineColor(kViolet);
  h4->SetLineWidth(2);
  h4->SetLineStyle(2);
  h4->Draw("same L");
  h5->SetLineColor(kTeal);
  h5->SetLineWidth(2);
  h5->Draw("same L");
  h6->SetLineColor(kGreen);
  h6->SetLineWidth(2);
  h6->Draw("same L");
  h7->SetLineColor(kGray);
  h7->SetLineStyle(2);
  h7->SetLineWidth(2);
  h7->Draw("same L");
  h8->SetLineColor(kOrange);
  h8->SetLineWidth(2);
  //h8->Draw("same L");
  h9->SetLineColor(kMagenta-4);
  h9->SetLineWidth(2);
  h9->Draw("same L");
  c1->cd(2);
  TLegend * l = new TLegend(0.1,0.1,0.9,0.9);
  l->SetBorderSize(0);
  l->AddEntry((TObject*)0,"RAA* Uncertainties","");
  l->AddEntry((TObject*)0,Form("%d-%d %%",5*s.lowCentBin[c],5*s.highCentBin[c]),"");
  l->AddEntry(h1,"Total Uncertainty","l");
  l->AddEntry(h2,"Species Correction","l");
  l->AddEntry(h3,"Misreconstruction","l");
  l->AddEntry(h4,"Efficiency Method","l");
  l->AddEntry(h5,"Resolution","l");
  l->AddEntry(h6,"Data vs. MC Efficiency","l");
  l->AddEntry(h7,"Track Selection","l");
  //l->AddEntry(h8,"Event Selection","l");
  l->AddEntry(h9,"pp Reference","l");
  l->AddEntry((TObject*)0,"Lumi. and partially-canceled uncerts removed from pp ref.","");
  l->Draw("same");
  c1->SaveAs(Form("systPlots/RAASystematics_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/RAASystematics_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/RAASystematics_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c]));
  delete c1;
  delete l;
}
void plotSpec(TH1D * h1, TH1D * h2, TH1D * h3, TH1D * h4, TH1D * h5, TH1D * h6, TH1D * h7, TH1D * h8, int c, Settings s){
  if(!isRelevent(c)) return;
  TCanvas * c1 = new TCanvas("c1","",1100,500);
  c1->Divide(2,1);
  c1->cd(1);
  c1->cd(1)->SetLogx();
  h1->GetXaxis()->SetRangeUser(0.5,120); 
  h1->GetXaxis()->SetTitle("p_{T}"); 
  //h1->GetYaxis()->SetRangeUser(0,0.4); 
  h1->GetYaxis()->SetTitle("Systematic Uncertainty"); 
  h1->GetYaxis()->SetTitleOffset(1.3); 
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  h1->Draw("L");
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->Draw("same L");
  h3->SetLineColor(kBlue);
  h3->SetLineWidth(2);
  h3->Draw("same L");
  h4->SetLineColor(kViolet);
  h4->SetLineWidth(2);
  h4->SetLineStyle(2);
  h4->Draw("same L");
  h5->SetLineColor(kTeal);
  h5->SetLineWidth(2);
  h5->Draw("same L");
  h6->SetLineColor(kGreen);
  h6->SetLineWidth(2);
  h6->Draw("same L");
  h7->SetLineColor(kGray);
  h7->SetLineStyle(2);
  h7->SetLineWidth(2);
  h7->Draw("same L");
  h8->SetLineColor(kOrange);
  h8->SetLineWidth(2);
  //h8->Draw("same L");
  c1->cd(2);
  TLegend * l = new TLegend(0.1,0.1,0.9,0.9);
  l->SetBorderSize(0);
  l->AddEntry((TObject*)0,"XeXe Spectra Uncertainties","");
  l->AddEntry((TObject*)0,Form("%d-%d %%",5*s.lowCentBin[c],5*s.highCentBin[c]),"");
  l->AddEntry(h1,"Total Uncertainty","l");
  l->AddEntry(h2,"Species Correction","l");
  l->AddEntry(h3,"Misreconstruction","l");
  l->AddEntry(h4,"Efficiency Method","l");
  l->AddEntry(h5,"Resolution","l");
  l->AddEntry(h6,"Data vs. MC Efficiency","l");
  l->AddEntry(h7,"Track Selection","l");
  //l->AddEntry(h8,"Event Selection","l");
  l->Draw("same");
  c1->SaveAs(Form("systPlots/SpectraSystematics_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/SpectraSystematics_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/SpectraSystematics_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c]));
  delete c1;
  delete l;
}

float PbFiniteMCStats(int c, int i){
  if(c==24 || c==25 || c==30){//30-50,50-70,70-90
    if(i>23){
      return 0.03;
    }else if(i>21){
      return 0.04;
    }else if(i>19){
      return 0.02;
    }else if(i>14){
      return 0.01;  
    }
  }else{
    if(i>27 && c!=23){
      return 0.04;
    }else if(i>21 && c!=23){
      return 0.045;
    }else if(i>16){
      return 0.01;
    }

    if(i>23 && c==23){
      return 0.035;
    }else if(i>21 && c==23){
      return 0.04;
    }
  }
  return 0;
}

void plotCutRatios(TH1D * h1, TH1D * h2, TH1D * h3, int c, Settings s){
  if(!isRelevent(c)) return;
  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  TLegend * l = new TLegend(0.3,0.1,0.8,0.35);
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  c1->SetLogx();
  gStyle->SetOptStat(0);
  //h1->SetTitle("");
  //h1->GetYaxis()->SetRangeUser(0.7,1.3);
  //h1->GetYaxis()->SetTitle("Modified Cuts/Nominal Result");
  //h1->GetXaxis()->SetTitle("p_{T}");
  //h1->SetMarkerStyle(8);
  //h1->SetLineColor(kBlack);
  //h1->SetMarkerColor(kBlack);
  h2->SetTitle("");
  h2->GetYaxis()->SetRangeUser(0.7,1.3);
  h2->GetYaxis()->SetTitle("Modified Cuts/Nominal Result");
  h2->GetXaxis()->SetTitle("p_{T}");
  h2->SetMarkerStyle(24);
  h2->SetLineColor(kRed);
  h2->SetMarkerColor(kRed);
  h3->SetMarkerStyle(25);
  h3->SetLineColor(kBlue);
  h3->SetMarkerColor(kBlue);
  //h1->Draw();
  h2->Draw("same");
  h2->Draw();
  h3->Draw("same");
  l->AddEntry((TObject*)0,Form("%d-%d %%",5*s.lowCentBin[c],5*s.highCentBin[c]),"");
  l->AddEntry(h2,"Selection E","p");
  l->AddEntry(h3,"Selection D","p");
  //l->AddEntry(h1,"Selection F","p");
  l->Draw("same");
  c1->SaveAs(Form("systPlots/CutRatios_%d_%d.pdf",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/CutRatios_%d_%d.png",5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/CutRatios_%d_%d.C",5*s.lowCentBin[c],5*s.highCentBin[c]));
  delete c1;
  delete l;
}
void plotEvtSelRatios(TH1D * h1, int c, Settings s, TF1 * f ,std::string name,std::string Filename){
  if(!isRelevent(c)) return;
  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  TLegend * l = new TLegend(0.2,0.2,0.5,0.5);
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  c1->SetLogx();
  gStyle->SetOptStat(0);
  h1->GetYaxis()->SetRangeUser(0,2);
  h1->GetYaxis()->SetTitle("Modified/Nominal Result");
  h1->GetXaxis()->SetTitle("p_{T}");
  h1->SetMarkerStyle(8);
  h1->SetLineColor(kBlack);
  h1->SetMarkerColor(kBlack);
  h1->Draw();
  l->AddEntry((TObject*)0,Form("%d-%d %%",5*s.lowCentBin[c],5*s.highCentBin[c]),"");
  l->AddEntry((TObject*)0,Form("%s",name.c_str()),"");
  l->Draw("same");
  f->Draw("same");
  c1->SaveAs(Form("systPlots/%s_%d_%d.pdf",Filename.c_str(),5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/%s_%d_%d.png",Filename.c_str(),5*s.lowCentBin[c],5*s.highCentBin[c]));
  c1->SaveAs(Form("systPlots/%s_%d_%d.C",Filename.c_str(),5*s.lowCentBin[c],5*s.highCentBin[c]));
  delete c1;
}

void systematics(){
  TH1::SetDefaultSumw2();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  Settings s = Settings();
  TFile * ppInput = new TFile(s.ppRefFile.c_str(),"read");
  TH1D * ppSyst_NoLumi = (TH1D*)ppInput->Get("ppScaledSyst_NoLumi");
  TH1D * ppSyst = (TH1D*)ppInput->Get("ppScaledSyst");
 
  TFile * evtSelFile = new TFile("output_Feb26_100percenteff.root","read");
  TH1D * evtSelVar1[s.nCentBins];
  TF1 * evtSelVar1Fit[s.nCentBins];
  TH1D * nVtx_evtSelVar1 = (TH1D*)evtSelFile->Get("nVtxMoreBin");
  for(int c = 0; c<s.nCentBins; c++){

   //FIXME
   if(c==20) evtSelVar1[c] = (TH1D*) evtSelFile->Get(Form("HI_0_100",5*s.lowCentBin[c],5*s.highCentBin[c]));
   //FIXME
    else evtSelVar1[c] = (TH1D*) evtSelFile->Get(Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    
    evtSelVar1[c]->Scale(1.0/nVtx_evtSelVar1->GetBinContent(nVtx_evtSelVar1->GetXaxis()->FindBin(c)));
  }

  TFile * fakeSyst = new TFile("fakeRateSyst/fakeSyst.root","read");
  TH1D * fakeSyst_h[8];
  for(int i = 0; i<8; i++){
    fakeSyst_h[i] = (TH1D*)fakeSyst->Get(Form("uncert_%d",i));
  }

  TFile * input = new TFile("output_0.root","read");
  TH1D * nVtx_input = (TH1D*)input->Get("nVtxMoreBin");
  for(int c = 0; c<s.nCentBins; c++){
    s.HI[c] = (TH1D*)input->Get(Form("HI_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_UpSpecCorr[c] = (TH1D*)input->Get(Form("HI_UpSpecCorr_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_UpSpecCorr[c]->Divide(s.HI[c]);
    s.HI_UpSpecCorr[c]->Print("All");
    s.HI_UpFakeCorr[c] = (TH1D*)input->Get(Form("HI_UpFakeCorr_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_UpFakeCorr[c]->Divide(s.HI[c]);

    s.HI_NoSpec[c] = (TH1D*)input->Get(Form("HI_NoSpec_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut1[c] = (TH1D*)input->Get(Form("HI_NoSpecCut1_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut1_copy[c] = (TH1D*)input->Get(Form("HI_NoSpecCut1_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut1[c]->Divide(s.HI_NoSpec[c]);
    s.HI_NoSpecCut2[c] = (TH1D*)input->Get(Form("HI_NoSpecCut2_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut2_copy[c] = (TH1D*)input->Get(Form("HI_NoSpecCut2_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut2[c]->Divide(s.HI_NoSpec[c]);
    s.HI_NoSpecCut3[c] = (TH1D*)input->Get(Form("HI_NoSpecCut3_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut3_copy[c] = (TH1D*)input->Get(Form("HI_NoSpecCut3_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpecCut3[c]->Divide(s.HI_NoSpec[c]);
    s.HI_NoSpec_EffUp1Sig[c] = (TH1D*)input->Get(Form("HI_NoSpec_EffUp1Sig_%d_%d",5*s.lowCentBin[c],5*s.highCentBin[c]));
    s.HI_NoSpec_EffUp1Sig[c]->Divide(s.HI_NoSpec[c]);

    //modify errors for correlation
    modErrorsForCorrelation(s.HI_NoSpecCut1[c],s.HI_NoSpecCut1_copy[c], s.HI_NoSpec[c],1);
    modErrorsForCorrelation(s.HI_NoSpecCut2[c],s.HI_NoSpecCut2_copy[c], s.HI_NoSpec[c],2);
    modErrorsForCorrelation(s.HI_NoSpecCut3[c],s.HI_NoSpecCut3_copy[c], s.HI_NoSpec[c],1);
    std::cout << "modified Errors" << std::endl;
    s.HI_NoSpecCut2[c]->Print("All");
    s.HI_NoSpecCut3[c]->Print("All");

    //finish fixing evt sel comparison
    evtSelVar1Fit[c] = new TF1(Form("evtSelVar1Fit_%d",c),"[0]",0.7,8);
    evtSelVar1[c]->Scale(nVtx_input->GetBinContent(nVtx_input->GetXaxis()->FindBin(c)));
    evtSelVar1[c]->Divide(s.HI[c]);
    evtSelVar1[c]->Fit(Form("evtSelVar1Fit_%d",c),"REM0");
    evtSelVar1[c]->SetLineColor(kRed);
    evtSelVar1[c]->SetLineWidth(2);
  }

  TFile * output = new TFile("systematics.root","recreate");
  for(int c = 0; c<s.nCentBins; c++){
    s.HI_NoSpecCut1[c]->SetDirectory(output);
    s.HI_NoSpecCut2[c]->SetDirectory(output);
    s.HI_NoSpecCut3[c]->SetDirectory(output);
    plotCutRatios(s.HI_NoSpecCut1[c],s.HI_NoSpecCut2[c],s.HI_NoSpecCut3[c],c,s);

    evtSelVar1[c]->SetDirectory(output);
    plotEvtSelRatios(evtSelVar1[c],c,s,evtSelVar1Fit[c],"100%% Eff Assumption","100PercentEff");
  }
  ppSyst_NoLumi->SetDirectory(output);
  //ppSyst_NoLumi->Write();
  ppSyst->SetDirectory(output);
  //ppSyst->Write();

  //definitions
  TH1D * spec_reso[s.nCentBins]; 
  TH1D * spec_MCvsDataEff[s.nCentBins]; 
  TH1D * spec_SpecCorr[s.nCentBins]; 
  TH1D * spec_FakeCorr[s.nCentBins]; 
  TH1D * spec_EffMethod[s.nCentBins]; 
  TH1D * spec_CutVariation[s.nCentBins]; 
  TH1D * spec_EventSelection[s.nCentBins];
  TH1D * spec_Total[s.nCentBins]; 

  TH1D * RAA_reso[s.nCentBins];
  TH1D * RAA_MCvsDataEff[s.nCentBins]; 
  TH1D * RAA_SpecCorr[s.nCentBins];
  TH1D * RAA_FakeCorr[s.nCentBins];  
  TH1D * RAA_EffMethod[s.nCentBins];  
  TH1D * RAA_CutVariation[s.nCentBins];  
  TH1D * RAA_EventSelection[s.nCentBins];
  TH1D * RAA_ppRef[s.nCentBins];
  TH1D * RAA_Total[s.nCentBins]; 
  
  TH1D * RXP_SpecCorr[s.nCentBins];
  TH1D * RXP_XeFakeCorr[s.nCentBins];  
  TH1D * RXP_XeEffMethod[s.nCentBins];  
  TH1D * RXP_XeCutVariation[s.nCentBins];  
  TH1D * RXP_PbFakeCorr[s.nCentBins];  
  TH1D * RXP_PbEffMethod[s.nCentBins];  
  TH1D * RXP_PbCutVariation[s.nCentBins];  
  TH1D * RXP_PbTrigger[s.nCentBins];  
  TH1D * RXP_EventSelection[s.nCentBins];
  TH1D * RXP_Total[s.nCentBins]; 

  for(int i = 0; i<s.nCentBins; i++){
    spec_reso[i] = new TH1D(Form("spec_reso_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_MCvsDataEff[i] = new TH1D(Form("spec_MCvsDataEff_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_SpecCorr[i] = new TH1D(Form("spec_specCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_FakeCorr[i] = new TH1D(Form("spec_fakeCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_EffMethod[i] = new TH1D(Form("spec_effMethod_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_CutVariation[i] = new TH1D(Form("spec_CutVariation_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_EventSelection[i] = new TH1D(Form("spec_EventSelection_%d",i),"",s.ntrkBins,s.xtrkbins);
    spec_Total[i] = new TH1D(Form("spec_Total_%d",i),"",s.ntrkBins,s.xtrkbins);
 
    RAA_reso[i]  = new TH1D(Form("RAA_reso_%d",i),"",s.ntrkBins,s.xtrkbins);
    RAA_MCvsDataEff[i] = new TH1D(Form("RAA_MCvsDataEff_%d",i),"",s.ntrkBins,s.xtrkbins); 
    RAA_SpecCorr[i] = new TH1D(Form("RAA_SpecCorr_%d",i),"",s.ntrkBins,s.xtrkbins); 
    RAA_FakeCorr[i]  = new TH1D(Form("RAA_FakeCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    RAA_EffMethod[i]  = new TH1D(Form("RAA_EffMethod_%d",i),"",s.ntrkBins,s.xtrkbins);
    RAA_CutVariation[i]  = new TH1D(Form("RAA_CutVariation_%d",i),"",s.ntrkBins,s.xtrkbins);
    RAA_EventSelection[i] = new TH1D(Form("RAA_EventSelection_%d",i),"",s.ntrkBins,s.xtrkbins);
    RAA_ppRef[i] = new TH1D(Form("RAA_ppRef_%d",i),"",s.ntrkBins,s.xtrkbins);
    RAA_Total[i] = new TH1D(Form("RAA_Total_%d",i),"",s.ntrkBins,s.xtrkbins);
  
    RXP_SpecCorr[i] = new TH1D(Form("RXP_SpecCorr_%d",i),"",s.ntrkBins,s.xtrkbins); 
    RXP_XeFakeCorr[i]  = new TH1D(Form("RXP_XeFakeCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_PbFakeCorr[i]  = new TH1D(Form("RXP_PbFakeCorr_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_XeEffMethod[i]  = new TH1D(Form("RXP_XeEffMethod_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_PbEffMethod[i]  = new TH1D(Form("RXP_PbEffMethod_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_XeCutVariation[i]  = new TH1D(Form("RXP_XeCutVariation_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_PbCutVariation[i]  = new TH1D(Form("RXP_PbCutVariation_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_PbTrigger[i]  = new TH1D(Form("RXP_PbTrigger_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_EventSelection[i] = new TH1D(Form("RXP_EventSelection_%d",i),"",s.ntrkBins,s.xtrkbins);
    RXP_Total[i] = new TH1D(Form("RXP_Total_%d",i),"",s.ntrkBins,s.xtrkbins);
  }  

  //spectra
  for(int i = 0; i<s.nCentBins; i++){
    for(int j = 1; j<s.ntrkBins+1; j++){
      double total2 = 0; 
      //species correction
      if(s.HI[i]->GetBinContent(j)==0) continue;
      spec_SpecCorr[i]->SetBinContent(j,TMath::Abs(s.HI_UpSpecCorr[i]->GetBinContent(j)-1));
      total2 += TMath::Power(s.HI_UpSpecCorr[i]->GetBinContent(j)-1,2);

      //fake correction - use fake value for high pt, use calculated uncert at low pt
      spec_FakeCorr[i]->SetBinContent(j,TMath::Abs(s.HI_UpFakeCorr[i]->GetBinContent(j)-1));
      if(spec_FakeCorr[i]->GetBinCenter(j) < 4){
        if(i==0 || i==1 || i== 23 || i==24 || i==25 || i==30 || i==20 || i==31){
          int cc = i;
          if(i==23) cc=2;
          if(i==24) cc=3;
          if(i==25) cc=4;
          if(i==30) cc=5;
          if(i==31) cc=6;
          if(i==20) cc=7;
          spec_FakeCorr[i]->SetBinContent(j,fakeSyst_h[cc]->GetBinContent(j));
        }
      }
      total2 += TMath::Power(spec_FakeCorr[i]->GetBinContent(j),2);
      
      //efficiency uncertainty from MC stats
      float effStat = s.HI_NoSpec_EffUp1Sig[i]->GetBinContent(j)-1;
      spec_EffMethod[i]->SetBinContent(j,effStat);
      total2 += TMath::Power(effStat,2);

      //resolution is a flat 0.5%
      spec_reso[i]->SetBinContent(j,0.005);
      total2 += 0.005*0.005;

      //data MC Diff is a flat 5%
      spec_MCvsDataEff[i]->SetBinContent(j,0.05);
      total2 += 0.05*0.05;
      
      //Syst from cut variations
      float tempSyst = (spec_CutVariation[i]->GetBinLowEdge(j)<20) ? 0.06 : 0.03;
      spec_CutVariation[i]->SetBinContent(j,tempSyst);
      total2 += TMath::Power(tempSyst,2);
      
      //Syst from event selections, just take the fit value for now
      spec_EventSelection[i]->SetBinContent(j,TMath::Abs(evtSelVar1Fit[i]->Eval(5)-1));
      //don't include evt selection uncert in total
      //total2 += TMath::Power(evtSelVar1Fit[i]->Eval(5)-1,2);

      //total
      spec_Total[i]->SetBinContent(j,TMath::Sqrt(total2));
    }
  plotSpec(spec_Total[i], spec_SpecCorr[i], spec_FakeCorr[i],  spec_EffMethod[i], spec_reso[i], spec_MCvsDataEff[i],  spec_CutVariation[i], spec_EventSelection[i], i, s); 
  }

  //RAA
  for(int i = 0; i<s.nCentBins; i++){
    for(int j = 1; j<s.ntrkBins+1; j++){
      double total2 = 0; 
      if(s.HI[i]->GetBinContent(j)==0) continue;
      //pp reference without lumi and with 4% pp data/MC Eff difference removed
      //also removed 1% resolution correction
      //note that the total2 thing is the square of a sqrt
      RAA_ppRef[i]->SetBinContent(j,TMath::Sqrt(TMath::Power(ppSyst_NoLumi->GetBinContent(j),2)-0.04*0.04-0.01*0.01));
      total2 += TMath::Power(ppSyst_NoLumi->GetBinContent(j),2)-0.04*0.04-0.01*0.01;

      //species corr
      RAA_SpecCorr[i]->SetBinContent(j,spec_SpecCorr[i]->GetBinContent(j));
      total2 += TMath::Power(spec_SpecCorr[i]->GetBinContent(j),2);
      
      //fake correction
      RAA_FakeCorr[i]->SetBinContent(j,spec_FakeCorr[i]->GetBinContent(j));
      total2 += TMath::Power(spec_FakeCorr[i]->GetBinContent(j),2);
      
      //efficiency uncertainty from MC stats
      RAA_EffMethod[i]->SetBinContent(j,spec_EffMethod[i]->GetBinContent(j));
      total2 += TMath::Power(spec_EffMethod[i]->GetBinContent(j),2);

      //resolution
      RAA_reso[i]->SetBinContent(j,0.005);
      total2 += TMath::Power(0.005,2);
      
      // MC vs data uncert assumed to cancle at least as well at PbPb 
      RAA_MCvsDataEff[i]->SetBinContent(j,trackingDataMCDiffUncert(RAA_MCvsDataEff[i]->GetBinCenter(j),s.lowCentBin[i]*5+1));
      total2 += TMath::Power(trackingDataMCDiffUncert(RAA_MCvsDataEff[i]->GetBinCenter(j),s.lowCentBin[i]*5+1),2);
      
      //Syst from cut variations
      RAA_CutVariation[i]->SetBinContent(j,spec_CutVariation[i]->GetBinContent(j));
      total2 += TMath::Power(spec_CutVariation[i]->GetBinContent(j),2);
      
      //Syst from eventSelection
      RAA_EventSelection[i]->SetBinContent(j,spec_EventSelection[i]->GetBinContent(j));
      //don't include event selection uncer in total
      //total2 += TMath::Power(spec_EventSelection[i]->GetBinContent(j),2);

      //total
      RAA_Total[i]->SetBinContent(j,TMath::Sqrt(total2));
    }
  plotRAA(RAA_Total[i], RAA_SpecCorr[i], RAA_FakeCorr[i],  RAA_EffMethod[i], RAA_reso[i], RAA_MCvsDataEff[i],  RAA_CutVariation[i], RAA_EventSelection[i], RAA_ppRef[i] , i, s); 
  }

  //RXePb
  for(int i = 0; i<s.nCentBins; i++){
    if(i!=0 && i!=1 && i!= 23 && i!=24 && i!= 25 && i!=30) continue;
    TFile * hyperon = TFile::Open(Form("Pbsystematics/HyperonFractions_%d_%d.root",5*s.lowCentBin[i],(i==30) ? 90 : 5*s.highCentBin[i]),"read");
    TH1D * hyperonCorr = (TH1D*)hyperon->Get("netSyst");
    TFile * trigger = TFile::Open("Pbsystematics/Spectra_ForPaper_Aug12.root","read");
    TH1D * TriggerUncert = (TH1D*)trigger->Get(Form("h_HInormSyst_%d_%d",5*s.lowCentBin[i],(i==30) ? 90 : 5*s.highCentBin[i]));
    TFile * fakeFile = TFile::Open("Pbsystematics/Closure_PbPb.root","read");
    TH1D * PbPbFake = (TH1D*)fakeFile->Get("Fake_0");

    for(int j = 1; j<s.ntrkBins+1; j++){
      double total2 = 0;
      if(s.HI[i]->GetBinContent(j)==0) continue;
      float PbPbCorr = TMath::Max(hyperonCorr->GetBinContent(hyperonCorr->FindBin(RXP_SpecCorr[i]->GetBinCenter(j))),0.015);
      //fix high-pt region 
      if(PbPbCorr>0.3) PbPbCorr = 0.015;

      //stuff that doesn't inherit from above 
      //species corr
      RXP_SpecCorr[i]->SetBinContent(j,TMath::Abs(PbPbCorr-spec_SpecCorr[i]->GetBinContent(j)));
      total2 += TMath::Power(TMath::Abs(PbPbCorr-spec_SpecCorr[i]->GetBinContent(j)),2);
      
      //fake correction
      double Pbfake = PbPbFake->GetBinContent(PbPbFake->FindBin(RXP_PbFakeCorr[i]->GetBinCenter(j)));
      RXP_PbFakeCorr[i]->SetBinContent(j,Pbfake-1);
      total2 += TMath::Power(Pbfake-1,2);
      
      //Pb efficiency uncertinaty from MC stats
      RXP_PbEffMethod[i]->SetBinContent(j,PbFiniteMCStats(i,j));
      total2 += TMath::Power(PbFiniteMCStats(i,j),2);
      
      //Syst from cut variations
      RXP_PbCutVariation[i]->SetBinContent(j,0.04);
      total2 += 0.04*0.04;
      
      //Syst from PbPb trigger
      float triggerUncertTemp = TriggerUncert->GetBinContent(TriggerUncert->FindBin(RXP_PbTrigger[i]->GetBinCenter(j)));
      RXP_PbTrigger[i]->SetBinContent(j,triggerUncertTemp);
      total2 += TMath::Power(triggerUncertTemp,2);


      //inherits from above
      //Xeefficiency uncertainty from MC stats
      RXP_XeEffMethod[i]->SetBinContent(j,spec_EffMethod[i]->GetBinContent(j));
      total2 += TMath::Power(spec_EffMethod[i]->GetBinContent(j),2);
      
      //Syst from cut variations
      RXP_XeCutVariation[i]->SetBinContent(j,spec_CutVariation[i]->GetBinContent(j));
      total2 += TMath::Power(spec_CutVariation[i]->GetBinContent(j),2);
      
      //Syst from eventSelection
      RXP_EventSelection[i]->SetBinContent(j,spec_EventSelection[i]->GetBinContent(j));
      //don't include uncert in total
      //total2 += TMath::Power(spec_EventSelection[i]->GetBinContent(j),2);
      
      //fake correction
      RXP_XeFakeCorr[i]->SetBinContent(j,TMath::Abs(s.HI_UpFakeCorr[i]->GetBinContent(j)-1));
      total2 += TMath::Power(s.HI_UpFakeCorr[i]->GetBinContent(j)-1,2);   

      //total
      RXP_Total[i]->SetBinContent(j,TMath::Sqrt(total2));
    }
    plotRXP(RXP_Total[i], RXP_SpecCorr[i], RXP_XeFakeCorr[i],  RXP_XeEffMethod[i], RXP_XeCutVariation[i], RXP_EventSelection[i],  RXP_PbFakeCorr[i], RXP_PbEffMethod[i] , RXP_PbCutVariation[i] , RXP_PbTrigger[i] , i, s); 
    
    hyperon->Close();
    trigger->Close();
    fakeFile->Close();
  }
  output->Write(); 
}

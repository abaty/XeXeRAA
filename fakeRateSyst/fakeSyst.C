#include "TFile.h"
#include "TH1D.h"
#include "../Settings.h"

void fakeSyst(){
  TFile * d = TFile::Open("data.root","read");
  TFile * mc = TFile::Open("hydjet.root","read");

  Settings s = Settings();

  TH1D * dz_expanded[s.ntrkBins][8][4], * d0_expanded[s.ntrkBins][8][4];
  TH1D * uncert[8];
  for(int i = 0; i<8; i++) uncert[i] = new TH1D(Form("uncert_%d",i),"",s.ntrkBins,s.xtrkbins);
  
  for(int i = 0; i<s.ntrkBins; i++){
    for(int j = 0; j<8; j++){
      float integralsz = 0;
      float integrals0 = 0;
      for(int k = 0; k<4; k++){
        if(k==0) dz_expanded[i][j][k] = (TH1D*)d->Get(Form("dz_expanded_%d_%d",j,i));
        if(k!=0) dz_expanded[i][j][k] = (TH1D*)mc->Get(Form("dz_expanded_%d_%d_%d",j,i,k-1));
        if(k<2) integralsz = dz_expanded[i][j][k]->Integral(0,dz_expanded[i][j][k]->GetSize()-1);
        dz_expanded[i][j][k]->Scale(1./integralsz);
      
        if(k==0) d0_expanded[i][j][k] = (TH1D*)d->Get(Form("d0_expanded_%d_%d",j,i));
        if(k!=0) d0_expanded[i][j][k] = (TH1D*)mc->Get(Form("d0_expanded_%d_%d_%d",j,i,k-1));
        if(k<2) integrals0 = d0_expanded[i][j][k]->Integral(0,d0_expanded[i][j][k]->GetSize()-1);
        d0_expanded[i][j][k]->Scale(1./integrals0);
      }
      
      int binLL = dz_expanded[i][j][0]->FindBin(-30);
      int binL = dz_expanded[i][j][0]->FindBin(-20);
      int binH = dz_expanded[i][j][0]->FindBin(20);
      int binHH = dz_expanded[i][j][0]->FindBin(30);
 
      if(i>15) continue;

      /*float d_z_wide = dz_expanded[i][j][0]->Integral(binLL,binL)+ dz_expanded[i][j][0]->Integral(binH,binHH);
      std::cout << i << " " << j << " Data integral: " << d_z_wide << std::endl;
      
      float mc_z_wide = dz_expanded[i][j][1]->Integral(binLL,binL)+ dz_expanded[i][j][1]->Integral(binH,binHH);
      std::cout << i << " " << j << " MC integral: " << mc_z_wide << std::endl;
      float fake_z_wide = dz_expanded[i][j][3]->Integral(binLL,binL)+ dz_expanded[i][j][3]->Integral(binH,binHH);
      std::cout << i << " " << j << " MC fake integral: " << fake_z_wide << " Fraction: " << fake_z_wide/mc_z_wide << std::endl;
      float totalFakez = dz_expanded[i][j][3]->Integral(0,dz_expanded[i][j][3]->GetSize());
      float scalingFactorz = (1-totalFakez)/(fake_z_wide/d_z_wide-totalFakez);
      std::cout << scalingFactorz << std::endl;
      float oldFakeYieldz = dz_expanded[i][j][3]->Integral(dz_expanded[i][j][3]->FindBin(-3),dz_expanded[i][j][3]->FindBin(3));
      float scaledFakeYieldz = scalingFactorz*oldFakeYieldz;
      float scaledRealYieldz = dz_expanded[i][j][2]->Integral(dz_expanded[i][j][2]->FindBin(-3),dz_expanded[i][j][2]->FindBin(3));       std::cout << oldFakeYieldz/(oldFakeYieldz+scaledRealYieldz) << " " << scaledFakeYieldz/(scaledRealYieldz+scaledFakeYieldz) << std::endl;
      std::cout << "Percentage of old fake: " << (scaledFakeYieldz/(scaledRealYieldz+scaledFakeYieldz)/(oldFakeYieldz/(oldFakeYieldz+scaledRealYieldz)))-1 << std::endl;
      */

      float d_0_wide = d0_expanded[i][j][0]->Integral(binLL,binL)+ d0_expanded[i][j][0]->Integral(binH,binHH);
      std::cout << i << " " << j << " Data integral: " << d_0_wide << std::endl;
      
      float mc_0_wide = d0_expanded[i][j][1]->Integral(binLL,binL)+ d0_expanded[i][j][1]->Integral(binH,binHH);
      std::cout << i << " " << j << " MC integral: " << mc_0_wide << std::endl;
      float fake_0_wide = d0_expanded[i][j][3]->Integral(binLL,binL)+ d0_expanded[i][j][3]->Integral(binH,binHH);
      std::cout << i << " " << j << " MC fake integral: " << fake_0_wide << " Fraction: " << fake_0_wide/mc_0_wide << std::endl;
      float totalFake = d0_expanded[i][j][3]->Integral(0,d0_expanded[i][j][3]->GetSize());
      float scalingFactor0 = (1-totalFake)/(fake_0_wide/d_0_wide-totalFake);
      std::cout << scalingFactor0 << std::endl;
      float oldFakeYield = d0_expanded[i][j][3]->Integral(d0_expanded[i][j][3]->FindBin(-3),d0_expanded[i][j][3]->FindBin(3));
      float scaledFakeYield = scalingFactor0*oldFakeYield;
      float scaledRealYield = d0_expanded[i][j][2]->Integral(d0_expanded[i][j][2]->FindBin(-3),d0_expanded[i][j][2]->FindBin(3));       
      std::cout << oldFakeYield/(oldFakeYield+scaledRealYield) << " " << scaledFakeYield/(scaledRealYield+scaledFakeYield) << std::endl;
      std::cout << "Percentage of old fake: " << (scaledFakeYield/(scaledRealYield+scaledFakeYield)/(oldFakeYield/(oldFakeYield+scaledRealYield)))-1 << std::endl;
      std::cout << "Uncertainty: " << (1-(scaledFakeYield/(scaledRealYield+scaledFakeYield)))/(1-(oldFakeYield/(oldFakeYield+scaledRealYield))) - 1 << std::endl;
      uncert[j]->SetBinContent(i+1,TMath::Abs((1-(scaledFakeYield/(scaledRealYield+scaledFakeYield)))/(1-(oldFakeYield/(oldFakeYield+scaledRealYield))) - 1)); 


      TH1D * scaledFake = (TH1D*)d0_expanded[i][j][3]->Clone("temp");
      TH1D * scaledReal = (TH1D*)d0_expanded[i][j][2]->Clone("temp2");
      TH1D * scaledTotal = (TH1D*)d0_expanded[i][j][2]->Clone("temp3");
      scaledFake->Scale(scalingFactor0);
      scaledTotal->Add(scaledFake);
      float scale = scaledTotal->Integral(0,scaledTotal->GetSize());
      scaledTotal->Scale(1./scale);
      scaledFake->Scale(1./scale);
      scaledReal->Scale(1./scale);


      TCanvas * c1 = new TCanvas("c1","c1",600,600);
      gStyle->SetOptStat(0);
      c1->SetLogy();
      d0_expanded[i][j][0]->SetMarkerStyle(8);
      d0_expanded[i][j][0]->GetYaxis()->SetTitle("normalized to unity");
      d0_expanded[i][j][0]->GetYaxis()->SetTitleOffset(1.3);
      d0_expanded[i][j][0]->GetXaxis()->SetTitle("d0/#sigma_{d0}");
      d0_expanded[i][j][0]->SetMarkerColor(kBlack);
      d0_expanded[i][j][0]->GetYaxis()->SetRangeUser(0.000001,0.3);
      d0_expanded[i][j][0]->Draw();
      d0_expanded[i][j][1]->SetLineColor(kBlack);
      d0_expanded[i][j][1]->Draw("same HIST");
      d0_expanded[i][j][2]->SetLineColor(kRed);
      d0_expanded[i][j][2]->Draw("same HIST");
      d0_expanded[i][j][3]->SetLineColor(kBlue);
      d0_expanded[i][j][3]->Draw("same HIST");

      TLine * l = new TLine(-20,0.000001,-20,0.3);
      l->SetLineColor(4);
      l->SetLineStyle(2);
      l->DrawLine(20,0.000001,20,0.3);
      l->DrawLine(-20,0.000001,-20,0.3);

      l->SetLineColor(8);
      l->DrawLine(3,0.000001,3,0.3);
      l->DrawLine(-3,0.000001,-3,0.3);
  
      TLegend * leg = new TLegend(0.6,0.6,0.9,0.9);
      leg->AddEntry(d0_expanded[i][j][0],"Data","p");
      leg->AddEntry(d0_expanded[i][j][1],"Total MC","l");
      leg->AddEntry(d0_expanded[i][j][2],"Real MC","l");
      leg->AddEntry(d0_expanded[i][j][3],"Fake MC","l");
      int a = 0; int b = 5;
      if(j==1){a=5; b=10;}
      if(j==2){a=10; b=30;}
      if(j==3){a=30; b=50;}
      if(j==4){a=50; b=70;}
      if(j==5){a=70; b=90;}
      if(j==6){a=0; b=10;}
      if(j==7){a=0; b=100;}
      leg->AddEntry((TObject*)0,Form("%d-%d%%",a,b),"");
      leg->AddEntry((TObject*)0,Form("%.1f<p_{T}<%.1f",s.xtrkbins[i],s.xtrkbins[i+1]),"");

      leg->Draw("same");

      c1->SaveAs(Form("img/Unscaled_%d_%d.png",i,j));
      c1->SaveAs(Form("img/Unscaled_%d_%d.pdf",i,j));
      c1->SaveAs(Form("img/Unscaled_%d_%d.C",i,j));

      
      d0_expanded[i][j][0]->Draw();
      scaledTotal->SetLineColor(kBlack);
      scaledTotal->Draw("same HIST");
      scaledFake->SetLineColor(kBlue);
      scaledFake->Draw("same HIST"); 
      scaledReal->SetLineColor(kRed);
      scaledReal->Draw("same HIST");
      
      l->SetLineColor(4);
      l->SetLineStyle(2);
      l->DrawLine(20,0.000001,20,0.3);
      l->DrawLine(-20,0.000001,-20,0.3);

      l->SetLineColor(8);
      l->DrawLine(3,0.000001,3,0.3);
      l->DrawLine(-3,0.000001,-3,0.3);
     
      leg->AddEntry((TObject*)0,"After fake scaling",""); 
      leg->Draw("same");
      
      c1->SaveAs(Form("img/Scaled_%d_%d.png",i,j));
      c1->SaveAs(Form("img/Scaled_%d_%d.pdf",i,j));
      c1->SaveAs(Form("img/Scaled_%d_%d.C",i,j));


      delete c1;
      delete l;
      delete scaledFake;
      delete scaledReal;
      delete scaledTotal;
    }
  }



  for(int i = 0; i<8; i++) uncert[i]->Print("All");

  TCanvas * c1 = new TCanvas("c1","c1",600,600);
  for(int i = 0; i<8; i++){
    uncert[i]->GetXaxis()->SetRangeUser(0.5,4.0);
    uncert[i]->GetXaxis()->SetTitle("p_{T}");
    uncert[i]->GetYaxis()->SetTitle("Uncertainty");
    uncert[i]->GetYaxis()->SetTitleOffset(1.3);
    uncert[i]->GetYaxis()->SetRangeUser(0,0.2);
    uncert[i]->SetMarkerStyle(8);
    uncert[i]->Draw("HIST p");
      TLegend * leg = new TLegend(0.6,0.6,0.9,0.9);
      int a = 0; int b = 5;
      if(i==1){a=5; b=10;}
      if(i==2){a=10; b=30;}
      if(i==3){a=30; b=50;}
      if(i==4){a=50; b=70;}
      if(i==5){a=70; b=90;}
      if(i==6){a=0; b=10;}
      if(i==7){a=0; b=100;}
      leg->AddEntry((TObject*)0,Form("%d-%d%%",a,b),"");
      leg->Draw();
      c1->SaveAs(Form("img/uncert_%d.png",i));
      c1->SaveAs(Form("img/uncert_%d.pdf",i));
      c1->SaveAs(Form("img/uncert_%d.C",i)); 
      delete leg;
  }
  TFile * output = TFile::Open("fakeSyst.root","recreate");
  for(int i = 0; i<8; i++){
    uncert[i]->SetDirectory(output);
  }
  output->Write();
}

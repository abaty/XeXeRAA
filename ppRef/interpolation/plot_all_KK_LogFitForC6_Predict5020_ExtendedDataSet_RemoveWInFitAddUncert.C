//purpose: use the predicted 5.02 TeV result and try to predict a measured value
//I use the log-log pol2 equal weights fit function for this

#include "/net/hidsk0001/d00/scratch/krajczar/ppRefForpPb_PilotRun/interpolation_HIN10005_kk/divide_graph_by_function.C"
#include "/net/hidsk0001/d00/scratch/krajczar/ppRefForpPb_PilotRun/interpolation_HIN10005_kk/scale_graph.C"

void plot_all_KK_LogFitForC6_Predict5020_ExtendedDataSet_RemoveWInFitAddUncert(Bool_t xt=kTRUE, Float_t expo=4.9)
{
        SetStyle();
        gStyle->SetOptFile(0);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
 
        xt=kFALSE;

	//define dummy histogram and some style parameters
	TH1F *dum;
	if(xt) {
		dum = new TH1F("dum","",160,5e-4,0.3); 
		dum->SetMinimum(1e4);
		dum->SetMaximum(9e20);
		dum->SetTitle(Form(";x_{T};#sqrt{s}^{%0.1f}  E d^{3}#sigma/dp^{3}",expo));
	} else {
		dum = new TH1F("dum","",160,0,200.0);
		dum->SetMinimum(2e-12);
		dum->SetMaximum(5e2);
		dum->SetTitle(";p_{T} [GeV/c];E d^{3}#sigma/dp^{3}");
	}
	dum->SetLineWidth(0);
	dum->SetStats(0);
	dum->GetXaxis()->CenterTitle();
	dum->GetYaxis()->CenterTitle();
	dum->GetXaxis()->SetTitleSize(0.05);
	dum->GetYaxis()->SetTitleSize(0.05);
	dum->GetXaxis()->SetTitleOffset(1.17);
	dum->GetYaxis()->SetTitleOffset(1.3);

	gROOT->LoadMacro("/net/hidsk0001/d00/scratch/krajczar/ppRefForpPb_PilotRun/interpolation_HIN10005_kk/data_table_to_graph.C");

	//get 7 TeV points
	TGraphErrors *cms_7000_g = data_table_to_graph("cms",7000,xt,expo);
	cms_7000_g->SetMarkerColor(kBlack);
	
	TF1 *cms_7000_fit = new TF1("cms_7000_fit","[0]*pow(1.0+(x/[1]),[2])",2e-3,0.1);
	cms_7000_fit->SetLineWidth(1);
	cms_7000_fit->SetParameters(3e22,2.5e-4,-7);
	cms_7000_g->Fit(cms_7000_fit,"REMW0");
	
	//get 2.36 TeV points
//	TGraphErrors *cms_2360_g = data_table_to_graph("cms",2360,xt,expo);
//	cms_2360_g->SetMarkerColor(kMagenta+3);
	
//	TF1 *cms_2360_fit = new TF1("cms_2360_fit","[0]*pow(1.0+(x/[1]),[2])",2e-3,0.1);
//	cms_2360_fit->SetLineWidth(1);
//	cms_2360_fit->SetParameters(3e22,2.5e-4,-7);
//	cms_2360_g->Fit(cms_2360_fit,"REMW0");

	//get 2.76 TeV points (KK using existing txt files)
	TGraphErrors *cms_2760_g = data_table_to_graph("cms",2760,xt,expo);
	cms_2760_g->SetMarkerColor(kMagenta+3);
	TF1 *cms_2760_fit = new TF1("cms_2760_fit","[0]*pow(1.0+(x/[1]),[2])",2e-3,0.1);
	cms_2760_fit->SetLineWidth(1);
	cms_2760_fit->SetParameters(3e22,2.5e-4,-7);
	cms_2760_g->Fit(cms_2760_fit,"REMW0");
	
	//get 1.96 TeV points
	TGraphErrors *cdf_1960_g = data_table_to_graph("cdf",1960,xt,expo);
	cdf_1960_g->SetMarkerColor(kOrange-3);
	cdf_1960_g->SetMarkerStyle(30);
	
	//TGraphErrors *cdfold_1960_g = data_table_to_graph("cdfold",1960,xt);
	//cdfold_1960_g->SetMarkerColor(kBlue);
	//cdfold_1960_g->SetMarkerStyle(30);
	
	TF1 *cdf_1960_fit = new TF1("cdf_1960_fit","[0]*pow(1.0+(x/[1]),[2])",4e-3,0.1);
	cdf_1960_fit->SetLineColor(kOrange-3);
	cdf_1960_fit->SetLineWidth(1);
	cdf_1960_fit->SetParameters(3e22,2.5e-4,-7);
	cdf_1960_g->Fit(cdf_1960_fit,"REMW0");
	
	//get 1.8 TeV points
	TGraphErrors *cdf_1800_g = data_table_to_graph("cdf",1800,xt,expo);
	cdf_1800_g->SetMarkerColor(kGreen+3);
	cdf_1800_g->SetMarkerStyle(28);

	TF1 *cdf_1800_fit = new TF1("cdf_1800_fit","[0]*pow(1.0+(x/[1]),[2])",4e-3,0.1);
	cdf_1800_fit->SetLineColor(kGreen+3);
	cdf_1800_fit->SetLineWidth(1);
	cdf_1800_fit->SetParameters(3e22,2.5e-4,-7.2);
	cdf_1800_fit->FixParameter(2,-7.2);
	cdf_1800_g->Fit(cdf_1800_fit,"REMW0");
	
	//get 0.9 TeV points
	TGraphErrors *cms_900_g = data_table_to_graph("cms",900,xt,expo);
	cms_900_g->SetMarkerColor(kRed);
	
	TF1 *cms_900_fit = new TF1("cms_900_fit","[0]*pow(1.0+(x/[1]),[2])",9e-3,0.1);
	cms_900_fit->SetLineColor(kRed);
	cms_900_fit->SetLineWidth(1);
	cms_900_fit->SetParameters(3e22,2.5e-4,-7);
	cms_900_g->Fit(cms_900_fit,"REMW0");
	
//	TGraphErrors *ua1_900_g = data_table_to_graph("ua1",900,xt,expo);
//	ua1_900_g->SetMarkerColor(kCyan+1);
//	ua1_900_g->SetMarkerStyle(26);

	// get 0.63 TeV points
	TGraphErrors *cdf_630_g = data_table_to_graph("cdf",630,xt,expo);
	cdf_630_g->SetMarkerColor(kOrange+3);
	cdf_630_g->SetMarkerStyle(27);

	//draw graphs to canvas
	TCanvas *c1 = new TCanvas("c1","spectra interpolation",600,600);
	dum->Draw();
	cdf_1960_g->Draw("pz");
	//cdfold_1960_g->Draw("pz");
	cdf_1800_g->Draw("pz");
//	if(!xt) ua1_900_g->Draw("pz"); // abs(eta) within 2.5 changes high xt behavior
	cdf_630_g->Draw("pz");
	cms_900_g->Draw("pz");         // draw the CMS points on top
//	cms_2360_g->Draw("pz");
	cms_2760_g->Draw("pz"); //KK
	cms_7000_g->Draw("pz");

	//make legend
	TLegend *leg1 = new TLegend(0.2,0.21,0.50,0.51,"p+p(#bar{p})");
	leg1->SetBorderSize(0);
	leg1->SetFillStyle(1);
	leg1->SetFillColor(0);
	leg1->AddEntry(cms_7000_g,"7 TeV  (CMS)","lp");
	leg1->AddEntry(cms_2760_g,"2.76 TeV (CMS)","lp");
//	leg1->AddEntry(cms_2360_g,"2.36 TeV (CMS)","lp");
	leg1->AddEntry(cdf_1960_g,"1.96 TeV  (CDF)","lp");
	leg1->AddEntry(cdf_1800_g,"1.8 TeV  (CDF)","lp");
	leg1->AddEntry(cms_900_g,"0.9 TeV  (CMS)","lp");
//	if(!xt) leg1->AddEntry(ua1_900_g,"0.9 TeV  (UA1)  |#eta|<2.5","lp");
	leg1->AddEntry(cdf_630_g,"0.63 TeV  (CDF)","lp");
	leg1->Draw();
	
	gPad->SetLogy();
	//if(xt) gPad->SetLogx();
	gPad->SetLogx();
	
	//**************************
	
	if(xt) {
		TCanvas *c2 = new TCanvas("c2","fit to all",600,500);
		TList *list = new TList();
		list->Add(cdf_630_g);
		list->Add(cms_900_g);
		list->Add(cdf_1800_g);
		list->Add(cdf_1960_g);
		list->Add(cms_2760_g);
		
		TGraphErrors *merge_g = (TGraphErrors*) cms_7000_g->Clone("merge_g");
		merge_g->Merge(list);
		merge_g->Sort();
		
		dum->Draw();
		merge_g->Draw("pz");
		cms_7000_fit->Draw("same");
		cms_2760_fit->Draw("same");
		cdf_1960_fit->Draw("same");
		cdf_1800_fit->Draw("same");
		cms_900_fit->Draw("same");
		
		TF1 *merge_fit = new TF1("merge_fit","[0]*pow(1.0+(x/[1]),[2])",0.002,0.06); // was 0.003-0.07
		merge_fit->SetParameters(1.8e26,7.5e-5,-7);
		merge_fit->FixParameter(2,-7);
		merge_fit->SetLineColor(4);
		merge_fit->SetLineWidth(3);
		merge_g->Fit(merge_fit,"REMW");
		
		gPad->SetLogy();
		gPad->SetLogx();
				
		TCanvas *c3 = new TCanvas("c3","ratio to global fit",600,500);
		TH1F *hratio = new TH1F("hratio",";x_{T};ratio",160,0.0003,0.07); //was 0.003-0.04
		hratio->SetMaximum(2.0);
		hratio->SetMinimum(0.0);
		hratio->SetStats(0);
		hratio->Draw();
		
		TGraphErrors* ratio_cdf_1960_g = divide_graph_by_function(cdf_1960_g,merge_fit);
		ratio_cdf_1960_g->SetName("ratio_cdf_1960_g");
		ratio_cdf_1960_g->SetLineColor(kOrange-9);
		ratio_cdf_1960_g->SetMarkerSize(0.9);
		ratio_cdf_1960_g->Draw("pz");
		
		TF1 *logfit1960 = new TF1("logfit1960","[0]+[1]*log(x)+[2]/x/x",0.003,0.04); // was 0.001
		logfit1960->SetLineWidth(2);
		logfit1960->SetLineColor(kOrange-3);
		ratio_cdf_1960_g->Fit(logfit1960,"REMW");
		logfit1960->Draw("same");
		
		//TGraphErrors* ratio_cdfold_1960_g = divide_graph_by_function(cdfold_1960_g,merge_fit);
		//ratio_cdfold_1960_g->Draw("pz");
		
		//Double_t *yyy; Int_t NNN;
		//TGraph *ratio_cdf_1960_smooth = (TGraph*) ratio_cdf_1960_g->Clone("ratio_cdf_1960_smooth");
		//NNN = ratio_cdf_1960_smooth->GetN();
		//yyy = ratio_cdf_1960_smooth->GetY();
		//TH1::SmoothArray(NNN,yyy,10);
		//ratio_cdf_1960_smooth->Draw("pz");
		
		TGraphErrors* ratio_cdf_1800_g = divide_graph_by_function(cdf_1800_g,merge_fit);
		//ratio_cdf_1800_g->Draw("pz");
		
		TGraphErrors* ratio_cdf_630_g = divide_graph_by_function(cdf_630_g,merge_fit);
		//ratio_cdf_630_g->Draw("pz");
		
		TGraphErrors* ratio_cms_7000_g = divide_graph_by_function(cms_7000_g,merge_fit);
		ratio_cms_7000_g->SetName("ratio_cms_7000_g");
		ratio_cms_7000_g->Draw("pz");
		
		TF1 *logfit7000 = new TF1("logfit7000","[0]+[1]*log(x)+[2]/x/x",0.0015,0.1); // was 0.001
		logfit7000->SetLineWidth(2);
		ratio_cms_7000_g->Fit(logfit7000,"REMW");

		TGraphErrors* ratio_cms_2760_g = divide_graph_by_function(cms_2760_g,merge_fit);
		ratio_cms_2760_g->SetName("ratio_cms_2760_g");
		ratio_cms_2760_g->Draw("pz");
		
		TF1 *logfit2760 = new TF1("logfit2760","[0]+[1]*log(x)+[2]/x/x",0.0015,0.1); // was 0.001
		logfit2760->SetLineWidth(2);
		logfit2760->SetLineColor(kMagenta+3);
		ratio_cms_2760_g->Fit(logfit2760,"REMW");
		
		TGraphErrors* ratio_cms_900_g = divide_graph_by_function(cms_900_g,merge_fit);
		ratio_cms_900_g->SetName("ratio_cms_900_g");
		ratio_cms_900_g->Draw("pz");
		
		TF1 *logfit900 = new TF1("logfit900","[0]+[1]*log(x)+[2]/sqrt(x)",0.008,0.05); // was 0.005
		logfit900->SetLineWidth(2);
		logfit900->SetLineColor(2);
		ratio_cms_900_g->Fit(logfit900,"REMW");
		ratio_cms_900_g->SetLineColor(kRed);
		
//		TGaxis *A1 = new TGaxis(0.0003,2.0,0.07,2.0,1380*0.0003,1380*0.07,410,"-");
//		A1->SetTitle("p_{T} for #sqrt{s}=2.76 TeV");
//		A1->Draw();
		TGaxis *A1 = new TGaxis(0.0003,2.0,0.07,2.0,2510*0.0003,2510*0.07,410,"-");
		A1->SetTitle("p_{T} for #sqrt{s}=5.02 TeV");
		A1->Draw();
		
		gPad->SetTickx(0);
		
		TList *rlist = new TList();
		rlist->Add(ratio_cms_900_g);

		TGraphErrors *merge_ratio = (TGraphErrors*) ratio_cms_7000_g->Clone("merge_ratio");
		merge_ratio->Merge(rlist);
		merge_ratio->Sort();
		merge_ratio->SetMarkerColor(4);
		//merge_ratio->Draw("pz");
		
		//TF1 *merge_ratio_fit = new TF1("merge_ratio_fit","(logfit900+logfit7000+logfit1960)/3",0.001,0.1);
		//TF1 *merge_ratio_fit = new TF1("merge_ratio_fit","(logfit900*0.0+logfit7000*0.8+logfit1960*4.24)/(0.0+0.8+4.24)",0.001,0.1);
		TF1 *merge_ratio_fit = new TF1("merge_ratio_fit","(logfit900*0.0+logfit7000*0.14+logfit1960*0.84)",0.0036,0.1);
		merge_ratio_fit->SetLineColor(4);
		merge_ratio_fit->SetLineWidth(3);
// K.K. we don't want to plot the mean prediction (I think!)
//		merge_ratio_fit->Draw("same");

		//merge_ratio_fit->Draw("same");
		TF1 *merge_ratio_fit_up = new TF1("merge_ratio_fit_up","merge_ratio_fit*(1.12)",0.001,0.07); // was 7%
		merge_ratio_fit_up->SetLineColor(4);
		merge_ratio_fit_up->SetLineWidth(1);
		merge_ratio_fit_up->SetLineStyle(2);
		TF1 *merge_ratio_fit_dn = new TF1("merge_ratio_fit_dn","merge_ratio_fit*(0.88)",0.001,0.07); // was 7%
		merge_ratio_fit_dn->SetLineColor(4);
		merge_ratio_fit_dn->SetLineWidth(1);
		merge_ratio_fit_dn->SetLineStyle(2);
		//merge_ratio_fit_up->Draw("same");
		//merge_ratio_fit_dn->Draw("same");
		
		Double_t plx[20] = {0.0036,0.0055,0.0075,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.07,0.06,0.05,0.04,0.03,0.02,0.01,0.0075,0.0055,0.0036};
		Double_t ply[20];
		for(Int_t i=0; i<10; i++)
			ply[i]=TMath::Min(merge_ratio_fit_dn->Eval(plx[i]),logfit7000->Eval(plx[i]));
		for(Int_t i=10; i<20; i++)
			ply[i]=TMath::Max(merge_ratio_fit_up->Eval(plx[i]),logfit1960->Eval(plx[i]));
		
		TPolyLine *pline = new TPolyLine(20,plx,ply);
		pline->SetFillColor(kGray);
		pline->SetLineColor(kGray+1);
		pline->SetLineWidth(1);
		
		// now draw everything again in the right order
//		pline->Draw("fsame");
		//pline->Draw("csame");
		ratio_cdf_1960_g->Draw("pzsame");
		ratio_cms_900_g->Draw("pzsame");
		ratio_cms_7000_g->Draw("pzsame");
// KK: this seems to be the middle of the curve prediction; here it is plotted on top of the others
//		merge_ratio_fit->Draw("same");
		
		TH1F *int_2760_xt = new TH1F("int_2760_xt","interpolation to 2.76 TeV; x_{T}",1000,0.003,0.04);
		int_2760_xt->SetMarkerStyle(20);
		int_2760_xt->SetMarkerColor(4);
		int_2760_xt->SetLineColor(4);
		int_2760_xt->SetMarkerSize(0.4);
		TH1F *int_2760_pt = new TH1F("int_2760_pt","interpolation to 2.76 TeV; p_{T} (GeV/c)",1000,5,60);
		
		for(int hbin=1; hbin<=1000; hbin++) {
			float binxt = int_2760_xt->GetBinCenter(hbin);
			float binpt = int_2760_pt->GetBinCenter(hbin);
			int_2760_xt->SetBinContent(hbin,merge_fit->Eval(binxt)*merge_ratio_fit->Eval(binxt));
			int_2760_pt->SetBinContent(hbin,merge_fit->Eval(binpt/1380)*merge_ratio_fit->Eval(binpt/1380));
		}
		
		c1->cd();
                merge_fit->SetLineColor(41);
                merge_fit->SetLineStyle(1);
                merge_fit->Draw("same"); //This is the common fit to CMS 900, 7000 and CDF 630, 1800, 1960

//		int_2760_xt->Draw("lsame");
		
		cout << "Power-law fit:" 
		<< "\n\t par0 = " << merge_fit->GetParameter(0)
		<< "\n\t par1 = " << merge_fit->GetParameter(1)
		<< "\n\t par2 = " << merge_fit->GetParameter(2)
		<< "\nPolynomial correction:" 
		<< "\n\t par0 = " << merge_ratio_fit->GetParameter(0)
		<< "\n\t par1 = " << merge_ratio_fit->GetParameter(1)
		<< "\n\t par2 = " << merge_ratio_fit->GetParameter(2)
		<< "\n\t par3 = " << merge_ratio_fit->GetParameter(3)
		<< "\n\t par4 = " << merge_ratio_fit->GetParameter(4)
		<< "\n\t par5 = " << merge_ratio_fit->GetParameter(5)
		<< "\n\t par6 = " << merge_ratio_fit->GetParameter(6)
		<< "\n\t par7 = " << merge_ratio_fit->GetParameter(7)
		<< "\n\t par8 = " << merge_ratio_fit->GetParameter(8)
		<< endl;
		
		// nlo ratios to 2.75 TeV
		c3->cd();
//		TFile *nlofile = new TFile("output_nlo.root");
		TFile *nlofile = new TFile("output_nlo_100_KK.root");
		TH1F *nlo900 = (TH1F*) nlofile->Get("h900");
		TH1F *nlo7000 = (TH1F*) nlofile->Get("h7000");
		TH1F *nlo1960 = (TH1F*) nlofile->Get("h1960");
		TFile *nlofile50 = new TFile("output_nlo_050_KK.root");
		TH1F *nlo900m50 = (TH1F*) nlofile50->Get("h900");
		TH1F *nlo7000m50 = (TH1F*) nlofile50->Get("h7000");
		TH1F *nlo1960m50 = (TH1F*) nlofile50->Get("h1960");
		TFile *nlofile200 = new TFile("output_nlo_200_KK.root");
		TH1F *nlo900m200 = (TH1F*) nlofile200->Get("h900");
		TH1F *nlo7000m200 = (TH1F*) nlofile200->Get("h7000");
		TH1F *nlo1960m200 = (TH1F*) nlofile200->Get("h1960");
		
		TH1F *scaled900 = (TH1F*) nlo900->Clone("scaled900");
		TH1F *scaled7000 = (TH1F*) nlo7000->Clone("scaled7000");
		TH1F *scaled1960 = (TH1F*) nlo1960->Clone("scaled1960");
		TH1F *scaled900m50 = (TH1F*) nlo900m50->Clone("scaled900m50");
		TH1F *scaled7000m50 = (TH1F*) nlo7000m50->Clone("scaled7000m50");
		TH1F *scaled1960m50 = (TH1F*) nlo1960m50->Clone("scaled1960m50");
		TH1F *scaled900m200 = (TH1F*) nlo900m200->Clone("scaled900m200");
		TH1F *scaled7000m200 = (TH1F*) nlo7000m200->Clone("scaled7000m200");
		TH1F *scaled1960m200 = (TH1F*) nlo1960m200->Clone("scaled1960m200");
		
		for(Int_t i=1; i<=scaled900->GetNbinsX(); i++) {
			
			scaled900->SetBinContent(i,logfit900->Eval(scaled900->GetBinCenter(i)));
			scaled7000->SetBinContent(i,logfit7000->Eval(scaled7000->GetBinCenter(i)));
			scaled1960->SetBinContent(i,logfit1960->Eval(scaled1960->GetBinCenter(i)));
			scaled900m50->SetBinContent(i,logfit900->Eval(scaled900m50->GetBinCenter(i)));
			scaled7000m50->SetBinContent(i,logfit7000->Eval(scaled7000m50->GetBinCenter(i)));
			scaled1960m50->SetBinContent(i,logfit1960->Eval(scaled1960m50->GetBinCenter(i)));
			scaled900m200->SetBinContent(i,logfit900->Eval(scaled900m200->GetBinCenter(i)));
			scaled7000m200->SetBinContent(i,logfit7000->Eval(scaled7000m200->GetBinCenter(i)));
			scaled1960m200->SetBinContent(i,logfit1960->Eval(scaled1960m200->GetBinCenter(i)));
			
			// if NLO points aren't available in ratio, remove them
			if(scaled900->GetBinCenter(i) > 0.045 || scaled900->GetBinCenter(i) < 0.008) {scaled900->SetBinContent(i,0.0); scaled900m50->SetBinContent(i,0.0); scaled900m200->SetBinContent(i,0.0);}
			if(scaled1960->GetBinCenter(i) < 0.004) {scaled1960->SetBinContent(i,0.0); scaled1960m50->SetBinContent(i,0.0); scaled1960m200->SetBinContent(i,0.0);}
			if(scaled7000->GetBinCenter(i) < 0.003) {scaled7000->SetBinContent(i,0.0); scaled7000m50->SetBinContent(i,0.0); scaled7000m200->SetBinContent(i,0.0);}
			
			// if pt is below 8 GeV, remove NLO-corrected xt-scaled data
			if((scaled900->GetBinCenter(i)*450) < 8) {scaled900->SetBinContent(i,0.0); scaled900m50->SetBinContent(i,0.0); scaled900m200->SetBinContent(i,0.0);}
			if((scaled1960->GetBinCenter(i)*980) < 8) {scaled1960->SetBinContent(i,0.0); scaled1960m50->SetBinContent(i,0.0); scaled1960m200->SetBinContent(i,0.0);}
			if((scaled7000->GetBinCenter(i)*3500) < 8) {scaled7000->SetBinContent(i,0.0); scaled7000m50->SetBinContent(i,0.0); scaled7000m200->SetBinContent(i,0.0);}

		}
		
		scaled900->Divide(nlo900);
		scaled1960->Divide(nlo1960);
		scaled7000->Divide(nlo7000);
		scaled900m50->Divide(nlo900m50);
		scaled1960m50->Divide(nlo1960m50);
		scaled7000m50->Divide(nlo7000m50);
		scaled900m200->Divide(nlo900m200);
		scaled1960m200->Divide(nlo1960m200);
		scaled7000m200->Divide(nlo7000m200);
		
		scaled900->SetLineColor(kBlue);
		scaled1960->SetLineColor(kBlue);
		scaled7000->SetLineColor(kBlue);
		scaled900m50->SetLineColor(kBlue);
		scaled1960m50->SetLineColor(kBlue);
		scaled7000m50->SetLineColor(kBlue);
		scaled900m200->SetLineColor(kBlue);
		scaled1960m200->SetLineColor(kBlue);
		scaled7000m200->SetLineColor(kBlue);
//KK: DON'T PLOT THE NLO-SCALED RATIO FOR NOW; c3!
//		scaled900->Draw("psame");  scaled1960->Draw("psame");  scaled7000->Draw("psame");
/*
		scaled900m50->Draw("psame");  scaled1960m50->Draw("psame");  scaled7000m50->Draw("psame");
		scaled900m200->Draw("psame");  scaled1960m200->Draw("psame");  scaled7000m200->Draw("psame");
*/
		TFile *fitoutput = new TFile("output_xtscaling_KK.root","RECREATE");
		TF1 *xt_scaling_fit_2760 = new TF1("xt_scaling_fit_2760","merge_fit*merge_ratio_fit",0.001,0.07);
		//xt_scaling_fit_2760->Draw("same");
		xt_scaling_fit_2760->Write();
		
		ratio_cdf_1960_g->Write();
		logfit1960->Write();
		ratio_cms_900_g->Write();
		logfit900->Write();
		ratio_cms_7000_g->Write();
		logfit7000->Write();
		
                merge_fit->Write();
		merge_ratio_fit->Write();
		merge_ratio_fit_up->Write();
		merge_ratio_fit_dn->Write();
		
		scaled900->Write();
		scaled1960->Write();
		scaled7000->Write();
		
		scaled900m50->Write();
		scaled1960m50->Write();
		scaled7000m50->Write();
		
		scaled900m200->Write();
		scaled1960m200->Write();
		scaled7000m200->Write();
		
		pline->Write();
		
		fitoutput->ls();
		fitoutput->Close();
		
	} else {
		
		TF1 *cdf_630_fit_pt = new TF1("cdf_630_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,10.0);
		cdf_630_fit_pt->SetLineColor(kOrange+3);
		cdf_630_fit_pt->SetParameters(20,10,-7);
		cdf_630_g->Fit(cdf_630_fit_pt,"REM");
		
		TF1 *cms_900_fit_pt = new TF1("cms_900_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,10.0);
		cms_900_fit_pt->SetLineColor(kRed);
		cms_900_fit_pt->SetParameters(20,10,-7);
		cms_900_g->Fit(cms_900_fit_pt,"REM");

		TF1 *cdf_1800_fit_pt = new TF1("cdf_1800_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,10.0);
		cdf_1800_fit_pt->SetLineColor(kGreen+3);
		cdf_1800_fit_pt->SetParameters(20,10,-7);
		cdf_1800_g->Fit(cdf_1800_fit_pt,"REM");
		
		TF1 *cdf_1960_fit_pt = new TF1("cdf_1960_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,10.0);
		cdf_1960_fit_pt->SetLineColor(kOrange-3);
		cdf_1960_fit_pt->SetParameters(20,10,-7);
		cdf_1960_g->Fit(cdf_1960_fit_pt,"REM");
		
//		TF1 *cms_2360_fit_pt = new TF1("cms_2360_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,10.0);
//		cms_2360_fit_pt->SetLineColor(kMagenta+3);
//		cms_2360_fit_pt->SetParameters(20,10,-7);
//		cms_2360_g->Fit(cms_2360_fit_pt,"REM");

		TF1 *cms_2760_fit_pt = new TF1("cms_2760_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,100.0);
		cms_2760_fit_pt->SetLineColor(kMagenta+3);
		cms_2760_fit_pt->SetParameters(200,1,-7);
                std::cerr<<"==== Start to fit the 2760 GeV data" << std::endl;
		cms_2760_g->Fit(cms_2760_fit_pt,"REM");
                std::cerr<<"==== Finished fitting the 2760 GeV data" << std::endl;
		
		TF1 *cms_7000_fit_pt = new TF1("cms_7000_fit_pt","[0]*pow(1.0+(x/[1]),[2])",1.0,100.0);
		cms_7000_fit_pt->SetLineColor(kBlack);
		cms_7000_fit_pt->SetParameters(200,1,-7);
                std::cerr<<"==== Start to fit the 7000 GeV data" << std::endl;
		cms_7000_g->Fit(cms_7000_fit_pt,"REM");
                std::cerr<<"==== Finished fitting the 7000 GeV data" << std::endl;
		
		TF1 *cms_2760_PL_pt = new TF1("cms_2760_PL_pt","[0]*pow(1.0+(x/1380/[1]),[2])",1.0,100.0);
		//cms_2760_PL_pt->SetParameters(2.59664e+19*pow(2760,-1*expo),0.000745074,-7.0);  // prePap
		cms_2760_PL_pt->SetParameters(2.75643e+19*pow(2760,-1*expo),0.000736666,-7.0);
		TF1 *cms_2760_res_pt = new TF1("cms_2760_res_pt","0.0*([0]+[1]*log(x/1380)+[2]/sqrt(x/1380))+0.14*([3]+[4]*log(x/1380)+[5]*1380*1380/x/x)+0.84*([6]+[7]*log(x/1380)+[8]*1380*1380/x/x)",1.0,100.0);
		cms_2760_res_pt->SetParameters(2.30194,0.787168,0.251703,2.0172,0.246122,2.52377e-06,1.54941,0.165443,7.70429e-06); // prePap 
		//cms_2760_res_pt->SetParameters(3.19697,1.26756,0.390141,1.93545,0.231813,2.60768ee-6,1.58439,0.170378,7.71344e-06);
		TF1 *cms_2760_int_pt = new TF1("cms_2760_int_pt","cms_2760_PL_pt*cms_2760_res_pt",1.0,100.0);
		cms_2760_int_pt->SetLineColor(6); //4
		cms_2760_int_pt->SetLineWidth(4);
//		cms_2760_int_pt->Draw("same");

		TF1 *cms_5020_PL_pt = new TF1("cms_5020_PL_pt","[0]*pow(1.0+(x/2510/[1]),[2])",1.0,100.0);
		cms_5020_PL_pt->SetParameters(2.75643e+19*pow(5020,-1*expo),0.000736666,-7.0);
		TF1 *cms_5020_res_pt = new TF1("cms_5020_res_pt","0.0*([0]+[1]*log(x/2510)+[2]/sqrt(x/2510))+0.14*([3]+[4]*log(x/2510)+[5]*2510*2510/x/x)+0.84*([6]+[7]*log(x/2510)+[8]*2510*2510/x/x)",1.0,100.0);
		cms_5020_res_pt->SetParameters(2.30194,0.787168,0.251703,2.0172,0.246122,2.52377e-06,1.54941,0.165443,7.70429e-06); // prePap 
		TF1 *cms_5020_int_pt = new TF1("cms_5020_int_pt","cms_5020_PL_pt*cms_5020_res_pt",1.0,100.0);
		cms_5020_int_pt->SetLineColor(7);
		cms_5020_int_pt->SetLineWidth(4);
//		cms_5020_int_pt->Draw("same");
		
		TCanvas *c4 = new TCanvas("c4","ratio to fits",600,500);
		
		TH1F *hratiopt = new TH1F("hratiopt",";p_{T} [GeV/c];ratio",6000,0.3,100); 
		hratiopt->SetMaximum(15.0);
		hratiopt->SetMinimum(0.5);
		hratiopt->SetStats(0);
         	hratiopt->GetXaxis()->CenterTitle();
        	hratiopt->GetYaxis()->CenterTitle();
        	hratiopt->GetXaxis()->SetTitleSize(0.05);
         	hratiopt->GetYaxis()->SetTitleSize(0.05);
        	hratiopt->GetXaxis()->SetTitleOffset(1.17);
        	hratiopt->GetYaxis()->SetTitleOffset(1.3);
		hratiopt->Draw();
				
		TGraphErrors* ratio_cdf_1960_pt = divide_graph_by_function(cdf_1960_g,cdf_1960_fit_pt);
		ratio_cdf_1960_pt->Draw("pz");
		TMVA::TSpline1 *err_cdf_1960_pt = errors_from_graph(cdf_1960_g,0.06);
		
		TGraphErrors* ratio_cdf_1800_pt = divide_graph_by_function(cdf_1800_g,cdf_1800_fit_pt);
		ratio_cdf_1800_pt->Draw("pz");
		TMVA::TSpline1 *err_cdf_1800_pt = errors_from_graph(cdf_1800_g,0.14);
		
		TGraphErrors* ratio_cdf_630_pt = divide_graph_by_function(cdf_630_g,cdf_630_fit_pt);
		ratio_cdf_630_pt->Draw("pz");
		TMVA::TSpline1 *err_cdf_630_pt = errors_from_graph(cdf_630_g,0.088);
		
		TGraphErrors* ratio_cms_900_pt = divide_graph_by_function(cms_900_g,cms_900_fit_pt);
		ratio_cms_900_pt->Draw("pz");
		TMVA::TSpline1 *err_cms_900_pt = errors_from_graph(cms_900_g,0.115);
		
//		TGraphErrors* ratio_cms_2360_pt = divide_graph_by_function(cms_2360_g,cms_2360_fit_pt);
//		ratio_cms_2360_pt->Draw("pz");
//		TMVA::TSpline1 *err_cms_2360_pt = errors_from_graph(cms_2360_g,0.11); // error from PYTHIA cross section usage + ~5% systematic on dN/dpt ??

		TGraphErrors* ratio_cms_2760_pt = divide_graph_by_function(cms_2760_g,cms_2760_fit_pt);
		ratio_cms_2760_pt->Draw("pz");
		TMVA::TSpline1 *err_cms_2760_pt = errors_from_graph(cms_2760_g,0.11); // check syst. error
		
		TGraphErrors* ratio_cms_7000_pt = divide_graph_by_function(cms_7000_g,cms_7000_fit_pt);
		ratio_cms_7000_pt->Draw("pz");
		TMVA::TSpline1 *err_cms_7000_pt = errors_from_graph(cms_7000_g,0.04);
		
		Double_t *yy; Int_t NN;
		NN = ratio_cdf_1960_pt->GetN();
		yy = ratio_cdf_1960_pt->GetY();
		TH1::SmoothArray(NN,yy,50);
		
		Double_t *yy2; Int_t NN2;
		NN2 = ratio_cdf_1800_pt->GetN();
		yy2 = ratio_cdf_1800_pt->GetY();
		TH1::SmoothArray(NN2,yy2,50);
		
		Double_t *yy3; Int_t NN3;
		NN3 = ratio_cdf_630_pt->GetN();
		yy3 = ratio_cdf_630_pt->GetY();
		TH1::SmoothArray(NN3,yy3,50);
				
		TMVA::TSpline1 *cms_900_spline = new TMVA::TSpline1("cms_900_spline",ratio_cms_900_pt);
		cms_900_spline->SetLineColor(kRed);
		cms_900_spline->SetLineWidth(2);
		cms_900_spline->Draw("lsame");
		
		TMVA::TSpline1 *cms_7000_spline = new TMVA::TSpline1("cms_7000_spline",ratio_cms_7000_pt);
		cms_7000_spline->SetLineColor(kBlack);
		cms_7000_spline->SetLineWidth(2);
		cms_7000_spline->Draw("lsame");
		
//		TMVA::TSpline1 *cms_2360_spline = new TMVA::TSpline1("cms_2360_spline",ratio_cms_2360_pt);
//		cms_2360_spline->SetLineColor(kMagenta+3);
//		cms_2360_spline->SetLineWidth(2);
//		cms_2360_spline->Draw("lsame");

		TMVA::TSpline1 *cms_2760_spline = new TMVA::TSpline1("cms_2760_spline",ratio_cms_2760_pt);
		cms_2760_spline->SetLineColor(kMagenta+3);
		cms_2760_spline->SetLineWidth(2);
		cms_2760_spline->Draw("lsame");
		
		TMVA::TSpline1 *cdf_1960_spline = new TMVA::TSpline1("cdf_1960_spline",ratio_cdf_1960_pt);
		cdf_1960_spline->SetLineColor(kOrange-3);
		cdf_1960_spline->SetLineWidth(2);
		cdf_1960_spline->Draw("lsame");
		
		TMVA::TSpline1 *cdf_1800_spline = new TMVA::TSpline1("cdf_1800_spline",ratio_cdf_1800_pt);
		cdf_1800_spline->SetLineColor(kGreen+3);
		cdf_1800_spline->SetLineWidth(2);
		cdf_1800_spline->Draw("lsame");
		
		TMVA::TSpline1 *cdf_630_spline = new TMVA::TSpline1("cdf_630_spline",ratio_cdf_630_pt);
		cdf_630_spline->SetLineColor(kOrange+3);
		cdf_630_spline->SetLineWidth(2);
		cdf_630_spline->Draw("lsame");
		
		// fine-bin histogram the power-law + residual spline spectra for easier interpolation
		TH1D *h900 = new TH1D("h900","900 GeV fitted spectra;p_{T}",7600,0.5,30);
		h900->SetLineColor(kRed);
		TH1D *h1960 = new TH1D("h1960","1.96 TeV fitted spectra;p_{T}",7600,0.5,30);
		h1960->SetLineColor(kOrange-3);
		TH1D *h7000 = new TH1D("h7000","7 TeV fitted spectra;p_{T}",30400,0.5,118.5);
		TH1D *h1800 = new TH1D("h1800","1.8 TeV fitted spectra;p_{T}",7600,0.5,30);
		h1800->SetLineColor(kGreen+3);
		TH1D *h630 = new TH1D("h630","0.63 TeV fitted spectra;p_{T}",7600,0.5,30);
		h630->SetLineColor(kOrange+3);
//		TH1D *h2360 = new TH1D("h2360","2.36 TeV fitted spectra;p_{T}",7600,0.5,30);
//		h2360->SetLineColor(kMagenta+3);
		TH1D *h2760_EdTxt = new TH1D("h2760_EdTxt","2.76 TeV fitted spectra;p_{T}",30400,0.5,118.5);
		h2760_EdTxt->SetLineColor(kMagenta+3);

		for(int hbin=1; hbin<=7600; hbin++) {
			float pt = h900->GetBinCenter(hbin);
			h900->SetBinContent(hbin,cms_900_spline->Eval(pt)*cms_900_fit_pt->Eval(pt));
			h1960->SetBinContent(hbin,cdf_1960_spline->Eval(pt)*cdf_1960_fit_pt->Eval(pt));
			h1800->SetBinContent(hbin,cdf_1800_spline->Eval(pt)*cdf_1800_fit_pt->Eval(pt));
	        	h630->SetBinContent(hbin,cdf_630_spline->Eval(pt)*cdf_630_fit_pt->Eval(pt));
//			h7000->SetBinContent(hbin,cms_7000_spline->Eval(pt)*cms_7000_fit_pt->Eval(pt));
//			h2760_EdTxt->SetBinContent(hbin,cms_2760_spline->Eval(pt)*cms_2760_fit_pt->Eval(pt));
//			h2360->SetBinContent(hbin,cms_2360_fit_pt->Eval(pt)); // don't use spline since the residual is flat except the last crazy point anyways
		}
		for(int hbin=1; hbin<=30400; hbin++) {
			float pt = h7000->GetBinCenter(hbin);
			h7000->SetBinContent(hbin,cms_7000_spline->Eval(pt)*cms_7000_fit_pt->Eval(pt));
			h2760_EdTxt->SetBinContent(hbin,cms_2760_spline->Eval(pt)*cms_2760_fit_pt->Eval(pt));
                }		

		TCanvas *c5 = new TCanvas("c5","final low-pt fits",600,500);
		TH1D* dumDirectInt = new TH1D("dumDirectInt","Final fits; p_{T} (GeV/c)",120,0,120);
		dumDirectInt->SetMaximum(20);
		dumDirectInt->SetMinimum(1e-12);
		dumDirectInt->GetXaxis()->SetRangeUser(0.5,120.);
		dumDirectInt->SetStats(0);
		dumDirectInt->GetYaxis()->SetTitle("Ed^{3}#sigma/dp^{3}");
		dumDirectInt->Draw();
		h900->Draw("same");
		h1960->Draw("same");
		h1800->Draw("same");
		h630->Draw("same");
		h7000->Draw("same");
//		h2360->Draw("same");
		h2760_EdTxt->Draw("same");
		gPad->SetLogy();
		
		// inspect pol2 direct interpolations
		TCanvas *c6 = new TCanvas("c6","interpolations",600,500);
		c6->Divide(3,4);
		float s[6]; float xs[6]; float es[6]={0.0,0.0,0.0,0.0,0.0,0.0}; float exs[6];   TGraphErrors *gXS[12];
                float s_log[6]; float xs_log[6]; float es_log[6]={0.0,0.0,0.0,0.0,0.0,0.0}; float exs_log[6];
                TGraphErrors *gXS_log[12]; //KK test
                TGraphErrors *gXS_log_lemma[12]; //KK test
//		float s[7]; float xs[7]; float es[7]={0.0,0.0,0.0,0.0,0.0,0.0,0.0}; float exs[7];   TGraphErrors *gXS[10];
		float s1[1]={2.76}; float xs1[1]; float ex1[1]={0.0}; float ey1[1]; 		TGraphErrors *gXS1[12];
		float s1_5020[1]={5.02}; float xs1_5020[1]; float ex1_5020[1]={0.0}; float ey1_5020[1]; TGraphErrors *gXS1_5020[12];
		float s2[1]={2.76}; float xs2[1]; float ex2[1]={0.0}; float ey2[1]; 		TGraphErrors *gXS2[12];
		float s2_5020[1]={5.02}; float xs2_5020[1]; float ex2_5020[1]={0.0}; float ey2_5020[1]; TGraphErrors *gXS2_5020[12];
		float s630[1]={0.63}; float xs630[1]; float ex630[1]={0.0}; float ey630[1]; TGraphErrors *gXS630[12];
		float s900[1]={0.9}; float xs900[1]; float ex900[1]={0.0}; float ey900[1]; TGraphErrors *gXS900[12];
		float s1800[1]={1.8}; float xs1800[1]; float ex1800[1]={0.0}; float ey1800[1]; TGraphErrors *gXS1800[12];
		float s1960[1]={1.96}; float xs1960[1]; float ex1960[1]={0.0}; float ey1960[1]; TGraphErrors *gXS1960[12];
//		float s2360[1]={2.36}; float xs2360[1]; float ex2360[1]={0.0}; float ey2360[1]; TGraphErrors *gXS2360[10];
		float s2760[1]={2.76}; float xs2760[1]; float ex2760[1]={0.0}; float ey2760[1]; TGraphErrors *gXS2760[12];
		float s7000[1]={7.0}; float xs7000[1]; float ex7000[1]={0.0}; float ey7000[1]; TGraphErrors *gXS7000[12];

		TF1 *fitXS[12];  TH1F *dumXS[12];
                TF1 *fitXS_log[12];
		float ptbins[12]={1.0,2.0,3.0,4.0,6.0,9.0,12.0,15.0,18.0,20.0,30.0,40.0};

                std::cerr<<"ALIVE 1" << std::endl;
		
		for(Int_t ipt=0; ipt<=11; ipt++) { // 1,2,...,9 GeV/c
						
			c6->cd(ipt+1);
			int npoints=0;
			if(ptbins[ipt]<=3.9) {
				s[npoints]=0.63; s_log[npoints]=log10(s[npoints]);
				xs[npoints]=h630->GetBinContent(h630->FindBin(ptbins[ipt])); xs_log[npoints]=log10(xs[npoints]);
                                //Test: exs_log[npoints]=log10(exs[npoints]) -> exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
				exs[npoints]=err_cdf_630_pt->Eval(ptbins[ipt])*xs[npoints]; exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
				xs630[0]=xs[npoints]; ey630[0]=exs[npoints];
				npoints++;
			}
//			if(ptbins[ipt]<=19.9) {
			if(ptbins[ipt]<=21.9) {
     				xs[npoints]=h900->GetBinContent(h900->FindBin(ptbins[ipt])); s[npoints]=0.9; exs[npoints]=err_cms_900_pt->Eval(ptbins[ipt])*xs[npoints]; xs900[0]=xs[npoints]; ey900[0]=exs[npoints];
				xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
	                        npoints++;
                        }
			if(ptbins[ipt]<=5.9) {
				s[npoints]=1.8; s_log[npoints]=log10(s[npoints]);
				xs[npoints]=h1800->GetBinContent(h1800->FindBin(ptbins[ipt])); xs_log[npoints]=log10(xs[npoints]);
				exs[npoints]=err_cdf_1800_pt->Eval(ptbins[ipt])*xs[npoints]; exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
				xs1800[0]=xs[npoints]; ey1800[0]=exs[npoints];
				npoints++;
			}
			if(ptbins[ipt]<=29.9) {
				xs[npoints]=h1960->GetBinContent(h1960->FindBin(ptbins[ipt])); s[npoints]=1.96; exs[npoints]=err_cdf_1960_pt->Eval(ptbins[ipt])*xs[npoints]; xs1960[0]=xs[npoints]; ey1960[0]=exs[npoints];
	 			xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
	                        npoints++;
                        }
/*
			if(ptbins[ipt]<=5.9) {
				s[npoints]=2.36;
				xs[npoints]=h2360->GetBinContent(h2360->FindBin(ptbins[ipt]));
				exs[npoints]=err_cms_2360_pt->Eval(ptbins[ipt])*xs[npoints];
				xs2360[0]=xs[npoints]; ey2360[0]=exs[npoints];
				npoints++;
			}
*/  
/*
                        // do I need to change the npoints interval?
			xs[npoints]=h2760_EdTxt->GetBinContent(h2760_EdTxt->FindBin(ptbins[ipt])); s[npoints]=2.76; exs[npoints]=err_cms_2760_pt->Eval(ptbins[ipt])*xs[npoints]; xs2760[0]=xs[npoints]; ey2760[0]=exs[npoints];
			xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
                        npoints++;
*/
			xs[npoints]=h7000->GetBinContent(h7000->FindBin(ptbins[ipt])); s[npoints]=7.0; exs[npoints]=err_cms_7000_pt->Eval(ptbins[ipt])*xs[npoints]; xs7000[0]=xs[npoints]; ey7000[0]=exs[npoints];
			xs_log[npoints]=log10(xs[npoints]); s_log[npoints]=log10(s[npoints]); exs_log[npoints]=TMath::Max(fabs(log10(xs[npoints]-exs[npoints])-log10(xs[npoints])),fabs(log10(xs[npoints]+exs[npoints])-log10(xs[npoints])));
                        npoints++;
			
			dumXS[ipt] = new TH1F(Form("dumXS%d",ipt),Form("p_{T} = %0.0f GeV/c;#sqrt{s} [TeV]",ptbins[ipt]),100,0,20);
			dumXS[ipt]->SetMinimum(0.5*xs[0]);
			dumXS[ipt]->SetMaximum(2.0*xs[npoints-1]);
			dumXS[ipt]->SetStats(0);
			dumXS[ipt]->GetXaxis()->SetRangeUser(0.5,10.0);
                 	dumXS[ipt]->GetXaxis()->CenterTitle();
                	dumXS[ipt]->GetYaxis()->CenterTitle();
                	dumXS[ipt]->GetYaxis()->SetTitle("E d#sigma^{3}/dp^{3}");
                	dumXS[ipt]->GetXaxis()->SetTitleSize(0.10);
                	dumXS[ipt]->GetYaxis()->SetTitleSize(0.10);
                	dumXS[ipt]->GetYaxis()->SetLabelSize(0.10);
                	dumXS[ipt]->GetXaxis()->SetLabelSize(0.10);
                	dumXS[ipt]->GetXaxis()->SetTitleOffset(0.6);
                	dumXS[ipt]->GetYaxis()->SetTitleOffset(0.8);
			dumXS[ipt]->Draw();
			gPad->SetLogy();  gPad->SetLogx();

                        std::cerr<< "npoints: " << npoints << std::endl;
			
			gXS[ipt] = new TGraphErrors(npoints,s,xs,es,exs);  gXS[ipt]->SetName(Form("gXS%d",ipt));
			gXS[ipt]->SetMarkerStyle(20);
			gXS_log[ipt] = new TGraphErrors(npoints,s_log,xs_log,es_log,exs_log); gXS_log[ipt]->SetName(Form("gXS_log%d",ipt));
                        //check s_log
                        for(int vero=0; vero<6; vero++) {
                           std::cerr<<"s_log: " << s_log[vero] << std::endl; 
                           std::cerr<<"xs_log: " << xs_log[vero] << std::endl; 
                           std::cerr<<"es_log: " << es_log[vero] << std::endl; 
                           std::cerr<<"exs_log: " << exs_log[vero] << std::endl; 
                        }
			//gXS[ipt]->Draw("pz");
			if(ptbins[ipt]<=3.9) {
				gXS630[ipt] = new TGraphErrors(1,s630,xs630,ex630,ey630); gXS630[ipt]->SetName(Form("gXS630_%d",ipt)); 
				gXS630[ipt]->SetMarkerStyle(27);  gXS630[ipt]->SetMarkerColor(kOrange+3); gXS630[ipt]->Draw("pz");
			}
//			if(ptbins[ipt]<=19.9) {
			if(ptbins[ipt]<=21.9) {
				gXS900[ipt] = new TGraphErrors(1,s900,xs900,ex900,ey900); gXS900[ipt]->SetName(Form("gXS900_%d",ipt)); 
				gXS900[ipt]->SetMarkerStyle(20);  gXS900[ipt]->SetMarkerColor(kRed); gXS900[ipt]->Draw("pz");
                        }
			if(ptbins[ipt]<=5.9) {
				gXS1800[ipt] = new TGraphErrors(1,s1800,xs1800,ex1800,ey1800); gXS1800[ipt]->SetName(Form("gXS1800_%d",ipt)); 
				gXS1800[ipt]->SetMarkerStyle(28);  gXS1800[ipt]->SetMarkerColor(kGreen+3); gXS1800[ipt]->Draw("pz");
			}
			if(ptbins[ipt]<=29.9) {
				gXS1960[ipt] = new TGraphErrors(1,s1960,xs1960,ex1960,ey1960); gXS1960[ipt]->SetName(Form("gXS1960_%d",ipt)); 
				gXS1960[ipt]->SetMarkerStyle(30);  gXS1960[ipt]->SetMarkerColor(kOrange-3); gXS1960[ipt]->Draw("pz");
                        }
/*
			if(ptbins[ipt]<=5.9) {
				gXS2360[ipt] = new TGraphErrors(1,s2360,xs2360,ex2360,ey2360); gXS2360[ipt]->SetName(Form("gXS2360_%d",ipt)); 
				gXS2360[ipt]->SetMarkerStyle(20);  gXS2360[ipt]->SetMarkerColor(kMagenta+3); gXS2360[ipt]->Draw("pz");
			}
*/
//			gXS2760[ipt] = new TGraphErrors(1,s2760,xs2760,ex2760,ey2760); gXS2760[ipt]->SetName(Form("gXS2760_%d",ipt)); 
//			gXS2760[ipt]->SetMarkerStyle(20);  gXS2760[ipt]->SetMarkerColor(kMagenta+3); gXS2760[ipt]->Draw("pz");	
			gXS7000[ipt] = new TGraphErrors(1,s7000,xs7000,ex7000,ey7000); gXS7000[ipt]->SetName(Form("gXS7000_%d",ipt)); 
			gXS7000[ipt]->SetMarkerStyle(20);  gXS7000[ipt]->SetMarkerColor(kBlack); gXS7000[ipt]->Draw("pz");	
			
//			fitXS[ipt] = new TF1(Form("fitXS%d",ipt),"pol2",0.3,7.2);
                        if(npoints>2)
				fitXS_log[ipt] = new TF1(Form("fitXS_log%d",ipt),"pol2",-0.52288,0.85733);
                        else
				fitXS_log[ipt] = new TF1(Form("fitXS_log%d",ipt),"pol1",-0.52288,0.85733);
			//fitXS[ipt]->FixParameter(0,0.0);
//			gXS[ipt]->Fit(fitXS[ipt], "REM0"); //"REMW");
                        std::cerr<<"--> BEFORE FIT" << std::endl;
			gXS_log[ipt]->Fit(fitXS_log[ipt], "REM0"); //"REMW");
                        std::cerr<<"--> AFTER FIT" << std::endl;

			// full covariance errors on fit
			TVirtualFitter *fitter = TVirtualFitter::GetFitter();
			TMatrixD matrix(3,3,fitter->GetCovarianceMatrix());
			Double_t e00 = fitter->GetCovarianceMatrixElement(0,0);
			Double_t e11 = fitter->GetCovarianceMatrixElement(1,1);
			Double_t e22 = fitter->GetCovarianceMatrixElement(2,2);
			Double_t e01 = fitter->GetCovarianceMatrixElement(0,1);
			Double_t e02 = fitter->GetCovarianceMatrixElement(0,2);
			Double_t e12 = fitter->GetCovarianceMatrixElement(1,2);

                        //Due to properties of the covariance matrix:
                        Double_t e10 = e01;
                        Double_t e20 = e02;
                        Double_t e21 = e12;

                        gXS_log_lemma[ipt] = new TGraphErrors(); gXS_log_lemma[ipt]->SetName(Form("gXS_log_lemma%d",ipt));
                        int kkk = 0;
                        for(int kk = log10(0.8*s[0])*10000.; kk <= log10(1.3*s[npoints-1])*10000.; kk++) {
                            float kk_lemma = kk/10000.;
                            float value = fitXS_log[ipt]->Eval(kk_lemma);
                            gXS_log_lemma[ipt]->SetPoint(kkk,TMath::Power(10,kk_lemma),TMath::Power(10,value));
                            kkk++;
                        }
			//gXS[ipt]->Fit("pol2");
//			fitXS[ipt]->SetRange(0.8*s[0],1.3*s[npoints-1]);
//			fitXS[ipt]->SetLineWidth(1);
//			fitXS[ipt]->Draw("same");
                        gXS_log_lemma[ipt]->SetLineColor(2);
                        gXS_log_lemma[ipt]->Draw("same");
			
			cout << "cov(0,0) = " << e00 
			<< "\ncov(1,1) = " << e11 
			<< "\ncov(2,2) = " << e22 
			<< "\ncov(0,1) = " << e01 
			<< "\ncov(0,2) = " << e02 
			<< "\ncov(1,2) = " << e12 
			<< endl;
			
//			cout << "wrong error = " << TMath::Power(10,(fitXS_log[ipt]->GetParError(0)+fitXS_log[ipt]->GetParError(1)*fitXS_log[ipt]->Eval(2.76)+fitXS_log[ipt]->GetParError(2)*fitXS_log[ipt]->Eval(2.76)*fitXS_log[ipt]->Eval(2.76))) << endl;

//wrong:			
//			cout << "naive error = " << TMath::Power(10,fitXS_log[ipt]->GetParError(0)+fitXS_log[ipt]->GetParError(1)*0.7007+fitXS_log[ipt]->GetParError(2)*0.7007*0.7007) 
//			<< " on value of " << TMath::Power(10,fitXS_log[ipt]->Eval(0.7007)) << " at 5.02 TeV " << endl;
			
                        //0.7007 = log10(5.02)
                        //0.7007 = log10(2.76)
			Double_t fullerr2 = e00 + e11*0.7007*0.7007 + e22*0.7007*0.7007*0.7007*0.7007 + 2*e01*0.7007 + 2*e02*0.7007*0.7007 + 2*e12*0.7007*0.7007*0.7007;
                        //Plan (1.,0.7007,0.7007^2)(COV)(1.,0.7007,0.7007^2):
                        Double_t where = 0.7007;
                        Double_t fullerr2_alternative = e00 + 2.*e01*where + 2.*e02*where*where + 2.*e12*where*where*where + e11*where*where + e22*where*where*where*where;
			
			cout << "full covariance error = " << TMath::Sqrt(fullerr2) << endl;
			cout << "full covariance error alternative: = " << TMath::Sqrt(fullerr2_alternative) << endl;
                        float error_in_percentage = 100.*(TMath::Power(10,TMath::Sqrt(fullerr2))-1.);
                        cout << "   on " << fitXS_log[ipt]->Eval(0.7007) << std::endl;
                        cout << "   error in percentage: " << error_in_percentage << std::endl;

                        //THIS IS FROM GLOBAL XT FIT			
			if(ptbins[ipt] > 4.5) {
				xs1[0] = cms_2760_int_pt->Eval(ptbins[ipt]);
				ey1[0] = 0.13 * xs1[0];
				gXS1[ipt] = new TGraphErrors(1,s1,xs1,ex1,ey1); gXS1[ipt]->SetName(Form("gXS1_%d",ipt));
				gXS1[ipt]->SetMarkerColor(6);
				gXS1[ipt]->SetMarkerStyle(24);
//				gXS1[ipt]->Draw("pz");

                                //5020 GeV - KK
				xs1_5020[0] = cms_5020_int_pt->Eval(ptbins[ipt]);
				ey1_5020[0] = 0.13 * xs1_5020[0];
				gXS1_5020[ipt] = new TGraphErrors(1,s1_5020,xs1_5020,ex1_5020,ey1_5020); 
                                gXS1_5020[ipt]->SetName(Form("gXS1_5020_%d",ipt));
				gXS1_5020[ipt]->SetMarkerColor(7);
				gXS1_5020[ipt]->SetMarkerStyle(24);
//				gXS1_5020[ipt]->Draw("pz");
			}
			
                        //THIS IS FROM THE FIT
			xs2[0] = fitXS_log[ipt]->Eval(0.4409);
			//ey2[0] = fitXS[ipt]->GetParError(0)+fitXS[ipt]->GetParError(1)*xs2[0]+fitXS[ipt]->GetParError(2)*xs2[0]*xs2[0]; // wrong
			//ey2[0] = fitXS[ipt]->GetParError(0)+fitXS[ipt]->GetParError(1)*2.76+fitXS[ipt]->GetParError(2)*2.76*2.76;       // ignores covariance terms
			ey2[0] = error_in_percentage*0.01*xs2[0];
//			ey2[0] = TMath::Sqrt(fullerr2);
			gXS2[ipt] = new TGraphErrors(1,s2,xs2,ex2,ey2); gXS2[ipt]->SetName(Form("gXS2_%d",ipt));
			gXS2[ipt]->SetMarkerColor(7);
			gXS2[ipt]->SetLineColor(7);
			gXS2[ipt]->SetMarkerStyle(kOpenSquare);
			gXS2[ipt]->Draw("pz");

                        //5020
			xs2_5020[0] = TMath::Power(10,fitXS_log[ipt]->Eval(0.7007));
			ey2_5020[0] = error_in_percentage*0.01*xs2_5020[0];
			gXS2_5020[ipt] = new TGraphErrors(1,s2_5020,xs2_5020,ex2_5020,ey2_5020); gXS2_5020[ipt]->SetName(Form("gXS2_5020_%d",ipt));
			gXS2_5020[ipt]->SetMarkerColor(7);
			gXS2_5020[ipt]->SetLineColor(7);
			gXS2_5020[ipt]->SetMarkerStyle(kOpenSquare);
//			gXS2_5020[ipt]->Draw("pz");
									
		}
		
		// combine direct interpolation with xt-scaling
		TGraph *gDirectInt[31000];
		TGraph *gDirectInt_09_7[31000];
		TGraph *gDirectInt_log[31000];
		TGraph *gDirectInt_09_7_log[31000];
		TF1 *fitDirectInt[31000];
		TF1 *fitDirectInt_09_7[31000];
		TF1 *fitDirectInt_log[31000];
		TF1 *fitDirectInt_09_7_log[31000];
		TH1D *h2760 = new TH1D("h2760","",7600,0.5,30);
		TH1D *h5020 = new TH1D("h5020","",7600,0.5,30);
		TH1D *h5020_To100GeV = new TH1D("h5020_To100GeV","",30400,0.5,118.5);
		TH1D *h5020_To100GeV_09_7 = new TH1D("h5020_To100GeV_09_7","",30400,0.5,118.5);
		TH1D *h5020_FromLogFit = new TH1D("h5020_FromLogFit","",7600,0.5,30);
		TH1D *h5020_To100GeV_FromLogFit = new TH1D("h5020_To100GeV_FromLogFit","",30400,0.5,118.5);
		TH1D *h5020_To100GeV_09_7_FromLogFit = new TH1D("h5020_To100GeV_09_7_FromLogFit","",30400,0.5,118.5);
//		TH1D *h2760combined = new TH1D("h2760combined","",3960,1,100);
		TH1D *h2760combined = new TH1D("h2760combined","",7920,0.5,199);

/*
                //Long range loop
		for(Int_t ipt=1; ipt<=30400; ipt++) {
		    xs[0]=h2760_EdTxt->GetBinContent(ipt); s[0]=2.76;
		    xs[1]=h7000->GetBinContent(ipt); s[1]=7.0;
		    gDirectInt_09_7[ipt] = new TGraph(2,s,xs);
		    fitDirectInt_09_7[ipt] = new TF1(Form("fitDirectInt_09_7%d",ipt),"pol1",0.3,7.2);
                    fitDirectInt_09_7[ipt]->SetParameters(-1.,1.);
		    gDirectInt_09_7[ipt]->Fit(fitDirectInt_09_7[ipt],"REMWQ");//REMW");
		    h5020_To100GeV_09_7->SetBinContent(ipt,fitDirectInt_09_7[ipt]->Eval(5.02));

                    xs_log[0]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[0]=log10(2.76);
                    xs_log[1]=log10(h7000->GetBinContent(ipt)); s_log[1]=log10(7.0);
		    gDirectInt_09_7_log[ipt] = new TGraph(2,s_log,xs_log);
		    fitDirectInt_09_7_log[ipt] = new TF1(Form("fitDirectInt_09_7_log%d",ipt),"pol1",-0.52288,0.85733);
                    gDirectInt_09_7_log[ipt]->Fit(fitDirectInt_09_7_log[ipt],"REMWQ");//REMW");
		    h5020_To100GeV_09_7_FromLogFit->SetBinContent(ipt,TMath::Power(10,fitDirectInt_09_7_log[ipt]->Eval(0.7007)));
*/
/*
                    if(ipt<=7600) {
			xs[0]=h900->GetBinContent(ipt); s[0]= 0.9;
			xs[1]=h1960->GetBinContent(ipt); s[1]=1.96;
			xs[2]=h2760_EdTxt->GetBinContent(ipt); s[2]=2.76;
			xs[3]=h7000->GetBinContent(ipt); s[3]=7.0;
			gDirectInt[ipt] = new TGraph(4,s,xs);
			fitDirectInt[ipt] = new TF1(Form("fitDirectInt%d",ipt),"pol2",0.3,7.2);
                        //try to give some initial values
                        fitDirectInt[ipt]->SetParameters(-2.46711,1.13503,-0.257744);
			gDirectInt[ipt]->Fit(fitDirectInt[ipt],"REMWQ");//REMW");
			h5020_To100GeV->SetBinContent(ipt,fitDirectInt[ipt]->Eval(5.02));

			xs_log[0]=log10(h900->GetBinContent(ipt)); s_log[0]= log10(0.9);
			xs_log[1]=log10(h1960->GetBinContent(ipt)); s_log[1]=log10(1.96);
			xs_log[2]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[2]=log10(2.76);
			xs_log[3]=log10(h7000->GetBinContent(ipt)); s_log[3]=log10(7.0);
			gDirectInt_log[ipt] = new TGraph(4,s_log,xs_log);
			fitDirectInt_log[ipt] = new TF1(Form("fitDirectInt_log%d",ipt),"pol2",-0.52288,0.85733);
			gDirectInt_log[ipt]->Fit(fitDirectInt_log[ipt],"REMWQ");//REMW");
			h5020_To100GeV_FromLogFit->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log[ipt]->Eval(0.7007)));
                    } else {
			xs[0]=h2760_EdTxt->GetBinContent(ipt); s[0]=2.76;
			xs[1]=h7000->GetBinContent(ipt); s[1]=7.0;
			gDirectInt[ipt] = new TGraph(2,s,xs);
			fitDirectInt[ipt] = new TF1(Form("fitDirectInt%d",ipt),"pol1",0.3,7.2);
                        //try to give some initial values
                        fitDirectInt[ipt]->SetParameters(-1.,1.);
			gDirectInt[ipt]->Fit(fitDirectInt[ipt],"REMWQ");//REMW");
			h5020_To100GeV->SetBinContent(ipt,fitDirectInt[ipt]->Eval(5.02));

			xs_log[0]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[0]=log10(2.76);
			xs_log[1]=log10(h7000->GetBinContent(ipt)); s_log[1]=log10(7.0);
			gDirectInt_log[ipt] = new TGraph(2,s_log,xs_log);
			fitDirectInt_log[ipt] = new TF1(Form("fitDirectInt_log%d",ipt),"pol1",-0.52288,0.85733);
			gDirectInt_log[ipt]->Fit(fitDirectInt_log[ipt],"REMWQ");//REMW");
			h5020_To100GeV_FromLogFit->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log[ipt]->Eval(0.7007)));
                    }
		}
*/
/*                
                //Lower range loop, legacy combination
		for(Int_t ipt=1; ipt<=7600; ipt++) {
//                        std::cerr<<" ---> ipt: " << ipt << std::endl;
//                        std::cerr<<"      center: " << h900->GetBinCenter(ipt) << std::endl;
			//xs[0]=h630->GetBinContent(ipt); s[0]=0.63;
			xs[0]=h900->GetBinContent(ipt); s[0]= 0.9;
			//xs[2]=h1800->GetBinContent(ipt); s[2]=1.8;
			xs[1]=h1960->GetBinContent(ipt); s[1]=1.96;
			xs[2]=h2760_EdTxt->GetBinContent(ipt); s[2]=2.76;
			xs[3]=h7000->GetBinContent(ipt); s[3]=7.0;
			gDirectInt[ipt] = new TGraph(4,s,xs);
			fitDirectInt[ipt] = new TF1(Form("fitDirectInt%d",ipt),"pol2",0.3,7.2);
                        //try to give some initial values
                        fitDirectInt[ipt]->SetParameters(-2.46711,1.13503,-0.257744);
			gDirectInt[ipt]->Fit(fitDirectInt[ipt],"REMWQ");//REMW");
			h2760->SetBinContent(ipt,fitDirectInt[ipt]->Eval(2.76));
			h5020->SetBinContent(ipt,fitDirectInt[ipt]->Eval(5.02));

			xs_log[0]=log10(h900->GetBinContent(ipt)); s_log[0]= log10(0.9);
			xs_log[1]=log10(h1960->GetBinContent(ipt)); s_log[1]=log10(1.96);
			xs_log[2]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[2]=log10(2.76);
			xs_log[3]=log10(h7000->GetBinContent(ipt)); s_log[3]=log10(7.0);
			gDirectInt_log[ipt] = new TGraph(4,s_log,xs_log);
			fitDirectInt_log[ipt] = new TF1(Form("fitDirectInt_log%d",ipt),"pol2",-0.52288,0.85733);
			gDirectInt_log[ipt]->Fit(fitDirectInt_log[ipt],"REMWQ");//REMW");
			h5020_FromLogFit->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log[ipt]->Eval(0.7007)));

			float thePtValue = h2760combined->GetBinCenter(ipt);
			if(thePtValue < 6) { // phase in xt-scaling contribution from pt = 6 - 20
				h2760combined->SetBinContent(ipt,fitDirectInt[ipt]->Eval(2.76));
			} else {
				h2760combined->SetBinContent(ipt,((20.-thePtValue)/14.)*fitDirectInt[ipt]->Eval(2.76) + ((thePtValue-6.)/14.)*cms_2760_int_pt->Eval(h2760combined->GetBinCenter(ipt)));
			}
		}
*/
//		for(Int_t ipt=761; ipt<=3960; ipt++) {
//		for(Int_t ipt=761; ipt<=7920; ipt++) {
//			h2760combined->SetBinContent(ipt,cms_2760_int_pt->Eval(h2760combined->GetBinCenter(ipt)));
//		}
			
		c5->cd(); //KK: Final low-pT fits
		h2760->SetLineColor(4);
		h2760combined->SetMarkerColor(4);
		h2760combined->SetMarkerStyle(20);
		h2760combined->SetMarkerSize(0.2);
//		h2760->Draw("same");
//		h2760combined->Draw("psame");
//		cms_2760_int_pt->Draw("same");
                h5020_To100GeV_FromLogFit->SetLineColor(7);
                h5020_To100GeV_FromLogFit->Draw("same");
                h5020_To100GeV_09_7_FromLogFit->SetLineStyle(2);
                h5020_To100GeV_09_7_FromLogFit->SetLineColor(7);
                h5020_To100GeV_09_7_FromLogFit->Draw("same");
		c1->cd(); //KK: spectra interpolation; inv. xsec. as a function of pT
//		h2760->Draw("csame");
/*
		// compare 2.76 TeV PYTHIA cross sections to combined interpolation 
		TGraph *g2760combined = new TGraph(h2760combined);
		TMVA::TSpline1 *s2760combined = new TMVA::TSpline1("s2760combined",g2760combined);
		
		TFile *fPY8 = new TFile("GEN_TrkHistGEN_2760GeV_jan08_qcdNSD_PY8_Pt0to30_eta_0.0to1.0_jet_0.0to2400.0_preTrackAna_varBin1_rebin4.root");
		//TH1D *hPY8 = (TH1D*) fPY8->Get("corrTypeTwoGEN/hInvCorr");
		TGraphErrors *gPY8 = (TGraphErrors*) fPY8->Get("corrTypeTwoGEN/tInvCorr");
		scale_graph(gPY8,6.204E+01/2);
		gPY8->SetMarkerColor(4);
		gPY8->SetMarkerStyle(kStar);
		
		TFile *fD6T = new TFile("GEN_TrkHistGEN_2760GeV_jan08_qcdNSD_D6T_Pt0to20_eta_0.0to1.0_jet_0.0to2400.0_preTrackAna_varBin1_rebin4.root");
		//TH1D *hD6T = (TH1D*) fD6T->Get("corrTypeTwoGEN/hInvCorr");
		TGraphErrors *gD6T = (TGraphErrors*) fD6T->Get("corrTypeTwoGEN/tInvCorr");
		scale_graph(gD6T,6.197E+01/2);
		gD6T->SetMarkerColor(4);
		gD6T->SetMarkerStyle(kOpenDiamond);
		
		//c5->cd();
		//gPY8->Draw("pzsame");
		//gD6T->Draw("pzsame");
		
		TCanvas *c7 = new TCanvas("c7","ratio of PYTHIA tunes to interpolation",800,500);
		TGraphErrors *rPY8 = divide_graph_by_function(gPY8,s2760combined);
		TGraphErrors *rD6T = divide_graph_by_function(gD6T,s2760combined);
		TH1D *dumPythia = new TH1D("dumPythia","Ratio of PYTHIA tunes to 2.76 TeV interpolation;p_{T} (GeV/c)",100,0,100);
		dumPythia->SetMaximum(2.0);
		dumPythia->SetMinimum(0.5);
		dumPythia->GetXaxis()->SetRangeUser(1,100);
		dumPythia->SetStats(0);
		dumPythia->Draw();
		TPave *box7 = new TPave(1,0.8,100,1.2);
		box7->SetFillColor(17);
		box7->Draw("same");
		TLine *line7 = new TLine(1,1,100,1);
		line7->SetLineStyle(3);
		line7->Draw("same");
		rPY8->Draw("psame");
		rD6T->Draw("psame");
		TLegend *leg7 = new TLegend(0.57,0.57,0.87,0.87);
		leg7->SetBorderSize(0);
		leg7->SetFillStyle(0);
		leg7->SetFillColor(0);
		leg7->AddEntry(rPY8,"PYTHIA 8","lp");
		leg7->AddEntry(rD6T,"D6T tune","lp");
		leg7->Draw();
*/		
/*		
		for(int i=0; i<9; i++) {
			float theValue = fitXS[i]->Eval(2.76);
			float theErr = gXS2[i]->GetErrorY(0);
			cout << "fractional fit error at 2.76 is " << theErr/theValue << endl;
			Double_t theXtValue=5.0, theXtValuePt=5.0;
			if(i>3) {
				gXS1[i]->GetPoint(0,theXtValuePt,theXtValue);
				cout << "ratio of xt-scaling to pt-interpolation is " << theXtValue/theValue << endl;
			}
		}
*/		
	        //Predict the 2.76 TeV points
		//Need to fit
		TGraphErrors *gDirectInt_log_test[31000];
	        TF1 *fitDirectInt_log_test[31000];
	        TH1D *h5020_predicted = new TH1D("h5020_predicted","",30400,0.5,118.5);

		for(Int_t ipt=1; ipt<=30400; ipt++) {
        	    if(ipt<=550) { //pT=2.63 GeV/c
			xs_log[0]=log10(h630->GetBinContent(ipt)); s_log[0]= log10(0.63);
			xs_log[1]=log10(h900->GetBinContent(ipt)); s_log[1]= log10(0.9);
			xs_log[2]=log10(h1800->GetBinContent(ipt)); s_log[2]=log10(1.8);
			xs_log[3]=log10(h1960->GetBinContent(ipt)); s_log[3]=log10(1.96);
			xs_log[4]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[4]=log10(2.76);
			xs_log[5]=log10(h7000->GetBinContent(ipt)); s_log[5]=log10(7.0);

                        float errorxs_KK_log[6];
                        float uncert = 1.1;
                        errorxs_KK_log[0] = fabs(log10(uncert*h630->GetBinContent(ipt))-log10(h630->GetBinContent(ipt)));
                        errorxs_KK_log[1] = fabs(log10(uncert*h900->GetBinContent(ipt))-log10(h900->GetBinContent(ipt)));
                        errorxs_KK_log[2] = fabs(log10(uncert*h1800->GetBinContent(ipt))-log10(h1800->GetBinContent(ipt)));
                        errorxs_KK_log[3] = fabs(log10(uncert*h1960->GetBinContent(ipt))-log10(h1960->GetBinContent(ipt)));
                        errorxs_KK_log[4] = fabs(log10(uncert*h2760_EdTxt->GetBinContent(ipt))-log10(h2760_EdTxt->GetBinContent(ipt)));
                        errorxs_KK_log[5] = fabs(log10(uncert*h7000->GetBinContent(ipt))-log10(h7000->GetBinContent(ipt)));

			gDirectInt_log_test[ipt] = new TGraphErrors(6,s_log,xs_log,es_log,errorxs_KK_log);
			fitDirectInt_log_test[ipt] = new TF1(Form("fitDirectInt_log_test%d",ipt),"pol2",-0.52288,0.85733);
			gDirectInt_log_test[ipt]->Fit(fitDirectInt_log_test[ipt],"REMQ");//REMW");
			h5020_predicted->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log_test[ipt]->Eval(0.7007)));
                    }
        	    if(ipt>550 && ipt<=2100) { //pT=8.65 GeV/c
			xs_log[0]=log10(h900->GetBinContent(ipt)); s_log[0]= log10(0.9);
			xs_log[1]=log10(h1800->GetBinContent(ipt)); s_log[1]=log10(1.8);
			xs_log[2]=log10(h1960->GetBinContent(ipt)); s_log[2]=log10(1.96);
			xs_log[3]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[3]=log10(2.76);
			xs_log[4]=log10(h7000->GetBinContent(ipt)); s_log[4]=log10(7.0);

                        float errorxs_KK_log[5];
                        float uncert = 1.1;
                        errorxs_KK_log[0] = fabs(log10(uncert*h900->GetBinContent(ipt))-log10(h900->GetBinContent(ipt)));
                        errorxs_KK_log[1] = fabs(log10(uncert*h1800->GetBinContent(ipt))-log10(h1800->GetBinContent(ipt)));
                        errorxs_KK_log[2] = fabs(log10(uncert*h1960->GetBinContent(ipt))-log10(h1960->GetBinContent(ipt)));
                        errorxs_KK_log[3] = fabs(log10(uncert*h2760_EdTxt->GetBinContent(ipt))-log10(h2760_EdTxt->GetBinContent(ipt)));
                        errorxs_KK_log[4] = fabs(log10(uncert*h7000->GetBinContent(ipt))-log10(h7000->GetBinContent(ipt)));

			gDirectInt_log_test[ipt] = new TGraphErrors(5,s_log,xs_log,es_log,errorxs_KK_log);
			fitDirectInt_log_test[ipt] = new TF1(Form("fitDirectInt_log_test%d",ipt),"pol2",-0.52288,0.85733);
			gDirectInt_log_test[ipt]->Fit(fitDirectInt_log_test[ipt],"REMQ");//REMW");
			h5020_predicted->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log_test[ipt]->Eval(0.7007)));
                    }
//        	    if(ipt<=7600) { //pT=30 GeV/c
        	    if(ipt>2100 && ipt<=6300) { //pT=24.95 GeV/c
			xs_log[0]=log10(h900->GetBinContent(ipt)); s_log[0]= log10(0.9);
			xs_log[1]=log10(h1960->GetBinContent(ipt)); s_log[1]=log10(1.96);
			xs_log[2]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[2]=log10(2.76);
			xs_log[3]=log10(h7000->GetBinContent(ipt)); s_log[3]=log10(7.0);

                        float errorxs_KK_log[4];
                        float uncert = 1.1;
                        errorxs_KK_log[0] = fabs(log10(uncert*h900->GetBinContent(ipt))-log10(h900->GetBinContent(ipt)));
                        errorxs_KK_log[1] = fabs(log10(uncert*h1960->GetBinContent(ipt))-log10(h1960->GetBinContent(ipt)));
                        errorxs_KK_log[2] = fabs(log10(uncert*h2760_EdTxt->GetBinContent(ipt))-log10(h2760_EdTxt->GetBinContent(ipt)));
                        errorxs_KK_log[3] = fabs(log10(uncert*h7000->GetBinContent(ipt))-log10(h7000->GetBinContent(ipt)));

			gDirectInt_log_test[ipt] = new TGraphErrors(4,s_log,xs_log,es_log,errorxs_KK_log);
			fitDirectInt_log_test[ipt] = new TF1(Form("fitDirectInt_log_test%d",ipt),"pol2",-0.52288,0.85733);
			gDirectInt_log_test[ipt]->Fit(fitDirectInt_log_test[ipt],"REMQ");//REMW");
			h5020_predicted->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log_test[ipt]->Eval(0.7007)));
                    }
        	    if(ipt>6300) { //pT=24.95 GeV/c
                        float errorxs_KK_log[2];
                        float uncert = 1.1;
                        errorxs_KK_log[0] = fabs(log10(uncert*h2760_EdTxt->GetBinContent(ipt))-log10(h2760_EdTxt->GetBinContent(ipt)));
                        errorxs_KK_log[1] = fabs(log10(uncert*h7000->GetBinContent(ipt))-log10(h7000->GetBinContent(ipt)));

			xs_log[0]=log10(h2760_EdTxt->GetBinContent(ipt)); s_log[0]= log10(2.76);
			xs_log[1]=log10(h7000->GetBinContent(ipt)); s_log[1]=log10(7.0);
			gDirectInt_log_test[ipt] = new TGraphErrors(2,s_log,xs_log,es_log,errorxs_KK_log);
			fitDirectInt_log_test[ipt] = new TF1(Form("fitDirectInt_log_test%d",ipt),"pol1",-0.52288,0.85733);
			gDirectInt_log_test[ipt]->Fit(fitDirectInt_log_test[ipt],"REMQ");//REMW");
			h5020_predicted->SetBinContent(ipt,TMath::Power(10,fitDirectInt_log_test[ipt]->Eval(0.7007)));
        	    }
   		}

		TFile *output = new TFile("plot_all_KK_LogFitForC6_Predict5020_ExtendedDataSet_RemoveWInFitAddUncert.root","RECREATE");
		h5020->Write();
		h5020_To100GeV->Write();
                h5020_To100GeV_09_7->Write();
		h5020_FromLogFit->Write();
                h5020_To100GeV_FromLogFit->Write();
                h5020_To100GeV_09_7_FromLogFit->Write();
		h2760combined->Write();

                h5020_predicted->Write();
                h2760_EdTxt->Write();
		
		output->ls();
		output->Close();

	}//end of the xT/pT loop
}

void SetStyle() {

   gStyle->SetErrorX(0);
   gStyle->SetPalette(1,0);
   gStyle->SetPadColor(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameLineColor(0);
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);

   gStyle->SetPalette(1,0);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadColor(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameLineColor(0);
   gStyle->SetTextFont(62);
   gStyle->SetLabelFont(42,"XYZ");
   gStyle->SetTitleFont(42,"XYZ");
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetTitleXSize(.045);
   gStyle->SetTitleYSize(.045);
   //gStyle->SetTitleXOffset(1.0);
   //gStyle->SetTitleYOffset(1.6);
   gStyle->SetTitleXOffset(1.2);
   //gStyle->SetTitleYOffset(2.2);
   gStyle->SetTitleYOffset(1.8);
   gStyle->SetLabelSize(0.040,"XYZ");
   gStyle->SetLabelOffset(0.01,"X");
   gStyle->SetLabelOffset(0.01,"Y");
   gStyle->SetTitleColor(1,"XYZ");
   gStyle->SetHistFillColor(1);
   gStyle->SetHistFillStyle(0);
   gStyle->SetHistLineColor(1);
   gStyle->SetHistLineStyle(0);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistLineWidth(1);
   gStyle->SetEndErrorSize(0);
   gStyle->SetErrorX(0);
   gStyle->SetMarkerStyle(20);
   //gStyle->SetMarkerSize(1.25);
   gStyle->SetMarkerSize(1.5);

   gStyle->SetOptFit(1111);
   gStyle->SetStatColor(0);
   gStyle->SetStatBorderSize(1);
   gStyle->SetOptTitle(0);
   //gStyle->SetOptStat(1111);
   //gStyle->SetOptStat(0);


   gStyle->SetPadLeftMargin(0.17);
   //gStyle->SetPadLeftMargin(0.21);
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.04);


   const Int_t NRGBs = 5;
   //const Int_t NCont = 255;
   const Int_t NCont = 200;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   //gStyle->CreateColorGradientTable(NRGBs, stops, red, green, blue, NCont);

   gStyle->SetNumberContours(NCont);

   gROOT->ForceStyle();
}

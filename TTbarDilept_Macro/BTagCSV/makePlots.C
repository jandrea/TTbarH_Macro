void addbin(TH1D*);
double errfMC(double,double,double,double);

void makePlots()
{
   gROOT->ProcessLine(".x PlotStyle.C");

   TCanvas *c1 = new TCanvas("c1","c1",1000,800);
   c1->SetBottomMargin(0.3);
   c1->cd();

   TFile *f = TFile::Open("hist/sig.root");

   const int nPt = 16;
   std::string ptName[nPt] = 
     {
	"pt20t30","pt30t40","pt40t50","pt50t60","pt60t70","pt70t80","pt80t100",
	"pt100t120","pt120t160","pt160t210","pt210t260","pt260t320","pt320t400",
	"pt400t500","pt500t600","pt600t800"	
     };
   
   for(int i=0;i<nPt;i++)
     {	
	std::string hname = "h_bjet_CSV_"+ptName[i];
	TH1D *h_bjet_CSV = (TH1D*)f->Get(hname.c_str());
	addbin(h_bjet_CSV);

	double eff[5];
	eff[0] = 1.;
	eff[4] = 0.;

	double effCorr[5];
	effCorr[0] = 1.;
	effCorr[4] = 0.;
	
	double err[5];
	err[0] = 0.;
	err[4] = 0.;

	double errCorr[5];
	errCorr[0] = 0.;
	errCorr[4] = 0.;

	double deleff[5];
	deleff[0] = 0.;
	deleff[4] = 0.;

	double delerr[5];
	delerr[0] = 0.;
	delerr[4] = 0.;
	
	int nb = h_bjet_CSV->GetXaxis()->GetNbins();
	double intErr0 = 0.;
	double int0 = h_bjet_CSV->IntegralAndError(1,nb,intErr0);
	for(int ib=1;ib<nb;ib++)
	  {
	     double intSum = 0.;
	     double intSumErr = 0.;
	     for(int ibb=ib+1;ibb<=nb;ibb++)
	       {
		  intSum += h_bjet_CSV->GetBinContent(ibb);
		  intSumErr += pow(h_bjet_CSV->GetBinError(ibb),2);
	       }
	     intSumErr = sqrt(intSumErr);
	     
	     eff[ib] = (int0 > 0.) ? intSum/int0 : 0.;
	     err[ib] = errfMC(intSum,intSumErr,int0,intErr0);
	     
	     double sfc = SF(i,"b",ib-1).first;
	     double sferrc = SF(i,"b",ib-1).second;
	     
	     effCorr[ib] = eff[ib] * sfc;
	     errCorr[ib] = sqrt(pow(err[ib]*sfc,2)+pow(eff[ib]*sferrc,2));
	     
	     deleff[ib] = eff[ib] - effCorr[ib];
//	     delerr[ib] = 
	  }
	
	double x[5] = {0.,0.244,0.679,0.898,1.};
	double xerr[5] = {0.,0.,0.,0.,0.};
	
	TGraphErrors *gr = new TGraphErrors(5,x,eff,xerr,err);
	TGraphErrors *grCorr = new TGraphErrors(5,x,effCorr,xerr,errCorr);
	TGraphErrors *grDel = new TGraphErrors(5,x,deleff,xerr,err);// FIXME
	
	gr->SetMarkerStyle(20);
	gr->SetMarkerSize(1.0);
	gr->SetMarkerColor(kBlack);
	gr->SetLineColor(kBlack);

	grCorr->SetMarkerStyle(22);
	grCorr->SetMarkerSize(1.0);
	grCorr->SetMarkerColor(kRed);
	grCorr->SetLineColor(kRed);
	
	gr->Draw("AP");
	grCorr->Draw("PS");

	gr->GetXaxis()->SetTitle("CSV discriminant");
	gr->GetYaxis()->SetTitle("Efficiency");
	gr->GetXaxis()->SetRangeUser(0.,1.);

	TLegend *leg = new TLegend(0.65,0.90,0.88,0.75);
	leg->SetFillColor(253);
	leg->SetBorderSize(0);
	leg->AddEntry(gr,"MC","lp");
	leg->AddEntry(grCorr,"MC(corrected)","lp");
	leg->Draw();
	
	std::string pname = "pics/bjetCSV_"+ptName[i]+".eps";
	c1->Print(pname.c_str());
	c1->Clear();

	grDel->SetMarkerStyle(20);
	grDel->SetMarkerSize(1.0);
	grDel->SetMarkerColor(kBlack);
	grDel->SetLineColor(kBlack);
	
	grDel->Draw("AP");

	grDel->GetXaxis()->SetTitle("CSV discriminant");
	grDel->GetYaxis()->SetTitle("Efficiency");
	grDel->GetXaxis()->SetRangeUser(0.,1.);

//	delta_eff(x) = eff_data - eff_mc = c_1*(1-x)+c_2*(1-x)^2+(-c_1-c_2)*(1-x)^3
//	  c_1*(1-x)+c_2*(1-x)^2+c_3*(1-x)^3+(-c_1-c_2-c_3)*(1-x)^4
	
	TLegend *leg = new TLegend(0.35,0.90,0.55,0.75);
	leg->SetFillColor(253);
	leg->SetBorderSize(0);
	leg->AddEntry(grDel,"#epsilon_{Corrected}-#epsilon_{MC}","lp");
	leg->Draw();

	pname = "pics/bjetCSVDel_"+ptName[i]+".eps";
	c1->Print(pname.c_str());
	c1->Clear();
	
	delete leg;
	delete gr;
	delete grCorr;
     }

   gApplication->Terminate();
}

void addbin(TH1D *h)
{   
   // Add overflow and underflow bins
   Int_t x_nbins = h->GetXaxis()->GetNbins();
   h->SetBinContent(1,h->GetBinContent(0)+h->GetBinContent(1));
   h->SetBinError(1,TMath::Sqrt(pow(h->GetBinError(0),2)+pow(h->GetBinError(1),2)));
   h->SetBinContent(x_nbins,h->GetBinContent(x_nbins)+h->GetBinContent(x_nbins+1));
   h->SetBinError(x_nbins,TMath::Sqrt(pow(h->GetBinError(x_nbins),2)+
				      pow(h->GetBinError(x_nbins+1),2)));
   // Set overflow and underflow bins to 0
   h->SetBinContent(0,0.);
   h->SetBinError(0,0.);
   h->SetBinContent(x_nbins+1,0.);
   h->SetBinError(x_nbins+1,0.);
}

std::pair<float,float> SF(int idx,std::string flav,int wp)
{
   float sf = 1.;
   float sferr = 0.;
   
   std::pair<float,float> sfp;
   sfp.first = sf;
   sfp.second = sferr;

   float SFb_CSVL_error[16] =
     {	
	0.033299,
	0.0146768,
	0.013803,
	0.0170145,
	0.0166976,
	0.0137879,
	0.0149072,
	0.0153068,
	0.0133077,
	0.0123737,
	0.0157152,
	0.0175161,
	0.0209241,
	0.0278605,
	0.0346928,
	0.0350099 
     };
   
   float SFb_CSVM_error[16] =
     {	
	0.0415707,
	0.0204209,
	0.0223227,
	0.0206655,
	0.0199325,
	0.0174121,
	0.0202332,
	0.0182446,
	0.0159777,
	0.0218531,
	0.0204688,
	0.0265191,
	0.0313175,
	0.0415417,
	0.0740446,
	0.0596716 
     };
   
   float SFb_CSVT_error[16] =
     {	
	0.0515703,
	0.0264008,
	0.0272757,
	0.0275565,
	0.0248745,
	0.0218456,
	0.0253845,
	0.0239588,
	0.0271791,
	0.0273912,
	0.0379822,
	0.0411624,
	0.0786307,
	0.0866832,
	0.0942053,
	0.102403 
     };
   
   float jpt = 0.;
   if( idx == 0 ) jpt = 25.;
   else if( idx == 1 ) jpt = 35.;
   else if( idx == 2 ) jpt = 45.;
   else if( idx == 3 ) jpt = 55.;
   else if( idx == 4 ) jpt = 65.;
   else if( idx == 5 ) jpt = 75.;
   else if( idx == 6 ) jpt = 90.;
   else if( idx == 7 ) jpt = 110.;
   else if( idx == 8 ) jpt = 140.;
   else if( idx == 9 ) jpt = 185.;
   else if( idx == 10 ) jpt = 235.;
   else if( idx == 11 ) jpt = 290.;
   else if( idx == 12 ) jpt = 360.;
   else if( idx == 13 ) jpt = 450.;
   else if( idx == 14 ) jpt = 550.;
   else if( idx == 15 ) jpt = 700.;
   
   if( flav == "b" || flav == "c" )
     {	
	if( wp == 0 )
	  {
	     sf = 0.997942*((1.+(0.00923753*jpt))/(1.+(0.0096119*jpt)));
	     sferr = SFb_CSVL_error[idx];
	     if( flav == "c" ) sferr *= 2;
	  }	
	else if( wp == 1 )
	  {
	     sf = (0.938887+(0.00017124*jpt))+(-2.76366e-07*(jpt*jpt));
	     sferr = SFb_CSVM_error[idx];
	     if( flav == "c" ) sferr *= 2;
	  }       
	else if( wp == 2 )
	  {
	     sf = (0.927563+(1.55479e-05*jpt))+(-1.90666e-07*(jpt*jpt));
	     sferr = SFb_CSVT_error[idx];
	     if( flav == "c" ) sferr *= 2;
	  }	
     }   

   sfp.first = sf;
   sfp.second = sferr;
   
   return sfp;
}

double errfMC(double v1,double ve1,double v2,double ve2)
{
   if( v2 == 0 ) return -666;

   double err = pow(v2-v1,2)*ve1*ve1/pow(v2,4) +                                                                            
     v1*v1*(ve2*ve2-ve1*ve1)/pow(v2,4);                                                                                     
   
   err = sqrt(err);                                                                                                         
   
   return err;                                                                                                              
}

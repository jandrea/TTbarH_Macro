#include "TH1F.h"
#include "TFile.h"

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TString.h"
#include "TLine.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"


void DoToyPlots(bool doBias){
  
   
  gStyle->SetOptFit(0111);
  gStyle->SetOptStat(0);   
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0); // must be kWhite but I dunno how to do that in PyROOT  
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
 
  TCanvas *c1 = new TCanvas("c1","c1", 1000, 800);
  c1->cd();

  
  //output file
  TFile * inputfile = new TFile("output_pseudo.root");
  
  
  std::vector<TH1F*> thehistvect;
  std::vector<TString> thehistonames;
  if(doBias){
    thehistonames.push_back("theBias0p5");
    thehistonames.push_back("theBias0p6");
    thehistonames.push_back("theBias0p7");
    thehistonames.push_back("theBias0p8");
    thehistonames.push_back("theBias0p9");
    thehistonames.push_back("theBias1p0");
    thehistonames.push_back("theBias1p1");
    thehistonames.push_back("theBias1p2");
    thehistonames.push_back("theBias1p3");
    thehistonames.push_back("theBias1p4");
    thehistonames.push_back("theBias1p5");
  }else{
    thehistonames.push_back("thePull0p5");
    thehistonames.push_back("thePull0p6");
    thehistonames.push_back("thePull0p7");
    thehistonames.push_back("thePull0p8");
    thehistonames.push_back("thePull0p9");
    thehistonames.push_back("thePull1p0");
    thehistonames.push_back("thePull1p1");
    thehistonames.push_back("thePull1p2");
    thehistonames.push_back("thePull1p3");
    thehistonames.push_back("thePull1p4");
    thehistonames.push_back("thePull1p5");
  }
  
  float scan_mean[11],scan_mean_err[11]; 
  float scan_relmean[11],  scan_relmean_err[11];
      
  for(int i=0; i<11; i++){
    TH1F* tmpshist = (TH1F*)inputfile->Get( thehistonames[i].Data() )->Clone();
    TF1 * gaustmp = new TF1("gaustmp", "gaus", 0, 2 );
    tmpshist->Fit(gaustmp);
  
    if(doBias){
      scan_mean[i] = gaustmp->GetParameter(1);
      scan_mean_err[i] = gaustmp->GetParError(1);
    }else{
      scan_mean[i] = gaustmp->GetParameter(2);
      scan_mean_err[i] = gaustmp->GetParError(2);
    }
    
    if(i==0) scan_relmean[i]  = 0.5;
    if(i==1) scan_relmean[i]  = 0.6;
    if(i==2) scan_relmean[i]  = 0.7;
    if(i==3) scan_relmean[i]  = 0.8;
    if(i==4) scan_relmean[i]  = 0.9;
    if(i==5) scan_relmean[i]  = 1.0;
    if(i==6) scan_relmean[i]  = 1.1;
    if(i==7) scan_relmean[i]  = 1.2;
    if(i==8) scan_relmean[i]  = 1.3;
    if(i==9) scan_relmean[i]  = 1.4;
    if(i==10) scan_relmean[i] = 1.5;
    scan_relmean_err[i]=0;
    
    
    if(i==5){
      TCanvas *cbias = new TCanvas("cbias","cbias", 1000, 800);
      cbias->cd();
      tmpshist->Draw();
      gaustmp->Draw("same");
      if(doBias) cbias->SaveAs("example_toy_bias.gif");
      else cbias->SaveAs("example_toy_pull.gif");
    }
    
    
    delete gaustmp;
  }
  
  TCanvas *cbias_2D = new TCanvas("cbias_2D","cbias_2D", 1000, 800);
  cbias_2D->cd();
  TGraphErrors* graph_scan ;
  if(doBias) graph_scan= new TGraphErrors(11, scan_mean,   scan_relmean, scan_mean_err,   scan_relmean_err);
  else       graph_scan= new TGraphErrors(11, scan_relmean, scan_mean,   scan_relmean_err, scan_mean_err  );
  
  TH1F * thescanhisto  = new TH1F("thescanhisto", "thescanhisto", 100, 0.4, 1.6);
  thescanhisto->SetMaximum(1.6);
  thescanhisto->SetMinimum(0.4);
  thescanhisto->GetYaxis()->SetTitle("simulated signal strength");
  thescanhisto->GetYaxis()->SetTitleOffset(1.3);
  thescanhisto->GetXaxis()->SetTitle("estimated signal strength");
  if(!doBias){
    thescanhisto->GetYaxis()->SetTitle("pull width");
    thescanhisto->GetXaxis()->SetTitle("simulated signal strength");
  }
  thescanhisto->Draw();
  graph_scan->SetMarkerStyle(20);
  graph_scan->Draw("epsame");
  TLine * thelinepull = new TLine(0.4, 0.4, 1.6, 1.6);
  thelinepull->SetLineColor(2);
  if(doBias){
    thelinepull->Draw("same");
    graph_scan->Fit("pol1");
    cbias_2D->SaveAs("bias_scan_results.gif");
  }else{
    graph_scan->Fit("pol0");
  }
}


void DoToyPlots(){
  
  
  DoToyPlots(false);


  
}

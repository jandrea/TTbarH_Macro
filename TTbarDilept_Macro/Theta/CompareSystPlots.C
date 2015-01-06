
#include "TString.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"
#include <iostream>



void CompareSystPlots(TString var, TString syst, TString process){
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0); // must be kWhite but I dunno how to do that in PyROOT  
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");

 
  //TFile * inputfile_fit = new TFile("RootFiles/Template_JES_JER_BTag_LES_Q2_Mpts_VVsplit.root");
  //TFile * inputfile_fit = new TFile("theta_histofiles.root");
  TFile * inputfile_fit = new TFile("../TreeReader/outputroot/histofile_merged.root");

  TH1F * hist_comp_         = (TH1F*)inputfile_fit->Get( (var+"__"+process).Data() )->Clone();
  TH1F * hist_comp___minus  = (TH1F*)inputfile_fit->Get( (var+"__"+process+"__"+syst+"__minus").Data() )->Clone();
  TH1F * hist_comp___plus   = (TH1F*)inputfile_fit->Get( (var+"__"+process+"__"+syst+"__plus").Data() )->Clone();
  
  
  TCanvas *c1 = new TCanvas("c1","c1", 1000, 800);
  c1->cd();

  /*
  hist_comp_->GetXaxis()->SetBinLabel(1, "(0,0)");
  hist_comp_->GetXaxis()->SetBinLabel(2, "(1,0)");
  hist_comp_->GetXaxis()->SetBinLabel(3, "(1,1)");
  hist_comp_->GetXaxis()->SetBinLabel(4, "(2,0)");
  hist_comp_->GetXaxis()->SetBinLabel(5, "(2,1)");
  hist_comp_->GetXaxis()->SetBinLabel(6, "(2,2)");
  hist_comp_->GetXaxis()->SetBinLabel(7, "(3,0)");
  hist_comp_->GetXaxis()->SetBinLabel(8, "(3,1)");
  hist_comp_->GetXaxis()->SetBinLabel(9, "(3,2)");
  hist_comp_->GetXaxis()->SetBinLabel(10, "(3,3)");
  hist_comp_->GetXaxis()->SetBinLabel(11, "(4,0)");
  hist_comp_->GetXaxis()->SetBinLabel(12, "(4,1)");
  hist_comp_->GetXaxis()->SetBinLabel(13, "(4,2)");
  hist_comp_->GetXaxis()->SetBinLabel(14, "(4,3)");
  hist_comp_->GetXaxis()->SetBinLabel(14, "(4,>3)");
  hist_comp_->GetXaxis()->SetTitle("(NJets, NBJets)");*/
  hist_comp_->SetTitle("");
  
  
  hist_comp_->       SetLineColor(1);
  hist_comp___minus->SetLineColor(2);
  hist_comp___plus-> SetLineColor(4);
  
  
  hist_comp_->       SetLineWidth(3);
  hist_comp___minus->SetLineWidth(3);
  hist_comp___plus-> SetLineWidth(3);
  
  
  hist_comp_->Draw("");
  hist_comp___minus->Draw("same");
  hist_comp___plus->Draw("same");
  
   
  TLegend* qw = new TLegend(.45,.60,.85,.85);
  qw->SetShadowColor(0);
  qw->SetFillColor(0);
  qw->SetLineColor(0);
  qw->AddEntry(hist_comp_,          (var+"__"+process).Data() , "l");
  qw->AddEntry(hist_comp___minus,   (var+"__"+process+"__"+syst+"__minus").Data()  , "l");
  qw->AddEntry(hist_comp___plus,    (var+"__"+process+"__"+syst+"__plus").Data()  , "l");
 
  qw->Draw();
  c1->SaveAs( ("plots/"+var+"__"+process+"__"+syst+".gif").Data());
}

void CompareSystPlots(){
  //CompareSystPlots(TString var, TString syst, TString process)
  //CompareSystPlots("NJetsNBJetsSup3Jet_emu_afterZsel", "btag", "TT");
  CompareSystPlots("NJetsNBJetsemuafterZsel", "scale", "TT");
  //CompareSystPlots("BTAgProba_emu_afterleptsel", "btag", "TT");
  
}

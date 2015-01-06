
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

void CompareDistrib(TString var, TString selstep, std::vector<TString > process){
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0); // must be kWhite but I dunno how to do that in PyROOT  
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");

 
  //TFile * inputfile_fit = new TFile("RootFiles/Template_JES_JER_BTag_LES_Q2_Mpts_VVsplit.root");
  TFile * inputfile_fit = new TFile("outputroot/histofile_merged.root");
  
  
  std::vector<TString > thechannels;
  thechannels.push_back("mumumu");
  thechannels.push_back("mumue");
  thechannels.push_back("eemu");
  thechannels.push_back("eee");
  
  std::vector<TH1F*> theFinalHist;
  
  for(unsigned int h=0; h<process.size(); h++){
    TH1F *hist_comp = 0;
    for(unsigned int i=0; i<thechannels.size(); i++){
       TString namehisto = var+"_"+thechannels[i]+"_"+selstep+"__"+process[h];
       cout <<  "histo name " <<  namehisto << endl;
       if(i==0) hist_comp        = (TH1F*)inputfile_fit->Get( (namehisto).Data() )->Clone();
       else hist_comp->Add(        (TH1F*)inputfile_fit->Get( (namehisto).Data() )->Clone());
    }
    theFinalHist.push_back(hist_comp);
    theFinalHist[h]->SetLineWidth(1.2);
    theFinalHist[h]->SetLineColor(1+h);
   }
  
  
  for(unsigned int i=0; i<theFinalHist.size(); i++){
    if(i==0) theFinalHist[i]->DrawNormalized("h");
    else theFinalHist[i]->DrawNormalized("hsame");
  }
  
}

void CompareDistrib(){
  std::vector<TString > process;
   process.push_back("tZq");
   process.push_back("TTW");
   process.push_back("TTZ");
   
  CompareDistrib("NJet", "afterbjetsel", process);
  
  
  
  
}

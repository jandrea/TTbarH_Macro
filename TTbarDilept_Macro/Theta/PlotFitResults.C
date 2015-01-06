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


void PlotFitResults(  std::vector<TString> mcSample_list, std::vector<int> colorVector, bool usePostFit, TString inputdistrib , TString inputfilename, TString outputplotname){
  
  
      
  Int_t stati=0;
  Bool_t  fit=1;
  Bool_t logy=0;
  
  bool setlogy = 0;
  
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0); // must be kWhite but I dunno how to do that in PyROOT
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);
  
  
  // For the Pad:
  gStyle->SetPadBorderMode(0);
  // ROOT . gStyle . SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(0); // kWhite
  gStyle->SetPadGridX(0); //false
  gStyle->SetPadGridY(0); //false
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  // For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);
  
  // For the histo:rebin
  // ROOT . gStyle . SetHistFillColor(1);
  // ROOT . gStyle . SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(1);
  // ROOT . gStyle . SetLegoInnerR(Float_t rad = 0.5);
  // ROOT . gStyle . SetNumberContours(Int_t number = 20);
  
  gStyle->SetEndErrorSize(2);
  //ROOT . gStyle . SetErrorMarker(20);   /// I COMMENTED THIS OUT
  //ROOT . gStyle . SetErrorX(0.);
  
  //ROOT . gStyle . SetMarkerStyle(20);
  
  
  //For the fit/function:
  gStyle->SetOptFit(1011);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);
  
  //For the date:
  gStyle->SetOptDate(0);
  // ROOT . gStyle . SetDateX(Float_t x = 0.01);
  // ROOT . gStyle . SetDateY(Float_t y = 0.01);
  
  // For the statistics box:
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(0); // kWhite
  gStyle->SetStatFont(42);
  //ROOT . gStyle . SetStatFontSize(0.025);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);
  // ROOT . gStyle . SetStatStyle(Style_t style = 1001);
  // ROOT . gStyle . SetStatX(Float_t x = 0);
  // ROOT . gStyle . SetStatY(Float_t y = 0);
  
  // Margins:
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.16);
  //ROOT . gStyle . SetPadRightMargin(0.12);
  gStyle->SetPadRightMargin(0.03);
  
  // For the Global title:
  
  gStyle->SetOptTitle(0);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.05);
  // ROOT . gStyle . SetTitleH(0); // Set the height of the title box
  // ROOT . gStyle . SetTitleW(0); // Set the width of the title box
  // ROOT . gStyle . SetTitleX(0); // Set the position of the title box
  // ROOT . gStyle . SetTitleY(0.985); // Set the position of the title box
  // ROOT . gStyle . SetTitleStyle(Style_t style = 1001);
  // ROOT . gStyle . SetTitleBorderSize(2);
  
  // For the axis titles:
  
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // ROOT . gStyle . SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // ROOT . gStyle . SetTitleYSize(Float_t size = 0.02);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.25);
  // ROOT . gStyle . SetTitleOffset(1.1, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");
  
  // For the axis:
  
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(1); // kTRUE
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);
  
  // Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  
  // Postscript options:
  gStyle->SetPaperSize(20.,20.);
  // ROOT . gStyle . SetLineScalePS(Float_t scale = 3);
  // ROOT . gStyle . SetLineStyleString(Int_t i, const char* text);
  // ROOT . gStyle . SetHeaderPS(const char* header);
  // ROOT . gStyle . SetTitlePS(const char* pstitle);
  
  // ROOT . gStyle . SetBarOffset(Float_t baroff = 0.5);
  // ROOT . gStyle . SetBarWidth(Float_t barwidth = 0.5);
  // ROOT . gStyle . SetPaintTextFormat(const char* format = "g");
  // ROOT . gStyle . SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // ROOT . gStyle . SetTimeOffset(Double_t toffset);
  // ROOT . gStyle . SetHistMinimumZero(kTRUE);
  
  
  //TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
  TCanvas *c1 = new TCanvas("c1","c1", 1000, 800);
  c1->SetBottomMargin(0.3);
  c1->SetLogy(setlogy);
  c1->cd();
   
  TFile * inputfile_fit ;
  if(usePostFit) inputfile_fit = new TFile("histos-mle_TT.root");
  else  inputfile_fit = new TFile(inputfilename);
  
  TFile * inputfile_data =  new TFile("theta_histofiles.root");
  
  TFile * inputfile	  = new TFile( inputfilename.Data() );
  TH1F * histo_data       = (TH1F*)inputfile_data->Get( (inputdistrib+"__DATA").Data() )->Clone();
  
  
 
  
  std::vector<TH1F *> histo_mcSamples;  
  
  for(unsigned int imc = 0; imc < mcSample_list.size(); imc++){
    
    TString histo_mc_name   = inputdistrib+ "__"+ mcSample_list[imc];
    TH1F * histo_tmp = (TH1F*)inputfile->Get(histo_mc_name);
    histo_mcSamples.push_back(histo_tmp); 
  }
  
  THStack *the_stack_histo= new THStack();
  for(unsigned int imc = 0; imc< histo_mcSamples.size(); imc++){
    
    histo_mcSamples[imc]->SetFillStyle(1001);
    histo_mcSamples[imc]->SetFillColor(colorVector[imc]);
    histo_mcSamples[imc]->SetLineColor(colorVector[imc]);
    if(imc < histo_mcSamples.size() && colorVector[imc] != colorVector[imc+1] )  histo_mcSamples[imc]->SetLineColor(1);
    if(imc ==  histo_mcSamples.size()) histo_mcSamples[imc]->SetLineColor(1);
    the_stack_histo->Add(histo_mcSamples[imc]);
  }  
  
    the_stack_histo->Draw("h");
  the_stack_histo->GetXaxis()->SetLabelSize(0.0);
  the_stack_histo->GetYaxis()->SetLabelSize(0.04);
  if(histo_data->GetMaximum() > the_stack_histo->GetMaximum() ) the_stack_histo->SetMaximum(histo_data->GetMaximum()+0.1*histo_data->GetMaximum());
  else the_stack_histo->SetMaximum(the_stack_histo->GetMaximum()+0.1*the_stack_histo->GetMaximum());

  
  
  
  
  
  histo_data->SetMarkerStyle(20);
  histo_data->SetMarkerSize(1.2);
  histo_data->SetLineColor(1);
  histo_data->Draw("epsame");
  
   
  //--------------------------
  //MC systematic plot
  //--------------------------
  TH1F * histo_syst_MC   = (TH1F*)(the_stack_histo->GetHistogram() )->Clone();
  for(unsigned int imc=0; imc< histo_mcSamples.size(); imc++){
    histo_syst_MC->Add(histo_mcSamples[imc]);
  }
  
  
  
  for (int ibin=0; ibin<histo_syst_MC->GetNbinsX(); ibin++) {
    //histo_syst_MC->SetBinError(ibin, histo_syst_MC->GetBinError(ibin)+histo_syst_MC->GetBinError(ibin)*0.025);
    
  }
  TGraphErrors *thegraph = new TGraphErrors(histo_syst_MC);
  thegraph->SetFillStyle(3005);
  thegraph->SetFillColor(1);
  thegraph->Draw("e2same");
  
 
  
  
  //-------------------
  //legend and captions
  //-------------------
  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->SetTextAlign(31); 
  latex->DrawLatex(0.45, 0.95, "CMS Preliminary");
  
  
  
  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.04);
  latex2->SetTextAlign(31); 
  latex2->DrawLatex(0.87, 0.95, "19.7 fb^{-1} at #sqrt{s} = 8 TeV");
  
  TString info_data = "emu channel";
  
  
  TLatex * text2 = new TLatex(0.45,0.98, info_data);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.18);
  text2->SetY(0.92);
  //text2->SetLineWidth(2);
  text2->SetTextFont(42);
  text2->SetTextSize(0.0610687);
  //    text2->SetTextSizePixels(24);// dflt=28
  text2->Draw();
  
  
  TLegend*  qw = new TLegend(.80,.60,.95,.90);

  qw->SetShadowColor(0);
  qw->SetFillColor(0);
  qw->SetLineColor(0);
  
  
  qw->AddEntry(histo_data,         "Data" ,                "ep");
  for(unsigned int i=0; i<mcSample_list.size(); i++){
    if(mcSample_list[i] == "TT"        ) qw->AddEntry( histo_mcSamples[0],	"t#bar{t}"	 ,"f");
    if(mcSample_list[i] == "TTljets"   ) qw->AddEntry( histo_mcSamples[1],	"t#bar{t} bkg"	 ,"f");
    if(mcSample_list[i] == "Zjets"     ) qw->AddEntry( histo_mcSamples[2],	"DY"		 ,"f");
    if(mcSample_list[i] == "barsChan"  ) qw->AddEntry( histo_mcSamples[3],	"single top"	 ,"f");
    if(mcSample_list[i] == "WZ"        ) qw->AddEntry( histo_mcSamples[11],	"VV"		 ,"f");
    if(mcSample_list[i] == "TTZ"       ) qw->AddEntry( histo_mcSamples[9],	"t#bar{t}V"	 ,"f");
  }
  
  
  
  
  
  qw->Draw();
  
  
  
  //--------------------------
  //Data over background ratio
  //--------------------------
  
   //TPad *canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.34);
  TPad *canvas_2 = new TPad("canvas_2", "canvas_2", 0.0, 0.0, 1.0, 1.0);
  canvas_2->SetTopMargin(0.7);
  canvas_2->SetFillColor(0);
  canvas_2->SetFillStyle(0);
  canvas_2->SetGridy(1);
  canvas_2->Draw();
  canvas_2->cd(0);
  
  
  
  
  TH1F * histo_ratio_data = (TH1F*)histo_data->Clone();
  histo_ratio_data->Divide(histo_syst_MC);
  
  //double theX[thegraph->GetN()] = thegraph->GetX();
  TGraphErrors *thegraph_tmp = (TGraphErrors*) thegraph->Clone();
  
  double *theErrorX  = thegraph_tmp->GetEX();
  double *theErrorY  = thegraph_tmp->GetEY();
  double *theY       = thegraph_tmp->GetY() ;
  for(int i=0; i<thegraph_tmp->GetN(); i++){
    theErrorY[i] = theErrorY[i]/theY[i];
    theY[i]=1;
  }
  
  
  
  TGraphErrors *thegraph_ratio = new TGraphErrors(thegraph_tmp->GetN(), thegraph_tmp->GetX() , theY ,  thegraph_tmp->GetEX(),     thegraph_tmp->GetEY() );
  thegraph_ratio->SetFillStyle(3005);
  thegraph_ratio->SetFillColor(1);
 
  histo_ratio_data->SetMinimum(0.5);
  histo_ratio_data->SetMaximum(1.5);
  histo_ratio_data->GetXaxis()->SetTitleOffset(1.2);
  histo_ratio_data->GetXaxis()->SetLabelSize(0.04);
  histo_ratio_data->GetYaxis()->SetLabelSize(0.03);
  histo_ratio_data->GetYaxis()->SetNdivisions(6);
  histo_ratio_data->GetYaxis()->SetTitleSize(0.03);
  
  if(inputdistrib == "NJetsNBJetsSup3JetmuafterZsel"){
  
    histo_ratio_data->GetXaxis()->SetBinLabel(1, "(0,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(2, "(1,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(3, "(1,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(4, "(2,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(5, "(2,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(6, "(2,2)");
    histo_ratio_data->GetXaxis()->SetBinLabel(7, "(#geq3,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(8, "(#geq3,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(9, "(#geq3,2)");
    histo_ratio_data->GetXaxis()->SetBinLabel(10, "(#geq3,#geq3)");
  
  
  }
  
  if(inputdistrib=="NJetsNBJetsemuafterZsel"){
    histo_ratio_data->GetXaxis()->SetBinLabel(1, "(0,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(2, "(1,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(3, "(1,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(4, "(2,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(5, "(2,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(6, "(2,2)");
    histo_ratio_data->GetXaxis()->SetBinLabel(7, "(3,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(8, "(3,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(9, "(3,2)");
    histo_ratio_data->GetXaxis()->SetBinLabel(10, "(3,3)");
    histo_ratio_data->GetXaxis()->SetBinLabel(11, "(#geq 4,0)");
    histo_ratio_data->GetXaxis()->SetBinLabel(12, "(#geq4,1)");
    histo_ratio_data->GetXaxis()->SetBinLabel(13, "(#geq4,2)");
    histo_ratio_data->GetXaxis()->SetBinLabel(14, "(#geq4,3)");
    histo_ratio_data->GetXaxis()->SetBinLabel(14, "(#geq4,#geq 4)");
    histo_ratio_data->GetXaxis()->SetTitle("(NJets,NBjets)");
  }
   
  
  histo_ratio_data->Draw("E1X0");
  
  
  thegraph_ratio->Draw("e2same");
  
  
  

  c1->SaveAs( (outputplotname+".pdf").Data());
 
}


void PlotFitResults(){


   //-------------------------
 //define list of MC samples 
  std::vector<TString> mcSample_list;
  std::vector<int> colorVector;
  mcSample_list.push_back("TT");            colorVector.push_back(kRed+1);
  mcSample_list.push_back("TTljets");            colorVector.push_back(kRed+2);
  mcSample_list.push_back("Zjets");         colorVector.push_back(kAzure-2);
  mcSample_list.push_back("barsChan");     colorVector.push_back(kMagenta);
  mcSample_list.push_back("sChan");        colorVector.push_back(kMagenta);
  mcSample_list.push_back("tChan");        colorVector.push_back(kMagenta);
  mcSample_list.push_back("bartChan");     colorVector.push_back(kMagenta);
  mcSample_list.push_back("tW");           colorVector.push_back(kMagenta);
  mcSample_list.push_back("bartW");        colorVector.push_back(kMagenta);
  mcSample_list.push_back("TTZ");           colorVector.push_back(kRed-7);
  mcSample_list.push_back("TTW");           colorVector.push_back(kRed-7);
  mcSample_list.push_back("WZ");            colorVector.push_back(13);
  mcSample_list.push_back("ZZ");            colorVector.push_back(13);
  mcSample_list.push_back("WW");            colorVector.push_back(13);
  //mcSample_list.push_back("WZHF");            colorVector.push_back(12);
  //mcSample_list.push_back("DYToLL_M10-50"); colorVector.push_back(kAzure-2);
  mcSample_list.push_back("tZq");           colorVector.push_back(kGreen+2);
  
  
  
  
 
  
  
  
  
  
  //PlotFitResults(mcSample_list,colorVector,  false, "NJetsNBJetsemuafterZsel", "theta_histofiles.root", "PreFit_NJetsNBjets_CSVT");
  PlotFitResults(mcSample_list,colorVector,  false, "NJetsNBJetsemuafterZsel", "histos-mle_TT.root", "PreFit_NJetsNBjets_CSVT");
  
  
  //PlotFitResults(true, "InvMass");

}

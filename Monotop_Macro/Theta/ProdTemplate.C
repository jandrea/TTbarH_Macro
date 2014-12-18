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



void setNjetSel(TH1F * thehisto, int njetsel){
  
  if(njetsel!=0) {
    for(int i=1; i<=njetsel; i++){
      thehisto->SetBinContent(i, 0.0000000001);
      thehisto->SetBinError(i, 0.0000000001);
    }
  }
  
}


void ProdTemplate(TString inputdistrib, std::vector<TString> sampleList, std::vector<TString> stytList, TString intputfilename, TString outputfilename){
  
  TFile * inputfile	  = new TFile( intputfilename.Data() );

  TH1F * distrib__DATA  	   = (TH1F*)inputfile->Get( (inputdistrib+"__DataMu").Data() )->Clone();
 
  
  std::vector<TH1F* > distrib_MC;
  std::vector<TH1F* > distrib_MC_sys;
  
  
  
  
  for(unsigned int i=0; i<sampleList.size(); i++){ 
    cout << inputdistrib+"__"+sampleList[i]  << endl;
    distrib_MC.push_back( (TH1F*)inputfile->Get( (inputdistrib+"__"+sampleList[i]).Data() )->Clone() ); 
  } 
  
  
  for(unsigned int i=0; i<sampleList.size(); i++){
    for(unsigned int j=0; j<stytList.size(); j++){
      if(stytList[j] == "scale"    && sampleList[i] !="TT") continue; 
      if(stytList[j] == "matching" && sampleList[i] !="TT") continue; 
      cout << "  " << (inputdistrib+"__"+sampleList[i]+"__"+stytList[j]) << endl;
      distrib_MC_sys.push_back( (TH1F*)inputfile->Get( (inputdistrib+"__"+sampleList[i]+"__"+stytList[j]+"__plus").Data() )->Clone() );  
      distrib_MC_sys.push_back( (TH1F*)inputfile->Get( (inputdistrib+"__"+sampleList[i]+"__"+stytList[j]+"__minus").Data() )->Clone() );  
    }
  }  
  
  cout << __LINE__ << endl;
   
  for(unsigned int i=0; i<stytList.size(); i++) outputfilename+="_"+stytList[i];
  outputfilename+=".root"; 
  
  
  TFile * outputfile = new TFile(  outputfilename.Data() "recreate" );
  outputfile->cd();

  distrib__DATA->Write((inputdistrib+"__DATA").Data());   
  
  for(unsigned int i=0; i<distrib_MC.size(); i++)               {  distrib_MC[i]->Write();}
  for(unsigned int i=0; i<distrib_MC_sys.size(); i++)           {  distrib_MC_sys[i]->Write();}
  
  
}


void ProdTemplate(){
  
  std::vector<TString> sampleList;
  sampleList.push_back("TT");          
  sampleList.push_back("TTljets");    
  sampleList.push_back("Zjets");       
  sampleList.push_back("barsChan");   
  sampleList.push_back("sChan");      
  sampleList.push_back("tChan");      
  sampleList.push_back("bartChan");   
  sampleList.push_back("tW");         
  sampleList.push_back("bartW");      
  sampleList.push_back("TTZ");         
  sampleList.push_back("TTW");         
  sampleList.push_back("WZ");          
  sampleList.push_back("ZZ");          
  sampleList.push_back("WW");          
  sampleList.push_back("tZq"); 
  
       
  std::vector<TString> systlist;
  
  systlist.push_back("lept");   
  //systlist.push_back("trig__plus");
  //systlist.push_back("trig__minus" );  
  //systlist.push_back("PDF__plus");     
  //systlist.push_back("PDF__minus");    
  //systlist.push_back("PU");     
  systlist.push_back("jes");    
  systlist.push_back("jer");  
  //systlist.push_back("metuncls");
  systlist.push_back("scale");  
  systlist.push_back("matching");  
  systlist.push_back("toppt"); 
  
  
  //systlist.push_back("PU"); 
  
  
  systlist.push_back("btagJES");
  systlist.push_back("btagCSVLF");
  systlist.push_back("btagCSVHFStats1");
  systlist.push_back("btagCSVHFStats2");
  systlist.push_back("btagCSVCErr1");
  systlist.push_back("btagCSVCErr2");
  systlist.push_back("btagCSVHF");
  systlist.push_back("btagCSVLFStats1");
  systlist.push_back("btagCSVLFStats2");
  
  //NJetsNBJets_emu_afterZsel__DataMuEG
  
  ProdTemplate("MWT_Signal", sampleList,  systlist,  "../TreeReader/outputroot/histofile_merged.root", "MWT_Signal");
  ProdTemplate("MWT_WJet",   sampleList,  systlist,  "../TreeReader/outputroot/histofile_merged.root", "MWT_WJet");
  ProdTemplate("MWT_TTBar",  sampleList,  systlist,  "../TreeReader/outputroot/histofile_merged.root", "MWT_TTBar");
  
}

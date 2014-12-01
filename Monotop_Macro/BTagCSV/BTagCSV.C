#define BTagCSV_cxx
#include "BTagCSV.h"

int getPtBin(float);

void BTagCSV::Loop(TString sample)
{      
   if (fChain == 0) return;
   
   const int nPt = 16;
   std::string ptName[nPt] = 
     {
	"pt20t30","pt30t40","pt40t50","pt50t60","pt60t70","pt70t80","pt80t100",
	"pt100t120","pt120t160","pt160t210","pt210t260","pt260t320","pt320t400",
	"pt400t500","pt500t600","pt600t800"	
     };

   float binsx[5] = {0,0.244,0.679,0.898,1.};
   
   TH1D *h_bjet_CSV[nPt];
   for(int ih=0;ih<nPt;ih++)
     {	
	std::string hname = "h_bjet_CSV_"+ptName[ih];
	h_bjet_CSV[ih] = new TH1D(hname.c_str(),hname.c_str(),4,binsx);
	h_bjet_CSV[ih]->Sumw2();
     }   

   TH1D *h_bjet_CSV_sum = new TH1D("h_bjet_CSV_sum","h_bjet_CSV_sum",4,binsx);
   h_bjet_CSV_sum->Sumw2();
   
   Long64_t nentries = fChain->GetEntriesFast();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;

	for(int ij=0;ij<treeCSV_jetN;ij++)
	  {
	     if( treeCSV_jetPt[ij] < 20. ) continue;
	     if( fabs(treeCSV_jetEta[ij]) > 2.4 ) continue;
	     
	     int idx = getPtBin(treeCSV_jetPt[ij]);
	     
	     int flav = abs(treeCSV_jetFlav[ij]);
	     bool isBJet = (flav == 5);
	     bool isCJet = (flav == 4);
	     bool isLJet = (flav == 1 || flav == 21);

	     if( isBJet ) 
	       {
		  h_bjet_CSV[idx]->Fill(treeCSV_jetCSV[ij],treeCSV_EvtWeight);
		  h_bjet_CSV_sum->Fill(treeCSV_jetCSV[ij],treeCSV_EvtWeight);
	       } 	     
	  }	
     }
}

int getPtBin(float jetPt)
{
   int idx = -1;
   
   if( jetPt > 20. && jetPt <= 30. ) idx = 0;
   else if( jetPt > 30. && jetPt <= 40. ) idx = 1;
   else if( jetPt > 40. && jetPt <= 50. ) idx = 2;
   else if( jetPt > 50. && jetPt <= 60. ) idx = 3;
   else if( jetPt > 60. && jetPt <= 70. ) idx = 4;
   else if( jetPt > 70. && jetPt <= 80. ) idx = 5;
   else if( jetPt > 80. && jetPt <= 100. ) idx = 6;
   else if( jetPt > 100. && jetPt <= 120. ) idx = 7;
   else if( jetPt > 120. && jetPt <= 160. ) idx = 8;
   else if( jetPt > 160. && jetPt <= 210. ) idx = 9;
   else if( jetPt > 210. && jetPt <= 260. ) idx = 10;
   else if( jetPt > 260. && jetPt <= 320. ) idx = 11;
   else if( jetPt > 320. && jetPt <= 400. ) idx = 12;
   else if( jetPt > 400. && jetPt <= 500. ) idx = 13;
   else if( jetPt > 500. && jetPt <= 600. ) idx = 14;
   else if( jetPt > 600. ) idx = 15;
   
   return idx;
}

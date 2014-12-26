#define Optimization_cxx
#include "Optimization.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

double Optimization::Loop(double lept_pT, double jet_pT, double theMWT)
{

   double nselEvents = 0;
   if (fChain == 0) return 0;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      
      //default selection
      if(smalltree_lept_pt[0] > 33 && fabs(smalltree_lept_eta[0]) < 2.1 ){
        
	
        int njets=0;
        int nbjets = 0;
        for(int ijet=0; ijet<smalltree_njets; ijet++){
         if(smalltree_jet_pt[ijet] < 30 || fabs(smalltree_jet_eta[ijet]) > 2.4) continue;
	 njets++;
	 if(smalltree_jet_btagdiscri[ijet] > 0.679)  nbjets++;
	 
        }
	
        
	//default selection
	if(njets == 1 && nbjets == 1){
	
	  double mTW = pow( 2*smalltree_lept_pt[0]*smalltree_met_pt*(1-cos(smalltree_lept_phi[0] -  smalltree_met_phi)) ,0.5);
	  
	  /*cout << "smalltree_lept_pt[0] " << smalltree_lept_pt[0] << endl;
	  cout << "smalltree_jet_pt[0]  " << smalltree_jet_pt[0] << endl;
	  cout << "theMWT " <<  mTW<< endl;*/
	  
	  
	  if(smalltree_lept_pt[0] > lept_pT && smalltree_jet_pt[0] > jet_pT && mTW > theMWT){
	    //cout << "pass the sel " << endl;
	    nselEvents += smalltree_evtweight;
	  }
	  
	}
	
	
	
      }
   }
   
   return nselEvents;
   
}

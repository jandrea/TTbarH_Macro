#define TreeReader_cxx
#include "TreeReader.h"

void TreeReader::Loop(TString sample)
{
   TString thesample  = sample;
   TFile * theoutputfile = new TFile( ("outputroot/histofile_"+thesample+".root").Data() , "recreate");
   
   
   doTopReco = true;
   
   
    
    
    
   for(unsigned int i=0; i< systlist.size(); i++){
     TString samplename = "";
     if( systlist[i]== "") samplename = thesample;
     else                  samplename = thesample+"__"+systlist[i];
     
     bool firstinit = false;
     if(i==0) firstinit = true;
     //cout << " iiii " << i << endl;
     //cout << samplename << endl;
     initializeHisto(samplename, firstinit);
    }

   isData = (sample== "DataEGZenriched" || sample== "DataMuEGZenriched" || sample== "DataMuZenriched" ||
	     sample== "DataEG" || sample== "DataMuEG" || sample== "DataMu");
   SetUpCSVreweighting();
   
   
   std::vector<int> config ;
   int nMassPts   = 500;
   int rangeLow   = 100; 
   int rangeHigh  = rangeLow+nMassPts;
   int nbrJetSmear= 100;
   int verbosity  = 3;

   config.push_back(nMassPts);
   config.push_back(rangeLow);
   config.push_back(rangeHigh);
   config.push_back(nbrJetSmear);
   config.push_back(verbosity);
   
   
   //if(doTopReco) amwt = new AMWT( config, isData);
    
   cout << "starting loops on events " << endl;
   
   
   //-------------------------------
   //determine the btag scale factor
   //-------------------------------
   //fBTagSF = new BTagSFUtil("CSVL","ABCD");//ReReco
   fBTagSF = new BTagSFUtil("CSVM","ABCD");//ReReco
   //fBTagSF = new BTagSFUtil("CSVT","ABCD");//ReReco
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(jentry%10000 == 0) cout << " processing " << sample << " event number " << jentry << endl;
      
      TString thechannel = determineChannel(smalltree_lept_flav[0], smalltree_lept_flav[1]);
      
      
      //----------------------------------------------------------------------
      //apply event selection
      //second argument is for the systematics
      //"" means no sysetmatics
      //else, enter the systematic strings that appears in the histograms name
      //systematic names are :  
      //"leptup", "leptdown", "trigup", "trigdown", "PDFup", "PDFdown" 
      //"jesup", "jesdown", "jerup", "jerdown", "metunclsup", "metunclsdown"  
      //----------------------------------------------------------------------
      
      for(unsigned int isyst=0; isyst< systlist.size(); isyst++){
      
        //------------------------------------------------------
	//don't do all systematics for the generator uncertainty
        if(isyst !=0 && 
	 (thesample == "TT__matching__minus" || thesample == "TT__matching__plus" || thesample == "TT__scale__minus" ||thesample == "TT__scale__plus" ) ) continue;
	 
	 if(  sample == "TT"   ||sample == "TT_mass166_5"	 || sample == "TT_mass169_5"  
	   || sample == "TT_mass171_5" || sample == "TT_mass173_5"
	   || sample == "TT_mass175_5" || sample == "TT_matchingdown" 
	   || sample == "TT_matchingup" || sample == "TT_scaledown" 
	   || sample == "TT_scaleup"){
	     //cout << "smalltree_tmeme " << smalltree_tmeme << endl;
	     //check if dilepton 
	     //if(smalltree_tmeme != 11 && smalltree_tmeme !=10110 && smalltree_tmeme !=11001 ) continue;
	   }
	   
	   if(sample == "TTljets" && (smalltree_tmeme == 11 || smalltree_tmeme ==10110 || smalltree_tmeme ==11001) ) continue;
           applyEventSel(thechannel, systlist[isyst], thesample);
      }
      
      
      
   }
   
   
   theoutputfile->Write();
   deleteHisto();
   theoutputfile->Close();
   delete theoutputfile;
   
}



bool TreeReader::applyEventSel(TString thechannel, TString systtype, TString sample){
      
      
      bool applyCSV_reshape = 0;
      
      bool applyCSV = 1;
      
      int btagSys   = 0;
      int mistagSys = 0;
      
      TLorentzVector lept1, lept2;
      
      lept1.SetPtEtaPhiM(smalltree_lept_pt[0], smalltree_lept_eta[0], smalltree_lept_phi[0], 0);
      lept2.SetPtEtaPhiM(smalltree_lept_pt[1], smalltree_lept_eta[1], smalltree_lept_phi[1], 0);
      
      
      double met_pt    = smalltree_met_pt;
      double met_phi   = smalltree_met_phi;
      double evtweight = -1;
      
      TString thesample = sample;
      if(systtype != "") thesample = thesample + "__"+systtype;
      //cout << thesample << thesample << endl;
      //cout << "smalltree_met_pt   " << smalltree_met_pt<< endl;
      int iter_jets          = 0;
      float * jet_pt         = 0;
      float * jet_eta        = 0;
      float * jet_phi        = 0;
      float * jet_btagdiscri = 0;
      int   * jet_flav       = 0;
      
      
      
      double wCSV = 1.;
      wCSV = GetCSVweight(0,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
   
      evtweight      = smalltree_evtweight;
      iter_jets      = smalltree_njets;
      jet_pt	     = smalltree_jet_pt;
      jet_eta	     = smalltree_jet_eta;
      jet_phi	     = smalltree_jet_phi;
      jet_btagdiscri = smalltree_jet_btagdiscri;
      jet_flav       = smalltree_jet_flav;
      //cout << "smalltree_evtweights " << smalltree_evtweight << endl;
     // cout << "evtweight " << evtweight << endl;
      
      if(systtype == "" || 
         systtype == "lept__plus"    ||   systtype == "lept__minus" || 
         systtype == "trig__plus"    ||   systtype == "trig__minus" ||
         systtype == "PDF__plus"     ||   systtype == "PDF__minus"  ||
         systtype == "PU__plus"      ||   systtype == "PU__minus"  ||
	 systtype == "toppt__plus"   ||   systtype == "toppt__minus"  ||
	 systtype == "matching__plus"||   systtype == "matching__minus"  ||
	 systtype == "scale__plus"   ||   systtype == "scale__minus"  
	 
      ){
	iter_jets      = smalltree_njets;
        jet_pt         = smalltree_jet_pt;
        jet_eta        = smalltree_jet_eta;
        jet_phi        = smalltree_jet_phi;
        jet_btagdiscri = smalltree_jet_btagdiscri;
        jet_flav       = smalltree_jet_flav;
	
	evtweight = smalltree_evtweight;
	//cout << "----------------" << endl;
	//if(     systtype == "lept__plus")  cout << "in lept up " << endl;
	//cout << "evtweight "  << evtweight << endl;
	if(     systtype == "lept__plus")    evtweight = smalltree_weight_leptup;
	else if(systtype == "lept__minus")   evtweight = smalltree_weight_leptdown;
	else if(systtype == "trig__plus")    evtweight = smalltree_weight_trigup;
	else if(systtype == "trig__minus")   evtweight = smalltree_weight_trigdown;
	else if(systtype == "PDF__plus")     evtweight = smalltree_weight_PDFup;
	else if(systtype == "PDF__minus")    evtweight = smalltree_weight_PDFdown;
	else if(systtype == "PDF__plus")     evtweight = smalltree_weight_PDFup;
	else if(systtype == "PDF__minus")    evtweight = smalltree_weight_PDFdown;
	else if(systtype == "PU__plus")      evtweight = smalltree_weight_PUup;
	else if(systtype == "PU__minus")     evtweight = smalltree_weight_PUdown;
	else if(systtype == "toppt__plus")   evtweight = smalltree_weight_toppt*smalltree_evtweight;
	
	
	//cout << "evtweight "  << evtweight << endl;
	
        
      
      }else if(systtype == "jes__plus"){
      
	evtweight = smalltree_evtweight;
	met_pt    = smalltree_met_jesup_pt;
	met_phi   = smalltree_met_jesup_phi;
	iter_jets      = smalltree_jesup_njets;
        jet_pt         = smalltree_jet_jesup_pt;
        jet_eta        = smalltree_jet_jesup_eta;
        jet_phi        = smalltree_jet_jesup_phi;
        jet_btagdiscri = smalltree_jet_jesup_btagdiscri;
        jet_flav       = smalltree_jet_jesup_flav;
	
      }else if(systtype == "jes__minus"){
	evtweight = smalltree_evtweight;
	met_pt    = smalltree_met_jesdown_pt;
	met_phi   = smalltree_met_jesdown_phi;
	iter_jets      = smalltree_jesdown_njets;
        jet_pt         = smalltree_jet_jesdown_pt;
        jet_eta        = smalltree_jet_jesdown_eta;
        jet_phi        = smalltree_jet_jesdown_phi;
        jet_btagdiscri = smalltree_jet_jesdown_btagdiscri;
        jet_flav       = smalltree_jet_jesdown_flav;
      }else if(systtype == "jer__plus"){
	evtweight = smalltree_evtweight;
	met_pt    = smalltree_met_jerup_pt;
	met_phi   = smalltree_met_jerup_phi;
	iter_jets      = smalltree_jerup_njets;
        jet_pt         = smalltree_jet_jerup_pt;
        jet_eta        = smalltree_jet_jerup_eta;
        jet_phi        = smalltree_jet_jerup_phi;
        jet_btagdiscri = smalltree_jet_jerup_btagdiscri;
        jet_flav       = smalltree_jet_jerup_flav;
      }else if(systtype == "jer__minus"){
	evtweight = smalltree_evtweight;
	met_pt    = smalltree_met_jerdown_pt;
	met_phi   = smalltree_met_jerdown_phi;
	iter_jets      = smalltree_jerdown_njets;
        jet_pt         = smalltree_jet_jerdown_pt;
        jet_eta        = smalltree_jet_jerdown_eta;
        jet_phi        = smalltree_jet_jerdown_phi;
        jet_btagdiscri = smalltree_jet_jerdown_btagdiscri;
        jet_flav       = smalltree_jet_jerdown_flav;
      }else if(systtype == "metuncls__plus"){
	evtweight = smalltree_evtweight;
	met_pt    = smalltree_met_unclsup_pt;
	met_phi   = smalltree_met_unclsup_phi;
      }else if(systtype == "metuncls__minus"){
	evtweight = smalltree_evtweight;
	met_pt    = smalltree_met_unclsdown_pt;
	met_phi   = smalltree_met_unclsdown_phi;
      }else if(systtype == "btagJES__plus"){
	wCSV = GetCSVweight(1,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagJES__minus"){
	wCSV = GetCSVweight(2,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVLF__plus"){
	wCSV = GetCSVweight(3,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVLF__minus"){
	wCSV = GetCSVweight(4,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVHFStats1__plus"){
	wCSV = GetCSVweight(5,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVHFStats1__minus"){
	wCSV = GetCSVweight(6,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVHFStats2__plus"){
	wCSV = GetCSVweight(7,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVHFStats2__minus"){
	wCSV = GetCSVweight(8,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVCErr1__plus"){
	wCSV = GetCSVweight(9,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVCErr1__minus"){
	wCSV = GetCSVweight(10,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVCErr2__plus"){
	wCSV = GetCSVweight(11,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVCErr2__minus"){
	wCSV = GetCSVweight(12,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVHF__plus"){
	wCSV = GetCSVweight(13,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVHF__minus"){
	wCSV = GetCSVweight(14,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVLFStats1__plus"){
	wCSV = GetCSVweight(15,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVLFStats1__minus"){
	wCSV = GetCSVweight(16,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVLFStats2__plus"){
	wCSV = GetCSVweight(17,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btagCSVLFStats2__minus"){
	wCSV = GetCSVweight(18,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__plus" ) { btagSys =  1;}
      else  if(systtype == "btag__minus") { btagSys = -1;}
      else  if(systtype == "mistag__plus" ) { btagSys =  1;}
      else  if(systtype == "mistag__minus") { btagSys = -1;}
      else{
        cout << "WARNING syst type not recognized !! " << endl;
	cout << "correct syst types are " << endl;
	cout << " \"\",  \"lept__plus\", \"lept__minus\", \"trig__plus\", \"trig__minus\", \"PDF__plus\", \"PDF__minus\"  " << endl;
	cout << "\"jes__plus\", \"jes__minus\", \"jer__plus\", \"jer__minus\", \"metuncls__plus\", \"metuncls__minus\" " << endl;      
      }
      
      if( applyCSV_reshape &&  !applyCSV && thesample != "DataMuEG" && thesample != "DataMu" && thesample != "DataEG" && !isData) evtweight *= wCSV;
 
      //determine the btag systematic
      
      if(systtype == "btag__plus"   ){
          btagSys   =  1;
          evtweight = smalltree_evtweight;
      }
      if(systtype == "btag__minus"  ){
        btagSys   = -1;
	evtweight = smalltree_evtweight;
      }
      if(systtype == "mistag__plus" ){
        mistagSys =  1;
	evtweight = smalltree_evtweight;
      }
      if(systtype == "mistag__minus"){
       mistagSys = -1;
       evtweight = smalltree_evtweight;
      }
      
       if(  sample == "TT"   ||sample == "TT_mass166_5"     || sample == "TT_mass169_5"  
	   || sample == "TT_mass171_5" || sample == "TT_mass173_5"
	   || sample == "TT_mass175_5" 
	   || sample == "TT__matching__minus" || sample == "TT__matching__plus"
	   || sample == "TT__scale__minus" || sample == "TT__scale__plus"){
	     
	     if(smalltree_tmeme == 11 || smalltree_tmeme ==10110 || smalltree_tmeme ==11001 ){
	      evtweight *= pow(10.86/11.11,2);
	     }
	     
	   }
      
      //scale for trigger efficiency
      if(sample != "DataMuEG" && sample != "DataMu" && sample != "DataEG"){
        evtweight *= 0.970;
        //cout << "the trigger weight" << endl;
      }
      
      TLorentzVector Zcand = lept1+lept2;
      
      //reconstruction of the Z invarian mass
      double InvMass_ll = Zcand.M();
    
     
     
     int njets=0;
     int nbjets = 0;
     std::vector<int > btagged_jet_idx;
     for(int ijet=0; ijet<iter_jets; ijet++){
       if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
       njets++;
       fillHisto(thechannel, "JetPt",     "afterleptsel",  thesample,  jet_pt[ijet] , evtweight);
       fillHisto(thechannel, "JetEta",    "afterleptsel",  thesample,  jet_eta[ijet] , evtweight);
       //if(applyCSV_reshape && !applyCSV && jet_btagdiscri[ijet] > 0.244)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
       if(applyCSV_reshape && !applyCSV && jet_btagdiscri[ijet] > 0.679)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
       //if(applyCSV_reshape && !applyCSV && jet_btagdiscri[ijet] > 0.898)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
       
       if(applyCSV){
         bool isbtag = 0;
         if(isData) isbtag = fBTagSF->IsTagged( jet_btagdiscri[ijet], -999999        , jet_pt[ijet] , jet_eta[ijet], btagSys); // for nominal sample
         else{
           if(abs(jet_flav[ijet]) ==5||abs(jet_flav[ijet])==4){
             isbtag = fBTagSF->IsTagged( jet_btagdiscri[ijet], jet_flav[ijet] , jet_pt[ijet] , jet_eta[ijet], btagSys); 
	   }else{
             isbtag = fBTagSF->IsTagged( jet_btagdiscri[ijet], jet_flav[ijet] , jet_pt[ijet] , jet_eta[ijet], mistagSys); 
	   }
	    fillHisto(thechannel, "BTAgProba", "afterleptsel",  thesample, isbtag , evtweight);
         }
         if(applyCSV && isbtag)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
       }
       
     }
     
     
     fillHisto(thechannel, "NJet",       "afterleptsel",  thesample,  iter_jets , evtweight);
     fillHisto(thechannel, "NBJet",      "afterleptsel",  thesample,   nbjets, evtweight);
     
     
     
     fillHisto(thechannel, "LeptPt",     "afterleptsel",  thesample,   lept1.Pt(),  evtweight);
     fillHisto(thechannel, "LeptEta",    "afterleptsel",  thesample,   lept1.Eta(), evtweight);
     fillHisto(thechannel, "LeptPt",     "afterleptsel",  thesample,   lept2.Pt(),  evtweight);
     fillHisto(thechannel, "LeptEta",    "afterleptsel",  thesample,   lept2.Eta(), evtweight);
     
     
     fillHisto(thechannel, "CutFlow", "",  thesample, 0, evtweight);
      
      
      //---------------------------------
      //apply dilepton invariant mass cut
       //if( 
         //fabs(InvMass_ll-91) < 15 && )
	 
       if(thechannel == "emu" && InvMass_ll > 20  ) 
	 
       {
         
	 if(fabs( smalltree_lept_eta[0]) > 2.1 && abs(smalltree_lept_flav[0]) == 13 ) return true;
	 if(fabs( smalltree_lept_eta[1]) > 2.1 && abs(smalltree_lept_flav[1]) == 13 ) return true;
	 
	 double delptaphill = fabs(lept1.DeltaPhi(lept2));
	 
         if(njets ==0 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 0, evtweight);
         if(njets ==1 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 1, evtweight);
         if(njets ==1 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 2, evtweight);
         if(njets ==2 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 3, evtweight);
         if(njets ==2 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 4, evtweight);
         if(njets ==2 && nbjets ==2 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 5, evtweight);
         if(njets ==3 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 6, evtweight);
         if(njets ==3 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 7, evtweight);
         if(njets ==3 && nbjets ==2 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 8, evtweight);
         if(njets ==3 && nbjets ==3 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 9, evtweight);
         if(njets >=4 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 10, evtweight);
         if(njets >=4 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 11, evtweight);
         if(njets >=4 && nbjets ==2 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 12, evtweight);
         if(njets >=4 && nbjets ==3 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 13, evtweight);
         if(njets >=4 && nbjets >=4 ) fillHisto(thechannel, "NJetsNBJets", "afterZsel",  thesample, 14, evtweight);
	 
         if(njets ==0 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 0, evtweight);
         if(njets ==1 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 1, evtweight);
         if(njets ==1 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 2, evtweight);
         if(njets ==2 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 3, evtweight);
         if(njets ==2 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 4, evtweight);
         if(njets ==2 && nbjets ==2 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 5, evtweight);
         if(njets >=3 && nbjets ==0 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 6, evtweight);
         if(njets >=3 && nbjets ==1 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 7, evtweight);
         if(njets >=3 && nbjets ==2 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 8, evtweight);
         if(njets >=3 && nbjets >=3 ) fillHisto(thechannel, "NJetsNBJetsSup3Jet", "afterZsel",  thesample, 9, evtweight);
	 
         for(int ijet=0; ijet<iter_jets; ijet++){
           if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
           fillHisto(thechannel, "JetPt",     "afterZsel",  thesample,  jet_pt[ijet] , evtweight);
           fillHisto(thechannel, "JetEta",    "afterZsel",  thesample,  jet_eta[ijet] , evtweight);
         }
     
     
         fillHisto(thechannel, "NJet",       "afterZsel",  thesample,  iter_jets , evtweight);
         fillHisto(thechannel, "NBJet",      "afterZsel",  thesample,   nbjets, evtweight);
     
     
         fillHisto(thechannel, "InvM_ll",    "afterZsel",  thesample,   InvMass_ll,   evtweight);
         fillHisto(thechannel, "LeptPt",     "afterZsel",  thesample,   lept1.Pt(),  evtweight);
         fillHisto(thechannel, "LeptEta",    "afterZsel",  thesample,   lept1.Eta(), evtweight);
         fillHisto(thechannel, "LeptPt",     "afterZsel",  thesample,   lept2.Pt(),  evtweight);
         fillHisto(thechannel, "LeptEta",    "afterZsel",  thesample,   lept2.Eta(), evtweight);
         fillHisto(thechannel, "MET",        "afterZsel",  thesample,  met_pt , evtweight);
	 
     
     
  
         fillHisto(thechannel, "CutFlow", "",  thesample, 1, evtweight);
	
	
	 //------------------------
	 //ask for at least two jet
	 if(njets>=2){

	    
           for(int ijet=0; ijet<iter_jets; ijet++){
             if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
             fillHisto(thechannel, "JetPt",     "afterjetsel",  thesample,  jet_pt[ijet] , evtweight);
             fillHisto(thechannel, "JetEta",    "afterjetsel",  thesample,  jet_eta[ijet] , evtweight);
           }
     
            fillHisto(thechannel, "JetPt1",     "afterjetsel",  thesample,  jet_pt[0] , evtweight);
            fillHisto(thechannel, "JetEta1",    "afterjetsel",  thesample,  jet_eta[0] , evtweight);
	    
            fillHisto(thechannel, "JetPt2",     "afterjetsel",  thesample,  jet_pt[1] , evtweight);
            fillHisto(thechannel, "JetEta2",    "afterjetsel",  thesample,  jet_eta[1] , evtweight);
     
           fillHisto(thechannel, "NJet",       "afterjetsel",  thesample,  iter_jets , evtweight);
           fillHisto(thechannel, "NBJet",      "afterjetsel",  thesample,   nbjets, evtweight);
     
     
           fillHisto(thechannel, "InvM_ll",    "afterjetsel",  thesample,   InvMass_ll,   evtweight);
           fillHisto(thechannel, "LeptPt",     "afterjetsel",  thesample,   lept1.Pt(),  evtweight);
           fillHisto(thechannel, "LeptEta",    "afterjetsel",  thesample,   lept1.Eta(), evtweight);
           fillHisto(thechannel, "LeptPt",     "afterjetsel",  thesample,   lept2.Pt(),  evtweight);
           fillHisto(thechannel, "LeptEta",    "afterjetsel",  thesample,   lept2.Eta(), evtweight);
     
           fillHisto(thechannel, "DeltaPhiLL",    "afterjetsel",  thesample,   delptaphill, evtweight);
           fillHisto(thechannel, "DeltaPhiLLATLAS",    "afterjetsel",  thesample,   delptaphill/3.1416, evtweight);
           fillHisto(thechannel, "MET",    "afterjetsel",  thesample,  met_pt , evtweight);
	  
           fillHisto(thechannel, "CutFlow", "",  thesample, 2, evtweight);
	   
	   
	   //------------------------
	   //ask for at least one b-tagged jet
	   if(nbjets>=1){
	   
	   
	    
             for(int ijet=0; ijet<iter_jets; ijet++){
               if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
               fillHisto(thechannel, "JetPt",     "afterbjetsel",  thesample,  jet_pt[ijet] , evtweight);
               fillHisto(thechannel, "JetEta",    "afterbjetsel",  thesample,  jet_eta[ijet] , evtweight);
             }
     
     
             fillHisto(thechannel, "NJet",       "afterbjetsel",  thesample,  iter_jets , evtweight);
             fillHisto(thechannel, "NBJet",      "afterbjetsel",  thesample,   nbjets, evtweight);
     
     
             fillHisto(thechannel, "InvM_ll",    "afterbjetsel",  thesample,   InvMass_ll,   evtweight);
             fillHisto(thechannel, "LeptPt",     "afterbjetsel",  thesample,   lept1.Pt(),  evtweight);
             fillHisto(thechannel, "LeptEta",    "afterbjetsel",  thesample,   lept1.Eta(), evtweight);
             fillHisto(thechannel, "LeptPt",     "afterbjetsel",  thesample,   lept2.Pt(),  evtweight);
             fillHisto(thechannel, "LeptEta",    "afterbjetsel",  thesample,   lept2.Eta(), evtweight);
             fillHisto(thechannel, "DeltaPhiLL",    "afterbjetsel",  thesample,   delptaphill, evtweight);
             fillHisto(thechannel, "DeltaPhiLLATLAS",    "afterbjetsel",  thesample,   delptaphill/3.1416, evtweight);
               fillHisto(thechannel, "MET",    "afterbjetsel",  thesample,  met_pt , evtweight);
     
	  
             fillHisto(thechannel, "CutFlow", "",  thesample, 3, evtweight);
	   
	   
	     //------------------------
	     //ask for at least two b-tagged jet
	     if(nbjets>=2){
	   
               for(int ijet=0; ijet<iter_jets; ijet++){
                 if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
                 fillHisto(thechannel, "JetPt",     "after2bjetsel",  thesample,  jet_pt[ijet] , evtweight);
                 fillHisto(thechannel, "JetEta",    "after2bjetsel",  thesample,  jet_eta[ijet] , evtweight);
               }
     
     
               fillHisto(thechannel, "NJet",       "after2bjetsel",  thesample,  iter_jets , evtweight);
               fillHisto(thechannel, "NBJet",      "after2bjetsel",  thesample,   nbjets, evtweight);
     
     
               fillHisto(thechannel, "InvM_ll",    "after2bjetsel",  thesample,   InvMass_ll,   evtweight);
               fillHisto(thechannel, "LeptPt",     "after2bjetsel",  thesample,   lept1.Pt(),  evtweight);
               fillHisto(thechannel, "LeptEta",    "after2bjetsel",  thesample,   lept1.Eta(), evtweight);
               fillHisto(thechannel, "LeptPt",     "after2bjetsel",  thesample,   lept2.Pt(),  evtweight);
               fillHisto(thechannel, "LeptEta",    "after2bjetsel",  thesample,   lept2.Eta(), evtweight);
               fillHisto(thechannel, "DeltaPhiLL",    "after2bjetsel",  thesample,   delptaphill, evtweight);
               fillHisto(thechannel, "DeltaPhiLLATLAS",    "after2bjetsel",  thesample,   delptaphill/3.1416, evtweight);
	       
               fillHisto(thechannel, "MET",    "after2bjetsel",  thesample,  met_pt , evtweight);
     
	  
               fillHisto(thechannel, "CutFlow", "",  thesample, 4, evtweight);
	   
	  
	   
	   
	   }//end 2 bjet jet selection
	 }//end 1 bjet jet selection
	}//end jet selection
      }//end dilepton M cut
      
}




//------------------------------------------------------
//initialize the historams for the analysis
//------------------------------------------------------


void TreeReader::initializeHisto(TString sample, bool isfirstset){
  
  
  cout << "#####################################" << endl;
  cout << "#####################################" << endl;
  cout << " initialize histograms               " << endl;
  cout << "#####################################" << endl;
  cout << "#####################################" << endl;
  
  
  if(isfirstset){
    numb_histo = 0;
    TH1F * first_emptyHisto = new TH1F("first_emptyHisto", "first_emptyHisto", 100, 0, 1000);
    histo_list_mm.push_back(first_emptyHisto);
    histo_list_em.push_back(first_emptyHisto);
    histo_list_ee.push_back(first_emptyHisto);
  
    numb_histo++;
  }
  cout << numb_histo << endl;
  addHisto("CutFlow", "", sample.Data(),  15,-0.5,14.5);
  addHisto("NVtx",    "", sample.Data(),  60, 0, 60); 
  
  
  
  //after lepton selection
  addHisto("NJet",      "afterleptsel",  sample.Data(),  5,-0.5,4.5);
  addHisto("NBJet",     "afterleptsel",  sample.Data(),   5,-0.5,4.5);
  addHisto("InvM_ll",   "afterleptsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "afterleptsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "afterleptsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "afterleptsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "afterleptsel",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("MET",       "afterleptsel",  sample.Data(),   100,0,300) ;
  
  addHisto("BTAgProba",               "afterleptsel",  sample.Data(),  2,-0.5,1.5);
  
  //after Z selection selection
  addHisto("NJet",      "afterZsel",  sample.Data(),  5,-0.5,4.5);
  addHisto("NBJet",     "afterZsel",  sample.Data(),   5,-0.5,4.5);
  addHisto("InvM_ll",   "afterZsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "afterZsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "afterZsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "afterZsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "afterZsel",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("MET",       "afterZsel",  sample.Data(),   100,0,300) ;
  
  addHisto("NJetsNBJets",      "afterZsel",  sample.Data(),  15,-0.5,14.5);
  
  addHisto("NJetsNBJetsSup3Jet",      "afterZsel",  sample.Data(),  10,-0.5,9.5);
  
   
  //after jet selection
  addHisto("NJet",      "afterjetsel",  sample.Data(),  5,-0.5,4.5);
  addHisto("NBJet",     "afterjetsel",  sample.Data(),   5,-0.5,4.5);
  addHisto("InvM_ll",   "afterjetsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "afterjetsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "afterjetsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "afterjetsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "afterjetsel",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("DeltaPhiLL",   "afterjetsel",  sample.Data(),   20, 0, 3.14 );
  addHisto("MET",       "afterjetsel",  sample.Data(),   100,0,300) ;
  
  addHisto("JetPt1",     "afterjetsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta1",    "afterjetsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("JetPt2",     "afterjetsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta2",    "afterjetsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("DeltaPhiLLATLAS",   "afterjetsel",  sample.Data(),   28, -0.2, 1.2 );
  
  
  
  //after b-jet selection
  addHisto("NJet",      "afterbjetsel",  sample.Data(),  5,-0.5,4.5);
  addHisto("NBJet",     "afterbjetsel",  sample.Data(),   5,-0.5,4.5);
  addHisto("InvM_ll",   "afterbjetsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "afterbjetsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "afterbjetsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "afterbjetsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "afterbjetsel",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("DeltaPhiLL",   "afterbjetsel",  sample.Data(),   20, 0, 3.14 );
  addHisto("MET",       "afterbjetsel",  sample.Data(),   100,0,300) ;
  addHisto("BJetCSV",    "afterbjetsel",  sample.Data(),  30,0.,1.);
   
  addHisto("DeltaPhiLLATLAS",   "afterbjetsel",  sample.Data(),   28, -0.2, 1.2 );
  
  //after 2 b-jet selection
  
  addHisto("NJet",      "after2bjetsel",  sample.Data(),  5,-0.5,4.5);
  addHisto("NBJet",     "after2bjetsel",  sample.Data(),   5,-0.5,4.5);
  addHisto("InvM_ll",   "after2bjetsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "after2bjetsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "after2bjetsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "after2bjetsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "after2bjetsel",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("DeltaPhiLL",   "after2bjetsel",  sample.Data(),   20, 0, 3.14 );
  addHisto("MET",       "after2bjetsel",  sample.Data(),   100,0,300) ;
  
  addHisto("DeltaPhiLLATLAS",   "after2bjetsel",  sample.Data(),   28, -0.2, 1.2 );
  
  
  
  
  
  
   
  cout << "#####################################" << endl;
  cout << "#####################################" << endl;
  cout << " histograms  initialized             " << endl;
  cout << "#####################################" << endl;
  cout << "#####################################" << endl;
  
    
  //--------------------------------------//
  //   Output TTree 	
  //--------------------------------------//
  TString treename = "Ttree_"+sample;
  cout << treename << endl;
  TTree * TheTree = new TTree(treename.Data(),treename.Data());
  TheTree->Branch("tree_cosThetaStar",     &tree_cosThetaStar,     "tree_cosThetaStar/F"   );
  TheTree->Branch("tree_topMass",     &tree_topMass,     "tree_topMass/F"   );
  TheTree->Branch("tree_totMass",     &tree_totMass,     "tree_totMass/F"   );
  TheTree->Branch("tree_deltaPhilb",  &tree_deltaPhilb,  "tree_deltaPhilb/F");
  TheTree->Branch("tree_deltaRlb",    &tree_deltaRlb,    "tree_deltaRlb/F"  );
  TheTree->Branch("tree_deltaRTopZ",  &tree_deltaRTopZ,  "tree_deltaRTopZ/F");
  TheTree->Branch("tree_asym",        &tree_asym,        "tree_asym/F"      );
  TheTree->Branch("tree_Zpt",         &tree_Zpt,         "tree_Zpt/F"       );
  TheTree->Branch("tree_ZEta",        &tree_ZEta,        "tree_ZEta/F"      );
  TheTree->Branch("tree_topPt",       &tree_topPt,       "tree_topPt/F"     );
  TheTree->Branch("tree_topEta",      &tree_topEta,      "tree_topEta/F"    );
  TheTree->Branch("tree_NJets",       &tree_NJets,       "tree_NJets/F"     );
  TheTree->Branch("tree_NBJets",      &tree_NBJets,      "tree_NBJets/F"    );
  TheTree->Branch("tree_deltaRZl",    &tree_deltaRZl,    "tree_deltaRZl/F"     );
  TheTree->Branch("tree_deltaPhiZmet",&tree_deltaPhiZmet,"tree_deltaPhiZmet/F" );
  TheTree->Branch("tree_btagDiscri",  &tree_btagDiscri,  "tree_btagDiscri/F"   );
  
  TheTree->Branch("tree_totPt",      &tree_totPt,      "tree_totPt/F"   );
  TheTree->Branch("tree_totEta",     &tree_totEta,     "tree_totEta/F"   );
  
  
  TheTree->Branch("tree_leptWPt",        &tree_leptWPt        , "tree_leptWPt/F"        );
  TheTree->Branch("tree_leptWEta",       &tree_leptWEta       , "tree_leptWEta/F"       );
  TheTree->Branch("tree_leadJetPt",      &tree_leadJetPt      , "tree_leadJetPt/F"      ); 
  TheTree->Branch("tree_leadJetEta",     &tree_leadJetEta     , "tree_leadJetEta/F"     );
  TheTree->Branch("tree_deltaRZleptW",   &tree_deltaRZleptW   , "tree_deltaRZleptW/F"   );
  TheTree->Branch("tree_deltaPhiZleptW", &tree_deltaPhiZleptW , "tree_deltaPhiZleptW/F" );
  
  
  TheTree->Branch("tree_met", &tree_met , "tree_met/F" );
  TheTree->Branch("tree_mTW", &tree_mTW , "tree_mTW/F" );
  
  
  TheTree->Branch("tree_EvtWeight",   &tree_EvtWeight,   "tree_EvtWeight/F" );
  TheTree->Branch("tree_SampleType",  &tree_SampleType,  "tree_SampleType/I");
  TheTree->Branch("tree_Channel",     &tree_Channel,     "tree_Channel/I"   );

  theTree_list.push_back(TheTree);
  theTree_map[sample] = theTree_list.back();
  
      
  tree_cosThetaStar   = -10000;
  tree_EvtWeight      = -10000;    
  tree_topMass        = -10000;
  tree_totMass        = -10000; 
  tree_deltaPhilb     = -10000; 
  tree_deltaRlb       = -10000; 
  tree_deltaRTopZ     = -10000; 
  tree_asym	      = -10000; 
  tree_Zpt	      = -10000; 
  tree_ZEta	      = -10000; 
  tree_topPt	      = -10000; 
  tree_topEta	      = -10000; 
  tree_totPt	      = -10000;
  tree_totEta	      = -10000; 
  tree_deltaRZl       = -10000; 
  tree_deltaPhiZmet   = -10000; 
  tree_btagDiscri     = -10000; 
  tree_NJets	      = -10000; 
  tree_NBJets	      = -10000;
  tree_leptWPt        = -10000; 
  tree_leptWEta       = -10000;
  tree_leadJetPt      = -10000; 
  tree_leadJetEta     = -10000; 
  tree_deltaRZleptW   = -10000; 
  tree_deltaPhiZleptW = -10000; 
  tree_met            = -10000;
  tree_mTW            = -10000;
  tree_Channel        = -10000; 
  tree_SampleType     = -10000; 
  

  //--------------------------------------//
  //   Output CSV TTree
  //--------------------------------------//
   
//  TString treenameCSV = "TtreeCSV_"+sample;
//  cout << treenameCSV << endl;
//  TTree * TheTreeCSV = new TTree(treenameCSV.Data(),treenameCSV.Data());
//  TheTreeCSV->Branch("treeCSV_jetN",        &treeCSV_jetN,        "treeCSV_jetN/I"      );
//  TheTreeCSV->Branch("treeCSV_jetPt",       &treeCSV_jetPt,       "treeCSV_jetPt/F"     );
//  TheTreeCSV->Branch("treeCSV_jetEta",      &treeCSV_jetEta,      "treeCSV_jetEta/F"    );
//  TheTreeCSV->Branch("treeCSV_jetCSV",      &treeCSV_jetCSV,      "treeCSV_jetCSV/F"    );
//  TheTreeCSV->Branch("treeCSV_jetFlav",     &treeCSV_jetFlav,     "treeCSV_jetFlav/I"   );
     
//  TheTreeCSV->Branch("treeCSV_EvtWeight",   &treeCSV_EvtWeight,   "treeCSV_EvtWeight/F" );
//  TheTreeCSV->Branch("treeCSV_SampleType",  &treeCSV_SampleType,  "treeCSV_SampleType/I");
//  TheTreeCSV->Branch("treeCSV_Channel",     &treeCSV_Channel,     "treeCSV_Channel/I"   );
  
//  theTreeCSV_list.push_back(TheTreeCSV);
//  theTreeCSV_map[sample] = theTreeCSV_list.back();
   
//  treeCSV_jetN        = -10000;
   
//  for(int i=0;i<1000;i++)
//     {	
//	treeCSV_jetPt[i]              = -10000;
//	treeCSV_jetEta[i]      = -10000;
//	treeCSV_jetCSV[i]      = -10000;
//	treeCSV_jetFlav[i]      = -10000;
//     }
           
//  treeCSV_EvtWeight      = -10000;
//  treeCSV_Channel        = -10000;
//  treeCSV_SampleType     = -10000;
}


//-------------------------------------------------------------
//instantiate and add
//first parameter is the variable name,
// second parameter is the selection step (like "afterleptsel")
//third parameter is the sample name (like "Z)
//others are TH1F binning
//creates one histograms per channel
//-------------------------------------------------------------

void TreeReader::addHisto(TString var, TString selstep, TString sample, int nbins, float min, float max){
  
  
  TString name_mm =  var+"mumu"+selstep+"__"+sample;
  TH1F * thehisto_mm = new TH1F(name_mm,name_mm,nbins,min,max);
  thehisto_mm->Sumw2();
  histo_list_mm.push_back(thehisto_mm);
  histo_map_mm[name_mm.Data()] = numb_histo;
  
  TString name_em =  var+"emu"+selstep+"__"+sample;
  TH1F * thehisto_em = new TH1F(name_em,name_em,nbins,min,max);
  thehisto_em->Sumw2();
  histo_list_em.push_back(thehisto_em);
  histo_map_em[name_em.Data()] = numb_histo;
  
  TString name_ee =  var+"ee"+selstep+"__"+sample;
  TH1F * thehisto_ee = new TH1F(name_ee,name_ee,nbins,min,max);
  thehisto_ee->Sumw2();
  histo_list_ee.push_back(thehisto_ee);
  histo_map_ee[name_ee.Data()] = numb_histo;
  
  //cout << "adding an histo with name " << name_mmm  << " and map integer " << numb_histo << endl;
  //cout << "adding an histo with name " << name_mme  << " and map integer " << numb_histo << endl;
  //cout << "adding an histo with name " << name_eem  << " and map integer " << numb_histo << endl;
  //cout << "adding an histo with name " << name_eee  << " and map integer " << numb_histo << endl;
  
  numb_histo++;
  
  
}

//-------------------------------------------------------------
//fill histograms
//first parameter is the channel,
//second parameter is the variable name,
//third parameter is the selection step (like "afterleptsel")
//forths parameter is the sample name (like "Z)
//others are value and weight
//-------------------------------------------------------------
void TreeReader::fillHisto(TString channel, TString var, TString selstep, TString sample, float val, float weight){
  TString name = var+channel+selstep+"__"+sample;

  
  if(channel == "mumu" && histo_map_mm[name.Data()] == 0) {
    cout << "   WARNING trying to fill a non existing histograms " << endl;
    cout << "   please check the naming conventions " << endl;
    cout << "   histo name "  << name << endl;
  }
  if(channel == "emu" && histo_map_em[name.Data()] == 0) {
    cout << "  WARNING trying to fill a non existing histograms " << endl;
    cout << "  please check the naming conventions " << endl;
    cout << "  histo name "  << name << endl;
  }
  if(channel == "ee" && histo_map_ee[name.Data()] == 0) {
    cout << "  WARNING trying to fill a non existing histograms " << endl;
    cout << "  please check the naming conventions " << endl;
    cout << "  histo name "  << name << endl;
  }
  
  
  /*if(sample == "tZq_leptup") {
    cout << "val " << val << " weight  " << weight << endl; 
    cout << "name " << name << endl;  
    cout << "channel " << channel << endl;
  }*/
  if(channel == "mumu")      histo_list_mm[histo_map_mm[name.Data()]]->Fill(val, weight);
  else if(channel == "emu")  histo_list_em[histo_map_em[name.Data()]]->Fill(val, weight);
  else if(channel == "ee")   histo_list_ee[histo_map_ee[name.Data()]]->Fill(val, weight);  
  
}

//-------------------------------------------------------------
//determine the decay channel
//-------------------------------------------------------------
TString TreeReader::determineChannel(int leptflav1, int leptflav2){
  
  TString thechannel = "";
  
  
  if(abs(smalltree_lept_flav[0]) == 11  && abs(smalltree_lept_flav[1]) == 11) thechannel = "ee";
  if(abs(smalltree_lept_flav[0]) == 13  && abs(smalltree_lept_flav[1]) == 13) thechannel = "mumu";
  if(
    (abs(smalltree_lept_flav[0]) == 11  && abs(smalltree_lept_flav[1]) == 13) ||
    (abs(smalltree_lept_flav[0]) == 13  && abs(smalltree_lept_flav[1]) == 11) ) thechannel = "emu";
  
  
  
  
  if(thechannel == "") cout << "WARNING no channel found, please check the lepton flavor " << endl;
  return thechannel;
  
  
}

void TreeReader::deleteHisto(){
   /*for(unsigned int i=0; i<histo_list_mmm.size(); i++){
     
     delete  histo_list_mmm[i];
     delete  histo_list_mme[i];
     delete  histo_list_eem[i];
     delete  histo_list_eee[i];
     
     
   }*/
  //delete TheTree;
  
  
}

//SetUp CSV reweighting
void TreeReader::SetUpCSVreweighting(){

  // Do not set it up if we're running on collision data
  if(isData){ return; }
  f_CSVwgt_HF = new TFile ("../BTagCSV/CSVRW/csv_rwt_hf.root");
  f_CSVwgt_LF = new TFile ("../BTagCSV/CSVRW/csv_rwt_lf.root");


  // CSV reweighting
  for( int iSys=0; iSys<9; iSys++ ){
    TString syst_csv_suffix_hf = "final";
    TString syst_csv_suffix_c = "final";
    TString syst_csv_suffix_lf = "final";
    
    switch( iSys ){
    case 0:
      // this is the nominal case
      break;
    case 1:
      // JESUp
      syst_csv_suffix_hf = "final_JESUp"; syst_csv_suffix_lf = "final_JESUp";
      syst_csv_suffix_c  = "final_cErr1Up";
      break;
    case 2:
      // JESDown
      syst_csv_suffix_hf = "final_JESDown"; syst_csv_suffix_lf = "final_JESDown";
      syst_csv_suffix_c  = "final_cErr1Down";
      break;
    case 3:
      // purity up
      syst_csv_suffix_hf = "final_LFUp"; syst_csv_suffix_lf = "final_HFUp";
      syst_csv_suffix_c  = "final_cErr2Up";
      break;
    case 4:
      // purity down
      syst_csv_suffix_hf = "final_LFDown"; syst_csv_suffix_lf = "final_HFDown";
      syst_csv_suffix_c  = "final_cErr2Down";
      break;
    case 5:
      // stats1 up
      syst_csv_suffix_hf = "final_Stats1Up"; syst_csv_suffix_lf = "final_Stats1Up";
      break;
    case 6:
      // stats1 down
      syst_csv_suffix_hf = "final_Stats1Down"; syst_csv_suffix_lf = "final_Stats1Down";
      break;
    case 7:
      // stats2 up
      syst_csv_suffix_hf = "final_Stats2Up"; syst_csv_suffix_lf = "final_Stats2Up";
      break;
    case 8:
      // stats2 down
      syst_csv_suffix_hf = "final_Stats2Down"; syst_csv_suffix_lf = "final_Stats2Down";
      break;
    }

    for( int iPt=0; iPt<6; iPt++ ) h_csv_wgt_hf[iSys][iPt] = (TH1D*)f_CSVwgt_HF->Get( Form("csv_ratio_Pt%i_Eta0_%s",iPt,syst_csv_suffix_hf.Data()) );

    if( iSys<5 ){
      for( int iPt=0; iPt<6; iPt++ ) c_csv_wgt_hf[iSys][iPt] = (TH1D*)f_CSVwgt_HF->Get( Form("c_csv_ratio_Pt%i_Eta0_%s",iPt,syst_csv_suffix_c.Data()) );
    }
    
    for( int iPt=0; iPt<4; iPt++ ){
      for( int iEta=0; iEta<3; iEta++ )h_csv_wgt_lf[iSys][iPt][iEta] = (TH1D*)f_CSVwgt_LF->Get( Form("csv_ratio_Pt%i_Eta%i_%s",iPt,iEta,syst_csv_suffix_lf.Data()) );
    }
  }

}

// Get event weight
double TreeReader::GetCSVweight(const int iSys, int jet_n,
				float *jet_pt,float *jet_eta,float *jet_btagdiscri,int *jet_flav){
  if (isData) return 1.0;

  int iSysHF = 0;
  int iSysC = 0;
  int iSysLF = 0;
   
  // systematic variations
  // 1 HF/LF JESup iSysHF=1 iSysC=0 iSysLF=1
  // 2 HF/LF JESdown iSysHF=2 iSysC=0 iSysLF=2
  // 3 HF CSVLFup iSysHF=3 iSysC=0 iSysLF=0
  // 4 HF CSVLFdown iSysHF=4 iSysC=0 iSysLF=0
  // 5 HF CSVHFStats1up iSysHF=5 iSysC=0 iSysLF=0
  // 6 HF CSVHFStats1down iSysHF=6 iSysC=0 iSysLF=0
  // 7 HF CSVHFStats2up iSysHF=7 iSysC=0 iSysLF=0
  // 8 HF CSVHFStats2down iSysHF=8 iSysC=0 iSysLF=0
  // 9 C CSVCErr1up iSysHF=0 iSysC=1 iSysLF=0
  // 10 C CSVCErr1down iSysHF=0 iSysC=2 iSysLF=0
  // 11 C CSVCErr2up iSysHF=0 iSysC=3 iSysLF=0
  // 12 C CSVCErr2down iSysHF=0 iSysC=4 iSysLF=0
  // 13 LF CSVHFup iSysHF=0 iSysC=0 iSysLF=3
  // 14 LF CSVHFdown iSysHF=0 iSysC=0 iSysLF=4
  // 15 LF CSVLFStats1up iSysHF=0 iSysC=0 iSysLF=5
  // 16 LF CSVLFStats1down iSysHF=0 iSysC=0 iSysLF=6
  // 17 LF CSVLFStats2up iSysHF=0 iSysC=0 iSysLF=7
  // 18 LF CSVLFStats2down iSysHF=0 iSysC=0 iSysLF=8
  if( iSys == 1 ) {iSysHF=1; iSysC=0; iSysLF=1;}
  else if( iSys == 2 ) {iSysHF=2; iSysC=0; iSysLF=2;}
  else if( iSys == 3 ) {iSysHF=3; iSysC=0; iSysLF=0;}
  else if( iSys == 4 ) {iSysHF=4; iSysC=0; iSysLF=0;}
  else if( iSys == 5 ) {iSysHF=5; iSysC=0; iSysLF=0;}
  else if( iSys == 6 ) {iSysHF=6; iSysC=0; iSysLF=0;}
  else if( iSys == 7 ) {iSysHF=7; iSysC=0; iSysLF=0;}
  else if( iSys == 8 ) {iSysHF=8; iSysC=0; iSysLF=0;}
  else if( iSys == 9 ) {iSysHF=0; iSysC=1; iSysLF=0;}
  else if( iSys == 10 ) {iSysHF=0; iSysC=2; iSysLF=0;}
  else if( iSys == 11 ) {iSysHF=0; iSysC=3; iSysLF=0;}
  else if( iSys == 12 ) {iSysHF=0; iSysC=4; iSysLF=0;}
  else if( iSys == 13 ) {iSysHF=0; iSysC=0; iSysLF=3;}
  else if( iSys == 14 ) {iSysHF=0; iSysC=0; iSysLF=4;}
  else if( iSys == 15 ) {iSysHF=0; iSysC=0; iSysLF=5;}
  else if( iSys == 16 ) {iSysHF=0; iSysC=0; iSysLF=6;}
  else if( iSys == 17 ) {iSysHF=0; iSysC=0; iSysLF=7;}
  else if( iSys == 18 ) {iSysHF=0; iSysC=0; iSysLF=8;}

//  iSysHF=1; // JESup
//  iSysHF=2; // JESdown
//  iSysHF=3; // CSVLFup
//  iSysHF=4; // CSVLFdown
//  iSysHF=5; // CSVHFStats1up
//  iSysHF=6; // CSVHFStats1down
//  iSysHF=7; // CSVHFStats2up
//  iSysHF=8; // CSVHFStats2down

//  iSysC=1; // CSVCErr1up
//  iSysC=2; // CSVCErr1down
//  iSysC=3; // CSVCErr2up
//  iSysC=4; // CSVCErr2down

//  iSysLF=1; // JESup
//  iSysLF=2; // JESdown
//  iSysLF=3; // CSVHFup
//  iSysLF=4; // CSVHFdown
//  iSysLF=5; // CSVLFStats1up
//  iSysLF=6; // CSVLFStats1down
//  iSysLF=7; // CSVLFStats2up
//  iSysLF=8; // CSVLFStats2down


  double csvWgthf = 1.;
  double csvWgtC  = 1.;
  double csvWgtlf = 1.;

  for( int ij=0;ij<jet_n;ij++){
     
    double csv = jet_btagdiscri[ij];
    double jetPt = jet_pt[ij];
    double jetAbsEta = fabs( jet_eta[ij] );
    int flavor = abs( jet_flav[ij] );

    if( jetPt < 20. || jetAbsEta > 2.5 ) continue;
     
    int iPt = -1; int iEta = -1;
    if (jetPt >=19.99 && jetPt<30) iPt = 0;
    else if (jetPt >=30 && jetPt<40) iPt = 1;
    else if (jetPt >=40 && jetPt<60) iPt = 2;
    else if (jetPt >=60 && jetPt<100) iPt = 3;
    else if (jetPt >=100 && jetPt<160) iPt = 4;
    else if (jetPt >=160 && jetPt<10000) iPt = 5;

    if (jetAbsEta >=0 &&  jetAbsEta<0.8) iEta = 0;
    else if ( jetAbsEta>=0.8 && jetAbsEta<1.6) iEta = 1;
    else if ( jetAbsEta>=1.6 && jetAbsEta<2.41) iEta = 2;
    // kskovpen hack - should change eta cut to 2.4 !
    else if ( jetAbsEta>=2.41 && jetAbsEta<=2.5) iEta = 2;
     
    if (iPt < 0 || iEta < 0) std::cout << "Error, couldn't find Pt, Eta bins for this b-flavor jet, jetPt = " << jetPt << ", jetAbsEta = " << jetAbsEta << std::endl;

    if (abs(flavor) == 5 ){
      int useCSVBin = (csv>=0.) ? h_csv_wgt_hf[iSysHF][iPt]->FindBin(csv) : 1;
      double iCSVWgtHF = h_csv_wgt_hf[iSysHF][iPt]->GetBinContent(useCSVBin);
      if( iCSVWgtHF!=0 ) csvWgthf *= iCSVWgtHF;

    }
    else if( abs(flavor) == 4 ){
      int useCSVBin = (csv>=0.) ? c_csv_wgt_hf[iSysC][iPt]->FindBin(csv) : 1;
      double iCSVWgtC = c_csv_wgt_hf[iSysC][iPt]->GetBinContent(useCSVBin);
      if( iCSVWgtC!=0 ) csvWgtC *= iCSVWgtC;

    }
    else {
      if (iPt >=3) iPt=3;       /// [>60] 
      int useCSVBin = (csv>=0.) ? h_csv_wgt_lf[iSysLF][iPt][iEta]->FindBin(csv) : 1;
      double iCSVWgtLF = h_csv_wgt_lf[iSysLF][iPt][iEta]->GetBinContent(useCSVBin);
      if( iCSVWgtLF!=0 ) csvWgtlf *= iCSVWgtLF;


    }
  }


  double csvWgtTotal = csvWgthf * csvWgtC * csvWgtlf;

  return csvWgtTotal;
}




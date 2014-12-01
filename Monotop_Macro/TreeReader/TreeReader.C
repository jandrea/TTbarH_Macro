#define TreeReader_cxx
#include "TreeReader.h"

void TreeReader::Loop(TString sample)
{
   TString thesample  = sample;
   TFile * theoutputfile = new TFile( ("outputroot/histofile_"+thesample+".root").Data() , "recreate");
   
    
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
   
    
   cout << "starting loops on events " << endl;
   
   
   
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(jentry%10000 == 0) cout << " processing " << sample << " event number " << jentry << endl;
      
      TString thechannel = determineChannel(smalltree_lept_flav[0], smalltree_lept_flav[1], smalltree_lept_flav[2]);
      
      
      //----------------------------------------------------------------------
      //apply event selection
      //second argument is for the systematics
      //"" means no sysetmatics
      //else, enter the systematic strings that appears in the histograms name
      //systematic names are :  
      //"leptup", "leptdown", "trigup", "trigdown", "PDFup", "PDFdown" 
      //"jesup", "jesdown", "jerup", "jerdown", "metunclsup", "metunclsdown"  
      //----------------------------------------------------------------------
      
      for(unsigned int isyst=0; isyst< systlist.size(); isyst++) applyEventSel(thechannel, systlist[isyst], thesample);
      
      
      
      
   }
   
   
   theoutputfile->Write();
   deleteHisto();
   theoutputfile->Close();
   delete theoutputfile;
   
}



bool TreeReader::applyEventSel(TString thechannel, TString systtype, TString sample){
  
      bool applyCSV = 1;
      
      TLorentzVector leptZ1, leptZ2, leptW;
      
      leptZ1.SetPtEtaPhiM(smalltree_lept_pt[0], smalltree_lept_eta[0], smalltree_lept_phi[0], 0);
      leptZ2.SetPtEtaPhiM(smalltree_lept_pt[1], smalltree_lept_eta[1], smalltree_lept_phi[1], 0);
      leptW.SetPtEtaPhiM( smalltree_lept_pt[2], smalltree_lept_eta[2], smalltree_lept_phi[2], 0);
      
      
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
   
      evtweight = smalltree_evtweight;
      iter_jets      = smalltree_njets;
      jet_pt	     = smalltree_jet_pt;
      jet_eta	     = smalltree_jet_eta;
      jet_phi	     = smalltree_jet_phi;
      jet_btagdiscri = smalltree_jet_btagdiscri;
      jet_flav       = smalltree_jet_flav;
      
      
      if(systtype == "" || 
         systtype == "lept__plus" ||   systtype == "lept__minus" || 
         systtype == "trig__plus" ||   systtype == "trig__minus" ||
         systtype == "PDF__plus"  ||   systtype == "PDF__minus"  
	 
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
	//cout << "evtweight "  << evtweight << endl;
	
        if(sample == "WZ" || sample == "WZHF" || sample == "tZq" || sample == "TTZ" || sample == "TTW" || sample == "ZZ"){
          if(thechannel == "mumumu" ) evtweight *= 0.9871;
          if(thechannel == "mumue"  ) evtweight *= 0.9001;
          if(thechannel == "eemu"   ) evtweight *= 0.9451;
          if(thechannel == "eee"    ) evtweight *= 0.9975;
        }
      
      }else if(systtype == "jes__plus"){
      
	met_pt    = smalltree_met_jesup_pt;
	met_phi   = smalltree_met_jesup_phi;
	iter_jets      = smalltree_jesup_njets;
        jet_pt         = smalltree_jet_jesup_pt;
        jet_eta        = smalltree_jet_jesup_eta;
        jet_phi        = smalltree_jet_jesup_phi;
        jet_btagdiscri = smalltree_jet_jesup_btagdiscri;
        jet_flav       = smalltree_jet_jesup_flav;
	
      }else if(systtype == "jes__minus"){
	met_pt    = smalltree_met_jesdown_pt;
	met_phi   = smalltree_met_jesdown_phi;
	iter_jets      = smalltree_jesdown_njets;
        jet_pt         = smalltree_jet_jesdown_pt;
        jet_eta        = smalltree_jet_jesdown_eta;
        jet_phi        = smalltree_jet_jesdown_phi;
        jet_btagdiscri = smalltree_jet_jesdown_btagdiscri;
        jet_flav       = smalltree_jet_jesdown_flav;
      }else if(systtype == "jer__plus"){
	met_pt    = smalltree_met_jerup_pt;
	met_phi   = smalltree_met_jerup_phi;
	iter_jets      = smalltree_jerup_njets;
        jet_pt         = smalltree_jet_jerup_pt;
        jet_eta        = smalltree_jet_jerup_eta;
        jet_phi        = smalltree_jet_jerup_phi;
        jet_btagdiscri = smalltree_jet_jerup_btagdiscri;
        jet_flav       = smalltree_jet_jerup_flav;
      }else if(systtype == "jer__minus"){
	met_pt    = smalltree_met_jerdown_pt;
	met_phi   = smalltree_met_jerdown_phi;
	iter_jets      = smalltree_jerdown_njets;
        jet_pt         = smalltree_jet_jerdown_pt;
        jet_eta        = smalltree_jet_jerdown_eta;
        jet_phi        = smalltree_jet_jerdown_phi;
        jet_btagdiscri = smalltree_jet_jerdown_btagdiscri;
        jet_flav       = smalltree_jet_jerdown_flav;
      }else if(systtype == "metuncls__plus"){
	met_pt    = smalltree_met_unclsup_pt;
	met_phi   = smalltree_met_unclsup_phi;
      }else if(systtype == "metuncls__minus"){
	met_pt    = smalltree_met_unclsdown_pt;
	met_phi   = smalltree_met_unclsdown_phi;
      }else if(systtype == "btag__JESup"){
	wCSV = GetCSVweight(1,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__JESdown"){
	wCSV = GetCSVweight(2,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVLFup"){
	wCSV = GetCSVweight(3,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVLFdown"){
	wCSV = GetCSVweight(4,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVHFStats1up"){
	wCSV = GetCSVweight(5,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVHFStats1down"){
	wCSV = GetCSVweight(6,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVHFStats2up"){
	wCSV = GetCSVweight(7,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVHFStats2down"){
	wCSV = GetCSVweight(8,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVCErr1up"){
	wCSV = GetCSVweight(9,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVCErr1down"){
	wCSV = GetCSVweight(10,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVCErr2up"){
	wCSV = GetCSVweight(11,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVCErr2down"){
	wCSV = GetCSVweight(12,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVHFup"){
	wCSV = GetCSVweight(13,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVHFdown"){
	wCSV = GetCSVweight(14,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVLFStats1up"){
	wCSV = GetCSVweight(15,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVLFStats1down"){
	wCSV = GetCSVweight(16,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVLFStats2up"){
	wCSV = GetCSVweight(17,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else if(systtype == "btag__CSVLFStats2down"){
	wCSV = GetCSVweight(18,smalltree_njets,smalltree_jet_pt,smalltree_jet_eta,smalltree_jet_btagdiscri,smalltree_jet_flav);
      }else{
        cout << "WARNING syst type not recognized !! " << endl;
	cout << "correct syst types are " << endl;
	cout << " \"\",  \"lept__plus\", \"lept__minus\", \"trig__plus\", \"trig__minus\", \"PDF__plus\", \"PDF__minus\"  " << endl;
	cout << "\"jes__plus\", \"jes__minus\", \"jer__plus\", \"jer__minus\", \"metuncls__plus\", \"metuncls__minus\" " << endl;      
      }
      
      if( applyCSV ) evtweight *= wCSV;
     
     
     if(thesample == "NTuple_53X_SingleMuRun2012A" || thesample == "NTuple_53X_SingleMuRun2012B" 
     || thesample == "NTuple_53X_SingleMuRun2012C" || thesample == "NTuple_53X_SingleMuRun2012D" ) evtweight = 1;
     
     
     if(smalltree_lept_pt[0] > 33 && fabs(smalltree_lept_eta[0]) < 2.1 ){
     
       TLorentzVector lept, met, leadingJet;
       lept.SetPtEtaPhiM(smalltree_lept_pt[0], smalltree_lept_eta[0],  smalltree_lept_phi[0], 0.);
       met.SetPtEtaPhiM(met_pt, 0, met_phi , 0.);
       
       if(iter_jets>0) leadingJet.SetPtEtaPhiM(jet_pt[0], jet_eta[0], jet_phi[0], 0);
       
       
       int njets=0;
       int nbjets = 0;
       bool jetsup70 = false;
       std::vector<int > btagged_jet_idx;
       for(int ijet=0; ijet<iter_jets; ijet++){
         if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
         njets++;
         fillHisto(thechannel, "JetPt",     "afterleptsel",  thesample,  jet_pt[ijet] , evtweight);
         fillHisto(thechannel, "JetEta",    "afterleptsel",  thesample,  jet_eta[ijet] , evtweight);
         //if(jet_btagdiscri[ijet] > 0.244)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
         if(jet_btagdiscri[ijet] > 0.679)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
	 
	 if(jet_pt[ijet] > 70 ) jetsup70 = true;
       }
       
       
       
       double mTW = pow(
         		2*smalltree_lept_pt[0]*met_pt*(1-cos(smalltree_lept_phi[0] -  met_phi))
         		,0.5);
       
       double term1 = lept.Pz()*(lept.Px()*met.Px() + lept.Py()*met.Py() + (80.399)*(80.399)/2.);
        double det = lept.Px()*met.Px() + lept.Py()*met.Py() + (80.399)*(80.399)/2.
        		  - met.Pt()*met.Pt()*(lept.E()*lept.E() - lept.Pz()*lept.Pz());
        if(det<0) det=0;
        double term2 = lept.E()*pow(det, 0.5);
        double denom = lept.E()*lept.E() - lept.Pz()*lept.Pz();


        double sol1 = (term1 - term2)/denom;
        //double sol2 = (term1 + term2)/denom;

        double neutrE = pow( pow(met.Px(),2) + pow(met.Py(),2) + sol1*sol1, 0.5);//neglecting neut mass

        TLorentzVector neutrino;
        neutrino.SetPxPyPzE( met.Px(), met.Py(), sol1, neutrE);
        
        TLorentzVector theWcand = neutrino + lept;

       
        fillHisto(thechannel, "NJet",       "afterleptsel",  thesample,  iter_jets , evtweight);
        fillHisto(thechannel, "NBJet",      "afterleptsel",  thesample,   nbjets, evtweight);
     
     
        fillHisto(thechannel, "mWT",        "afterleptsel",  thesample,   mTW,    evtweight);
        fillHisto(thechannel, "mW",         "afterleptsel",  thesample,   theWcand.M(),    evtweight);
        fillHisto(thechannel, "MET",        "afterleptsel",  thesample,   met_pt, evtweight);
        fillHisto(thechannel, "LeptPt",     "afterleptsel",  thesample,   smalltree_lept_pt[0], evtweight);
        fillHisto(thechannel, "LeptEta",    "afterleptsel",  thesample,   smalltree_lept_eta[0], evtweight);
        
        if(fabs(theWcand.M()-80) < 10){
         
	 
          fillHisto(thechannel, "mWT",        "afterMWsel",  thesample,   mTW,    evtweight);
          fillHisto(thechannel, "MET",        "afterMWsel",  thesample,   met_pt, evtweight);
	 
        }
	
        //***********************************
        //W enriched region
        //***********************************
	if(jetsup70 && njets == 1 && nbjets == 0){

          fillHisto(thechannel, "mWT",        "Wenriched_highpt",  thesample,   mTW,    evtweight);
          fillHisto(thechannel, "MET",        "Wenriched_highpt",  thesample,   met_pt, evtweight);
          fillHisto(thechannel, "DeltaPhiLJ", "Wenriched_highpt",  thesample,   lept.DeltaPhi(leadingJet), evtweight);
          fillHisto(thechannel, "DeltaRLJ",   "Wenriched_highpt",  thesample,   lept.DeltaR(leadingJet), evtweight);
          fillHisto(thechannel, "LeptPt",     "Wenriched_highpt",  thesample,   smalltree_lept_pt[0], evtweight);
          fillHisto(thechannel, "LeptEta",    "Wenriched_highpt",  thesample,   smalltree_lept_eta[0], evtweight);
          fillHisto(thechannel, "DeltaPhiLJ", "Wenriched_highpt",  thesample,   lept.DeltaPhi(leadingJet), evtweight);
          fillHisto(thechannel, "DeltaRLJ",   "Wenriched_highpt",  thesample,   lept.DeltaR(leadingJet), evtweight);
 	 
        
	
	}
        //***********************************
        //signal enriched region
        //***********************************
        if(jetsup70 && njets == 1 && nbjets == 1){
        
        
          fillHisto(thechannel, "mWT",        "signalregion",  thesample,   mTW,    evtweight);
          fillHisto(thechannel, "MET",        "signalregion",  thesample,   met_pt, evtweight);
          fillHisto(thechannel, "DeltaPhiLJ", "signalregion",  thesample,   lept.DeltaPhi(leadingJet), evtweight);
          fillHisto(thechannel, "DeltaRLJ",   "signalregion",  thesample,   lept.DeltaR(leadingJet), evtweight);
 	 
        }
        
        //***********************************
        //ttbar enriched region
        //***********************************
        if(jetsup70 && njets >= 4 && nbjets ==2 ){
        
          fillHisto(thechannel, "mWT",        "ttbarregion_highpt",  thesample,   mTW,    evtweight);
          fillHisto(thechannel, "MET",        "ttbarregion_highpt",  thesample,   met_pt, evtweight);
          fillHisto(thechannel, "LeptPt",     "ttbarregion_highpt",  thesample,   smalltree_lept_pt[0], evtweight);
          fillHisto(thechannel, "LeptEta",    "ttbarregion_highpt",  thesample,   smalltree_lept_eta[0], evtweight);
          fillHisto(thechannel, "DeltaPhiLJ", "ttbarregion_highpt",  thesample,   lept.DeltaPhi(leadingJet), evtweight);
          fillHisto(thechannel, "DeltaRLJ",   "ttbarregion_highpt",  thesample,   lept.DeltaR(leadingJet), evtweight);
 	 
        
        }
        
        //***********************************
        //ttbar enriched region lowjetpt
        //***********************************
        if( njets >= 4 && nbjets ==2 ){
        
          fillHisto(thechannel, "mWT",        "ttbarregion_lowjetpt",  thesample,   mTW,    evtweight);
          fillHisto(thechannel, "MET",        "ttbarregion_lowjetpt",  thesample,   met_pt, evtweight);
          fillHisto(thechannel, "LeptPt",     "ttbarregion_lowjetpt",  thesample,   smalltree_lept_pt[0], evtweight);
          fillHisto(thechannel, "LeptEta",    "ttbarregion_lowjetpt",  thesample,   smalltree_lept_eta[0], evtweight);
 	 
  	  for(int ijet=0; ijet<iter_jets; ijet++){
            if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
            fillHisto(thechannel, "JetPt",     "ttbarregion_lowjetpt",  thesample,  jet_pt[ijet] , evtweight);
            fillHisto(thechannel, "JetEta",    "ttbarregion_lowjetpt",  thesample,  jet_eta[ijet] , evtweight);
          }
      
          fillHisto(thechannel, "JetPt1",     "ttbarregion_lowjetpt",  thesample,  jet_pt[0] , evtweight);
          fillHisto(thechannel, "JetEta1",    "ttbarregion_lowjetpt",  thesample,  jet_eta[0] , evtweight);
	  
          fillHisto(thechannel, "JetPt2",     "ttbarregion_lowjetpt",  thesample,  jet_pt[1] , evtweight);
          fillHisto(thechannel, "JetEta2",    "ttbarregion_lowjetpt",  thesample,  jet_eta[1] , evtweight);
	  
          fillHisto(thechannel, "JetPt3",     "ttbarregion_lowjetpt",  thesample,  jet_pt[2] , evtweight);
          fillHisto(thechannel, "JetEta3",    "ttbarregion_lowjetpt",  thesample,  jet_eta[2] , evtweight);
	  
          fillHisto(thechannel, "JetPt4",     "ttbarregion_lowjetpt",  thesample,  jet_pt[3] , evtweight);
          fillHisto(thechannel, "JetEta4",    "ttbarregion_lowjetpt",  thesample,  jet_eta[3] , evtweight);
        
        }

      } //lepton selection
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
    histo_list_mujets.push_back(first_emptyHisto);
  
    numb_histo++;
  }
  cout << numb_histo << endl;
  addHisto("CutFlow", "", sample.Data(),  15,-0.5,14.5);
  addHisto("NVtx",    "", sample.Data(),  60, 0, 60); 
  
  
  
  //after lepton selection
  addHisto("NJet",      "afterleptsel",  sample.Data(),  5,-0.5,4.5);
  addHisto("NBJet",     "afterleptsel",  sample.Data(),   5,-0.5,4.5);
  addHisto("mWT",       "afterleptsel",  sample.Data(),   100,0,200);
  addHisto("mW",        "afterleptsel",  sample.Data(),   100,0,200);
  addHisto("MET",       "afterleptsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "afterleptsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "afterleptsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "afterleptsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "afterleptsel",  sample.Data(),   26, -2.5, 2.5 );
  
  addHisto("mWT",       "afterMWsel",  sample.Data(),   50,0,300);
  addHisto("MET",       "afterMWsel",  sample.Data(),   50,0,300);
  
  addHisto("mWT",       "Wenriched_highpt",  sample.Data(),   50,0,300);
  addHisto("MET",       "Wenriched_highpt",  sample.Data(),   50,0,300);
  addHisto("LeptPt",    "Wenriched_highpt",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "Wenriched_highpt",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("DeltaPhiLJ","Wenriched_highpt",  sample.Data(),   50, 0, 6.28 );
  addHisto("DeltaRLJ",  "Wenriched_highpt",  sample.Data(),   50, 0, 6.28 );
  
  addHisto("mWT",       "signalregion",  sample.Data(),   50,0,300);
  addHisto("MET",       "signalregion",  sample.Data(),   50,0,300);
  addHisto("DeltaPhiLJ","signalregion",  sample.Data(),   50, 0, 6.28 );
  addHisto("DeltaRLJ",  "signalregion",  sample.Data(),   50, 0, 6.28 );
  
  addHisto("mWT",       "ttbarregion_highpt",  sample.Data(),   50,0,300);
  addHisto("MET",       "ttbarregion_highpt",  sample.Data(),   50,0,300);
  addHisto("LeptPt",    "ttbarregion_highpt",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "ttbarregion_highpt",  sample.Data(),   26, -2.5, 2.5 );
  addHisto("DeltaPhiLJ","ttbarregion_highpt",  sample.Data(),   50, 0, 6.28 );
  addHisto("DeltaRLJ",  "ttbarregion_highpt",  sample.Data(),   50, 0, 6.28 );
  
  addHisto("mWT",       "ttbarregion_lowjetpt",  sample.Data(),   30,0,300);
  addHisto("MET",       "ttbarregion_lowjetpt",  sample.Data(),   30,0,300);
  addHisto("JetPt",     "ttbarregion_lowjetpt",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "ttbarregion_lowjetpt",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "ttbarregion_lowjetpt",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "ttbarregion_lowjetpt",  sample.Data(),   26, -2.5, 2.5 );
  
  
  addHisto("JetPt1",     "ttbarregion_lowjetpt",  sample.Data(),   100,0,450) ;
  addHisto("JetEta1",    "ttbarregion_lowjetpt",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("JetPt2",     "ttbarregion_lowjetpt",  sample.Data(),   100,0,450) ;
  addHisto("JetEta2",    "ttbarregion_lowjetpt",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("JetPt3",     "ttbarregion_lowjetpt",  sample.Data(),   100,0,450) ;
  addHisto("JetEta3",    "ttbarregion_lowjetpt",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("JetPt4",     "ttbarregion_lowjetpt",  sample.Data(),   100,0,450) ;
  addHisto("JetEta4",    "ttbarregion_lowjetpt",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  
   
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
  
  
  TString name_mujets =  var+"_mujets_"+selstep+"__"+sample;
  TH1F * thehisto_mujets = new TH1F(name_mujets,name_mujets,nbins,min,max);
  thehisto_mujets->Sumw2();
  histo_list_mujets.push_back(thehisto_mujets);
  histo_map_mujets[name_mujets.Data()] = numb_histo;
  
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
  TString name = var+"_"+channel+"_"+selstep+"__"+sample;

  
  if(channel == "mujets" && histo_map_mujets[name.Data()] == 0) {
    cout << "   WARNING trying to fill a non existing histograms " << endl;
    cout << "   please check the naming conventions " << endl;
    cout << "   histo name "  << name << endl;
  }
   
  
  /*if(sample == "tZq_leptup") {
    cout << "val " << val << " weight  " << weight << endl; 
    cout << "name " << name << endl;  
    cout << "channel " << channel << endl;
  }*/
  if(channel == "mujets")     histo_list_mujets[histo_map_mujets[name.Data()]]->Fill(val, weight);
  
}

//-------------------------------------------------------------
//determine the decay channel
//-------------------------------------------------------------
TString TreeReader::determineChannel(int leptflav1, int leptflav2, int leptflav3){
  
  TString thechannel = "";
  
  thechannel = "mujets";
   
  //cout << "leptflav1 " << leptflav1 << "  leptflav2 " << leptflav2 << "  leptflav3 " << leptflav3 <<  "  the channel " << thechannel << endl;
  if(thechannel == "") cout << "WARNING no channel found, please check the lepton flavor " << endl;
  return thechannel;
  
  
}

void TreeReader::deleteHisto(){
   cout << __LINE__ << endl;
   /*for(unsigned int i=0; i<histo_list_mmm.size(); i++){
     
     delete  histo_list_mmm[i];
     delete  histo_list_mme[i];
     delete  histo_list_eem[i];
     delete  histo_list_eee[i];
     
     
   }*/
   cout << __LINE__ << endl;
  //delete TheTree;
   cout << __LINE__ << endl;
  
  
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




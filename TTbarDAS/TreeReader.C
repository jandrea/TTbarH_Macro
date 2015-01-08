#define TreeReader_cxx
#include "TreeReader.h"

void TreeReader::Loop(TString sample)
{
   TString thesample  = sample;
   TFile * theoutputfile = new TFile( ("Output/histofile_"+thesample+".root").Data() , "recreate");
   
    
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
      }
     
     
     if(thesample == "NTuple_53X_SingleMuRun2012A" || thesample == "NTuple_53X_SingleMuRun2012B" 
     || thesample == "NTuple_53X_SingleMuRun2012C" || thesample == "NTuple_53X_SingleMuRun2012D" ) evtweight = 1;
     
     
     if(smalltree_lept_pt[0] > 33 && fabs(smalltree_lept_eta[0]) < 2.1 ){
     
       TLorentzVector lept, met, leadingJet;
       lept.SetPtEtaPhiM(smalltree_lept_pt[0], smalltree_lept_eta[0],  smalltree_lept_phi[0], 0.);
       met.SetPtEtaPhiM(met_pt, 0, met_phi , 0.);
       
       if(iter_jets>0) leadingJet.SetPtEtaPhiM(jet_pt[0], jet_eta[0], jet_phi[0], 0);
       
       
       int njets=0;
       int nbjets = 0;
       std::vector<int > btagged_jet_idx;
       for(int ijet=0; ijet<iter_jets; ijet++){
         if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
         njets++;
         fillHisto(thechannel, "JetPt",     "afterleptsel",  thesample,  jet_pt[ijet] , evtweight);
         fillHisto(thechannel, "JetEta",    "afterleptsel",  thesample,  jet_eta[ijet] , evtweight);
         //if(jet_btagdiscri[ijet] > 0.244)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
         if(jet_btagdiscri[ijet] > 0.679)  {nbjets++;   btagged_jet_idx.push_back(ijet); }  
	 
       }
       
       
       
       double mTW = pow(
         		2*smalltree_lept_pt[0]*met_pt*(1-cos(smalltree_lept_phi[0] -  met_phi))
         		,0.5);
      
       
        fillHisto(thechannel, "NJet",       "afterleptsel",  thesample,  iter_jets , evtweight);
        fillHisto(thechannel, "NBJet",      "afterleptsel",  thesample,   nbjets, evtweight);
     
     
        fillHisto(thechannel, "mWT",        "afterleptsel",  thesample,   mTW,    evtweight);
        fillHisto(thechannel, "MET",        "afterleptsel",  thesample,   met_pt, evtweight);
        fillHisto(thechannel, "LeptPt",     "afterleptsel",  thesample,   smalltree_lept_pt[0], evtweight);
        fillHisto(thechannel, "LeptEta",    "afterleptsel",  thesample,   smalltree_lept_eta[0], evtweight);
        
       
        //***********************************
        //ttbar enriched region lowjetpt
        //***********************************
        if( njets >= 4 && nbjets ==2 ){
        
          fillHisto(thechannel, "mWT",        "ttbarregion",  thesample,   mTW,    evtweight);
          fillHisto(thechannel, "MET",        "ttbarregion",  thesample,   met_pt, evtweight);
          fillHisto(thechannel, "LeptPt",     "ttbarregion",  thesample,   smalltree_lept_pt[0], evtweight);
          fillHisto(thechannel, "LeptEta",    "ttbarregion",  thesample,   smalltree_lept_eta[0], evtweight);
 	 
  	  for(int ijet=0; ijet<iter_jets; ijet++){
            if(jet_pt[ijet] < 30 || fabs(jet_eta[ijet]) > 2.4) continue;     
            fillHisto(thechannel, "JetPt",     "ttbarregion",  thesample,  jet_pt[ijet] , evtweight);
            fillHisto(thechannel, "JetEta",    "ttbarregion",  thesample,  jet_eta[ijet] , evtweight);
          }
      
          fillHisto(thechannel, "JetPt1",     "ttbarregion",  thesample,  jet_pt[0] , evtweight);
          fillHisto(thechannel, "JetEta1",    "ttbarregion",  thesample,  jet_eta[0] , evtweight);
	  
          fillHisto(thechannel, "JetPt2",     "ttbarregion",  thesample,  jet_pt[1] , evtweight);
          fillHisto(thechannel, "JetEta2",    "ttbarregion",  thesample,  jet_eta[1] , evtweight);
	  
          fillHisto(thechannel, "JetPt3",     "ttbarregion",  thesample,  jet_pt[2] , evtweight);
          fillHisto(thechannel, "JetEta3",    "ttbarregion",  thesample,  jet_eta[2] , evtweight);
	  
          fillHisto(thechannel, "JetPt4",     "ttbarregion",  thesample,  jet_pt[3] , evtweight);
          fillHisto(thechannel, "JetEta4",    "ttbarregion",  thesample,  jet_eta[3] , evtweight);
        
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
  addHisto("MET",       "afterleptsel",  sample.Data(),   100,0,200);
  addHisto("JetPt",     "afterleptsel",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "afterleptsel",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "afterleptsel",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "afterleptsel",  sample.Data(),   26, -2.5, 2.5 );
  
  
  addHisto("mWT",       "ttbarregion",  sample.Data(),   30,0,300);
  addHisto("MET",       "ttbarregion",  sample.Data(),   30,0,300);
  addHisto("JetPt",     "ttbarregion",  sample.Data(),   100,0,300) ;
  addHisto("JetEta",    "ttbarregion",  sample.Data(),   26, -2.5, 2.5 ) ;
  addHisto("LeptPt",    "ttbarregion",  sample.Data(),   100,0.,200);
  addHisto("LeptEta",   "ttbarregion",  sample.Data(),   26, -2.5, 2.5 );
  
  
  addHisto("JetPt1",    "ttbarregion",  sample.Data(),   100,0,450) ;
  addHisto("JetEta1",   "ttbarregion",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("JetPt2",    "ttbarregion",  sample.Data(),   100,0,450) ;
  addHisto("JetEta2",   "ttbarregion",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("JetPt3",    "ttbarregion",  sample.Data(),   100,0,450) ;
  addHisto("JetEta3",   "ttbarregion",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  addHisto("JetPt4",    "ttbarregion",  sample.Data(),   100,0,450) ;
  addHisto("JetEta4",   "ttbarregion",  sample.Data(),   26, -2.5, 2.5 ) ;
  
  
   
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




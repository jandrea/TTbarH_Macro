

{

 gROOT->ProcessLine(".L PlotStack.C+");
 gROOT->SetStyle("Plain");
 gStyle->SetPalette(1);
 gStyle->SetOptStat(0);
 
 //----------------
 //list of channels
 std::vector<TString> channel_list;
 //channel_list.push_back("mumu");
 channel_list.push_back("emu");
 //channel_list.push_back("ee");
 
  
  //---------------------------
  //define list of data samples 
  std::vector<TString> dataSample_list;
  //dataSample_list.push_back("DataMu");
  dataSample_list.push_back("DataMuEG");
  //dataSample_list.push_back("DataEG");
  
  //------------------------------------
  //define list of data-driven templates
  std::vector< TString > dataDrivenTemplates_list; 
  //dataDrivenTemplates_list.push_back( "DataEGZenriched"  );
  //dataDrivenTemplates_list.push_back( "DataMuEGZenriched");
  //dataDrivenTemplates_list.push_back( "DataMuZenriched"  );
  
  
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
  
  
  
 //-----------------------------
 //define list of signal samples 
  std::vector<TString> signalSample_list;
  
  
  
  
 //--------------------------
 //define list of systematics
 std::vector<TString> syst_list;
 /*syst_list.push_back("leptup");
 syst_list.push_back("leptdown");
 //syst_list.push_back("trigup");
 //syst_list.push_back("trigdown");
 //syst_list.push_back("PDFup");
 //syst_list.push_back("PDFdown");
 syst_list.push_back("jesup");
 syst_list.push_back("jesdown");
 syst_list.push_back("jerup");
 syst_list.push_back("jerdown");
 syst_list.push_back("metunclsup");
 syst_list.push_back("metunclsdown");*/
  
  
 
 //--------------------------
 //define list of systematics
 std::vector<TString> selectionStep_list;
 //selectionStep_list.push_back("afterleptsel");
 selectionStep_list.push_back("afterZsel");
 //selectionStep_list.push_back("afterjetsel");
 //selectionStep_list.push_back("afterbjetsel");
 //selectionStep_list.push_back("after2bjetsel");
 
 
 //------------------------
 //define list of variables
 std::vector<TString> variables_list;
 variables_list.push_back("NJetsNBJets");
 //variables_list.push_back("NJetsNBJetsSup3Jet");
 //variables_list.push_back("NJet");
 //variables_list.push_back("NBJet");
 //variables_list.push_back("InvM_ll");
 
 //variables_list.push_back("LeptPt");
 //variables_list.push_back("LeptEta");
 //variables_list.push_back("JetPt");
 //variables_list.push_back("JetEta");
 //variables_list.push_back("MET");
 //variables_list.push_back("DeltaPhiLL");
 //variables_list.push_back("DeltaPhiLLATLAS");
 //variables_list.push_back("JetPt1");
 //variables_list.push_back("JetEta1");
 //variables_list.push_back("JetPt2");
 //variables_list.push_back("JetEta2");
 
 
 

  for(int iselstep=0; iselstep < selectionStep_list.size(); iselstep++){
      //PlotStack("InvM_ll_",channel_list[ichan],"_afterleptsel", i, k);
    for(int ivar=0; ivar < variables_list.size(); ivar++){
        
      for (int ichan=0; ichan<channel_list.size(); ichan++) {
	  //PlotStack(variables_list[ivar],  channel_list[ichan],  selectionStep_list[iselstep] , 0,  1);
	  PlotStack(variables_list[ivar],  channel_list[ichan],  selectionStep_list[iselstep] , 0, dataSample_list,  channel_list, mcSample_list, signalSample_list, colorVector, dataDrivenTemplates_list, false);
      }
      // PlotStack(variables_list[ivar],  "",  selectionStep_list[iselstep] , 0, dataSample_list,  channel_list, mcSample_list, signalSample_list, colorVector, dataDrivenTemplates_list, true);
    }
   } // end loop jchan
   
   
   
   
   
 }

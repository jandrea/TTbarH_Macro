{
  
  gSystem->Load("../BTagSFNotReshaping/BTagSFUtil_C.so");
  gSystem->Load("../MassAMWT/libAMWT.so");
  
  gROOT->ProcessLine(".L TreeReader.C+");
  
  
  std::vector<TString > systlist;
  systlist.push_back("");
  
  /*
  		
  systlist.push_back("lept__plus");
  systlist.push_back("lept__minus" );    
  //systlist.push_back("trig__plus");
  //systlist.push_back("trig__minus" );  
  //systlist.push_back("PDF__plus");     
  //systlist.push_back("PDF__minus");    
  systlist.push_back("jes__plus");
  systlist.push_back("jes__minus");      
  systlist.push_back("jer__plus");
  systlist.push_back("jer__minus");   
  systlist.push_back("metuncls__plus");
  systlist.push_back("metuncls__minus");
  systlist.push_back("btag__plus");
  systlist.push_back("btag__minus");
  systlist.push_back("mistag__plus");
  systlist.push_back("mistag__minus");
  systlist.push_back("PU__plus");
  systlist.push_back("PU__minus");
  systlist.push_back("toppt__plus");
  systlist.push_back("toppt__minus");
  
  //systlist.push_back("scale__plus");
  //systlist.push_back("scale__minus");
  //systlist.push_back("matching__plus");
  //systlist.push_back("matching__minus");
  
  */ 
  /*
  systlist.push_back("btagJES__plus");
  systlist.push_back("btagJES__minus");
  systlist.push_back("btagCSVLF__plus");
  systlist.push_back("btagCSVLF__minus");
  systlist.push_back("btagCSVHFStats1__plus");
  systlist.push_back("btagCSVHFStats1__minus");
  systlist.push_back("btagCSVHFStats2__plus");
  systlist.push_back("btagCSVHFStats2__minus");
  systlist.push_back("btagCSVCErr1__plus");
  systlist.push_back("btagCSVCErr1__minus");
  systlist.push_back("btagCSVCErr2__plus");
  systlist.push_back("btagCSVCErr2__minus");
  systlist.push_back("btagCSVHF__plus");
  systlist.push_back("btagCSVHF__minus");
  systlist.push_back("btagCSVLFStats1__plus");
  systlist.push_back("btagCSVLFStats1__minus");
  systlist.push_back("btagCSVLFStats2__plus");
  systlist.push_back("btagCSVLFStats2__minus");*/
  
  
  
  std::vector<TString > systlist2;
  systlist2.push_back("");
  
   
  std::vector<TString > datalist ;
  datalist.push_back("");
   
  TTree* tree=0;
  
  
  TString sampleList;
  sampleList.push_back();
  
  
  
  TreeReader * tree_DataMuEG = new TreeReader(tree, "DataMuEG", datalist);
  tree_DataMuEG.Loop("DataMuEG");
  delete tree_DataMuEG;

/*
  
  TreeReader * tree_tZq = new TreeReader(tree, "tZq", systlist);
  tree_tZq.Loop("tZq");
  delete tree_tZq;
  
  
  
  TreeReader * tree_TTZ = new TreeReader(tree, "TTZ", systlist);
  tree_TTZ.Loop("TTZ");
  delete tree_TTZ;
  
  
  TreeReader * tree_TTW = new TreeReader(tree, "TTW", systlist);
  tree_TTW.Loop("TTW");
  delete tree_TTW;
  
  
  

  /*TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_central", systlist);
  tree_TT.Loop("TT");
  delete tree_TT;*/
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMCatNLO", systlist);
  tree_TT.Loop("TT");
  delete tree_TT;
  /*
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_central", systlist);
  tree_TT.Loop("TTljets");
  delete tree_TT;
  
   
  
  //******************************************************
  //top mass samples 
  //******************************************************
  
  
  /*
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_mass166_5", datalist);
  tree_TT.Loop("TT_mass166_5");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_mass169_5", datalist);
  tree_TT.Loop("TT_mass169_5");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_mass171_5", datalist);
  tree_TT.Loop("TT_mass171_5");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_mass173_5", datalist);
  tree_TT.Loop("TT_mass173_5");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_mass175_5", datalist);
  tree_TT.Loop("TT_mass175_5");
  delete tree_TT;
  
  */
  
  /*
  
  //******************************************************
  //ttbar syst samples
  //******************************************************
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_matchingdown", systlist2);
  tree_TT.Loop("TT__matching__minus");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_matchingup", systlist2);
  tree_TT.Loop("TT__matching__plus");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_scaledown", systlist2);
  tree_TT.Loop("TT__scale__minus");
  delete tree_TT;
  
  TreeReader * tree_TT = new TreeReader(tree, "TTMSDecays_scaleup", systlist2);
  tree_TT.Loop("TT__scale__plus");
  delete tree_TT;
  
  /*
  
  
  
  TreeReader * tree_DYToLL_M10_50 = new TreeReader(tree, "DYToLL_M10-50", systlist);
  tree_DYToLL_M10_50.Loop("DYToLL_M10-50");
  delete tree_DYToLL_M10_50;
  
  
  
  TreeReader * tree_Zjets = new TreeReader(tree, "Zjets", systlist);
  tree_Zjets.Loop("Zjets");
  delete tree_Zjets;
  
  TreeReader * tree_Wjets = new TreeReader(tree, "Wjets", systlist);
  tree_Wjets.Loop("Wjets");
  delete tree_Wjets;
  
  //one for WZ +light
  TreeReader * tree_WZ = new TreeReader(tree, "WZ", systlist);
  tree_WZ.Loop("WZ");
  delete tree_WZ;
  

  TreeReader * tree_ZZ = new TreeReader(tree, "ZZ", systlist);
  tree_ZZ.Loop("ZZ");
  delete tree_ZZ;
  
  TreeReader * tree_WW = new TreeReader(tree, "WW", systlist);
  tree_WW.Loop("WW");
  delete tree_WW;
  
  
  TreeReader * tree_TbarsChan = new TreeReader(tree, "TbarsChan", systlist);
  tree_TbarsChan.Loop("barsChan");
  delete tree_TbarsChan;

  
  TreeReader * tree_TsChan = new TreeReader(tree, "TsChan", systlist);
  tree_TsChan.Loop("sChan");
  delete tree_TsChan;

  
  TreeReader * tree_TtChan = new TreeReader(tree, "TtChan", systlist);
  tree_TtChan.Loop("tChan");
  delete tree_TtChan;


  TreeReader * tree_TbartChan = new TreeReader(tree, "TbartChan", systlist);
  tree_TbartChan.Loop("bartChan");
  delete tree_TbartChan;

  
  TreeReader * tree_TtW = new TreeReader(tree, "TtW", systlist);
  tree_TtW.Loop("tW");
  delete tree_TtW;

  
  TreeReader * tree_TbartW = new TreeReader(tree, "TbartW", systlist);
  tree_TbartW.Loop("bartW");
  delete tree_TbartW;

  */
  
  
}

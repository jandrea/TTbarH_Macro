{
  gROOT->ProcessLine(".L TreeReader.C+");
  
  
  std::vector<TString > systlist;
  systlist.push_back("");		
  /*systlist.push_back("lept__plus");
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
  
  
  */
  
  
  
  std::vector<TString > datalist;
  datalist.push_back("");	
  
  TTree* tree=0;
  


  TreeReader * tree_S1_1000_100 = new TreeReader(tree, "S1_1000_100", datalist);
  tree_S1_1000_100.Loop("S1_1000_100");
  delete tree_S1_1000_100;

  TreeReader * tree_TTJetsMadgraphZ2 = new TreeReader(tree, "NTuple_53X_TTJetsMadgraphZ2", datalist);
  tree_TTJetsMadgraphZ2.Loop("NTuple_53X_TTJetsMadgraphZ2");
  delete tree_TTJetsMadgraphZ2;


  TreeReader * tree_TTWJets_8TeVmadgraph = new TreeReader(tree, "NTuple_53X_TTWJets_8TeVmadgraph", datalist);
  tree_TTWJets_8TeVmadgraph.Loop("NTuple_53X_TTWJets_8TeVmadgraph");
  delete tree_TTWJets_8TeVmadgraph;


  TreeReader * tree_NTuple_53X_TTZJets_8TeVmadgraph_v2 = new TreeReader(tree, "NTuple_53X_TTZJets_8TeVmadgraph_v2", datalist);
  tree_NTuple_53X_TTZJets_8TeVmadgraph_v2.Loop("NTuple_53X_TTZJets_8TeVmadgraph_v2");
  delete tree_NTuple_53X_TTZJets_8TeVmadgraph_v2;


  TreeReader * tree_NTuple_53X_TZJetsTo3LNuB = new TreeReader(tree, "NTuple_53X_TZJetsTo3LNuB", datalist);
  tree_NTuple_53X_TZJetsTo3LNuB.Loop("NTuple_53X_TZJetsTo3LNuB");
  delete tree_NTuple_53X_TZJetsTo3LNuB;


  TreeReader * tree_NTuple_53X_WJetsToLNu = new TreeReader(tree, "NTuple_53X_WJetsToLNu", datalist);
  tree_NTuple_53X_WJetsToLNu.Loop("NTuple_53X_WJetsToLNu");
  delete tree_NTuple_53X_WJetsToLNu;


  TreeReader * tree_NTuple_53X_DYJetsToLL_M_10To50 = new TreeReader(tree, "NTuple_53X_DYJetsToLL_M-10To50", datalist);
  tree_NTuple_53X_DYJetsToLL_M_10To50.Loop("NTuple_53X_DYJetsToLL_M-10To50");
  delete tree_NTuple_53X_DYJetsToLL_M_10To50;


  TreeReader * tree_NTuple_53X_DYJetsToLL_M_50 = new TreeReader(tree, "NTuple_53X_DYJetsToLL_M-50", datalist);
  tree_NTuple_53X_DYJetsToLL_M_50.Loop("NTuple_53X_DYJetsToLL_M-50");
  delete tree_NTuple_53X_DYJetsToLL_M_50;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_T_s-channel", datalist);
  tree_.Loop("NTuple_53X_T_s-channel");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_T_t-channel", datalist);
  tree_.Loop("NTuple_53X_T_t-channel");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_T_tW-channel", datalist);
  tree_.Loop("NTuple_53X_T_tW-channel");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_Tbar_s-channel", datalist);
  tree_.Loop("NTuple_53X_Tbar_s-channe");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_Tbar_t-channel", datalist);
  tree_.Loop("NTuple_53X_Tbar_t-channel");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_Tbar_tW-channel", datalist);
  tree_.Loop("NTuple_53X_Tbar_tW-channel");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_WZJetsIncl", datalist);
  tree_.Loop("NTuple_53X_WZJetsIncl");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_WWJetsIncl", datalist);
  tree_.Loop("NTuple_53X_WWJetsIncl");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_ZZJetsIncl", datalist);
  tree_.Loop("NTuple_53X_ZZJetsIncl");
  delete tree_;




  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-20to30_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-20to30_MuEnrichedPt5");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-30to50_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-30to50_MuEnrichedPt5");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-50to80_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-50to80_MuEnrichedPt5");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-80to120_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-80to120_MuEnrichedPt5");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-120to170_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-120to170_MuEnrichedPt5");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-170to300_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-170to300_MuEnrichedPt");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "QCD_Pt-300to470_MuEnrichedPt5", datalist);
  tree_.Loop("QCD_Pt-300to470_MuEnrichedPt5");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_SingleMuRun2012A", datalist);
  tree_.Loop("NTuple_53X_SingleMuRun2012A");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_SingleMuRun2012B", datalist);
  tree_.Loop("NTuple_53X_SingleMuRun2012B");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_SingleMuRun2012C", datalist);
  tree_.Loop("NTuple_53X_SingleMuRun2012C");
  delete tree_;


  TreeReader * tree_ = new TreeReader(tree, "NTuple_53X_SingleMuRun2012D", datalist);
  tree_.Loop("NTuple_53X_SingleMuRun2012D");
  delete tree_;


  
}

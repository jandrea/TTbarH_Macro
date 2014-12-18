{
    gROOT->ProcessLine(".L TreeReader.C+");


    std::vector<TString > systlist;
    systlist.push_back("");
    systlist.push_back("lept__plus");
    systlist.push_back("lept__minus");
    //systlist.push_back("trig__plus");
    //systlist.push_back("trig__minus");
    //systlist.push_back("PDF__plus");
    //systlist.push_back("PDF__minus");
    systlist.push_back("PU__plus");
    systlist.push_back("PU__minus");
    systlist.push_back("jes__plus");
    systlist.push_back("jes__minus");
    systlist.push_back("jer__plus");
    systlist.push_back("jer__minus");
    systlist.push_back("metuncls__plus");
    systlist.push_back("metuncls__minus");

    /////////////////////////////////////////
    //////   QCDCorr possible values   //////
    ////   0 : QCD region (iso > 0.4)    ////
    ///    1 : Analysis wo QCD correction ///
    //     2 : Analysis with QCD correction /
    ///    3 : Analysis with systematics  ///
    /////////////////////////////////////////
    short int QCDCorr = 3;



    std::vector<TString > datalist_longnames;
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012A");
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012B");
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012C");
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012D");

    std::vector<TString > datalist;
    datalist.push_back("SingleMuA");
    datalist.push_back("SingleMuB");
    datalist.push_back("SingleMuC");
    datalist.push_back("SingleMuD");

    std::vector<TString > mclist;
    mclist.push_back("TTbar_Madgraph");
    //mclist.push_back("WJets");
    mclist.push_back("Wminus_Powheg");
    mclist.push_back("Wplus_Powheg");
    mclist.push_back("DYJetsToLL_M-10To50");
    mclist.push_back("DYJetsToLL_M-50");
    mclist.push_back("T_s");
    mclist.push_back("T_t");
    mclist.push_back("T_tW");
    mclist.push_back("Tbar_t");
    mclist.push_back("Tbar_tW");
    mclist.push_back("WZ");
    mclist.push_back("WW");
    mclist.push_back("ZZ");


    TTree* tree=0;


  if(QCDCorr == 0)
  {
  TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist, tree, "S1_1000_100", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "S1_1000_100", systlist);
    delete tree_;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_TTJetsMadgraphZ2", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_TTJetsMadgraphZ2", systlist);
    delete tree_;

/*
    TreeReader * tree_TTWJets_8TeVmadgraph = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_TTWJets_8TeVmadgraph", systlist);
    tree_TTWJets_8TeVmadgraph.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_TTWJets_8TeVmadgraph", systlist);
    delete tree_TTWJets_8TeVmadgraph;


    TreeReader * tree_NTuple_53X_TTZJets_8TeVmadgraph_v2 = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_TTZJets_8TeVmadgraph_v2", systlist);
    tree_NTuple_53X_TTZJets_8TeVmadgraph_v2.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_TTZJets_8TeVmadgraph_v2", systlist);
    delete tree_NTuple_53X_TTZJets_8TeVmadgraph_v2;


    TreeReader * tree_NTuple_53X_TZJetsTo3LNuB = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_TZJetsTo3LNuB", systlist);
    tree_NTuple_53X_TZJetsTo3LNuB.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_TZJetsTo3LNuB", systlist);
    delete tree_NTuple_53X_TZJetsTo3LNuB;
*/

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_WJetsToLNu", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_WJetsToLNu", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_DYJetsToLL_M-10To50", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_DYJetsToLL_M-10To50", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_DYJetsToLL_M-50", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_DYJetsToLL_M-50", systlist);
    delete tree_;

/*
    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_T_s-channel", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_T_s-channel", systlist);
    delete tree_;
*/

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_T_t-channel", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_T_t-channel", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_T_tW-channel", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_T_tW-channel", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_Tbar_s-channel", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_Tbar_s-channel", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_Tbar_t-channel", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_Tbar_t-channel", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_Tbar_tW-channel", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_Tbar_tW-channel", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_WZJetsIncl", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_WZJetsIncl", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_WWJetsIncl", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_WWJetsIncl", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_ZZJetsIncl", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_ZZJetsIncl", systlist);
    delete tree_;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-20to30_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-20to30_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-30to50_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-30to50_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-50to80_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-50to80_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-80to120_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-80to120_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-120to170_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-120to170_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-170to300_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-170to300_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-300to470_MuEnrichedPt5", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-300to470_MuEnrichedPt5", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_SingleMuRun2012A", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_SingleMuRun2012A", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_SingleMuRun2012B", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_SingleMuRun2012B", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_SingleMuRun2012C", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_SingleMuRun2012C", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "NTuple_53X_SingleMuRun2012D", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "NTuple_53X_SingleMuRun2012D", systlist);
    delete tree_;


  }

  if(QCDCorr == 1 || QCDCorr == 2 || QCDCorr == 3)
  {

    TreeReader * tree_S1 = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "S1", systlist);
    tree_S1.Loop(QCDCorr, datalist, datalist_longnames, mclist, "S1", systlist);
    delete tree_S1;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "TTbar_Madgraph", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "TTbar_Madgraph", systlist);
    delete tree_;
/*
    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "Wminus_Powheg", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "Wminus_Powheg", systlist);
    delete tree_;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "Wplus_Powheg", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "Wplus_Powheg", systlist);
    delete tree_;
*/
    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "WJets", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "WJets", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "DYJetsToLL_M-10To50", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "DYJetsToLL_M-10To50", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "DYJetsToLL_M-50", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "DYJetsToLL_M-50", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "T_s", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "T_s", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "T_t", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "T_t", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "T_tW", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "T_tW", systlist);
    delete tree_;

/*
    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "Tbar_s", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "Tbar_s", systlist);
    delete tree_;
*/

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "Tbar_t", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "Tbar_t", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "Tbar_tW", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "Tbar_tW", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "WZ", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "WZ", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "WW", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "WW", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "ZZ", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "ZZ", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "SingleMuA", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "SingleMuA", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "SingleMuB", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "SingleMuB", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "SingleMuC", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "SingleMuC", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "SingleMuD", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "SingleMuD", systlist);
    delete tree_;

  }

  if(QCDCorr == 1)
  {


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-20to30", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-20to30", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-30to50", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-30to50", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-50to80", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-50to80", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-80to120", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-80to120", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-120to170", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-120to170", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-170to300", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-170to300", systlist);
    delete tree_;


    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_Pt-300to470", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_Pt-300to470", systlist);
    delete tree_;

  }

  if(QCDCorr == 2 || QCDCorr == 3)
  {

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_A", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_A", systlist);
    delete tree_;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_B", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_B", systlist);
    delete tree_;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_C", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_C", systlist);
    delete tree_;

    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "QCD_D", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "QCD_D", systlist);
    delete tree_;

  }


}

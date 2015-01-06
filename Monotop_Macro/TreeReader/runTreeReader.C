{
    gROOT->ProcessLine(".L TreeReader.C+");


    std::vector<TString > systlist;
    systlist.push_back(""                      );
    systlist.push_back("lept__plus"            );
    systlist.push_back("lept__minus"           );
    //systlist.push_back("trig__plus"          );
    //systlist.push_back("trig__minus"         );
    //systlist.push_back("PDF__plus"           );
    //systlist.push_back("PDF__minus"          );
    systlist.push_back("PU__plus"              );
    systlist.push_back("PU__minus"             );
    systlist.push_back("jes__plus"             );
    systlist.push_back("jes__minus"            );
    systlist.push_back("jer__plus"             );
    systlist.push_back("jer__minus"            );
    systlist.push_back("metuncls__plus"        );
    systlist.push_back("metuncls__minus"       );
    systlist.push_back("btag__JESup"           );
    systlist.push_back("btag__JESdown"         );
    systlist.push_back("btag__CSVLFup"         );
    systlist.push_back("btag__CSVLFdown"       );
    systlist.push_back("btag__CSVHFStats1up"   );
    systlist.push_back("btag__CSVHFStats1down" );
    systlist.push_back("btag__CSVHFStats2up"   );
    systlist.push_back("btag__CSVHFStats2down" );
    systlist.push_back("btag__CSVCErr1up"      );
    systlist.push_back("btag__CSVCErr1down"    );
    systlist.push_back("btag__CSVCErr2up"      );
    systlist.push_back("btag__CSVCErr2down"    );
    systlist.push_back("btag__CSVHFup"         );
    systlist.push_back("btag__CSVHFdown"       );
    systlist.push_back("btag__CSVLFStats1up"   );
    systlist.push_back("btag__CSVLFStats1down" );
    systlist.push_back("btag__CSVLFStats2up"   );
    systlist.push_back("btag__CSVLFStats2down" );


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

    std::vector<TString > mclist_longnames;
    mclist_longnames.push_back("NTuple_53X_TTJetsMadgraphZ2"            );
    mclist_longnames.push_back("NTuple_53X_WJetsToLNu"                  );
    //mclist_longnames.push_back("NTuple_53X_TTWJets_8TeVmadgraph"      );
    //mclist_longnames.push_back("NTuple_53X_TTZJets_8TeVmadgraph_v2"   );
    //mclist_longnames.push_back("NTuple_53X_TZJetsTo3LNuB"             );
    mclist_longnames.push_back("NTuple_53X_DYJetsToLL_M-10To50"         );
    mclist_longnames.push_back("NTuple_53X_DYJetsToLL_M-50"             );
    mclist_longnames.push_back("NTuple_53X_T_s-channel"                 );
    mclist_longnames.push_back("NTuple_53X_T_t-channel"                 );
    mclist_longnames.push_back("NTuple_53X_T_tW-channel"                );
    mclist_longnames.push_back("NTuple_53X_Tbar_t-channel"              );
    mclist_longnames.push_back("NTuple_53X_Tbar_tW-channel"             );
    mclist_longnames.push_back("NTuple_53X_WZJetsIncl"                  );
    mclist_longnames.push_back("NTuple_53X_WWJetsIncl"                  );
    mclist_longnames.push_back("NTuple_53X_ZZJetsIncl"                  );
    mclist_longnames.push_back("QCD_Pt-20to30_MuEnrichedPt5"            );
    mclist_longnames.push_back("QCD_Pt-30to50_MuEnrichedPt5"            );
    mclist_longnames.push_back("QCD_Pt-50to80_MuEnrichedPt5"            );
    mclist_longnames.push_back("QCD_Pt-80to120_MuEnrichedPt5"           );
    mclist_longnames.push_back("QCD_Pt-120to170_MuEnrichedPt5"          );
    mclist_longnames.push_back("QCD_Pt-170to300_MuEnrichedPt5"          );
    mclist_longnames.push_back("QCD_Pt-300to470_MuEnrichedPt5"          );

    std::vector<TString > mclist;
    mclist.push_back("TTbar_Madgraph"       );
    mclist.push_back("WJets"                );
    //mclist.push_back("Wminus_Powheg"      );
    //mclist.push_back("Wplus_Powheg"       );
    mclist.push_back("DYJetsToLL_M-10To50"  );
    mclist.push_back("DYJetsToLL_M-50"      );
    mclist.push_back("T_s"                  );
    mclist.push_back("T_t"                  );
    mclist.push_back("T_tW"                 );
    mclist.push_back("Tbar_t"               );
    mclist.push_back("Tbar_tW"              );
    mclist.push_back("WZ"                   );
    mclist.push_back("WW"                   );
    mclist.push_back("ZZ"                   );

    std::vector<TString > qcdlist;
    qcdlist.push_back("QCD_Pt-20to30"   );
    qcdlist.push_back("QCD_Pt-30to50"   );
    qcdlist.push_back("QCD_Pt-50to80"   );
    qcdlist.push_back("QCD_Pt-80to120"  );
    qcdlist.push_back("QCD_Pt-120to170" );
    qcdlist.push_back("QCD_Pt-170to300" );
    qcdlist.push_back("QCD_Pt-300to470" );

    std::vector<TString > qcdcorrectedlist;
    qcdcorrectedlist.push_back("QCD_A");
    qcdcorrectedlist.push_back("QCD_B");
    qcdcorrectedlist.push_back("QCD_C");
    qcdcorrectedlist.push_back("QCD_D");


    TTree* tree=0;


  if(QCDCorr == 0)
  {
    TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist, tree, "S1_1000_100", systlist);
    tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, "S1_1000_100", systlist);
    delete tree_;

    for (unsigned int imc = 0; imc < mclist_longnames.size(); imc++)
    {
        TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, mclist_longnames[imc], systlist);
        tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, mclist_longnames[imc], systlist);
        delete tree_;
    }

    for (unsigned int idata = 0; idata < datalist_longnames.size(); idata++)
    {
        TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, datalist_longnames[idata], systlist);
        tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, datalist_longnames[idata], systlist);
        delete tree_;
    }
  }

  if(QCDCorr == 1 || QCDCorr == 2 || QCDCorr == 3)
  {
    TreeReader * tree_S1 = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, "S1", systlist);
    tree_S1.Loop(QCDCorr, datalist, datalist_longnames, mclist, "S1", systlist);
    delete tree_S1;

    for (unsigned int imc = 0; imc < mclist.size(); imc++)
    {
        TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, mclist[imc], systlist);
        tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, mclist[imc], systlist);
        delete tree_;
    }

    for (unsigned int idata = 0; idata < datalist.size(); idata++)
    {
        TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, datalist[idata], systlist);
        tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, datalist[idata], systlist);
        delete tree_;
    }
  }

  if(QCDCorr == 1)
  {
    for (unsigned int iqcd = 0; iqcd < qcdlist.size(); iqcd++)
    {
        TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, qcdlist[iqcd], systlist);
        tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, qcdlist[iqcd], systlist);
        delete tree_;
    }
  }

  if(QCDCorr == 2 || QCDCorr == 3)
  {
    for (unsigned int iqcd = 0; iqcd < qcdcorrectedlist.size(); iqcd++)
    {
        TreeReader * tree_ = new TreeReader(QCDCorr, datalist, datalist_longnames, mclist,  tree, qcdcorrectedlist[iqcd], systlist);
        tree_.Loop(QCDCorr, datalist, datalist_longnames, mclist, qcdcorrectedlist[iqcd], systlist);
        delete tree_;
    }
  }

}

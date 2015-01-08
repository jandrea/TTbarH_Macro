{
    gROOT->ProcessLine(".L TreeReader.C+");


    std::vector<TString > systlist;
    systlist.push_back(""                      );
    //systlist.push_back("jes__plus"             );
    //systlist.push_back("jes__minus"            );
    

    std::vector<TString > datalist_longnames;
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012A");
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012B");
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012C");
    datalist_longnames.push_back("NTuple_53X_SingleMuRun2012D");



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


    

    TTree* tree=0;
    for(unsigned int idata = 0; idata<datalist_longnames.size(); idata++){
      TreeReader * tree_DataMu = new TreeReader(tree,  datalist_longnames[idata], systlist);
      tree_DataMu.Loop(datalist_longnames[idata]);
      delete tree_DataMu;
    }
    
    
    for(unsigned int imc = 0; imc<mclist_longnames.size(); imc++){
      TreeReader * treeReader_tmp= new TreeReader(tree, mclist_longnames[imc], systlist);
      treeReader_tmp.Loop( mclist_longnames[imc] );
      delete treeReader_tmp;
    }
    
}

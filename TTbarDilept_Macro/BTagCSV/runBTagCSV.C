{
  gROOT->ProcessLine(".L BTagCSV.C+");  

  TTree* tree=0;
  
  BTagCSV *tree_tZq = new BTagCSV(tree,"tZq");
  tree_tZq.Loop("tZq");
  delete tree_tZq;
  
  BTagCSV *tree_WZ = new BTagCSV(tree,"WZ");
  tree_WZ.Loop("WZ");
  delete tree_WZ;

  BTagCSV *tree_TT = new BTagCSV(tree,"TT");
  tree_TT.Loop("TT");
  delete tree_TT;

  BTagCSV *tree_TTW = new BTagCSV(tree,"TTW");
  tree_TTW.Loop("TTW");
  delete tree_TTW;

  BTagCSV *tree_TTZ = new BTagCSV(tree,"TTZ");
  tree_TTZ.Loop("TTZ");
  delete tree_TTZ;

  BTagCSV *tree_TbarsChan = new BTagCSV(tree,"TbarsChan");
  tree_TbarsChan.Loop("TbarsChan");
  delete tree_TbarsChan;

  BTagCSV *tree_TbartChan = new BTagCSV(tree,"TbartChan");
  tree_TbartChan.Loop("TbartChan");
  delete tree_TbartChan;

  BTagCSV *tree_TbartW = new BTagCSV(tree,"TbartW");
  tree_TbartW.Loop("TbartW");
  delete tree_TbartW;

  BTagCSV *tree_TsChan = new BTagCSV(tree,"TsChan");
  tree_TsChan.Loop("TsChan");
  delete tree_TsChan;

  BTagCSV *tree_TtChan = new BTagCSV(tree,"TtChan");
  tree_TtChan.Loop("TtChan");
  delete tree_TtChan;

  BTagCSV *tree_TtW = new BTagCSV(tree,"TtW");
  tree_TtW.Loop("TtW");
  delete tree_TtW;

  BTagCSV *tree_WW = new BTagCSV(tree,"WW");
  tree_WW.Loop("WW");
  delete tree_WW;

  BTagCSV *tree_ZZ = new BTagCSV(tree,"ZZ");
  tree_ZZ.Loop("ZZ");
  delete tree_ZZ;

  BTagCSV *tree_Wjets = new BTagCSV(tree,"Wjets");
  tree_Wjets.Loop("Wjets");
  delete tree_Wjets;

  BTagCSV *tree_Zjets = new BTagCSV(tree,"Zjets");
  tree_Zjets.Loop("Zjets");
  delete tree_Zjets;
   
  gApplication->Terminate();
}

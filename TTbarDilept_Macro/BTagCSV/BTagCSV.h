#ifndef BTagCSV_h
#define BTagCSV_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>

#include <TLorentzVector.h>

#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class BTagCSV {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   // Declaration of leaf types
   Int_t             treeCSV_jetN;
   Float_t           treeCSV_jetPt[1000];
   Float_t           treeCSV_jetEta[1000];
   Float_t           treeCSV_jetCSV[1000];
   Int_t             treeCSV_jetFlav[1000];
   Int_t             treeCSV_SampleType;
   Int_t             treeCSV_Channel;
   Float_t           treeCSV_EvtWeight;

   // List of branches
   TBranch        *b_treeCSV_jetN;
   TBranch        *b_treeCSV_jetPt;
   TBranch        *b_treeCSV_jetEta;
   TBranch        *b_treeCSV_jetCSV;
   TBranch        *b_treeCSV_jetFlav;
   TBranch        *b_treeCSV_SampleType;
   TBranch        *b_treeCSV_Channel;
   TBranch        *b_treeCSV_EvtWeight;
  
   BTagCSV(TTree *tree=0, TString sample="");
   virtual ~BTagCSV();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString sample);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   
   TFile *fout;
};

#endif

#ifdef BTagCSV_cxx
BTagCSV::BTagCSV(TTree *tree, TString sample) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) 
     {
	TFile *f = TFile::Open("../TreeReader/outputroot/histofile_merged.root");
	f->GetObject( ("TtreeCSV_"+sample).Data(),tree);
     }
   Init(tree);
   
   fout = new TFile(("hist/output_"+sample+".root").Data(),"RECREATE");
}

BTagCSV::~BTagCSV()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
   
   fout->Write();
   fout->Close();
}

Int_t BTagCSV::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t BTagCSV::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void BTagCSV::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("treeCSV_jetN", &treeCSV_jetN, &b_treeCSV_jetN);
   fChain->SetBranchAddress("treeCSV_jetPt", &treeCSV_jetPt, &b_treeCSV_jetPt);
   fChain->SetBranchAddress("treeCSV_jetEta", &treeCSV_jetEta, &b_treeCSV_jetEta);
   fChain->SetBranchAddress("treeCSV_jetCSV", &treeCSV_jetCSV, &b_treeCSV_jetCSV);
   fChain->SetBranchAddress("treeCSV_jetFlav", &treeCSV_jetFlav, &b_treeCSV_jetFlav);
   
   fChain->SetBranchAddress("treeCSV_SampleType", &treeCSV_SampleType, &b_treeCSV_SampleType);
   fChain->SetBranchAddress("treeCSV_EvtWeight", &treeCSV_EvtWeight, &b_treeCSV_EvtWeight);
   fChain->SetBranchAddress("treeCSV_Channel", &treeCSV_Channel, &b_treeCSV_Channel);
   
   Notify();
}

Bool_t BTagCSV::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void BTagCSV::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t BTagCSV::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef BTagCSV_cxx

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec 26 15:02:48 2014 by ROOT version 5.34/18
// from TTree SmallTree_S1_1000_100/SmallTree_S1_1000_100
// found on file: ../Inputs/proof_merged_monotop.root
//////////////////////////////////////////////////////////

#ifndef Optimization_h
#define Optimization_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


#include "GeneticAlgo.h"
#include "Individual.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Optimization {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           smalltree_nlepton;
   Float_t         smalltree_lept_pt[1];   //[smalltree_nlepton]
   Float_t         smalltree_lept_eta[1];   //[smalltree_nlepton]
   Float_t         smalltree_lept_phi[1];   //[smalltree_nlepton]
   Float_t         smalltree_lept_iso[1];   //[smalltree_nlepton]
   Int_t           smalltree_lept_flav[1];   //[smalltree_nlepton]
   Int_t           smalltree_njets;
   Float_t         smalltree_jet_pt[100];   //[smalltree_njets]
   Float_t         smalltree_jet_eta[100];   //[smalltree_njets]
   Float_t         smalltree_jet_phi[100];   //[smalltree_njets]
   Float_t         smalltree_jet_btagdiscri[100];   //[smalltree_njets]
   Int_t           smalltree_jet_flav[100];   //[smalltree_njets]
   Float_t         smalltree_met_pt;
   Float_t         smalltree_met_phi;
   Float_t         smalltree_evtweight;

   // List of branches
   TBranch        *b_smalltree_nlepton;   //!
   TBranch        *b_smalltree_lept_pt;   //!
   TBranch        *b_smalltree_lept_eta;   //!
   TBranch        *b_smalltree_lept_phi;   //!
   TBranch        *b_smalltree_lept_iso;   //!
   TBranch        *b_smalltree_lept_flav;   //!
   TBranch        *b_smalltree_njets;   //!
   TBranch        *b_smalltree_jet_pt;   //!
   TBranch        *b_smalltree_jet_eta;   //!
   TBranch        *b_smalltree_jet_phi;   //!
   TBranch        *b_smalltree_jet_btagdiscri;   //!
   TBranch        *b_smalltree_jet_flav;   //!
   TBranch        *b_smalltree_met_pt;   //!
   TBranch        *b_smalltree_met_phi;   //!
   TBranch        *b_smalltree_evtweight;   //!

   Optimization(TTree *tree=0, bool doSignal=false);
   virtual ~Optimization();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual double   Loop(double lept_pT, double jet_pT, double theMWT);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Optimization_cxx
Optimization::Optimization(TTree *tree, bool doSignal) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../Inputs/proof_merged_monotop.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../Inputs/proof_merged_monotop.root");
      }
      if(doSignal) f->GetObject("SmallTree_S1_1000_100",tree);
      else         f->GetObject("SmallTree_NTuple_53X_WJetsToLNu",tree);

   }
   Init(tree);
}

Optimization::~Optimization()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Optimization::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Optimization::LoadTree(Long64_t entry)
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

void Optimization::Init(TTree *tree)
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

   fChain->SetBranchAddress("smalltree_nlepton", &smalltree_nlepton, &b_smalltree_nlepton);
   fChain->SetBranchAddress("smalltree_lept_pt", smalltree_lept_pt, &b_smalltree_lept_pt);
   fChain->SetBranchAddress("smalltree_lept_eta", smalltree_lept_eta, &b_smalltree_lept_eta);
   fChain->SetBranchAddress("smalltree_lept_phi", smalltree_lept_phi, &b_smalltree_lept_phi);
   fChain->SetBranchAddress("smalltree_lept_iso", smalltree_lept_iso, &b_smalltree_lept_iso);
   fChain->SetBranchAddress("smalltree_lept_flav", smalltree_lept_flav, &b_smalltree_lept_flav);
   fChain->SetBranchAddress("smalltree_njets", &smalltree_njets, &b_smalltree_njets);
   fChain->SetBranchAddress("smalltree_jet_pt", smalltree_jet_pt, &b_smalltree_jet_pt);
   fChain->SetBranchAddress("smalltree_jet_eta", smalltree_jet_eta, &b_smalltree_jet_eta);
   fChain->SetBranchAddress("smalltree_jet_phi", smalltree_jet_phi, &b_smalltree_jet_phi);
   fChain->SetBranchAddress("smalltree_jet_btagdiscri", smalltree_jet_btagdiscri, &b_smalltree_jet_btagdiscri);
   fChain->SetBranchAddress("smalltree_jet_flav", smalltree_jet_flav, &b_smalltree_jet_flav);
   fChain->SetBranchAddress("smalltree_met_pt", &smalltree_met_pt, &b_smalltree_met_pt);
   fChain->SetBranchAddress("smalltree_met_phi", &smalltree_met_phi, &b_smalltree_met_phi);
   fChain->SetBranchAddress("smalltree_evtweight", &smalltree_evtweight, &b_smalltree_evtweight);
   Notify();
}

Bool_t Optimization::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Optimization::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Optimization::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Optimization_cxx

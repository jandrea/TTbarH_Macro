############# run the code #############
############# run the code #############
############# run the code #############
The main code is in the TreeReader directory. It run over a flat tree, 
applies event selection and produce plots.

To run it simply do :

cd TreeReader/
root -l runTreeReader.C

the output root files are produced in the outputroot/ subdirectory.
WARNING : they have to be merged with hadd

hadd histofile_merged.root *.root

(To do : do it automatically in runTreeReader.C)


############# How to change the input file :

go to TreeReader.h and modify the 2 pathes in 

TreeReader::TreeReader(TTree *tree, TString sample, std::vector<TString> thesystlist) : fChain(0) 

around line 267.

The current NTuple file to use can be found on ;


/opt/sbg/data/safe1/cms/jandrea/UpdateFramework_2013_08_22/CMSSW_5_3_11/src/IPHCAnalysis/NTuple/macros/Monotop/backup_outputProof28-11-14_23-00/proof_merged_monotop.root


############# How to add a histogram :

edite TreeReader.C

go to the "initializeHisto" function
and add a line with the following formate

addHisto("Variable",      "selectionstep",  sample.Data(),  nbin, xmin, xmax);


############# edit event selection and fill histogram :

edite TreeReader.C

go to the "applyEventSel" function
After line 237, just apply the event selection you like.
Object selection is already performed at the step of producing the TTree.

To fill histogram, just do :

fillHisto(thechannel, "variable",        "selectionstep",  thesample,   var_value,    evtweight);
        
WARNING : "variable" and "selectionstep" shoulw match histograms in "initializeHisto"
If an histogram that is not existing is being filled, there will be a warning on the screen.


############# How To produce plots #############
############# How To produce plots #############
############# How To produce plots #############


To produce plots (in gif format), go to the PlotMaker/ directory
Simply do : 

root -l makePlots.C


the list of samples to be considered, the list of pltos to produced and 
the list of systematic are configurable in "makePlots.C".
I tink it is clear enough.

#include "RunOptimization.h"


RunOptimization::RunOptimization(){

  theGenAlgo.createPopulation(0);
  
}

RunOptimization::RunOptimization(int nindividuals){

  theGenAlgo.createPopulation(nindividuals);
  
}

double RunOptimization::evaluateQuality(Individual theInd){

  std::vector<double> theGenes = theInd.getGenes();
  
  TTree * theTree = 0;
  theOpt = new Optimization(theTree, true);
  double theSignal = theOpt->Loop(theGenes[0], theGenes[1], theGenes[2]);
  
  
  theOpt = new Optimization(theTree, false);
  double thebackground = theOpt->Loop(theGenes[0], theGenes[1], theGenes[2]);
  
  //cout << "theSignal  " << theSignal << endl;
  //cout << "thebackground  " << thebackground << endl;
  return theSignal/pow( theSignal + thebackground, 0.5);
  
  
}

void RunOptimization::sortIndividuals(){
  
  
  for(unsigned int i=0; i<theGenAlgo.theInd.size(); i++){
    cout << "evaluate Quality of the  individual  " << i << "/" << theGenAlgo.theInd.size() << endl;
    double significance = evaluateQuality( theGenAlgo.theInd[i]);
    
    theGenAlgo.theInd[i].setQualityCriteria(significance);
    
  }
  
  theGenAlgo.sortIndividuals();
  theGenAlgo.selectIndividuals();
}

void RunOptimization::nextGeneration(){
  cout << "[nextGeneration] create a new population " << endl;
  theGenAlgo.crossPopulation();
  //cout << "[nextGeneration] size of the new population " << theGenAlgo.theInd.size() << endl;
  //theGenAlgo.selectIndividuals();
  //cout << "[nextGeneration] truncated population if too large " << theGenAlgo.theInd.size() << endl;
  cout << "[nextGeneration] size of the new population " << theGenAlgo.theInd.size() << endl;
  //theGenAlgo.displayPolulation();
  
}


void RunOptimization::displayPopulation(){
  
  theGenAlgo.displayPolulation();
  
}

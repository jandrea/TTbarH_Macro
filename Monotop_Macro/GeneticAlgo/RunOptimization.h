#ifndef RunOptimization_h
#define RunOptimization_h


#include "GeneticAlgo.h"
#include "Individual.h"
#include "Optimization.h"
#include "TTree.h"


class RunOptimization{
  
public : 
  
  RunOptimization();
  RunOptimization(int nindividuals);
  
  ~RunOptimization(){};
  
  GeneticAlgo theGenAlgo;
  
  Optimization *theOpt;
  
  
  double evaluateQuality(Individual theInd);
  
  void sortIndividuals();
  
  void nextGeneration();
  
  void displayPopulation();
  
};


#endif // #ifdef RunOptimization_cxx

//////////////////////////////////////////////////////////
// This class has been created on
// Wed Dec 24 15:55:04 2014 
//////////////////////////////////////////////////////////

#ifndef GeneticAlgo_h
#define GeneticAlgo_h


#include "TRandom1.h"
#include "Individual.h"
#include <algorithm>
#include <iostream>

struct sortclass {
  bool operator() ( Individual i, Individual j) { return (i.qualityCriteria > j.qualityCriteria);}
} mysort;


class  GeneticAlgo{

public :

  GeneticAlgo(){};
  
  ~GeneticAlgo(){};
  
  // create the population
  void createPopulation(int nindiv);
  
  //cross the induvudual of the population
  void crossPopulation();
  
  //mutate the individual of the population
  void mutatePopulation();
  
  //selection of individuals
  void selectIndividuals();
  
  //selection of individuals
  void sortIndividuals();
  
  
  //for radom numbers
  TRandom1 rand;
  
  //idividual class
  std::vector<Individual> theInd;
  
  void displayPolulation(){
    
    for(unsigned int i=0; i<theInd.size(); i++){
      
      std::vector<double> thegenesv = theInd[i].getGenes();
      double              thequalv = theInd[i].getQualityCriteria();
      cout << "the genes : " ;
      
      for(unsigned int j=0; j< thegenesv.size(); j++){
        cout << "  " << thegenesv[j] ;
      }
      cout << "  " << endl;
      cout << "  the qual : " << thequalv << endl;
    }
  }
  
  
};


#endif 

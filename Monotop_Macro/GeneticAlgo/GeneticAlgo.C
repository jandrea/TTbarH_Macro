#define  GeneticAlgo_cxx
#include "GeneticAlgo.h"


using namespace std;

// create the population
void GeneticAlgo::createPopulation(int nindiv){
  
  for(int i=0; i<nindiv; i++){
  
    std::vector<double > varlist;
    //--------------------------
    //for lepton pT optimization
    double min_lept_pT = 20.;
    double max_lept_pT = 200.;
    varlist.push_back(min_lept_pT + rand.Uniform()*(max_lept_pT-min_lept_pT));
    
    
    //--------------------------
    //for jet pT optimization
    double min_jet_pT = 30.;
    double max_jet_pT = 200.;
    varlist.push_back(min_jet_pT + rand.Uniform()*(max_jet_pT-min_jet_pT));
    
    
    
    //--------------------------
    //mWT pT optimization
    double min_mWT = 0.;
    double max_mWT = 500.;
    varlist.push_back(min_mWT + rand.Uniform()*(max_mWT-min_mWT));
    
    
    theInd.push_back(Individual(varlist, 0));
     
  }
  
  
}


//cross the individual of the population
void GeneticAlgo::crossPopulation(){

}

//mutate the individual of the population
void GeneticAlgo::mutatePopulation(){

}


//selection of individuals
void GeneticAlgo::selectIndividuals(){




}

//selection of individuals
void GeneticAlgo::sortIndividuals(){

 // using object as comp
  std::sort (theInd.begin(), theInd.end(), mysort);     //(12 26 32 33 45 53 71 80)



}


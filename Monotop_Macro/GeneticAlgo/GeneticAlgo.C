#define  GeneticAlgo_cxx
#include "GeneticAlgo.h"


using namespace std;

// create the population
void GeneticAlgo::createPopulation(int nindiv){
  nindividuals = nindiv;
  
  for(int i=0; i<nindiv; i++){
  
    std::vector<double > varlist;
    //--------------------------
    //for lepton pT optimization
    double min_lept_pT = 33.;
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
  
  std::vector<Individual> theInd_tomix ;
  double total_quality = 0;
  for(unsigned int i=0; i<theInd.size(); i++){
    
    total_quality += theInd[i].getQualityCriteria();
    
  }
  //cout << "[crossPopulation] total quality is " << total_quality << endl;
  cout << "[crossPopulation] nindividuals " << nindividuals << endl;
  for(int k=0; k<  nindividuals; k++){
    for(unsigned int i=0; i<theInd.size(); i++){
      if(  rand.Uniform(total_quality) < theInd[i].getQualityCriteria()   ){
        theInd_tomix.push_back(theInd[i]);
      }
    }
  }
  
  //cout << "[crossPopulation] size of the population to mix " << theInd_tomix.size() << endl;
  
  std::vector<Individual> theInd_new;
  for(unsigned int i=0; i<theInd_tomix.size(); i++){
    
    std::vector<double> thegenes;
    for(unsigned int j=0;j < theInd_tomix[0].getGenes().size();j++){
    
      double theSingleGen = (theInd_tomix[ int(rand.Uniform(theInd_tomix.size()))].getGenes())[j];
      
      if(rand.Uniform() > 0.50){
        theSingleGen = rand.Gaus(theSingleGen, theSingleGen*0.50);
	if(j==0 && theSingleGen < 33) theSingleGen = 33;
	if(j==1 && theSingleGen < 30) theSingleGen = 30;
	if(j==3 && theSingleGen <  0) theSingleGen =  0;
      }
      thegenes.push_back( theSingleGen);
    }
    
    Individual thenewInd(thegenes, 0);
    theInd.push_back(thenewInd);
  }
  
  
  cout << "[crossPopulation] size of the new population " << theInd_tomix.size() << endl;
}


//selection of individuals
void GeneticAlgo::selectIndividuals(){
  
  
  cout << "[selectIndividuals] nindividuals " << nindividuals<< endl;
  cout << "[selectIndividuals] theInd.size() " <<theInd.size() << endl;
  std::vector<Individual> theInd_truncated ;
  if(nindividuals < theInd.size() ){
    for(unsigned int i=0; i< nindividuals; i++){
      theInd_truncated.push_back(theInd[i]);
    }
    theInd = theInd_truncated;
  }
  
  
  
  
}

//selection of individuals
void GeneticAlgo::sortIndividuals(){

 // using object as comp
  std::sort (theInd.begin(), theInd.end(), mysort);     



}


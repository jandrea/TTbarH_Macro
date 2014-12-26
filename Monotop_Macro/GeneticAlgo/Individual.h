//////////////////////////////////////////////////////////
// This class has been created on
// Wed Dec 24 15:55:04 2014 
//////////////////////////////////////////////////////////

#ifndef Individual_h
#define Individual_h

class  Individual{


private : 

  std::vector<double > genes;
  
  double qualityCriteria;

public :

  Individual(){};
  
  Individual(std::vector<double > thegenes, double thequal){
     genes = thegenes;
     qualityCriteria = thequal;
  };
  
  ~Individual(){};
  
  void setQualityCriteria(double thequal)    {qualityCriteria = thequal;};
  void setGenes(std::vector<double> thegenes){ genes = thegenes;};
  
  double getQualityCriteria(){return qualityCriteria;};
  std::vector<double>  getGenes(){return genes;};
  
};


#endif 

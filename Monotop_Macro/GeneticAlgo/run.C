{
  gROOT->ProcessLine(".L GeneticAlgo.C+");
  gROOT->ProcessLine(".L Optimization.C+");
  gROOT->ProcessLine(".L RunOptimization.C+");
  
  //---------------
  //first iteration
  //---------------
  cout << "first iteration " << endl;
  RunOptimization thopt(150);
  thopt.sortIndividuals();
  thopt.displayPopulation();
  for(int i=0; i<15; i++){
    cout << "calculation for generation " << i+1 << endl;
    //---------------------
    //create new population
    //---------------------
    thopt.nextGeneration();
    
    cout << "do sorting "  << endl;
    //----------------------
    //determine new quality
    //----------------------
    thopt.sortIndividuals();
    thopt.displayPopulation();
  }
  
  
  
}

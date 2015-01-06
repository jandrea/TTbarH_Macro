//#include "../interface/SimpleJetResolution.h"

void TestJetResolution()
{
double rawPt=100;
double rawEta=1;
double rawPhi=0;
double rawE=9.8; 
double JPTE=200;
int NPU=20;
  //gROOT->ProcessLine("#include <vector>");
  gSystem->Load("../../lib/libJetMETObjects.so");
  //gSystem->Load("/home/jandrea/WORK/TTbarDilept_Macro/JetMETObjects/test/../../tmp/SimpleJetResolution.o");
  //AutoLibraryLoader::enable();
  ////////////// Construct the JetCorrectorParameters objects ///////////////////////

  string ak5CHSTag = "../data/JetResolutionInputAK5PFCHS.txt"; 
  string ak5Tag = "../data/JetResolutionInputAK5PF.txt"; 
  JetCorrectorParameters *AK5PFCHSPar    = new JetCorrectorParameters(ak5CHSTag);
  JetCorrectorParameters *AK5PFPar    = new JetCorrectorParameters(ak5Tag);
  cout<<"AK5PFCHSPar isValid:"<<AK5PFCHSPar->isValid()<<endl;
  cout<<"AK5PFCHSPar size:"<<AK5PFCHSPar->size()<<endl;
  cout<<"AK5PFPar isValid:"<<AK5PFPar->isValid()<<endl;
  cout<<"AK5PFPar size:"<<AK5PFPar->size()<<endl;
//  cout<<"L1Par printScreen:"<<L1Par->printScreen()<<endl;
  ////////////// Construct a FactorizedJetCorrector object //////////////////////
//  JetUncertainty->setJetEta(0.4);
  ////////////// Loop over jets //////////////////////
  std::vector<float> fx, fY;
  fx.push_back(0.04);  // Jet Eta
  fY.push_back(50); // Jet PT
  fY.push_back(35); // Number of truth pileup
  SimpleJetResolution *ak5PFResolution =  new SimpleJetResolution(*AK5PFPar);
  cout<<"ak5PFResolution Jet pT=: "<<fY[0]<<" GeV, Number of Truth pielup: "<<fY[1]<<" eta: "<<fx[0]<<" resoltuion: "<<ak5PFResolution->resolution(fx,fY)<<endl; // get resolution 
  SimpleJetResolution *ak5PFCHSResolution =  new SimpleJetResolution(*AK5PFCHSPar);
  cout<<"ak5PFCHSResolution Jet pT=: "<<fY[0]<<" GeV, Number of Truth pielup: "<<fY[1]<<" eta: "<<fx[0]<<" resoltuion: "<<ak5PFCHSResolution->resolution(fx,fY)<<endl; // get resolution 
//  cout<<"Correction applied to JPT jet after L1Offset = "<<vcor[0]<<endl;
//  cout<<"Correction applied to JPT jet after L1JPTOffset = "<<vcor[1]<<endl;
}

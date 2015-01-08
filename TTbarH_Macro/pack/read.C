{
   gROOT->SetBatch(1);
   
   gSystem->Load("libNtuple");

   TFile *f = TFile::Open("output.root");
   TTree *tr = (TTree*)f->Get("Nt");
   
   int nev = tr->GetEntries();
   std::cout << "Total number of events is " << nev << std::endl;

   std::vector<Electron> *v_Electron = new std::vector<Electron>();
   tr->SetBranchAddress("Electron", &v_Electron);
   
   for(int i=0;i<nev;i++)
     {
	tr->GetEntry(i);
	
	int nElec = v_Electron->size();
	for(int ie=0;ie<nElec;ie++)
	  {	     
	     std::cout << v_Electron->at(ie).pt() << std::endl;
	  }	
     }

   gApplication->Terminate();
}

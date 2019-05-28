//This code written by Philip Adsley - e-mail padsley@gmail.com with any suggestions, problems, queries or comments
#include "K600DigitalMerge.h"

int main(int argc, char *argv[])
{
    bool FoundVME = false;
    bool FoundDig = false;
    bool VerboseFlag = false;

    int EventOffset = 0;
    
    TGraph *gTACRatios = new TGraph();
    TGraph *gSkips = new TGraph();
    int GraphCounter = 0;
    
    if(argc!=4)
    {
        fprintf(stderr, "usage: mcerr <filename for VME DAQ> <filename for digital DAQ> <verbosity setting - 1 is verbose, anything else is false>\n");
        exit(1);
    }
    
    if(atoi(argv[3]) == 1)
    {
        std::cout << "Setting verbose mode on" << std::endl;
        VerboseFlag = true;
    }
    
    std::cout << "Run number is set according to the VME file" << std::endl;
    
    std::string RunName = argv[1];
    if(VerboseFlag)std::cout << RunName.substr(6,5) << std::endl;
    int RunNumber = atoi(RunName.substr(6,5).c_str());
    if(VerboseFlag)std::cout << "Run number: " << RunNumber << std::endl;
    
    std::cout << "Using VME DAQ file: " << argv[1] << std::endl;
    
    TFile *fVME = TFile::Open(argv[1]);
    
    if(!fVME)
    {
        fprintf(stderr, "Cannot find VME input file given\n");
        exit(1);
    }
    else
    {
        FoundVME = true;
        if(VerboseFlag)fVME->ls();
    }
    
    std::cout << "Using digital DAQ file: " << argv[2] << std::endl;
    
    TFile *fDig = TFile::Open(argv[2]);
    
    if(!fDig)
    {
        fprintf(stderr, "Cannot find digital input file given\n");
        exit(1);
    }
    else
    {
        FoundDig = true;
        if(VerboseFlag)fDig->ls();
    }
    
    
    //Get the information from the VME TTree - how many TBranches, what the names are etc.
    TTree *tVME = (TTree*)fVME->FindObjectAny("DATA");
    if(VerboseFlag)tVME->Print();
    
    TObjArray *branchListVME = (TObjArray*)tVME->GetListOfBranches();
    TObjArray *leafListVME   = (TObjArray*)tVME->GetListOfLeaves();
    int nBranchesVME = tVME->GetNbranches();
    
    TString *BranchNamesVME = new TString[nBranchesVME];
    TString *LeafTypesVME = new TString[nBranchesVME];
    
    for(unsigned int i=0;i<nBranchesVME;i++)
    {
        BranchNamesVME[i] = branchListVME->At(i)->GetName();
        if(VerboseFlag)std::cout << "BranchNamesVME[" << i << "]: " << BranchNamesVME[i] << std::endl;
        LeafTypesVME[i] = (tVME->GetLeaf(leafListVME->At(i)->GetName()))->GetTypeName();
        if(VerboseFlag)std::cout << "LeafTypesVME[" << i << "]: " << LeafTypesVME[i] << std::endl;
    }
    
    if(VerboseFlag)std::cout << "nBranchesVME: " << nBranchesVME << std::endl;
    
    //Now do the same as above for the digital DAQ TBranches
    TTree *tDig = (TTree*)fDig->FindObjectAny("DATA");
    if(VerboseFlag)tDig->Print();
    
    TObjArray *branchListDig = (TObjArray*)tDig->GetListOfBranches();
    TObjArray *leafListDig   = (TObjArray*)tDig->GetListOfLeaves();
    int nBranchesDig = tDig->GetNbranches();
    
    TString *BranchNamesDig = new TString[nBranchesDig];
    TString *LeafTypesDig   = new TString[nBranchesDig];
    int *LeafLengthsDig = new int [nBranchesDig];
    
    int DigInts = 0;
    int DigDoubles = 0;
    
    for(unsigned int i=0;i<nBranchesDig;i++)
    {
        BranchNamesDig[i] = branchListDig->At(i)->GetName();
        if(VerboseFlag)std::cout << "BranchNamesDig[" << i << "]: " << BranchNamesDig[i] << std::endl;
        LeafTypesDig[i] = (tDig->GetLeaf(leafListDig->At(i)->GetName()))->GetTypeName();
        if(VerboseFlag)std::cout << "LeafTypesDig[" << i << "]: " << LeafTypesDig[i] << std::endl;
        LeafLengthsDig[i] = (tDig->GetLeaf(leafListDig->At(i)->GetName()))->GetLen();
        if(VerboseFlag)std::cout << "LeafLengthsDig[" << i << "]: " << LeafLengthsDig[i] << std::endl;
        
        if(LeafTypesDig[i] == "Int_t")DigInts++;
        else if(LeafTypesDig[i] == "Double_t")DigDoubles++;
        else std::cout << "Leaf type not found" << std::endl;
    }
    
    if(VerboseFlag)std::cout << "nBranchesDig: " << nBranchesDig << std::endl;
    
    
    //Now creat the output merged file
    TFile *fOut = new TFile(Form("merged%d.root",RunNumber),"RECREATE");
    TTree *trout = new TTree("DATA","Merged data from K600 VME and digital DAQs");
    
    int VMETAC = 0;
    double DigTAC = 0;
    tVME->SetBranchAddress("TAC",&VMETAC);
    tDig->SetBranchAddress("tac_energy",&DigTAC);
    
    //Do it first for the VME DAQ branches
    for(unsigned int i=0;i<nBranchesVME;i++)
    {
//         tVME->Branch(
    }
    
    //...and now do it for the digital DAQ branches
    for(unsigned int i=0;i<nBranchesDig;i++)
    {
        char type;
        if(LeafTypesDig[i] == "Int_t")type = "I";
        else if(LeafTypesDig[i] == "Double_t")type = "D";
        else std::cout << "Leaf type not defined" << std::endl;
        
        if(LeafLengthsDig[i]==1)trout->Branch(BranchNamesDig[i],,Form("%s/%s",BranchNames[i],type));
        else trout->Branch(BranchNamesDig[i],,Form("%s[%d]/%s",BranchNames[i],LeafLengthsDig[i],type));
    }
    
    if(VerboseFlag)trout->Print();//Now print out the information in the combined TTree to check that the branches have the right names and types and sizes
    
    //Now loop over all the entries in the VME DAQ to look for 
    for(Long64_t jentry;jentry<tVME->GetEntries();jentry++)
    {
        tVME->GetEntry(jentry);
        
        tDig->GetEntry(jentry + EventOffset);
        
        
        //Compute the TAC ratio from the VME and digital DAQ data
//         tacratio = 0.08*DigTacEnergy/(MidasTac-200);
        double TACRatio = TACPar[0] * DigTAC / ((double)VMETAC - TACPar[1]);
        
        if((TACRatio>TACRatioLimits[0] && TACRatio<TACRatioLimits[1]) || TACRatio>TACRatioLimits[2])
        {
//             EventOffset = FindNextDigitalEvent(jentry,EventOffset,tVME,tDig);
        }
    }
    
    fVME->Close();
    fDig->Close();
    fOut->Close();
    return 0;
}

/*
int ReAlignDAQs(int MidasEventNumber, int DigitalEventSkip, TTree* MidasTree, TTree *DigitalTree)
{
    cout << "Bad TAC ratio - going to try to find the next good digital TAC event" << endl;
    
    int result = DigitalEventSkip; //Return number of skipped events to get a good correlation again
    
    cout << "Starting with skipping " << result << " events" << endl;    
    
    bool MatchEvents = false;
    bool PositiveMove = true;
    int StepSize = 1;
    
    while(abs(result-DigitalEventSkip)<100 && !MatchEvents)
    {
        cout << "DigitalEventSkip = " << result << endl;
        cout << "This is " << result-DigitalEventSkip << " more skips since the last matching event" << endl;
        
        MidasTree->GetEntry(MidasEventNumber);
        DigitalTree->GetEntry(MidasEventNumber+result);
        
        double tacratio = 0.08*DigTacEnergy/(MidasTac-200);
        cout << "tacratio: " << tacratio << endl;
        
        if(!((tacratio>lowratio1 && tacratio<hiratio1) || tacratio>lowratio2))
        {
            MatchEvents = true;
            cout << "Found GOOD matching event" << endl;
        }
        else if(PositiveMove)
        {
            result = result+StepSize;
            PositiveMove = false;
        }
        else if(!PositiveMove)
        {
            result = result - StepSize;
            PositiveMove = true;
        }
        StepSize++;
    }
    
    cout << endl;
    
    return result;
}
*/
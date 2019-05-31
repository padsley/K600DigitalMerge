//This code written by Philip Adsley - e-mail padsley@gmail.com with any suggestions, problems, queries or comments
#include "K600DigitalMerge.h"

bool VerboseFlag = false;
bool VeryVerboseFlag = false;

int main(int argc, char *argv[])
{
    bool FoundVME = false;
    bool FoundDig = false;
    
    
    int EventOffset = 0;
    
    TGraph *gTACRatios = new TGraph();
    gTACRatios->SetName("gTACRatios");
    TGraph *gSkips = new TGraph();
    gSkips->SetName("gSkips");
    int MergedEventsCounter = 0;
    
    if(argc!=4)
    {
        fprintf(stderr, "usage: mcerr <filename for VME DAQ> <filename for digital DAQ> <verbosity setting - 1 is verbose, 2 is very verbose, anything else is false>\n");
        exit(1);
    }
    
    if(atoi(argv[3]) == 1)
    {
        std::cout << "Setting verbose mode on" << std::endl;
        VerboseFlag = true;
    }
    else if(atoi(argv[3]) == 2)
    {
        std::cout << "Setting very verbose mode on" << std::endl;
        VerboseFlag = true;
        VeryVerboseFlag = true;
    }
    
    std::cout << "Run number is set according to the VME file" << std::endl;
    
    std::string RunName = argv[1];
    if(VeryVerboseFlag)std::cout << RunName.substr(6,5) << std::endl;
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
        if(VeryVerboseFlag)fVME->ls();
    }
    
    TTree *tVME = (TTree*)fVME->Get("DATA");
    
    tVME->SetBranchAddress("TAC",&VMETAC);
    TTreeReader ReaderVME("DATA",fVME);
    
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
        if(VeryVerboseFlag)fDig->ls();
    }
    
    TTree *tDig = (TTree*)fDig->Get("DATA");
    tDig->SetBranchAddress("tac_energy",&DigTAC);
//     for(Long64_t i = 0; i<tDig->GetEntries();i++)
//     {
//         tDig->GetEntry(i);
//         std::cout << "DigTAC: " << DigTAC << std::endl;
//     }
//     
    
    //Now creat the output merged file
    TFile *fOut = new TFile(Form("merged%d.root",RunNumber),"RECREATE");
    TTree *trout = (TTree*)tVME->Clone("MergedData");
    
    int DigEventNumber = 0;
    double TACRatio = 0;
    trout->Branch("DigEventNumber",&DigEventNumber,"DigEventNumber/I");
    trout->Branch("TACRatio",&TACRatio,"TACRatio/D");
    
    int nDigitalTreeBranches = tDig->GetNbranches();
    
    
    if(VeryVerboseFlag)trout->Print();//Now print out the information in the combined TTree to check that the branches have the right names and types and sizes
    
    //Now loop over all the entries in the VME DAQ to look for 
    for(Long64_t i=0;i<tVME->GetEntries();i++)
    {
        if(VeryVerboseFlag)std::cout << "Entry: " << i << std::endl;
        
        tVME->GetEntry(i);
        if(VeryVerboseFlag)std::cout << "VMETAC: " << VMETAC << std::endl;
        
        tDig->GetEntry(i + EventOffset);
        if(VeryVerboseFlag)std::cout << "DigTAC: " << DigTAC << std::endl;
        
        TACRatio = TACPar[0] * DigTAC / ((double)VMETAC - TACPar[1]);
        
//         if(VeryVerboseFlag)std::cout << "TACRatio: " << TACRatio << std::endl;
        if(!(TACRatio>TACRatioLimits[0] && TACRatio<TACRatioLimits[1]) && DigTAC>0)
        {
            if(VeryVerboseFlag)std::cout << "TACRatio is bad for VME event number: " << i << "\t Current TACRatio: " << TACRatio << std::endl;
            EventOffset = ReAlignDAQs(i,EventOffset,tVME,tDig);
            tDig->GetEntry(i + EventOffset);
            TACRatio = TACPar[0] * DigTAC / ((double)VMETAC - TACPar[1]);
        }
        
        if(DigTAC>0 && TACRatio>TACRatioLimits[0] && TACRatio<TACRatioLimits[1])
        {
            gTACRatios->SetPoint(MergedEventsCounter,MergedEventsCounter,TACRatio);
            gSkips->SetPoint(MergedEventsCounter,MergedEventsCounter,EventOffset);
            MergedEventsCounter++;
            
            trout->Fill();
        }
    }
    
    if(VerboseFlag)trout->Print();//Print at the end to get some idea if the branches have been filled
    
    gTACRatios->Write();
    gSkips->Write();
    trout->Write();
    
    fVME->Close();
    fDig->Close();
    fOut->Close();
    
    std::cout << "Finished merging files" << std::endl;
    std::cout << std::endl;
    return 0;
}


int ReAlignDAQs(int VMEEventNumber, int EventOffset, TTree* tVME, TTree *tDig)
{
    if(VeryVerboseFlag)std::cout << "Bad TAC ratio - going to try to find the next good digital TAC event" << std::endl;
    
    int result = EventOffset; //Return number of skipped events to get a good correlation again
    
    if(VeryVerboseFlag)std::cout << "Starting with skipping " << result << " events" << std::endl;    
    
    bool MatchEvents = false;
    bool PositiveMove = true;
    int StepSize = 1;
    
    while(abs(result-EventOffset)<EventOffsetLimit && !MatchEvents)
    {
        if(VeryVerboseFlag)std::cout << "EventOffset = " << result << std::endl;
        if(VeryVerboseFlag)std::cout << "This is " << result-EventOffset << " more skips since the last matching event" << std::endl;
        
        tVME->GetEntry(VMEEventNumber);
        tDig->GetEntry(VMEEventNumber+result);
        if(VeryVerboseFlag)std::cout << "Realign - VMETAC: " << VMETAC << std::endl;
        if(VeryVerboseFlag)std::cout << "Realign - DigTAC: " << DigTAC << std::endl;
        
        
        double TACRatio = TACPar[0] * DigTAC / ((double)VMETAC - TACPar[1]);
        
        if(VeryVerboseFlag)std::cout << "Realign - TACRatio: " << TACRatio << std::endl;
        
        if((TACRatio>TACRatioLimits[0] && TACRatio<TACRatioLimits[1]) && DigTAC>0)
        {
            MatchEvents = true;
            if(VeryVerboseFlag)std::cout << "Found GOOD matching event with TACRatio of: " << TACRatio << std::endl;
        } 
        else if(PositiveMove)
        {
            result = result + StepSize;
            PositiveMove = false;
        }
        else if(!PositiveMove)
        {
            result = result - StepSize;
            PositiveMove = true;
        }
        StepSize++;
    }
    
    if(VerboseFlag && abs(result - EventOffset)>=EventOffsetLimit)std::cout << "Could not find matching event within an event offset limit of " << EventOffsetLimit << std::endl;
    
    if(VeryVerboseFlag)std::cout << std::endl;
    
    return result;
}

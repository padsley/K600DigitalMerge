//This code written by Philip Adsley - e-mail padsley@gmail.com with any suggestions, problems, queries or comments
#include "K600DigitalMerge.h"

bool VerboseFlag = false;
bool VeryVerboseFlag = false;

bool *UsedDigitalEvent;

int main(int argc, char *argv[])
{
    bool FoundVME = false;
    bool FoundDig = false;
    
    
    int EventOffset = 0;
    
    TGraph *gTACDifferences = new TGraph();
    gTACDifferences->SetName("gTACDifferences");
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
    
    //     GammaData *gammy;
    //     RawData *roar;
    
    std::cout << std::endl << "******************************************************" << std::endl;
    std::cout << "VME Tree Entries: " << tVME->GetEntries() << std::endl;
    std::cout << "Digital Tree Entries: " << tDig->GetEntries() << std::endl;
    std::cout << "Difference: " << tVME->GetEntries() - tDig->GetEntries() << std::endl;
    std::cout << "******************************************************" << std::endl << std::endl;
    
    UsedDigitalEvent = new bool[tVME->GetEntries()];
    for(int i=0;i<tVME->GetEntries();i++)UsedDigitalEvent[i] = false;
    
    
    //Now creat the output merged file
    TFile *fOut = new TFile(Form("merged%d.root",RunNumber),"RECREATE");
    TTree *trout = (TTree*)tVME->Clone("MergedData");
    
    int DigEventNumber = 0;
    double TACDifference = 0;
    TBranch *t_DigEventNumber = trout->Branch("DigEventNumber",&DigEventNumber,"DigEventNumber/I");
    TBranch *t_TACDifference = trout->Branch("TACDifference",&TACDifference,"TACDifference/D");
    
    
    int nDigitalTreeBranches = tDig->GetNbranches();
    double trig_time = 0;
    double tac_time = 0;
    int trig_scaler = 0;
    int tac_scaler = 0;
    int trig_rate = 0;
    int tac_rate = 0;
    int tac_energy = 0;
    int Evtnum = 0;
    int trig_cnt = 0;
    double Ge_time[48];
    double Ge_rawEnergy[48];
    double Ge_calEnergy[48];
    
    bool CorrelatedDigitalEvent = false;
    
    TBranch *t_Evtnum = trout->Branch("Evtnum",&Evtnum,"Evtnum/I");
    TBranch *t_Ge_time = trout->Branch("Ge_time",&Ge_time,"Ge_time[48]/D");
    TBranch *t_Ge_rawEnergy = trout->Branch("Ge_rawEnergy",&Ge_rawEnergy,"Ge_rawEnergy[48]/D");
    TBranch *t_Ge_calEnergy = trout->Branch("Ge_calEnergy",&Ge_calEnergy,"Ge_calEnergy[48]/D");
    TBranch *t_CorrelatedDigitalEvent = trout->Branch("CorrelatedDigitalEvent",&CorrelatedDigitalEvent,"CorrelatedDigitalEvent/O");
    
    if(VeryVerboseFlag)trout->Print();//Now print out the information in the combined TTree to check that the branches have the right names and types and sizes
    
    //Now loop over all the entries in the VME DAQ to look for 
    for(Long64_t i=0;i<tVME->GetEntries();i++)
    {
        if(VeryVerboseFlag)std::cout << "Entry: " << i << std::endl;
        if(i%10000 == 0)std::cout << "\rEntry: " << i << " of " << tVME->GetEntries() << "      " << "EventOffset: " << EventOffset << std::flush;
        if(i==tVME->GetEntries()-1)std::cout << "\r        Final Event!            " << std::flush;
        
        CorrelatedDigitalEvent = false;
        
        tVME->GetEntry(i);
        if(VeryVerboseFlag)std::cout << "VMETAC: " << VMETAC << std::endl;
        
        tDig->GetEntry(i + EventOffset);
        if(VeryVerboseFlag)std::cout << "DigTAC: " << DigTAC << std::endl;
        
        if(DigTAC>0 && VMETAC>0)
        {
            TACDifference = DigTAC - (TACPar[0] + TACPar[1] * (double)VMETAC);
            
            if(VeryVerboseFlag)std::cout << "TACDifference: " << TACDifference << std::endl;
            if(abs(DigTAC - (TACPar[0] + TACPar[1]*VMETAC))>DifferenceLimit)
            {
                if(VeryVerboseFlag)std::cout << "TACDifference is bad for VME event number: " << i << "\t Current TACDifference: " << TACDifference << std::endl;
                EventOffset = ReAlignDAQs(i,EventOffset,tVME,tDig);
                tDig->GetEntry(i + EventOffset);
                TACDifference = DigTAC - (TACPar[0] + TACPar[1] * (double)VMETAC);
            }
            
            if(DigTAC>0 && abs(DigTAC - (TACPar[0] +TACPar[1]*VMETAC))<DifferenceLimit)
            {
                gTACDifferences->SetPoint(MergedEventsCounter,MergedEventsCounter,TACDifference);
                gSkips->SetPoint(MergedEventsCounter,MergedEventsCounter,EventOffset);
                MergedEventsCounter++;
                
                
                DigEventNumber = i + EventOffset;
                t_DigEventNumber->Fill();
                t_TACDifference->Fill();
                t_Evtnum->Fill();
                t_Ge_time->Fill();
                t_Ge_rawEnergy->Fill();
                t_Ge_calEnergy->Fill();
                CorrelatedDigitalEvent = true;
            }
            
        }
        t_CorrelatedDigitalEvent->Fill();
    }
    
    if(VeryVerboseFlag)trout->Print();//Print at the end to get some idea if the branches have been filled
    
    
    std::cout << "Got to the end of merging the files - now writing some potentially useful graphs" << std::endl;
    gTACDifferences->Write();
    gSkips->Write();
    trout->Write();
    
    fVME->Close();
    fDig->Close();
    fOut->Close();
    
    delete [] UsedDigitalEvent;
    
    std::cout << "Finished" << std::endl;
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
    unsigned int StepSize = 1;
    
    while(abs(result-EventOffset)<EventOffsetLimit && !MatchEvents)
    {
        if(VeryVerboseFlag)std::cout << "result (finding new TAC match): " << result << std::endl;
        
        if(VeryVerboseFlag)std::cout << "EventOffset = " << result << std::endl;
        if(VeryVerboseFlag)std::cout << "This is " << result-EventOffset << " more skips since the last matching event" << std::endl;
        
        tVME->GetEntry(VMEEventNumber);
        tDig->GetEntry(VMEEventNumber + result);
        if(VeryVerboseFlag)std::cout << "Realign - VMETAC: " << VMETAC << std::endl;
        if(VeryVerboseFlag)std::cout << "Realign - DigTAC: " << DigTAC << std::endl;
        
        
        double TACDifference = DigTAC - (TACPar[0] + TACPar[1] * (double)VMETAC);
        
        if(VeryVerboseFlag)std::cout << "Realign - TACDifference: " << TACDifference << std::endl;
        
        if(UsedDigitalEvent[VMEEventNumber + result] && VeryVerboseFlag)std::cout << "Already correlated this digital event!" << std::endl;
        
        if(DigTAC>0 && abs(DigTAC - (TACPar[0] +TACPar[1]*VMETAC))<DifferenceLimit && VMEEventNumber + result < tDig->GetEntries())
        {
            if(!UsedDigitalEvent[VMEEventNumber + result])
            {
                MatchEvents = true;
                UsedDigitalEvent[VMEEventNumber + result] = true;
                if(VeryVerboseFlag)std::cout << "Found GOOD matching event with TACDifference of: " << TACDifference << std::endl;
            } 
        }
        
        if(!MatchEvents && PositiveMove)
        {
            result = result + StepSize;
            PositiveMove = false;
        }
        else if(!MatchEvents && !PositiveMove)
        {
            result = result - StepSize;
            PositiveMove = true;
        }
        
        
        if(VeryVerboseFlag)std::cout << std::endl;
        
        StepSize++;
    }
    
    if(VerboseFlag && abs(result - EventOffset)>=EventOffsetLimit)std::cout << "Could not find matching event within an event offset limit of " << EventOffsetLimit << std::endl;
    
    if(VeryVerboseFlag)std::cout << std::endl;
    
    if(!MatchEvents)
    {
        if(VeryVerboseFlag)std::cout << "Could not find good matching event within the limiting number of jumps going to find a nearby event with a digital TAC value of zero and assume that that's the corresponding event but I'm not going to keep it for the TTree" << std::endl;
        
        PositiveMove = true;
        StepSize = 1;
        
        result = EventOffset;
        
        while(abs(result - EventOffset)<EventOffsetLimit && !MatchEvents)
        {
            if(VeryVerboseFlag)std::cout << "result (finding a zero): " << result << std::endl;
            
            tVME->GetEntry(VMEEventNumber);
            tDig->GetEntry(VMEEventNumber+EventOffset);
            
            if(VeryVerboseFlag)std::cout << "EventOffset = " << result << std::endl;
            if(VeryVerboseFlag)std::cout << "This is " << result-EventOffset << " more skips since the last matching event" << std::endl;
            if(VeryVerboseFlag)std::cout << "Find a zero - DigTAC: " << DigTAC << std::endl;
            if(UsedDigitalEvent[VMEEventNumber + result] && VeryVerboseFlag)std::cout << "Already used this digital event" << std::endl;
            
            if(DigTAC == 0 && VMEEventNumber + result < tDig->GetEntries()) 
            {
                if(!UsedDigitalEvent[VMEEventNumber + result])
                {
                    MatchEvents = true;
                    UsedDigitalEvent[VMEEventNumber + result] = true;
                }
            }
            
            if(!MatchEvents && PositiveMove)
            {
                result = result + StepSize;
                PositiveMove = false;
            }
            else if(!MatchEvents && !PositiveMove)
            {
                result = result - StepSize;
                PositiveMove = true;
            }
            if(VeryVerboseFlag)std::cout << std::endl;
            
            StepSize++;
        }
    }
    
    if(!MatchEvents)result = EventOffset;//Fuckit - go back to the original number of skipped events and try the next VME event
    
    if(VeryVerboseFlag)std::cout << "Now the offset is " << result << " events" << std::endl;
    return result;
}

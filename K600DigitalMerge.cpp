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
    
    TGraph *gTACValues = new TGraph();
    gTACValues->SetName("gTACValues");    
    TGraph *gGoodTACValues = new TGraph();
    gGoodTACValues->SetName("gGoodTACValues");
    TGraph *gAlreadyGoodTACValues = new TGraph();
    gAlreadyGoodTACValues->SetName("gAlreadyGoodTACValues");
    TGraph *gTACDifferences = new TGraph();
    gTACDifferences->SetName("gTACDifferences");
    TGraph *gTACDifferences2 = new TGraph();
    gTACDifferences2->SetName("gTACDifferences2");
    TGraph *gSkips = new TGraph();
    gSkips->SetName("gSkips");
    int MergedEventsCounter = 0;
    
    TH1F *DigitalTACHisto = new TH1F("DigitalTACHisto","DigitalTACHisto",10000,0,10000);
    TH1F *VMETACHisto = new TH1F("VMETACHisto","VMETACHisto",4100,0,4100);
    TH1F *TACDifferenceHisto = new TH1F("TACDifferenceHisto","TACDifferenceHisto",20000,-10000,10000);
    
    if(argc!=5)
    {
        fprintf(stderr, "usage: mcerr <filename for VME DAQ> <filename for digital DAQ> <verbosity setting - 1 is verbose, 2 is very verbose, anything else is false> <limit for number of events to skip for alignment>\n");
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
    
    EventOffsetLimit = atoi(argv[4]);
    std::cout << "Setting the maximum number of events to skip for alignment to " << EventOffsetLimit << std::endl;
    
    std::cout << "Run number is set according to the VME file" << std::endl;
    
    std::string RunName = argv[1];
    std::string TestString ("sorted");
    std::size_t position = RunName.find(TestString);
    
    if(VeryVerboseFlag)std::cout << "RunName.substr(position+6,5): " << RunName.substr(position+6,5) << std::endl;
    int RunNumber = atoi(RunName.substr(position+6,5).c_str());
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
    double DigTrigTime = 0;
    double Ge_time[48];
    double Ge_rawEnergy[48];
    double Ge_calEnergy[48];
    
    
    tDig->SetBranchAddress("tac_energy",&DigTAC);
    tDig->SetBranchAddress("trig_time",&ReadDigTrigTime);
    tDig->SetBranchAddress("Evtnum",&ReadEvtnum);
    tDig->SetBranchAddress("Ge_time",&ReadGe_time);
    tDig->SetBranchAddress("Ge_rawEnergy",&ReadGe_rawEnergy);
    tDig->SetBranchAddress("Ge_calEnergy",&ReadGe_calEnergy);

    
    std::cout << std::endl << "******************************************************" << std::endl;
    std::cout << "VME Tree Entries: " << tVME->GetEntries() << std::endl;
    std::cout << "Digital Tree Entries: " << tDig->GetEntries() << std::endl;
    std::cout << "Difference: " << tVME->GetEntries() - tDig->GetEntries() << std::endl;
    std::cout << "******************************************************" << std::endl << std::endl;
    
    UsedDigitalEvent = new bool[tVME->GetEntries()];
    for(int i=0;i<tVME->GetEntries();i++)UsedDigitalEvent[i] = false;
    
    
    //Now creat the output merged file
    TFile *fOut = new TFile(Form("merged%d.root",RunNumber),"RECREATE");
    fOut->ls();
    fOut->cd();
    TTree *trout = (TTree*)tVME->CloneTree(-1,"fast");
    trout->SetName("MergedData");
    fOut->ls();
    
    int DigEventNumber = 0;
    double WriteDigTAC = 0;
    double TACDifference = 0;
    TBranch *t_DigEventNumber = trout->Branch("DigEventNumber",&DigEventNumber,"DigEventNumber/I");
    TBranch *t_DigTAC = trout->Branch("DigTAC",&WriteDigTAC,"DigTAC/D");
    TBranch *t_TACDifference = trout->Branch("TACDifference",&TACDifference,"TACDifference/D");
    
    bool CorrelatedDigitalEvent = false;
    
    TBranch *t_Evtnum = trout->Branch("Evtnum",&Evtnum,"Evtnum/I");
    TBranch *t_DigTrigTime = trout->Branch("DigTrigTime",&DigTrigTime,"DigTrigTime/D");
    TBranch *t_Ge_time = trout->Branch("Ge_time",&Ge_time,"Ge_time[48]/D");
    TBranch *t_Ge_rawEnergy = trout->Branch("Ge_rawEnergy",&Ge_rawEnergy,"Ge_rawEnergy[48]/D");
    TBranch *t_Ge_calEnergy = trout->Branch("Ge_calEnergy",&Ge_calEnergy,"Ge_calEnergy[48]/D");
    TBranch *t_CorrelatedDigitalEvent = trout->Branch("CorrelatedDigitalEvent",&CorrelatedDigitalEvent,"CorrelatedDigitalEvent/O");
    
    if(VeryVerboseFlag)trout->Print();//Now print out the information in the combined TTree to check that the branches have the right names and types and sizes
    
    //Now loop over all the entries in the VME DAQ to look for 
//     int TACRawCounter = 0, TACGoodCounter = 0;
    for(Long64_t i=0;i<tVME->GetEntries();i++)
    {
        if(VeryVerboseFlag)std::cout << "Entry: " << i << std::endl;
        if(i%10000 == 0)std::cout << "\rEntry: " << i << " of " << tVME->GetEntries() << "      " << "EventOffset: " << EventOffset << std::flush;
        if(i==tVME->GetEntries()-1)std::cout << "\r        Final Event!            " << std::flush;
        
        CorrelatedDigitalEvent = false;
        
        int VMEEntryReturn = -2, DigEntryReturn = -2;
        
        VMEEntryReturn = tVME->GetEntry(i);
        if(VeryVerboseFlag)std::cout << "VMETAC: " << VMETAC << std::endl;
        
        DigEntryReturn = tDig->GetEntry(i + EventOffset);
        if(VeryVerboseFlag)std::cout << "DigTAC: " << DigTAC << std::endl;
        
        if(VerboseFlag && VMEEntryReturn==0)std::cout << "VME entry does not exist" << std::endl;
        if(VerboseFlag && VMEEntryReturn==-1)std::cout << "VME entry I/O error" << std::endl;
        
        if(VerboseFlag && DigEntryReturn==0)std::cout << "Digital entry does not exist" << std::endl;
        if(VerboseFlag && DigEntryReturn==-1)std::cout << "Digital entry I/O error" << std::endl;
        
        if(DigTAC>0 && VMETAC>0 && VMEEntryReturn>0 && DigEntryReturn>0)
        {
            gTACValues->SetPoint(gTACValues->GetN(),VMETAC,DigTAC);
//             TACRawCounter++;
                                 
            TACDifference = DigTAC - (TACPar[0] + TACPar[1] * (double)VMETAC);
            
            if(VeryVerboseFlag)std::cout << "TACDifference: " << TACDifference << std::endl;
            if(abs(DigTAC - (TACPar[0] + TACPar[1]*VMETAC))>DifferenceLimit)
            {
                if(VeryVerboseFlag)std::cout << "TACDifference is bad for VME event number: " << i << "\t Current TACDifference: " << TACDifference << std::endl;
                EventOffset = ReAlignDAQs(i,EventOffset,tVME,tDig);
                tDig->GetEntry(i + EventOffset);
                TACDifference = DigTAC - (TACPar[0] + TACPar[1] * (double)VMETAC);
            }
            else
            {
                if(VeryVerboseFlag)std::cout << "Good TACDifference for this event already" << std::endl;
                gAlreadyGoodTACValues->SetPoint(gAlreadyGoodTACValues->GetN(),VMETAC,DigTAC);
            }
            
            if(abs(DigTAC - (TACPar[0] + TACPar[1]*(double)VMETAC))<DifferenceLimit)
            {
                gGoodTACValues->SetPoint(gGoodTACValues->GetN(),VMETAC,DigTAC);
                if(VeryVerboseFlag)std::cout << "Successful correlation - filling relevant branches" << std::endl;
                gTACDifferences->SetPoint(MergedEventsCounter,MergedEventsCounter,TACDifference);
                gTACDifferences2->SetPoint(gTACDifferences2->GetN(),VMETAC,TACDifference);
                gSkips->SetPoint(MergedEventsCounter,MergedEventsCounter,EventOffset);
                MergedEventsCounter++;
                
                DigTrigTime = ReadDigTrigTime;
                if(VeryVerboseFlag)std::cout << "ReadDigTrigTime = " << ReadDigTrigTime << "\t DigTrigTime = " << DigTrigTime << std::endl; 
                
                Evtnum = ReadEvtnum;
                WriteDigTAC = DigTAC;
                
                DigitalTACHisto->Fill(WriteDigTAC);
                VMETACHisto->Fill(VMETAC);
                
                TACDifferenceHisto->Fill(TACDifference);
                
                for(int p=0;p<48;p++)
                {
                    Ge_time[p] = ReadGe_time[p];
                    Ge_rawEnergy[p] = ReadGe_rawEnergy[p];
                    Ge_calEnergy[p] = ReadGe_calEnergy[p];
                }
                
                DigEventNumber = i + EventOffset;
                CorrelatedDigitalEvent = true;
                t_DigTrigTime->Fill();
                t_DigEventNumber->Fill();
                t_TACDifference->Fill();
                t_Evtnum->Fill();
                t_Ge_time->Fill();
                t_Ge_rawEnergy->Fill();
                t_Ge_calEnergy->Fill();
                t_DigTAC->Fill();
                t_CorrelatedDigitalEvent->Fill();
            }
            else
            {
                if(VeryVerboseFlag)std::cout << "Could not find correlated digital DAQ event for this VME DAQ event" << std::endl;
                
                for(int p=0;p<48;p++)
                {
                    Ge_time[p] =  -1;
                    Ge_rawEnergy[p] = -1;
                    Ge_calEnergy[p] = -1;
                }
                Evtnum = -1;
                CorrelatedDigitalEvent = false;
                DigEventNumber = i + EventOffset;
                DigTrigTime = -1;
                t_DigTrigTime->Fill();
                t_DigEventNumber->Fill();
                t_TACDifference->Fill();
                t_Evtnum->Fill();
                t_Ge_time->Fill();
                t_Ge_rawEnergy->Fill();
                t_Ge_calEnergy->Fill();
                t_DigTAC->Fill();
                t_CorrelatedDigitalEvent->Fill();
            }
            
        }
        else if(DigTAC==0 && VMETAC>0)
        {
            if(VeryVerboseFlag)std::cout << "Have to deal with event which does not have a DigTAC value - going to throw some null results into the TTree" << std::endl;
            for(int p=0;p<48;p++)
                {
                    Ge_time[p] =  -1;
                    Ge_rawEnergy[p] = -1;
                    Ge_calEnergy[p] = -1;
                }
                Evtnum = -1;
                CorrelatedDigitalEvent = false;
                DigTrigTime = -1;
                DigEventNumber = i + EventOffset;
                t_DigEventNumber->Fill();
                t_DigTrigTime->Fill();
                t_TACDifference->Fill();
                t_Evtnum->Fill();
                t_Ge_time->Fill();
                t_Ge_rawEnergy->Fill();
                t_Ge_calEnergy->Fill();
                t_DigTAC->Fill();
                t_CorrelatedDigitalEvent->Fill();
        }
            
            
//         t_CorrelatedDigitalEvent->Fill();
    }
    
    if(VeryVerboseFlag)trout->Print();//Print at the end to get some idea if the branches have been filled
    
    
    std::cout << "Got to the end of merging the files - now writing some potentially useful graphs" << std::endl;
    std::cout << "Writing the merged data tree" << std::endl;
    trout->Write();
    gTACValues->Write();
    gGoodTACValues->Write();
    gAlreadyGoodTACValues->Write();
    gTACDifferences->Write();
    gTACDifferences2->Write();
    gSkips->Write();
    DigitalTACHisto->Write();
    VMETACHisto->Write();
    TACDifferenceHisto->Write();
    
    delete gTACValues;
    delete gGoodTACValues;
    delete gAlreadyGoodTACValues;
    delete gTACDifferences;
    delete gTACDifferences2;
    delete gSkips;
    delete DigitalTACHisto;
    delete VMETACHisto;
    delete TACDifferenceHisto;
    
    std::cout << "Closing the files" << std::endl;
//     fOut->ls();
    fOut->Close();
    std::cout << "Closing the files" << std::endl;
    fVME->cd();
//     fVME->ls();
//     delete tVME;
    fVME->Close();
    std::cout << "Closing the files" << std::endl;
//     delete tDig;
    fDig->Close();
    
    std::cout << "Finished writing all of the data" << std::endl;
//     delete [] UsedDigitalEvent;
    
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

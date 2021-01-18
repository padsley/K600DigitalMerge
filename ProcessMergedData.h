//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 18 10:53:25 2021 by ROOT version 6.23/01
// from TTree MergedData/K600 data
// found on file: merged272.root
//////////////////////////////////////////////////////////

#ifndef ProcessMergedData_h
#define ProcessMergedData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ProcessMergedData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           runtime;
   Int_t           evtcounter;
   Int_t           tdcsperevent;
   Int_t           triggerI;
   Int_t           triggerU;
   Int_t           CIU;
   Int_t           CII;
   Int_t           tof;
   Int_t           toftdc1;
   Int_t           toftdc2;
   Int_t           toftdc3;
   Int_t           toftdc4;
   Int_t           toftdc5;
   Int_t           toftdc6;
   Int_t           toftdc7;
   Int_t           k600;
   Double_t        pad1;
   Double_t        pad2;
   Double_t        pad1hiP;
   Double_t        pad1lowP;
   Double_t        pad2hiP;
   Double_t        pad2lowP;
   Double_t        pad1hiPT;
   Double_t        pad1lowPT;
   Double_t        pad2hiPT;
   Double_t        pad2lowPT;
   Double_t        X1pos;
   Double_t        X1th;
   Int_t           X1flag;
   Double_t        X1Rsq;
   Double_t        X1res0;
   Double_t        X1res1;
   Int_t           X1hits;
   Double_t        X1effID;
   Double_t        X1effall;
   Double_t        X1effdt;
   Double_t        X1effgroup;
   Double_t        X1effgood;
   Int_t           nX1wiresUsed;
   Int_t           X1doublewires;
   Int_t           X1multiplemin;
   Double_t        X1TimeDiff;
   Int_t           X1wireUsed[8];   //[t_nX1wiresUsed]
   Double_t        X1distUsed[8];   //[t_nX1wiresUsed]
   Double_t        U1pos;
   Double_t        U1th;
   Int_t           U1flag;
   Double_t        U1Rsq;
   Double_t        U1res0;
   Double_t        U1res1;
   Double_t        U1effID;
   Int_t           U1hits;
   Double_t        U1effall;
   Double_t        U1effdt;
   Double_t        U1effgroup;
   Double_t        U1effgood;
   Int_t           nU1wiresUsed;
   Int_t           U1doublewires;
   Int_t           U1multiplemin;
   Int_t           U1wireUsed[6];   //[t_nU1wiresUsed]
   Double_t        X2pos;
   Double_t        X2th;
   Int_t           X2flag;
   Double_t        X2Rsq;
   Double_t        X2res0;
   Double_t        X2res1;
   Double_t        X2effID;
   Int_t           X2hits;
   Double_t        X2effall;
   Double_t        X2effdt;
   Double_t        X2effgroup;
   Double_t        X2effgood;
   Int_t           nX2wiresUsed;
   Int_t           X2doublewires;
   Int_t           X2multiplemin;
   Int_t           X2wireUsed[1];   //[t_nX2wiresUsed]
   Double_t        U2pos;
   Double_t        U2th;
   Int_t           U2flag;
   Double_t        U2Rsq;
   Double_t        U2res0;
   Double_t        U2res1;
   Double_t        U2effID;
   Int_t           U2hits;
   Double_t        U2effall;
   Double_t        U2effdt;
   Double_t        U2effgroup;
   Double_t        U2effgood;
   Int_t           nU2wiresUsed;
   Int_t           U2doublewires;
   Int_t           U2multiplemin;
   Int_t           U2wireUsed[1];   //[t_nU2wiresUsed]
   Double_t        thetaFP;
   Double_t        thetaFPx;
   Double_t        phiFP;
   Double_t        Y1;
   Double_t        Y2;
   Int_t           pulser;
   Double_t        X1posC;
   Double_t        X1posO;
   Double_t        Ex;
   Double_t        ExC;
   Double_t        T3;
   Double_t        rigidity3;
   Double_t        theta;
   Double_t        thetaSCAT;
   Double_t        phiSCAT;
 //RawData         *RawInfo;
   vector<int>     ADCValues;
   vector<int>     ADCChannels;
   vector<double>  ADCCalibratedValues;
   vector<int>     QDCValues;
   vector<int>     TDCChannels;
   vector<int>     TDCValues;
   Int_t           TAC;
   Int_t           ADCQDCcheck;
   Int_t           DigEventNumber;
   Double_t        DigTAC;
   Double_t        TACDifference;
   Int_t           Evtnum;
   Double_t        DigTrigTime;
   Double_t        Ge_time[48];
   Double_t        Ge_rawEnergy[48];
   Double_t        Ge_calEnergy[48];
   Bool_t          CorrelatedDigitalEvent;

   // List of branches
   TBranch        *b_t_runtime;   //!
   TBranch        *b_t_evtcounter;   //!
   TBranch        *b_t_tdcsperevent;   //!
   TBranch        *b_t_triggerI;   //!
   TBranch        *b_t_triggerU;   //!
   TBranch        *b_t_CIU;   //!
   TBranch        *b_t_CII;   //!
   TBranch        *b_t_tof;   //!
   TBranch        *b_t_toftdc1;   //!
   TBranch        *b_t_toftdc2;   //!
   TBranch        *b_t_toftdc3;   //!
   TBranch        *b_t_toftdc4;   //!
   TBranch        *b_t_toftdc5;   //!
   TBranch        *b_t_toftdc6;   //!
   TBranch        *b_t_toftdc7;   //!
   TBranch        *b_t_k600;   //!
   TBranch        *b_t_pad1;   //!
   TBranch        *b_t_pad2;   //!
   TBranch        *b_t_pad1hiP;   //!
   TBranch        *b_t_pad1lowP;   //!
   TBranch        *b_t_pad2hiP;   //!
   TBranch        *b_t_pad2lowP;   //!
   TBranch        *b_t_pad1hiPT;   //!
   TBranch        *b_t_pad1lowPT;   //!
   TBranch        *b_t_pad2hiPT;   //!
   TBranch        *b_t_pad2lowPT;   //!
   TBranch        *b_t_X1pos;   //!
   TBranch        *b_t_X1th;   //!
   TBranch        *b_t_X1flag;   //!
   TBranch        *b_t_X1Rsq;   //!
   TBranch        *b_t_X1res0;   //!
   TBranch        *b_t_X1res1;   //!
   TBranch        *b_t_X1hits;   //!
   TBranch        *b_t_X1effID;   //!
   TBranch        *b_t_X1effall;   //!
   TBranch        *b_t_X1effdt;   //!
   TBranch        *b_t_X1effgroup;   //!
   TBranch        *b_t_X1effgood;   //!
   TBranch        *b_t_nX1wiresUsed;   //!
   TBranch        *b_t_X1doublewires;   //!
   TBranch        *b_t_X1multiplemin;   //!
   TBranch        *b_t_X1TimeDiff;   //!
   TBranch        *b_X1wireUsed;   //!
   TBranch        *b_X1distUsed;   //!
   TBranch        *b_t_U1pos;   //!
   TBranch        *b_t_U1th;   //!
   TBranch        *b_t_U1flag;   //!
   TBranch        *b_t_U1Rsq;   //!
   TBranch        *b_t_U1res0;   //!
   TBranch        *b_t_U1res1;   //!
   TBranch        *b_t_U1effID;   //!
   TBranch        *b_t_U1hits;   //!
   TBranch        *b_t_U1effall;   //!
   TBranch        *b_t_U1effdt;   //!
   TBranch        *b_t_U1effgroup;   //!
   TBranch        *b_t_U1effgood;   //!
   TBranch        *b_t_nU1wiresUsed;   //!
   TBranch        *b_t_U1doublewires;   //!
   TBranch        *b_t_U1multiplemin;   //!
   TBranch        *b_U1wireUsed;   //!
   TBranch        *b_t_X2pos;   //!
   TBranch        *b_t_X2th;   //!
   TBranch        *b_t_X2flag;   //!
   TBranch        *b_t_X2Rsq;   //!
   TBranch        *b_t_X2res0;   //!
   TBranch        *b_t_X2res1;   //!
   TBranch        *b_t_X2effID;   //!
   TBranch        *b_t_X2hits;   //!
   TBranch        *b_t_X2effall;   //!
   TBranch        *b_t_X2effdt;   //!
   TBranch        *b_t_X2effgroup;   //!
   TBranch        *b_t_X2effgood;   //!
   TBranch        *b_t_nX2wiresUsed;   //!
   TBranch        *b_t_X2doublewires;   //!
   TBranch        *b_t_X2multiplemin;   //!
   TBranch        *b_X2wireUsed;   //!
   TBranch        *b_t_U2pos;   //!
   TBranch        *b_t_U2th;   //!
   TBranch        *b_t_U2flag;   //!
   TBranch        *b_t_U2Rsq;   //!
   TBranch        *b_t_U2res0;   //!
   TBranch        *b_t_U2res1;   //!
   TBranch        *b_t_U2effID;   //!
   TBranch        *b_t_U2hits;   //!
   TBranch        *b_t_U2effall;   //!
   TBranch        *b_t_U2effdt;   //!
   TBranch        *b_t_U2effgroup;   //!
   TBranch        *b_t_U2effgood;   //!
   TBranch        *b_t_nU2wiresUsed;   //!
   TBranch        *b_t_U2doublewires;   //!
   TBranch        *b_t_U2multiplemin;   //!
   TBranch        *b_U2wireUsed;   //!
   TBranch        *b_t_thetaFP;   //!
   TBranch        *b_t_thetaFPx;   //!
   TBranch        *b_t_phiFP;   //!
   TBranch        *b_t_Y1;   //!
   TBranch        *b_t_Y2;   //!
   TBranch        *b_t_pulser;   //!
   TBranch        *b_t_X1posC;   //!
   TBranch        *b_t_X1posO;   //!
   TBranch        *b_t_Ex;   //!
   TBranch        *b_t_ExC;   //!
   TBranch        *b_t_T3;   //!
   TBranch        *b_t_rigidity3;   //!
   TBranch        *b_t_theta;   //!
   TBranch        *b_t_thetaSCAT;   //!
   TBranch        *b_t_phiSCAT;   //!
   TBranch        *b_RawInfo_ADCValues;   //!
   TBranch        *b_RawInfo_ADCChannels;   //!
   TBranch        *b_RawInfo_ADCCalibratedValues;   //!
   TBranch        *b_RawInfo_QDCValues;   //!
   TBranch        *b_RawInfo_TDCChannels;   //!
   TBranch        *b_RawInfo_TDCValues;   //!
   TBranch        *b_t_TAC;   //!
   TBranch        *b_t_ADCQDCCheck;   //!
   TBranch        *b_DigEventNumber;   //!
   TBranch        *b_DigTAC;   //!
   TBranch        *b_TACDifference;   //!
   TBranch        *b_Evtnum;   //!
   TBranch        *b_DigTrigTime;   //!
   TBranch        *b_Ge_time;   //!
   TBranch        *b_Ge_rawEnergy;   //!
   TBranch        *b_Ge_calEnergy;   //!
   TBranch        *b_CorrelatedDigitalEvent;   //!

   ProcessMergedData(TTree *tree=0);
   virtual ~ProcessMergedData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ProcessMergedData_cxx
ProcessMergedData::ProcessMergedData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("merged272.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("merged272.root");
      }
      f->GetObject("MergedData",tree);

   }
   Init(tree);
}

ProcessMergedData::~ProcessMergedData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ProcessMergedData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ProcessMergedData::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ProcessMergedData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runtime", &runtime, &b_t_runtime);
   fChain->SetBranchAddress("evtcounter", &evtcounter, &b_t_evtcounter);
   fChain->SetBranchAddress("tdcsperevent", &tdcsperevent, &b_t_tdcsperevent);
   fChain->SetBranchAddress("triggerI", &triggerI, &b_t_triggerI);
   fChain->SetBranchAddress("triggerU", &triggerU, &b_t_triggerU);
   fChain->SetBranchAddress("CIU", &CIU, &b_t_CIU);
   fChain->SetBranchAddress("CII", &CII, &b_t_CII);
   fChain->SetBranchAddress("tof", &tof, &b_t_tof);
   fChain->SetBranchAddress("toftdc1", &toftdc1, &b_t_toftdc1);
   fChain->SetBranchAddress("toftdc2", &toftdc2, &b_t_toftdc2);
   fChain->SetBranchAddress("toftdc3", &toftdc3, &b_t_toftdc3);
   fChain->SetBranchAddress("toftdc4", &toftdc4, &b_t_toftdc4);
   fChain->SetBranchAddress("toftdc5", &toftdc5, &b_t_toftdc5);
   fChain->SetBranchAddress("toftdc6", &toftdc6, &b_t_toftdc6);
   fChain->SetBranchAddress("toftdc7", &toftdc7, &b_t_toftdc7);
   fChain->SetBranchAddress("k600", &k600, &b_t_k600);
   fChain->SetBranchAddress("pad1", &pad1, &b_t_pad1);
   fChain->SetBranchAddress("pad2", &pad2, &b_t_pad2);
   fChain->SetBranchAddress("pad1hiP", &pad1hiP, &b_t_pad1hiP);
   fChain->SetBranchAddress("pad1lowP", &pad1lowP, &b_t_pad1lowP);
   fChain->SetBranchAddress("pad2hiP", &pad2hiP, &b_t_pad2hiP);
   fChain->SetBranchAddress("pad2lowP", &pad2lowP, &b_t_pad2lowP);
   fChain->SetBranchAddress("pad1hiPT", &pad1hiPT, &b_t_pad1hiPT);
   fChain->SetBranchAddress("pad1lowPT", &pad1lowPT, &b_t_pad1lowPT);
   fChain->SetBranchAddress("pad2hiPT", &pad2hiPT, &b_t_pad2hiPT);
   fChain->SetBranchAddress("pad2lowPT", &pad2lowPT, &b_t_pad2lowPT);
   fChain->SetBranchAddress("X1pos", &X1pos, &b_t_X1pos);
   fChain->SetBranchAddress("X1th", &X1th, &b_t_X1th);
   fChain->SetBranchAddress("X1flag", &X1flag, &b_t_X1flag);
   fChain->SetBranchAddress("X1Rsq", &X1Rsq, &b_t_X1Rsq);
   fChain->SetBranchAddress("X1res0", &X1res0, &b_t_X1res0);
   fChain->SetBranchAddress("X1res1", &X1res1, &b_t_X1res1);
   fChain->SetBranchAddress("X1hits", &X1hits, &b_t_X1hits);
   fChain->SetBranchAddress("X1effID", &X1effID, &b_t_X1effID);
   fChain->SetBranchAddress("X1effall", &X1effall, &b_t_X1effall);
   fChain->SetBranchAddress("X1effdt", &X1effdt, &b_t_X1effdt);
   fChain->SetBranchAddress("X1effgroup", &X1effgroup, &b_t_X1effgroup);
   fChain->SetBranchAddress("X1effgood", &X1effgood, &b_t_X1effgood);
   fChain->SetBranchAddress("nX1wiresUsed", &nX1wiresUsed, &b_t_nX1wiresUsed);
   fChain->SetBranchAddress("X1doublewires", &X1doublewires, &b_t_X1doublewires);
   fChain->SetBranchAddress("X1multiplemin", &X1multiplemin, &b_t_X1multiplemin);
   fChain->SetBranchAddress("X1TimeDiff", &X1TimeDiff, &b_t_X1TimeDiff);
   fChain->SetBranchAddress("X1wireUsed", X1wireUsed, &b_X1wireUsed);
   fChain->SetBranchAddress("X1distUsed", X1distUsed, &b_X1distUsed);
   fChain->SetBranchAddress("U1pos", &U1pos, &b_t_U1pos);
   fChain->SetBranchAddress("U1th", &U1th, &b_t_U1th);
   fChain->SetBranchAddress("U1flag", &U1flag, &b_t_U1flag);
   fChain->SetBranchAddress("U1Rsq", &U1Rsq, &b_t_U1Rsq);
   fChain->SetBranchAddress("U1res0", &U1res0, &b_t_U1res0);
   fChain->SetBranchAddress("U1res1", &U1res1, &b_t_U1res1);
   fChain->SetBranchAddress("U1effID", &U1effID, &b_t_U1effID);
   fChain->SetBranchAddress("U1hits", &U1hits, &b_t_U1hits);
   fChain->SetBranchAddress("U1effall", &U1effall, &b_t_U1effall);
   fChain->SetBranchAddress("U1effdt", &U1effdt, &b_t_U1effdt);
   fChain->SetBranchAddress("U1effgroup", &U1effgroup, &b_t_U1effgroup);
   fChain->SetBranchAddress("U1effgood", &U1effgood, &b_t_U1effgood);
   fChain->SetBranchAddress("nU1wiresUsed", &nU1wiresUsed, &b_t_nU1wiresUsed);
   fChain->SetBranchAddress("U1doublewires", &U1doublewires, &b_t_U1doublewires);
   fChain->SetBranchAddress("U1multiplemin", &U1multiplemin, &b_t_U1multiplemin);
   fChain->SetBranchAddress("U1wireUsed", U1wireUsed, &b_U1wireUsed);
   fChain->SetBranchAddress("X2pos", &X2pos, &b_t_X2pos);
   fChain->SetBranchAddress("X2th", &X2th, &b_t_X2th);
   fChain->SetBranchAddress("X2flag", &X2flag, &b_t_X2flag);
   fChain->SetBranchAddress("X2Rsq", &X2Rsq, &b_t_X2Rsq);
   fChain->SetBranchAddress("X2res0", &X2res0, &b_t_X2res0);
   fChain->SetBranchAddress("X2res1", &X2res1, &b_t_X2res1);
   fChain->SetBranchAddress("X2effID", &X2effID, &b_t_X2effID);
   fChain->SetBranchAddress("X2hits", &X2hits, &b_t_X2hits);
   fChain->SetBranchAddress("X2effall", &X2effall, &b_t_X2effall);
   fChain->SetBranchAddress("X2effdt", &X2effdt, &b_t_X2effdt);
   fChain->SetBranchAddress("X2effgroup", &X2effgroup, &b_t_X2effgroup);
   fChain->SetBranchAddress("X2effgood", &X2effgood, &b_t_X2effgood);
   fChain->SetBranchAddress("nX2wiresUsed", &nX2wiresUsed, &b_t_nX2wiresUsed);
   fChain->SetBranchAddress("X2doublewires", &X2doublewires, &b_t_X2doublewires);
   fChain->SetBranchAddress("X2multiplemin", &X2multiplemin, &b_t_X2multiplemin);
   fChain->SetBranchAddress("X2wireUsed", &X2wireUsed, &b_X2wireUsed);
   fChain->SetBranchAddress("U2pos", &U2pos, &b_t_U2pos);
   fChain->SetBranchAddress("U2th", &U2th, &b_t_U2th);
   fChain->SetBranchAddress("U2flag", &U2flag, &b_t_U2flag);
   fChain->SetBranchAddress("U2Rsq", &U2Rsq, &b_t_U2Rsq);
   fChain->SetBranchAddress("U2res0", &U2res0, &b_t_U2res0);
   fChain->SetBranchAddress("U2res1", &U2res1, &b_t_U2res1);
   fChain->SetBranchAddress("U2effID", &U2effID, &b_t_U2effID);
   fChain->SetBranchAddress("U2hits", &U2hits, &b_t_U2hits);
   fChain->SetBranchAddress("U2effall", &U2effall, &b_t_U2effall);
   fChain->SetBranchAddress("U2effdt", &U2effdt, &b_t_U2effdt);
   fChain->SetBranchAddress("U2effgroup", &U2effgroup, &b_t_U2effgroup);
   fChain->SetBranchAddress("U2effgood", &U2effgood, &b_t_U2effgood);
   fChain->SetBranchAddress("nU2wiresUsed", &nU2wiresUsed, &b_t_nU2wiresUsed);
   fChain->SetBranchAddress("U2doublewires", &U2doublewires, &b_t_U2doublewires);
   fChain->SetBranchAddress("U2multiplemin", &U2multiplemin, &b_t_U2multiplemin);
   fChain->SetBranchAddress("U2wireUsed", &U2wireUsed, &b_U2wireUsed);
   fChain->SetBranchAddress("thetaFP", &thetaFP, &b_t_thetaFP);
   fChain->SetBranchAddress("thetaFPx", &thetaFPx, &b_t_thetaFPx);
   fChain->SetBranchAddress("phiFP", &phiFP, &b_t_phiFP);
   fChain->SetBranchAddress("Y1", &Y1, &b_t_Y1);
   fChain->SetBranchAddress("Y2", &Y2, &b_t_Y2);
   fChain->SetBranchAddress("pulser", &pulser, &b_t_pulser);
   fChain->SetBranchAddress("X1posC", &X1posC, &b_t_X1posC);
   fChain->SetBranchAddress("X1posO", &X1posO, &b_t_X1posO);
   fChain->SetBranchAddress("Ex", &Ex, &b_t_Ex);
   fChain->SetBranchAddress("ExC", &ExC, &b_t_ExC);
   fChain->SetBranchAddress("T3", &T3, &b_t_T3);
   fChain->SetBranchAddress("rigidity3", &rigidity3, &b_t_rigidity3);
   fChain->SetBranchAddress("theta", &theta, &b_t_theta);
   fChain->SetBranchAddress("thetaSCAT", &thetaSCAT, &b_t_thetaSCAT);
   fChain->SetBranchAddress("phiSCAT", &phiSCAT, &b_t_phiSCAT);
   fChain->SetBranchAddress("ADCValues", &ADCValues, &b_RawInfo_ADCValues);
   fChain->SetBranchAddress("ADCChannels", &ADCChannels, &b_RawInfo_ADCChannels);
   fChain->SetBranchAddress("ADCCalibratedValues", &ADCCalibratedValues, &b_RawInfo_ADCCalibratedValues);
   fChain->SetBranchAddress("QDCValues", &QDCValues, &b_RawInfo_QDCValues);
   fChain->SetBranchAddress("TDCChannels", &TDCChannels, &b_RawInfo_TDCChannels);
   fChain->SetBranchAddress("TDCValues", &TDCValues, &b_RawInfo_TDCValues);
   fChain->SetBranchAddress("TAC", &TAC, &b_t_TAC);
   fChain->SetBranchAddress("ADCQDCcheck", &ADCQDCcheck, &b_t_ADCQDCCheck);
   fChain->SetBranchAddress("DigEventNumber", &DigEventNumber, &b_DigEventNumber);
   fChain->SetBranchAddress("DigTAC", &DigTAC, &b_DigTAC);
   fChain->SetBranchAddress("TACDifference", &TACDifference, &b_TACDifference);
   fChain->SetBranchAddress("Evtnum", &Evtnum, &b_Evtnum);
   fChain->SetBranchAddress("DigTrigTime", &DigTrigTime, &b_DigTrigTime);
   fChain->SetBranchAddress("Ge_time", Ge_time, &b_Ge_time);
   fChain->SetBranchAddress("Ge_rawEnergy", Ge_rawEnergy, &b_Ge_rawEnergy);
   fChain->SetBranchAddress("Ge_calEnergy", Ge_calEnergy, &b_Ge_calEnergy);
   fChain->SetBranchAddress("CorrelatedDigitalEvent", &CorrelatedDigitalEvent, &b_CorrelatedDigitalEvent);
   Notify();
}

Bool_t ProcessMergedData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ProcessMergedData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ProcessMergedData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ProcessMergedData_cxx

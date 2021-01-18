#define ProcessMergedData_cxx
#include "ProcessMergedData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ProcessMergedData::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ProcessMergedData.C
//      root> ProcessMergedData t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile *fout = new TFile("ProcessedOutput.root","RECREATE");
   
   //PA - Make histograms here (or can make a TTree to store the output if desired
   TH2F *hPosEgamma = new TH2F("hPosEgamma","Position vs E_{#gamma}",800,0,800,10000,0,100000);
   hPosEgamma->SetStats(0);
   TH2F *hPosEgamma_TimeGate = new TH2F("hPosEgamma_TimeGate","Position vs E_{#gamma}",800,0,800,10000,0,100000);
   hPosEgamma_TimeGate->SetStats(0);
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(jentry % 100000 ==0)printf("%f %% complete\n",100*(double)jentry/(double)nentries);
      
      // if (Cut(ientry) < 0) continue;
      for(int n=0;n<48;n++)
      {
        hPosEgamma->Fill(X1pos,Ge_calEnergy[n]);
        if(Ge_time[n]>0 && (DigTrigTime - Ge_time[n]) > -0.8 && (DigTrigTime - Ge_time[n]) < -0.2)hPosEgamma_TimeGate->Fill(X1pos,Ge_calEnergy[n]);
      }
      
   }
   

   TCanvas *c1 = new TCanvas("c1","c1",800,800);
   hPosEgamma->Draw("col");
   
   TCanvas *c2 = new TCanvas("c2","c2",800,800);
   hPosEgamma_TimeGate->Draw("col");
}

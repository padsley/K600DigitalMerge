#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TBranch.h>
#include <TLeaf.h>
#include <TGraph.h>

double TACPar[2] = {0.08,200};

double TACRatioLimits[3] = {0.02,1,1.4};

int ReAlignDAQs(int MidasEventNumber, int DigitalEventSkip, TTree* MidasTree, TTree *DigitalTree);
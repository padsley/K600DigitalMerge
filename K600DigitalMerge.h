#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TBranch.h>
#include <TLeaf.h>
#include <TGraph.h>
#include <TTreeReader.h>
#include <TSystem.h>
#include <TH1.h>
// #include "GammaData.h"
// #include "RawData.h"

double TACPar[2] = {-2519.02,13.3022};

double DifferenceLimit = 100;

int ReAlignDAQs(int VMEEventNumber, int EventOffset, TTree* VMETree, TTree *DigitalTree);

int EventOffsetLimit = 5;

int VMETAC = 0;
double DigTAC = 0;
int ReadEvtnum = 0;

double ReadGe_time[48], ReadGe_rawEnergy[48], ReadGe_calEnergy[48];


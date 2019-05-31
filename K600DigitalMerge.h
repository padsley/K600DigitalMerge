#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TBranch.h>
#include <TLeaf.h>
#include <TGraph.h>
#include <TTreeReader.h>
#include "GammaData.h"
#include "RawData.h"

double TACPar[2] = {0.08,200};

double TACRatioLimits[3] = {0.8,1.4,1.4};

int ReAlignDAQs(int VMEEventNumber, int EventOffset, TTree* VMETree, TTree *DigitalTree);

int EventOffsetLimit = 5;

int VMETAC = 0;
double DigTAC = 0;
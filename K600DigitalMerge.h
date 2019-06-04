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
#include "GammaData.h"
#include "RawData.h"

double TACPar[2] = {-2519.02,13.3022};

double LimitValue = 0.1;

double TACRatioLimits[2] = {1.0-LimitValue,1.0+LimitValue};

int ReAlignDAQs(int VMEEventNumber, int EventOffset, TTree* VMETree, TTree *DigitalTree);

int EventOffsetLimit = 5;

int VMETAC = 0;
double DigTAC = 0;
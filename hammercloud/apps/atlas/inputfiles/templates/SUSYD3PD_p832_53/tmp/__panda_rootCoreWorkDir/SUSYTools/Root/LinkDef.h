#ifndef SUSYTOOLS_LINKDEF_H
#define SUSYTOOLS_LINKDEF_H

#include <vector>
#include <map>
#include <utility>
#include "SUSYTools/SUSYObjDef.h" 
#include "SUSYTools/MuonTriggerSFTool.h"
#include "SUSYTools/BTagCalib.h"
#include "SUSYTools/FakeMetEstimator.h"
#include "SUSYTools/TJVFReweighting.h"
#include "SUSYTools/SUSYCrossSection.h"
#include "SUSYTools/ScaleVariatioReweighter.hpp"
//#include "SUSYTools/Reco_dpd2.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

#pragma link C++ namespace SUSY;
#pragma link C++ namespace JetID;
#pragma link C++ namespace JetErr;
#pragma link C++ namespace BTagCalib;
#pragma link C++ namespace ScaleVariatioReweighter;

#pragma link C++ class SUSYObjDef+;
//#pragma link C++ class Reco_dpd2+;
//#pragma link C++ class Reco2Lep+;
#pragma link C++ class EmulFakeMet+;
#pragma link C++ class FakeMetEstimator+;
#pragma link C++ class MuonTriggerSFTool+;
#pragma link C++ class SUSY::TJVFReweighting+;
#pragma link C++ class SUSY::CrossSectionDB+;
#pragma link C++ class SUSY::CrossSectionDB::Process+;

#pragma link C++ class vector<vector<unsigned int> >+;
#pragma link C++ class vector<vector<int> >+;
#pragma link C++ class vector<vector<float> >+;
#pragma link C++ class vector<vector<double> >+;
#pragma link C++ class pair<float,vector<float> >+;
#pragma link C++ class pair<int,SUSY::CrossSectionDB::Process>+;
#pragma link C++ class map<int,SUSY::CrossSectionDB::Process>+;
#pragma link C++ class SUSY::CrossSectionDB::iterator-;

#endif

#endif

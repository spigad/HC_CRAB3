#include "CalibrationDataInterface/CalibrationDataInterfaceROOT.h"
#include "SUSYTools/BTagCalib.h"

std::pair<float, vector<float> > BTagCalib::BTagCalibrationFunction(const vector<float>& pt, const vector<float>& eta,
                                                                    const vector<float>& SV0, const vector<int>& pdgid, 
                                                                    int error, std::string taggerName,
                                                                    std::string OP, float opval, 
                                                                    std::string calibration, std::string calibfolder)
{

    // ***************************************************************************************************************
    // ****                 Function for applying Scale Factors and associated Errors to Analyses                 ****
    // ***************************************************************************************************************
    //
    // - Input Jet information: Pt, Eta, SV0, PDG ID. First three are vectors of floats and last one is vector of ints
    // - Input option for applying shift due to errors. Takes integer value: 0 = Default, 1 = Shift Up, 2 = Shift Down
    // - Function then uses input values to feed into root file, which provides Scale Factors and associated errors
    //   as a function of Pt and Eta. These Scale Factors are then used to calculate the weights applied to individual
    //   jets and the event as a whole.
    // - Function then returns a standard pair, one a float containing the Event Weight and the other a vector of
    //   floats containing the weights for the individual jets in the event.
    //
    // - IMPORTANT: SCALE FACTORS NOT DEFINED BELOW JET PT OF 20 GeV OR |ETA| ABOVE 2.5!!!
    //              NULL WEIGHT VALUES WILL BE RETURNED FOR THESE!
    // - For Jet Pt greater than 500 GeV (light) or 200 GeV (b/c) no Scale Factor is defined.
    //   In these cases Scale Factor values for either 500 GeV or 200 GeV will be used.
    //
    // ***************************************************************************************************************

    //! Create the BTagCalib object
    static Analysis::CalibrationDataInterfaceROOT* BTagCalib = new Analysis::CalibrationDataInterfaceROOT(taggerName,calibration,calibfolder);

    float EventWeight = -1;
    vector<float> jetWeightVector;
    vector<float> pt_to_use;

    //! Fill jet information into new vector and test values for applicable SF range
    for (unsigned int jitr = 0; jitr < pt.size(); jitr++) {
        pt_to_use.push_back(pt[jitr]);
        //if ((pdgid[jitr] != 4 && pdgid[jitr] != 5) && pt_to_use[jitr] > 500000.) pt_to_use[jitr] = 499000.; //! Currently no MC eff. defined above 200 GeV
        if ((pdgid[jitr] != 4 && pdgid[jitr] != 5) && pt_to_use[jitr] > 200000.) pt_to_use[jitr] = 199000.;
        else if ((pdgid[jitr] == 4 || pdgid[jitr] == 5) && pt_to_use[jitr] > 200000.) pt_to_use[jitr] = 199000.;
        else if (pt_to_use[jitr] < 20000. || fabs(eta[jitr]) > 2.5) {
            pt_to_use[jitr] = -1;
        }
    }

    //! Set BTag Calibration variables
    std::string label;          //! Flavour, Light = "N/A", or "C", "B"
    // std::string OP = "5_85";    //! Only operating point considered - New

    //! Perform actions for each individual jet in an event
    for (unsigned int jitr = 0; jitr < pt.size(); jitr++) {
        // If a jet was out of acceptance, the return a weight of one
        if (pt_to_use[jitr]<0){
            jetWeightVector.push_back(1.);
            continue;
        }

        //! Set quark flavour to be used
        if (pdgid[jitr] == 4) label = "C";
        else if (pdgid[jitr] == 5) label = "B";
        else label = "N/A";

        //! Set necessary b-tag variables for retrieving SF + errors
        Analysis::CalibrationDataVariables BTagVars;
        BTagVars.jetAuthor = "AntiKt4Topo";
        BTagVars.jetPt  = pt_to_use[jitr];
        BTagVars.jetEta = eta[jitr];

        Analysis::Uncertainty BTagUnc = Analysis::Systematic; //! None, Total, Statistical, Systematic

        std::pair<double, double> BTagCalibResult;
        BTagCalibResult = BTagCalib->getScaleFactor(BTagVars, label, OP, BTagUnc);

        std::pair<double, double> BTagCalibMCEff;
        BTagCalibMCEff = BTagCalib->getMCEfficiency(BTagVars, label, OP, BTagUnc);

        //! Scale the SV0 weight
        //float SV0Weight = SV0[jitr];
        float jetWeight;
        float ScaleFactor = (float)BTagCalibResult.first, MC_Efficiency = (float)BTagCalibMCEff.first;

        if (error == 1) ScaleFactor += (float)BTagCalibResult.second;
        else if (error == 2) ScaleFactor -= (float)BTagCalibResult.second;

        //! Calculate jet weight
        if (SV0[jitr] > opval) jetWeight = ScaleFactor;
        else jetWeight = (1 - ScaleFactor * MC_Efficiency) / (1 - MC_Efficiency);
        jetWeightVector.push_back(jetWeight);

        //! Calculate event weight
        if (jitr == 0) EventWeight = jetWeight;
        else EventWeight *= jetWeight;
    }

    std::pair<float, vector<float> > weights_pair (EventWeight, jetWeightVector);

    return weights_pair;
}


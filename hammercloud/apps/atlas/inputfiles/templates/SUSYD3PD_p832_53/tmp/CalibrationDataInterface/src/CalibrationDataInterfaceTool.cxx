///////////////////////////////////////////////////////////////////
// CalibrationDataInterfaceTool.cxx, (c) ATLAS Detector software
///////////////////////////////////////////////////////////////////

#include "CalibrationDataInterface/CalibrationDataInterfaceTool.h"
#include "JetEvent/Jet.h"

#include "TF1.h"
//#include "TMatrixT.h"
#include "TMatrixDSym.h"
#include "TMath.h"

// This constant denotes the array dimension for the function arguments
const int maxdim = 6;

//================ Constructor =================================================

Analysis::CalibrationDataInterfaceTool::CalibrationDataInterfaceTool(const std::string& t,
								     const std::string& n,
								     const IInterface*  p ) :
  AthAlgTool(t,n,p),
  m_broker("PerformanceBroker")
{
  declareInterface<Analysis::ICalibrationDataInterfaceTool>(this);

  declareProperty("taggerName", m_taggerName = "undefined",
		  "tagging algorithm name");
  declareProperty("operatingPoints", m_operatingPoints,
		  "operating points for this tagging algorithm");
  declareProperty("efficiencyCalibrationBName", m_EffcalibrationBName = "default",
		  "efficiency calibration curve for b jets");
  declareProperty("efficiencyCalibrationCName", m_EffcalibrationCName = "default",
		  "efficiency calibration curve for c jets");
  declareProperty("efficiencyCalibrationLightName", m_EffcalibrationLightName = "default",
		  "efficiency calibration curve for light-flavour jets");
  declareProperty("scaleFactorCalibrationBName", m_SFcalibrationBName = "default",
		  "scale factor calibration curve for b jets");
  declareProperty("scaleFactorCalibrationCName", m_SFcalibrationCName = "default",
		  "scale factor calibration curve for c jets");
  declareProperty("scaleFactorCalibrationLightName", m_SFcalibrationLightName = "default",
		  "scale factor calibration curve for light-flavour jets");
  declareProperty("PerformanceBroker", m_broker,
		  "tool interfacing with COOL Database");
}

//================ Destructor =================================================

Analysis::CalibrationDataInterfaceTool::~CalibrationDataInterfaceTool()
{}

//================ Interface stuff ===============================================

StatusCode Analysis::CalibrationDataInterfaceTool::queryInterface( const InterfaceID& riid, void** ppvIf )
{
   if ( riid == ICalibrationDataInterfaceTool::interfaceID() )  {
      *ppvIf = (ICalibrationDataInterfaceTool*)this;
      addRef();
      return StatusCode::SUCCESS;
   }

   return AthAlgTool::queryInterface( riid, ppvIf );
}

//================ Initialisation =================================================

StatusCode Analysis::CalibrationDataInterfaceTool::initialize()
{
  
  StatusCode sc = AthAlgTool::initialize();
  if (sc.isFailure()) return sc;

  sc = m_broker.retrieve();
  if (sc.isFailure()) {
    ATH_MSG_FATAL("initialize() in " << name() << ": unable to retrieve CalibrationBroker tool!");
    return sc;
  }

  std::map<std::string, std::string> calibrationNames;
  // insert the calibration names into a common object
  calibrationNames["B"] = m_EffcalibrationBName;
  calibrationNames["C"] = m_EffcalibrationCName;
  calibrationNames["Light"] = m_EffcalibrationLightName;
  setEffCalibrationNames(calibrationNames);
  calibrationNames["B"] = m_SFcalibrationBName;
  calibrationNames["C"] = m_SFcalibrationCName;
  calibrationNames["Light"] = m_SFcalibrationLightName;
  setSFCalibrationNames(calibrationNames);

  // register all objects
  for (std::map<std::string, std::string>::const_iterator it = calibrationNames.begin();
       it != calibrationNames.end(); ++it) {
    for (std::vector<std::string>::const_iterator op = m_operatingPoints.begin();
	 op != m_operatingPoints.end(); ++op) {
      registerObjects(it->first, *op);
    }
  }

  ATH_MSG_INFO("initialize() successful in " << name());
  return StatusCode::SUCCESS;
}

//================ Finalisation =================================================

StatusCode Analysis::CalibrationDataInterfaceTool::finalize()
{
  StatusCode sc = AthAlgTool::finalize();
  return sc;
}

//============================================================================================

//====================== efficiency scale factor retrieval =============================

Analysis::CalibResult
Analysis::CalibrationDataInterfaceTool::getScaleFactor (const Jet& jet, const std::string& label,
							const std::string& OP, Uncertainty unc) const
{
  // // For now, a calibration for the charm efficiency scale factor is assumed not to exist
  // if (label == "C") return getScaleFactor(jet, "B", OP, unc);

  // for light-flavour jets, rename from "N/A"
  std::string flavour(label);
  if (flavour == "N/A") flavour = "Light";

  std::string author = jet.jetAuthor();
  Double_t x[maxdim], xsyst[maxdim];

  std::string sfName(getBasename(OP, flavour, "_SF"));
  std::string suffix("_"); suffix += m_taggerName; suffix += "_SF";
  std::string fctName(getBasename(OP, flavour, suffix));

  /* The "update" flag is used here to decide whether the functional arguments should be
   re-assessed. They are then cached, for faster computation. */

  // Return a dummy result if the object is not found
  std::pair<TF1*,bool> ret = m_broker->retrieveTObject<TF1>(m_taggerName, author, sfName);
  if (! ret.first) {
    ATH_MSG_WARNING("in " << name() << ": unable to find SF calibration for object with "
		    << "tagger/jetCollection/flavour/operating point = "
		    << m_taggerName << "/" << author << "/" << flavour << "/" << OP);
    return Analysis::dummyResult;
  }
  if (ret.second) computeFunctionArguments(fctName, ret.first->GetTitle());
  retrieveFunctionArguments(jet, fctName, x);

  // No further checks are carried out of the existence of the parameter covariance matrix
  // and parametrisation of the systematic uncertainty

  TMatrixDSym* cov = 0;
  if (unc == Total || unc == Statistical) {
    std::string sfStatName(sfName);
    sfStatName += "_stat";
    std::pair<TMatrixDSym*, bool> pStat =
      m_broker->retrieveTObject<TMatrixDSym>(m_taggerName, author, sfStatName);
    if (pStat.first == 0)
      ATH_MSG_WARNING("in " << name()
		      << ": error retrieving Scale factor parameter covariance matrix!");
    else {
      msg() << MSG::DEBUG << "Scale factor parameter covariance matrix:";
      cov = pStat.first;
      Int_t npar = ret.first->GetNpar();
      for (Int_t ipar = 0; ipar < npar; ++ipar)
	for (Int_t jpar = ipar; jpar < npar; ++jpar)
	  msg() << MSG::DEBUG << " " << (*cov)(ipar,jpar);
      msg() << MSG::DEBUG << endreq;
    }
  }

  TF1* fctsys = 0;
  if (unc == Total || unc == Systematic) {
    std::string sfSystName(sfName);
    sfSystName += "_syst";
    std::string fctSystName(fctName);
    fctSystName += "_syst";
    std::pair<TF1*,bool> rSyst = m_broker->retrieveTObject<TF1>(m_taggerName, author, sfSystName);
    if (rSyst.second) computeFunctionArguments(fctSystName, rSyst.first->GetTitle());
    fctsys = rSyst.first;
    retrieveFunctionArguments(jet, fctSystName, xsyst);
  }

  return getResults(x, xsyst, ret.first, fctsys, cov);
}

//====================== "MC" efficiency retrieval ======================================

Analysis::CalibResult
Analysis::CalibrationDataInterfaceTool::getMCEfficiency (const Jet& jet, const std::string& label,
							 const std::string& OP, Uncertainty unc) const
{
  // extract the relevant jet quantities: kinematic variables and jet author

  // for light-flavour jets, rename from "N/A"
  std::string flavour(label);
  if (flavour == "N/A") flavour = "Light";

  std::string author = jet.jetAuthor();
  Double_t x[maxdim], xsyst[maxdim];

  std::string effName(getBasename(OP, flavour, "_Eff", false));
  std::string suffix("_"); suffix += m_taggerName; suffix += "_Eff";
  std::string fctName(getBasename(OP, flavour, suffix, false));

  /* The "update" flag is used here to decide whether the functional arguments should be
   re-assessed. They are then cached, for faster computation. */

  // Return a dummy result if the object is not found
  std::pair<TF1*,bool> ret = m_broker->retrieveTObject<TF1>(m_taggerName, author, effName);
  if (! ret.first) {
    ATH_MSG_WARNING("in " << name() << ": unable to find Eff calibration for object with "
		    << "tagger/jetCollection/flavour/operating point = "
		    << m_taggerName << "/" << author << "/" << flavour << "/" << OP);
    return Analysis::dummyResult;
  }
  if (ret.second) computeFunctionArguments(fctName, ret.first->GetTitle());
  retrieveFunctionArguments(jet, fctName, x);

  TMatrixDSym* cov = 0;
  if (unc == Total || unc == Statistical) {
    std::string effStatName(effName);
    effStatName += "_stat";
    std::pair<TMatrixDSym*, bool> pStat =
      m_broker->retrieveTObject<TMatrixDSym>(m_taggerName, author, effStatName);
    if (pStat.first == 0)
      ATH_MSG_WARNING("in " << name()
		      << ": error retrieving Efficiency parameter covariance matrix!");
    else {
      msg() << MSG::DEBUG << "Efficiency parameter covariance matrix:";
      cov = pStat.first;
      Int_t npar = ret.first->GetNpar();
      for (Int_t ipar = 0; ipar < npar; ++ipar)
	for (Int_t jpar = ipar; jpar < npar; ++jpar)
	  msg() << MSG::DEBUG << " " << (*cov)(ipar,jpar);
      msg() << MSG::DEBUG << endreq;
    }
  }

  TF1* fctsys = 0;
  if (unc == Total || unc == Systematic) {
    std::string effSystName(effName);
    effSystName += "_syst";
    std::string fctSystName(fctName);
    fctSystName += "_syst";
    std::pair<TF1*,bool> rSyst = m_broker->retrieveTObject<TF1>(m_taggerName, author, effSystName);
    if (rSyst.second) computeFunctionArguments(fctSystName, rSyst.first->GetTitle());
    fctsys = rSyst.first;
    retrieveFunctionArguments(jet, fctSystName, xsyst);
  }

  return getResults(x, xsyst, ret.first, fctsys, cov);
}

//====================== efficiency retrieval ==========================================

Analysis::CalibResult
Analysis::CalibrationDataInterfaceTool::getEfficiency (const Jet& jet, const std::string& label,
						       const std::string& OP, Uncertainty unc) const
{
  Analysis::CalibResult sfResult = getScaleFactor(jet, label, OP, unc);
  Analysis::CalibResult effResult = getMCEfficiency(jet, label, OP, unc);

  double relative = 0;
  double value = effResult.first*sfResult.first;
  if (value != 0) {
    relative = effResult.second/effResult.first;
    double sfRelative = sfResult.second/sfResult.first;
    relative = TMath::Sqrt(sfRelative*sfRelative + relative*relative);
  } else {
    ATH_MSG_WARNING("in " << name() << ": null result, SF=" << sfResult.first
		    << " MC eff=" << effResult.first);
    relative = Analysis::dummyValue;
  }

  return std::make_pair(value,value*relative);
}

//============================================================================================

void Analysis::CalibrationDataInterfaceTool::registerObjects(const std::string& flavour,
							     const std::string& OP) const
{
  static const std::string slash("/");

//   // construct a unique string to identify this combination
//   std::string unique(flavour); unique += slash; unique += OP;

//   // do nothing if registration of this combination has previously been attempted
//   for (std::vector<std::string>::const_iterator it = m_registrations.begin();
//        it != m_registrations.end(); ++it)
//     if (unique == *it) return;

  // Construct the common string part. Note that it isn't necessary to add the
  // jet author part here, as this is handled by the CalibrationBroker.
  std::string common = OP; common += slash;
  common += flavour; common += slash;
  std::string commonEff(common); commonEff += EffCalibrationName(flavour);
  std::string commonSF(common); commonSF += SFCalibrationName(flavour);

  // cycle through the obects that ought to be present in this subdirectory

  // central results
  std::string nameSF(commonSF); nameSF += "_SF";
  m_broker->registerHistogram(m_taggerName, nameSF);
  std::string nameEff(commonEff); nameEff += "_Eff";
  m_broker->registerHistogram(m_taggerName, nameEff);

  // statistical uncertainties
  std::string nameSFStat(nameSF); nameSFStat += "_stat";
  m_broker->registerHistogram(m_taggerName, nameSFStat);
  std::string nameEffStat(nameEff); nameEffStat += "_stat";
  m_broker->registerHistogram(m_taggerName, nameEffStat);

  // systematic uncertainties
  std::string nameSFSyst(nameSF); nameSFSyst += "_syst";
  m_broker->registerHistogram(m_taggerName, nameSFSyst);
  std::string nameEffSyst(nameEff); nameEffSyst += "_syst";
  m_broker->registerHistogram(m_taggerName, nameEffSyst);

  // indicate that registration for this combination has been attempted
  //  m_registrations.push_back(unique);
}

void Analysis::CalibrationDataInterfaceTool::retrieveFunctionArguments (const Jet& jet,
									const std::string& object, Double_t* x) const
{
  msg() << MSG::DEBUG << "object " << object << "argument values:";
  std::vector<int> argumentTypes = functionArguments(object);
  for (unsigned int t = 0; t < argumentTypes.size(); ++t) {
    switch(argumentTypes[t]) {
    case kPt:
      // NB convert from MeV to GeV!
      x[t] = jet.pt() * 0.001;
      msg() << MSG::DEBUG << " pt=" << x[t];
      break;
    case kEta:
      x[t] = jet.eta();
      msg() << MSG::DEBUG << " eta=" << x[t];
      break;
    case kAbsEta:
      x[t] = jet.eta();
      if (x[t] < 0) x[t] *= -1.;
      msg() << MSG::DEBUG << " abs(eta)=" << x[t];
    }
  }
  if (argumentTypes.size() == 0) msg() << " none";
  msg() << MSG::DEBUG << endreq;
}

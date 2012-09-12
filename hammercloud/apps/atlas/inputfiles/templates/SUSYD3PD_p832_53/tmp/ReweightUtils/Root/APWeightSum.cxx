#define APWeightSum_cxx
#include "ReweightUtils/APWeightSum.h"
#include "ReweightUtils/APWeightEntry.h"
#include "ReweightUtils/APEvtWeight.h"
#include "THnSparse.h"
#include <cmath>
#include <iostream>

APWeightSum::APWeightSum() {
  _k_evt_orig = 0;
  _k_evt_weight = 0.;
  _k_evt_weight2 = 0.;
  _k_evt_weight_external = 0.;
  _variance = 0.;
  _variance_nocorr = 0.;
  _variance_fullcorr = 0.;
  _variance_sys = 0.;
  
  _linear_uncert_mu = 0;
  _linear_uncert_el = 0;
  _linear_uncert_jet = 0;
  _linear_uncert_mumo = 0;
  _linear_uncert_elmo = 0;
  _linear_uncert_jetmo = 0;
  _linear_uncert_dimu = 0;
  _linear_uncert_diel = 0;
  _linear_uncert_dijet = 0;


  _isComputed = false;
}

APWeightSum::~APWeightSum() {
  if (_linear_uncert_mu != 0) delete _linear_uncert_mu;
  if (_linear_uncert_el != 0) delete _linear_uncert_el;
  if (_linear_uncert_jet != 0) delete _linear_uncert_jet;
  if (_linear_uncert_mumo != 0) delete _linear_uncert_mumo;
  if (_linear_uncert_elmo != 0) delete _linear_uncert_elmo;
  if (_linear_uncert_jetmo != 0) delete _linear_uncert_jetmo;
  if (_linear_uncert_dimu != 0) delete _linear_uncert_dimu;
  if (_linear_uncert_diel != 0) delete _linear_uncert_diel;
  if (_linear_uncert_dijet != 0) delete _linear_uncert_dijet;
}

void APWeightSum::AddWeightToEvt(APWeightEntry* weight) {
  _current_evt_weights.push_back(weight);
}

double APWeightSum::GetSumW() const {
  return _k_evt_weight;
}

double APWeightSum::GetSumW2() const {
  return _k_evt_weight2;
}

double APWeightSum::GetSumWExternal() const {
  return _k_evt_weight_external;
}

double APWeightSum::GetStdDev() {
  if ( !_isComputed ) Compute();
  return sqrt(_variance);
}

double APWeightSum::GetVariance() {
  if ( !_isComputed ) Compute();
  return _variance;
}

double APWeightSum::GetVarianceNoCorr() {
  return _variance_nocorr;
}

double APWeightSum::GetVarianceFullCorr() {
  if ( !_isComputed ) Compute();
  return _variance_fullcorr;
}

double APWeightSum::GetSysUncert() const {
  return sqrt(_variance_sys);
}

unsigned long APWeightSum::GetKUnweighted() const {
  return _k_evt_orig;
}

void APWeightSum::FinishEvt(double ext_weight) {
  ++_k_evt_orig;
  double evt_weight = 1.0;
  double uncert = 0.0;
  double uncert_sys = 0.0;
  for (unsigned int i = 0, I = _current_evt_weights.size(); i < I; ++i) {
    double uncert_summand = 1.0;
    evt_weight *= (1. - _current_evt_weights[i]->GetExpectancy());
    for (unsigned int k = 0; k < I; ++k) {
      if (i != k) uncert_summand *= (1. - _current_evt_weights[i]->GetExpectancy());
    }
    uncert += (uncert_summand * uncert_summand * _current_evt_weights[i]->GetVariance());
    uncert_sys += (uncert_summand * uncert_summand * _current_evt_weights[i]->GetSysUncert2());
  }
  _k_evt_weight += ext_weight * (1. - evt_weight);
  _k_evt_weight2 += _k_evt_weight*_k_evt_weight;
  _k_evt_weight_external += ext_weight;
  _variance += fabs(ext_weight) * uncert;
  _variance_sys += ext_weight * uncert_sys;
  _current_evt_weights.clear();
}

void APWeightSum::AddEvt(APEvtWeight* evt_weight, double ext_weight) {
  ++_k_evt_orig;
  _k_evt_weight += ext_weight * evt_weight->GetWeight();
  _k_evt_weight2 += _k_evt_weight*_k_evt_weight;
  _k_evt_weight_external += ext_weight;

  std::vector<APWeightEntry*> temp_vec_mu = evt_weight->GetWeightObjects(APEvtWeight::kMuon);
  std::vector<APWeightEntry*> temp_vec_dimu = evt_weight->GetWeightObjects(APEvtWeight::kDiMuon);
  std::vector<APWeightEntry*> temp_vec_mumo = evt_weight->GetWeightObjects(APEvtWeight::kMuonMO);
  if (temp_vec_mu.size() > 0) {
    if (_linear_uncert_mu == 0) {
      std::vector<int> original_dimensions = temp_vec_mu[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_mu = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_mu.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_mu[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_mu[i]->GetVariance());
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kMOORed || evt_weight->GetType() == APEvtWeight::kORed || evt_weight->GetType() == APEvtWeight::kMuon) weight_uncert *= (1.0 - temp_vec_mu[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_mu[j]->GetExpectancy();
        }
      }
      if(evt_weight->GetType() == APEvtWeight::kMOORed) {
        double weight_spart_temp = 1.;
        for( unsigned int l = 0; l < I; ++l ) {
          weight_spart_temp *= (1.-temp_vec_mu[l]->GetExpectancy());
        }
        weight_spart_temp = 1. - weight_spart_temp;
        double extra_derivative_temp = ( fabs(1.-weight_spart_temp) > 1.e-50 ) ? (1. - evt_weight->GetWeight())/(1.-weight_spart_temp) : 1.;
        weight_uncert *= extra_derivative_temp;
      }
      _linear_uncert_mu->SetBinContent(&coord.front(), _linear_uncert_mu->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }

  std::vector<APWeightEntry*> temp_vec_el = evt_weight->GetWeightObjects(APEvtWeight::kElectron);
  std::vector<APWeightEntry*> temp_vec_diel = evt_weight->GetWeightObjects(APEvtWeight::kDiElectron);
  std::vector<APWeightEntry*> temp_vec_elmo = evt_weight->GetWeightObjects(APEvtWeight::kElectronMO);
  if (temp_vec_el.size() > 0) {
    if (_linear_uncert_el == 0) {
      std::vector<int> original_dimensions = temp_vec_el[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_el = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_el.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_el[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_el[i]->GetVariance());
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kMOORed ||evt_weight->GetType() == APEvtWeight::kORed || evt_weight->GetType() == APEvtWeight::kElectron) weight_uncert *= (1.0 - temp_vec_el[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_el[j]->GetExpectancy();
        }
      }
      if(evt_weight->GetType() == APEvtWeight::kMOORed) {
        double weight_spart_temp = 1.;
        for( unsigned int l = 0; l < I; ++l ) {
          weight_spart_temp *= (1.-temp_vec_el[l]->GetExpectancy());
        }
        weight_spart_temp = 1. - weight_spart_temp;
        double extra_derivative_temp = ( fabs(1.-weight_spart_temp) > 1.e-50 ) ? (1. - evt_weight->GetWeight())/(1.-weight_spart_temp) : 1.;
        weight_uncert *= extra_derivative_temp;
      }
      _linear_uncert_el->SetBinContent(&coord.front(), _linear_uncert_el->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }
  
  std::vector<APWeightEntry*> temp_vec_jet = evt_weight->GetWeightObjects(APEvtWeight::kJet);
  std::vector<APWeightEntry*> temp_vec_dijet = evt_weight->GetWeightObjects(APEvtWeight::kDiJet);
  std::vector<APWeightEntry*> temp_vec_jetmo = evt_weight->GetWeightObjects(APEvtWeight::kJetMO);
  if (temp_vec_jet.size() > 0) {
    if (_linear_uncert_jet == 0) {
      std::vector<int> original_dimensions = temp_vec_jet[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_jet = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_jet.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_jet[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_jet[i]->GetVariance());
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kMOORed || evt_weight->GetType() == APEvtWeight::kORed || evt_weight->GetType() == APEvtWeight::kJet) weight_uncert *= (1.0 - temp_vec_jet[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_jet[j]->GetExpectancy();
        }
      }
      if(evt_weight->GetType() == APEvtWeight::kMOORed) {
        double weight_spart_temp = 1.;
        for( unsigned int l = 0; l < I; ++l ) {
          weight_spart_temp *= (1.-temp_vec_jet[l]->GetExpectancy());
        }
        weight_spart_temp = 1. - weight_spart_temp;
        double extra_derivative_temp = ( fabs(1.-weight_spart_temp) > 1.e-50 ) ? (1. - evt_weight->GetWeight())/(1.-weight_spart_temp) : 1.;
        weight_uncert *= extra_derivative_temp;
      }
      _linear_uncert_jet->SetBinContent(&coord.front(), _linear_uncert_jet->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }

  if (temp_vec_mumo.size() > 0) {
    if (_linear_uncert_mumo == 0) {
      std::vector<int> original_dimensions = temp_vec_mumo[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_mumo = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_mumo.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_mumo[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_mumo[i]->GetVariance());
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kMOORed || evt_weight->GetType() == APEvtWeight::kORed || evt_weight->GetType() == APEvtWeight::kMuon) weight_uncert *= (1.0 - temp_vec_mumo[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_mumo[j]->GetExpectancy();
        }
      }
      if(evt_weight->GetType() == APEvtWeight::kMOORed) {
        double weight_spart_temp = 1.;
        for( unsigned int l = 0; l < I; ++l ) {
          weight_spart_temp *= (1.-temp_vec_mumo[l]->GetExpectancy());
        }
        weight_spart_temp = 1. - weight_spart_temp;
        double extra_derivative_temp = ( fabs(1.-weight_spart_temp) > 1.e-50 ) ? (1. - evt_weight->GetWeight())/(1.-weight_spart_temp) : 1.;
        weight_uncert *= extra_derivative_temp;
      }
      _linear_uncert_mumo->SetBinContent(&coord.front(), _linear_uncert_mumo->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }
  
  if (temp_vec_elmo.size() > 0) {
    if (_linear_uncert_elmo == 0) {
      std::vector<int> original_dimensions = temp_vec_elmo[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_elmo = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_elmo.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_elmo[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_elmo[i]->GetVariance());
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kMOORed || evt_weight->GetType() == APEvtWeight::kORed || evt_weight->GetType() == APEvtWeight::kMuon) weight_uncert *= (1.0 - temp_vec_elmo[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_elmo[j]->GetExpectancy();
        }
      }
      if(evt_weight->GetType() == APEvtWeight::kMOORed) {
        double weight_spart_temp = 1.;
        for( unsigned int l = 0; l < I; ++l ) {
          weight_spart_temp *= (1.-temp_vec_elmo[l]->GetExpectancy());
        }
        weight_spart_temp = 1. - weight_spart_temp;
        double extra_derivative_temp = ( fabs(1.-weight_spart_temp) > 1.e-50 ) ? (1. - evt_weight->GetWeight())/(1.-weight_spart_temp) : 1.;
        weight_uncert *= extra_derivative_temp;
      }
      _linear_uncert_elmo->SetBinContent(&coord.front(), _linear_uncert_elmo->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }

  if (temp_vec_jetmo.size() > 0) {
    if (_linear_uncert_jetmo == 0) {
      std::vector<int> original_dimensions = temp_vec_jetmo[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_jetmo = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_jetmo.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_jetmo[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_jetmo[i]->GetVariance());
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kMOORed || evt_weight->GetType() == APEvtWeight::kORed || evt_weight->GetType() == APEvtWeight::kMuon) weight_uncert *= (1.0 - temp_vec_jetmo[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_jetmo[j]->GetExpectancy();
        }
      }
      if(evt_weight->GetType() == APEvtWeight::kMOORed) {
        double weight_spart_temp = 1.;
        for( unsigned int l = 0; l < I; ++l ) {
          weight_spart_temp *= (1.-temp_vec_jetmo[l]->GetExpectancy());
        }
        weight_spart_temp = 1. - weight_spart_temp;
        double extra_derivative_temp = ( fabs(1.-weight_spart_temp) > 1.e-50 ) ? (1. - evt_weight->GetWeight())/(1.-weight_spart_temp) : 1.;
        weight_uncert *= extra_derivative_temp;
      }
      _linear_uncert_jetmo->SetBinContent(&coord.front(), _linear_uncert_jetmo->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }


  if (temp_vec_dimu.size() > 0) {
    if (_linear_uncert_dimu == 0) {
      std::vector<int> original_dimensions = temp_vec_dimu[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_dimu = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_dimu.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_dimu[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_dimu[i]->GetVariance());
      double weight_derivative = 0.;
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kORed) weight_uncert *= (1.0 - temp_vec_dimu[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_dimu[j]->GetExpectancy();
          else if (evt_weight->GetType() == APEvtWeight::kDiMuon || evt_weight->GetType() == APEvtWeight::kMOORed) {
            double weight_derivative_temp = temp_vec_dimu[j]->GetExpectancy();
            for( unsigned int k = 0; k < I; ++k ) {
              if( k != j && k != i ) {
                 weight_derivative_temp *= (1.0 - temp_vec_dimu[k]->GetExpectancy() );
              }
            }
            weight_derivative += weight_derivative_temp;  
          }
        }
      }
      if( evt_weight->GetType() == APEvtWeight::kDiMuon || evt_weight->GetType() == APEvtWeight::kMOORed ) {
        weight_uncert *= weight_derivative;
        if( evt_weight->GetType() == APEvtWeight::kMOORed ) {
          double extra_derivative_temp = 1.;
          for( unsigned int l = 0, L = temp_vec_mu.size(); l < L; ++l ) {
            extra_derivative_temp *= 1. - temp_vec_mu[l]->GetExpectancy();
          }
          weight_uncert *= extra_derivative_temp;
        }
      }
      _linear_uncert_dimu->SetBinContent(&coord.front(), _linear_uncert_dimu->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }

  if (temp_vec_diel.size() > 0) {
    if (_linear_uncert_diel == 0) {
      std::vector<int> original_dimensions = temp_vec_diel[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_diel = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_diel.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_diel[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_diel[i]->GetVariance());
      double weight_derivative = 0.;
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kORed ) weight_uncert *= (1.0 - temp_vec_diel[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_diel[j]->GetExpectancy();
          else if (evt_weight->GetType() == APEvtWeight::kDiElectron || evt_weight->GetType() == APEvtWeight::kMOORed) {
            double weight_derivative_temp = temp_vec_diel[j]->GetExpectancy();
            for( unsigned int k = 0; k < I; ++k ) {
              if( k != j && k != i ) {
                 weight_derivative_temp *= (1.0 - temp_vec_diel[k]->GetExpectancy() );
              }
            }
            weight_derivative += weight_derivative_temp;
          }
        }
      }
      if( evt_weight->GetType() == APEvtWeight::kDiElectron || evt_weight->GetType() == APEvtWeight::kMOORed) {
        weight_uncert *= weight_derivative;
        if( evt_weight->GetType() == APEvtWeight::kMOORed ) {
          double extra_derivative_temp = 1.;
          for( unsigned int l = 0, L = temp_vec_el.size(); l < L; ++l ) {
            extra_derivative_temp *= 1. - temp_vec_el[l]->GetExpectancy();
          }
          weight_uncert *= extra_derivative_temp;
        }
      }
      _linear_uncert_diel->SetBinContent(&coord.front(), _linear_uncert_diel->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }
  
  if (temp_vec_dijet.size() > 0) {
    if (_linear_uncert_dijet == 0) {
      std::vector<int> original_dimensions = temp_vec_dijet[0]->GetOriginalDimensions();
      int *bins = new int[original_dimensions.size()];
      double *xmin = new double[original_dimensions.size()];
      double *xmax = new double[original_dimensions.size()];
      for (unsigned int i = 0, I = original_dimensions.size(); i < I; ++i) {
        bins[i] = original_dimensions[i];
        xmin[i] = 0.;
        xmax[i] = 10.;
      }
      _linear_uncert_dijet = new THnSparseD("","",original_dimensions.size(),bins,xmin,xmax);
    }
    for (unsigned int i = 0, I = temp_vec_dijet.size(); i < I; ++i) {
      std::vector<int> coord = temp_vec_dijet[i]->GetCoords();
      double weight_uncert = sqrt(temp_vec_dijet[i]->GetVariance());
      double weight_derivative = 0.;
      for (unsigned int j = 0; j < I; ++j) {
        if (j != i) {
          if (evt_weight->GetType() == APEvtWeight::kORed) weight_uncert *= (1.0 - temp_vec_dijet[j]->GetExpectancy());
          else if (evt_weight->GetType() == APEvtWeight::kANDed) weight_uncert *= temp_vec_dijet[j]->GetExpectancy();
          else if (evt_weight->GetType() == APEvtWeight::kDiJet || evt_weight->GetType() == APEvtWeight::kMOORed ) {
            double weight_derivative_temp = temp_vec_dijet[j]->GetExpectancy();
            for( unsigned int k = 0; k < I; ++k ) {
              if( k != j && k != i ) {
                 weight_derivative_temp *= (1.0 - temp_vec_dijet[k]->GetExpectancy() );
              }
            }
            weight_derivative += weight_derivative_temp;
          }
        }
      }
      if( evt_weight->GetType() == APEvtWeight::kDiJet || evt_weight->GetType() == APEvtWeight::kMOORed) {
        weight_uncert *= weight_derivative;
        if( evt_weight->GetType() == APEvtWeight::kMOORed ) {
          double extra_derivative_temp = 1.;
          for( unsigned int l = 0, L = temp_vec_jet.size(); l < L; ++l ) {
            extra_derivative_temp *= 1. - temp_vec_jet[l]->GetExpectancy();
          }
          weight_uncert *= extra_derivative_temp;
        }
      }
      _linear_uncert_dijet->SetBinContent(&coord.front(), _linear_uncert_dijet->GetBinContent(&coord.front())+weight_uncert);
      _variance_nocorr += weight_uncert*weight_uncert;
    }
  }

  
  _variance_sys += ext_weight * evt_weight->GetSysVariance();
  
  _isComputed = false;
}

void APWeightSum::Compute() {
  _variance = 0.;
  _variance_fullcorr = 0.;
  if (_linear_uncert_mu != 0) {
    double temp_linear_uncerts = 0.; 
    for (unsigned int i = 0, I = _linear_uncert_mu->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_mu->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
  if (_linear_uncert_el != 0) {
    double temp_linear_uncerts = 0.; 
    for (unsigned int i = 0, I = _linear_uncert_el->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_el->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
  if (_linear_uncert_jet != 0) {
    double temp_linear_uncerts = 0.; 
    for (unsigned int i = 0, I = _linear_uncert_jet->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_jet->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }

  if (_linear_uncert_mumo != 0) {
    double temp_linear_uncerts = 0.;
    for (unsigned int i = 0, I = _linear_uncert_mumo->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_mumo->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
  if (_linear_uncert_elmo != 0) {
    double temp_linear_uncerts = 0.;
    for (unsigned int i = 0, I = _linear_uncert_elmo->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_elmo->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
  if (_linear_uncert_jetmo != 0) {
    double temp_linear_uncerts = 0.;
    for (unsigned int i = 0, I = _linear_uncert_jetmo->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_jetmo->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
 
  if (_linear_uncert_dimu != 0) {
    double temp_linear_uncerts = 0.;
    for (unsigned int i = 0, I = _linear_uncert_dimu->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_dimu->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
  if (_linear_uncert_diel != 0) {
    double temp_linear_uncerts = 0.;
    for (unsigned int i = 0, I = _linear_uncert_diel->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_diel->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  }
  if (_linear_uncert_dijet != 0) {
    double temp_linear_uncerts = 0.;
    for (unsigned int i = 0, I = _linear_uncert_dijet->GetNbins(); i < I; ++i) {
      double bin_content = _linear_uncert_dijet->GetBinContent(i);
      _variance += bin_content*bin_content;
      temp_linear_uncerts += bin_content;
    }
    _variance_fullcorr += temp_linear_uncerts*temp_linear_uncerts;
  } 
  _isComputed = true;
}

THnSparse* APWeightSum::GetUncertHistogram( APEvtWeight::ObjType type ) {
  if( type >= APEvtWeight::kANDed ) {
    std::cout << "WARNING: You are requesting the uncertainty histogram for combined type. This histogram does not exist! Returning NULL-pointer!" << std::endl;
    return NULL;
  }
  if( type ==  APEvtWeight::kMuon ) return _linear_uncert_mu;
  if( type ==  APEvtWeight::kDiMuon ) return _linear_uncert_dimu;
  if( type ==  APEvtWeight::kElectron ) return _linear_uncert_el;
  if( type ==  APEvtWeight::kDiElectron ) return _linear_uncert_diel;
  if( type ==  APEvtWeight::kJet ) return _linear_uncert_jet;
  if( type ==  APEvtWeight::kDiJet ) return _linear_uncert_dijet;
  if( type ==  APEvtWeight::kMuonMO ) return _linear_uncert_mumo;
  if( type ==  APEvtWeight::kElectronMO ) return _linear_uncert_elmo;
  if( type ==  APEvtWeight::kJetMO ) return _linear_uncert_jetmo;
  std::cout << "WARNING: You are requesting the uncertainty histogram for an unknown type. Returning NULL-pointer!" << std::endl; return NULL;
    
}

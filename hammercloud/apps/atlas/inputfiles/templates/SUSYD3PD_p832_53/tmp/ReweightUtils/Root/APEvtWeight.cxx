#define APEvtWeight_cxx
#include "ReweightUtils/APEvtWeight.h"
#include "ReweightUtils/APWeightEntry.h"
#include <cmath>
#include <iostream>

APEvtWeight::APEvtWeight(ObjType type) {
  _n_entries = 0;
  _current_evt_weights = std::vector< std::vector< APWeightEntry* > >(9);
  if (type > APEvtWeight::kDiJet) _isComputed = true;
  else _isComputed = false;
  _type = type;
}

APEvtWeight::~APEvtWeight() {
}

void APEvtWeight::AddWeightToEvt(APWeightEntry* weight) {
  if (weight->IsTrig()) {
    if (_type <= APEvtWeight::kDiJet ) {
      _current_evt_weights[_type].push_back(weight);
      ++_n_entries;
      _isComputed = false;
    } else {
      std::cout << "ERROR in APEvtWeight::AddWeightToEvt: Trying to add a weight entry to a combined event weight. Ignoring command (not adding weight entry)." << std::endl;
    }
  } else {
    std::cout << "ERROR in APEvtWeight::AddWeightToEvt: Trying to add a non-trigger weight entry to trigger event weight. Ignoring command (not adding weight entry)." << std::endl;
  }
}

const APEvtWeight operator&&(const APEvtWeight& a_in, const APEvtWeight& b_in) {
  APEvtWeight ret(APEvtWeight::kANDed);
  APEvtWeight a = a_in;
  APEvtWeight b = b_in;

  if (a.GetType() > APEvtWeight::kJetMO || b.GetType() > APEvtWeight::kJetMO) {
    if ((a._current_evt_weights[APEvtWeight::kMuon].size() > 0 && b._current_evt_weights[APEvtWeight::kMuon].size() > 0) || (a._current_evt_weights[APEvtWeight::kElectron].size() > 0 && b._current_evt_weights[APEvtWeight::kElectron].size() > 0) || (a._current_evt_weights[APEvtWeight::kJet].size() > 0 && b._current_evt_weights[APEvtWeight::kJet].size() > 0) ||(a._current_evt_weights[APEvtWeight::kMuonMO].size() > 0 && b._current_evt_weights[APEvtWeight::kMuonMO].size() > 0) || (a._current_evt_weights[APEvtWeight::kElectronMO].size() > 0 && b._current_evt_weights[APEvtWeight::kElectronMO].size() > 0) || (a._current_evt_weights[APEvtWeight::kJetMO].size() > 0 && b._current_evt_weights[APEvtWeight::kJetMO].size() > 0) )
      std::cout << "WARNING in APEvtWeight::operator&&: Trying to combine already combined event weights with overlapping objects. Uncertainties will be incorrect." << std::endl;
  }
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuon].push_back(a._current_evt_weights[APEvtWeight::kMuon][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuon].push_back(b._current_evt_weights[APEvtWeight::kMuon][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectron].push_back(a._current_evt_weights[APEvtWeight::kElectron][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectron].push_back(b._current_evt_weights[APEvtWeight::kElectron][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJet].push_back(a._current_evt_weights[APEvtWeight::kJet][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJet].push_back(b._current_evt_weights[APEvtWeight::kJet][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kMuonMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuonMO].push_back(a._current_evt_weights[APEvtWeight::kMuonMO][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kMuonMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuonMO].push_back(b._current_evt_weights[APEvtWeight::kMuonMO][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kElectronMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectronMO].push_back(a._current_evt_weights[APEvtWeight::kElectronMO][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kElectronMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectronMO].push_back(b._current_evt_weights[APEvtWeight::kElectronMO][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kJetMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJetMO].push_back(a._current_evt_weights[APEvtWeight::kJetMO][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kJetMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJetMO].push_back(b._current_evt_weights[APEvtWeight::kJetMO][i]); 
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiMuon].push_back(a._current_evt_weights[APEvtWeight::kDiMuon][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiMuon].push_back(b._current_evt_weights[APEvtWeight::kDiMuon][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiElectron].push_back(a._current_evt_weights[APEvtWeight::kDiElectron][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiElectron].push_back(b._current_evt_weights[APEvtWeight::kDiElectron][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiJet].push_back(a._current_evt_weights[APEvtWeight::kDiJet][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiJet].push_back(b._current_evt_weights[APEvtWeight::kDiJet][i]);

  if (!b._isComputed) b.Compute();
  if (!a._isComputed) a.Compute();
  ret._n_entries = a._n_entries + b._n_entries;
  ret._k_evt_weight = a._k_evt_weight * b._k_evt_weight;
  ret._variance = a._variance * b._k_evt_weight * b._k_evt_weight + b._variance * a._k_evt_weight * a._k_evt_weight;
  ret._variance_sys = a._variance_sys * b._k_evt_weight * b._k_evt_weight + b._variance_sys * a._k_evt_weight * a._k_evt_weight;
  return ret;
}

const APEvtWeight operator||(const APEvtWeight& a_in, const APEvtWeight& b_in) {
  APEvtWeight a = a_in;
  APEvtWeight b = b_in;

  if( (a.GetType() == APEvtWeight::kElectron && b.GetType() == APEvtWeight::kDiElectron ) || (a.GetType() == APEvtWeight::kDiElectron && b.GetType() == APEvtWeight::kElectron ) || (a.GetType() == APEvtWeight::kMuon && b.GetType() == APEvtWeight::kDiMuon ) || (a.GetType() == APEvtWeight::kDiMuon && b.GetType() == APEvtWeight::kMuon ) || (a.GetType() == APEvtWeight::kJet && b.GetType() == APEvtWeight::kDiJet ) || (a.GetType() == APEvtWeight::kDiJet && b.GetType() == APEvtWeight::kJet ) ) {
    APEvtWeight ret(APEvtWeight::kMOORed );
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuon].push_back(a._current_evt_weights[APEvtWeight::kMuon][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuon].push_back(b._current_evt_weights[APEvtWeight::kMuon][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectron].push_back(a._current_evt_weights[APEvtWeight::kElectron][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectron].push_back(b._current_evt_weights[APEvtWeight::kElectron][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJet].push_back(a._current_evt_weights[APEvtWeight::kJet][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJet].push_back(b._current_evt_weights[APEvtWeight::kJet][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kMuonMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuonMO].push_back(a._current_evt_weights[APEvtWeight::kMuonMO][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kMuonMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuonMO].push_back(b._current_evt_weights[APEvtWeight::kMuonMO][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kElectronMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectronMO].push_back(a._current_evt_weights[APEvtWeight::kElectronMO][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kElectronMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectronMO].push_back(b._current_evt_weights[APEvtWeight::kElectronMO][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kJetMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJetMO].push_back(a._current_evt_weights[APEvtWeight::kJetMO][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kJetMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJetMO].push_back(b._current_evt_weights[APEvtWeight::kJetMO][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiMuon].push_back(a._current_evt_weights[APEvtWeight::kDiMuon][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiMuon].push_back(b._current_evt_weights[APEvtWeight::kDiMuon][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiElectron].push_back(a._current_evt_weights[APEvtWeight::kDiElectron][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiElectron].push_back(b._current_evt_weights[APEvtWeight::kDiElectron][i]);
    for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiJet].push_back(a._current_evt_weights[APEvtWeight::kDiJet][i]);
    for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiJet].push_back(b._current_evt_weights[APEvtWeight::kDiJet][i]);
  
    if (!b._isComputed) b.Compute();
    if (!a._isComputed) a.Compute();
    
    ret._n_entries = a._n_entries + b._n_entries;
    ret._k_evt_weight = a._k_evt_weight + b._k_evt_weight * ( 1.0 - a._k_evt_weight );
    ret._variance = a._variance * ( 1.0 - b._k_evt_weight ) * ( 1.0 - b._k_evt_weight ) + b._variance * ( 1.0 - a._k_evt_weight ) * ( 1.0 - a._k_evt_weight );
    ret._variance_sys = a._variance_sys * ( 1.0 - b._k_evt_weight ) * ( 1.0 - b._k_evt_weight ) + b._variance_sys * ( 1.0 - a._k_evt_weight ) * ( 1.0 - a._k_evt_weight );
    return ret;
  }
  else if (a.GetType() > APEvtWeight::kJetMO || b.GetType() > APEvtWeight::kJetMO) {
    if ((a._current_evt_weights[APEvtWeight::kMuon].size() > 0 && b._current_evt_weights[APEvtWeight::kMuon].size() > 0) || (a._current_evt_weights[APEvtWeight::kElectron].size() > 0 && b._current_evt_weights[APEvtWeight::kElectron].size() > 0) || (a._current_evt_weights[APEvtWeight::kJet].size() > 0 && b._current_evt_weights[APEvtWeight::kJet].size() > 0) || (a._current_evt_weights[APEvtWeight::kMuonMO].size() > 0 && b._current_evt_weights[APEvtWeight::kMuonMO].size() > 0) || (a._current_evt_weights[APEvtWeight::kElectronMO].size() > 0 && b._current_evt_weights[APEvtWeight::kElectronMO].size() > 0) || (a._current_evt_weights[APEvtWeight::kJetMO].size() > 0 && b._current_evt_weights[APEvtWeight::kJetMO].size() > 0) )
      std::cout << "WARNING in APEvtWeight::operator||: Trying to combine already combined event weights with overlapping objects. Uncertainties will be incorrect." << std::endl;
  }
  
  APEvtWeight ret(APEvtWeight::kORed);

  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuon].push_back(a._current_evt_weights[APEvtWeight::kMuon][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuon].push_back(b._current_evt_weights[APEvtWeight::kMuon][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectron].push_back(a._current_evt_weights[APEvtWeight::kElectron][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectron].push_back(b._current_evt_weights[APEvtWeight::kElectron][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJet].push_back(a._current_evt_weights[APEvtWeight::kJet][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJet].push_back(b._current_evt_weights[APEvtWeight::kJet][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kMuonMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuonMO].push_back(a._current_evt_weights[APEvtWeight::kMuonMO][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kMuonMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kMuonMO].push_back(b._current_evt_weights[APEvtWeight::kMuonMO][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kElectronMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectronMO].push_back(a._current_evt_weights[APEvtWeight::kElectronMO][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kElectronMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kElectronMO].push_back(b._current_evt_weights[APEvtWeight::kElectronMO][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kJetMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJetMO].push_back(a._current_evt_weights[APEvtWeight::kJetMO][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kJetMO].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kJetMO].push_back(b._current_evt_weights[APEvtWeight::kJetMO][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiMuon].push_back(a._current_evt_weights[APEvtWeight::kDiMuon][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiMuon].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiMuon].push_back(b._current_evt_weights[APEvtWeight::kDiMuon][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiElectron].push_back(a._current_evt_weights[APEvtWeight::kDiElectron][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiElectron].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiElectron].push_back(b._current_evt_weights[APEvtWeight::kDiElectron][i]);
  for (unsigned int i = 0, I = a._current_evt_weights[APEvtWeight::kDiJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiJet].push_back(a._current_evt_weights[APEvtWeight::kDiJet][i]);
  for (unsigned int i = 0, I = b._current_evt_weights[APEvtWeight::kDiJet].size(); i < I; ++i) ret._current_evt_weights[APEvtWeight::kDiJet].push_back(b._current_evt_weights[APEvtWeight::kDiJet][i]);

  if (!b._isComputed) b.Compute();
  if (!a._isComputed) a.Compute();

  ret._n_entries = a._n_entries + b._n_entries;
  ret._k_evt_weight = 1.0 - (1.0 - a._k_evt_weight) * (1.0 - b._k_evt_weight);
  ret._variance = a._variance * (1.0 - b._k_evt_weight) * (1.0 - b._k_evt_weight) + b._variance * (1.0 - a._k_evt_weight) * (1.0 - a._k_evt_weight);
  ret._variance_sys = a._variance_sys * (1.0 - b._k_evt_weight) * (1.0 - b._k_evt_weight) + b._variance_sys * (1.0 - a._k_evt_weight) * (1.0 - a._k_evt_weight);
  return ret;
}

double APEvtWeight::GetWeight() {
  if (!_isComputed) Compute();
  return _k_evt_weight;
}

double APEvtWeight::GetStdDev() {
  if (!_isComputed) Compute();
  return sqrt(_variance);
}

double APEvtWeight::GetVariance() {
  if (!_isComputed) Compute();
  return _variance;
}

double APEvtWeight::GetSysUncert() {
  if (!_isComputed) Compute();
  return sqrt(_variance_sys);
}

double APEvtWeight::GetSysVariance() {
  if (!_isComputed) Compute();
  return _variance_sys;
}

std::vector< APWeightEntry* > APEvtWeight::GetWeightObjects(ObjType type) {
  if (type > APEvtWeight::kDiJet) {
    std::cout << "WARNING in APEvtWeight::GetWeightObjects: Trying to get non-defined object type. Returning empty vector." << std::endl;
    return std::vector< APWeightEntry* >();
  }
  return _current_evt_weights[type];
}

unsigned long APEvtWeight::NEntries() {
  return _n_entries;
}

APEvtWeight::ObjType APEvtWeight::GetType() {
  return _type;
}

void APEvtWeight::Compute() {
  if (_type > APEvtWeight::kDiJet ) {
    std::cout << "ERROR in APEvtWeight::Compute: Trying to compute combined event weight. Ignoring command." << std::endl;
  } else {
    double evt_weight = 1.0;
    double variance = 0.0;
    double variance_sys = 0.0;
    if( _type <= APEvtWeight::kJetMO ) {
      for (unsigned int i = 0, I = _current_evt_weights[_type].size(); i < I; ++i) {
        double variance_summand = 1.0;
        evt_weight *= (1. - _current_evt_weights[_type][i]->GetExpectancy());
        for (unsigned int k = 0; k < I; ++k) {
          if (i != k) variance_summand *= (1. - _current_evt_weights[_type][k]->GetExpectancy());
        }
        variance += (variance_summand * variance_summand * _current_evt_weights[_type][i]->GetVariance());
        variance_sys += (variance_summand * variance_summand * _current_evt_weights[_type][i]->GetSysUncert2());
      }
    }
    else if( _type <= APEvtWeight::kDiJet ) {
      if( _current_evt_weights[_type].size() >= 2 ) {
        for( unsigned int i = 0, I = _current_evt_weights[_type].size(); i < I; ++i ) {
          evt_weight *= (1. - _current_evt_weights[_type][i]->GetExpectancy());
        }
        for( unsigned int i = 0, I = _current_evt_weights[_type].size(); i < I; ++i ) {
          double variance_summand = 0.0;
          double temp_weight = _current_evt_weights[_type][i]->GetExpectancy();
          for( unsigned int k = 0; k < I; ++k ) {
            double temp_variance_summand = 0.0;
            if( i != k ) {
              temp_weight *= (1.-_current_evt_weights[_type][k]->GetExpectancy());
              temp_variance_summand = _current_evt_weights[_type][k]->GetExpectancy();
            }  
            for( unsigned int j = 0; j < I; ++j ) {
              if( j != i && j != k ) temp_variance_summand *= (1.-_current_evt_weights[_type][j]->GetExpectancy());
            }
            variance_summand += temp_variance_summand;
          }
          variance += (variance_summand * variance_summand * _current_evt_weights[_type][i]->GetVariance());
          variance_sys += (variance_summand * variance_summand * _current_evt_weights[_type][i]->GetSysUncert2());
          evt_weight += temp_weight;
        }
      }
    }
    _k_evt_weight = (1. - evt_weight);
    _variance = variance;
    _variance_sys = variance_sys;
  }
  _isComputed = true;
}

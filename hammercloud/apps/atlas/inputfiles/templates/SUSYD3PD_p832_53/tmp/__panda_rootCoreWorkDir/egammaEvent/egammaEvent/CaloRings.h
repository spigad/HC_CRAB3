#ifndef EGAMMAEVENT_CALORINGS_H
#define EGAMMAEVENT_CALORINGS_H

#include <vector>
#include "CaloIdentifier/CaloCell_ID.h"
#include "CLIDSvc/CLASS_DEF.h"

class RingSet {
  public:

    std::vector<float> m_rings;
    
    std::vector<CaloCell_ID::CaloSample> m_layers;

    float m_deltaEta;   // size of ring in eta
    float m_deltaPhi;   // size of ring in phi
    
    // constructor and destructor
    RingSet() { };
    virtual ~RingSet() { };

    // accessors
    float &at(unsigned int i); 
    float &operator [](unsigned int i); 
    const float &at(unsigned int i) const; 
    const float &operator [](unsigned int i) const;
    size_t size() const; 
    void clearRings(); 
    void addRing(float r); 

    size_t numberOfLayers() const;
    CaloCell_ID::CaloSample &layer(unsigned int i); 
    const CaloCell_ID::CaloSample &layer(unsigned int i) const; 
    void clearLayers(); 
    void addLayer(CaloCell_ID::CaloSample c);

    float &deltaEta(); 
    float &deltaPhi();
    const float &deltaEta() const; 
    const float &deltaPhi() const;

};

class CaloRings {
  public:
    CaloRings();
    virtual ~CaloRings() { };
    
    void addRingSet(unsigned int numberOfRings,
                    std::vector<CaloCell_ID::CaloSample> &layers,
                    float deltaEta, float deltaPhi);
    RingSet &at(unsigned int i);
    const RingSet &at(unsigned int i) const;
    RingSet &operator [](unsigned int i);
    const RingSet &operator [](unsigned int i) const;
    void clear(); 

    float ringAt(unsigned int nRingSet, unsigned int nRing); 
    

    size_t size() const;
    std::vector<RingSet>::iterator begin(); 
    std::vector<RingSet>::iterator end();
    std::vector<RingSet>::const_iterator begin() const; 
    std::vector<RingSet>::const_iterator end() const; 

  private:
    std::vector<RingSet> m_ringsets;
};

CLASS_DEF(CaloRings, 177490517, 1)

#endif


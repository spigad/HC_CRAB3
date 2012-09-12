#ifndef OR_OPS_IS_Interface_h
#define OR_OPS_IS_Interface_h

#include <iostream>
#include "SmearingClass.h"



class D3PDSelector;

class ObjAccess;

class OverlapRemoval
{

  public:
    //Constructor
    OverlapRemoval() {}; //we don't want the defualt constructor

    OverlapRemoval(D3PDSelector* inst);  
  
    virtual ~OverlapRemoval() {};
  
    //--VS Jet
    virtual unsigned int ElectronJet_OR(ObjAccess* ele, ObjAccess* jet, unsigned int iteration);  
    virtual unsigned int MuonJet_OR(ObjAccess* muo, ObjAccess* jet, unsigned int iteration);
    virtual unsigned int PhotonJet_OR(ObjAccess* pho, ObjAccess* jet, unsigned int iteration);
  
    //--VS Electron
    virtual unsigned int MuonElectron_OR(ObjAccess* muo, ObjAccess* ele,  unsigned int iteration);
    virtual unsigned int PhotonElectron_OR(ObjAccess* pho, ObjAccess* ele,  unsigned int iteration);
    
    //--VS Muon
    virtual unsigned int PhotonMuon_OR(ObjAccess* pho, ObjAccess* muo,  unsigned int iteration);

    virtual void do_Electron_Jet(unsigned int iteration);
    virtual void do_Muon_Jet(unsigned int  iteration);
    virtual void do_Photon_Jet(unsigned int  iteration);
    virtual void do_Muon_Electron(unsigned int  iteration);
    virtual void do_Photon_Electron(unsigned int  iteration);
    virtual void do_Photon_Muon(unsigned int  iteration);
    virtual void overlapRemovalOrder();
    
    D3PDSelector * m_selector;

};



class ObjectPreSelection
{

  public:
    ObjectPreSelection() {}; //we don't want the defualt constructor
    ObjectPreSelection(D3PDSelector* inst);
    virtual ~ObjectPreSelection() {}; 
    virtual unsigned int Electron_OPS(ObjAccess* ele, unsigned int  iteration);
    virtual unsigned int Muon_OPS(ObjAccess* muo, unsigned int  iteration);
    virtual unsigned int Photon_OPS(ObjAccess* pho, unsigned int  iteration);
    virtual unsigned int Jet_OPS(ObjAccess* jet, unsigned int  iteration);

    virtual void do_Electron(unsigned int  iteration);
    virtual void do_Jet(unsigned int  iteration);
    virtual void do_Muon(unsigned int  iteration);
    virtual void do_Photon(unsigned int  iteration);
    virtual void objectPreSelectionOrder();

    D3PDSelector * m_selector;

  SmearingClass mcp_smear;
  int index_mu;
  int myEventNumber;
};





class ObjAccess //Helper Class
{
  private:
    D3PDSelector * m_accessor;
    std::string m_ob_name;
    unsigned int m_index; 
    
    
  public:
    ObjAccess(std::string ob_name, unsigned int index, D3PDSelector* infosource);    
    template <class T>
    T GetValue(std::string key);
    std::string getType();
    unsigned int getIndex();
    
  

};



#endif



/**
   @class    HforToolD3PD.h

   @brief    tool for removal of heavy flavor overlap in Alpgen samples

   @author   Dominic Hirschbuehl, Michel Saners (original code in athena)
   @author   Takashi Yamanaka (converted the code for D3PD)

   taken from  Generators/GenAnalysisTools/TruthUtils/tags/TruthUtils-00-00-10

   2 November 2011
*/


#include "SUSYTools/HforToolD3PD.h"
#include <iostream>

HforToolD3PD::HforToolD3PD() : m_isbbOnly(false)
{
  initialize("angularbased", 0.4);
  m_verbosity = ERROR;
}


void HforToolD3PD::initialize(const std::string schema, const double matchingcone) 
{
  if (m_verbosity<=INFO) std::cout << "in initialize()" << std::endl;

  m_schema = schema;
  m_matchingcone = matchingcone;
}

void HforToolD3PD::setVerbosity(const enum verbosity ver)
{
  m_verbosity = ver;
}

///////////////////////////////////////////////////////////////////////
// return the q-quarks labeled as MPI, GS, ME, incoming ME or unknown
///////////////////////////////////////////////////////////////////////
const std::vector<TParticle> & HforToolD3PD::get_bQuarks_MPI() {
  return m_Quarks_MPI[5];
}

const std::vector<TParticle> & HforToolD3PD::get_bQuarks_GS() {
  return m_Quarks_GS[5];
}

const std::vector<TParticle> & HforToolD3PD::get_bQuarks_ME() {
  return m_Quarks_ME[5];
}

const std::vector<TParticle> & HforToolD3PD::get_bQuarks_MEin() {
  return m_Quarks_MEin[5];
}

const std::vector<TParticle> & HforToolD3PD::get_bQuarks_unknown() {
  return m_Quarks_unknown[5];
}

const std::vector<TParticle> & HforToolD3PD::get_cQuarks_MPI() {
  return m_Quarks_MPI[4];
}

const std::vector<TParticle> & HforToolD3PD::get_cQuarks_GS() {
  return m_Quarks_GS[4];
}

const std::vector<TParticle> & HforToolD3PD::get_cQuarks_ME() {
  return m_Quarks_ME[4];
}

const std::vector<TParticle> & HforToolD3PD::get_cQuarks_MEin() {
  return m_Quarks_MEin[4];
}

const std::vector<TParticle> & HforToolD3PD::get_cQuarks_unknown() {
  return m_Quarks_unknown[4];
}



///////////////////////////////////////////////////////////////
int HforToolD3PD::getDecision(const int datasetNumber,
			      const int mc_n, 
			      const std::vector<float> *mc_pt,
			      const std::vector<float> *mc_eta,
			      const std::vector<float> *mc_phi,
			      const std::vector<float> *mc_m,
			      const std::vector<int> *mc_pdgId,
			      const std::vector<int> *mc_status,
			      const std::vector<std::vector<int> > *mc_parent_index,
			      const std::vector<std::vector<int> > *mc_child_index)
///////////////////////////////////////////////////////////////
{
  if (m_verbosity<=INFO) std::cout << "in getDecision()" << std::endl;

  if (!checkSampleType(datasetNumber)) {
    if(m_verbosity<=WARNING) std::cout << "This dataset does not need HforTool" << std::endl;
    return -1;
  }
  
  findHFQuarks(mc_n, mc_pt, mc_eta, mc_phi, mc_m, mc_pdgId, mc_status, mc_parent_index, mc_child_index, PtEtaPhiM);
  
  if (m_verbosity<=INFO) {
    std::cout << "GS(b) = " << m_Quarks_GS[5].size() 
	      << " ME(b) = " << m_Quarks_ME[5].size() 
	      << " MPI(b) = " << m_Quarks_MPI[5].size() << std::endl;
    std::cout << "GS(c) = " << m_Quarks_GS[4].size() 
	      << " ME(c) = " << m_Quarks_ME[4].size()
	      << " MPI(c) = " << m_Quarks_MPI[4].size() << std::endl;
  }

  if(m_schema == "angularbased")
    angularBasedRemoval();
  else 
    keepAllRemoval();

  if(m_verbosity<=WARNING) std::cout << "result= " << m_result << std::endl;

  if (m_result == "isBB")               return 0;
  else if (m_result == "isCC")          return 1;
  else if (m_result == "isC")           return 2;
  else if (m_result == "isLightFlavor") return 3;
  else if (m_result == "kill")          return 4;
  else                                  return -1;  
}


///////////////////////////////////////////////////////////////
int HforToolD3PD::getDecisionOld(const int datasetNumber,
				 const int mc_n, 
				 const std::vector<float> *mc_E,
				 const std::vector<float> *mc_px,
				 const std::vector<float> *mc_py,
				 const std::vector<float> *mc_pz,
				 const std::vector<int> *mc_pdgId,
				 const std::vector<int> *mc_status,
				 const std::vector<std::vector<int> > *mc_parent_index,
				 const std::vector<std::vector<int> > *mc_child_index)
///////////////////////////////////////////////////////////////
{
  if (m_verbosity<=INFO) std::cout << "in getDecisionOld()" << std::endl;

  if (!checkSampleType(datasetNumber)) {
    if(m_verbosity<=WARNING) std::cout << "This dataset does not need HforTool" << std::endl;
    return -1;
  }
  
  findHFQuarks(mc_n, mc_px, mc_py, mc_pz, mc_E, mc_pdgId, mc_status, mc_parent_index, mc_child_index, PxPyPzE);
  
  if (m_verbosity<=INFO) {
    std::cout << "GS(b) = " << m_Quarks_GS[5].size() 
	      << " ME(b) = " << m_Quarks_ME[5].size() 
	      << " MPI(b) = " << m_Quarks_MPI[5].size() << std::endl;
    std::cout << "GS(c) = " << m_Quarks_GS[4].size() 
	      << " ME(c) = " << m_Quarks_ME[4].size()
	      << " MPI(c) = " << m_Quarks_MPI[4].size() << std::endl;
  }

  if(m_schema == "angularbased")
    angularBasedRemoval();
  else 
    keepAllRemoval();

  if(m_verbosity<=WARNING) std::cout << "result= " << m_result << std::endl;

  if (m_result == "isBB")               return 0;
  else if (m_result == "isCC")          return 1;
  else if (m_result == "isC")           return 2;
  else if (m_result == "isLightFlavor") return 3;
  else if (m_result == "kill")          return 4;
  else                                  return -1;
  
}

/////////////////////////////////////////////////
// Find the heavy flavor quarks in this event
void HforToolD3PD::findHFQuarks(const int mc_n, 
				const std::vector<float> *mc_p1,
				const std::vector<float> *mc_p2,
				const std::vector<float> *mc_p3,
				const std::vector<float> *mc_p4,
				const std::vector<int> *mc_pdgId,
				const std::vector<int> *mc_status,
				const std::vector<std::vector<int> > *mc_parent_index,
				const std::vector<std::vector<int> > *mc_child_index,
				const enum momentumSet mode)
/////////////////////////////////////////////////
{
  if(m_verbosity<=DEBUG) std::cout << "in findHFQuarks()" << std::endl;

  // clean up the previous event
  m_Quarks_MPI.clear();
  m_Quarks_GS.clear();
  m_Quarks_ME.clear();
  m_Quarks_MEin.clear();
  m_Quarks_unknown.clear();

  if(m_verbosity<=DEBUG) std::cout << "m_Quarks cleared" << std::endl;

  // vectors with the intial and final state b/c quarks: 
  // ie. initial or final in the parton shower:
  // ignore b/c quarks from b/c-hadron decays
  std::map< int,std::vector<TParticle> > finalstate_q;

  if(m_verbosity<=DEBUG) std::cout << "mc_n=" << mc_n << std::endl;

  for (int i=0; i<mc_n; i++) {
    int pdg = mc_pdgId->at(i);
    int apdg = std::abs(pdg);
    int status = mc_status->at(i);
    int parent[2] = {-1, -1};
    int child[2] = {-1, -1};
    if ( apdg==5 || apdg==4 ) { // b or c quark
      
      if(m_verbosity<=DEBUG) std::cout << "pdg = " << pdg << ": " << i << " : stat " << status << " ( " << mc_p1->at(i) << " " << mc_p2->at(i) << " " << mc_p3->at(i) << " " << mc_p4->at(i) << " )" << std::endl;

      // find the production vertex and parents
      bool hasbchadronparent(false);
      bool hasmpiparent(false);
      if (mc_parent_index->at(i).size()) {

	if(m_verbosity<=DEBUG) std::cout << "  parents size: " << mc_parent_index->at(i).size() << std::endl;

	// check that there is no b/c-hadron as a parent
	// also find mpi parent
	for(unsigned int j=0; j<mc_parent_index->at(i).size(); j++) {
	  int parentId = mc_parent_index->at(i).at(j);
	  if(j<2) parent[j] = parentId;
     
	  if(m_verbosity<=DEBUG) std::cout << "   incoming: " << parentId << std::endl;

	  if (parentId < mc_n) {
	    int pdgin = std::abs(mc_pdgId->at( parentId ));
	    
	    if( (pdgin%10000)/1000 == apdg || (pdgin%1000)/100 == apdg )
	      hasbchadronparent = true;
	    
	    // also reject the c-quarks 
	    if ( apdg == 4 && ( pdgin == 5 || (pdgin%10000)/1000 == 5 ||
				(pdgin%1000)/100 == 5 ) )
	      hasbchadronparent = true;
	    
	    if ( pdgin == 0 && mc_status->at( mc_parent_index->at(i).at(j) ) == 120 )
	      hasmpiparent = true;
	  } else {
	    if(m_verbosity<=DEBUG) std::cout << "  parent particle is out of range" << std::endl;
	  }
	}
      } else {
	// b/c parton without production vertex
	if(m_verbosity<=DEBUG) std::cout << "  b/c parton without production vertex" << std::endl;
      }

      // find the decay vertex and children
      bool hasbcquarkdaughter(false);
      if ( mc_child_index->at(i).size() ) {
	
	if(m_verbosity<=DEBUG) std::cout << "  children size: " << mc_child_index->at(i).size() << std::endl;

	// check whether there are only non b/c-quark daughters
	for(unsigned int j=0; j<mc_child_index->at(i).size(); j++) {
	  int childId = mc_child_index->at(i).at(j); 
	  if(j<2) child[j] = childId;
	  if(m_verbosity<=DEBUG) std::cout << "   outgoing: " << childId << std::endl;

	  if (childId<mc_n) {
	    int pdgout = std::abs(mc_pdgId->at( childId ));
	    if ( pdgout==apdg )
	      hasbcquarkdaughter = true;
	  } else {
	    if(m_verbosity<=DEBUG) std::cout << "  child particle is out of range" << std::endl;
	  }
	}
      } else {
	// b/c parton without decay vertex
	if(m_verbosity<=DEBUG) std::cout << "  b/c parton without decay vertex" << std::endl;
      }

      TLorentzVector part_hlv;
      if (mode==PtEtaPhiM) {
	part_hlv.SetPtEtaPhiM(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
      } else if (mode==PtEtaPhiE) {
	part_hlv.SetPtEtaPhiE(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
      } else if (mode==PxPyPzM) {
	part_hlv.SetXYZM(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
      } else if (mode==PxPyPzE) {
	part_hlv.SetPxPyPzE(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
      } else {
	std::cerr << "unknown momentum set." << std::endl;
      }

      TParticle bcpart(pdg, status, parent[0], parent[1], child[0], child[1], part_hlv.Px(), part_hlv.Py(), part_hlv.Pz(), part_hlv.E(), 0., 0., 0., 0.);
     
      if (!hasbchadronparent && !hasbcquarkdaughter) {
	if(m_verbosity<=DEBUG) std::cout << " final state b/c quark, status=" << status << std::endl;
	// if no b/c-hadron parent and no b/c-quark daughter. keep it!
	finalstate_q[apdg].push_back(bcpart);
      }

      // if no b/c-hadron parent. check it to see whether it comes from the ME
      // but ignore the ones with an MPI parent
      if (!hasbchadronparent && !hasmpiparent && 
	  (status == 123 || status == 124 ) ) {
	if(m_verbosity<=DEBUG) std::cout << "  b/c-quark from ME" << std::endl;
	m_Quarks_MEin[apdg].push_back(bcpart);
      }
   
    } // particle is b or c quark

  } // loop over all particles in the event


  // loop over all the final state b/c-quarks and find out where they come from
  // first loop over quars flavors that were stored (b,c)
  for( std::map< int, std::vector<TParticle> >::const_iterator ipdg = finalstate_q.begin(); 
       ipdg != finalstate_q.end(); ipdg++ ) {
    int apdg(ipdg->first);
    if(m_verbosity<=DEBUG) std::cout << "looking for ancestors of pdg " << apdg << std::endl;

    // second loop over the final state quarks
    for( std::vector<TParticle>::const_iterator ibcpart = finalstate_q[apdg].begin() ;
	 ibcpart != finalstate_q[apdg].end(); ibcpart++) {
      const TParticle bcpart(*ibcpart);
      if(m_verbosity<=DEBUG) std::cout << "final state b/c " << bcpart.GetStatusCode() << std::endl;
      bool isMPI(false);
      bool isGS(false);
      bool isME(false);
      bool isPDF(false);
      bool iscquarkfromb(false);
      // if the final state quark is a PDF parton, ignore it
      // (in AOD, descendants of these partons may be filtered out)
      if ( bcpart.GetStatusCode() == 141 || bcpart.GetStatusCode() == 142 ) {
	if(m_verbosity<=DEBUG) std::cout << "PDF !!" << std::endl;
	isPDF = true;
      }
      if ( !isPDF && bcpart.GetMother(0) != -1 ) {
	std::vector< std::vector<int> > ancestor_index;
	for(int i=0; i<2 && bcpart.GetMother(i)!=-1 && bcpart.GetMother(i)<mc_n; i++) {
	  std::vector<int> temp_vector;
	  temp_vector.push_back( bcpart.GetMother(i) );
	  ancestor_index.push_back( temp_vector );
	}
	for (int i=0; i<100; i++) {
	  std::vector<int> temp_vector;
	  for (unsigned int j=0; j<ancestor_index.at(i).size(); j++) {
	    for (unsigned int k=0; k<mc_parent_index->at(ancestor_index.at(i).at(j)).size(); k++) {
	      temp_vector.push_back( mc_parent_index->at(ancestor_index.at(i).at(j)).at(k) );
	    }
	  }
	  if(temp_vector.size()){
	    ancestor_index.push_back( temp_vector );
	  }else{
	    break;
	  }
	}
 

	for(unsigned int i=0; i<ancestor_index.size(); i++) {
	  for(unsigned int j=0; j<ancestor_index.at(i).size(); j++) {
	    int apdgin = std::abs(mc_pdgId->at( ancestor_index.at(i).at(j) ));
	    int statusin = mc_status->at( ancestor_index.at(i).at(j) );
	    if (apdgin != apdg) {
	      // if MPI as a non-b parent, label it
	      if ( apdgin == 0 && statusin == 120 ) {
		isMPI = true;
	      }
	      // gluon splitting or ME origin: in evgen files.
	      // proton <id::2212> seem to be save in all events: not so in  AOD files
	      // Thus look for non-HF origin with status 121 or 122
	      if ( statusin == 121 || statusin == 122 ) {
		isGS = true;
	      }
	      // c quarks froma b quark (in b-hadron decays)
	      if (apdg == 4 && (apdgin == 5 || (apdgin&10000)/1000 == 5 ||
				(apdgin%1000)/100 == 5 ) ) {
		iscquarkfromb = true;
	      }
	    } else {
	      if (m_verbosity<=DEBUG) std::cout << " b/c parent" << std::endl;
	      // if the status of a b-quark is 123 or 124, then it is a ME b-quark
	      if ( statusin == 123 || statusin == 124 ) {
		if (m_verbosity<=DEBUG) std::cout << "  ME !!" << std::endl;
		isME = true;
	      }
	      // if status 141 or 142 then it came from the PDF. ignore them!!
	      if ( statusin == 141 || statusin == 142 ) {
		if (m_verbosity<=DEBUG) std::cout << "  PDF !!" << std::endl;
		isPDF = true;
	      }
	    } // b/c or non-b/c quark
	  }
	} // loop over all ancestors
      } // final state b/c-quark with a production vertex

      // MPI output is also status 123,124 so MPI comes before anything else
      // ME parents have status 121 or 122 so ME comes before GS
      if ( !iscquarkfromb && !isPDF ) {
	if ( isMPI ) {
	  if(m_verbosity<=DEBUG) std::cout << " come from MPI" << std::endl;
	  m_Quarks_MPI[apdg].push_back( bcpart );
	} else if ( isME ) {
	  if (m_verbosity<=DEBUG) std::cout << " come from ME" << std::endl;
	  m_Quarks_ME[apdg].push_back( bcpart );
	} else if ( isGS ) {
	  // in AOD, incoming ME partons may look like GS partons 
	  // if their descendants are filltered out
	  if ( !(bcpart.GetStatusCode() == 123 || bcpart.GetStatusCode() == 124) ) {
	    if (m_verbosity<=DEBUG) std::cout << " come from GS" << std::endl;
	    m_Quarks_GS[apdg].push_back( bcpart );
	  } else
	    if(m_verbosity<=DEBUG) std::cout << "ME b/c-quark identified as GS" << std::endl;
	} else {
	  if(m_verbosity<=DEBUG) std::cout << " Unidentified b/c-quark" << std::endl;
	  m_Quarks_unknown[apdg].push_back( bcpart );
	}
      } // not a c-quark from a b decay or a PDF c-quark
    } // loop over final state b/c-quarks
  } // loop over quark flavors
  if(m_verbosity<=DEBUG) std::cout << "Loop over quaurk flavors " << std::endl;

} // end of HforToolD3PD::findHFQuarks()
      
	  



///////////////////////////////////////////////////////
// No overlap removal. only migration of events
// to be used only Wbb samples with phase space cuts
void HforToolD3PD::keepAllRemoval()
////////////////////////////////////////////////////////
{
  if ((m_Quarks_GS[5].size() + m_Quarks_ME[5].size())>0) 
    m_result = "isBB";
  else if ((m_Quarks_GS[4].size() + m_Quarks_ME[4].size())>0)
    m_result = "isCC";
  else 
    m_result = "isLightFlavor";
}




/////////////////////////////////////////
// Do the angular based removal
void HforToolD3PD::angularBasedRemoval()
//////////////////////////////////////////
{
  
  // container to keep matched quarks
  // 0:GS  1:ME
  bool hasCC[2] = {false, false};
  bool hasBB[2] = {false, false};

  int match_bGS = matchdR(&m_Quarks_GS[5]);
  if (match_bGS > 0) hasBB[0] = true;

  int match_bME = matchdR(&m_Quarks_ME[5]);
  if (match_bME > 0) hasBB[1] = true;

  int match_cGS = matchdR(&m_Quarks_GS[4]);
  if (match_cGS > 0) hasCC[0] = true;

  int match_cME = matchdR(&m_Quarks_ME[4]);
  if (match_cME > 0) hasCC[1] = true;


  // light flavor samples
  if (m_sampleType == "isLightFlavor") {
    m_result = "isLightFlavor";

    if (!(m_isZinclusive || m_isbbOnly)) {
      // remove ME HF
      if ( (m_Quarks_ME[5].size()>0) || (m_Quarks_ME[4].size()>0) ) {
	m_result = "kill";
      } else if (m_Quarks_GS[5].size()>0) {
	// remove unmatched HF from GS
	if (hasBB[0])
	  m_result = "isBB";
	else 
	  m_result = "kill";
      } else if (m_Quarks_GS[4].size()>0) {
	// remove unmatched HF from GS
	if (hasCC[0])
	  m_result = "isCC";
	else 
	  m_result = "kill";
      }
    } else {

      // ======================================
      // special case for the Z inclusive  sample
      // we only have to remove overlap with Zbb samples

      // remove ME HF
      if (m_Quarks_ME[5].size()>0) {
	m_result = "kill";
      } else if (m_Quarks_GS[5].size()>0) {
	// remove unmatched HF from GS
	if (hasBB[0])
	  m_result = "isBB";
	else 
	  m_result = "kill";
      } else if ( (m_Quarks_GS[4].size() + m_Quarks_ME[4].size()) > 0) {
	// nothing to remove in case of c quarks
	m_result = "isCC";
      }
      // ==========================================
    }
  }

  // cc samples
  if (m_sampleType == "isCC") {
    m_result = "isCC";
    
    // remove matched ME HF
    if (hasCC[1])
      m_result = "kill";
    else if (hasBB[0])
      m_result = "isBB";
    else if (m_Quarks_GS[5].size()>0)
      m_result = "kill";

  }
  
  // c samples
  if (m_sampleType == "isC") {
    m_result = "isC";
    
    // remove matched ME HF
    if (hasCC[1])
      m_result = "kill";
    else if (hasBB[0])
      m_result = "isBB";
    else if (m_Quarks_GS[5].size()>0)
      m_result = "kill";

  }
  
  // bb samples - we only "promote" events,
  // therefore not c-quarks have to be considered
  if (m_sampleType == "isBB") {
    m_result = "isBB";

    // remove matched ME HF
    if (hasBB[1])
      m_result = "kill";
  }

}



///////////////////////////////////////////////
// Perform DeltaR matching between two quarks
int HforToolD3PD::matchdR(std::vector<TParticle>* quarks)
///////////////////////////////////////////////
{
  int match = 0;
  if (quarks->size() > 1) {
    for (unsigned int i=0; i<quarks->size(); i++) {
      for (unsigned int j=i+1; j<quarks->size(); j++) {
	double dR = deltaR(quarks->at(i), quarks->at(j));
	if (m_verbosity<=DEBUG) std::cout << "deltaR( " << i << " , " << j << " )= " << dR << std::endl;
	if (dR < m_matchingcone) {
	  ++match;
	}
      }
    }
  }
  return match;
}


////////////////////////////////////////////////
// Check which sample we are running over
bool HforToolD3PD::checkSampleType(int datasetNumber)
////////////////////////////////////////////////
{
  if(m_verbosity<=DEBUG) std::cout << "in checkSampleType" << std::endl;

  m_isZinclusive = false;

  // W inclusive samples
  if ( (datasetNumber >= 107680 && datasetNumber <= 107685)
       || (datasetNumber >= 107690 && datasetNumber <= 107695)
       || (datasetNumber >= 107700 && datasetNumber <= 107705)
       || (datasetNumber >= 144018 && datasetNumber <= 144020)
       || (datasetNumber >= 144196 && datasetNumber <= 144207)) {
    m_sampleType = "isLightFlavor";
    return true;
  }
  
  // Z inclusive samples
  if ( (datasetNumber >= 107650 && datasetNumber <= 107655)
       || (datasetNumber >= 107660 && datasetNumber <= 107665)
       || (datasetNumber >= 107670 && datasetNumber <= 107675) 
       || (datasetNumber >= 107710 && datasetNumber <= 107715)
       || (datasetNumber == 144017)
       || (datasetNumber >= 144192 && datasetNumber <= 144195)) {
    m_sampleType = "isLightFlavor";
    m_isZinclusive = true;
    return true;
  }

  if (datasetNumber >= 117288 && datasetNumber <= 117297) {
    m_sampleType = "isC";
    return true;
  }

  if (datasetNumber >= 117284 && datasetNumber <= 117287) {
    m_sampleType = "isCC";
    return true;
  }
  
  // Wbb samples
  if ( (datasetNumber >= 106280 && datasetNumber <= 106283)
       || (datasetNumber >= 107280 && datasetNumber <= 107283) ) {
    m_sampleType = "isBB";
    return true;
  }

  // Zbb samples
  if ( (datasetNumber >= 109300 && datasetNumber <= 109313) 
       || (datasetNumber >= 118962 && datasetNumber <= 118965) ) {
    m_sampleType = "isBB";
    return true;
  }

  // ttbar inclusive samples
  if ( (datasetNumber >= 105890 && datasetNumber <= 105897)
       || (datasetNumber >= 117887 && datasetNumber <= 117899) ){
    m_sampleType = "isLightFlavor";
    return true;
  }

  // ttbb sample
  if ( datasetNumber == 116108 ) {
    m_sampleType = "isBB";
    return true;
  }
  
  // ttcc sample
  if ( datasetNumber == 116109 ) {
    m_sampleType = "isCC";
    return true;
  }
  
  return false;

}
  


HforToolD3PD::~HforToolD3PD() {
}

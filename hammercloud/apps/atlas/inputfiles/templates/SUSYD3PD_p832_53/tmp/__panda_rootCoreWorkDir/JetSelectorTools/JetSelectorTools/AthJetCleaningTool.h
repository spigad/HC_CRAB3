// Dear emacs, this is -*-c++-*-

#ifndef __ATHJETCLEANINGTOOL__
#define __ATHJETCLEANINGTOOL__

/**
   @class AthJetCleaningTool
   @brief Tool to select objects in Athena using an underlying ARA and pure ROOT tool.

   @author Karsten Koeneke (CERN)
   @date   July 2011

*/

// Include the athena/ARA dual use wrapper
#include "AraTool/AraAlgToolWrapper.h"

// Include the AthenaRootAccess tool
#include "ARAJetCleaningTool.h"


class AthJetCleaningTool : public  AraAlgToolWrapper< ARAJetCleaningTool >
{

public: 
  /** Standard constructor */
  AthJetCleaningTool( const std::string& type,
                      const std::string& name,
                      const IInterface* parent )
    : AlgTool( type, name, parent ),
      AraAlgToolWrapper< ARAJetCleaningTool > ( type, name, parent )
  {
    AlgTool::declareInterface< ARAJetCleaningTool >(this);
  };

}; // End: class definition


#endif


// Dear emacs, this is -*-c++-*-

#ifndef __TSELECTORTOOLBASE__
#define __TSELECTORTOOLBASE__

/**
   @class TSelectorToolBase
   @brief Bsse class for tools to select objects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/

// Include the return object
#include "TAccept.h"


namespace Root {
  class TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TSelectorToolBase(const char* name="TSelectorToolBase") :
      m_name(name),
      m_accept( Form("%s_TAccept",name) )
    {
    }
    
    /** Standard destructor */
    virtual ~TSelectorToolBase(){}
  

    // Main methods
  public:
    /** Initialize this class */
    virtual int initialize() = 0;

    /** Finalize this class; everything that should be done after the event loop should go here */
    virtual int finalize() = 0;


    /** Get the name of the class instance */
    inline const char* getName() const { return m_name; };


    // Protected members
  protected:
    /** The name of the class instance */
    const char* m_name;

    /** The return TAccept object */
    TAccept m_accept;


  }; // End: class definition


} // End: namespace Root

#endif

// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XBOP_Area2dBuilder_HeaderFile
#define _XBOP_Area2dBuilder_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _XBOP_AreaBuilder_HeaderFile
#include <XBOP_AreaBuilder.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class XBOP_LoopSet;
class XBOP_LoopClassifier;



class XBOP_Area2dBuilder  : public XBOP_AreaBuilder {
public:

  void* operator new(size_t,void* anAddress) 
  {
    return anAddress;
  }
  void* operator new(size_t size) 
  {
    return Standard::Allocate(size); 
  }
  void  operator delete(void *anAddress) 
  {
    if (anAddress) Standard::Free((Standard_Address&)anAddress); 
  }

  
//! Empty  Constructor <br>
  Standard_EXPORT   XBOP_Area2dBuilder();
  
//! Creates an  object to build faces on <br>
//! the (wires,blocks of edge) of <LS>, <br>
//! using the classifier <LC>. <br>
  Standard_EXPORT   XBOP_Area2dBuilder(XBOP_LoopSet& LS,XBOP_LoopClassifier& LC,const Standard_Boolean ForceClass = Standard_False);
  
//! Initializes the object to find the areas of <br>
//! the shapes described by <LS>, <br>
//! using the classifier <LC>. <br>
  Standard_EXPORT   virtual  void InitAreaBuilder(XBOP_LoopSet& LS,XBOP_LoopClassifier& LC,const Standard_Boolean ForceClass = Standard_False) ;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif

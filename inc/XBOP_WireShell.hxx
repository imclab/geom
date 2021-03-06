// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XBOP_WireShell_HeaderFile
#define _XBOP_WireShell_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _XBOP_WireShape_HeaderFile
#include <XBOP_WireShape.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _TopAbs_ShapeEnum_HeaderFile
#include <TopAbs_ShapeEnum.hxx>
#endif
#ifndef _XBOP_Operation_HeaderFile
#include <XBOP_Operation.hxx>
#endif
class XBOPTools_DSFiller;



//!  The class to perform a Boolean Operations (BO) <br>
//!  Common,Cut,Fuse  between arguments when one of them is <br>
//!  a wire and other argument is a shell <br>
//! <br>
class XBOP_WireShell  : public XBOP_WireShape {
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

  
//! Empty constructor; <br>
  Standard_EXPORT   XBOP_WireShell();
  
//! See base classes, please <br>
  Standard_EXPORT   virtual  void Do() ;
  
//! See base classes, please <br>
  Standard_EXPORT   virtual  void DoWithFiller(const XBOPTools_DSFiller& aDSF) ;
  
//! Destructor <br>
  Standard_EXPORT   virtual  void Destroy() ;
Standard_EXPORT virtual ~XBOP_WireShell(){Destroy();}
  
//! See base classes, please <br>
  Standard_EXPORT   virtual  void BuildResult() ;
  
//! Check the types of arguments. <br>
//! Returns  FALSE if types of arguments <br>
//! are non-valid to be  treated by the <br>
//! agorithm <br>
  Standard_EXPORT   static  Standard_Boolean CheckArgTypes(const TopAbs_ShapeEnum theType1,const TopAbs_ShapeEnum theType2,const XBOP_Operation theOperation) ;





protected:





private:

  
//! Internal  usage <br>
  Standard_EXPORT     Standard_Boolean CheckArgTypes() const;




};





// other Inline functions and methods (like "C++: function call" methods)


#endif

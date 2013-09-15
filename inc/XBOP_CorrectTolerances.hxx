// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XBOP_CorrectTolerances_HeaderFile
#define _XBOP_CorrectTolerances_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
class TopoDS_Shape;



//!  The  Set  of  static functions to provide valid values of <br>
//!  tolerances for shapes. <br>
//!  Tolerances becomes valid in  terms of the checkshape. <br>
class XBOP_CorrectTolerances  {
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

  
//! Provides valid values of tolerances for the shape <aS> <br>
//! <aTolMax> is max value of the tolerance that can be <br>
//! accepted for correction.  If real value of the tolerance <br>
//! will be greater than  <aTolMax>, the correction does not <br>
//! perform. <br>
  Standard_EXPORT   static  void CorrectTolerances(const TopoDS_Shape& aS,const Standard_Real aTolMax = 0.0001) ;
  
//! Provides valid values of tolerances for the shape <aS> <br>
//! in  terms of BRepCheck_InvalidCurveOnSurface. <br>
  Standard_EXPORT   static  void CorrectCurveOnSurface(const TopoDS_Shape& aS,const Standard_Real aTolMax = 0.0001) ;
  
//! Provides valid values of tolerances for the shape <aS> <br>
//! in  terms of BRepCheck_InvalidPointOnCurve. <br>
  Standard_EXPORT   static  void CorrectPointOnCurve(const TopoDS_Shape& aS,const Standard_Real aTolMax = 0.0001) ;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif

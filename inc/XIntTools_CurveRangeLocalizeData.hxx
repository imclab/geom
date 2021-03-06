// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XIntTools_CurveRangeLocalizeData_HeaderFile
#define _XIntTools_CurveRangeLocalizeData_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _XIntTools_MapOfCurveSample_HeaderFile
#include <XIntTools_MapOfCurveSample.hxx>
#endif
#ifndef _XIntTools_DataMapOfCurveSampleBox_HeaderFile
#include <XIntTools_DataMapOfCurveSampleBox.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class XIntTools_CurveRangeSample;
class Bnd_Box;
class XIntTools_ListOfCurveRangeSample;



class XIntTools_CurveRangeLocalizeData  {
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

  
  Standard_EXPORT   XIntTools_CurveRangeLocalizeData(const Standard_Integer theNbSample,const Standard_Real theMinRange);
  
        Standard_Integer GetNbSample() const;
  
        Standard_Real GetMinRange() const;
  
  Standard_EXPORT     void AddOutRange(const XIntTools_CurveRangeSample& theRange) ;
  
  Standard_EXPORT     void AddBox(const XIntTools_CurveRangeSample& theRange,const Bnd_Box& theBox) ;
  
  Standard_EXPORT     Standard_Boolean FindBox(const XIntTools_CurveRangeSample& theRange,Bnd_Box& theBox) const;
  
  Standard_EXPORT     Standard_Boolean IsRangeOut(const XIntTools_CurveRangeSample& theRange) const;
  
  Standard_EXPORT     void ListRangeOut(XIntTools_ListOfCurveRangeSample& theList) const;





protected:





private:



Standard_Integer myNbSampleC;
Standard_Real myMinRangeC;
XIntTools_MapOfCurveSample myMapRangeOut;
XIntTools_DataMapOfCurveSampleBox myMapBox;


};


#include <XIntTools_CurveRangeLocalizeData.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif

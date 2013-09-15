// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XBOP_FaceBuilder_HeaderFile
#define _XBOP_FaceBuilder_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TopoDS_Face_HeaderFile
#include <TopoDS_Face.hxx>
#endif
#ifndef _XBOP_PWireEdgeSet_HeaderFile
#include <XBOP_PWireEdgeSet.hxx>
#endif
#ifndef _TopTools_ListOfShape_HeaderFile
#include <TopTools_ListOfShape.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _TColStd_SequenceOfInteger_HeaderFile
#include <TColStd_SequenceOfInteger.hxx>
#endif
#ifndef _Handle_XIntTools_Context_HeaderFile
#include <Handle_XIntTools_Context.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class XIntTools_Context;
class XBOP_WireEdgeSet;
class TopTools_ListOfShape;



//!   The  algorithm to   construct Faces from a WireEdgeSet <br>
//! <br>
class XBOP_FaceBuilder  {
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
  Standard_EXPORT   XBOP_FaceBuilder();
  
//! Launches the algorithm consisting of four steps <br>
//! 1.  Split the WES on wires <br>
//! 2.  Make Loops from wires <br>
//! 3.  Make Areas from Loops <br>
//! 4.  Make Faces from Areas <br>
//! Make Faces from Areas <br>
//! <br>
  Standard_EXPORT     void Do(const XBOP_WireEdgeSet& aWES,const Standard_Boolean aForceClass = Standard_True) ;
  
//! Sets intersection context <aCtx> <br>
  Standard_EXPORT     void SetContext(const Handle(XIntTools_Context)& aCtx) ;
  
//! Returns intersection context <br>
  Standard_EXPORT    const Handle_XIntTools_Context& Context() const;
  
//! Selector <br>
  Standard_EXPORT    const XBOP_WireEdgeSet& WES() const;
  
//! Selector <br>
  Standard_EXPORT    const TopTools_ListOfShape& NewFaces() const;
  
//! Modifier <br>
//! 0 -Treat internal edges, <br>
//! 1 -Do not treat internal edges <br>
  Standard_EXPORT     void SetTreatment(const Standard_Integer aTreatment) ;
  
//! Modifier <br>
//! 1 -Treat scale configured same domain faces, <br>
//! 0 -Do not treat them. <br>
//! <br>
//!    SetManifoldFlag(me: out; <br>
//!    	aMFlag:  Boolean from Standard); <br>
//! Modifier <br>
//! <br>
//!    ManifoldFlag(me) <br>
//!    	returns Boolean from Standard; <br>
//! Selector <br>
  Standard_EXPORT     void SetTreatSDScales(const Standard_Integer aTreatment) ;
  
//! Selector <br>
  Standard_EXPORT     Standard_Integer Treatment() const;
  
//! Selector <br>
//! <br>
//! <br>
//! Wires' iterator <br>
//! <br>
//!    InitWire(me:out) <br>
//!    	returns Integer from Standard; <br>
//! <br>
//! Make Loops from wires <br>
  Standard_EXPORT     Standard_Integer TreatSDScales() const;





protected:

  
//! Processes internal edges if they exists <br>
  Standard_EXPORT     void DoInternalEdges() ;
  
//! Treatment SD faces with a "scale" <br>
  Standard_EXPORT     void SDScales() ;
  
  Standard_EXPORT     void PerformAreas(XBOP_WireEdgeSet& SS) ;




private:



TopoDS_Face myFace;
XBOP_PWireEdgeSet myWES;
TopTools_ListOfShape myNewFaces;
Standard_Integer myTreatment;
Standard_Integer myTreatSDScales;
TColStd_SequenceOfInteger myNegatives;
Handle_XIntTools_Context myContext;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif

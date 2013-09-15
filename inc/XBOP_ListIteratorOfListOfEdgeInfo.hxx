// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XBOP_ListIteratorOfListOfEdgeInfo_HeaderFile
#define _XBOP_ListIteratorOfListOfEdgeInfo_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Handle_XBOP_ListNodeOfListOfEdgeInfo_HeaderFile
#include <Handle_XBOP_ListNodeOfListOfEdgeInfo.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class XBOP_ListOfEdgeInfo;
class XBOP_EdgeInfo;
class XBOP_ListNodeOfListOfEdgeInfo;



class XBOP_ListIteratorOfListOfEdgeInfo  {
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

  
  Standard_EXPORT   XBOP_ListIteratorOfListOfEdgeInfo();
  
  Standard_EXPORT   XBOP_ListIteratorOfListOfEdgeInfo(const XBOP_ListOfEdgeInfo& L);
  
  Standard_EXPORT     void Initialize(const XBOP_ListOfEdgeInfo& L) ;
  
        Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT     XBOP_EdgeInfo& Value() const;


friend class XBOP_ListOfEdgeInfo;



protected:





private:



Standard_Address current;
Standard_Address previous;


};

#define Item XBOP_EdgeInfo
#define Item_hxx <XBOP_EdgeInfo.hxx>
#define TCollection_ListNode XBOP_ListNodeOfListOfEdgeInfo
#define TCollection_ListNode_hxx <XBOP_ListNodeOfListOfEdgeInfo.hxx>
#define TCollection_ListIterator XBOP_ListIteratorOfListOfEdgeInfo
#define TCollection_ListIterator_hxx <XBOP_ListIteratorOfListOfEdgeInfo.hxx>
#define Handle_TCollection_ListNode Handle_XBOP_ListNodeOfListOfEdgeInfo
#define TCollection_ListNode_Type_() XBOP_ListNodeOfListOfEdgeInfo_Type_()
#define TCollection_List XBOP_ListOfEdgeInfo
#define TCollection_List_hxx <XBOP_ListOfEdgeInfo.hxx>

#include <TCollection_ListIterator.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_ListNode
#undef TCollection_ListNode_hxx
#undef TCollection_ListIterator
#undef TCollection_ListIterator_hxx
#undef Handle_TCollection_ListNode
#undef TCollection_ListNode_Type_
#undef TCollection_List
#undef TCollection_List_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif

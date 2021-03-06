// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XBOP_ListNodeOfListOfFaceInfo_HeaderFile
#define _XBOP_ListNodeOfListOfFaceInfo_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_XBOP_ListNodeOfListOfFaceInfo_HeaderFile
#include <Handle_XBOP_ListNodeOfListOfFaceInfo.hxx>
#endif

#ifndef _XBOP_FaceInfo_HeaderFile
#include <XBOP_FaceInfo.hxx>
#endif
#ifndef _TCollection_MapNode_HeaderFile
#include <TCollection_MapNode.hxx>
#endif
#ifndef _TCollection_MapNodePtr_HeaderFile
#include <TCollection_MapNodePtr.hxx>
#endif
class XBOP_FaceInfo;
class XBOP_ListOfFaceInfo;
class XBOP_ListIteratorOfListOfFaceInfo;



class XBOP_ListNodeOfListOfFaceInfo : public TCollection_MapNode {

public:

  
      XBOP_ListNodeOfListOfFaceInfo(const XBOP_FaceInfo& I,const TCollection_MapNodePtr& n);
  
        XBOP_FaceInfo& Value() const;




  DEFINE_STANDARD_RTTI(XBOP_ListNodeOfListOfFaceInfo)

protected:




private: 


XBOP_FaceInfo myValue;


};

#define Item XBOP_FaceInfo
#define Item_hxx <XBOP_FaceInfo.hxx>
#define TCollection_ListNode XBOP_ListNodeOfListOfFaceInfo
#define TCollection_ListNode_hxx <XBOP_ListNodeOfListOfFaceInfo.hxx>
#define TCollection_ListIterator XBOP_ListIteratorOfListOfFaceInfo
#define TCollection_ListIterator_hxx <XBOP_ListIteratorOfListOfFaceInfo.hxx>
#define Handle_TCollection_ListNode Handle_XBOP_ListNodeOfListOfFaceInfo
#define TCollection_ListNode_Type_() XBOP_ListNodeOfListOfFaceInfo_Type_()
#define TCollection_List XBOP_ListOfFaceInfo
#define TCollection_List_hxx <XBOP_ListOfFaceInfo.hxx>

#include <TCollection_ListNode.lxx>

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

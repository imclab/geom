// Created on: 2000-11-21
// Created by: Peter KURNEV
// Copyright (c) 2000-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.



#include <XBOPTools_VEInterference.ixx>

//=======================================================================
//function :  XBOPTools_VEInterference
//purpose  : 
//=======================================================================
XBOPTools_VEInterference::XBOPTools_VEInterference()
:
  XBOPTools_ShapeShapeInterference(0,0)
{}

//=======================================================================
//function :  XBOPTools_ESInterference
//purpose  : 
//=======================================================================
  XBOPTools_VEInterference::XBOPTools_VEInterference
  (const Standard_Integer anIndex1,
   const Standard_Integer anIndex2,
   const Standard_Real aT)
:  
  XBOPTools_ShapeShapeInterference(anIndex1,anIndex2),
  myParameter(aT)
{}

//=======================================================================
//function :  SetParameter
//purpose  : 
//=======================================================================
  void XBOPTools_VEInterference::SetParameter  (const Standard_Real aT)
{
  myParameter=aT;
}
//=======================================================================
//function :  Parameter
//purpose  : 
//=======================================================================
  Standard_Real XBOPTools_VEInterference::Parameter  ()const 
{
  return myParameter;
}

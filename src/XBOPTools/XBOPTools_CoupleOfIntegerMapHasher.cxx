// Created on: 2003-12-05
// Created by: Peter KURNEV
// Copyright (c) 2003-2012 OPEN CASCADE SAS
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



#include <XBOPTools_CoupleOfIntegerMapHasher.ixx>

//=======================================================================
//function : HashCode
//purpose  : 
//=======================================================================
Standard_Integer XBOPTools_CoupleOfIntegerMapHasher::HashCode(const XBOPTools_CoupleOfInteger& aPKey,
							       const Standard_Integer Upper)
{
  return aPKey.HashCode(Upper);
}
//=======================================================================
//function :IsEqual
//purpose  : 
//=======================================================================
  Standard_Boolean XBOPTools_CoupleOfIntegerMapHasher::IsEqual(const XBOPTools_CoupleOfInteger& aPKey1,
							      const XBOPTools_CoupleOfInteger& aPKey2)
{
  return aPKey1.IsEqual(aPKey2);
}

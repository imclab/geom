// Copyright (C) 2007-2013  CEA/DEN, EDF R&D, OPEN CASCADE
//
// Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//

// File:        NMTDS_Pair.hxx
// Author:      Peter KURNEV

#ifndef _NMTDS_Pair_HeaderFile
#define _NMTDS_Pair_HeaderFile

#include <Standard.hxx>
#include <Standard_Macro.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Boolean.hxx>

//=======================================================================
//function : NMTDS_Pair
//purpose  : 
//=======================================================================
class NMTDS_Pair  {
 public:
  Standard_EXPORT   
    NMTDS_Pair();

  Standard_EXPORT
    virtual ~NMTDS_Pair();
  
  Standard_EXPORT   
    NMTDS_Pair(const NMTDS_Pair& Other);

  Standard_EXPORT
    NMTDS_Pair& operator =(const NMTDS_Pair& Other);
  
  Standard_EXPORT
    void Clear() ;
  
  Standard_EXPORT
    void SetIds(const Standard_Integer aI1,
                const Standard_Integer aI2) ;
  
  Standard_EXPORT
    void Ids(Standard_Integer& aI1,
             Standard_Integer& aI2) const;
  
  Standard_EXPORT
    Standard_Boolean IsEqual(const NMTDS_Pair& aOther) const;
  
  Standard_EXPORT
    Standard_Integer HashCode(const Standard_Integer Upper) const;

protected:
Standard_Integer myId1;
Standard_Integer myId2;
};
#endif

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

// File:        NMTTools_PaveFiller_5.cxx
// Created:     Mon Dec 15 11:28:33 2003
// Author:      Peter KURNEV
//              <pkv@irinox>
//
#include <NMTTools_PaveFiller.hxx>

#include <TColStd_IndexedMapOfInteger.hxx>

#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>

#include <Bnd_Box.hxx>

#include <TopAbs_ShapeEnum.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Compound.hxx>

#include <TopExp.hxx>

#include <TopTools_IndexedMapOfShape.hxx>

#include <XIntTools_ShrunkRange.hxx>
#include <XIntTools_Range.hxx>
#include <XIntTools_EdgeFace.hxx>
#include <XIntTools_SequenceOfCommonPrts.hxx>
#include <XIntTools_CommonPrt.hxx>
#include <XIntTools_Tools.hxx>
#include <XIntTools_Context.hxx>

#include <XBooleanOperations_AncestorsSeqAndSuccessorsSeq.hxx>
#include <XBooleanOperations_IndexedDataMapOfShapeInteger.hxx>
#include <XBooleanOperations_OnceExplorer.hxx>

#include <XBOPTools_Tools.hxx>
#include <XBOPTools_Pave.hxx>
#include <XBOPTools_PaveSet.hxx>
#include <XBOPTools_ListOfPave.hxx>
#include <XBOPTools_ListIteratorOfListOfPave.hxx>
#include <XBOPTools_PaveBlock.hxx>
#include <XBOPTools_ListOfPaveBlock.hxx>
#include <XBOPTools_ListIteratorOfListOfPaveBlock.hxx>
#include <XBOPTools_ESInterference.hxx>

#include <XBOPTools_CArray1OfVVInterference.hxx>
#include <XBOPTools_CArray1OfESInterference.hxx>
#include <XBOPTools_VVInterference.hxx>
#include <XBOPTools_ESInterference.hxx>
#include <XBOPTools_IDMapOfPaveBlockIMapOfInteger.hxx>
#include <XBOPTools_IMapOfPaveBlock.hxx>
#include <BRepTools.hxx>

#include <NMTDS_ShapesDataStructure.hxx>
#include <NMTDS_Iterator.hxx>
#include <NMTDS_InterfPool.hxx>

#include <NMTTools_ListOfCommonBlock.hxx>
#include <NMTTools_CommonBlockAPI.hxx>
#include <NMTTools_IndexedDataMapOfIndexedMapOfInteger.hxx>
#include <NMTTools_CommonBlockAPI.hxx>
#include <NMTTools_ListOfCommonBlock.hxx>
#include <NMTTools_Tools.hxx>


static
  void VertexParameter(const XIntTools_CommonPrt& aCPart,
                       Standard_Real& aT);
static
  Standard_Boolean IsOnPave(const Standard_Real& aTR,
                            const XIntTools_Range& aCPRange,
                            const Standard_Real& aTolerance);
//
//=======================================================================
// function: PerformEF
// purpose:
//=======================================================================
  void NMTTools_PaveFiller::PerformEF()
{
  Standard_Boolean bJustAdd;
  Standard_Integer n1, n2, anIndexIn, nE, nF, aNbEFs, aBlockLength;
  Standard_Integer aDiscretize;
  Standard_Real aTolE, aTolF, aDeflection;
  XBooleanOperations_IndexedDataMapOfShapeInteger aMapVI;
  XBOPTools_IDMapOfPaveBlockIMapOfInteger aMapCB;
  XBOPTools_IMapOfPaveBlock aIMPBx;
  //
  myIsDone=Standard_False;
  aDeflection=0.01;
  aDiscretize=35;
  //
  XBOPTools_CArray1OfESInterference& aEFs=myIP->ESInterferences();
  //
  myDSIt->Initialize(TopAbs_EDGE, TopAbs_FACE);
  //
  // BlockLength correction
  aNbEFs=myDSIt->BlockLength();
  aBlockLength=aEFs.BlockLength();
  if (aNbEFs > aBlockLength) {
    aEFs.SetBlockLength(aNbEFs);
  }
  //
  for (; myDSIt->More(); myDSIt->Next()) {
    myDSIt->Current(n1, n2, bJustAdd);
    //
    if(bJustAdd) {
      continue;
    }
    //
    anIndexIn = 0;
    //
    nE=n1;
    nF=n2;
    if (myDS->GetShapeType(n2)==TopAbs_EDGE) {
      nE=n2;
      nF=n1;
    }
    //
    // all Common Blocks for face nF
    NMTTools_ListOfCommonBlock aLCBF;
    CommonBlocksFace(nF, aLCBF);
    NMTTools_CommonBlockAPI aCBAPIF(aLCBF);
    //
    // Edge
    const TopoDS_Edge aE=TopoDS::Edge(myDS->Shape(nE));
    if (NMTTools_Tools::IsDegenerated(aE)){
      continue;
    }
    //
    // Face
    const TopoDS_Face aF=TopoDS::Face(myDS->Shape(nF));
    //
    TopTools_IndexedMapOfShape aME;
    TopExp::MapShapes(aF, TopAbs_EDGE, aME);
    if (aME.Contains(aE)) {
      continue;
    }
    //
    aTolF=BRep_Tool::Tolerance(aF);
    aTolE=BRep_Tool::Tolerance(aE);

    const Bnd_Box& aBBF=myDS->GetBoundingBox(nF);
    //
    // Process each PaveBlock on edge nE
    XBOPTools_ListOfPaveBlock& aLPB=mySplitShapesPool(myDS->RefEdge(nE));
    //
    XBOPTools_ListIteratorOfListOfPaveBlock anIt(aLPB);
    for (; anIt.More(); anIt.Next()) {
      XBOPTools_PaveBlock& aPB=anIt.Value();
      if (aCBAPIF.IsCommonBlock(aPB)) {
        continue;
      }
      //
      const XIntTools_ShrunkRange& aShrunkRange=aPB.ShrunkRange();
      const XIntTools_Range& aSR =aShrunkRange.ShrunkRange();
      const Bnd_Box& aBBE=aShrunkRange.BndBox();
      //
      if (aBBF.IsOut (aBBE)) {
        continue;
      }
      //
      // EF
      XIntTools_EdgeFace aEF;
      aEF.SetEdge (aE);
      aEF.SetFace (aF);
      aEF.SetTolE (aTolE);
      aEF.SetTolF (aTolF);
      aEF.SetDiscretize (aDiscretize);
      aEF.SetDeflection (aDeflection);
      //
      aEF.SetContext(myContext);
      //
      XIntTools_Range anewSR = aSR;
      //
      // Correction of the Shrunk Range
      XBOPTools_Tools::CorrectRange(aE, aF, aSR, anewSR);
      aEF.SetRange (anewSR);
      //
      BRepTools::Write(aE, "/dn20/salome/skv/SALOME/scripts/Dumps/edge");
      BRepTools::Write(aF, "/dn20/salome/skv/SALOME/scripts/Dumps/face");
      aEF.Perform();
      //
      if (aEF.IsDone()) {
        Standard_Boolean bCoinsideFlag;
        Standard_Integer i, aNbCPrts;
        TopAbs_ShapeEnum aType;
        //
        const XIntTools_SequenceOfCommonPrts& aCPrts=aEF.CommonParts();
        //
        aNbCPrts=aCPrts.Length();
        for (i=1; i<=aNbCPrts; ++i) {
          anIndexIn=0;
          //
          const XIntTools_CommonPrt& aCPart=aCPrts(i);
          aType=aCPart.Type();
          //
          switch (aType) {
            //
            case TopAbs_VERTEX:  {
              Standard_Boolean bIsOnPave1, bIsOnPave2;
              Standard_Integer nVF;
              Standard_Real aT, aTolToDecide;
              TopoDS_Vertex aNewVertex;
              //
              const XIntTools_Range& aR=aCPart.Range1();
              //
              // New Vertex
              VertexParameter(aCPart, aT);
              XBOPTools_Tools::MakeNewVertex(aE, aT, aF, aNewVertex);
              //
              //decide to add pave or not
              aTolToDecide=5.e-8;
              bIsOnPave1=IsOnPave(anewSR.First(), aR, aTolToDecide);
              bIsOnPave2=IsOnPave(anewSR.Last() , aR, aTolToDecide);
              //
              if (!bIsOnPave1 && !bIsOnPave2) {
                nVF=CheckFacePaves(aNewVertex, nF);
                if (!nVF) {
                  // really new vertex
                  // Add Interference to the Pool
                  XBOPTools_ESInterference anInterf (nE, nF, aCPart);
                  anIndexIn=aEFs.Append(anInterf);
                  anInterf.SetNewShape(0);
                  //
                  aMapVI.Add(aNewVertex, anIndexIn);
                  aIMPBx.Add(aPB);
                  //
                  myIP->Add(nE, nF, Standard_True, NMTDS_TI_EF);
                  //
                }// if (!nVF)
              }// if (!bIsOnPave1 && !bIsOnPave2)
              //
              //modified by NIZNHY-PKV Fri Apr 18 10:55:38 2008f
              else {
                const XBOPTools_Pave& aPave=(bIsOnPave1)? aPB.Pave1() : aPB.Pave2();
                nVF=aPave.Index();
                const TopoDS_Vertex& aVF=TopoDS::Vertex(myDS->Shape(nVF));
                XBOPTools_Tools::UpdateVertex (aVF, aNewVertex);
              }
              //modified by NIZNHY-PKV Fri Apr 18 10:55:40 2008t
              //
            }// case TopAbs_VERTEX:
              break;
            //
            case TopAbs_EDGE: {
              bCoinsideFlag=XBOPTools_Tools::IsBlockInOnFace(aPB, aF, myContext);
              if (!bCoinsideFlag) {
                break;
              }
              //
              // Fill aMapCB
              if (aMapCB.Contains(aPB)) {
                TColStd_IndexedMapOfInteger& aMapF=aMapCB.ChangeFromKey(aPB);
                aMapF.Add(nF);
              }
              else {
                TColStd_IndexedMapOfInteger aMapF;
                aMapF.Add(nF);
                aMapCB.Add(aPB, aMapF);
              }
              //
              aIMPBx.Add(aPB);
              myIP->Add(nE, nF, Standard_True, NMTDS_TI_EF);
            }// case TopAbs_EDGE:
              break;

            default:
              break;
          } // switch (aType)
        } // for (i=1; i<=aNbCPrts; i++)
      } //if (aEF.IsDone())
    } // for (; anIt.More(); anIt.Next())
  }// for (; myDSIt.More(); myDSIt.Next())
  //
  // Treat New vertices
  EFNewVertices(aMapVI);
  //
  // Add draft Common Blocks of EF type
  EFCommonBlocks(aMapCB);
  //
  // Collect all CB we suspected to split by new vertices
  NMTTools_ListOfCommonBlock aLCBx;
  {
    Standard_Integer i, aNbPBx, nEx;
    XBOPTools_IMapOfPaveBlock aMx;
    //
    aNbPBx=aIMPBx.Extent();
    for (i=1; i<=aNbPBx; ++i) {
      const XBOPTools_PaveBlock& aPBx=aIMPBx(i);
      nEx=aPBx.OriginalEdge();
      NMTTools_ListOfCommonBlock& aLCB=myCommonBlockPool(myDS->RefEdge(nEx));
      if (aLCB.Extent()) {
        NMTTools_CommonBlockAPI aCBAPIx(aLCB);
        if (aCBAPIx.IsCommonBlock(aPBx)) {
          NMTTools_CommonBlock& aCBx=aCBAPIx.CommonBlock(aPBx);
          const XBOPTools_PaveBlock& aPB1=aCBx.PaveBlock1();
          if (!aMx.Contains(aPB1)){
            aMx.Add(aPB1);
            aLCBx.Append(aCBx);
          }
        }
      }
    }
  }
  //
  // Split the common blocks above
  if (aLCBx.Extent()) {
    ReplaceCommonBlocks(aLCBx);
  }
  //
  myIsDone=Standard_True;
}
//=======================================================================
// function:EFCommonBlocks
// purpose:
//=======================================================================
  void NMTTools_PaveFiller::EFCommonBlocks
    (const XBOPTools_IDMapOfPaveBlockIMapOfInteger& aMapCB)
{
  Standard_Integer i, aNbPB, nE, j, aNbF, nF;
  //
  aNbPB=aMapCB.Extent();
  for (i=1; i<=aNbPB; ++i) {
    const XBOPTools_PaveBlock& aPB=aMapCB.FindKey(i);
    const TColStd_IndexedMapOfInteger& aMapF=aMapCB.FindFromIndex(i);
    aNbF=aMapF.Extent();
    //
    nE=aPB.OriginalEdge();
    //
    NMTTools_ListOfCommonBlock& aLCB=myCommonBlockPool(myDS->RefEdge(nE));
    //
    NMTTools_CommonBlockAPI aCBAPI(aLCB);
    if (aCBAPI.IsCommonBlock(aPB)) {
      NMTTools_CommonBlock& aCB=aCBAPI.CommonBlock(aPB);
      for (j=1; j<=aNbF; ++j) {
        nF=aMapF(j);
        aCB.AddFace(nF);
      }
    }
    else {
      NMTTools_CommonBlock aCB;
      //
      aCB.AddPaveBlock(aPB);
      for (j=1; j<=aNbF; ++j) {
        nF=aMapF(j);
        aCB.AddFace(nF);
      }
      aLCB.Append(aCB);
    }
  }
}
//=======================================================================
// function:EFNewVertices
// purpose:
//=======================================================================
  void NMTTools_PaveFiller::EFNewVertices
    (const XBooleanOperations_IndexedDataMapOfShapeInteger& aMapVI)
{
  Standard_Integer i, j, aNb, aNewShape, aFlag, iX, aNbVV, aNbSimple;
  Standard_Integer aWhat, aWith, nE, nF, nV, aNbIEF, aNbEdges, iTmp;
  Standard_Real aT;
  TopoDS_Compound aCompound;
  TopoDS_Vertex aNewVertex;
  BRep_Builder aBB;
  XBOPTools_Pave aPave;
  NMTTools_IndexedDataMapOfIndexedMapOfInteger aMNVE, aMNVIEF;
  XBooleanOperations_AncestorsSeqAndSuccessorsSeq anASSeq;
  TopTools_IndexedMapOfShape aMNVComplex, aMNVSimple;
  //
  aNb=aMapVI.Extent();
  if (!aNb) { // no new vertices, no new problems
    return;
  }
  //
  XBOPTools_CArray1OfESInterference& aEFs=myIP->ESInterferences();
  //
  // 0.
  if (aNb==1) {
    aNewVertex=TopoDS::Vertex(aMapVI.FindKey(1));
    EFNewVertices(aNewVertex, aMapVI);
    return;
  }
  //
  // 1. Make compound from new vertices
  aBB.MakeCompound(aCompound);
  for (i=1; i<=aNb; ++i) {
    const TopoDS_Shape& aV=aMapVI.FindKey(i);
    aBB.Add(aCompound, aV);
  }
  //
  // 2. VV intersection between these vertices
  //       using the auxiliary Filler
  NMTTools_PaveFiller tPF;
  //
  tPF.SetCompositeShape(aCompound);
  //
  tPF.Init();
  tPF.PerformVV();
  //
  NMTDS_ShapesDataStructure& tDS=*(tPF.DS());
  NMTDS_InterfPool& tInterfPool=*(tPF.IP());
  XBOPTools_CArray1OfVVInterference& aVVInterfs=tInterfPool.VVInterferences();
  //
  // 3. Separate Comlex and Simple new vertices
  aNbVV=aVVInterfs.Extent();
   for (i=1; i<=aNbVV; ++i) {
    const XBOPTools_VVInterference& aVV=aVVInterfs(i);
    aVV.Indices(aWhat, aWith);
    const TopoDS_Shape& aV1=tDS.Shape(aWhat);
    const TopoDS_Shape& aV2=tDS.Shape(aWith);
    aMNVComplex.Add(aV1);
    aMNVComplex.Add(aV2);
  }
  //
  for (i=1; i<=aNb; ++i) {
    const TopoDS_Shape& aV=aMapVI.FindKey(i);
    if (!aMNVComplex.Contains(aV)) {
      aMNVSimple.Add(aV);
    }
  }
  //
  // 4. Treat Simple new Vertices
  aNbSimple=aMNVSimple.Extent();
  for (i=1; i<=aNbSimple; ++i) {
    const TopoDS_Vertex& aV=TopoDS::Vertex(aMNVSimple(i));
    EFNewVertices(aV, aMapVI);
  }
  //
  // 3. Fill Maps : NewVertex-edges (aMNVE)
  //                NewVertex-interferences (aMNVIEE)
  aNb=aVVInterfs.Extent();
  for (i=1; i<=aNb; ++i) {
    const XBOPTools_VVInterference& aVV=aVVInterfs(i);
    aNewShape=aVV.NewShape();
    if (!aNewShape) {
      continue;
    }
    //
    if (!aMNVE.Contains(aNewShape)) {
      TColStd_IndexedMapOfInteger aMx;
      aMNVE.Add(aNewShape, aMx);
    }
    if (!aMNVIEF.Contains(aNewShape)) {
      TColStd_IndexedMapOfInteger aMx;
      aMNVIEF.Add(aNewShape, aMx);
    }
    //
    TColStd_IndexedMapOfInteger& aME=aMNVE.ChangeFromKey(aNewShape);
    TColStd_IndexedMapOfInteger& aMIEF=aMNVIEF.ChangeFromKey(aNewShape);
    //
    aVV.Indices(aWhat, aWith);
    //aWhat
    const TopoDS_Shape& aV1=tDS.Shape(aWhat);
    iX=aMapVI.FindFromKey(aV1);
    const XBOPTools_ESInterference& aEF1=aEFs(iX);
    aEF1.Indices(nE, nF);
    //
    if (myDS->GetShapeType(nF)==TopAbs_EDGE) {
      iTmp=nE;
      nE=nF;
      nF=iTmp;
    }
    aME.Add(nE);
    aMIEF.Add(iX);
    //aWith
    const TopoDS_Shape& aV2=tDS.Shape(aWith);
    iX=aMapVI.FindFromKey(aV2);
    const XBOPTools_ESInterference& aEF2=aEFs(iX);
    aEF2.Indices(nE, nF);
    //
    if (myDS->GetShapeType(nF)==TopAbs_EDGE) {
      iTmp=nE;
      nE=nF;
      nF=iTmp;
    }
    aME.Add(nE);
    aMIEF.Add(iX);
  }// for (i=1; i<=aNb; ++i) {
  //
  // 4. Process new vertices
  aNb=aMNVE.Extent();
  for (i=1; i<=aNb; ++i) { // xx
    //
    //  new Vertex
    nV=aMNVE.FindKey(i);
    aNewVertex=TopoDS::Vertex(tDS.Shape(nV));
    //
    // Insert New Vertex in DS;
    myDS->InsertShapeAndAncestorsSuccessors(aNewVertex, anASSeq);
    aNewShape=myDS->NumberOfInsertedShapes();
    myDS->SetState (aNewShape, XBooleanOperations_ON);
    //
    // Update index of NewShape in EF interferences
    const TColStd_IndexedMapOfInteger& aMIEF=aMNVIEF.FindFromKey(nV);
    aNbIEF=aMIEF.Extent();
    for (j=1; j<=aNbIEF; ++j) {
      iX=aMIEF(j);
      XBOPTools_ESInterference& aEF=aEFs(iX);
      aEF.SetNewShape(aNewShape);
    }
    //
    // Update Paves on all edges
    const TColStd_IndexedMapOfInteger& aME=aMNVE(i);
    aNbEdges=aME.Extent();
    for (j=1; j<=aNbEdges; ++j) {
      nE=aME(j);
      const TopoDS_Edge aE=TopoDS::Edge(myDS->Shape(nE));//mpv
      //
      aFlag=myContext->ComputeVE (aNewVertex, aE, aT);
      //
      if (!aFlag) {
        aPave.SetInterference(-1);
        aPave.SetType (XBooleanOperations_EdgeSurface);
        aPave.SetIndex(aNewShape);
        aPave.SetParam(aT);
        //
        XBOPTools_PaveSet& aPaveSet=myPavePoolNew(myDS->RefEdge(nE));
        aPaveSet.Append(aPave);
      }
    }
  }
}
//=======================================================================
// function:EFNewVertices
// purpose:
//=======================================================================
  void NMTTools_PaveFiller::EFNewVertices
    (const TopoDS_Vertex& aNewVertex,
     const XBooleanOperations_IndexedDataMapOfShapeInteger& aMapVI)
{
  Standard_Integer i, aNewShape, nE, nF;
  Standard_Real aT;
  XBOPTools_Pave aPave;
  XBooleanOperations_AncestorsSeqAndSuccessorsSeq anASSeq;
  //
  XBOPTools_CArray1OfESInterference& aEFs=myIP->ESInterferences();
  //
  // Insert New Vertex in DS;
  myDS->InsertShapeAndAncestorsSuccessors(aNewVertex, anASSeq);
  aNewShape=myDS->NumberOfInsertedShapes();
  myDS->SetState (aNewShape, XBooleanOperations_ON);
  //
  // Insert New Vertex in EFInterference
  i=aMapVI.FindFromKey(aNewVertex);
  XBOPTools_ESInterference& aEFInterf= aEFs(i);
  aEFInterf.SetNewShape(aNewShape);
  // Extract interference info
  aEFInterf.Indices(nE, nF);
  if (myDS->GetShapeType(nF)==TopAbs_EDGE) {
    nE=nF;
  }
  const XIntTools_CommonPrt& aCPart=aEFInterf.CommonPrt();
  VertexParameter(aCPart, aT);
  //
  // Pave for edge nE
  aPave.SetInterference(i);
  aPave.SetType (XBooleanOperations_EdgeSurface);
  aPave.SetIndex(aNewShape);
  aPave.SetParam(aT);
  // Append the Pave to the myPavePoolNew
  XBOPTools_PaveSet& aPaveSet=myPavePoolNew(myDS->RefEdge(nE));
  aPaveSet.Append(aPave);
  //
}
//=======================================================================
// function: CheckFacePaves
// purpose:
//=======================================================================
  Standard_Integer NMTTools_PaveFiller::CheckFacePaves
    (const TopoDS_Vertex& aNewVertex,
     const Standard_Integer nF)
{
  Standard_Integer nEF, nVF, iFlag, i, aNbV, iRet;
  XBOPTools_ListIteratorOfListOfPave anIt;
  TColStd_IndexedMapOfInteger aMVF;
  //
  iRet=0;
  //
  XBooleanOperations_OnceExplorer aExp(*myDS);
  aExp.Init(nF, TopAbs_EDGE);
  for (; aExp.More(); aExp.Next()) {
    nEF=aExp.Current();
    XBOPTools_PaveSet& aPaveSet=myPavePool(myDS->RefEdge(nEF));
    const XBOPTools_ListOfPave& aLP=aPaveSet.Set();
    anIt.Initialize(aLP);
    for (; anIt.More(); anIt.Next()) {
      const XBOPTools_Pave& aPave=anIt.Value();
      nVF=aPave.Index();
      aMVF.Add(nVF);
    }
  }
  //
  aNbV=aMVF.Extent();
  for (i=1; i<=aNbV; ++i) {
    nVF=aMVF(i);
    const TopoDS_Vertex aVF=TopoDS::Vertex(myDS->Shape(nVF));
    iFlag=XIntTools_Tools::ComputeVV(aNewVertex, aVF);
    if (!iFlag) {
      return nVF;
    }
  }
  return iRet;
}
//
//=======================================================================
// function: VertexParameter
// purpose:
//=======================================================================
void VertexParameter(const XIntTools_CommonPrt& aCPart,
                     Standard_Real& aT)
{
  const XIntTools_Range& aR=aCPart.Range1();
  aT=0.5*(aR.First()+aR.Last());
  if((aCPart.VertexParameter1() >= aR.First()) &&
     (aCPart.VertexParameter1() <= aR.Last())) {
    aT = aCPart.VertexParameter1();
  }
}
//=======================================================================
// function: IsOnPave
// purpose:
//=======================================================================
Standard_Boolean IsOnPave(const Standard_Real& aTR,
                          const XIntTools_Range& aCPRange,
                          const Standard_Real& aTolerance)
{
  Standard_Boolean bIsOnPave;
  Standard_Real aT1, aT2, dT1, dT2;
  //
  aT1=aCPRange.First();
  aT2=aCPRange.Last();
  bIsOnPave=(aTR>=aT1 && aTR<=aT1);
  if (bIsOnPave) {
    return bIsOnPave;
  }
  //
  dT1=Abs(aTR-aT1);
  dT2=Abs(aTR-aT2);
  bIsOnPave=(dT1<=aTolerance || dT2<=aTolerance);
  return bIsOnPave;
}

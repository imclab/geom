// Copyright (c) 1999-2012 OPEN CASCADE SAS
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

#include <XIntTools_TopolTool.ixx>

#include <Standard_NotImplemented.hxx>
#include <Precision.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>
#include <gp_Circ.hxx>
#include <gp_Cone.hxx>
#include <ElSLib.hxx>

#include <TColStd_HArray1OfReal.hxx>

static void Analyse(const TColgp_Array2OfPnt& array2,
		    Standard_Integer&         theNbSamplesU,
		    Standard_Integer&         theNbSamplesV);

// =====================================================================================
// function: Constructor
// purpose:
// =====================================================================================
XIntTools_TopolTool::XIntTools_TopolTool()
{
  myNbSmplU = 0;
  myNbSmplV = 0;
  myDU = 1.;
  myDV = 1.;
}

// =====================================================================================
// function: Constructor
// purpose:
// =====================================================================================
XIntTools_TopolTool::XIntTools_TopolTool(const Handle(Adaptor3d_HSurface)& theSurface)
{
  Initialize(theSurface);
  myNbSmplU = 0;
  myNbSmplV = 0;
  myDU = 1.;
  myDV = 1.;
}

// =====================================================================================
// function: Initialize
// purpose:
// =====================================================================================
void XIntTools_TopolTool::Initialize() 
{
  Standard_NotImplemented::Raise("XIntTools_TopolTool::Initialize ()");
}

// =====================================================================================
// function: Initialize
// purpose:
// =====================================================================================
void XIntTools_TopolTool::Initialize(const Handle(Adaptor3d_HSurface)& theSurface) 
{
  Adaptor3d_TopolTool::Initialize(theSurface);
  //myS = theSurface;
  myNbSmplU = 0;
  myNbSmplV = 0;
  myDU = 1.;
  myDV = 1.;
}

// =====================================================================================
// function: ComputeSamplePoints
// purpose:
// =====================================================================================
void XIntTools_TopolTool::ComputeSamplePoints() 
{
  Standard_Real uinf, usup, vinf, vsup;
  uinf = myS->FirstUParameter();  
  usup = myS->LastUParameter();
  vinf = myS->FirstVParameter();  
  vsup = myS->LastVParameter();
  const Standard_Integer aMaxNbSample = 50;

  if (usup < uinf) { Standard_Real temp = uinf; uinf = usup; usup = temp; }
  if (vsup < vinf) { Standard_Real temp = vinf; vinf = vsup; vsup = temp; }
  Standard_Boolean isbiguinf, isbigusup, isbigvinf, isbigvsup;
  isbiguinf = Precision::IsNegativeInfinite(uinf);
  isbigusup = Precision::IsPositiveInfinite(usup);
  isbigvinf = Precision::IsNegativeInfinite(vinf);
  isbigvsup = Precision::IsPositiveInfinite(vsup);

  if(isbiguinf && isbigusup) {uinf = -1.e5; usup = 1.e5;}
  else if(isbiguinf) {uinf = usup - 2.e5;}
  else if(isbigusup) {usup = uinf + 2.e5;}

  if(isbigvinf && isbigvsup) {vinf = -1.e5; vsup = 1.e5;}
  else if(isbigvinf) {vinf = vsup - 2.e5;}
  else if(isbigvsup) {vsup = vinf + 2.e5;}
  myU0 = uinf;
  myV0 = vinf;

  Standard_Integer nbsu,nbsv;
  GeomAbs_SurfaceType typS = myS->GetType();

  switch(typS) {
  case GeomAbs_Plane: { 
    nbsu = 10; nbsv = 10;
  }
    break;
  case GeomAbs_Cylinder: {
    Standard_Real aRadius = myS->Cylinder().Radius();
    Standard_Real aMaxAngle = M_PI * 0.5;
    Standard_Real aDeflection = 1.e-02;

    if(aRadius > aDeflection) {
      aMaxAngle = ACos(1. - aDeflection / aRadius) * 2.;
    }
    if(aMaxAngle > Precision::Angular()) {
      nbsu = Standard_Integer((usup-uinf) / aMaxAngle);
    }
    nbsv = (Standard_Integer)(vsup-vinf);
    nbsv /= 10;

    if(nbsu < 2) nbsu = 2;
    if(nbsv < 2) nbsv = 2;

//    if(nbsu < 10) nbsu = 10;
//    if(nbsv < 10) nbsv = 10;
    if(nbsu > aMaxNbSample) nbsu = aMaxNbSample;
    if(nbsv > aMaxNbSample) nbsv = aMaxNbSample;
  }
    break;
  case GeomAbs_Cone: {
    gp_Cone aCone = myS->Cone();
    gp_Circ aCircle = ElSLib::ConeVIso(aCone.Position(), aCone.RefRadius(), aCone.SemiAngle(), vinf);
    Standard_Real aRadius = aCircle.Radius();
    aCircle = ElSLib::ConeVIso(aCone.Position(), aCone.RefRadius(), aCone.SemiAngle(), vsup);

    if(aRadius < aCircle.Radius())
      aRadius = aCircle.Radius();
    Standard_Real aMaxAngle = M_PI * 0.5;
    Standard_Real aDeflection = 1.e-02;

    if(aRadius > aDeflection) {
      aMaxAngle = ACos(1. - aDeflection / aRadius) * 2.;
    }

    if(aMaxAngle > Precision::Angular()) {
      nbsu = Standard_Integer((usup - uinf) / aMaxAngle);
    }
    nbsv = (Standard_Integer)(vsup - vinf);
    nbsv /= 10;

//     if(nbsu < 2) nbsu = 2;
//     if(nbsv < 2) nbsv = 2;

    if(nbsu < 10) nbsu = 10;
    if(nbsv < 10) nbsv = 10;
    if(nbsu > aMaxNbSample) nbsu = aMaxNbSample;
    if(nbsv > aMaxNbSample) nbsv = aMaxNbSample;
  }
    break;
  case GeomAbs_Sphere:
  case GeomAbs_Torus: {
    gp_Circ aCircle;
    Standard_Real aRadius1, aRadius2;

    if(typS == GeomAbs_Torus) {
      gp_Torus aTorus = myS->Torus();
      aCircle = ElSLib::TorusUIso(aTorus.Position(), aTorus.MajorRadius(), aTorus.MinorRadius(), uinf);
      aRadius2 = aCircle.Radius();
      aCircle = ElSLib::TorusUIso(aTorus.Position(), aTorus.MajorRadius(), aTorus.MinorRadius(), usup);
      aRadius2 = (aRadius2 < aCircle.Radius()) ? aCircle.Radius() : aRadius2;
      
      aCircle = ElSLib::TorusVIso(aTorus.Position(), aTorus.MajorRadius(), aTorus.MinorRadius(), vinf);
      aRadius1 = aCircle.Radius();
      aCircle = ElSLib::TorusVIso(aTorus.Position(), aTorus.MajorRadius(), aTorus.MinorRadius(), vsup);
      aRadius1 = (aRadius1 < aCircle.Radius()) ? aCircle.Radius() : aRadius1;
    }
    else {
      gp_Sphere aSphere = myS->Sphere();
      aRadius1 = aSphere.Radius();
      aRadius2 = aSphere.Radius();
    }
    Standard_Real aMaxAngle = M_PI * 0.5;
    Standard_Real aDeflection = 1.e-02;
    
    if(aRadius1 > aDeflection) {
      aMaxAngle = ACos(1. - aDeflection / aRadius1) * 2.;
    }
    
    if(aMaxAngle > Precision::Angular()) {
      nbsu = Standard_Integer((usup - uinf) / aMaxAngle);
    }
    aMaxAngle = M_PI * 0.5;

    if(aRadius2 > aDeflection) {
      aMaxAngle = ACos(1. - aDeflection / aRadius2) * 2.;
    }
    
    if(aMaxAngle > Precision::Angular()) {
      nbsv = Standard_Integer((vsup - vinf) / aMaxAngle);
    }
    if(nbsu < 10) nbsu = 10;
    if(nbsv < 10) nbsv = 10;
    if(nbsu > aMaxNbSample) nbsu = aMaxNbSample;
    if(nbsv > aMaxNbSample) nbsv = aMaxNbSample;
  }
    break;
  case GeomAbs_BezierSurface: {
    nbsv = 3 + myS->NbVPoles(); 
    nbsu = 3 + myS->NbUPoles();

    if(nbsu > 10 || nbsv > 10) {
      TColgp_Array2OfPnt array2(1, myS->NbUPoles(), 1, myS->NbVPoles());
      myS->Bezier()->Poles(array2);
      Analyse(array2, nbsu, nbsv);
    }

    if(nbsu < 10) nbsu = 10;
    if(nbsv < 10) nbsv = 10;
  }
    break;
  case GeomAbs_BSplineSurface: {
    nbsv = myS->NbVKnots();     nbsv *= myS->VDegree();     if(nbsv < 4) nbsv=4;    
    nbsu = myS->NbUKnots();     nbsu *= myS->UDegree();     if(nbsu < 4) nbsu=4;
    
    if(nbsu > 10 || nbsv > 10) {
      TColgp_Array2OfPnt array2(1, myS->NbUPoles(), 1, myS->NbVPoles());
      myS->BSpline()->Poles(array2);
      Analyse(array2, nbsu, nbsv);
    }
    if(nbsu < 10) nbsu = 10;
    if(nbsv < 10) nbsv = 10;
  }
    break;
  case GeomAbs_SurfaceOfExtrusion: {
    nbsu = 15;
    nbsv = (Standard_Integer)(vsup - vinf);
    nbsv /= 10;
    if(nbsv < 15) nbsv = 15;
    if(nbsv > aMaxNbSample) nbsv = aMaxNbSample;
  }
    break;
  case GeomAbs_SurfaceOfRevolution: {
    nbsv = 15; nbsu = 15;
  }
    break;
  default: {
    nbsu = 10; nbsv = 10;
  }
    break;
  }
  myNbSmplU = nbsu;
  myNbSmplV = nbsv;

  myNbSamplesU = myNbSmplU;
  myNbSamplesV = myNbSmplV;

  myDU = (usup - uinf)/(myNbSmplU + 1);
  myDV = (vsup - vinf)/(myNbSmplV + 1);
}

// =====================================================================================
// function: NbSamplesU
// purpose:
// =====================================================================================
Standard_Integer XIntTools_TopolTool::NbSamplesU() 
{
  if(myNbSmplU <= 0) {
    ComputeSamplePoints();
  }
  return myNbSmplU;
}

// =====================================================================================
// function: NbSamplesV
// purpose:
// =====================================================================================
Standard_Integer XIntTools_TopolTool::NbSamplesV() 
{
  if(myNbSmplV <= 0) {
    ComputeSamplePoints();
  }
  return myNbSmplV;
}

// =====================================================================================
// function: NbSamples
// purpose:
// =====================================================================================
Standard_Integer XIntTools_TopolTool::NbSamples() 
{
  if(myNbSmplU <= 0) { 
    ComputeSamplePoints();    
  }
  return(myNbSmplU * myNbSmplV);
}

// =====================================================================================
// function: SamplePoint
// purpose:
// =====================================================================================
void XIntTools_TopolTool::SamplePoint(const Standard_Integer Index,
				     gp_Pnt2d&              P2d,
				     gp_Pnt&                P3d) 
{
  if (myUPars.IsNull())
    {
      if(myNbSmplU <= 0) { 
	ComputeSamplePoints();    
      }
      Standard_Integer iv = 1 + Index / myNbSmplU;
      Standard_Integer iu = 1 + Index - (iv - 1) * myNbSmplU;
      Standard_Real u = myU0 + iu * myDU;
      Standard_Real v = myV0 + iv * myDV;
      P2d.SetCoord(u, v);
      P3d = myS->Value(u, v);
    }
  else
    Adaptor3d_TopolTool::SamplePoint(Index, P2d, P3d);
}


//=======================================================================
// function : Analyse
// purpose  : 
//=======================================================================
void Analyse(const TColgp_Array2OfPnt& array2,
	     Standard_Integer&         theNbSamplesU,
	     Standard_Integer&         theNbSamplesV) 
{ 
  gp_Vec Vi,Vip1;
  Standard_Integer sh,nbch,i,j;
  const Standard_Integer nbup = array2.UpperRow() - array2.LowerRow() + 1;
  const Standard_Integer nbvp = array2.UpperCol() - array2.LowerCol() + 1;
  
  sh = 1;
  nbch = 0;
  if(nbvp>2) {

    for(i = array2.LowerRow(); i <= array2.UpperRow(); i++) {
      const gp_Pnt& A=array2.Value(i,1);
      const gp_Pnt& B=array2.Value(i,2);
      const gp_Pnt& C=array2.Value(i,3);
      Vi.SetCoord(C.X()-B.X()-B.X()+A.X(),
		  C.Y()-B.Y()-B.Y()+A.Y(),
		  C.Z()-B.Z()-B.Z()+A.Z());
      Standard_Integer locnbch=0;

      for(j = array2.LowerCol() + 2; j < array2.UpperCol();j++) {  //-- essai
	const gp_Pnt& Ax=array2.Value(i,j-1);
	const gp_Pnt& Bx=array2.Value(i,j);
	const gp_Pnt& Cx=array2.Value(i,j+1);
	Vip1.SetCoord(Cx.X()-Bx.X()-Bx.X()+Ax.X(),
		      Cx.Y()-Bx.Y()-Bx.Y()+Ax.Y(),
		      Cx.Z()-Bx.Z()-Bx.Z()+Ax.Z());
	Standard_Real pd = Vi.Dot(Vip1);
	Vi=Vip1;
	if(pd>1.0e-7 || pd<-1.0e-7) {  
	  if(pd>0) {  if(sh==-1) {   sh=1; locnbch++; 	}  }
	  else { 	if(sh==1) {  sh=-1; locnbch++; 	}  }
	}
      }
      if(locnbch>nbch) { 
	nbch=locnbch; 
      }
    }
  }
  theNbSamplesV = nbch+5;
  

  nbch=0;
  if(nbup > 2) { 
    for(j = array2.LowerCol(); j <= array2.UpperCol(); j++) { 
      const gp_Pnt& A=array2.Value(array2.LowerRow(),     j);
      const gp_Pnt& B=array2.Value(array2.LowerRow() + 1, j);
      const gp_Pnt& C=array2.Value(array2.LowerRow() + 2, j);
      Vi.SetCoord(C.X()-B.X()-B.X()+A.X(),
		  C.Y()-B.Y()-B.Y()+A.Y(),
		  C.Z()-B.Z()-B.Z()+A.Z());
      Standard_Integer locnbch=0;

      for(i = array2.LowerRow() + 2; i < array2.UpperRow(); i++) {  //-- essai
	const gp_Pnt& Ax=array2.Value(i-1,j);
	const gp_Pnt& Bx=array2.Value(i,j);
	const gp_Pnt& Cx=array2.Value(i+1,j);
	Vip1.SetCoord(Cx.X()-Bx.X()-Bx.X()+Ax.X(),
		    Cx.Y()-Bx.Y()-Bx.Y()+Ax.Y(),
		    Cx.Z()-Bx.Z()-Bx.Z()+Ax.Z());
	Standard_Real pd = Vi.Dot(Vip1);
	Vi=Vip1;
	if(pd>1.0e-7 || pd<-1.0e-7) {  
	  if(pd>0) {  if(sh==-1) {   sh=1; locnbch++; 	}  }
	  else { 	if(sh==1) {  sh=-1; locnbch++; 	}  }
	}
      }
      if(locnbch>nbch) nbch=locnbch;
    }  
  }
  theNbSamplesU = nbch+5;
}

//Modified IFV
//=======================================================================
//function : SamplePnts
//purpose  : 
//=======================================================================

void XIntTools_TopolTool::SamplePnts(const Standard_Real theDefl, 
				    const Standard_Integer theNUmin,
				    const Standard_Integer theNVmin)
{ 
  Adaptor3d_TopolTool::SamplePnts(theDefl, theNUmin, theNVmin);

  myNbSmplU = Adaptor3d_TopolTool::NbSamplesU();
  myNbSmplV = Adaptor3d_TopolTool::NbSamplesV();

  myU0 = myUPars->Value(1);
  myV0 = myVPars->Value(1);

  myDU = (myUPars->Value(myNbSmplU) - myU0)/(myNbSmplU-1);  
  myDV = (myVPars->Value(myNbSmplV) - myU0)/(myNbSmplV-1);
}

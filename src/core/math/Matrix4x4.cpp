#include "Matrix4x4.h"
#include "MathHelper.h"
#include "math.h"


//-----------------------------------------------------------------------------------
Matrix4x4::Matrix4x4()
{
	SetIdentity();
}

//-----------------------------------------------------------------------------------
void Matrix4x4::SetIdentity()
{
	Set(0,0, 1.0f);  Set(1,0, 0.0f);  Set(2,0, 0.0f);  Set(3,0, 0.0f);
	Set(0,1, 0.0f);  Set(1,1, 1.0f);  Set(2,1, 0.0f);  Set(3,1, 0.0f);
	Set(0,2, 0.0f);  Set(1,2, 0.0f);  Set(2,2, 1.0f);  Set(3,2, 0.0f);
	Set(0,3, 0.0f);  Set(1,3, 0.0f);  Set(2,3, 0.0f);  Set(3,3, 1.0f);
}

//-----------------------------------------------------------------------------------
float Matrix4x4::Get(int iColumn, int iRow)
{
	return mMatrix[ (iRow*4) + iColumn ];
}

//-----------------------------------------------------------------------------------
void Matrix4x4::Set(int iColumn, int iRow, float fValue)
{
	mMatrix[ (iRow*4) + iColumn ] = fValue;
}

//-----------------------------------------------------------------------------------
Matrix4x4 Matrix4x4::operator *(float fScalar)
{
	Matrix4x4 matResult;

	for( int iRow = 0; iRow < 4; ++iRow)
	{
		for(int iColumn = 0; iColumn < 4; ++iColumn)
		{
			float fVal = Get(iColumn, iRow);
			fVal *= fScalar;
			Set(iColumn, iRow, fVal);
		}
	}

	return matResult;
}

//-----------------------------------------------------------------------------------
Matrix4x4 Matrix4x4::operator *(Matrix4x4 other)
{
	Matrix4x4 matResult;

	const int iDim = 4;

	Vector4 myRow[iDim];
	Vector4 otherCol[iDim];
	for(int i=0; i<iDim; ++i)
	{
		myRow[i] = GetRow(i);
		otherCol[i] = other.GetColumn(i);
	}

	for(int row = 0; row < iDim; ++row )
	{
		float dots[iDim];
		dots[0] = Vector4::Dot( myRow[row], otherCol[0] );
		dots[1] = Vector4::Dot( myRow[row], otherCol[1] );
		dots[2] = Vector4::Dot( myRow[row], otherCol[2] );
		dots[3] = Vector4::Dot( myRow[row], otherCol[3] );

		matResult.SetRow(row, Vector4(dots));
	}


	return matResult;
}

//-----------------------------------------------------------------------------------
Vector4 Matrix4x4::operator *(Vector4 vec)
{
	Vector4 vecResult;
	
	vecResult.x( Vector4::Dot( vec, this->GetColumn(0)) );
	vecResult.y( Vector4::Dot( vec, this->GetColumn(1)) );
	vecResult.z( Vector4::Dot( vec, this->GetColumn(2)) );
	vecResult.w( Vector4::Dot( vec, this->GetColumn(3)) );


	return vecResult;
}

//-----------------------------------------------------------------------------------
Vector4 Matrix4x4::GetColumn(int iColumn)
{
	Vector4 vec(Get(iColumn, 0), Get(iColumn, 1), Get(iColumn, 2), Get(iColumn, 3));
	return vec;
}

//-----------------------------------------------------------------------------------
void Matrix4x4::SetColumn(int iColumn, Vector4 vec)
{
	Set(iColumn,0, vec.x());
	Set(iColumn,1, vec.y());
	Set(iColumn,2, vec.z());
	Set(iColumn,3, vec.w());
}

//-----------------------------------------------------------------------------------
Vector4 Matrix4x4::GetRow(int iRow)
{
	Vector4 vec(Get(0, iRow), Get(1, iRow), Get(2, iRow), Get(3, iRow));
	return vec;
}

//-----------------------------------------------------------------------------------
void Matrix4x4::SetRow(int iRow, Vector4 vec)
{
	Set(0, iRow, vec.x());
	Set(1, iRow, vec.y());
	Set(2, iRow, vec.z());
	Set(3, iRow, vec.w());
}

//-----------------------------------------------------------------------------------
void Matrix4x4::Transpose()
{
	Vector4 row0 = GetRow(0);
	Vector4 row1 = GetRow(1);
	Vector4 row2 = GetRow(2);
	Vector4 row3 = GetRow(3);

	SetColumn(0, row0);
	SetColumn(1, row1);
	SetColumn(2, row2);
	SetColumn(3, row3);
}

//-----------------------------------------------------------------------------------
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb205350(v=vs.85).aspx
void Matrix4x4::SetPerspectiveFovLH(float fFovY, float fAspectRatio, float fZN, float fZF)
{
	SetIdentity();
	
	float cotan = 1/tan(fFovY/2.0f);
	float fYScale = cotan;
	float fXScale = fYScale/fAspectRatio;


	Set(0,0, fXScale);
	Set(1,1, fYScale);
	Set(2,2, fZF/(fZF-fZN));
	Set(3,2, 1.0f);
	Set(2,3, (-fZN*fZF)/(fZF-fZN));
	Set(3,3, 0.00f);

}

//-----------------------------------------------------------------------------------
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb204940(v=vs.85).aspx
void Matrix4x4::SetOrthoLH(float w, float h, float fZN, float fZF)
{
	SetIdentity();

	Set(0,0, 2/w);
	Set(1,1, 2/h);
	Set(2,2, 1/(fZF-fZN));
	Set(2,3, fZN/(fZN-fZF));
	Set(3,3, 1.00f);
}

//-----------------------------------------------------------------------------------
void Matrix4x4::Translate( Vector3 position )
{
	Set(0,3, position.x());
	Set(1,3, position.y());
	Set(2,3, position.z());
}

//-----------------------------------------------------------------------------------
void Matrix4x4::RotationY( float degrees )
{
	float fRad = degrees * MathHelper::Deg2Rad;
	float fs = sin(fRad);
	float fc = cos(fRad);

	SetIdentity();
	Set(0,0, fc);
	Set(2,0, fs);
	Set(0,2, -fs);
	Set(2,2, fc);
}

//-----------------------------------------------------------------------------------
void Matrix4x4::RotationZ( float degrees )
{
	float fRad = degrees * MathHelper::Deg2Rad;
	float fs = sin(fRad);
	float fc = cos(fRad);

	SetIdentity();
	Set(0,0, fc);
	Set(1,0, fs);
	Set(0,1, -fs);
	Set(1,1, fc);
}

//-----------------------------------------------------------------------------------
void Matrix4x4::UniformScale( float fScale )
{
	SetIdentity();
	Set(0,0, fScale);
	Set(1,1, fScale);
	Set(2,2, fScale);
}

//-----------------------------------------------------------------------------------
void Matrix4x4::FromLookAt( Vector3 look )
{
	Vector3 right = Vector3::Cross(look, Vector3::Up());
	right.Normalize();

	Vector3 up = Vector3::Cross(right, look);
	up.Normalize();

	SetRow(0, Vector4(right,0));
	SetRow(1, Vector4(up,0));
	SetRow(2, Vector4(look,0));
}

//-----------------------------------------------------------------------------------
Matrix4x4 Matrix4x4::TInverse(Matrix4x4 posMat, Matrix4x4 rotMat)
{
	Matrix4x4 inv;
	inv.SetIdentity();

	Vector4 v0 = rotMat.GetRow(0);
	Vector4 v1 = rotMat.GetRow(1);
	Vector4 v2 = rotMat.GetRow(2);
	Vector4 pos = posMat.GetRow(3);

	inv.SetColumn(0, v0.GetNormalized());
	inv.SetColumn(1, v1.GetNormalized());
	inv.SetColumn(2, v2.GetNormalized());


	float x = Vector4::Dot(-pos, inv.GetColumn(0));
	float y = Vector4::Dot(-pos, inv.GetColumn(1));
	float z = Vector4::Dot(-pos, inv.GetColumn(2));
	pos.x(x); pos.y(y); pos.z(z); pos.w(1.0f);
	
	inv.SetRow(3, pos);

	return inv;
}
 
#ifdef COMPILE_DX9_RENDERER
//-----------------------------------------------------------------------------------
D3DMATRIX Matrix4x4::ToD3DMatrix()
{
	Matrix4x4 m(*this);
	m.Transpose();

	D3DMATRIX d3dmat;
	d3dmat._11 = m.mMatrix[0]; d3dmat._12 = m.mMatrix[1]; d3dmat._13 = m.mMatrix[2]; d3dmat._14 = m.mMatrix[3];
	d3dmat._21 = m.mMatrix[4]; d3dmat._22 = m.mMatrix[5]; d3dmat._23 = m.mMatrix[6]; d3dmat._24 = m.mMatrix[7];
	d3dmat._31 = m.mMatrix[8]; d3dmat._32 = m.mMatrix[9]; d3dmat._33 = m.mMatrix[10]; d3dmat._34 = m.mMatrix[11];
	d3dmat._41 = m.mMatrix[12]; d3dmat._42 = m.mMatrix[13]; d3dmat._43 = m.mMatrix[14]; d3dmat._44 = m.mMatrix[15];

	return d3dmat;
}
#endif
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

}

//-----------------------------------------------------------------------------------
void Matrix4x4::Translate( Vector3 position )
{
	Set(0,3, position.x());
	Set(1,3, position.y());
	Set(2,3, position.z());
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
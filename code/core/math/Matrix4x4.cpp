#include "Matrix4x4.h"

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
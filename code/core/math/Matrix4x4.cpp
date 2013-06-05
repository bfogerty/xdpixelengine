#include "Matrix4x4.h"


Matrix4x4::Matrix4x4()
{
	SetIdentity();
}
void Matrix4x4::SetIdentity()
{
	Set(0,0, 1.0f);  Set(1,0, 0.0f);  Set(2,0, 0.0f);  Set(3,0, 0.0f);
	Set(0,1, 0.0f);  Set(1,1, 1.0f);  Set(2,1, 0.0f);  Set(3,1, 0.0f);
	Set(0,2, 0.0f);  Set(1,2, 0.0f);  Set(2,2, 1.0f);  Set(3,2, 0.0f);
	Set(0,3, 0.0f);  Set(1,3, 0.0f);  Set(2,3, 0.0f);  Set(3,3, 1.0f);
}

float Matrix4x4::Get(int iColumn, int iRow)
{
	return mMatrix[ (iRow*4) + iColumn ];
}

void Matrix4x4::Set(int iColumn, int iRow, float fValue)
{
	mMatrix[ (iRow*4) + iColumn ] = fValue;
}

Matrix4x4 Matrix4x4::operator *(Matrix4x4 other)
{
	Matrix4x4 matResult;

	return matResult;
}
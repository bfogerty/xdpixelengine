#ifndef __MATRIX4X4__
#define __MATRIX4X4__

#include "Vector3.h"

class Matrix4x4
{
public:
	float mMatrix[16];

	Matrix4x4();
	void SetIdentity();
	float Get(int iColumn, int iRow);
	void Set(int iColumn, int iRow, float fValue);
	Matrix4x4 operator*(Matrix4x4 other);

};

#endif
#ifndef __MATRIX4X4__
#define __MATRIX4X4__

#include "Vector3.h"
#include "Vector4.h"

class Matrix4x4
{
public:
	float mMatrix[16];

	Matrix4x4();
	void SetIdentity();
	float Get(int iColumn, int iRow);
	void Set(int iColumn, int iRow, float fValue);
	Matrix4x4 operator*(float fScalar);
	Matrix4x4 operator*(Matrix4x4 other);
	Vector4 operator*(Vector4 vec);

	Vector4 GetColumn(int iColumn);
	void SetColumn(int iColumn, Vector4 vec);

	Vector4 GetRow(int iRow);
	void SetRow(int iRow, Vector4 vec);

	void Transpose();
	void SetPerspectiveFovLH(float fFovY, float fAspectRatio, float fZN, float fZF);
	void SetOrthoLH(float w, float h, float fZN, float fZF);
	void Translate( Vector3 position );
	void RotationY( float degrees );
	void RotationZ( float degrees );
	void UniformScale( float fScale );

	void FromLookAt(Vector3 look);

};

#endif
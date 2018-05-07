#ifndef __MATRIX4X4__
#define __MATRIX4X4__

#include "core/platform.h"

#include "core/math/Vector3.h"
#include "core/math/Vector4.h"


#ifdef COMPILE_DX9_RENDERER
#include <d3d9.h>
#endif

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

	static Matrix4x4 TInverse(Matrix4x4 posMat, Matrix4x4 rotMat);

#ifdef COMPILE_DX9_RENDERER
	D3DMATRIX ToD3DMatrix();
#endif

};

#endif
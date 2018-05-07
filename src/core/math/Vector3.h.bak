#ifndef __VECTOR3__
#define __VECTOR3__

#include "core/BaseObject.h"
#include "string"
using namespace std;

class Vector3 : BaseObject
{
public:

	enum XYZ
	{
		X = 0,
		Y = 1,
		Z = 2,
	};

	float data[3];

	Vector3();
	Vector3( float x, float y, float z );
	~Vector3();

	float x() { return data[X];}
	void x(float v) { data[X] = v;}
	
	float y() { return data[Y];}
	void y(float v) { data[Y] = v;}

	float z() { return data[Z];}
	void z(float v) { data[Z] = v;}

	Vector3 operator-();
	Vector3 operator+(Vector3 vec);
	Vector3 operator-(Vector3 vec);
	Vector3 operator*(float fScale);

	Vector3 Scale( float fScalar );
	float Magnitude();
	float SqrMagnitude();

	Vector3 GetNormalized();
	void Normalize();

	void Set( float x, float y, float z);
	
	virtual string ToString();

	static float Dot( Vector3 vec1, Vector3 vec2 );
	static Vector3 Cross( Vector3 vec1, Vector3 vec2 );
	static Vector3 OrthoNormalize( Vector3 vecNormal, Vector3 vecTangent );
	static Vector3 MoveTowards( Vector3 vecCurrent, Vector3 vecTarget, float fMaxDistanceDelta);
	static Vector3 Lerp( Vector3 vecA, Vector3 vecB, float t);
	static float Angle( Vector3 vecA, Vector3 vecB);
	static Vector3 ClampMagnitude( Vector3 vecA, float fMagnitude );
	static Vector3 Project( Vector3 vecA, Vector3 vecB );
	static Vector3 Reflect( Vector3 vecA, Vector3 vecNormal );
	static Vector3 Reflect( Vector3 vecA, Vector3 vecNormal, bool bBounce, float fBounceDamp);
	static float Distance( Vector3 vecA, Vector3 vecB );

	static Vector3 Forward();
	static Vector3 Up();
	static Vector3 Right();
	static Vector3 One();
	static Vector3 Zero();

};

#endif
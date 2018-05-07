#ifndef __VECTOR4__
#define __VECTOR4__

#include "core/BaseObject.h"
#include "string"
using namespace std;

class Vector3;

class Vector4 : BaseObject
{
public:

	enum XYZW
	{
		X = 0,
		Y = 1,
		Z = 2,
		W = 3,
	};

	float data[4];

	Vector4();
	Vector4( Vector3 vec3, float w );
	Vector4( float x, float y, float z, float w );
	Vector4( float *values );
	~Vector4();

	float x() { return data[X];}
	void x(float v) { data[X] = v;}
	
	float y() { return data[Y];}
	void y(float v) { data[Y] = v;}

	float z() { return data[Z];}
	void z(float v) { data[Z] = v;}

	float w() { return data[W];}
	void w(float v) { data[W] = v;}

	Vector4 operator-();
	Vector4 operator+(Vector4 vec);
	Vector4 operator-(Vector4 vec);
	Vector4 operator*(float fScale);

	Vector4 Scale( float fScalar );
	float Magnitude();
	float SqrMagnitude();

	Vector4 GetNormalized();
	void Normalize();

	void Set( float x, float y, float z, float w);
	
	virtual string ToString();

	static float Dot( Vector4 vec1, Vector4 vec2 );
	static Vector4 MoveTowards( Vector4 vecCurrent, Vector4 vecTarget, float fMaxDistanceDelta);
	static Vector4 Lerp( Vector4 vecA, Vector4 vecB, float t);
	static float Angle( Vector4 vecA, Vector4 vecB);
	static Vector4 ClampMagnitude( Vector4 vecA, float fMagnitude );
	static float Distance( Vector4 vecA, Vector4 vecB );

	static Vector4 Forward();
	static Vector4 Up();
	static Vector4 Right();
	static Vector4 One();
	static Vector4 Zero();

};

#endif
#ifndef __QUATERNION__
#define __QUATERNION__

#include "Vector3.h"
#include "Matrix4x4.h"

class Quaternion
{
public:

	Quaternion();
	Quaternion(Vector3 vec, float w);
	~Quaternion();
	void Identity();
	Quaternion operator *(Quaternion other);
	Vector3 operator *(Vector3 v);

	static Quaternion AxisAngle(Vector3 axis, float fAngle);
	static Quaternion Negation(Quaternion quat);
	static Quaternion Conjugate(Quaternion quat);
	static float Magnitude(Quaternion quat);
	static Quaternion Inverse(Quaternion quat);
	static Matrix4x4 ToMatrix(Quaternion quat);
	static Quaternion FromMatrix( Matrix4x4 matRot );
	static Quaternion FromLook( Vector3 look );
	static Quaternion FromEulerAngles( Vector3 angles );

	float w;
	Vector3 v;
};

#endif
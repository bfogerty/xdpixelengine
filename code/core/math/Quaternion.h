#ifndef __QUATERNION__
#define __QUATERNION__

#include "Vector3.h"

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

	float w;
	Vector3 v;
};

#endif
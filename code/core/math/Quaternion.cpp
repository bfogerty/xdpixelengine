#include "Quaternion.h"
#include "math.h"
#include "MathHelper.h"

//-----------------------------------------------------------------------------------
Quaternion::Quaternion()
{
	Identity();
}

//-----------------------------------------------------------------------------------
Quaternion::Quaternion(Vector3 vec, float w)
{
	this->v = vec;
	this->w = w;
}

//-----------------------------------------------------------------------------------
Quaternion::~Quaternion()
{

}

//-----------------------------------------------------------------------------------
void Quaternion::Identity()
{
	w = 1.00f;
	v = Vector3::Zero();
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::operator *(Quaternion other)
{
	Quaternion qResult;

	Vector3 w1V2 = other.v * this->w;
	Vector3 w2V1 = this->v * other.w;
	Vector3 CrossOfV2V1 = Vector3::Cross(other.v, this->v);

	qResult.w = (this->w * other.w) - Vector3::Dot(this->v, other.v);
	qResult.v = w1V2+ w2V1+ CrossOfV2V1;
	

	return qResult;
}

//-----------------------------------------------------------------------------------
Vector3 Quaternion::operator *(Vector3 v)
{
	Vector3 vResult;

	Quaternion p = Quaternion(v,0);
	Quaternion qInv = Quaternion::Inverse(*this);

	Quaternion r = *this * p * qInv;

	vResult = r.v;

	return vResult;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::AxisAngle(Vector3 axis, float fAngleDEG)
{
	Quaternion qResult;
	float fAngle = fAngleDEG * MathHelper::Deg2Rad;

	float c = cos(fAngle/2.0f);
	float s = sin(fAngle/2.0f);

	qResult.w = c;
	qResult.v.x(axis.x() * s);
	qResult.v.y(axis.y() * s);
	qResult.v.z(axis.z() * s);

	return qResult;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::Negation(Quaternion quat)
{
	Quaternion qResult;

	qResult.w = -quat.w;
	qResult.v.x(-quat.v.x());
	qResult.v.y(-quat.v.y());
	qResult.v.z(-quat.v.z());

	return qResult;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::Conjugate(Quaternion quat)
{
	Quaternion qResult;

	qResult.w = quat.w;
	qResult.v.x(-quat.v.x());
	qResult.v.y(-quat.v.y());
	qResult.v.z(-quat.v.z());

	return qResult;
}

//-----------------------------------------------------------------------------------
float Quaternion::Magnitude(Quaternion quat)
{
	float fResult = 0.0f;

	fResult = sqrt(quat.w*quat.w + quat.v.x()*quat.v.x() + quat.v.y()*quat.v.y() + quat.v.z()*quat.v.z());

	return fResult;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::Inverse(Quaternion quat)
{
	Quaternion qResult;

	Quaternion quatC = Quaternion::Conjugate(quat);
	float fMagnitude = Quaternion::Magnitude(quat);

	qResult.w = quatC.w / fMagnitude;
	qResult.v.x( quatC.v.x() / fMagnitude );
	qResult.v.y( quatC.v.y() / fMagnitude );
	qResult.v.z( quatC.v.z() / fMagnitude );


	return qResult;
}
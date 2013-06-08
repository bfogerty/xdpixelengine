#include "Vector4.h"
#include "math.h"
#include "MathHelper.h"
#include <sstream>
using namespace std;

Vector4::Vector4()
{
	data[X] = 0.0000f;
	data[Y] = 0.0000f;
	data[Z] = 0.0000f;
	data[W] = 0.0000f;
}

Vector4::Vector4( float x, float y, float z, float w )
{
	data[X] = x;
	data[Y] = y;
	data[Z] = z;
	data[W] = w;
}

Vector4::Vector4( float *values )
{
	data[X] = values[0];
	data[Y] = values[1];
	data[Z] = values[2];
	data[W] = values[3];
}

Vector4 Vector4::operator -()
{
	Vector4 vecResult;
	vecResult.data[X] = -data[X];
	vecResult.data[Y] = -data[Y];
	vecResult.data[Z] = -data[Z];
	vecResult.data[W] = -data[W];

	return vecResult;
}

Vector4 Vector4::operator +( Vector4 vec )
{
	Vector4 vecResult;
	vecResult.data[X] = data[X] + vec.data[X];
	vecResult.data[Y] = data[Y] + vec.data[Y];
	vecResult.data[Z] = data[Z] + vec.data[Z];
	vecResult.data[W] = data[W] + vec.data[W];
	
	return vecResult;
}

Vector4 Vector4::operator -(Vector4 vec)
{
	Vector4 vecResult;
	vecResult.data[X] = data[X] - vec.data[X];
	vecResult.data[Y] = data[Y] - vec.data[Y];
	vecResult.data[Z] = data[Z] - vec.data[Z];
	vecResult.data[W] = data[W] - vec.data[W];

	return vecResult;
}

Vector4 Vector4::operator *( float fScale )
{
	Vector4 vecResult;
	vecResult.data[X] = data[X] * fScale;
	vecResult.data[Y] = data[Y] * fScale;
	vecResult.data[Z] = data[Z] * fScale;
	vecResult.data[W] = data[W] * fScale;

	return vecResult;
}

Vector4 Vector4::Scale( float fScale )
{
	Vector4 vecResult;
	Vector4 vecMe = *this;
	vecResult = vecMe * fScale;

	return vecResult;
}

float Vector4::Magnitude()
{
	float fResult = sqrt( SqrMagnitude() );

	return fResult;
}

float Vector4::SqrMagnitude()
{
	float fResult = (data[X] * data[X]) + 
					(data[Y] * data[Y]) + 
					(data[Z] * data[Z]) +
					(data[W] * data[W]);

	return fResult;
}

Vector4 Vector4::GetNormalized()
{
	Vector4 vecResult;
	float fNorm = Magnitude();

	vecResult.data[X] = data[X] / fNorm;
	vecResult.data[Y] = data[Y] / fNorm;
	vecResult.data[Z] = data[Z] / fNorm;
	vecResult.data[W] = data[W] / fNorm;

	return vecResult;
}

void Vector4::Normalize()
{
	Vector4 vecNormalized = GetNormalized();

	data[X] = vecNormalized.data[X];
	data[Y] = vecNormalized.data[Y];
	data[Z] = vecNormalized.data[Z];
	data[W] = vecNormalized.data[W];
}

void Vector4::Set( float x, float y, float z, float w)
{
	data[X] = x;
	data[Y] = y;
	data[Z] = z;
	data[W] = w;
}

float Vector4::Dot( Vector4 vec1, Vector4 vec2 )
{
	float fResult = 0.0000f;
	fResult = ( vec1.data[X] * vec2.data[X] ) + ( vec1.data[Y] * vec2.data[Y] ) + (vec1.data[Z] * vec2.data[Z])  + (vec1.data[W] * vec2.data[W]);

	return fResult;
}


Vector4 Vector4::MoveTowards( Vector4 vecA, Vector4 vecB, float fMaxDistanceDelta)
{
	Vector4 vecFromAToB = vecB - vecA;
	float fDistance = vecFromAToB.Magnitude();

	if( fMaxDistanceDelta < 0.0000f)
	{
		return vecA;
	}
	else if( fMaxDistanceDelta > fDistance )
	{
		return vecB;
	}

	vecFromAToB.Normalize();

	Vector4 vecResult = vecA + (vecFromAToB * fMaxDistanceDelta);

	return vecResult;

}

Vector4 Vector4::Lerp( Vector4 vecA, Vector4 vecB, float t)
{
	Vector4 vecResult = vecA*(1.0f - t) + (vecB*t);

	return vecResult;
}

float Vector4::Angle( Vector4 vecA, Vector4 vecB)
{
	// DOT(A,B) = |A|*|B|*COS(t)
	Vector4 vecAN = vecA.GetNormalized();
	Vector4 vecBN = vecB.GetNormalized();
	float fThetaRAD =  acos( Vector4::Dot( vecAN, vecBN) );

	float fThetaDEG = fThetaRAD * 180.0f / MathHelper::PI;

	return fThetaDEG;
}

Vector4 Vector4::ClampMagnitude( Vector4 vecA, float fMagnitude )
{
	float fSqrMag = vecA.SqrMagnitude();
	float fMaxSqrMag = fMagnitude * fMagnitude;
	if( fSqrMag <= fMaxSqrMag )
	{
		return vecA;
	}

	Vector4 vecAN = vecA.GetNormalized();
	Vector4 vecResult = vecAN * fMagnitude;

	return vecResult;
}

float Vector4::Distance( Vector4 vecA, Vector4 vecB )
{
	float fResult = 0.000f;
	Vector4 vecFromAToB = vecB - vecA;
	fResult = vecFromAToB.Magnitude();

	return fResult;
}

Vector4 Vector4::Forward()
{
	Vector4 vecResult(0.0000f, 0.0000f, 1.0000f, 0.0000f);
	return vecResult;
}

Vector4 Vector4::Up()
{
	Vector4 vecResult(0.0000f, 1.0000f, 0.0000f, 0.0000f);
	return vecResult;
}

Vector4 Vector4::Right()
{
	Vector4 vecResult(1.0000f, 0.0000f, 0.0000f, 0.0000f);
	return vecResult;
}

Vector4 Vector4::One()
{
	Vector4 vecResult(1.0000f, 1.0000f, 1.0000f, 1.0000f);
	return vecResult;
}

Vector4 Vector4::Zero()
{
	Vector4 vecResult(0.0000f, 0.0000f, 0.0000f, 0.0000f);
	return vecResult;
}

string Vector4::ToString()
{
	std::stringstream ss;
	ss << "[" << data[X] << ", " << data[Y] << ", " << data[Z] << ", " << data[W] << "]";
	
	std::string strVal = ss.str();

	return strVal;
}

Vector4::~Vector4()
{

}
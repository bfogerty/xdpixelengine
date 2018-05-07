#include "Vector3.h"
#include "math.h"
#include "MathHelper.h"
#include <sstream>
using namespace std;

Vector3::Vector3()
{
	data[X] = 0.0000f;
	data[Y] = 0.0000f;
	data[Z] = 0.0000f;
}

Vector3::Vector3( float x, float y, float z )
{
	data[X] = x;
	data[Y] = y;
	data[Z] = z;
}

/*
Vector3::Vector3( const Vector3 &rhs )
{
	this->Set(rhs.data[X], rhs.data[Y], rhs.data[Z]);
}
*/

Vector3 Vector3::operator -()
{
	Vector3 vecResult;
	vecResult.data[X] = -data[X];
	vecResult.data[Y] = -data[Y];
	vecResult.data[Z] = -data[Z];

	return vecResult;
}

Vector3 Vector3::operator +( Vector3 vec )
{
	Vector3 vecResult;
	vecResult.data[X] = data[X] + vec.data[X];
	vecResult.data[Y] = data[Y] + vec.data[Y];
	vecResult.data[Z] = data[Z] + vec.data[Z];
	
	return vecResult;
}

Vector3 Vector3::operator -(Vector3 vec)
{
	Vector3 vecResult;
	vecResult.data[X] = data[X] - vec.data[X];
	vecResult.data[Y] = data[Y] - vec.data[Y];
	vecResult.data[Z] = data[Z] - vec.data[Z];

	return vecResult;
}

Vector3 Vector3::operator *( float fScale )
{
	Vector3 vecResult;
	vecResult.data[X] = data[X] * fScale;
	vecResult.data[Y] = data[Y] * fScale;
	vecResult.data[Z] = data[Z] * fScale;

	return vecResult;
}

/*
Vector3& Vector3::operator=( const Vector3 &rhs )
{
	this->Set(rhs.data[X], rhs.data[Y],rhs.data[Z]);

	return *this;
}
*/

Vector3 Vector3::Scale( float fScale )
{
	Vector3 vecResult;
	Vector3 vecMe = *this;
	vecResult = vecMe * fScale;

	return vecResult;
}

float Vector3::Magnitude()
{
	float fResult = sqrt( SqrMagnitude() );

	return fResult;
}

float Vector3::SqrMagnitude()
{
	float fResult = (data[X] * data[X]) + 
					(data[Y] * data[Y]) + 
					(data[Z] * data[Z]);

	return fResult;
}

Vector3 Vector3::GetNormalized()
{
	Vector3 vecResult;
	float fNorm = Magnitude();

	vecResult.data[X] = data[X] / fNorm;
	vecResult.data[Y] = data[Y] / fNorm;
	vecResult.data[Z] = data[Z] / fNorm;

	return vecResult;
}

void Vector3::Normalize()
{
	Vector3 vecNormalized = GetNormalized();

	data[X] = vecNormalized.data[X];
	data[Y] = vecNormalized.data[Y];
	data[Z] = vecNormalized.data[Z];
}

void Vector3::Set( float x, float y, float z)
{
	data[X] = x;
	data[Y] = y;
	data[Z] = z;
}

float Vector3::Dot( Vector3 vec1, Vector3 vec2 )
{
	float fResult = 0.0000f;
	fResult = ( vec1.data[X] * vec2.data[X] ) + ( vec1.data[Y] * vec2.data[Y] ) + (vec1.data[Z] * vec2.data[Z]);

	return fResult;
}

Vector3 Vector3::Cross( Vector3 vec1, Vector3 vec2 )
{
	Vector3 vecResult;
	vecResult.data[X] = (vec2.data[Y] * vec1.data[Z]) - ( vec1.data[Y] * vec2.data[Z] ); 
	vecResult.data[Y] = (vec2.data[Z] * vec1.data[X]) - ( vec1.data[Z] * vec2.data[X] );
	vecResult.data[Z] = (vec2.data[X] * vec1.data[Y]) - ( vec1.data[X] * vec2.data[Y] );

	return vecResult;
}

Vector3 Vector3::OrthoNormalize( Vector3 vecNormal, Vector3 vecTangent )
{
	vecNormal.Normalize();
	vecTangent.Normalize();

	Vector3 vecBiNormal = Vector3::Cross( vecNormal, vecTangent );
	vecBiNormal.Normalize();

	return vecBiNormal;
}

Vector3 Vector3::MoveTowards( Vector3 vecA, Vector3 vecB, float fMaxDistanceDelta)
{
	Vector3 vecFromAToB = vecB - vecA;
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

	Vector3 vecResult = vecA + (vecFromAToB * fMaxDistanceDelta);

	return vecResult;

}

Vector3 Vector3::Lerp( Vector3 vecA, Vector3 vecB, float t)
{
	Vector3 vecResult = vecA*(1.0f - t) + (vecB*t);

	return vecResult;
}

float Vector3::Angle( Vector3 vecA, Vector3 vecB)
{
	// DOT(A,B) = |A|*|B|*COS(t)
	Vector3 vecAN = vecA.GetNormalized();
	Vector3 vecBN = vecB.GetNormalized();
	float fThetaRAD =  acos( Vector3::Dot( vecAN, vecBN) );

	float fThetaDEG = fThetaRAD * 180.0f / MathHelper::PI;

	return fThetaDEG;
}

Vector3 Vector3::ClampMagnitude( Vector3 vecA, float fMagnitude )
{
	float fSqrMag = vecA.SqrMagnitude();
	float fMaxSqrMag = fMagnitude * fMagnitude;
	if( fSqrMag <= fMaxSqrMag )
	{
		return vecA;
	}

	Vector3 vecAN = vecA.GetNormalized();
	Vector3 vecResult = vecAN * fMagnitude;

	return vecResult;
}

Vector3 Vector3::Project( Vector3 vecV, Vector3 vecN )
{
	Vector3 vecResult;

	float fNMag = vecN.Magnitude();
	float fVDotN = Vector3::Dot(vecV, vecN);

	vecResult = vecN * (fVDotN / (fNMag*fNMag));

	return vecResult;
}

Vector3 Vector3::Reflect( Vector3 vecA, Vector3 vecNormal )
{
	return Reflect( vecA, vecNormal, false, 0.0f );
}

Vector3 Vector3::Reflect( Vector3 vecA, Vector3 vecNormal, bool bBounce, float fBounceDamp)
{
	Vector3 vecResult;

	Vector3 vecNegA = -vecA;

	Vector3 vecProj = Project(vecNegA, vecNormal);
	Vector3 vecFromProjToA = vecNegA - vecProj;

	vecResult = vecProj + (-vecFromProjToA.GetNormalized() * vecFromProjToA.Magnitude());

	if( bBounce )
	{
		return vecResult * fBounceDamp;
	}

	return -vecResult;
}

float Vector3::Distance( Vector3 vecA, Vector3 vecB )
{
	float fResult = 0.000f;
	Vector3 vecFromAToB = vecB - vecA;
	fResult = vecFromAToB.Magnitude();

	return fResult;
}

Vector3 Vector3::Forward()
{
	Vector3 vecResult(0.0000f, 0.0000f, 1.0000f);
	return vecResult;
}

Vector3 Vector3::Up()
{
	Vector3 vecResult(0.0000f, 1.0000f, 0.0000f);
	return vecResult;
}

Vector3 Vector3::Right()
{
	Vector3 vecResult(1.0000f, 0.0000f, 0.0000f);
	return vecResult;
}

Vector3 Vector3::One()
{
	Vector3 vecResult(1.0000f, 1.0000f, 1.0000f);
	return vecResult;
}

Vector3 Vector3::Zero()
{
	Vector3 vecResult(0.0000f, 0.0000f, 0.0000f);
	return vecResult;
}

string Vector3::ToString()
{
	std::stringstream ss;
	ss << "[" << data[X] << ", " << data[Y] << ", " << data[Z] << "]";
	
	std::string strVal = ss.str();

	return strVal;
}

Vector3::~Vector3()
{

}
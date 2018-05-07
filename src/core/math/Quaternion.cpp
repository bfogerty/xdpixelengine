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

//-----------------------------------------------------------------------------------
Matrix4x4 Quaternion::ToMatrix(Quaternion quat)
{
	Matrix4x4 mat;

	float t = acos(quat.w)*2.0f;;
	float ct = cos(t);
	float st = sin(t);
	float stDiv2 = sin(t/2.0f);
	float OMCT = (1.0f - ct);

	Vector3 n;
	n.x(quat.v.x() / stDiv2);
	n.y(quat.v.y() / stDiv2);
	n.z(quat.v.z() / stDiv2);

	float nx2 = n.x() * n.x();
	float ny2 = n.y() * n.y();
	float nz2 = n.z() * n.z();

	float nxny = n.x() * n.y();
	float nxnz = n.x() * n.z();
	float nynz = n.y() * n.z();

	mat.Set(0,0, nx2*OMCT+ct);				mat.Set(1,0, nxny*OMCT+n.z()*st);		mat.Set(2,0, nxnz*OMCT-n.y()*st);
	mat.Set(0,1, nxny*OMCT-n.z()*st);		mat.Set(1,1, ny2*OMCT+ct);				mat.Set(2,1, nynz*OMCT+n.x()*st);
	mat.Set(0,2, nxnz*OMCT+n.y()*st);		mat.Set(1,2, nynz*OMCT-n.x()*st);		mat.Set(2,2, nz2*OMCT+ct);

	mat.SetRow(0, mat.GetRow(0).GetNormalized() );
	mat.SetRow(1, mat.GetRow(1).GetNormalized() );
	mat.SetRow(2, mat.GetRow(2).GetNormalized() );

	return mat;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::FromMatrix( Matrix4x4 m )
{
	Quaternion q;

	float tr = m.Get(0,0) + m.Get(1,1) + m.Get(2,2);

	if( tr > 0 )
	{
		float s = sqrt( 1 + tr ) * 2.0f;
		q.w = 0.25f * s;
		q.v.x((m.Get(2,1) - m.Get(1,2))/(s));
		q.v.y((m.Get(0,2) - m.Get(2,0))/(s));
		q.v.z((m.Get(1,0) - m.Get(0,1))/(s));
	}
	else if( (m.Get(0,0) > m.Get(1,1) && (m.Get(0,0) > m.Get(2,2))))
	{
		float s = sqrt(1.0f + m.Get(0,0) - m.Get(1,1) - m.Get(2,2)) * 2.0f;
		q.w = (m.Get(2,1) - m.Get(1,2)) / s;
		q.v.x( 0.25f * s);
		q.v.y((m.Get(0,1) + m.Get(1,0))/(s));
		q.v.z((m.Get(0,2) + m.Get(2,0))/(s));
	}
	else if( m.Get(1,1) > m.Get(2,2))
	{
		float s = sqrt(1.0f + m.Get(1,1) - m.Get(0,0) - m.Get(2,2)) * 2.0f;
		q.w = (m.Get(0,2) - m.Get(2,0)) / s;
		q.v.x( (m.Get(0,1) + m.Get(1,0)) / s);
		q.v.y(0.25f * s);
		q.v.z((m.Get(1,2) + m.Get(2,1))/(s));
	}
	else
	{
		float s = sqrt(1.0f + m.Get(2,2) - m.Get(0,0) - m.Get(1,1)) * 2.0f;
		q.w = (m.Get(1,0) - m.Get(0,1)) / s;
		q.v.x( (m.Get(0,2) + m.Get(2,0)) / s);
		q.v.y((m.Get(1,2) + m.Get(2,1)) / s);
		q.v.z(0.25f * s);
	}
	return q;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::FromLook( Vector3 look )
{
	Quaternion q;
	Matrix4x4 m;
	m.FromLookAt(look);

	q = FromMatrix(m);

	return q;
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::GetNormalized()
{
	Quaternion quatResult = *this;
	quatResult.Normalize();

	return quatResult;
	
}

//-----------------------------------------------------------------------------------
void Quaternion::Normalize()
{
	float fMag = Quaternion::Magnitude( *this );

	float x = v.x() / fMag;
	float y = v.y() / fMag;
	float z = v.z() / fMag;

	this->w = w / fMag;
	this->v.x(x);
	this->v.x(y);
	this->v.x(z);
}

//-----------------------------------------------------------------------------------
Quaternion Quaternion::FromEulerAngles( Vector3 angles )
{
	float p = angles.x() * MathHelper::Deg2Rad;
	float h = angles.y() * MathHelper::Deg2Rad;
	float r = angles.z() * MathHelper::Deg2Rad;

	if( p == 0.000f )
	{
		p = 0.001f;
	}

	if( h == 0.000f )
	{
		h = 0.001f;
	}

	if( r == 0.000f )
	{
		r = 0.001f;
	}

	Quaternion qp;
	qp.w = cos( p / 2) ; qp.v.x(sin( p/2 ));

	Quaternion qh;
	qh.w = cos( h / 2) ; qh.v.y(sin( h/2 ));

	Quaternion qr;
	qr.w = cos( r / 2) ; qr.v.z(sin( r/2 ));

	Quaternion quatResult = qr * qh * qp;

	return quatResult;
}

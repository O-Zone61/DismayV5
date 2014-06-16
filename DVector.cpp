#include <cmath>
#include "DVector.h"
#include "DAngle.h"
#include <cfloat>

#define DEG2RAD(x) ((float)x * M_PI / 180.0f)
#define RAD2DEG(x) ((float)x * 180.0f / M_PI)

#define M_PI 3.1415926535f

DVector operator* (float x, DVector y)
{
    return DVector(y.x * x, y.y * x, y.z * x);
}
DVector operator* (DVector y, float x)
{
    return DVector(y.x * x, y.y * x, y.z * x);
}



void __fastcall VectorNormalizeFast (Vector& vec)
{
	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.0f / (sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z) + FLT_EPSILON);
	
	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;
	
}
void VectorAngles(const Vector &forward, QAngle &angles)
{
	Vector cross;
		float	tmp, yaw, pitch;
	
	if (forward.y == 0 && forward.x == 0)
	{
		yaw = 0;
		if (forward.z > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward.y, forward.x) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt (forward.x*forward.x + forward.y*forward.y);
		pitch = (atan2(forward.z, tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}
	angles.p = pitch;
	angles.y = yaw;
	angles.r = 0;
}

void SinCos(const float x, float *sinval, float *cosval)
{
	*sinval = sin(x);
	*cosval = cos(x);
}

void AngleVectors (const QAngle &angles, Vector *forward)
{
	float	sp, sy, cp, cy;
	
	SinCos(DEG2RAD(angles.y), &sy, &cy);
	SinCos(DEG2RAD(angles.p), &sp, &cp);
	
	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}
void AngleVectors( const QAngle &angles, Vector *forward, Vector *right, Vector *up )
{
	float sr, sp, sy, cr, cp, cy;

	SinCos( DEG2RAD( angles.y ), &sy, &cy );
	SinCos( DEG2RAD( angles.p ), &sp, &cp );
	SinCos( DEG2RAD( angles.r ), &sr, &cr );

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1*sr*sp*cy+-1*cr*-sy);
		right->y = (-1*sr*sp*sy+-1*cr*cy);
		right->z = -1*sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy+-sr*-sy);
		up->y = (cr*sp*sy+-sr*cy);
		up->z = cr*cp;
	}
}

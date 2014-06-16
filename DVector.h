
#include "Forward.h"
#ifndef VECTOR_H
#define VECTOR_H
#pragma once
#include "DAngle.h"

class DVector 
{
public:
	DVector()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	DVector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	DVector operator*(DVector mult)
	{
		return DVector(this->x * mult.x, this->y * mult.y, this->z * mult.z);
	}
	DVector operator+(DVector m)
	{
		return DVector(this->x + m.x, this->y + m.y, this->z + m.z);
	}
public:
	float x, y, z;
};

typedef DVector Vector;

extern DVector operator*(float x, DVector y);
extern DVector operator*(DVector y, float x);
void AngleVectors(const QAngle &angles, Vector *forward);
extern void VectorAngles(const Vector &forward, QAngle &angles);
extern void AngleVectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up);


#endif // VECTOR_H
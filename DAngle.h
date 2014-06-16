#ifndef ANGLE_H
#define ANGLE_H
class QAngle;

class QAngle
{
public:

	QAngle()
	{
		p = 0;
		y = 0;
		r = 0;
	}
	QAngle(float p, float y, float r)
	{
		this->p = p;
		this->y = y;
		this->r = r;
	}
	QAngle operator *(float mult)
	{
		return QAngle(this->p * mult, this->y * mult, this->r * mult);
	}
	bool IsShit()
	{
		if(this->p == -1000 && this->r == -1000 && this->y == -1000)
			return true;
		return false;
	}
public:
	float p, y, r;
};


#endif // ANGLE_H
#include <math.h>
#include "Point3.h"

Point3::Point3() 
{
	x = 0.0f;y = 0.0f;z = 0.0f;
}

Point3::Point3(float xx, float yy, float zz) 
{
	x = xx;y = yy;z = zz;
}

void Point3::set(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}

void Point3::set(Point3 p)
{
	set(p.getX(), p.getY(), p.getZ());
}


void Point3::draw(void)
{	glBegin(GL_POINTS);	
	glVertex3f((GLfloat)x, (GLfloat)y, (GLfloat)z);
	glEnd();
}

/***************************************************/

void Vector3::set(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}
void Vector3::set(Vector3 v)
{
	set(v.getX(), v.getY(), v.getZ());
}

float Vector3::dot(Vector3 b)
{
	return x*b.getX() + y*b.getY() + z*b.getZ();
}

Vector3 Vector3::cross(Vector3 b)	// return this X b
{
	Vector3 c(	y*b.getZ() - z*b.getY(), 
				z*b.getX() - x*b.getZ(), 
				x*b.getY() - y*b.getX());

	return c;
}

void Vector3::normalize()		// adjust this vector to unit length
{
	double sizeSq = x*x + y*y + z*z;
	float scaleFactor = 1.0/(float) sqrt(sizeSq);
	x *= scaleFactor;
	y *= scaleFactor;
	z *= scaleFactor;
}


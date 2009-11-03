#ifndef	point3_h
#define point3_h

#include <GL/GLUT.h>

class Point3 
{
public:
	Point3(); 	// constructor
	Point3(float xx, float yy, float zz); // constructor2
	Point3(Point3 &b) {x = b.getX(); y=b.getY(); z=b.getZ();}
	void set(float xx, float yy, float zz);
	void set(Point3 p);
	float getX() {return x;}
	float getY() {return y;}
	float getZ()  {return z;}
	void draw(void);				// draw this point
	float x,y,z;
};

class Vector3: public Point3
{
public: 
	Vector3() : Point3() {}
	Vector3(float xx, float yy, float zz) : Point3(xx, yy, zz) {}
	Vector3(const Vector3& b) {x = b.x; y=b.y; z=b.z;} 
	void set(float xx, float yy, float zz);
	void set(Vector3 v);
	float dot(Vector3 b);
	Vector3 cross(Vector3 b);
	void normalize();
};


#endif
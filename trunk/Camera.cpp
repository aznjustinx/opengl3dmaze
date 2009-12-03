#include <iostream>
#include <math.h>
#include "Camera.h"
#include "Constants.h"
using namespace std;


Camera::Camera()
{

}

void Camera::setModelViewMatrix(void)
{ // load modelview matrix with existing camera values
	float m[16];
	Vector3 eVec(eye.getX(), eye.getY(), eye.getZ());  // a vector version of eye
	m[0] = u.getX();	m[4] = u.getY();	m[8] = u.getZ();	m[12] = -eVec.dot(u);
	m[1] = v.getX();	m[5] = v.getY();	m[9] = v.getZ();	m[13] = -eVec.dot(v);
	m[2] = n.getX();	m[6] = n.getY();	m[10] = n.getZ();	m[14] = -eVec.dot(n);
	m[3] = 0.0f;		m[7] = 0.0f;		m[11] = 0.0f;		m[15] = 1.0f;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);				// load OpenGL's modelview matrix
}

void Camera::set(Point3 Eye, Point3 look, Vector3 up)
{ // create a modelview matrix and send it to OpenGL
	eye.set(Eye);			// store the given eye position
	n.set(eye.getX()-look.getX(), eye.getY()-look.getY(), eye.getZ()-look.getZ());
	u.set(up.cross(n));		// make u = up X n;
	n.normalize();
	u.normalize();
	v.set(n.cross(u));		// make v = n X u
	//setModelViewMatrix();	// tell OpenGL	
}

void Camera::setPerspective(float vAng, float asp, float nearD, float farD)
{
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
}


void Camera::setParallel(float left, float right, float bottom, float top, float nearD, float farD)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho((GLdouble)left,(GLdouble)right,(GLdouble)bottom,(GLdouble)top, (GLdouble)nearD, (GLdouble)farD);
}

void Camera::slide(float delU, float delV, float delN)
{
	float x = eye.getX() + delU*u.getX() + delV*v.getX() + delN*n.getX();
	float y = eye.getY() + delU*u.getY() + delV*v.getY() + delN*n.getY();
	float z = eye.getZ() + delU*u.getZ() + delV*v.getZ() + delN*n.getZ();
	eye.set(x, y, z);

	//setModelViewMatrix();
}

// Getur einungis farið í x y stefnu
void Camera::slideWallFrontBack(float delU, float delV, float delN)
{	
	float x = eye.getX() + delU*u.getX() + delV*v.getX() + delN*n.getX();
	float y = eye.getY() + delU*u.getY() + delV*v.getY() + delN*n.getY();
	float z = eye.getZ();// + delU*u.getZ() + delV*v.getZ() + delN*n.getZ();	
	eye.set(x, y, z);
}

// Getur einungis farið í z y stefnu
void Camera::slideWallSide(float delU, float delV, float delN)
{
	float x = eye.getX();// + delU*u.getX() + delV*v.getX() + delN*n.getX();
	float y = eye.getY() + delU*u.getY() + delV*v.getY() + delN*n.getY();
	float z = eye.getZ() + delU*u.getZ() + delV*v.getZ() + delN*n.getZ();
	eye.set(x, y, z);
}

// Getur einungis farið í y stefnu
void Camera::slideGravity(float delU, float delV, float delN)
{
	float x = eye.getX();// + delU*u.getX() + delV*v.getX() + delN*n.getX();
	float y = eye.getY() + delU*u.getY() + delV*v.getY() + delN*n.getY();
	float z = eye.getZ();// + delU*u.getZ() + delV*v.getZ() + delN*n.getZ();
	eye.set(x, y, z);
}

void Camera::roll(float angle)
{	// roll the camera through angle degrees
	// rotation about n-axis
	float cs = cos(RadPerDeg * angle);
	float sn = sin(RadPerDeg * angle);
	Vector3 t = u;		// remember old u
	u.set(	cs*t.getX() - sn*v.getX(),
			cs*t.getY() - sn*v.getY(),
			cs*t.getZ() - sn*v.getZ());
	v.set(	sn*t.getX() + cs*v.getX(),
			sn*t.getY() + cs*v.getY(),
			sn*t.getZ() + cs*v.getZ());
	//setModelViewMatrix();
}

void Camera::yaw(float angle)
{	// yaw the camera through angle degrees; 
	// rotation about v-axis
	float cs = cos(RadPerDeg * angle);
	float sn = sin(RadPerDeg * angle);
	Vector3 t = u;		// remember old u
	u.set(	cs*t.getX() + sn*n.getX(),
			cs*t.getY() + sn*n.getY(),
			cs*t.getZ() + sn*n.getZ());
	n.set(	-sn*t.getX() + cs*n.getX(),
			-sn*t.getY() + cs*n.getY(),
			-sn*t.getZ() + cs*n.getZ());
	//cout << "n.x: "<< n.getX() << endl;
	//cout << "n.z: "<< n.getZ() << endl;
	//setModelViewMatrix();
}

void Camera::pitch(float angle)
{	// pitch the camera through angle degrees; 
	// rotation about u-axis
	float cs = cos(RadPerDeg * angle);
	float sn = sin(RadPerDeg * angle);
	Vector3 t = v;		// remember old u
	v.set(	cs*t.getX() - sn*n.getX(),
			cs*t.getY() - sn*n.getY(),
			cs*t.getZ() - sn*n.getZ());
	n.set(	sn*t.getX() + cs*n.getX(),
			sn*t.getY() + cs*n.getY(),
			sn*t.getZ() + cs*n.getZ());
	//setModelViewMatrix();
}

Point3* Camera::getPosition()
{
	return &eye;
}

Vector3* Camera::getYaw()
{
	return &n;
}
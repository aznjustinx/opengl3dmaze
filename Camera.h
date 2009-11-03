#ifndef	camera_h
#define camera_h

#include "Point3.h"

class Camera {
private:
	Point3 eye;
	Vector3 u, v, n;
	float viewAngle, aspect, nearDist, farDist;	// view volume shape
public:
	Camera();
	void setModelViewMatrix();		// tell OpenGL where the camera is
	void set(Point3 Eye, Point3 look, Vector3 up);	// like gluLookAt
	void roll(float angle);							// roll it
	void yaw(float angle);							// yaw it
	void pitch(float angle);						// pitch it
	void slide(float delU, float delV, float delN);	// slide it
	// get ready for perspective projection
	void setPerspective(float vAng, float asp, float nearD, float farD);
	// get ready for parallel projection
	void setParallel(float left, float right, float bottom, float top, float nearD, float farD);

	Point3* getPosition();
};

#endif camera_h
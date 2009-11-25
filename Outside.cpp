#include <iostream>
#include <stdlib.h>
#include "Outside.h"
#include <GL/glut.h>
#include <gl/gl.h>

using namespace std;

Outside::Outside(void)
{
}

Outside::~Outside(void)
{
}

// Structure used in makePlate
struct Vertex {
    // GL_T2F_V3F
    float tu, tv;
    float x, y, z;
};

// makePlate
// Create a flat polygonal mesh of the given dimensions in the x/y plane
// 'dw' and 'dh' specify the number of vertices across the width and height 
void makePlate(float width, float height, int dw, int dh, float texWidth, float texHeight) {
	float widthRatio = width / texWidth;
	float heightRadio = height / texHeight;


	Vertex *v = new Vertex[dw*dh];
	float stepw = (width/(float)(dw-1));
	float steph = (height/(float)(dh-1));
	// Create Our Plate Verticies
	for (int i = 0; i < dw; i++) {
		for (int j = 0; j < dh; j++) {
			v[i*dh+j].x = i*stepw;				
			v[i*dh+j].y = j*steph;						
			v[i*dh+j].z = 0;				
			v[i*dh+j].tu = ((float)i/ (float)(dw-1) * widthRatio);
			v[i*dh+j].tv = ((float)j/ (float)(dh-1) * heightRadio);
		}
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	for (int i = 0; i < dw - 1; i++) {
		// Draw A Triangle Strip For Each Column Of Our Mesh
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < dh; j++) {
			glTexCoord2f(v[i*dh+j].tu, v[i*dh+j].tv);
			glVertex3f(v[i*dh+j].x, v[i*dh+j].y, v[i*dh+j].z);	// Draw Vertex
			glTexCoord2f(v[(i+1)*dh+j].tu, v[(i+1)*dh+j].tv);
			glVertex3f(v[(i+1)*dh+j].x, v[(i+1)*dh+j].y, v[(i+1)*dh+j].z);// Draw Vertex
		}
		glEnd();
	}
	delete v;
}

void Outside::display() {
	//cout<<"Outside::display";
}

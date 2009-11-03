/*
Stefan Einarsson
stefane07@ru.is

Skilaverkefni 3
Tölvugrafik 
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Maze.h"
#include "Main.h"

using namespace std;

Maze maze;

// þegar breyting er
void Main::handleResize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
	void gluPerspective(	GLdouble  	fovy, 
 							GLdouble  	aspect, 
 							GLdouble  	zNear, 
 							GLdouble  	zFar);
	*/
	gluPerspective(	45.0f, 
					(double)width / (double)height, 
					0.1f, 
					100.0f);	
	// glMatrixMode verður að vera fyrir neðan allt hér...
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity();
}


// sér um að kalla á og birta objectana
void Main::display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity(); // Til að fara aftur að miðju
	maze.loadLightning();
	
	maze.drawBox();

	glutSwapBuffers();
}


Main::Main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(640, 480);			// stærð glugga
	glutInitWindowPosition(100,100);		// init staðsetning glugga
	glutCreateWindow("Skilaverkefni 3");	// nafn glugga


	maze.initRendering();						// inits 3D rendering

	glutDisplayFunc(&Main::display);			// Teiknar hlutina
	glutReshapeFunc(&Main::handleResize);

	glutMainLoop();    
}

Main::~Main(void)
{
}
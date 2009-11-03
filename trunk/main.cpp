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
#include "Player.h"
#include "Maze.h"

using namespace std;

Player player;
Maze maze;

float _angle = 30.0f;
float _cameraAngle = 0.0f;

//const float PI = 3.141592654f;
const float piover180 = 0.0174532925f; // til að skipta milli rad og deg



void  specialKeyDown(int  key,  int  x,  int  y)
{
	player.specialKeyDown(key, x, y);
}

void  specialKeyUp(int  key,  int  x,  int  y)
{
	player.specialKeyUp(key, x, y);
}


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
}

// þegar breyting er
void handleResize(int width, int height)
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

void loadLightning()
{
	//Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

// sér um að kalla á og birta objectana
void display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity(); // Til að fara aftur að miðju
	player.display();
	loadLightning();
	
	maze.drawBox();

	glutSwapBuffers();
}

void updateScene(int id)
{
	glutTimerFunc(32,updateScene,0);
	if(player.upKeyPressed)
	{
		player.moveUp();
	}
	if(player.downKeyPressed)
	{
		player.moveDown();
	}
	if(player.leftKeyPressed)
	{
		player.moveLeft();
	}
	if(player.rightKeyPressed)
	{
		player.moveRight();
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed
}

void mouse(int x, int y) {
	player.mouse(x, y);
}
	
// main fallið
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(640, 480);			// stærð glugga
	glutInitWindowPosition(100,100);		// init staðsetning glugga
	glutCreateWindow("Skilaverkefni 3");	// nafn glugga
	initRendering();						// inits 3D rendering

	glutDisplayFunc(display);			// Teiknar hlutina
	glutReshapeFunc(handleResize);

	// player input
	glutPassiveMotionFunc(mouse); //check for mouse movement
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutIgnoreKeyRepeat(1);
	glutTimerFunc(32,  updateScene,  0);
	//glutSpecialFunc(myArrowKeys);		// Virkjar örvatakkana
	glutMainLoop();    
}

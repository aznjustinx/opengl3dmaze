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
#include "Mesh.h"

using namespace std;

const int DELAY_TIME = 32;
Player player;
Maze maze;
Mesh mesh;

void specialKeyDown(int  key,  int  x,  int  y)
{
	player.specialKeyDown(key, x, y);
}

void specialKeyUp(int  key,  int  x,  int  y)
{
	player.specialKeyUp(key, x, y);
}

void keyboardDown(unsigned char key, int x, int y)
{
	player.keyboardDown(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y)
{
	player.keyboardUp(key, x, y);
}

//Initializes 3D rendering
void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
	glClearColor(0., 0., 0., 0.);

	mesh.readFile("BARNSIMP.3VN");
}

// þegar breyting er
void resize(int width, int height)
{
	cout<<"handleResize";
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
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}

void displayLightning()
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

void displayLightningBook()
{
	float lightArr[4];
	lightArr[0] = 1.0;
	lightArr[1] = 1.0;
	lightArr[2] = 1.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 1.0;
	lightArr[3] = 0.0f;
	glLightfv(GL_LIGHT0, GL_POSITION, lightArr);
}

// sér um að kalla á og birta objectana
void display()
{	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayLightning();
	player.display();
	
	//mesh.draw();
	
	maze.drawBox();

	glutSwapBuffers();
}

void update(int id)
{
	glutTimerFunc(DELAY_TIME, update, 0);
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
	glutCreateWindow("3d Maze");	// nafn glugga
	glutReshapeFunc(resize);
	init();						// inits 3D rendering

	glutDisplayFunc(display);			// Teiknar hlutina
	glutTimerFunc(DELAY_TIME, update, 0);
	
	// player input
	glutPassiveMotionFunc(mouse); //check for mouse movement
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutIgnoreKeyRepeat(1);
	
	glutMainLoop();    
}

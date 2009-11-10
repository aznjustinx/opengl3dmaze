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
#include "main.h"
#include "Collision.h"

using namespace std;

// enums
const int Z_N_AXIS = 0;
// constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int DELAY_TIME = 32;
const float SLIDE_INCREMENT = 0.5;
const float ROT_INCREMENT = 5.0;
GLfloat COL_GREEN[3] = { 0., 1., 0. };
// globals
Player player;
Maze maze;
Collision collision;


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

void mouse(int x, int y) {
	//player.mouse(x, y);
}

void newGame()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDisable (GL_BLEND);

	player.set(Point3(12., 0., 2.5), Point3(0., 0., -1.), Vector3(0., 1., 0.));
	player.yaw(ROT_INCREMENT * 15);

}

//Initializes 3D rendering
void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0., 0., 0., 0.);
	
	player.set(Point3(12., 0., 2.5), Point3(0., 0., -1.), Vector3(0., 1., 0.));
	player.yaw(ROT_INCREMENT * 15);

	collision.init(&player, &maze);
	maze.init();
	Point3 point = maze.getFinishPos();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	player.setPerspective( 45.0f, (double)width / (double)height, 0.1f, 100.0f);
}

void displayLightning()
{
	float lightArr[4];
	lightArr[0] = .7;
	lightArr[1] = .7;
	lightArr[2] = .7;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightArr);
	lightArr[0] = .1;
	lightArr[1] = .1;
	lightArr[2] = .1;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 350.;
	lightArr[2] = 250.;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_POSITION, lightArr);

	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = .4;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 1.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightArr);
	lightArr[0] = -250.;
	lightArr[1] = 350.;
	lightArr[2] = 100.;
	lightArr[3] = 1.0f; // The position is a point now so the light has position
	glLightfv(GL_LIGHT1, GL_POSITION, lightArr);

	lightArr[0] = 0.;
	lightArr[1] = .2;
	lightArr[2] = 0.;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.;
	lightArr[1] = .9;
	lightArr[2] = 0.;
	lightArr[3] = 1.f;
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightArr);
	lightArr[0] = 250.;
	lightArr[1] = 350.;
	lightArr[2] = 100.;
	lightArr[3] = 1.0f; // The position is a point now so the light has position
	glLightfv(GL_LIGHT2, GL_POSITION, lightArr);

}

void displayText(const char * message, GLfloat x, GLfloat y/*, GLfloat z*/, int fontSize, GLfloat color[]) {
	glColor3f(color[0], color[1], color[2]);
	glRasterPos2f(x, y);
	//glRasterPos3f(x, y, z);
	while (*message) {
		if (fontSize == 18) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
		}
		if (fontSize == 10) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *message++);
		}
	}
}

void displayWinText() {
	displayText("Congratulations! You won the game", (WINDOW_WIDTH / 2) - 135, (WINDOW_HEIGHT / 2) + 20, 18, COL_GREEN);
	displayText("Press 'r' to restart game", (WINDOW_WIDTH / 2) - 85, (WINDOW_HEIGHT / 2), 18, COL_GREEN);
	displayText("Press 'q' to quit game", (WINDOW_WIDTH / 2) - 75, (WINDOW_HEIGHT / 2) - 20, 18, COL_GREEN);
}

// sér um að kalla á og birta objectana
void display()
{	
	
	player.setModelViewMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (collision.checkFinish())
	{
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glMatrixMode(GL_PROJECTION); 
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity(); 
		gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		displayWinText();
		//cout<<"FINISHED";
	}
	else {
		displayLightning();
		maze.displayMaze();
		
	}
	glutSwapBuffers();
	glFlush();
}

void update(int id)
{	
	glutTimerFunc(DELAY_TIME, update, 0);
	if (collision.checkFinish())
	{
		cout<<"if inUpdate";
		if(player.restartPressed)
		{
			newGame();
		}
		if(player.quitPressed)
		{
			exit(EXIT_SUCCESS);
		}

	}
	else {
		cout<<"else inUpdate";
	

	if(player.upKeyPressed)
	{
		//Point3* pos = player.getPosition();
		//cout<<"eye: x: "<<pos->getX()<<" y: "<<pos->getY()<<" z: "<<pos->getZ()<<"\n";
		if ( collision.check() != 0) {	
			if(collision.check() == 1 || collision.check() == 3 )
			{				
				player.slideWallFrontBack(0.0f, 0.0f, -SLIDE_INCREMENT);
			}
			else if(collision.check() == 2)
			{	
				player.slideWallSide(0.0f, 0.0f, -SLIDE_INCREMENT);
			}
			else if(collision.check() == 4)
			{
				player.slide(0.0f, 0.0f, 0.0f);
			}
		}
		else
		{
			player.slide(0.0f, 0.0f, -SLIDE_INCREMENT);
		}
	}

	if(player.downKeyPressed)
	{
		player.slide(0.0f, 0.0f, SLIDE_INCREMENT);
		if ( collision.check() != 0) {
			player.slide(0.0f, 0.0f, -SLIDE_INCREMENT);
		}
	}
	if(player.leftKeyPressed)
	{
		player.yaw(-ROT_INCREMENT);
	}
	if(player.rightKeyPressed)
	{
		player.yaw(ROT_INCREMENT);
	}
	if (player.floatUpPressed)
	{
		player.slide(0., SLIDE_INCREMENT, 0.);
	}
	if (player.floatDownPressed)
	{
		player.slide(0., -SLIDE_INCREMENT, 0.);
	}
	


	maze.updateObjects();
	}
	glutPostRedisplay(); //Tell GLUT that the display has change	
}

// main fallið
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			// stærð glugga
	glutInitWindowPosition(600,100);		// init staðsetning glugga
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
/*
Stefan Einarsson
stefane07@ru.is

Skilaverkefni 3
T�lvugrafik 
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Player.h"
#include "Maze.h"
#include "Mesh.h"
#include "main.h"
#include "Collision.h"
#include <sstream>
#include <string>

using namespace std;

// enums
const int Z_N_AXIS = 0;
// constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int DELAY_TIME = 24;
const float SLIDE_INCREMENT = 0.3;
//const float GRAVITY = 0.2;
const float ROT_INCREMENT = 3.;
GLfloat COL_GREEN[3] = { 0., 1., 0. };
GLfloat COL_WHITE[3] = { 1., 1., 1. };
GLfloat COL_RED[3] = { 1., 0., 0. };
// globals
Player player;
Maze maze;
Collision collision;
bool moved = false;
bool gameOver;
bool debugMode;
float weakSource = 0.285;
float strongSource = 0.57;


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

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	player.setPerspective( 45.0f, (double)width / (double)height, 0.1f, 100.0f);
}

/*void displayLightning()
{
	float lightArr[4];
	lightArr[0] = weakSource;
	lightArr[1] = weakSource;
	lightArr[2] = strongSource;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightArr);
	lightArr[0] = weakSource;
	lightArr[1] = weakSource;
	lightArr[2] = strongSource;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightArr);
	lightArr[0] = 0.;
	lightArr[1] = 35.;
	lightArr[2] = 0.;
	lightArr[3] = 0.;
	glLightfv(GL_LIGHT0, GL_POSITION, lightArr);

	Point3* pos = player.getPosition();
	lightArr[0] = 1.0;
	lightArr[1] = 1.0;
	lightArr[2] = 1.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightArr);
	lightArr[0] = 1.0;
	lightArr[1] = 1.0;
	lightArr[2] = 1.0;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightArr);
	lightArr[0] = 0.;
	lightArr[1] = 35.;
	lightArr[2] = 0.;
	lightArr[3] = 0.;
	glLightfv(GL_LIGHT1, GL_POSITION, lightArr);

	lightArr[0] = 0.2;
	lightArr[1] = 0.;
	lightArr[2] = 0.;
	lightArr[3] = 1.0f;
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightArr);
	lightArr[0] = 0.7;
	lightArr[1] = 0.;
	lightArr[2] = 0.;
	lightArr[3] = 1.f;
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightArr);
	lightArr[0] = 0.0;
	lightArr[1] = 0.0;
	lightArr[2] = 0.0;
	lightArr[3] = 1.f;
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightArr);
	lightArr[0] = 250.;
	lightArr[1] = 350.;
	lightArr[2] = 100.;
	lightArr[3] = 1.0f; // The position is a point now so the light has position
	glLightfv(GL_LIGHT2, GL_POSITION, lightArr);
}*/

void displayText(const char* message, GLfloat x, GLfloat y, int fontSize, GLfloat color[]) {
	glColor3f(color[0], color[1], color[2]);
	glRasterPos2f(x, y);
	//glRasterPos3f(x, y, z);
	while (*message) {
		if (fontSize == 18) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
		}
		if (fontSize == 10) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
		}
	}
}

void displayGameFinished() {
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	displayText("Congratulations! You won the game", (WINDOW_WIDTH / 2) - 135, (WINDOW_HEIGHT / 2) + 20, 18, COL_WHITE);
	displayText("Press 'q' to quit game", (WINDOW_WIDTH / 2) - 75, (WINDOW_HEIGHT / 2) - 20, 18, COL_WHITE);
}

void push2D()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix();
	glLoadIdentity();
}

void pop2D()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

}	

// s�r um a� kalla � og birta objectana
void display()
{	
	char txtScore[5];
	sprintf(txtScore, "%d", player.getScore());
	player.setModelViewMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameOver)
	{
		push2D();
		displayText("You finished with score ", (WINDOW_WIDTH / 2) - 100, (WINDOW_HEIGHT / 2) + 30, 18, COL_WHITE);
		displayText(txtScore, (WINDOW_WIDTH / 2) + 50, (WINDOW_HEIGHT / 2) + 30, 18, COL_WHITE);
		displayText("Press 'q' to quit", (WINDOW_WIDTH / 2) - 100, (WINDOW_HEIGHT / 2), 18, COL_WHITE);
		pop2D();
	}
	else {
		//displayLightning();
		maze.displayMaze();
		push2D();
		
		displayText("SCORE:", 10, 10, 18, COL_WHITE);
		displayText(txtScore, 100, 10, 18, COL_WHITE);
		pop2D();
	}
	glutSwapBuffers();
	glFlush();
}

void update(int id)
{	
	Point3* pos = player.getPosition();
	
	if (pos->getY() < 12 && pos->getY() > 6.3)
	{
		//cout << pos->getY() << " : ";
		weakSource -= 0.03;
		strongSource -= 0.03;
	}

	glutTimerFunc(DELAY_TIME, update, 0);
	if (collision.won()) gameOver = true;
	if (gameOver)
	{
		//gameOver = true;
		player.disabled = true;
		glutPostRedisplay(); //Tell GLUT that the display has change
	}
	else {
		if (player.headlightToggle)
		{
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
		}
		else
		{
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
		}

		// gravity
		if (moved == true)
			if(collision.gravity() == false)
				player.slideGravity(0., -SLIDE_INCREMENT, 0.);
				collision.goodies();

		if(player.jumpKeyPressed)
		{
			player.slide(0., SLIDE_INCREMENT, 0.);
		}
		if(player.upKeyPressed)
		{
			//Point3* pos = player.getPosition();
			//cout<<"eye: x: "<<pos->getX()<<" y: "<<pos->getY()<<" z: "<<pos->getZ()<<"\n";
			if ( collision.check(1) != 0) {	
				if(collision.check(1) == 1 || collision.check(1) == 3 )
				{				
					player.slideWallFrontBack(0.0f, 0.0f, -SLIDE_INCREMENT);
				}
				else if(collision.check(1) == 2)
				{	
					player.slideWallSide(0.0f, 0.0f, -SLIDE_INCREMENT);
				}
				else if(collision.check(1) == 4)
				{
					player.slide(0.0f, 0.0f, 0.0f);
				}
			}
			else
			{
				player.slide(0.0f, 0.0f, -SLIDE_INCREMENT);
			}

			moved = true;
		}

		if(player.downKeyPressed)
		{		
			if ( collision.check(0) != 0) {
				//player.slide(0.0f, 0.0f, -SLIDE_INCREMENT);

				if(collision.check(0) == 1 || collision.check(0) == 3 )
				{				
					player.slideWallFrontBack(0.0f, 0.0f,SLIDE_INCREMENT);
				}
				else if(collision.check(0) == 2)
				{	
					player.slideWallSide(0.0f, 0.0f, SLIDE_INCREMENT);
				}
				else if(collision.check(0) == 4)
				{
					player.slide(0.0f, 0.0f, 0.0f);
				}
			}
			else
				player.slide(0.0f, 0.0f, SLIDE_INCREMENT);

			moved = true;
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
		if (player.floatDownPressed)// && player.getPosition()->getY() > 0)
		{
			player.slide(0., -SLIDE_INCREMENT, 0.);
		}

		maze.updateObjects();
		glutPostRedisplay(); //Tell GLUT that the display has change
	}
	if(player.quitPressed)
	{
		exit(EXIT_SUCCESS);
	}	
}

void init()
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); // headlight in player
	// turning off global ambient light.
	GLfloat amb[] = {0, 0, 0, 0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	
	gameOver = false;
	player.debugMode = false;
	
	
	collision.init(&player, &maze);
	maze.init();
	float x, y = 12/*9*/, z;
	if (player.debugMode) {
		x = 20.;
		z = -20;
	}
	else
	{
		x = 14.;
		z = -10.;
	}
	player.set(Point3(x, y, z), Point3(0., y, 0.), Vector3(0., 1., 0.));
	player.yaw(123);
}

// main falli�
void main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			// st�r� glugga
	glutInitWindowPosition(600,100);		// init sta�setning glugga
	glutCreateWindow("3d Maze");	// nafn glugga
	glutReshapeFunc(resize);
	glClearColor(0., 0., 0., 0.);

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
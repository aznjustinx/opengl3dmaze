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
#include "Point3.h"

Point3 wall;
Point3 pMap[100];
double size = 0.0;

using namespace std;

class Point {
public:
	double x,z;
	Point() { x = 0.0; z = 0.0; }
};

int numberOfWalls = 0;

Point P;

int getNumberOfWalls()
{
	return numberOfWalls;
}

GLuint texture; //the array for our texture
GLuint texture2; //the array for our second texture

int cMap[10][10] = { //our map
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 'G', 1, 1, 1, 1, 1},
};

Maze::Maze()
{

}

Maze::~Maze()
{
}

Point3* Maze::getPosition()
{
	//return &wall;
	return pMap;
}

Point3* Maze::setPosition(double x, double y, double z, int pos)
{
	pMap[pos] = Point3(x,y,z);
	//cout << pMap[10].x << ',' << pMap[10].y << ',' << pMap[10].z << endl;
	return false;
}

// draws 3D box
void Maze::drawMaze()
{
	
//	glTranslatef(-12, 0, -20); //translate back a bit to view the map correctly
	//glTranslatef(0, 0, 0); //translate back a bit to view the map correctly
	drawBox();
		
	glLoadIdentity(); // Til að núlla hreyfingu á angle
}




// draws 3D box
void Maze::drawBox()
{
	numberOfWalls = 0;
	for (int i = 0; i < 10; i++) //loop through the height of the map
	{
		for (int j = 0; j < 10; j++) //loop through the width of the map
		{
			if (cMap[i][j] == 0) //if the map at this position contains a 0
			{				
				//glBindTexture( GL_TEXTURE_2D, texture ); //bind our grass texture to our shape
				glColor3f(0,1,1);
				glPushMatrix(); //push the matrix so that our translations only affect this tile
			
				glTranslatef(j*3, 0, -i*3); //translate the tile to where it should belong				
				drawFloor();
	
				glEnd();
				glPopMatrix(); //pop the matrix
			}
			else if (cMap[i][j] == 'G')
			{
				glColor3f(1,1,1);
				glPushMatrix(); //push the matrix so that our translations only affect this tile
			
				glTranslatef(j*3, 0, -i*3); //translate the tile to where it should belong				
				drawFloor();
	
				glEnd();
				glPopMatrix(); //pop the matrix
			}
			else //otherwise
			{
				glColor3f(0,1,0);
				glPushMatrix(); //push the matrix so that our translations only affect this tile
			
				glTranslatef(j*3, 0, -i*3); //translate the tile to where it should belong
		/*		P.x = j*3;
				P.z = -i*3;*/
				
				setPosition(j*3,0,-i*3,j+i);

				//cout << '(' << P.x << ',' << P.z << ')' << endl;
				//drawWall();
				drawSolidCube(3);
	
				glEnd();
				glPopMatrix(); //pop the matrix
				//glBindTexture( GL_TEXTURE_2D, texture2 ); //bind our dirt texture to our shape
				numberOfWalls++;
			}
			
			
		} //end first loop
	} //end second loop
	/*Point3* map = getPosition();
	cout << map[5].z << endl;
	system("PAUSE");*/
	cout << numberOfWalls << endl;
}

void Maze::drawSolidCube () 
{
    glColor3f(1.0, 0.0, 0.0); //color the cube red
    //glutWireCube(3); //draw a wired cube with side lengths of 2
	glutSolidCube(size);
}

void Maze::drawFloor()
{
	glRotatef(-90,1,0,0);
	glBegin(GL_POLYGON);
	//bottom
	glNormal3f(0.0f, 0.0f, -1.49);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.6f, -1.6f, -1.49);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.6f, 1.6f, -1.49);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.6f, 1.6f, -1.49);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.6f, -1.6f, -1.49);
	glRotatef(90,0,1,0);

	glEnd();
	glLoadIdentity();
}

void Maze::drawWall()
{
	//glTranslatef(0.0f, 0.0f, -8.0f); // zooma út
	//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	
	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	
	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	
	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	
	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.5f);

	glEnd();

	glRotatef(-90,1,0,0);
	// ceiling
	glBegin(GL_POLYGON);
	//bottom
	glNormal3f(0.0f, 0.0f, 1);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.5f, 1);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.5f, 1);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.5f, 1);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.5f, 1);
	//glRotatef(90,0,1,0);
	glRotatef(90,1,0,0);
	glEnd();
	
	glEnd();
	glLoadIdentity(); // Til að núlla hreyfingu á angle
}
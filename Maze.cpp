/*
Stefan Einarsson
stefane07@ru.is
Egill Antonsson

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

using namespace std;

Point3 wall;
Point3 pMap[100];
const float TILE_SIZE = 3.0;
int numberOfCubes = 0;

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
	{1, 1, 1, 1, 9, 1, 1, 1, 1, 1},
};

int Maze::getNumberOfWalls()
{
	return numberOfCubes;
}

Maze::Maze()
{	
}

Maze::~Maze()
{
}

void Maze::init()
{
	cout<<"MAZE INIT";
	finishSign = new Mesh();
	if (finishSign->readFile("FINISH_SIGN.3VN") == -1)
	{
		cout<<"Error in read file";
	}
}

Point3* Maze::getPosition()
{
	return pMap;
}

void Maze::setPosition(float x, float y, float z, int pos)
{
	pMap[pos] = Point3(x,y,z);
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
	numberOfCubes = 0;
	for (int i = 0; i < 10; i++) //loop through the height of the map
	{
		for (int j = 0; j < 10; j++) //loop through the width of the map
		{
			Point3* point = new Point3(j*TILE_SIZE, 0, -i*TILE_SIZE);
			glPushMatrix();
			glTranslatef(point->getX(), point->getY(), point->getZ()); //translates to where it should belong	
			switch (cMap[i][j])
			{
				case 0 :
				//++glColor3f(0,1,1);
				drawFloor();
				break;

				case 1 :
				setPosition(point->getX(), point->getY(), point->getZ(), numberOfCubes);							
				//glutWireCube(size); //draw a wired cube with side lengths of 2
				glutSolidCube(TILE_SIZE);
				numberOfCubes++;
				case 9 :
				//glColor3f(1,1,1);
				drawFloor();
				finishSign->draw();
				break;
			}
			glPopMatrix();
			delete point;
		} //end first loop
	} //end second loop
}

void Maze::drawFloor()
{
	//glPushMatrix();
	//glRotatef(-90,1,0,0);
	glBegin(GL_POLYGON);
	//bottom
	//glNormal3f(0.0f, 0.0f, -1.49);
	//glColor3f(1,1,0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(-1.6f, -1.6f, -1.49);
	glVertex3f(-1.0f, 0.5f, -1.0f);
	//glVertex3f(-1.6f, 1.6f, -1.49);
	glVertex3f(1.0f, 0.5f, -1.0f);
	//glVertex3f(1.6f, 1.6f, -1.49);
	glVertex3f(1.0f, 0.5f, 1.0f);
	//glVertex3f(1.6f, -1.6f, -1.49);
	glVertex3f(-1.0f, 0.5f, 1.0f);
	glEnd();
	//glRotatef(90,0,1,0);
	//glPopMatrix();
	
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
	//glNormal3f(-5.0f, 0.0f, -1.0f);
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
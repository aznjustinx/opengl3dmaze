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

int cMap[MAP_SIZE][MAP_SIZE] = {
	{1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 9, 1, 1, 1, 1, 1},};

Maze::Maze()
{	
}

Maze::~Maze()
{
}

/*int Maze::getNumberOfWalls()
{
	return numberOfCubes;
}*/

void Maze::init()
{
	cout<<"MAZE INIT";
	finishSign = new Mesh();
	if (finishSign->readFile("FINISH_SIGN.3VN") == -1)
	{
		cout<<"Error in read file";
	}
	finishRotAngle = 0;
	nrOfCubes = 0;

	for (int i = 0; i < MAP_SIZE; i++) //loop through the height of the map
	{
		for (int j = 0; j < MAP_SIZE; j++) //loop through the width of the map
		{
			if (cMap[i][j] == 1)
			{
				cubesPos[nrOfCubes] = Point3(j*TILE_SIZE, 0, -i*TILE_SIZE);
				nrOfCubes++;
			}

			if (cMap[i][j] == 9)
			{
				finishPos = Point3(j*TILE_SIZE, 0, -i*TILE_SIZE);
			}
		}
	}
}

Point3* Maze::getCubesPos()
{
	return cubesPos;
}

int Maze::getNrOfCubes()
{
	return nrOfCubes;
}

/*Point3* Maze::getFinishPos()
{
	return finishPos;
}*/

void Maze::updateObjects()
{
	if (finishRotAngle == 359) {
		finishRotAngle = 0;
	} else {
		++finishRotAngle;
	}
}

void Maze::displayMaze()
{
	
	for (int i = 0; i < MAP_SIZE; i++) //loop through the height of the map
	{
		for (int j = 0; j < MAP_SIZE; j++) //loop through the width of the map
		{
			Point3* point = new Point3(j*TILE_SIZE, 0, -i*TILE_SIZE);
			glPushMatrix();
			
			
			glTranslatef(point->getX(), point->getY(), point->getZ()); //translates to where it should belong	
			switch (cMap[i][j])
			{
				case 0:
				displayFloor();
				//displayFinishSign();
				break;

				case 1:
				materialColor(.75164, .60648, .22648, 1., .75164, .60648, .22648, 1., .75164, .60648, .22648, 1., 51.2);
				//glutSolidCube(TILE_SIZE);
				glutWireCube(TILE_SIZE);
				break;

				case 9:
				displayFloor();
				displayFinishSign();
				//finishSign->draw();
				break;
			}
			glPopMatrix();
			delete point;
		} //end first loop
	} //end second loop
}

void Maze::materialColor(float dif0, float dif1, float dif2, float dif3
						 , float spec0, float spec1, float spec2, float spec3
						 , float amb0, float amb1, float amb2, float amb3, float shininess)
{
	float materialArr[4];
	materialArr[0] = dif0;
	materialArr[1] = dif1;
	materialArr[2] = dif2;
	materialArr[3] = dif3;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialArr);
	materialArr[0] = spec0;
	materialArr[1] = spec1;
	materialArr[2] = spec2;
	materialArr[3] = spec3;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialArr);
	materialArr[0] = amb0;
	materialArr[1] = amb1;
	materialArr[2] = amb2;
	materialArr[3] = amb3;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialArr);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}


void Maze::displayFinishSign()
{	
	materialColor(.4, .4, .4, 1., .774597, .774597, .774597, 1., .25, .25, .25, 1., 76.8);
	glPushMatrix();	
	glTranslatef(0., -TILE_SIZE/2 + .1, 0.);
	glRotatef(finishRotAngle, 0., 1., 0.);
	finishSign->draw();
	glPopMatrix();
}

void Maze::displayFloor()
{
	materialColor(.2775, .2775, .2775, 1., .773911, .773911, .773911, 1., .23135, .23135, .23135, 1., 89.6);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-TILE_SIZE/2, -TILE_SIZE/2, -TILE_SIZE/2);
	glVertex3f(TILE_SIZE/2, -TILE_SIZE/2, -TILE_SIZE/2);
	glVertex3f(TILE_SIZE/2, -TILE_SIZE/2, TILE_SIZE/2);
	glVertex3f(-TILE_SIZE/2, -TILE_SIZE/2, TILE_SIZE/2);
	glEnd();
}

void Maze::displayWall()
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
/*
Stefan Einarsson
stefane07@ru.is
Egill Antonsson

Skilaverkefni 4
Tölvugrafik 
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Maze.h"
#include "Point3.h"
#include <gl/gl.h>
#include <FreeImage.h>
#include <vector>
#include "main.h"

using namespace std;

vector <vector <int> > v; /*two dimensions*/
//   0  1  2  3  4  5  6  7  8  9
int cMap[MAP_SIZE_Z][MAP_SIZE_X] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,9},
	{1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,1,0,0,0,0},
	{1,0,0,0,1,1,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1},};

int dMap[MAP_SIZE_Z][MAP_SIZE_X] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,8,8,0,0,0,1},
	{1,0,0,0,8,8,0,0,0,1},
	{1,0,0,0,8,8,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},};

int eMap[MAP_SIZE_Z][MAP_SIZE_X] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,8,8,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,1,0,1},
	{1,0,0,1,0,0,1,0,0,1},
	{1,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},};

int fMap[MAP_SIZE_Z][MAP_SIZE_X] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,0,0,1},
	{1,0,0,1,8,8,1,0,0,1},
	{1,0,0,1,8,8,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},};

// Holds all texture objects
/*GLuint g_textures[MAX_TEXTURES];
enum { TEX_FLOOR, TEX_WALL, TEX_GOODIE, TEX_TILES, TEX_BRICKS };*/

Maze::Maze()
{
}

Maze::~Maze()
{
}

void Maze::init()
{
	finished = false;
	finishSign = new Mesh();
	if (finishSign->readFile("FINISH_SIGN.3VN") == -1)
	{
		cout<<"Error in read file";
	}
	finishRotAngle = 0;
	
	/*ghostCount = 4;
	while (ghostCount == 0) {

	if (rand()%500 == 0) {
	pieces
	}*/

	for (int y = 0; y < MAP_SIZE_Y; y++) //loop through the LEVELS of the map
	{
		vector<int> temp;
		for (int z = 0; z < MAP_SIZE_Z; z++) //loop through the height of the map
		{
			for (int x = 0; x < MAP_SIZE_X; x++) //loop through the width of the map
			{
				if (y==0)
					temp.push_back(cMap[z][x]);
				else if(y==1)
					temp.push_back(dMap[z][x]);
				else if(y==2)
					temp.push_back(eMap[z][x]);
				else if(y==3)
					temp.push_back(fMap[z][x]);
					//cout << cMap[z][x]<< endl;
			}
		}
		v.push_back(temp);
	}

	for (int y = 0; y < MAP_SIZE_Y; y++) //loop through the LEVELS of the map
	{
		int zx = 0;
		for (int z = 0; z < MAP_SIZE_Z; z++) //loop through the height of the map
		{
			for (int x = 0; x < MAP_SIZE_X; x++) //loop through the width of the map
			{	
				if (v[y][zx] == 1)
				{
					cubesPos[y][z][x] = Point3(x*TILE_SIZE,y*3 , -z*TILE_SIZE);
					floorPos[y][z][x] = Point3(x*TILE_SIZE,y , -z*TILE_SIZE);
				}

				else if (v[y][zx] == 9)
				{
					finishPos = Point3(x*TILE_SIZE, y, -z*TILE_SIZE);
				}
				else if(v[y][zx] == 0) {
					floorPos[y][z][x] = Point3(x*TILE_SIZE,y, -z*TILE_SIZE);
					pieces[y][z][x] = new Piece();
				}
				zx++;
			}							
		}
	}
	
	main::materialColor(1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 100);
	
	glGenTextures(MAZE_MAX_TEXTURES, g_MazeTextures);
	main::loadImage(g_MazeTextures[TEX_FLOOR], ".\\TilesOrnate.jpg");
	main::loadImage(g_MazeTextures[TEX_WALL], ".\\BrickLargeBare.jpg");
	
}

Point3 Maze::getCubesPos(int y,int z, int x)
{
	return cubesPos[y][z][x];
}

Point3 Maze::getFloorPos(int y,int z, int x)
{
	return floorPos[y][z][x];
}

Point3 Maze::getFinishPos()
{
	return finishPos;
}

void Maze::updateObjects()
{
	if (finishRotAngle == 359) {
		finishRotAngle = 0;
	} else {
		++finishRotAngle;
	}
	//for (int i = 0; i < 
}

void Maze::displayMaze()
{
	for (int y = 0; y < MAP_SIZE_Y; y++) //loop through the LEVELS of the map
	{
		int zx = 0;
		for (int z = 0; z < MAP_SIZE_Z; z++) //loop through the height of the map
		{
			for (int x = 0; x < MAP_SIZE_X; x++) //loop through the width of the map
			{
				Point3* point = new Point3(x*TILE_SIZE, y*TILE_SIZE, -z*TILE_SIZE);
				glPushMatrix();								
				glTranslatef(point->getX(), point->getY(), point->getZ()); //translates to where it should belong	
				switch (v[y][zx])
				{
					case 0:
					displayFloor();
					pieces[y][z][x]->display();
					break;

					case 1:
					//materialColor(.75164, .60648, .22648, 1., .75164, .60648, .22648, 1., .75164, .60648, .22648, 1., 51.2);
					//glutSolidCube(TILE_SIZE);							
					//glutWireCube(TILE_SIZE);
					displayFloor();

					// display cube ceiling?
					if (y+1 == MAP_SIZE_Y)
						displayCube(true);
					else 
						displayCube(false);
					break;

					case 9:
					displayFloor();
					displayFinishSign();
					break;
				}

				glPopMatrix();
				delete point;
				zx++;
			} //end first loop
		} //end second loop
	}
}

void Maze::displayFinishSign()
{	
	main::materialColor(.4, .4, .4, 1., .774597, .774597, .774597, 1., .25, .25, .25, 1., 76.8);
	glPushMatrix();	
	glTranslatef(0., -TILE_SIZE/2 + .5, 0.);
	glRotatef(finishRotAngle, 0., 1., 0.);
	finishSign->draw();
	glPopMatrix();
}

void Maze::displayFloor()
{	
	main::materialColor(.4, .4, .4, 1., .1, .1, .1, 1., .4, .4, .4, 1., 25);
	glBindTexture( GL_TEXTURE_2D, g_MazeTextures[TEX_FLOOR] );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();		
	glTranslatef(-TILE_SIZE/2, -TILE_SIZE/2, -TILE_SIZE/2);
	glRotatef(90., 1., 0., 0.);
	main::makePlate(TILE_SIZE, TILE_SIZE, NR_OF_VERTEXES, NR_OF_VERTEXES, TILE_SIZE, TILE_SIZE);
	glPopMatrix();
}

void Maze::displayCube(bool ceiling)
{
	main::materialColor(1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1000);
	glBindTexture( GL_TEXTURE_2D, g_MazeTextures[TEX_WALL] );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();		
	glTranslatef(-TILE_SIZE/2, -TILE_SIZE/2, -TILE_SIZE/2);
	main::makePlate(TILE_SIZE, TILE_SIZE, NR_OF_VERTEXES, NR_OF_VERTEXES, TILE_SIZE, TILE_SIZE);
	glPopMatrix();

	glPushMatrix();		
	glTranslatef(-TILE_SIZE/2, -TILE_SIZE/2, TILE_SIZE/2);
	main::makePlate(TILE_SIZE, TILE_SIZE, NR_OF_VERTEXES, NR_OF_VERTEXES, TILE_SIZE, TILE_SIZE);
	glPopMatrix();

	glPushMatrix();		
	glTranslatef(-TILE_SIZE/2, -TILE_SIZE/2, -TILE_SIZE/2);
	glRotatef(-90., 0., 1., 0.);
	main::makePlate(TILE_SIZE, TILE_SIZE, NR_OF_VERTEXES, NR_OF_VERTEXES, TILE_SIZE, TILE_SIZE);
	glPopMatrix();

	glPushMatrix();		
	glTranslatef(TILE_SIZE/2, -TILE_SIZE/2, -TILE_SIZE/2);
	glRotatef(-90., 0., 1., 0.);
	main::makePlate(TILE_SIZE, TILE_SIZE, NR_OF_VERTEXES, NR_OF_VERTEXES, TILE_SIZE, TILE_SIZE);
	glPopMatrix();

	if(ceiling)
	{
		glPushMatrix();		
		glTranslatef(-TILE_SIZE/2, TILE_SIZE/2, -TILE_SIZE/2);
		glRotatef(90., 1., 0., 0.);
		main::makePlate(TILE_SIZE, TILE_SIZE, NR_OF_VERTEXES, NR_OF_VERTEXES, TILE_SIZE, TILE_SIZE);
		glPopMatrix();
	}

}
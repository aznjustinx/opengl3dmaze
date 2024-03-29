/*
Stefan Einarsson
stefane07@ru.is
Egill Antonsson

Skilaverkefni 4
Tölvugrafik 
*/
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Maze.h"
#include <vector>

using namespace std;

vector <vector <int> > v; /*two dimensions*/
//   0  1  2  3  4  5  6  7  8  9
int cMap[MAP_SIZE_Z][MAP_SIZE_X] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,9,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
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
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,0,0,1},
	{1,0,0,1,8,8,1,0,0,1},
	{1,0,0,1,1,1,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},};

int gMap[MAP_SIZE_Z][MAP_SIZE_X] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,0,0,1},
	{1,0,0,1,7,7,1,0,0,1},
	{1,0,0,1,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,8,8,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},};

Maze::Maze()
{
}

Maze::~Maze()
{
}

void Maze::init()
{
	//glEnable(GL_LIGHT0);
	//main::changeLightning(GL_LIGHT0, 0.3,0.3,0.5,1, 0.3,0.3,0.5,1, 0,0,0,1, 0,35,0,0);
	glGenTextures(MAZE_MAX_TEXTURES, g_MazeTextures );
	main::loadImage(g_MazeTextures[TEX_FLOOR], ".\\TilesOrnate.jpg");
	main::loadImage(g_MazeTextures[TEX_WALL], ".\\BrickLargeBare.jpg");

	skyBox = new SkyBox();

	finished = false;
	finishSign = new Mesh();
	if (finishSign->readFile("FINISH_SIGN.3VN") == -1)
	{
		cout<<"Error in read file";
	}
	finishRotAngle = 0;

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
				else if(y==4)
					temp.push_back(gMap[z][x]);
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
				switch (v[y][zx])
				{
				case 1:
					cubesPos[y][z][x] = Point3(x*TILE_SIZE,y*3 , -z*TILE_SIZE);
					floorPos[y][z][x] = Point3(x*TILE_SIZE,y , -z*TILE_SIZE);
					break;

				case 9:
					finishPos = Point3(x*TILE_SIZE, y, -z*TILE_SIZE);
					floorPos[y][z][x] = Point3(x*TILE_SIZE,y , -z*TILE_SIZE);
					break;

				case 0:
					pieces[y][z][x] = new Piece();

				case 7:
					floorPos[y][z][x] = Point3(x*TILE_SIZE,y, -z*TILE_SIZE);
					break;
				}
				zx++;
			}							
		}
	}

	ghostCount = 25;	
	int yy, zz, xx;
	while (ghostCount > 0)
	{
		yy = rand()%MAP_SIZE_Y;
		zz = rand()%MAP_SIZE_Z;
		xx = rand()%MAP_SIZE_X;

		if (pieces[yy][zz][xx] != NULL)
		{
			if (rand()%20 == 0)
			{
				pieces[yy][zz][xx]->changeType(GHOST);
				ghostCount--;
			}
		}
	}
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
	
	for (int y = 0; y < MAP_SIZE_Y; y++) {
		int zx = 0;
		for (int z = 0; z < MAP_SIZE_Z; z++) {
			for (int x = 0; x < MAP_SIZE_X; x++) {
				if ((v[y][zx]) == 0) {
					if(pieces[y][z][x] != NULL)
						pieces[y][z][x]->update();
				}
				zx++;
			}
		}
	}
}

void Maze::displayMaze()
{
	skyBox->display();

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
					if(pieces[y][z][x] != NULL)
						pieces[y][z][x]->display();

					case 7:
					displayFloor();
					break;

					case 1:
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
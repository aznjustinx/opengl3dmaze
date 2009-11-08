#ifndef maze_h
#define maze_h
#include "Point3.h"
#include "Mesh.h"

const float TILE_SIZE = 3.0;
const int MAP_SIZE = 3;

class Maze
{
private:
	Mesh* finishSign;
	float finishRotAngle;
	int nrOfCubes;
	Point3 cubesPos[MAP_SIZE*MAP_SIZE];
	Point3 finishPos;
public:	
	Maze();
	~Maze();	
	void displayMaze();
	void displayBox();
	void displayWall();
	void displayFloor();
	void left();
	void right();
	void forward();
	Point3* getCubesPos();
	Point3 getFinishPos();
	int getNrOfCubes();
	void setPosition(float x, float y, float z, int pos);
	void init();
	void displayFinishSign();
	void updateObjects();
	void materialColor(float dif0, float dif1, float dif2, float dif3
						 , float spec0, float spec1, float spec2, float spec3
						 , float amb0, float amb1, float amb2, float amb3, float shininess);

	
};
#endif maze_h
#ifndef maze_h
#define maze_h
#include "Point3.h"
#include "Mesh.h"

class Maze
{
private:
	Mesh* finishSign;
public:
	Maze();
	~Maze();	
	int getNumberOfWalls();
	void drawMaze();
	void drawBox();
	void drawWall();
	void drawFloor();
	void left();
	void right();
	void forward();
	void drawSolidCube();
	Point3* getPosition();
	void setPosition(float x, float y, float z, int pos);
	void init();
	
};
#endif maze_h
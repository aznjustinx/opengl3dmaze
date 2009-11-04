#ifndef maze_h
#define maze_h
#include "Point3.h"
class Maze
{
public:
	Maze();
	~Maze();
	Point3 wall;
	void drawMaze();
	void drawBox();
	void drawWall();
	void drawFloor();
	void left();
	void right();
	void forward();
	void drawSolidCube();
	Point3* getPosition();
	
};
#endif maze_h
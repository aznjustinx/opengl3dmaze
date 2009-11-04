#ifndef maze_h
#define maze_h
#include "Point3.h"
class Maze
{
public:
	Maze();
	~Maze();	

	void drawMaze();
	void drawBox();
	void drawWall();
	void drawFloor();
	void left();
	void right();
	void forward();
	void drawSolidCube(double size);
	Point3* getPosition();
	Point3* setPosition(double x, double y, double z, int pos);
	
};
#endif maze_h
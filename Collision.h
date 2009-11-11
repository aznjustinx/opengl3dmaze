#pragma once
#include "Player.h"
#include "Maze.h"

const float cubeOffset = 1.5;

class Collision
{
private:
	Player* player;
	Maze* maze;
public:	
	Collision(void);
	void init(Player* pl, Maze* ma);
	int check(int forward);
	~Collision(void);
	void leftSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void rightSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void topSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void bottomSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void Collision::bottomRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void Collision::bottomLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void Collision::topLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void Collision::topRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE_Y][MAP_SIZE_X]);
	void Collision::checkFinish(Point3* pos);
	bool Collision::won();
};

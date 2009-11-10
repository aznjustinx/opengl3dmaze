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
	bool checkFinish();
	void leftSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void rightSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void topSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void bottomSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void Collision::bottomRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void Collision::bottomLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void Collision::topLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
	void Collision::topRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10]);
};

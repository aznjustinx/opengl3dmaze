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
	bool check();
	int getWallFace();
	~Collision(void);
	bool checkFinish();
};

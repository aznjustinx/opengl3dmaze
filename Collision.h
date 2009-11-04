#pragma once
#include "Player.h"
#include "Maze.h"


class Collision
{
private:
	Player* player;
	Maze* maze;
public:
	Collision(void);
	void init(Player* pl, Maze* ma);
	bool check();
	~Collision(void);
};

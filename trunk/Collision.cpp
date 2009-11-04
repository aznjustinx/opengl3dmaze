#include <iostream>
#include "Collision.h"


using namespace std;

Collision::Collision(void)
{
}

void Collision::init(Player* pl, Maze* ma)
{
	player = pl;
	maze = ma;
}

bool Collision::check()
{
	Point3* pos = player->getPosition();
	cout<<"Collision eye: x: "<<pos->getX()<<" y: "<<pos->getY()<<" z: "<<pos->getZ()<<"\n";
	
	Point3* ma = maze->getPosition();
	for (int i = 0; i < maze->getNumberOfWalls(); ++i) {
		float xx =  ma[i].getX() + 1.5;



		if (ma[i].getX() + 1.5 == player->getPosition()->getX() ||  ma[i].getX() - 1.5 == player->getPosition()->getX() ||
			ma[i].getZ() + 1.5 == player->getPosition()->getZ() ||  ma[i].getZ() - 1.5 == player->getPosition()->getZ()) {
			return true;
		}

	}
	
	
	return false;
}

Collision::~Collision(void)
{
}

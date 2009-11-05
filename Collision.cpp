#include <iostream>
#include "Collision.h"
#include "math.h"

using namespace std;

int value = 0;

Collision::Collision(void)
{
}

void Collision::init(Player* pl, Maze* ma)
{
	player = pl;
	maze = ma;
	value = 0;
}

int Collision::getWallFace()
{
	return value;
}

bool Collision::check()
{
	Point3* pos = player->getPosition();
	//cout<<"Collision eye: x: "<<int(pos->getX())<<" y: "<<int(pos->getY())<<" z: "<<int(pos->getZ())<<"\n";
	
	Point3* ma = maze->getPosition();
	bool collision = false;
	//cout<<"Collision wall: x: "<<ma[3].getX()<<" y: "<<ma[3].getY()<<" z: "<<ma[3].getZ()<<"\n";
	for (int i = 0; i < maze->getNumberOfWalls(); ++i) {
		//float xx =  ma[i].getX() + 1.5;
		// offset er radius á vegg (1.5) + auka pláss til að stoppa player áður en hann snertir vegginn.
		float offset = 1.5;		
		
		// hliðar
		if (	fabs(ma[i].getX() - (pos->getX())) < 1 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < 1)			
		{
			value = 2;
			collision = true;
		}
		if (	fabs(ma[i].getX() -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < 1)			
		{	
			value = 1;
			collision = true;
		}
		else if (	fabs(ma[i].getX() +offset -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() -(pos->getZ())) < 1)			
		{
			value = 2;
			collision = true;
		}
		else if (	fabs(ma[i].getX() -offset -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() -(pos->getZ())) < 1)			
		{
			value = 2;
			collision = true;
		}

		// hornin
		else if (	fabs(ma[i].getX() + offset -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < 1)			
		{
			value = 1;
			collision = true;
		}
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < 1
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < 1 ) 
		{
			value = 1;
			collision = true;
		}
		else if (fabs(ma[i].getX() + offset -(pos->getX())) < 1
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < 1 ) 
		{
			value = 1;
			collision = true;
		}
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < 1
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < 1 ) 
		{
			value = 1;
			collision = true;
		}				
	}
		
	return collision;
}

Collision::~Collision(void)
{
}

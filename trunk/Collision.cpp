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
}

int Collision::check()
{
	Point3* pos = player->getPosition();
	//cout<<"Collision eye: x: "<<int(pos->getX())<<" y: "<<int(pos->getY())<<" z: "<<int(pos->getZ())<<"\n";
	
	Point3* ma = maze->getCubesPos();
	int collision = 0;
	//cout<<"Collision wall: x: "<<ma[3].getX()<<" y: "<<ma[3].getY()<<" z: "<<ma[3].getZ()<<"\n";
	for (int i = 0; i < maze->getNrOfCubes(); ++i) {
		//float xx =  ma[i].getX() + 1.5;
		// offset er radius á vegg (1.5) + auka pláss til að stoppa player áður en hann snertir vegginn.
		//cout<<"Collision wall: "<<i<<" x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
		float offset = 1.5;		
		float lesserThan = 1;		
		// hliðar
		if (	fabs(ma[i].getX() - (pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan)			
		{
			collision = 1;
		}
		else if (	fabs(ma[i].getX() -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan)			
		{	
			collision = 3;
		}
		else if (	fabs(ma[i].getX() +offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		else if (	fabs(ma[i].getX() -offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}

		// hornin
		else if (	fabs(ma[i].getX() + offset -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan)			
		{
			collision = 1;
		}
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 1;
		}
		else if (fabs(ma[i].getX() + offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 3;
		}
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 3;
		}				
	}
		
	return collision;
}

Collision::~Collision(void)
{
}

/*bool Collision::checkFinish()
{
		
}*/

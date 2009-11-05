#include <iostream>
#include "Collision.h"
#include "math.h"


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
	cout<<"Collision eye: x: "<<int(pos->getX())<<" y: "<<int(pos->getY())<<" z: "<<int(pos->getZ())<<"\n";
	
	Point3* ma = maze->getPosition();
	//cout<<"Collision wall: x: "<<ma[3].getX()<<" y: "<<ma[3].getY()<<" z: "<<ma[3].getZ()<<"\n";
	for (int i = 0; i < maze->getNumberOfWalls(); ++i) {
		float offset = 1.5;
		
		//cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";

		/*if (ma[i].getX() + 10.5 == player->getPosition()->getX() ||  ma[i].getX() - 1.5 == player->getPosition()->getX() ||
			ma[i].getZ() + 1.5 == player->getPosition()->getZ() ||  ma[i].getZ() - 1.5 == player->getPosition()->getZ()) 
		{*/
		// hliðar
		if (	fabs(ma[i].getX()  -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < 1)			
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}
		else if (	fabs(ma[i].getX() -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < 1)			
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}
		else if (	fabs(ma[i].getX() +offset -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() -(pos->getZ())) < 1)			
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}
		else if (	fabs(ma[i].getX() -offset -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() -(pos->getZ())) < 1)			
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}

		// hornin
		else if (	fabs(ma[i].getX() + offset -(pos->getX())) < 1 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < 1)			
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < 1
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < 1 ) 
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}
		else if (fabs(ma[i].getX() + offset -(pos->getX())) < 1
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < 1 ) 
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < 1
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < 1 ) 
		{
			cout<<"Collision wall:"<<i<<": x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
			return true;
		}

	}
	
	
	return false;
}

Collision::~Collision(void)
{
}

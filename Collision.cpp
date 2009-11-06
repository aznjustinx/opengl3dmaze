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
		float offset = 1.5;			// út að ytri hlið kubbs
		float lesserThan = 1;		// stærð á kalli
		float side_offset = 0.3;	// frá horni 

		// 678
		// 4 5
		// 123

		// niðri vinstra 1
		if (fabs(ma[i].getX() - offset +side_offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 1; // 1
		}
		// niðri miðja 2
		if (	fabs(ma[i].getX() - (pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan)			
		{
			collision = 1; // 2
		}
		// niðri hægri 3
		if (	fabs(ma[i].getX() + offset -side_offset -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan)			
		{
			collision = 1; // 3
		}


		// niðri vinstra HLIÐ 12
		if (fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() + offset - side_offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 2;
		}
		// niðri hægra HLIÐ 13
		if (	fabs(ma[i].getX() + offset -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -side_offset -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		// miðja vinstri 4
		if (	fabs(ma[i].getX() -offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		// miðja hægri 5
		if (	fabs(ma[i].getX() +offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		// efri vinstri HLIÐ 36
		if (fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset + side_offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 2;
		}	
		// efri hægri HLIÐ 38
		if (fabs(ma[i].getX() + offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset +side_offset-(pos->getZ())) < lesserThan ) 
		{
			collision = 2;
		}					

		
		
		// efri vinstra 6
		if (fabs(ma[i].getX() - offset + side_offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 3; // 6
		}	
		// efri miðja 7
		if (	fabs(ma[i].getX() -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan)			
		{	
			collision = 3; // 7
		}
		// efri hægra 8
		if (fabs(ma[i].getX() + offset - side_offset-(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 3; // 8
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

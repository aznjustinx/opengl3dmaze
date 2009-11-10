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
	Vector3* n = player->getYaw();
	
	//cout<<"Collision eye: x: "<<intpos->getX()<<" y: "<<int(pos->getY())<<" z: "<<intpos->getZ()<<"\n";
	
	//Point3 ma = maze->cubesPos;//getCubesPos();
	int collision = 0;
	float offset = 1.5;			// út að ytri hlið kubbs
	float lesserThan = 1;		// stærð á kalli
	float side_offset = 0.5;	// frá horni 
	const int MAP_SIZE = 10;	
	Point3 ma[MAP_SIZE][MAP_SIZE];

	float yaw_offset = 0.5;
	
//	cout << "coll: "<< ma[3][3].getZ() << endl;
	
	for (int y = 0; y < MAP_SIZE; y++) //loop through the height of the map
	{
		for (int x = 0; x < MAP_SIZE; x++) //loop through the width of the map
		{
			ma[y][x] = maze->getCubesPos(y,x);		
		}
	}
	cout << endl;
	//cout<<"Collision wall: x: "<<ma[3].getX()<<" y: "<<ma[3].getY()<<" z: "<<ma[3].getZ()<<"\n";
	//for (int i = 0; i < maze->getNrOfCubes(); ++i) {
	for (int y = 0; y < MAP_SIZE; y++) //loop through the height of the map
	{
		for (int x = 0; x < MAP_SIZE; x++) //loop through the width of the map
		{
			// offset er radius á vegg (1.5) + auka pláss til að stoppa player áður en hann snertir vegginn.
			//cout<<"Collision wall: "<<i<<" x: "<<ma[y][x].getX()<<" y: "<<ma[y][x].getY()<<" z: "<<ma[y][x].getZ()<<"\n";
			

			// 678
			// 4 5
			// 123
			// NIÐRI************
			// 123
			// niðri vinstra 1
			if (fabs(ma[y][x].getX() - offset +side_offset -pos->getX()) < lesserThan
				&&  
				fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan 
				&&
				n->getZ() >= 0) 
			{
				collision = 1; // 1
			}
			// niðri miðja 2
			else if (	fabs(ma[y][x].getX() - pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan
			&&
				n->getZ() >= 0)			
			{
				collision = 1; // 2
			}
			// niðri hægri 3
			else if (	fabs(ma[y][x].getX() + offset -side_offset -pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan				
				&&
				n->getZ() >= 0)			
			{
				collision = 1; // 3
			}

			
			// UPPI *************
			// 678
			// efri vinstra 6
			if (fabs(ma[y][x].getX() - offset + side_offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan
				&&
				n->getZ() <= 0) 
			{
				collision = 3; // 6
			}	
			// efri miðja 7
			else if (	fabs(ma[y][x].getX() -pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan
				&&
				n->getZ() <= 0)			
			{	
				collision = 3; // 7
			}
			// efri hægra 8
			else if (fabs(ma[y][x].getX() + offset - side_offset-pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan 
				&&
				n->getZ() <= 0) 
			{
				collision = 3; // 8
			}	

			// HLIÐAR *********+
			//444 555
			// niðri vinstra HLIÐ 12
			if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() + offset - side_offset - pos->getZ()) < lesserThan 
				&&
				n->getX() <= 0) 
			{
				collision = 2;
			}
			// niðri hægra HLIÐ 13
			else if (	fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() + offset -side_offset -pos->getZ()) < lesserThan
				&&
				n->getX() >= 0)			
			{
				collision = 2;
			}
			// miðja vinstri 4
			else if (	fabs(ma[y][x].getX() -offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan
				&&
				n->getX() <= 0)			
			{
				collision = 2;
			}
			// miðja hægri 5
			else if (	fabs(ma[y][x].getX() +offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan
				&&
				n->getX() >= 0)			
			{
				collision = 2;
			}
			// efri vinstri HLIÐ 36
			else if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset + side_offset -pos->getZ()) < lesserThan 
				&&
				n->getX() <= 0) 
			{
				collision = 2;
			}	
			// efri hægri HLIÐ 38
			else if (fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset +side_offset-pos->getZ()) < lesserThan 
				&&
				n->getX() >= 0) 
			{
				collision = 2;
			}					

			// horn i horn
			// hægra neðra horn
			// niðri hlid vinstri og efra hægra
			if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
				&&  
				fabs(ma[y][x].getZ() + offset - side_offset - pos->getZ()) < lesserThan
				&&
				fabs(ma[y-1][x-1].getX() + offset - side_offset-pos->getX()) < lesserThan
				&&  
				fabs(ma[y-1][x-1].getZ() - offset -pos->getZ()) < lesserThan
				&&
				n->getX() <= 0
				&&
				n->getZ() <= 0)
			{
				collision = 4;
			}

			// neðra vinstra horn
			// niðri hlid hægri og efra vinstra
			if (fabs(ma[y][x].getX() + offset - pos->getX()) < lesserThan 
				&&  
				fabs(ma[y][x].getZ() + offset - side_offset -pos->getZ()) < lesserThan
				&&
				fabs(ma[y-1][x+1].getX() - offset + side_offset - pos->getX()) < lesserThan
				&&  
				fabs(ma[y-1][x+1].getZ() - offset - pos->getZ()) < lesserThan
				&&
				n->getX() >= 0
				&&
				n->getZ() <= 0)
			{
				collision = 4;
			}

			// efra vinstra horn
			// down left og hlið up right
			if (fabs(ma[y][x].getX() - offset +side_offset -pos->getX()) < lesserThan
				&&  
				fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan
				&&
				fabs(ma[y-1][x-1].getX() + offset -pos->getX()) < lesserThan
				&&  
				fabs(ma[y-1][x-1].getZ() - offset +side_offset-pos->getZ()) < lesserThan
				&&
				n->getX() >= 0
				&&
				n->getZ() >= 0)
			{
				collision = 4;
			}

			// efra hægra horn
			// down right og hlið up left
			if (fabs(ma[y][x].getX() + offset -side_offset -pos->getX()) < lesserThan 
				&&  
				fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan
				&&
				fabs(ma[y-1][x+1].getX() - offset -pos->getX()) < lesserThan
				&&  
				fabs(ma[y-1][x+1].getZ() - offset + side_offset -pos->getZ()) < lesserThan 
				&&
				n->getX() <= 0
				&&
				n->getZ() >= 0) 
				{
				collision = 4;
			}
		}					
	}
	Point3 finish =  maze->getFinishPos();
	//cout << finish.getX() << ", " << finish.getZ() << endl;

	if (
		(fabs(finish.getX() - pos->getX())  < lesserThan)
		&& 
		(fabs(finish.getZ() - pos->getZ()) < lesserThan)
		)
		cout << "You Won" << endl;

	return collision;
}

Collision::~Collision(void)
{
}

/*bool Collision::checkFinish()
{

}*/

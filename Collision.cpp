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
	float offset = 1.5;			// �t a� ytri hli� kubbs
	float lesserThan = 1;		// st�r� � kalli
	float side_offset = 0.5;	// fr� horni 
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
			// offset er radius � vegg (1.5) + auka pl�ss til a� stoppa player ��ur en hann snertir vegginn.
			//cout<<"Collision wall: "<<i<<" x: "<<ma[y][x].getX()<<" y: "<<ma[y][x].getY()<<" z: "<<ma[y][x].getZ()<<"\n";
			

			// 678
			// 4 5
			// 123
			// NI�RI************
			// 123
			// ni�ri vinstra 1
			if (fabs(ma[y][x].getX() - offset +side_offset -pos->getX()) < lesserThan
				&&  
				fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan 
				&&
				n->getZ() >= 0) 
			{
				collision = 1; // 1
			}
			// ni�ri mi�ja 2
			else if (	fabs(ma[y][x].getX() - pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan
			&&
				n->getZ() >= 0)			
			{
				collision = 1; // 2
			}
			// ni�ri h�gri 3
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
			// efri mi�ja 7
			else if (	fabs(ma[y][x].getX() -pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan
				&&
				n->getZ() <= 0)			
			{	
				collision = 3; // 7
			}
			// efri h�gra 8
			else if (fabs(ma[y][x].getX() + offset - side_offset-pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan 
				&&
				n->getZ() <= 0) 
			{
				collision = 3; // 8
			}	

			// HLI�AR *********+
			//444 555
			// ni�ri vinstra HLI� 12
			if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() + offset - side_offset - pos->getZ()) < lesserThan 
				&&
				n->getX() <= 0) 
			{
				collision = 2;
			}
			// ni�ri h�gra HLI� 13
			else if (	fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan 
				&&  fabs(ma[y][x].getZ() + offset -side_offset -pos->getZ()) < lesserThan
				&&
				n->getX() >= 0)			
			{
				collision = 2;
			}
			// mi�ja vinstri 4
			else if (	fabs(ma[y][x].getX() -offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan
				&&
				n->getX() <= 0)			
			{
				collision = 2;
			}
			// mi�ja h�gri 5
			else if (	fabs(ma[y][x].getX() +offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan
				&&
				n->getX() >= 0)			
			{
				collision = 2;
			}
			// efri vinstri HLI� 36
			else if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset + side_offset -pos->getZ()) < lesserThan 
				&&
				n->getX() <= 0) 
			{
				collision = 2;
			}	
			// efri h�gri HLI� 38
			else if (fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan
				&&  fabs(ma[y][x].getZ() - offset +side_offset-pos->getZ()) < lesserThan 
				&&
				n->getX() >= 0) 
			{
				collision = 2;
			}					

			// horn i horn
			// h�gra ne�ra horn
			// ni�ri hlid vinstri og efra h�gra
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

			// ne�ra vinstra horn
			// ni�ri hlid h�gri og efra vinstra
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
			// down left og hli� up right
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

			// efra h�gra horn
			// down right og hli� up left
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

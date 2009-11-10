#include <iostream>
#include "Collision.h"
#include "math.h"

using namespace std;

const float offset = 1.5;			// �t a� ytri hli� kubbs
const float lesserThan = 1;		// st�r� � kalli
const float side_offset = 0.5;	// fr� horni 
int collision = 0;



Collision::Collision(void)
{
}

void Collision::init(Player* pl, Maze* ma)
{
	player = pl;
	maze = ma;
}

int Collision::check(int forward)
{
	Point3* pos = player->getPosition();
	Vector3* n = player->getYaw();

	collision = 0;

	Point3 ma[MAP_SIZE][MAP_SIZE];

	//cout<<"Collision eye: x: "<<intpos->getX()<<" y: "<<int(pos->getY())<<" z: "<<intpos->getZ()<<"\n";
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
			if(n->getZ() >= 0 && forward || n->getZ() <= 0 && !forward)
			{
				bottomSide(y,x,pos,n,ma);
			}			

			if(n->getZ() <= 0 && forward || n->getZ() >= 0 && !forward){
				topSide(y,x,pos,n,ma);
			}			

			if(n->getX() <= 0 && forward || n->getX() >= 0 && !forward)
			{
				leftSide(y,x,pos,n,ma);
			}

			if(n->getX() >= 0 && forward || n->getX() <= 0 && !forward)
			{
				rightSide(y,x,pos,n,ma);			
			}			


			if(n->getX() <= 0
				&&
				n->getZ() <= 0
				&& 
				forward
				||
				n->getX() >= 0
				&&
				n->getZ() >= 0
				&& 
				!forward)
			{
				bottomRightCorner(y,x,pos,n,ma);
			}

			if(n->getX() >= 0
				&&
				n->getZ() <= 0
				&& 
				forward
				||
				n->getX() <= 0
				&&
				n->getZ() >= 0
				&& 
				!forward)
			{
				bottomLeftCorner(y,x,pos,n,ma);
			}			
			if(n->getX() >= 0
				&&
				n->getZ() >= 0
				&& 
				forward
				||
				n->getX() <= 0
				&&
				n->getZ() <= 0
				&& 
				!forward)
			{
				topLeftCorner(y,x,pos,n,ma);
			}

			if(n->getX() <= 0
				&&
				n->getZ() >= 0
				&& 
				forward
				||
				n->getX() >= 0
				&&
				n->getZ() <= 0
				&& 
				!forward)
			{
				topRightCorner(y,x,pos,n,ma);
			}
		}					
	}
	return collision;
}

void Collision::leftSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{

	// HLI�AR *********+
	//444 555
	// ni�ri vinstra HLI� 12
	if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() + offset - side_offset - pos->getZ()) < lesserThan ) 
	{
		collision = 2;
	}

	// mi�ja vinstri 4
	else if (	fabs(ma[y][x].getX() -offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan)			
	{
		collision = 2;
	}

	// efri vinstri HLI� 36
	else if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset + side_offset -pos->getZ()) < lesserThan 	) 
	{
		collision = 2;
	}	

}

void Collision::rightSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{

	// ni�ri h�gra HLI� 13
	if (	fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() + offset -side_offset -pos->getZ()) < lesserThan)			
	{
		collision = 2;
	}
	// mi�ja h�gri 5
	else if (	fabs(ma[y][x].getX() +offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan	)			
	{
		collision = 2;
	}
	// efri h�gri HLI� 38
	else if (fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset +side_offset-pos->getZ()) < lesserThan ) 
	{
		collision = 2;
	}	

}

void Collision::topSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{

	// UPPI *************
	// 678
	// efri vinstra 6
	if (fabs(ma[y][x].getX() - offset + side_offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan) 
	{
		collision = 3; // 6
	}	
	// efri mi�ja 7
	else if (	fabs(ma[y][x].getX() -pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan)			
	{	
		collision = 3; // 7
	}
	// efri h�gra 8
	else if (fabs(ma[y][x].getX() + offset - side_offset-pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan ) 
	{
		collision = 3; // 8
	}

}

void Collision::bottomSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{
	// NI�RI************
	// 123
	// ni�ri vinstra 1
	if (fabs(ma[y][x].getX() - offset +side_offset -pos->getX()) < lesserThan
		&&  
		fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan ) 
	{
		collision = 1; // 1
	}
	// ni�ri mi�ja 2
	else if (	fabs(ma[y][x].getX() - pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan)			
	{
		collision = 1; // 2
	}
	// ni�ri h�gri 3
	else if (	fabs(ma[y][x].getX() + offset -side_offset -pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan				)			
	{
		collision = 1; // 3
	}

}





void Collision::bottomRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{
	// horn i horn
	// h�gra ne�ra horn
	// ni�ri hlid vinstri og efra h�gra

	if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
		&&  
		fabs(ma[y][x].getZ() + offset - side_offset - pos->getZ()) < lesserThan
		&&
		fabs(ma[y-1][x-1].getX() + offset - side_offset-pos->getX()) < lesserThan
		&&  
		fabs(ma[y-1][x-1].getZ() - offset -pos->getZ()) < lesserThan)
	{
		collision = 4;
	}

}
void Collision::bottomLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{
	// ne�ra vinstra horn
	// ni�ri hlid h�gri og efra vinstra

	if (fabs(ma[y][x].getX() + offset - pos->getX()) < lesserThan 
		&&  
		fabs(ma[y][x].getZ() + offset - side_offset -pos->getZ()) < lesserThan
		&&
		fabs(ma[y-1][x+1].getX() - offset + side_offset - pos->getX()) < lesserThan
		&&  
		fabs(ma[y-1][x+1].getZ() - offset - pos->getZ()) < lesserThan)
	{
		collision = 4;
	}

}
void Collision::topLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{
	// efra vinstra horn
	// down left og hli� up right

	if (fabs(ma[y][x].getX() - offset +side_offset -pos->getX()) < lesserThan
		&&  
		fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan
		&&
		fabs(ma[y-1][x-1].getX() + offset -pos->getX()) < lesserThan
		&&  
		fabs(ma[y-1][x-1].getZ() - offset +side_offset-pos->getZ()) < lesserThan)
	{
		collision = 4;
	}

}
void Collision::topRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[10][10])
{
	// efra h�gra horn
	// down right og hli� up left

	if (fabs(ma[y][x].getX() + offset -side_offset -pos->getX()) < lesserThan 
		&&  
		fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan
		&&
		fabs(ma[y-1][x+1].getX() - offset -pos->getX()) < lesserThan
		&&  
		fabs(ma[y-1][x+1].getZ() - offset + side_offset -pos->getZ()) < lesserThan 	) 
	{
		collision = 4;
	}

}

Collision::~Collision(void)
{
}

bool Collision::checkFinish()
{
	return false;
}

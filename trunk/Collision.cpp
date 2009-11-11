#include <iostream>
#include "Collision.h"
#include "math.h"

using namespace std;

const float offset = 1.5;			// út að ytri hlið kubbs
const float lesserThan = 1;		// stærð á kalli
const float side_offset = 0.5;	// frá horni 
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

	// hleður staðsetningu á veggjum inn í array
	for (int y = 0; y < MAP_SIZE; y++) //loop through the height of the map
	{
		for (int x = 0; x < MAP_SIZE; x++) //loop through the width of the map
		{
			ma[y][x] = maze->getCubesPos(y,x);		
		}
	}
	// fer í gegnum öll stök í arrayi og leitar að árekstrum
	for (int y = 0; y < MAP_SIZE; y++) //loop through the height of the map
	{
		for (int x = 0; x < MAP_SIZE; x++) //loop through the width of the map
		{
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

			#pragma region corners

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
			#pragma endregion corners
		}					
	}
	return collision;
}

void Collision::leftSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{

	// HLIÐAR *********
	//444 555
	// niðri vinstra HLIÐ 12
	if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() + offset - side_offset - pos->getZ()) < lesserThan ) 
	{
		collision = 2;
	}

	// miðja vinstri 4
	else if (	fabs(ma[y][x].getX() -offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan)			
	{
		collision = 2;
	}

	// efri vinstri HLIÐ 36
	else if (fabs(ma[y][x].getX() - offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset + side_offset -pos->getZ()) < lesserThan 	) 
	{
		collision = 2;
	}	

}

void Collision::rightSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{

	// niðri hægra HLIÐ 13
	if (	fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() + offset -side_offset -pos->getZ()) < lesserThan)			
	{
		collision = 2;
	}
	// miðja hægri 5
	else if (	fabs(ma[y][x].getX() +offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() -pos->getZ()) < lesserThan	)			
	{
		collision = 2;
	}
	// efri hægri HLIÐ 38
	else if (fabs(ma[y][x].getX() + offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset +side_offset-pos->getZ()) < lesserThan ) 
	{
		collision = 2;
	}	

}

void Collision::topSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{

	// UPPI *************
	// 678
	// efri vinstra 6
	if (fabs(ma[y][x].getX() - offset + side_offset -pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan) 
	{
		collision = 3; // 6
	}	
	// efri miðja 7
	else if (	fabs(ma[y][x].getX() -pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan)			
	{	
		collision = 3; // 7
	}
	// efri hægra 8
	else if (fabs(ma[y][x].getX() + offset - side_offset-pos->getX()) < lesserThan
		&&  fabs(ma[y][x].getZ() - offset -pos->getZ()) < lesserThan ) 
	{
		collision = 3; // 8
	}

}

void Collision::bottomSide(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{
	// NIÐRI************
	// 123
	// niðri vinstra 1
	if (fabs(ma[y][x].getX() - offset +side_offset -pos->getX()) < lesserThan
		&&  
		fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan ) 
	{
		collision = 1; // 1
	}
	// niðri miðja 2
	else if (	fabs(ma[y][x].getX() - pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan)			
	{
		collision = 1; // 2
	}
	// niðri hægri 3
	else if (	fabs(ma[y][x].getX() + offset -side_offset -pos->getX()) < lesserThan 
		&&  fabs(ma[y][x].getZ() + offset -pos->getZ()) < lesserThan				)			
	{
		collision = 1; // 3
	}

}





void Collision::bottomRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{
	// horn i horn
	// hægra neðra horn
	// niðri hlid vinstri og efra hægra

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
void Collision::bottomLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{
	// neðra vinstra horn
	// niðri hlid hægri og efra vinstra

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
void Collision::topLeftCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{
	// efra vinstra horn
	// down left og hlið up right

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
void Collision::topRightCorner(int y, int x, Point3* pos,Vector3* n,Point3 ma[MAP_SIZE][MAP_SIZE])
{
	// efra hægra horn
	// down right og hlið up left

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

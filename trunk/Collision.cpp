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
	float offset = 1.5;			// �t a� ytri hli� kubbs
	float lesserThan = 1;		// st�r� � kalli
	float side_offset = 0.5;	// fr� horni 
	//cout<<"Collision wall: x: "<<ma[3].getX()<<" y: "<<ma[3].getY()<<" z: "<<ma[3].getZ()<<"\n";
	for (int i = 0; i < maze->getNrOfCubes(); ++i) {
		//float xx =  ma[i].getX() + 1.5;
		// offset er radius � vegg (1.5) + auka pl�ss til a� stoppa player ��ur en hann snertir vegginn.
		//cout<<"Collision wall: "<<i<<" x: "<<ma[i].getX()<<" y: "<<ma[i].getY()<<" z: "<<ma[i].getZ()<<"\n";
		

		// 678
		// 4 5
		// 123
		// NI�RI************
		// ni�ri vinstra 1
		if (fabs(ma[i].getX() - offset +side_offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 1; // 1
		}
		// ni�ri mi�ja 2
		else if (	fabs(ma[i].getX() - (pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan)			
		{
			collision = 1; // 2
		}
		// ni�ri h�gri 3
		else if (	fabs(ma[i].getX() + offset -side_offset -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -(pos->getZ())) < lesserThan)			
		{
			collision = 1; // 3
		}

		
		// UPPI *************
		// efri vinstra 6
		if (fabs(ma[i].getX() - offset + side_offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 3; // 6
		}	
		// efri mi�ja 7
		else if (	fabs(ma[i].getX() -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan)			
		{	
			collision = 3; // 7
		}
		// efri h�gra 8
		else if (fabs(ma[i].getX() + offset - side_offset-(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 3; // 8
		}	
		
		// HLI�AR *********+
		// ni�ri vinstra HLI� 12
		if (fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() + offset - side_offset - (pos->getZ())) < lesserThan ) 
		{
			collision = 2;
		}
		// ni�ri h�gra HLI� 13
		else if (	fabs(ma[i].getX() + offset -(pos->getX())) < lesserThan 
			&&  fabs(ma[i].getZ() + offset -side_offset -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		// mi�ja vinstri 4
		else if (	fabs(ma[i].getX() -offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		// mi�ja h�gri 5
		else if (	fabs(ma[i].getX() +offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() -(pos->getZ())) < lesserThan)			
		{
			collision = 2;
		}
		// efri vinstri HLI� 36
		else if (fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset + side_offset -(pos->getZ())) < lesserThan ) 
		{
			collision = 2;
		}	
		// efri h�gri HLI� 38
		else if (fabs(ma[i].getX() + offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() - offset +side_offset-(pos->getZ())) < lesserThan ) 
		{
			collision = 2;
		}					

		// horn i horn
		// ni�ri hlid vinstri og efra h�gra
		if (
			fabs(ma[i].getX() - offset -(pos->getX())) < lesserThan
			&&  fabs(ma[i].getZ() + offset - side_offset - (pos->getZ())) < lesserThan
			&&
			fabs(ma[i-3].getX() + offset - side_offset-(pos->getX())) < lesserThan
			&&  fabs(ma[i-3].getZ() - offset -(pos->getZ())) < lesserThan
			)
		{
			cout << "horn" << endl;
			collision = 4;
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

#pragma once
#include "Point3.h"
#include "Mesh.h"
#include "Outside.h"
#include "Piece.h"

const float GOODIE_SIZE = 0.3;
const int GOODIE_ROT_INC = 5;
const int GOODIE_NR_OF_VERTS = 8;

class Piece
{
private:
	float goodieRotAngle;
public:
	Piece(void);
	~Piece(void);
	void update();
	void display();
};

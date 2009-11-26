#pragma once
#include "Point3.h"
#include "Mesh.h"
#include "Outside.h"

const float GOODIE_SIZE = 0.3;
const int GOODIE_ROT_INC = 5;
const int GOODIE_NR_OF_VERTS = 8;
const int PIECE_MAX_TEXTURES = 5;

class Piece
{
private:
	float rotAngle;
	GLuint g_PieceTextures[PIECE_MAX_TEXTURES];
public:
	Piece(void);
	~Piece(void);
	void update();
	void display();
};

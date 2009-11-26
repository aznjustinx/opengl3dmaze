#pragma once
#include "Point3.h"

const float PIECE_SIZE = 0.3;
const int ROT_INC = 5;
const int NR_OF_VERTS = 8;
const int PIECE_MAX_TEXTURES = 2;

class Piece
{
private:
	float rotAngle;
	GLuint g_PieceTextures[PIECE_MAX_TEXTURES];
public:
	bool captured;
	Piece(void);
	~Piece(void);
	void update();
	void display();
};

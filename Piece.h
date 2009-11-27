#pragma once
#include "main.h"

const float PIECE_SIZE = 0.3;
const int ROT_INC = 5;
const int PIECE_NR_OF_VERTS = 8;
const int PIECE_MAX_TEXTURES = 3;

enum {PACMAN, GHOST};

class Piece
{
private:
	float rotAngle;
	GLuint g_PieceTextures[PIECE_MAX_TEXTURES];
	float score;
	int type;
public:
	bool captured;
	Piece();
	~Piece(void);
	void update();
	void display();
	void init();
	void changeType(int type);
};

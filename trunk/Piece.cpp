#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/gl.h>
#include "main.h"
#include "Piece.h"

using namespace std;

Piece::Piece(void)
{
	glGenTextures(PIECE_MAX_TEXTURES, g_PieceTextures);
	main::loadImage(g_PieceTextures[TEX_GOODIE], ".\\pacman.tif");
	rotAngle = 0;
	captured = false;
}

Piece::~Piece(void)
{
}

void Piece::update()
{
	if (rotAngle >= 359 + ROT_INC) {
		rotAngle = 359 - rotAngle + ROT_INC;
	} else {
		rotAngle += ROT_INC;
	}
}

void Piece::display()
{

		main::materialColor(1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.);
		glBindTexture( GL_TEXTURE_2D, g_PieceTextures[TEX_GOODIE] );
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
		glRotatef(rotAngle, 0., 1., 0.);
		glTranslatef(-PIECE_SIZE/2, -PIECE_SIZE/2, 0);
		
		main::makePlate(PIECE_SIZE, PIECE_SIZE, NR_OF_VERTS, NR_OF_VERTS, PIECE_SIZE, PIECE_SIZE);
		glPopMatrix();
		
		glPushMatrix();
		glRotatef(rotAngle + 180, 0., 1., 0.);
		glTranslatef(-PIECE_SIZE/2 - 0.001, -PIECE_SIZE/2, -0.001);
		
		main::makePlate(PIECE_SIZE, PIECE_SIZE, NR_OF_VERTS, NR_OF_VERTS, PIECE_SIZE, PIECE_SIZE);
		glPopMatrix();
	
}
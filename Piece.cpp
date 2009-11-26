#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Point3.h"
#include <gl/gl.h>
#include <FreeImage.h>
#include <vector>
#include "main.h"
#include "Piece.h"

using namespace std;

Piece::Piece(void)
{
	glGenTextures(PIECE_MAX_TEXTURES, g_PieceTextures);
	main::loadImage(g_PieceTextures[TEX_GOODIE], ".\\pacman.tif");
	rotAngle = 0;
}

Piece::~Piece(void)
{
}

void Piece::update()
{
	if (rotAngle >= 359 + GOODIE_ROT_INC) {
		rotAngle = 359 - rotAngle + GOODIE_ROT_INC;
	} else {
		rotAngle += GOODIE_ROT_INC;
	}
}

void Piece::display()
{
	main::materialColor(1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.);
	glBindTexture( GL_TEXTURE_2D, g_PieceTextures[TEX_GOODIE] );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(rotAngle, 0., 1., 0.);
	glTranslatef(-GOODIE_SIZE/2, -GOODIE_SIZE/2, 0);
	
	main::makePlate(GOODIE_SIZE, GOODIE_SIZE, GOODIE_NR_OF_VERTS, GOODIE_NR_OF_VERTS, GOODIE_SIZE, GOODIE_SIZE);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(rotAngle + 180, 0., 1., 0.);
	glTranslatef(-GOODIE_SIZE/2 - 0.001, -GOODIE_SIZE/2, -0.001);
	
	main::makePlate(GOODIE_SIZE, GOODIE_SIZE, GOODIE_NR_OF_VERTS, GOODIE_NR_OF_VERTS, GOODIE_SIZE, GOODIE_SIZE);
	glPopMatrix();
}
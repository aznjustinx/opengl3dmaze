#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Point3.h"
#include <gl/gl.h>
#include <FreeImage.h>
#include <vector>
#include "main.h"
#include "piece.h"

using namespace std;

Piece::Piece(void)
{
	main::loadImage(g_textures[main::TEX_GOODIE], ".\\pacman.tif");
}

Piece::~Piece(void)
{
}

void Piece::update()
{
	if (goodieRotAngle >= 359 + GOODIE_ROT_INC) {
		goodieRotAngle = 359 - goodieRotAngle + GOODIE_ROT_INC;
	} else {
		goodieRotAngle += GOODIE_ROT_INC;
	}
}

void Piece::display()
{
	main::materialColor(1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.);
	glBindTexture( GL_TEXTURE_2D, g_textures[main::TEX_GOODIE] );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(goodieRotAngle, 0., 1., 0.);
	glTranslatef(-GOODIE_SIZE/2, -GOODIE_SIZE/2, 0);
	
	main::makePlate(GOODIE_SIZE, GOODIE_SIZE, GOODIE_NR_OF_VERTS, GOODIE_NR_OF_VERTS, GOODIE_SIZE, GOODIE_SIZE);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(goodieRotAngle + 180, 0., 1., 0.);
	glTranslatef(-GOODIE_SIZE/2 - 0.001, -GOODIE_SIZE/2, -0.001);
	
	main::makePlate(GOODIE_SIZE, GOODIE_SIZE, GOODIE_NR_OF_VERTS, GOODIE_NR_OF_VERTS, GOODIE_SIZE, GOODIE_SIZE);
	glPopMatrix();
}
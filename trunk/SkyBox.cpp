#include "SkyBox.h"

SkyBox::SkyBox(void)
{
	glGenTextures(SKY_MAX_TEXTURES, g_skyTextures);
	main::loadImage(g_skyTextures[TEX_SKY], ".\\stars.jpg");
}

SkyBox::~SkyBox(void)
{
}

void SkyBox::update()
{
}

void SkyBox::display()
{
	main::materialColor(1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.);
	glBindTexture( GL_TEXTURE_2D, g_skyTextures[TEX_SKY] );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glPushMatrix();
	glTranslatef(-5, 7, 5);
	main::makePlate(SKY_WIDTH, SKY_HEIGHT, SKY_NR_OF_VERTS, SKY_NR_OF_VERTS, SKY_WIDTH/2, SKY_HEIGHT/2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, 7, 5);
	glRotatef(90, 0., 1., 0.);

	main::makePlate(SKY_WIDTH, SKY_HEIGHT, SKY_NR_OF_VERTS, SKY_NR_OF_VERTS, SKY_WIDTH/2, SKY_HEIGHT/2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, 7, -30);
	glRotatef(-90, 0., 1., 0.);
	main::makePlate(SKY_WIDTH, SKY_HEIGHT, SKY_NR_OF_VERTS, SKY_NR_OF_VERTS, SKY_WIDTH/2, SKY_HEIGHT/2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, SKY_HEIGHT + 7, -30);
	glRotatef(180, 1., 0., 0.);
	main::makePlate(SKY_WIDTH, SKY_HEIGHT, SKY_NR_OF_VERTS, SKY_NR_OF_VERTS, SKY_WIDTH/2, SKY_HEIGHT/2);
	glPopMatrix();
}

#include "SkyBox.h"

SkyBox::SkyBox(void)
{
	glGenTextures(SKY_MAX_TEXTURES, g_skyTextures);
	main::loadImage(g_skyTextures[TEX_SKY], ".\\StarsRed.jpg");
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
	//glRotatef(rotAngle, 0., 1., 0.);
	glTranslatef(-3, 3, -3);
	main::makePlate(SKY_SIZE, SKY_SIZE, SKY_NR_OF_VERTS, SKY_NR_OF_VERTS, SKY_SIZE, SKY_SIZE);
	glPopMatrix();
}

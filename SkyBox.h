#pragma once
#include "main.h"

const int SKY_MAX_TEXTURES = 3;
const int SKY_SIZE = 20;
const int SKY_NR_OF_VERTS = 4;

class SkyBox
{
private:
	GLuint g_skyTextures[SKY_MAX_TEXTURES];
public:
	SkyBox(void);
	~SkyBox(void);
	void update();
	void display();
};

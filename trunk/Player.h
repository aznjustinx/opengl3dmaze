#pragma once
#include "d:\sk�linn\5.�nn\t�lvugraf�k\src\opengl_project\opengl3dmaze\camera.h"

class Player :
	public Camera
{
private:
	// checkar � hvort takki er ni�ri
	bool upKeyPressed;
	bool downKeyPressed;
	bool leftKeyPressed;
	bool rightKeyPressed ;
public:
	Player(void);
	void specialKeyDown(int  key,  int  x,  int  y);
	void specialKeyUp(int  key,  int  x,  int  y);
	~Player(void);
};

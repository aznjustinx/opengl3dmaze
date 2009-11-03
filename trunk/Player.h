#pragma once
#include "d:\skólinn\5.önn\tölvugrafík\src\opengl_project\opengl3dmaze\camera.h"

class Player :
	public Camera
{
private:
	// checkar á hvort takki er niðri
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

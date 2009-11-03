#pragma once
#include "camera.h"

class Player :
	public Camera
{
public:
	// checkar � hvort takki er ni�ri
	bool upKeyPressed;
	bool downKeyPressed;
	bool leftKeyPressed;
	bool rightKeyPressed;
	Player(void);
	void specialKeyDown(int  key,  int  x,  int  y);
	void specialKeyUp(int  key,  int  x,  int  y);
	~Player(void);
};

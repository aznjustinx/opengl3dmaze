#pragma once
#include "camera.h"

class Player :
	public Camera
{
public:
	// checkar á hvort takki er niðri
	bool upKeyPressed, downKeyPressed, leftKeyPressed, rightKeyPressed;
	float lastx, lasty, xpos, ypos, zpos, xrot, yrot, angle;
	Player(void);
	void display();
	void specialKeyDown(int  key,  int  x,  int  y);
	void specialKeyUp(int  key,  int  x,  int  y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void mouse(int x, int y);
	~Player(void);
};

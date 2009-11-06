#pragma once
#include "camera.h"

class Player :
	public Camera
{
public:
	// checkar á hvort takki er niðri
	bool keyPressed, upKeyPressed, downKeyPressed, leftKeyPressed, rightKeyPressed;
	//debug
	bool floatUpPressed, floatDownPressed;
	float lastx, lasty, xpos, ypos, zpos, xrot, yrot, angle;
	Player(void);
	void specialKeyDown(int  key,  int  x,  int  y);
	void specialKeyUp(int  key,  int  x,  int  y);
	void keyboardDown(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void mouse(int x, int y);
	~Player(void);
};

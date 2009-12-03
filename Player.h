#pragma once
#include "camera.h"
#include "main.h"

class Player :
	public Camera
{
private:
	int score;
public:
	// checkar á hvort takki er niðri
	bool headlightToggle, headlight, disabled, upKeyPressed, downKeyPressed, leftKeyPressed, rightKeyPressed
			, quitPressed, jumpKeyPressed;
	//debug
	bool debugMode, floatUpPressed, floatDownPressed;
	float lastx, lasty, xpos, ypos, zpos, xrot, yrot, angle;
	Player(void);
	void specialKeyDown(int  key,  int  x,  int  y);
	void specialKeyUp(int  key,  int  x,  int  y);
	void keyboardDown(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
	void mouse(int x, int y);
	~Player(void);
	void addToScore(int value);
	int getScore();
};

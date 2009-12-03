#include <iostream>
#include <math.h>
#include "Constants.h"
#include "Player.h"

using namespace std;

Player::Player(void) {
	headlightToggle, headlight, disabled, upKeyPressed = downKeyPressed = leftKeyPressed = rightKeyPressed, quitPressed, jumpKeyPressed = false;
	// debug
	floatUpPressed = floatDownPressed = false;
}

void Player::addToScore(int value)
{
	score += value;
}

int Player::getScore()
{
	return score;
}

void Player::specialKeyDown(int  key,  int  x,  int  y)
{
	if ( !disabled) 
	{
		switch(key)
		{
			case GLUT_KEY_UP :
			upKeyPressed  =  true;
			break;
			case GLUT_KEY_DOWN :
			downKeyPressed  =  true;
			break;
			case GLUT_KEY_RIGHT :
			rightKeyPressed  =  true;
			break;
			case GLUT_KEY_LEFT :
			leftKeyPressed  =  true;
			break;
		}
	}
}

void Player::specialKeyUp(int  key,  int  x,  int  y)
{
	switch(key)
	{
		case GLUT_KEY_UP :
			upKeyPressed  =  false;
			break;
		case GLUT_KEY_DOWN :
			downKeyPressed  =  false;
			break;
		case GLUT_KEY_RIGHT :
			rightKeyPressed  =  false;
			break;
		case GLUT_KEY_LEFT :
			leftKeyPressed  =  false;
			break;
	}
}

void Player::keyboardDown(unsigned char key, int x, int y)
{
	switch(key)
	{
		if ( !disabled)
		{
			case 'w' :
				upKeyPressed  =  true;
				break;
			case 's' :
				downKeyPressed  =  true;
				break;
			case 'd' :
				rightKeyPressed  =  true;
				break;
			case 'a' :
				leftKeyPressed  =  true;
				break;
		}
		case 'q' :
			quitPressed = true;
			break;
		case 'l' :
			headlight = !headlight;
			if (headlight)
			{
				main::changeLightning(GL_LIGHT1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 0,23,0,1);
				cout<<"HEADLIGHT ON!!!";
			}
			//headlight = true;
			break;
		case ' ':
			jumpKeyPressed = true;
			break;
		if (debugMode)
		{
			case 'r' :
				floatUpPressed = true;
				break;
			case 'f' :
				floatDownPressed = true;
				break;
		}
	}
}

void Player::keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w' :
		upKeyPressed  =  false;
		break;
		case 's' :
		downKeyPressed  =  false;
		break;
		case 'd' :
		rightKeyPressed  =  false;
		break;
		case 'a' :
		leftKeyPressed  =  false;
		break;
		case 'q' :
		quitPressed = false;
		break;
		case ' ':
			jumpKeyPressed = false;
		break;
		if (debugMode)
		{
			case 'r' :
			floatUpPressed = false;
			break;
			case 'f' :
			floatDownPressed = false;
			break;
		}

	}
}

Player::~Player(void)
{
}
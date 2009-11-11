#include <iostream>
#include <math.h>
#include "Constants.h"
#include "Player.h"

using namespace std;

Player::Player(void) {
	keyPressed = upKeyPressed = downKeyPressed = leftKeyPressed = rightKeyPressed, quitPressed = false;
	// debug
	floatUpPressed = floatDownPressed = false;

}

void Player::specialKeyDown(int  key,  int  x,  int  y)
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
	keyPressed = true;
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
	keyPressed = false;
}

void Player::keyboardDown(unsigned char key, int x, int y)
{
	switch(key)
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
		case 'q' :
		quitPressed = true;
		break;

		//debug
		case 't' :
		floatUpPressed = true;
		break;
		case 'g' :
		floatDownPressed = true;
		break;
		case 'l' :
		glShadeModel(GL_FLAT);
		break;
		case 'm' :
		glShadeModel(GL_SMOOTH);
		break;
	}
	keyPressed = true;
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

		//debug
		case 't' :
		floatUpPressed = false;
		break;
		case 'g' :
		floatDownPressed = false;
		break;
	}
	keyPressed = false;

}

Player::~Player(void)
{
}
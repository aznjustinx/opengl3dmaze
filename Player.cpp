#include "Player.h"
#include <GL/glut.h>



Player::Player(void) {
	Player::upKeyPressed = Player::downKeyPressed = Player::leftKeyPressed = Player::rightKeyPressed = false;

}

void Player::specialKeyDown(int  key,  int  x,  int  y) {
	//cout<<"DOING DONG";
	if(key == GLUT_KEY_UP)
		upKeyPressed  =  true;
	if(key == GLUT_KEY_DOWN)
		downKeyPressed  =  true;
	if(key == GLUT_KEY_RIGHT)
		rightKeyPressed  =  true;
	if(key == GLUT_KEY_LEFT)
		leftKeyPressed  =  true;
}

void Player::specialKeyUp(int  key,  int  x,  int  y) {
	if(key == GLUT_KEY_UP)
		upKeyPressed  =  false;
	if(key == GLUT_KEY_DOWN)
		downKeyPressed  =  false;
	if(key == GLUT_KEY_RIGHT)
		rightKeyPressed  =  false;
	if(key == GLUT_KEY_LEFT)
		leftKeyPressed  =  false;
}


Player::~Player(void)
{
}

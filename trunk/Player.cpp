#include "Player.h"
#include <iostream>
#include <math.h>
#include "Constants.h"

using namespace std;

//const float PI = 3.141592654f;

Player::Player(void) {
	cout<<"Player constructor";
	upKeyPressed = downKeyPressed = leftKeyPressed = rightKeyPressed = false;
	xpos=0, ypos=0, zpos=0, xrot=0, yrot=0, angle=0.0;

}

void Player::display() {
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos, 0, -zpos); //translate the screen to the position of our camera
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
	}

}

void Player::moveUp()
{
	float xrotrad, yrotrad;
	yrotrad = yrot * RadPerDeg; //(yrot / 180 * Pi);
	xrotrad = xrot * RadPerDeg; //(xrot / 180 * Pi);
	xpos += float(sin(yrotrad))/2;
	zpos -= float(cos(yrotrad))/2;
	ypos -= float(sin(xrotrad))/2;
}

void Player::moveDown()
{
	float xrotrad, yrotrad;
	yrotrad = yrot * RadPerDeg; //(yrot / 180 * PI);
	xrotrad = xrot * RadPerDeg; //(xrot / 180 * PI);
	xpos -= float(sin(yrotrad))/2;
	zpos += float(cos(yrotrad))/2;
	ypos += float(sin(xrotrad))/2;	
}

void Player::moveLeft()
{
	yrot -= 5;
	if (yrot < -360)
		yrot += 360;
}

void Player::moveRight()
{
	yrot += 5;
	if (yrot < -360)
		yrot -= 360;
}

void Player::mouse(int x, int y) {
	int diffx=x-lastx; //check the difference between the current x and the last x position
	int diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	xrot += (float) diffy/30; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float) diffx/30;// set the xrot to yrot with the addition of the difference in the x position
}

Player::~Player(void)
{
}
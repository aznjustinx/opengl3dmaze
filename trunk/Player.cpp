#include "Player.h"
#include <iostream>
#include <math.h>

using namespace std;

const float PI = 3.141592654f;

Player::Player(void) {
	cout<<"Player constructor";
	upKeyPressed = downKeyPressed = leftKeyPressed = rightKeyPressed = false;
	xpos=0, ypos=0, zpos=0, xrot=0, yrot=0, angle=0.0;

}

void Player::display() {
	glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void Player::specialKeyDown(int  key,  int  x,  int  y) {
	cout<<"DOING DONG";
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

void Player::moveUp()
{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * PI);
	xrotrad = (xrot / 180 * PI);
	xpos += float(sin(yrotrad))/2;
	zpos -= float(cos(yrotrad))/2;
	ypos -= float(sin(xrotrad))/2;
}

void Player::moveDown()
{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * PI);
	xrotrad = (xrot / 180 * PI);
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
/*
Stefan Einarsson
stefane07@ru.is

Skilaverkefni 3
Tölvugrafik 
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

float _angle = 30.0f;
float _cameraAngle = 0.0f;

// checkar á hvort takki er niðri
bool    upKeyPressed  =  false;
bool    downKeyPressed  =  false;
bool    leftKeyPressed  =  false;
bool    rightKeyPressed  =  false;


const float PI = 3.141592654f;
const float piover180 = 0.0174532925f; // til að skipta milli rad og deg
float xpos=0,ypos=0,zpos=0,xrot = 0, yrot = 0, angle=0.0;
float lastx, lasty;

void  specialKeyDown(int  key,  int  x,  int  y)
{
	if(key == GLUT_KEY_UP)
		upKeyPressed  =  true;
	if(key == GLUT_KEY_DOWN)
		downKeyPressed  =  true;
	if(key == GLUT_KEY_RIGHT)
		rightKeyPressed  =  true;
	if(key == GLUT_KEY_LEFT)
		leftKeyPressed  =  true;
}

void  specialKeyUp(int  key,  int  x,  int  y)
{
	if(key == GLUT_KEY_UP)
		upKeyPressed  =  false;
	if(key == GLUT_KEY_DOWN)
		downKeyPressed  =  false;
	if(key == GLUT_KEY_RIGHT)
		rightKeyPressed  =  false;
	if(key == GLUT_KEY_LEFT)
		leftKeyPressed  =  false;
}


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
}

// þegar breyting er
void handleResize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
	void gluPerspective(	GLdouble  	fovy, 
 							GLdouble  	aspect, 
 							GLdouble  	zNear, 
 							GLdouble  	zFar);
	*/
	gluPerspective(	45.0f, 
					(double)width / (double)height, 
					0.1f, 
					100.0f);	
	// glMatrixMode verður að vera fyrir neðan allt hér...
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity();
}

void camera()
{
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void loadLightning()
{
	//Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}
void drawBox()
{
	//glTranslatef(0.0f, 0.0f, -8.0f); // zooma út
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);	
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	
	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	
	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	
	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	
	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	//glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	
	glEnd();
	glLoadIdentity(); // Til að núlla hreyfingu á angle
}

// sér um að kalla á og birta objectana
void drawScene()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity(); // Til að fara aftur að miðju
	camera();
	loadLightning();
	
	drawBox();

	glutSwapBuffers();
}

void updateScene(int id)
{
	glutTimerFunc(32,updateScene,0);
	if(upKeyPressed)
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos += float(sin(yrotrad))/2;
		zpos -= float(cos(yrotrad))/2;
		ypos -= float(sin(xrotrad))/2;
	}

	if(downKeyPressed)
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos -= float(sin(yrotrad))/2;
		zpos += float(cos(yrotrad))/2;
		ypos += float(sin(xrotrad))/2;
	}

	if(leftKeyPressed)
	{
		yrot -= 5;
		if (yrot < -360)yrot += 360;
	}

	if(rightKeyPressed)
	{
		yrot += 5;
		if (yrot < -360)yrot -= 360;
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed
}

void mouseMovement(int x, int y) {
	int diffx=x-lastx; //check the difference between the current x and the last x position
	int diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	xrot += (float) diffy/30; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float) diffx/30;// set the xrot to yrot with the addition of the difference in the x position
}

// sér um örvatakkana
// vantar smoothness!!!!!!****
//void myArrowKeys (int a_keys, int x, int y )
//{
//
//	switch ( a_keys ) {
//	case GLUT_KEY_UP:					// Up
//	{
//		float xrotrad, yrotrad;
//		yrotrad = (yrot / 180 * PI);
//		xrotrad = (xrot / 180 * PI);
//		xpos += float(sin(yrotrad));
//		zpos -= float(cos(yrotrad));
//		ypos -= float(sin(xrotrad));
//		break;
//	}
//	case GLUT_KEY_DOWN:					// Down
//	{
//		float xrotrad, yrotrad;
//		yrotrad = (yrot / 180 * PI);
//		xrotrad = (xrot / 180 * PI);
//		xpos -= float(sin(yrotrad));
//		zpos += float(cos(yrotrad));
//		ypos += float(sin(xrotrad));
//		break;
//	}	
//	case GLUT_KEY_RIGHT:				// Right		
//	{
//		yrot += 5;
//		if (yrot < -360)yrot -= 360;
//		break;
//	}
//	case GLUT_KEY_LEFT:					// Left    
//	{
//		yrot -= 5;
//    if (yrot < -360)yrot += 360;
//		break;
//	}
//	default:
//	break;
//	}
//}

// main fallið
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(640, 480);			// stærð glugga
	glutInitWindowPosition(100,100);		// init staðsetning glugga
	glutCreateWindow("Skilaverkefni 3");	// nafn glugga
	initRendering();						// inits 3D rendering

	// Handlers
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	

	glutDisplayFunc(drawScene);			// Teiknar hlutina
	glutReshapeFunc(handleResize);

	// keyboard input
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutIgnoreKeyRepeat(1);
	glutTimerFunc(32,  updateScene,  0);
	//glutSpecialFunc(myArrowKeys);		// Virkjar örvatakkana
	glutMainLoop();    
}

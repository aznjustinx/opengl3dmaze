/*
Stefan Einarsson
stefane07@ru.is

Skilaverkefni 3
Tölvugrafik 
*/
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

float _angle = 30.0f;
float _cameraAngle = 0.0f;

const float piover180 = 0.0174532925f; // til að skipta milli rad og deg
float xpos;
float zpos;
float heading;

GLfloat yrot;
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat z = 0.0f;		// Dypt inn að skjá


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
	glTranslatef(0.0f, 0.0f, -8.0f); // zooma út
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
	
	
	loadLightning();
	
	drawBox();

	// hreyfing myndavélar
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias-0.25f;
	GLfloat sceneroty = 360.0f - yrot;

	glRotatef(sceneroty,0,1.0f,0);
	
	glTranslatef(xtrans, ytrans, ztrans);
	
	glutSwapBuffers();
}

void updateScene()
{
	//_angle += 1.0f;			// hraði á rotation
	//if (_angle > 360) {
	//	_angle -= 360;
	//}
	
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	//glutTimerFunc(25, updateScene, 0);
}

// sér um örvatakkana
void myArrowKeys ( int a_keys, int x, int y )
{
	switch ( a_keys ) {
	case GLUT_KEY_UP:					// Up
	{
		xpos -= (float)sin(heading*piover180) * 0.05f;
		zpos -= (float)cos(heading*piover180) * 0.5f;	// labba áfram
		walkbiasangle+= 10;
		walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
		drawScene();
		break;
	}
	case GLUT_KEY_DOWN:					// Down
	{
		xpos += (float)sin(heading*piover180) * 0.05f;
		zpos += (float)cos(heading*piover180) * 0.5f;	// labba til baka
		walkbiasangle-= 10;
		walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
		drawScene();
		break;
	}
	case GLUT_KEY_LEFT:					// Left    
	{
		heading += 3.0f;	// horfa til vinstri
		yrot = heading;
		drawScene();
		break;
	}
	case GLUT_KEY_RIGHT:				// Right		
	{
		heading -= 3.0f;	// horfa til hægri
		yrot = heading;
		drawScene();
		break;
	}
	default:
	break;
	}
}

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
	glutSpecialFunc(myArrowKeys);		// Virkjar örvatakkana
	glutDisplayFunc(drawScene);			// Teiknar hlutina
	glutReshapeFunc(handleResize);
//	glutTimerFunc(25, updateScene, 0);	//Add a timer
	glutIdleFunc(updateScene);
	glutMainLoop();    
}

#ifndef maze_h
#define maze_h
#include "Point3.h"
#include "Mesh.h"


const float TILE_SIZE = 3.0;
const int MAP_SIZE = 10;
const int MAX_TEXTURES = 5;

class Maze
{
private:
	Mesh* finishSign;
	float finishRotAngle;
	int nrOfCubes;
	Point3 finishPos;
	
public:
	bool finished;
	Point3 cubesPos[MAP_SIZE][MAP_SIZE];
	Maze();
	~Maze();		
	void displayMaze();
	void displayBox();
	void displayWall();
	void displayFloor();
	Point3 getFinishPos();
	Point3 getCubesPos(int i, int j);	
	int getNrOfCubes();
	void setPosition(float x, float y, float z, int pos);
	void init();
	void displayFinishSign();
	void updateObjects();
	void loadImage(GLuint textureID, char* filename);
	void makePlate(float width, float height, int dw, int dh, float texWidth, float texHeight);
	void displayCube();
	void materialColor(float dif0, float dif1, float dif2, float dif3
						 , float spec0, float spec1, float spec2, float spec3
						 , float amb0, float amb1, float amb2, float amb3, float shininess);

	
};
#endif maze_h
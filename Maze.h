#ifndef maze_h
#define maze_h
#include "Point3.h"
#include "Mesh.h"
#include "Outside.h"
#include "Piece.h"

const float TILE_SIZE =3.0;
const int MAP_SIZE_Y = 4;
const int MAP_SIZE_Z = 9;
const int MAP_SIZE_X = 10;
const int MAZE_MAX_TEXTURES = 5;
const int NR_OF_VERTEXES = 4;
//const float GOODIE_SIZE = 0.3;
//const int GOODIE_ROT_INC = 5;
//const int GOODIE_NR_OF_VERTS = 8;

class Maze
{
private:
	Mesh* finishSign;
	float finishRotAngle;
	Point3 finishPos;
	Outside* outside;
	//float goodieRotAngle;
	Piece* pieces[MAP_SIZE_Y][MAP_SIZE_Z][MAP_SIZE_X];
	int ghostCount;
	GLuint g_MazeTextures[MAZE_MAX_TEXTURES];
public:
	bool finished;
	Point3 cubesPos[MAP_SIZE_Y][MAP_SIZE_Z][MAP_SIZE_X];
	Point3 floorPos[MAP_SIZE_Y][MAP_SIZE_Z][MAP_SIZE_X];
	Maze();
	~Maze();		
	void displayMaze();
	void displayBox();
	void displayWall();
	void displayFloor();
	Point3 getFinishPos();
	Point3 getCubesPos(int y,int z, int x);
	Point3 getFloorPos(int y,int z, int x);
	void setPosition(float x, float y, float z, int pos);
	void init();
	void displayFinishSign();
	void updateObjects();
	//void loadImage(GLuint textureID, char* filename);
	//void makePlate(float width, float height, int dw, int dh, float texWidth, float texHeight);
	void displayCube(bool ceiling);
	/*void materialColor(float dif0, float dif1, float dif2, float dif3
						 , float spec0, float spec1, float spec2, float spec3
						 , float amb0, float amb1, float amb2, float amb3, float shininess);*/
	void displayGoodie();

	
};
#endif maze_h
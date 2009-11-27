#ifndef maze_h
#define maze_h
#include "main.h"
#include "Point3.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Piece.h"

const float TILE_SIZE =3.0;
const int MAP_SIZE_Y = 4;
const int MAP_SIZE_Z = 9;
const int MAP_SIZE_X = 10;
const int MAZE_MAX_TEXTURES = 5;
const int NR_OF_VERTEXES = 4;
const int NR_OF_GHOSTS = 25;

class Maze
{
private:
	Mesh* finishSign;
	float finishRotAngle;
	Point3 finishPos;
	SkyBox* skyBox;
	
	int ghostCount;
	GLuint g_MazeTextures[MAZE_MAX_TEXTURES];
public:
	Piece* pieces[MAP_SIZE_Y][MAP_SIZE_Z][MAP_SIZE_X];
	bool finished;
	Point3 cubesPos[MAP_SIZE_Y][MAP_SIZE_Z][MAP_SIZE_X];
	Point3 floorPos[MAP_SIZE_Y][MAP_SIZE_Z][MAP_SIZE_X];
	Maze();
	~Maze();	
	//void deletePiece(int y,int z, int x);
	void displayMaze();
	void displayBox();
	void displayWall();
	void displayFloor();
	//bool getPiece(int y, int z, int x);
	Point3 getFinishPos();
	Point3 getCubesPos(int y,int z, int x);
	Point3 getFloorPos(int y,int z, int x);
	void setPosition(float x, float y, float z, int pos);
	void init();
	void displayFinishSign();
	void updateObjects();
	void displayCube(bool ceiling);
};
#endif maze_h
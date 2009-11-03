#ifndef	mesh_h
#define mesh_h

#include <stdlib.h>
#include "Point3.h"

class VertexID {
public: 
	int vertIndex;	// index of this vertex in the vertex list
	int normIndex;	// index of this vertex's normal
};

class Face {
public:
	int nVerts;			// number of vertices in this face
	VertexID* vert;	// the list of vertex and normal indices
	Face() {nVerts=0; vert=NULL;}		// constructor
	~Face() {delete[] vert; nVerts=0;}	// destructor
};

class Mesh {
private:
	int numVerts;		// number of vertices in the mesh
	Point3* pt;			// array of 3D vertices
	int numNormals;		// number of normal vectors for the mesh
	Vector3* norm;		// array of normals
	int numFaces;		// number of faces in the mesh
	Face* face;			// array of face data

public:
	Mesh();
	~Mesh(void);
	int readFile(char* fileName);  // read a description of a mesh
	void draw();					// draw the mesh
};
#endif mesh_h

#include <fstream>
#include "Mesh.h"


Mesh::Mesh()
{
	numVerts = 0;
	numNormals = 0;
	numFaces = 0;
}

Mesh::~Mesh()
{
	if(pt)
		delete[] pt;
	if(norm)
		delete[] norm;
	if(face)
		delete[] face;
}

void Mesh::draw()
{

	for (int f=0; f<numFaces; f++) 
	{	// draw each face
		  glBegin(GL_POLYGON);
			for (int v=0; v<face[f].nVerts; v++) 
			{	// for each vertex
				int in = face[f].vert[v].normIndex;	// index of this normal
				int iv = face[f].vert[v].vertIndex;	// index of this vertex
				glNormal3f(norm[in].x,norm[in].y,norm[in].z);
				glVertex3f(pt[iv].x,pt[iv].y, pt[iv].z);
			}
		   glEnd();
		
	}
}


int Mesh::readFile(char* fileName)
{
	std::ifstream infile;
	infile.open(fileName);
	if(infile.fail()) return -1;		// error: can't open file
	if(infile.eof()) return -1;			// error: empty file

	// Read number of vertices, normals and faces
	infile >> numVerts >> numNormals >> numFaces;
	pt = new Point3[numVerts];
	norm = new Vector3[numNormals];
	face = new Face[numFaces];
	
	for (int p=0; p<numVerts; p++)			// read the vertices
	{
		infile >> pt[p].x >> pt[p].y >> pt[p].z;
	};

	for (int n=0; n<numNormals; n++)			// read the normals
	{
        infile >> norm[n].x >> norm[n].y >> norm[n].z;
	
	};

	for (int f=0; f<numFaces; f++)			// read the faces
	{
		infile >> face[f].nVerts;
		face[f].vert = new VertexID[face[f].nVerts];
		for (int i=0; i<face[f].nVerts; i++)
			infile	>> face[f].vert[i].vertIndex;
		for (int k=0; k<face[f].nVerts; k++)
			    infile >> face[f].vert[k].normIndex;
	
	};

	infile.close();

	return 0;								// success
}

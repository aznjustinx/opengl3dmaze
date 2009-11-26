#pragma once
#include <FreeImage.h>

const int MAX_TEXTURES = 5;
static GLuint g_textures[MAX_TEXTURES];

class main
{

public:
	//static GLuint g_textures[MAX_TEXTURES];
	// Structure used in makePlate
	struct Vertex {
	// GL_T2F_V3F
	float tu, tv;
	float x, y, z;
	};
	// makePlate
	// Create a flat polygonal mesh of the given dimensions in the x/y plane
	// 'dw' and 'dh' specify the number of vertices across the width and height 
	static void makePlate(float width, float height, int dw, int dh, float texWidth, float texHeight) {
		float widthRatio = width / texWidth;
		float heightRadio = height / texHeight;

		Vertex *v = new Vertex[dw*dh];
		float stepw = (width/(float)(dw-1));
		float steph = (height/(float)(dh-1));
		// Create Our Plate Verticies
		for (int i = 0; i < dw; i++) {
			for (int j = 0; j < dh; j++) {
				v[i*dh+j].x = i*stepw;				
				v[i*dh+j].y = j*steph;						
				v[i*dh+j].z = 0;				
				v[i*dh+j].tu = ((float)i/ (float)(dw-1) * widthRatio);
				v[i*dh+j].tv = ((float)j/ (float)(dh-1) * heightRadio);
			}
		}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
		for (int i = 0; i < dw - 1; i++) {
			// Draw A Triangle Strip For Each Column Of Our Mesh
			glBegin(GL_TRIANGLE_STRIP);
			for (int j = 0; j < dh; j++) {
				glTexCoord2f(v[i*dh+j].tu, v[i*dh+j].tv);
				glVertex3f(v[i*dh+j].x, v[i*dh+j].y, v[i*dh+j].z);	// Draw Vertex
				glTexCoord2f(v[(i+1)*dh+j].tu, v[(i+1)*dh+j].tv);
				glVertex3f(v[(i+1)*dh+j].x, v[(i+1)*dh+j].y, v[(i+1)*dh+j].z);// Draw Vertex
			}
			glEnd();
		}
		delete v;
	}

	static void materialColor(float dif0, float dif1, float dif2, float dif3
						 , float spec0, float spec1, float spec2, float spec3
						 , float amb0, float amb1, float amb2, float amb3, float shininess)
	{
		float materialArr[4];
		materialArr[0] = dif0;
		materialArr[1] = dif1;
		materialArr[2] = dif2;
		materialArr[3] = dif3;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialArr);
		materialArr[0] = spec0;
		materialArr[1] = spec1;
		materialArr[2] = spec2;
		materialArr[3] = spec3;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialArr);
		materialArr[0] = amb0;
		materialArr[1] = amb1;
		materialArr[2] = amb2;
		materialArr[3] = amb3;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialArr);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}

		// loadImage
	// Create a new texture object and bind it to a valid textureID
	// Load the image data from the given file
	static void loadImage(GLuint textureID, char* filename) {
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(filename, 0);
		FIBITMAP *dib = FreeImage_Load(fifmt, filename,0);
		dib = FreeImage_ConvertTo32Bits(dib);
		if( dib != NULL ) {
			// Create a new texture object, bound to the name 'textureID'
			// Initially only default values fill the new texture object.
			// It does not contain texture data yet.
			glBindTexture( GL_TEXTURE_2D, textureID );
			glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			// On some platforms, the data gets read in the 
	// BGR format instead of RGB
			// This has to be "normalized" by reading the 
	// correct bits into a definite RGB format
			int bytespp = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);
			BYTE *bits = new BYTE[FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib) * bytespp];
			// get a pointer to FreeImage's data.
			BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
			// Iterate through the pixels, copying the data
			// from 'pixels' to 'bits' except in RGBA format.
			for(int pix=0; pix<FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib)*bytespp; pix+=bytespp) {
				bits[pix+0]=pixels[pix+FI_RGBA_RED];
				bits[pix+1]=pixels[pix+FI_RGBA_GREEN];
				bits[pix+2]=pixels[pix+FI_RGBA_BLUE];
				bits[pix+3]=pixels[pix+FI_RGBA_ALPHA];
			}
			// Fill the current texture object with texture data
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
					GL_RGBA, GL_UNSIGNED_BYTE, bits );
			// Unload the source image.
			// and free the bit data.
			FreeImage_Unload(dib);
			delete bits;
		}
		//return textureID;
	}

	
	
	enum { TEX_FLOOR, TEX_WALL, TEX_GOODIE, TEX_TILES, TEX_BRICKS };

	main(void);
	~main(void);
};
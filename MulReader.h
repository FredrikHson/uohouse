#ifndef __MULREADER_H__
#define __MULREADER_H__

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>								// Header File For Variable Argument Routines
#include <string.h>								// Header File For String Management
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library

struct Texture
{
	GLubyte *ImageData;
	GLuint TexID;
	GLushort Width;
	GLushort Height;
	GLushort realWidth;
	GLushort realHeight;
	int ItemID;
};
//bool LoadArt(Texture *Tex,int i,char* artfilename,char* artidxfilename,char*titledata);
bool LoadArt(Texture *Tex,int i,FILE* art,FILE* artidx);

#endif
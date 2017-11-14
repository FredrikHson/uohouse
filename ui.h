#ifndef UI_H
#define UI_H

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>								// Header File For Variable Argument Routines
#include <string.h>								// Header File For String Management
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <stdlib.h>
#ifdef UI_EXPORTS
#define UI_API __declspec(dllexport)
#else
#define UI_API __declspec(dllimport)
#endif



typedef unsigned char byte;

int resx=640;
int resy=480;
bool UI_API UiNeedKeyboard;
void UI_API SetupRes(int x,int y);
void UI_API Setup2D(int x,int y);
void UI_API Setup2D();
void UI_API Setup3D(void);


struct Vec2f
{
	float x,y;
};
struct Color3f
{
	float r,g,b;
};


class UI_API TGA
{
public:	
	GLuint width;
	GLuint height;
	GLuint bits;
	GLuint ID;
	
	GLubyte *TextureImage;

	TGA(){};
	~TGA()
	{
		};
	
	bool Load(char*filename);

};

class UI_API Cursor
{
public:
	TGA Pointer;
	Cursor(){};
	~Cursor(){};
	void DrawCursor(int x,int y);
};


class UI_API Button
{
	void (*leftfunc)();
	void (*rightfunc)();
public:
	char *Text;
	TGA ButtonImage;
	int x,y,w,h;
	bool Pressed;
	unsigned char mb;
	Button()
	{
		Pressed=false;
		x=y=0;
		w=h=1;
	};
	Button(int X,int Y,int W,int H)
	{
		x=X;
		y=Y;
		w=W;
		h=H;
	};
	Button(int X,int Y,int W,int H,char *Caption)
	{
		Pressed=false;
		x=X;
		y=Y;
		w=W;
		h=H;
		Text=Caption;
	};
	Button(char *filename,int X,int Y,int W,int H)
	{
		Pressed=false;
		x=X;
		y=Y;
		w=W;
		h=H;
		this->ButtonImage.Load(filename);
	};
	~Button(){};
	void Draw();
	bool Check(int m_x,int m_y);
	void Doit(unsigned char button);
	void Click(int m_x,int m_y,unsigned char button);
	void AssignLFunc(void (*func)())
	{
		leftfunc=func;
	};
	void AssignRFunc(void (*func)())
	{
		rightfunc=func;
	};
};


class UI_API Font
{
	unsigned int displaylist;
	TGA FontTexture;
public:
	Color3f Color;
	Font(){};
	void LoadFont(char *filename,int size=16);
	~Font(){};
	void SetColor(float r,float g,float b)
	{
		Color.r=r;
		Color.g=g;
		Color.b=b;
	};
	Color3f GetColor()
	{
		return Color;
	}
	void print(int x,int y,char *str);
	void print(int x,int y,char *str,int len,int start);
	void print(int x,int y,float Number);
	void print(int x,int y,int Number);
};

class UI_API TextBox
{
public:
	Font *f;
	char Text[256];
	int x,y,w,h;
	int maxlen,firsttodraw;
	bool multiline;
	bool IsBeingEdited;
	unsigned char mb;
	DWORD BlinkTimer;
	bool Blink;
	unsigned char where;

	TextBox(int X,int Y,int W,int H)
	{
		IsBeingEdited=false;
		multiline=false;
		x=X;
		y=Y;
		w=W;
		h=H;
		where=0;
	}
	~TextBox()
	{
	//	if(f)
	//		f=NULL;
	}
	void SetMultiline(bool m)
	{
		multiline=m;
	}
	void Draw();
	void BindFont(Font *font);
	bool Check(int m_x,int m_y);
	void TextBox::Click(int m_x,int m_y,unsigned char button);
	void KeyHandler(DWORD milliseconds);
	
};

class UI_API Keyboard
{										
public:
	BOOL keyDown [256];
	bool KeyPressed[256];
	bool CapslockState;
	Keyboard(){ UiNeedKeyboard=false; }	
};
Keyboard UI_API KeyBoard;

#endif
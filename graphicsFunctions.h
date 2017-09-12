/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : graphicsFunctions
File Type : header
*/

#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

#define _LINE_WIDTH 1.0f
#define _PI 3.14

struct COLOR
{
	float red, green, blue;
};

const COLOR _BLACK = 	{ 0.0f, 0.0f, 0.0f };
const COLOR _WHITE = 	{ 1.0f, 1.0f, 1.0f };
const COLOR _RED = 		{ 1.0f, 0.0f, 0.0f };
const COLOR _BLUE = 	{ 0.0f, 0.0f, 1.0f };
const COLOR _BACKGROUND = { 1.0f, 1.0f, 0.9f };

struct POINT
{
	unsigned int x, y;
};

struct LINE
{
	POINT start;
	POINT end;
};

bool operator==(const COLOR &c1, const COLOR &c2);
void initDisplay(int argc, char **argv); /*initialize the display window*/
void initBoard(); /*initialize the board*/
void drawLine(POINT start, POINT end, COLOR color, float width); /*draw a line between two POINTS*/
void drawLine(int xa, int ya, int xb, int yb, COLOR color, float width); /*draw a line between (xa,ya) and (xb,yb)*/
void drawCircle( int x, int y, COLOR color, float radius ); /*draw a filled circle with specifeid color, radius and center*/
void drawCharacter( int x, int y, COLOR color, char ch ); /*draw the specified character on the screen*/

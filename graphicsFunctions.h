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

const COLOR _BLACK = { 0.0f, 0.0f, 0.0f };
const COLOR _WHITE = { 1.0f, 1.0f, 1.0f };

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
void initDisplay(int argc, char **argv);
void initBoard();
void drawLine(POINT start, POINT end, COLOR color, float width);
void drawLine(int xa, int ya, int xb, int yb, COLOR color, float width);
void drawCircle( int x, int y, COLOR color, float radius );

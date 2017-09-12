/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : graphicsFunctions
File Type : source
*/

#include "graphicsFunctions.h"

bool operator==(const COLOR &c1, const COLOR &c2)
{
	if( (c1.red == c2.red) && (c1.green == c2.green) && (c1.blue == c2.blue) )
	{
		return true;
	}
	return false;
}

/*initialize the display window*/
void initDisplay(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Reactive GO");
}

/*initialize the board*/
void initBoard() 
{
	cout << "Initializing board" << endl;
	glClearColor(_BACKGROUND.red, _BACKGROUND.green, _BACKGROUND.blue, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);
}

/*draw a line between two POINTS*/
void drawLine(POINT start, POINT end, COLOR color, float width)
{
	glColor3f(color.red, color.green, color.blue); 
	glLineWidth(width);
	glBegin(GL_LINES); 
		glVertex2i(start.x, start.y); 
		glVertex2i(end.x, end.y);
	glEnd();
}

/*draw a line between (xa,ya) and (xb,yb)*/
void drawLine(int xa, int ya, int xb, int yb, COLOR color, float width)
{
	glColor3f(color.red, color.green, color.blue); 
	glLineWidth(width);
	glBegin(GL_LINES); 
		glVertex2i(xa, ya); 
		glVertex2i(xb, yb);
	glEnd();
}

/*draw a filled circle with specifeid color, radius and center*/
void drawCircle( int x, int y, COLOR color, float radius )
{
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * _PI; i += _PI / 10) //<-- Change this Value
 			glVertex2f((float)x + (cos(i) * radius), (float)y + (sin(i) * radius) );
	glEnd();			
}

/*draw the specified character on the screen*/
void drawCharacter( int x, int y, COLOR color, char ch )
{
	glColor3f( color.red, color.green, color.blue );
	glRasterPos2i(x, y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
}

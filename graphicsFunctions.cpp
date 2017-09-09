#include "graphicsFunctions.h"

void initDisplay(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Reactive GO");
}

void initBoard() 
{
	glClearColor(1.0, 1.0, 0.9, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);
}

void drawLine(POINT start, POINT end, COLOR color, float width)
{
	glColor3f(color.red, color.green, color.blue); 
	glLineWidth(width);
	glBegin(GL_LINES); 
		glVertex2i(start.x, start.y); 
		glVertex2i(end.x, end.y);
	glEnd();
}

void drawLine(int xa, int ya, int xb, int yb, COLOR color, float width)
{
	glColor3f(color.red, color.green, color.blue); 
	glLineWidth(width);
	glBegin(GL_LINES); 
		glVertex2i(xa, ya); 
		glVertex2i(xb, yb);
	glEnd();
}

void drawCircle( int x, int y, COLOR color, float radius )
{
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * _PI; i += _PI / 20) //<-- Change this Value
 			glVertex2f((float)400 + (cos(i) * radius), (float)400 + (sin(i) * radius) );
	glEnd();			
}
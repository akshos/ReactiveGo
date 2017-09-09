#include <GL/glut.h>
#include <math.h>

#define PI 3.14

int radius = 100;

void game()
{
	glClear(GL_COLOR_BUFFER_BIT);		/* clear the display */
	glColor3f(0.2, 0.3, 0.5);
	glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * PI; i += PI / 20) //<-- Change this Value
 			glVertex3f((float)400 + (cos(i) * radius), (float)400 + (sin(i) * radius), 1.0 );
	glEnd();				/* OpenGL draws the filled triangle */
  glFlush();				
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Reactive GO");
	glClearColor(1.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);
	glutDisplayFunc(game);
	glutMainLoop();
}

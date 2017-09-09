#include "board.h"

Board board;

void game()
{
	glClear(GL_COLOR_BUFFER_BIT);
	board.drawGrid();
	glFlush();
}

void onMouseClick( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN )
	{
		cout << "Mouse Position: X: " << x << " Y: " << y << endl;
	}
}

int main(int argc, char **argv)
{
	initDisplay(argc, argv);
	board.init();
	glutDisplayFunc(game);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}

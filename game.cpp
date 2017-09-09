#include "board.h"

Board board;

COLOR player[2];
int turn, row, col;

void switchPlayer()
{
	turn = (turn+1)%2;
}

void calculateCellPos(int x, int y)
{
	row = ( y / _CELL_HEIGHT );
	col = ( x / _CELL_WIDTH );
	cout << "Cell position : ROW: " << row+1 << " COL: " << col+1 << endl;
}

void playerFillCell()
{
	board.fillCell( row, col, player[turn] );
	switchPlayer();
}

void game()
{
	glClear(GL_COLOR_BUFFER_BIT);
	board.renderGrid();
	glFlush();
}

void onMouseClick( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN )
	{
		cout << "Mouse Position: X: " << x << " Y: " << y << endl;
		calculateCellPos(x, y);
		playerFillCell();
	}
}

int main(int argc, char **argv)
{
	initDisplay(argc, argv);
	board.init();
	glutDisplayFunc(game);
	glutMouseFunc(onMouseClick);
	player[0] = { 1, 0, 0 };
	player[1] = { 0, 0, 0 };
	turn = 0;
	glutMainLoop();
	return 0;
}

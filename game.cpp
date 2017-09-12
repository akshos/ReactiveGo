#include "board.h"

Board board;

int turn, row, col;

void switchPlayer()
{
	turn = (turn+1)%2;
	board.setCurrentPlayer(turn);
	cout << "Switched to player: " << turn+1 << endl;
}

void calculateCellPos(int x, int y)
{
	row = (int)( (_BOARD_HEIGHT - y) / _CELL_HEIGHT );
	col = (int)( x / _CELL_WIDTH );
	cout << "Cell position : ROW: " << row+1 << " COL: " << col+1 << endl;
}

void playerFillCell()
{
	int ret = board.playerFillCell( row, col, turn );
	if( ret != _OCCUPIED )
		switchPlayer();
}

void game()
{
	glClear(GL_COLOR_BUFFER_BIT);
	board.renderGrid();
	glFlush();
}

void checkExpand()
{
	board.checkAndExpand();
}

void onMouseClick( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN )
	{
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Mouse Position: X: " << x << " Y: " << y << endl;
		if( !board.isExpanding() )
		{
			calculateCellPos(x, y);
			playerFillCell();
		}
	}
}

int main(int argc, char **argv)
{
	initDisplay(argc, argv);
	board.init();
	glutDisplayFunc(game);
	glutIdleFunc(checkExpand);
	glutMouseFunc(onMouseClick);
	board.setPlayerColor( 0, _RED );
	board.setPlayerColor( 1, _BLUE );
	turn = 0;
	glutMainLoop();
	return 0;
}

/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : game
File Type :	source
*/

#include "board.h"

Board board;

int turn;
int tempRow, tempCol;

void switchPlayer()
{
	turn = (turn+1)%2;
	board.setCurrentPlayer(turn);
	cout << "Switched to player: " << turn+1 << endl;
}

void calculateCellPos(int x, int y, int &row, int &col)
{
	row = (int)( (_BOARD_HEIGHT - y) / _CELL_HEIGHT );
	col = (int)( x / _CELL_WIDTH );
}

void playerFillCell(int row, int col)
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
			int row, col;
			calculateCellPos(x, y, row, col);
			cout << "Cell position : ROW: " << row+1 << " COL: " << col+1 << endl;
			playerFillCell(row, col);
		}
	}
}

void onMouseMove( int x, int y )
{
	int newRow, newCol;
	calculateCellPos(x, y, newRow, newCol);
	if( (newRow != tempRow) || (newCol != tempCol) )
	{
		tempRow = newRow;
		tempCol = newCol;
		board.tempFillCell(tempRow, tempCol);
	}
}

int main(int argc, char **argv)
{
	initDisplay(argc, argv);
	board.init();
	glutDisplayFunc(game);
	glutIdleFunc(checkExpand);
	glutMouseFunc(onMouseClick);
	glutPassiveMotionFunc(onMouseMove);
	board.setPlayerColor( 0, _RED );
	board.setPlayerColor( 1, _BLUE );
	turn = 0;
	tempRow = tempCol = -1;
	glutMainLoop();
	return 0;
}

#include "board.h"


Board::Board()
{
	CELL *cell;
	int index = 0;
	for( int i = 0; i < _CELL_SPAN; i++ )
	{
		for( int j = 0; j < _CELL_SPAN; j++ )
		{
			cell = &cells[i][j];
			cell->color = _WHITE;
			cell->xcenter = cell->ycenter = 0;
			cell->count = 0;
			cell->occupied = false;
			cell->index = index++;
		}
	}
	cout << "Cell count : " << index << endl;
}

void Board::init()
{
	initBoard();
	initGrid();
}


void Board::initGrid()
{
	POINT start, end;
	LINE *line = gridLines;
	cout << "Initializing grid lines" << endl;
	//draw horizontal lines
	for( int y = _CELL_HEIGHT; y < _BOARD_HEIGHT; y += _CELL_HEIGHT )
	{
		line->start.x = 0; 			line->start.y = y;
		line->end.x = _BOARD_WIDTH;	line->end.y = y;
		line++;
	}
	//draw vertical lines
	for( int x = _CELL_WIDTH; x < _BOARD_WIDTH; x += _CELL_WIDTH )
	{
		line->start.x = x;	line->start.y = 0;
		line->end.x = x;	line->end.y = _BOARD_HEIGHT;
		line++;	
	}
}

void Board::drawGridLines()
{
	LINE *line = gridLines;
	int limit = (_CELL_SPAN * 2)-2;
	cout << "Drawing grid lines" << endl;
	for( int i = 0; i < limit; i++ )
	{
		drawLine( line->start, line->end, _BLACK, 5.0f );
		line++;
	}
	glutSwapBuffers();
}	

void BOARD::renderGrid()
{
	drawGridLines();
}

void BOARD::fillCell( int row, int col, COLOR color )
{
	CELL *cell = cells[row][col];
	if( cell->color == __WHITE )
	{
		activeCells.insertNode(row, col, cell->index);
		cell->color = color;
		cell->count = 1;
	}
	else if( cell->color == color )
	{
		cell->count += 1;
	}
	else
	{
		cout << "Cell occupied by other player" << endl;
	}
}
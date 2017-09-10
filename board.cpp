#include "board.h"

Board::Board()
{
	CELL *cell;
	int index = 0;
	for( int i = 0; i < _CELL_SPAN; i++ ) //initialize the cells matrix
	{
		for( int j = 0; j < _CELL_SPAN; j++ )
		{
			cell = &cells[i][j];
			cell->color = _WHITE;
			cell->xcenter = (_CELL_WIDTH * j) + _CELL_WIDTH_HALF;
			cell->ycenter = (_CELL_HEIGHT * i) + _CELL_HEIGHT_HALF;
			cell->count = 0;
			cell->occupied = false;
			cell->index = index++;
			cout << "Row: " << i << " Col: " << j << " Index: " << index << " X: " << cell->xcenter << " Y: " << cell->ycenter << endl;
		}
	}
	cout << "Cell count : " << index << endl;
}

void Board::init()
{
	initBoard();
	initGrid();
}

void Board::drawCellCount(int xcenter, int ycenter, int count)
{
	char ch = (char)((int)'0' + count);
	drawCharacter( xcenter, ycenter, _WHITE, ch );
}

/*calculate grid line coordinates and store for future referance (gridLines)*/
void Board::initGrid()
{
	POINT start, end;
	LINE *line = gridLines;
	cout << "Initializing grid lines" << endl;
	//calculate horizontal lines
	for( int y = _CELL_HEIGHT; y < _BOARD_HEIGHT; y += _CELL_HEIGHT )
	{
		line->start.x = 0; 			line->start.y = y;
		line->end.x = _BOARD_WIDTH;	line->end.y = y;
		line++;
	}
	//calculate vertical lines
	for( int x = _CELL_WIDTH; x < _BOARD_WIDTH; x += _CELL_WIDTH )
	{
		line->start.x = x;	line->start.y = 0;
		line->end.x = x;	line->end.y = _BOARD_HEIGHT;
		line++;	
	}
}

/*draw grid lines using coordinates present in previously defines array (gridLines)*/
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
	glFlush();
}

/*render occupied cells on the screen*/
void Board::drawActiveCells()
{
	NODE* currentNode =	activeCells.startSequential();
	CELL* currentCell;
	cout << "Drawing active cells: " << activeCells.getCount() << endl;
	while( currentNode != NULL )
	{
		currentCell = &cells[currentNode->row][currentNode->col];
		drawCircle(currentCell->xcenter, currentCell->ycenter, currentCell->color, _RADIUS);
		drawCellCount( currentCell->xcenter, currentCell->ycenter, currentCell->count );
		currentNode = activeCells.nextSequential();
	}
	glutSwapBuffers();
}

/*render the board grid on the screen*/
void Board::renderGrid() 
{
	drawGridLines();
	drawActiveCells();
}

int Board::fillCell( int row, int col, COLOR color )
{
	CELL *cell = &cells[row][col];
	if( cell->color == _WHITE ) //if the cell is unoccupied
	{
		activeCells.insertNode(row, col, cell->index); //add the cell to active list
		cell->color = color;
		cell->count = 1;
	}
	else if( cell->color == color ) //if the cell is occupied by the same color
	{
		cell->count += 1; //increase the count of the cell by 1
		checkMaxOccupied(row, col, cell);
	}
	else //the cell is occupied by color of other player
	{
		cout << "Cell occupied by other player" << endl;
		return _OCCUPIED;
	}
	glutPostRedisplay();
}

void Board::checkMaxOccupied(int row, int col, CELL *currentCell)
{
}
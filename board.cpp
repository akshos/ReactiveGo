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

void Board::drawCharacter( int x, int y, char ch )
{
	glRasterPos2i(x, y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch);
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
	cout << "Active cells: " << activeCells.getCount() << endl;
	while( currentNode != NULL )
	{
		currentCell = &cells[currentNode->row][currentNode->col];
		drawCircle(currentCell->xcenter, currentCell->ycenter, currentCell->color, _RADIUS);
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

void Board::fillCell( int row, int col, COLOR color )
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
	}
	else //the cell is occupied by color of other player
	{
		cout << "Cell occupied by other player" << endl;
	}
	glutPostRedisplay();
}
#include "board.h"

Board::Board()
{
	CELL *cell;
	int index = 0;
	player[0].color = _WHITE;
	player[1].color = _WHITE;
	player[0].points = 0;
	player[0].points = 0;
	for( int i = 0; i < _CELL_SPAN; i++ ) //initialize the cells matrix
	{
		for( int j = 0; j < _CELL_SPAN; j++ )
		{
			cell = &cells[i][j];
			cell->color = _WHITE;
			cell->xcenter = (_CELL_WIDTH * j) + _CELL_WIDTH_HALF;
			cell->ycenter = (_CELL_HEIGHT * i) + _CELL_HEIGHT_HALF;
			cell->count = 0;
			cell->player = -1;
			cell->occupied = false;
			cell->expand = false;
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

void Board::setPlayerColor( unsigned short turn, COLOR color )
{
	player[turn].color = color;
}

void Board::setCurrentPlayer( unsigned short turn )
{
	this->turn = turn;
}

void Board::drawCellCount(int xcenter, int ycenter, int count)
{
	char ch = (char)((int)'0' + count);
	drawCharacter( xcenter, ycenter, _WHITE, ch );
}

bool Board::isExpanding()
{
	return !expandCells.isEmpty();
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
		drawLine( line->start, line->end, _BLACK, 1.0f );
		line++;
	}
	glutSwapBuffers();
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

int Board::playerFillCell( int row, int col, int turn )
{

	int flag = fillCell(row, col, player[turn].color);
	glutPostRedisplay();
	return flag;
}

int Board::fillCell( int row, int col, COLOR color, bool takeOver)
{
	CELL *cell = &cells[row][col];
	if( cell->occupied == false ) //if the cell is unoccupied
	{
		activeCells.insertNode(row, col, cell->index); //add the cell to active list
		cell->color = color;
		cell->count = 1;
		cell->player = turn;
		cell->occupied = true;
	}
	else if( cell->color == color ) //if the cell is occupied by the same color
	{
		cell->count += 1; //increase the count of the cell by 1
		checkMaxOccupied(row, col, cell);
	}
	else if( takeOver == true )
	{
		cell->color = color;
		cell->count += 1;
		cell->player = turn;
		checkMaxOccupied(row, col, cell);
	}
	else //the cell is occupied by color of other player
	{
		cout << "Cell occupied by other player" << endl;
		return _OCCUPIED;
	}
	
}

void Board::unoccupyCell( CELL *cell )
{
	cell->occupied = false;
	cell->count = 0;
	cell->player = -1;
	cell->color = _WHITE;
	cout << "Deleting node " << endl;
	activeCells.deleteNode(cell->index);
	cout << "Node deleted " << endl;
}

void Board::checkMaxOccupied(int row, int col, CELL *currentCell)
{
	unsigned short position;
	bool corner = false;
	//determine the position of the cell w:r:t the edges
	if( row == 0 )
		position = _BOTTOM_EDGE;
	else if( row == _CELL_SPAN-1 )
		position = _TOP_EDGE;
	else
		position = _MIDDLE;
	if( col == 0 )
	{
		if( position != 0 )
			corner = true;
		position += _LEFT_EDGE;
	}
	else if( col == _CELL_SPAN-1 )
	{
		if( position != 0 )
			corner = true;
		position += _RIGHT_EDGE;
	}
	else
		position += _MIDDLE;
	
	if( position != _MIDDLE )
	{
		if( corner && (currentCell->count == 2) )
		{
			currentCell->expand = true;
			expandCells.insertNode(row, col, currentCell->index);
		}
		else if( currentCell->count == 3 )
		{
			currentCell->expand = true;
			expandCells.insertNode(row, col, currentCell->index);
		}
	}
	else if( currentCell->count == 4 )
	{
		currentCell->expand = true;
		expandCells.insertNode(row, col, currentCell->index);
	}
}
			
void Board::checkAndExpand()
{
	if( expandCells.isEmpty() )
		return;
	unsigned short up, down, left, right, position, row, col;
	up = down = left = right = 0;
	NODE *current = expandCells.removeFront();
	cout << "Expanding cell: " << current->index << " Row: " << current->row << " Col: " << current->col << endl;
	row = current->row;
	col = current->col;
	CELL *cell = &cells[row][col];
	position = cell->position;
	if( position ^ _LEFT_EDGE ) //not on left edge
	{
		left = _STEP;
		fillCell(row, col-1, cell->color, true);
	}
	if( position ^ _RIGHT_EDGE ) //not on right edge
	{
		right = _STEP;
		fillCell(row, col+1, cell->color, true);
	}
	if( position ^ _TOP_EDGE ) //not on top edge
	{
		up = _STEP;
		fillCell(row+1, col, cell->color, true);
	}
	if( position ^ _BOTTOM_EDGE ) //not on bottom edge
	{
		down = _STEP;
		fillCell(row-1, col, cell->color, true);
	}
	cout << "Unoccupying cell: " << current->index << endl;
	unoccupyCell(cell);
	delete current;
	glutPostRedisplay();
}







/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : board
File Type : source
*/

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
			getPosition(i, j, cell);
			cout << "Row: " << i << " Col: " << j << " Index: " << index << " X: " << cell->xcenter << " Y: " << cell->ycenter << endl;
		}
	}
	cout << "Cell count : " << index << endl;
}

//calculate the cell position on the board and store
void Board::getPosition(int row, int col, CELL *currentCell)
{
	unsigned short position;
	bool corner = false;
	//determine the position of the cell w:r:t the edges
	if( row == 0 ) //cell is on the bottom edge
		position = _BOTTOM_EDGE;
	else if( row == _CELL_SPAN-1 ) //cell is on the top edge
		position = _TOP_EDGE;
	else
		position = _MIDDLE; //cell is in between top and bottom
	if( col == 0 ) //cell is on the left edge
	{
		if( position != 0 ) //if cell is already on top or bottom edge
			corner = true; //cell is in a corver (top left or bottom left)
		position += _LEFT_EDGE;
	}
	else if( col == _CELL_SPAN-1 ) //cell is on the right edge
	{
		if( position != 0 ) //if cell is already on top or bottom edge
			corner = true; //cell is in a corver (top right or bottom right)
	}
	else //the cell is between left and right edges
		position += _MIDDLE;
	currentCell->corner = corner; //store the calculated positions
	currentCell->position = position;
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

//draw the cell capacity as character(number) at the center of the cell
void Board::drawCellCount(int xcenter, int ycenter, int count)
{
	char ch = (char)((int)'0' + count);
	drawCharacter( xcenter, ycenter, _WHITE, ch );
}

//returns true if there are pending cells to be expanded
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

void Board::drawTempCell()
{
	if( tempCell != NULL )
	{
		drawCircle(tempCell->xcenter, tempCell->ycenter, player[turn].color, _RADIUS);
	}
	glutSwapBuffers();
}

/*render the board grid on the screen*/
void Board::renderGrid() 
{
	drawGridLines();
	drawActiveCells();
	drawTempCell();
}

//the cell is being filled by the player (due to mouse click)
int Board::playerFillCell( int row, int col, int turn )
{

	int flag = fillCell(row, col, player[turn].color);
	glutPostRedisplay();
	tempCell = NULL;
	return flag;
}

//fill the cell at specified row and col with the specified color
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
		checkMaxOccupied(row, col, cell); //check is cell capacity is reached
	}
	else if( takeOver == true )
	{
		cell->color = color;
		cell->count += 1;
		cell->player = turn;
		checkMaxOccupied(row, col, cell); //check is cell capacity is reached
	}
	else //the cell is occupied by color of other player
	{
		cout << "Cell occupied by other player" << endl;
		return _OCCUPIED;
	}
	
}

//remove the cell from the activeCells list and reset its parameters
void Board::unoccupyCell( CELL *cell )
{
	cell->occupied = false;
	cell->count = 0;
	cell->player = -1;
	cell->color = _WHITE;
	//cout << "Deleting node " << endl;
	activeCells.deleteNode(cell->index); //delete from the list
	//cout << "Node deleted " << endl;
}

//check if the cell capacity is reached based on its position and set to expand
void Board::checkMaxOccupied(int row, int col, CELL *currentCell)
{
	if( currentCell->position != _MIDDLE ) //if the cell is not in the middle
	{
		if( currentCell->corner && (currentCell->count == 2) ) //if the cell is at a corner
		{
			currentCell->expand = true; //set the cell to be expanded
			expandCells.insertNode(row, col, currentCell->index);
		}
		else if( currentCell->count == 3 ) //if the cell is at an edge
		{
			currentCell->expand = true; //set the cell to be expanded
			expandCells.insertNode(row, col, currentCell->index);
		}
	}
	else if( currentCell->count == 4 ) //if the cell is somewhere in middle
	{
		currentCell->expand = true; //set the cell to be expanded
		expandCells.insertNode(row, col, currentCell->index);
	}
}


//check if there are cells to be expanded			
void Board::checkAndExpand()
{
	if( expandCells.isEmpty() ) //no cell pending to be expanded
		return;
	unsigned short position, row, col;
	NODE *current = expandCells.removeFront(); //retrieve the first cell to expand and remove from list
	row = current->row;
	col = current->col;
	cout << "Expanding cell: " << current->index << " Row: " << row << " Col: " << col << endl;
	CELL *cell = &cells[row][col];
	position = cell->position; 
	//expand to adjacents cells based on position on board
	if( !(position & _LEFT_EDGE) ) //not on left edge
	{
		fillCell(row, col-1, cell->color, true); //expand to left cell
	}
	if( !(position & _RIGHT_EDGE) ) //not on right edge
	{
		fillCell(row, col+1, cell->color, true); //expand to right cell
	}
	if( !(position & _TOP_EDGE) ) //not on top edge
	{
		fillCell(row+1, col, cell->color, true); //expand to top cell
	}
	if( !(position & _BOTTOM_EDGE) ) //not on bottom edge
	{
		fillCell(row-1, col, cell->color, true); //expand to bottom cell
	}
	cout << "Unoccupying cell: " << current->index << endl;
	unoccupyCell(cell); //unoccupy the expanded cell
	delete current; 
	glutPostRedisplay(); //call to render the board
}

void Board::tempFillCell( int row, int col )
{
	CELL *cell = &cells[row][col];
	if( !cell->occupied )
	{
		tempCell = cell;
	}
	else
	{
		tempCell	 = NULL;
	}
	glutPostRedisplay();
}











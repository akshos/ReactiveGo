/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : board
File Type : header
*/

#include "graphicsFunctions.h"
#include "list.h"
#include <unistd.h>

#define _OCCUPIED 1
#define _TOP_EDGE 0x8
#define _BOTTOM_EDGE 0x4
#define _LEFT_EDGE 0x2
#define _RIGHT_EDGE 0x1
#define _TOP_LEFT 0xa
#define _TOP_RIGHT 0x9
#define _BOTTOM_LEFT 0x6
#define _BOTTOM_RIGHT 0x5
#define _MIDDLE 0x0

#define _BOARD_HEIGHT 800
#define _BOARD_WIDTH 800
#define _CELL_SPAN 10

const unsigned short _CELL_COUNT = _CELL_SPAN * _CELL_SPAN;
const unsigned short _CELL_WIDTH = _BOARD_WIDTH / _CELL_SPAN;
const unsigned short _CELL_HEIGHT = _BOARD_HEIGHT / _CELL_SPAN;
const unsigned short _CELL_HEIGHT_HALF = _CELL_HEIGHT / 2;
const unsigned short _CELL_WIDTH_HALF = _CELL_WIDTH / 2;
const unsigned short _RADIUS = _CELL_WIDTH_HALF - 10;
const unsigned short _STEP = 5;

struct CELL
{
	int xcenter, ycenter, index;
	unsigned short count;
	unsigned short position;
	short player;
	bool occupied, expand, corner;
	COLOR color;
};

struct PLAYER
{
	COLOR color;
	unsigned short points;
};

class Board
{
private :
	CELL cells[_CELL_SPAN][_CELL_SPAN];
	LINE gridLines[_CELL_SPAN*2];
	List activeCells;
	List expandCells;
	unsigned short turn;
	PLAYER player[2];
	void initGrid(); /*calculate grid line coordinates and store for future referance (gridLines)*/
	void getPosition(int row, int col, CELL *currentCell); //calculate the cell position on the board and store
	void drawGridLines(); /*draw grid lines using coordinates present in previously defines array (gridLines)*/
	void drawActiveCells(); /*render occupied cells on the screen*/
	void drawCellCount( int xcenter, int ycenter, int count); //draw the cell capacity as character(number) at the center of the cell
	void checkMaxOccupied(int row, int col, CELL *currentCell); //check if the cell capacity is reached based on its position and set to expand
	int fillCell( int row, int col, COLOR color, bool takeOver = false ); //fill the cell at specified row and col with the specified color
	void unoccupyCell( CELL *cell ); //remove the cell from the activeCells list and reset its parameters
public :
	Board();
	void init();
	void renderGrid(); /*render the board grid on the screen*/
	bool isExpanding(); //returns true if there are pending cells to be expanded
	void checkAndExpand(); //check if there are cells to be expanded
	void setPlayerColor( unsigned short turn, COLOR color );
	void setCurrentPlayer( unsigned short turn );
	int playerFillCell( int row, int col, int turn ); //the cell is being filled by the player (due to mouse click)
};
	
	

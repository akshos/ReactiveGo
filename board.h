#include "graphicsFunctions.h"
#include <iostream>

using namespace std;

#define _BOARD_HEIGHT 800
#define _BOARD_WIDTH 800
#define _CELL_SPAN 10

const unsigned short _CELL_COUNT = _CELL_SPAN * _CELL_SPAN;
const unsigned short _CELL_WIDTH = _BOARD_WIDTH / _CELL_SPAN;
const unsigned short _CELL_HEIGHT = _BOARD_HEIGHT / _CELL_SPAN;
const unsigned short _CELL_HEIGHT_HALF = _CELL_HEIGHT / 2;
const unsigned short _CELL_WIDTH_HALF = _CELL_WIDTH / 2;
const unsigned short _RADIUS = _CELL_WIDTH_HALF - 10;

struct CELL
{
	int xcenter, ycenter;
	unsigned short count;
	bool occupied;
	COLOR color;
};

class Board
{
private :
	CELL cells[_CELL_SPAN][_CELL_SPAN];
	LINE gridLines[_CELL_SPAN*2];
	void initGrid();
public :
	Board();
	void init();
	void drawGrid();
};
	
	

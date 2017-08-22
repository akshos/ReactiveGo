#define _BOARD_HEIGHT 180
#define _BOARD_WIDTH 180
#define _CELL_COUNT 9

const unsigned short _CELL_WIDTH = _BOARD_WIDTH / _CELL_COUNT;
const unsigned short _CELL_HEIGHT = _BOARD_HEIGHT / _CELL_COUNT;
const unsigned short _CELL_HEIGHT_HALF = _CELL_HEIGHT / 2;
const unsigned short _CELL_WIDTH_HALF = _CELL_WIDTH / 2;

struct COLOR
{
	unsigned short red, green, blue;
};

const COLOR _BLACK = { 0, 0, 0 };
const COLOR _WHITE = { 1, 1, 1 };

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
	CELL cells[_CELL_COUNT][_CELL_COUNT];
public :
	Board();
};
	
	

#include "board.h"


Board::Board()
{
	for( int i = 0; i < _CELL_COUNT; i++ )
	{
		for( int j = 0; j < _CELL_COUNT; j++ )
		{
			cells[i][j] = _WHITE;
		}
	}
}

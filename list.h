#include <stdlib.h>

struct NODE
{
	int index;
	int row;
	int col;
	NODE *next;
	NODE *prev;
};

class List
{
private:
	NODE *head;
	NODE *tail;
	int count;
	NODE *currentNode;
	NODE* createNode(int row, int col, int index );
public:
	List();
	bool isEmpty();
	void insertNode( int row, int col, int index );
	void deleteNode( int index );
	NODE* getNode( int index );
	NODE* startSequential();
	NODE* nextSequential();
	int getCount();
};

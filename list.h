
struct NODE
{
	int index;
	int row;
	int col;
	NODE *next;
	NODE *prev;
};

class LIST
{
private:
	NODE *head;
	NODE *tail;
	int count;
	LIST* createNode();
public:
	LIST();
	bool isEmpty();
	void insertNode( int row, int col, int indes );
	void deleteNode( int index );
	NODE* getNode( int index );
	int getCount();
}

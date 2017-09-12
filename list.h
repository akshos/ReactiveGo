/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : list
File Type : header
*/

#include <stdlib.h>

/*
structure representing a node
contains the index, row and column of cells
*/
struct NODE
{
	int index;
	int row;
	int col;
	NODE *next;
	NODE *prev;
};

/*class to encapsulate a linked list and associated methods*/
class List
{
private:
	NODE *head;
	NODE *tail;
	int count;
	NODE* currentNode;
	NODE* createNode(int row, int col, int index ); /*returns a newely created node with values given in parameters*/
public:
	List();
	bool isEmpty(); /*returns true if the list is empty*/
	void insertNode( int row, int col, int index ); /*inserts a new node at the back of the list*/
	void deleteNode( int index ); /*delete a node(identified by index) from the list*/
	NODE* getNode( int index ); /*return the node identified by index*/
	NODE* startSequential(); /*sets the currentNode to the head and returns the first node*/
	NODE* nextSequential(); /*advances the currentNode and returns*/
	NODE* removeFront(); /*return the first node in the list while simultaneously deleting it*/
	int getCount(); /*returns the number of nodes in the list*/
}; 

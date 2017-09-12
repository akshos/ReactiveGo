/*
AUTHORS : 
	Abhishek Suresh (202)
	Akshay Venugopal(207)
	Priyanka Rajeev (244)
	Rachna Ramesh	(246)
Type : Computer Graphics Assignment
Program Name : Reactive GO
File Name : list
File Type : source
*/

#include "list.h"

List::List()
{
	head = tail = NULL;
	count = 0;
}

/*returns a newely created node with values given in parameters*/
NODE* List::createNode(int row, int col, int index )
{
	NODE *temp = new NODE;
	temp->index = index;
	temp->row = row;
	temp->col = col;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

/*inserts a new node at the back of the list*/
void List::insertNode( int row, int col, int index )
{
	NODE *newNode = createNode(row, col, index); //create a new node
	newNode->prev = tail;
	if( head == NULL ) //if the list is empty
	{
		head = newNode;
	}
	else
	{
		tail->next = newNode;
	}
	tail = newNode;
	count++;
}

/*delete a node(identified by index) from the list*/
void List::deleteNode( int index )
{
	NODE *temp = head;
	while( temp != NULL ) //search the list for node with index
	{
		if( temp->index == index ) //if found then delete
		{
			if( temp->prev != NULL )
				(temp->prev)->next = temp->next;
			if( temp->next != NULL )
				(temp->next)->prev = temp->prev;
			if( temp == head )
				head = temp->next;
			if( temp == tail )
				tail = temp->prev;
			delete temp;
			count--;
			return;
		}
		temp = temp->next;
	}
}

/*return the node identified by index*/
NODE* List::getNode( int index )
{
	NODE *temp = head;
	while( temp != NULL ) //search the list for node with index
	{
		if( temp->index == index ) //if found return the node
		{
			return temp;
		}
	}
	return NULL;
}

/*returns true if the list is empty*/
bool List::isEmpty()
{
	if( head == NULL )
		return true;
	return false;
}

/*returns the number of nodes in the list*/
int List::getCount()
{
	return count;
}

/*sets the currentNode to the head and returns the first node*/
NODE* List::startSequential()
{
	currentNode = head;
	return currentNode;
}

/*advances the currentNode and returns*/
NODE* List::nextSequential()
{
	if(currentNode != NULL) //if not null then advance
		currentNode = currentNode->next;
	return currentNode;
}

/*return the first node in the list while simultaneously deleting it*/
NODE* List::removeFront()
{
	NODE* tmp = head;
	if( head != NULL )
	{
		head = head->next;
		if( head != NULL )
			head->prev = NULL;
	}
	return tmp;
}

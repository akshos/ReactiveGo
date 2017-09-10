#include "list.h"

List::List()
{
	head = tail = NULL;
	count = 0;
}

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

void List::insertNode( int row, int col, int index )
{
	NODE *newNode = createNode(row, col, index);
	newNode->prev = tail;
	if( head == NULL )
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

void List::deleteNode( int index )
{
	NODE *temp = head;
	while( temp != NULL )
	{
		if( temp->index == index )
		{
			(temp->prev)->next = temp->next;
			(temp->next)->prev = temp->prev;
			if( temp == head )
				head = temp->next;
			if( temp == tail )
				tail = temp->prev;
			delete temp;
			count--;
		}
	}
}

NODE* List::getNode( int index )
{
	NODE *temp = head;
	while( temp != NULL )
	{
		if( temp->index == index )
		{
			return temp;
		}
	}
}

bool List::isEmpty()
{
	if( head == NULL )
		return true;
	return false;
}

int List::getCount()
{
	return count;
}

NODE* List::startSequential()
{
	currentNode = head;
	return currentNode;
}

NODE* List::nextSequential()
{
	if(currentNode != NULL)
		currentNode = currentNode->next;
	return currentNode;
}
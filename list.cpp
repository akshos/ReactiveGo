#include "list.h"

LIST::LIST()
{
	head = tail = NULL;
	count = 0;
}

NODE* LIST::createNode(int row, int col, int index )
{
	NODE *temp = new NODE;
	temp->index = index;
	temp->row = row;
	temp->col = col;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void LIST::insertNode( int row, int col, int index )
{
	NODE *newNode = createNode(row, col, index);
	newNode->prev = tail;
	if( head == NULL )
	{
		head = newNode;
	}
	tail = newNode;
	count++;
}

void LIST::deleteNode( int index )
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
			del temp;
			count--;
		}
	}
}

NODE* LIST::getNode( int index )
{
	NODE *temp = head;
	while( temp != NULL )
	{
		if( temp->index == inex )
		{
			return temp;
		}
	}
}

bool LIST::isEmpty()
{
	if( head == NULL )
		return true;
	return false;
}

int LIST::getCount()
{
	return count;
}
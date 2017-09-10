#include <iostream>
#include "list.h"

using namespace std;

int main()
{
	List list;
	NODE *temp;
	char choice;
	int row, col, index;
	do
	{
		cout << "1. Insert 2. Delete 3. Display 4.Exit" << endl;
		cout << "Option: " ;
		cin >> choice;
		switch( choice )
		{
			case '1':
				cout << "Row Col and Index: " ;
				cin >> row >> col >> index;
				list.insertNode(row, col, index);
				break;
			case '2':
				cout << "Index: ";
				cin >> index;
				list.deleteNode(index);
				break;
			case '3':
				temp = list.startSequential();
				while( temp != NULL )
				{
					cout << "Index: " << temp->index << " Row: " << temp->row << " Col: " << temp->col << endl;
					temp = list.nextSequential();
				}
				break;
			case '4':
				break;
			default : cout << "\nEnter a valid option number" << endl;
		}
	}while(choice != '4' );
	return 0;
}

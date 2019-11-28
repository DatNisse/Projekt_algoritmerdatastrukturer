// StorProjekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "DataClass.h"

using namespace std;

void printMenu()
{

	system("CLS");
	cout << "Possible choices in this program:" << endl;
	cout << "1: Avreage value." << endl;
	cout << "2: Sorting by highest." << endl;
	cout << "3: Sorting by lowest." << endl;
	cout << "4: Exit program." << endl << endl;

	cout << "Ditt val: ";
}


int main()
{
	cout << "start" << endl;
	DC::DataClass dataClass;
	int choice;
	
	do 
	{
		printMenu();
		cin >> choice;
		
		switch (int(choice))
		{
			case 1:
			{
				cout << "test" << endl;
				break;
			}

			case 2:
			{
				cout << "test" << endl;
				break;
			}

			case 3:
			{
				cout << "test" << endl;
				break;
			}

			case 4:
			{
				cout << "Exiting...";
				break;
			}

			default:
				cout << "Invalid Input" << endl;

		}
	} while (choice != 4);

}
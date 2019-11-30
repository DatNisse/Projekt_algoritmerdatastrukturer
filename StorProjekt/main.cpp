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
	int date[3] = {-1, -1, -1};
	string t1, t2, t3;
	
	
	do 
	{
		printMenu();
		cin >> choice;
		
		switch (int(choice))
		{
			case 1:
			{
				cout << "Please specify day for value: (yyyy-mm-dd)" << endl;
				cin >> t1;
				cout << "Please specify what type of value your looking for: (mold = m, temp = t, humidity = h )" << endl;
				cin >> t2;
				cout << "Is it the value of the inside sensor you are looking for? (y/n)";
				cin >> t3;
				if (date[0] == -1 || date[1] == -1 || date[2] == -1)
				{
					cout << "Invalid date has been input!" << endl;
				}
				else if (t3 == "y")
				{
					dataClass.fixDate(t1, date);
					dataClass.avreage(true, char(t2[0]), date);
				}

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
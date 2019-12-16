// StorProjekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "DataClass.h"

using namespace std;

	/*
	Used for printing UI for user.
	*/
void printMenu()
{

	system("CLS"); //clears any previus entries
	cout << "Possible choices in this program:" << endl;
	cout << "1: Avreage value." << endl;
	cout << "2: Sorting by highest." << endl;
	cout << "3: Sorting by lowest." << endl;
	cout << "4: Winter/Autum." << endl;
	cout << "5: Print datalist" << endl;
	cout << "6: Exit program." << endl << endl;

	cout << "Ditt val: ";
}


int main()
{
	cout << "start" << endl;
	DC::DataClass dataClass; //calls upon constructor for dataClass
	int choice;
	int dateInput;
	bool inside;
	string t1, t2, t3;
	
	
	do 
	{
		printMenu(); //prints menue when loading is complete
		cin >> choice;
		
		switch (int(choice))
		{
			case 1: //Avreage value.
			{
				cout << "Please specify day for value: (yyyy-mm-dd)" << endl;
				cin >> t1;
				cout << "Please specify what type of value your looking for: (mold = m, temp = t, humidity = h )" << endl;
				cin >> t2;
				cout << "Is it the value of the inside sensor you are looking for? (y/n)";
				cin >> t3;
				//formats date
				dateInput = stoi(t1.substr(0, 4))*10000;
				dateInput += stoi(t1.substr(5, 2))*100;
				dateInput += stoi(t1.substr(8, 2));
				//dataClass.fixDate(t1, &dateInput);
				
				//formats bool
				if (t3 == "y")
				{
					inside = true;
				}
				else 
				{
					inside = false;
				}
				cout << dataClass.getAvreage(inside, char(t2[0]), dateInput) << endl << "Press any key to continue." << endl; //calls funtion to retrive specified value
				cin >> t1;

				break;
			}

			case 2: //Sorting by highest.
			{
				cout << "Please specify what type of maximum value your looking for: (mold = m, temp = t, humidity = h )" << endl;
				cin >> t2;
				cout << "Is it the value of the inside sensor you are looking for? (y/n)" << endl;
				cin >> t3;
				if (t3 == "y")
				{
					inside = true;
				}
				else
				{
					inside = false;
				}
				cout << dataClass.getMax(inside, char(t2[0])) << endl << "Press any key to continue." << endl;
				cin >> t1;

				break;
			}

			case 3: //Sorting by lowest.
			{
				cout << "Please specify what type of minimum value your looking for: (mold = m, temp = t, humidity = h )" << endl;
				cin >> t2;
				cout << "Is it the value of the inside sensor you are looking for? (y/n)" << endl;
				cin >> t3;
				if (t3 == "y")
				{
					inside = true;
				}
				else
				{
					inside = false;
				}
				cout << dataClass.getMin(inside, char(t2[0])) << endl << "Press any key to continue." << endl;
				cin >> t1;

				break;
			}

			case 4: //Winter/Autum.
			{
				cout << "Is it when winter starts that you are looking for? (y/n)" << endl;
				cin >> t3;
				if (t3 == "y")
				{
					inside = true;
				}
				else 
				{
					inside = false;
				}
				cout << dataClass.getWintAut(inside) << endl << "Press any key to continue." << endl;
				cin >> t1;

				break;
			}

			case 5: //print list
			{
				cout << "Printing list:" << endl;
				dataClass.printAll();
				cout << endl << "Press any key to continue." << endl;
				cin >> t1;
				break;
			}
			
			case 6: //Exit program.
			{
				cout << "Exiting...";
				break;
			}
			default:
				cout << "Invalid Input" << endl;

		}
	} while (choice != 6); //loop ends when quit is pressed

}
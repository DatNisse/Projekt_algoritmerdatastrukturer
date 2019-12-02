#include "DataClass.h"
#include "DataCollector.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

using namespace DC;
using namespace Collector;





double DC::DataClass::calcAvreage(bool inside, int type, int index[2])
{
	double total = 0;
	int counter = 0;
	if (index[0] != -1) //if index is -1 somethings wrong
	{
		if (type == 1)
		{
			for (int i = index[1]; i < index[0]; i++)
			{
				if (coll.listDataDetail.at(i).inside == inside)
				{
					total += coll.listDataDetail.at(i).mogel;
					counter++; //for each element added to total, add 1 to counter;
				}
			}
		}
		else if (type == 2)
		{
			for (int i = index[1]; i < index[0]; i++)
			{
				if (coll.listDataDetail.at(i).inside == inside)
				{
					total += coll.listDataDetail.at(i).temp;
					counter++;
				}
			}
		}
		else if (type == 3)
		{
			for (int i = index[1]; i < index[0]; i++)
			{
				if (coll.listDataDetail.at(i).inside == inside)
				{
					total += coll.listDataDetail.at(i).humid;
					counter++;
				}
			}
		}
		return total / counter;
	}

	return -1;
}

int DC::DataClass::searchDate(bool inside, int day)
{
	int tDay[3];

	tDay[0] = int(day / 10000);
	tDay[1] = (int(day/100) * 100 - int(day / 10000) * 10000) / 100;
	tDay[2] = day - int(day / 100) * 100;

	for (int i = 0; i < dataVector.size(); i++)
	{
		if (dataVector.at(i).day[0] == tDay[0] && dataVector.at(i).day[1] == tDay[1] && dataVector.at(i).day[2] == tDay[2] && dataVector.at(i).inside == inside)
		{
			return i;
		}
	}

	return -1;
}

int DC::DataClass::searchLow(bool inside, int start)
{
	
	for (int i = start; i < dataVector.size(); i++)
	{
		if (dataVector.at(i).inside == inside)
		{
			return i;
		}
	}

	return -1;
}

int DC::DataClass::searchHigh(bool inside, int start)
{
	for (int i = start; i > 0 ; i--)
	{
		if (dataVector.at(i).inside == inside)
		{
			return i;
		}
	}

	return -1;
}

void DC::DataClass::swap(dataDay *a, dataDay *b)
{
	dataDay t = *a;
	*a = *b;
	*b = t;
}

int DC::DataClass::partition(int low, int high, char type)
{
	dataDay pivot = dataVector.at(high);
	int i = (low - 1); // Index of smaller element  

	if (type == 'm')
	{
		// If current element is smaller than the pivot  
		for (int j = low; j <= high - 1; j++)
		{
			if (dataVector[j].avgM < pivot.avgM)
			{
				i++; // increment index of smaller element  
				swap(&dataVector[i], &dataVector[j]);
			}
		}
	}
	else if (type == 'h')
	{
		// If current element is smaller than the pivot  
		for (int j = low; j <= high - 1; j++)
		{
			if (dataVector[j].avgH < pivot.avgH)
			{
				i++; // increment index of smaller element  
				swap(&dataVector[i], &dataVector[j]);
			}
		}
	}
	else if (type == 't')
	{
		// If current element is smaller than the pivot  
		for (int j = low; j <= high - 1; j++)
		{
			if (dataVector[j].avgT < pivot.avgT)
			{
				i++; // increment index of smaller element  
				swap(&dataVector[i], &dataVector[j]);
			}
		}
	}
	
	swap(&dataVector[i + 1], &dataVector[high]);
	return (i + 1);
	
	//return 0;
}

void DC::DataClass::listSort(char type, int low, int high) //sorts list depending on requested value
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(low, high, type);

		// Separately sort elements before  
		// partition and after partition  
		listSort(low, pi - 1, type);
		listSort(pi + 1, high, type);
	}
}

void DC::DataClass::bubbleSort(int high, char type)
{
	if (type == 'm')
	{
		for (int i = 0; i < high - 1; i++)
		{
			// Last i elements are already in place   
			for (int j = 0; j < high - i - 1; j++)
			{
				if (dataVector[j].avgM > dataVector[j + 1].avgM)
				{
					swap(&dataVector[j], &dataVector[j + 1]);
				}
			}
		}
	}
	else if (type == 'h')
	{
		for (int i = 0; i < high - 1; i++)
		{
			// Last i elements are already in place   
			for (int j = 0; j < high - i - 1; j++)
			{
				if (dataVector[j].avgH > dataVector[j + 1].avgH)
				{
					swap(&dataVector[j], &dataVector[j + 1]);
				}
			}
		}
	}
	else if (type == 't')
	{
		for (int i = 0; i < high - 1; i++)
		{
			// Last i elements are already in place   
			for (int j = 0; j < high - i - 1; j++)
			{
				if (dataVector[j].avgT > dataVector[j + 1].avgT)
				{
					swap(&dataVector[j], &dataVector[j + 1]);
				}
			}
		}
	}			
	else if (type == 'd')
	{
		for (int n = 3; n > 0; n--)
		{
			for (int i = 0; i < high - 1; i++)
			{
				// Last i elements are already in place   
				for (int j = 0; j < high - i - 1; j++)
				{
					if (dataVector[j].day[n] > dataVector[j + 1].day[n])
					{
						swap(&dataVector[j], &dataVector[j + 1]);
					}
				}
			}
		}		
	}
}





// Driver program to test above functions 
/*int main()
{
	int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
	int n = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, n);
	printf("Sorted array : \n");
	printArray(arr, n);
	return 0;
}*/


void DataClass::getData(bool inside)
{
	dataDay d;
	
	int date[3], index[2] = {0, 0}; //date that is added for reference
	

	for (int i = 0; i < 3; i++) //sets first date
	{
		date[i] = coll.listDataDetail.at(0).day[i];
	}
	d.inside = inside;
	do
	{
		index[0] = coll.getIndex(date, index[1]); //retrives scope of data from specifik date

		if (index[0] != -1)
		{
			d.day[0] = date[0];
			d.day[1] = date[1];
			d.day[2] = date[2];
		}
		
		d.avgM = calcAvreage(inside, 1, index);
		d.avgT = calcAvreage(inside, 2, index);
		d.avgH = calcAvreage(inside, 3, index);
		index[1] = index[0];

		

		dataVector.push_back(d);
		if (index[0] != coll.listDataDetail.size())
		{
			for (int i = 0; i < 3; i++)
			{
				date[i] = coll.listDataDetail.at(index[0] + 1).day[i]; //sets start date for next day
			}
		}
		else
		{
			index[0] = -1;
		}


	} while (index[0] != -1);

	

}





void DC::DataClass::fixDate(string date, int a[3])
{
	
	if (date.length() == 10)
	{
		int temp;
		temp = stoi(date.substr(0, 4));
		a[0] = temp;
		temp = stoi(date.substr(5, 2));
		a[1] = temp;
		temp = stoi(date.substr(8, 2));
		a[2] = temp;
	}

	return;
}

string DC::DataClass::avreage(bool inside, char type, int date)
{
	size_t index = searchDate(inside, date);
	string s;
	if (index != -1)
	{
		if (inside)
		{
			s = " The avreage inside ";
		}
		else
		{
			s = "The avreage outside ";
		}
		if (type == 't')
		{
			s += "temperature is ";
			s += to_string(dataVector.at(index).avgT);
		}
		else if (type == 'h')
		{
			s += "humidity is ";
			s += to_string(dataVector.at(index).avgH);
		}
		else if (type == 'm')
		{
			s += "risk for mold is ";
			s += to_string(dataVector.at(index).avgM);
		}

		return s;
	}
	return " no data found exists!";
}

string DC::DataClass::getMax(bool inside, char type)
{
	
	string s;
	int n = dataVector.size();
	//listSort(type, 0, n - 1);
	bubbleSort(n, type);
	int index = searchHigh(inside, n - 1);
	
	if (inside)
	{
		s = "The highest inside ";
	}
	else
	{
		s = "The highest outside ";
	}
	if (type == 't')
	{
		
		s += "temperature was on ";
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		s += " with a avreage temperature of: ";
		s += to_string(dataVector.at(index).avgT);
	}
	else if (type == 'h')
	{
		s += "humidity is ";
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		s += " with a avreage humidity of: ";
		s += to_string(dataVector.at(index).avgH);
	}
	else if (type == 'm')
	{
		s += "risk for mold is ";
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		s += " with a avreage mold risk of: ";
		s += to_string(dataVector.at(index).avgM);
	}

	s += "\n The next dates with highest values where the following: ";
	for (int i = 0 ; i < 4 ; i++, s+= "\n")
	{
		index = searchHigh(inside, index - 1);
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		if (type == 't')
		{
			s += " with a avreage temperature of: ";
			s += to_string(dataVector.at(index).avgT);
		}
		else if (type == 'h')
		{
			s += " with a avreage humidity of: ";
			s += to_string(dataVector.at(index).avgH);			 
		}
		else if (type == 'm')
		{
			s += " with a avreage mold risk of: ";
			s += to_string(dataVector.at(index).avgM);
		}
	}
	
	return s;
}

std::string DC::DataClass::getMin(bool inside, char type)
{


	string s;
	int n = dataVector.size();
	//listSort(type, 0, n - 1);
	bubbleSort(n, type);
	int index = searchLow(inside, 0);

	if (inside)
	{
		s = "The lowest inside ";
	}
	else
	{
		s = "The lowest outside ";
	}
	if (type == 't')
	{

		s += "temperature was on the ";
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		s += " with a avreage temperature of: ";
		s += to_string(dataVector.at(index).avgT);
	}
	else if (type == 'h')
	{
		s += "humidity was on the ";
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		s += " with a avreage humidity of: ";
		s += to_string(dataVector.at(index).avgH);
	}
	else if (type == 'm')
	{
		s += "risk for mold was on the ";
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		s += " with a avreage mold risk of: ";
		s += to_string(dataVector.at(index).avgM);
	}

	s += "\nThe next dates with lowest values where the following: \n";
	for (int i = 0; i < 4; i++, s += "\n")
	{
		index = searchLow(inside, index + 1);
		s += to_string(dataVector.at(index).day[0]);
		s += "-";
		s += to_string(dataVector.at(index).day[1]);
		s += "-";
		s += to_string(dataVector.at(index).day[2]);
		if (type == 't')
		{
			s += " with a avreage temperature of: ";
			s += to_string(dataVector.at(index).avgT);
		}
		else if (type == 'h')
		{
			s += " with a avreage humidity of: ";
			s += to_string(dataVector.at(index).avgH);
		}
		else if (type == 'm')
		{
			s += " with a avreage mold risk of: ";
			s += to_string(dataVector.at(index).avgM);
		}
	}

	return s;
}

std::string DC::DataClass::getWintAut(bool winter)
{
	string s;
	int start = 0, counter = 0;
	dataDay d1;
	bubbleSort(dataVector.size(), 'd');
	if (winter == false)
	{
		for (int i = start; i < dataVector.size()-1 && counter < 5 ; i++)
		{
			if (dataVector.at(i).avgT <= 10 && dataVector.at(i).inside == false)
			{
				counter = 1;
				d1 = dataVector.at(i);
				start = i;
				for (int j = start; counter < 5; i++)
				{
					if (dataVector.at(i).avgT > 10 && dataVector.at(i).inside == false)
					{
						counter = 0;
						break;
					}
					counter++;
				}
			}
		}
		s = "Autum began on the date: ";
	}
	else
	{
		for (int i = start; i < dataVector.size() - 1 && counter < 5; i++)
		{
			if (dataVector.at(i).avgT <= 0 && dataVector.at(i).inside == false)
			{
				counter = 1;
				d1 = dataVector.at(i);
				start = i;
				for (int j = start; counter < 5; i++)
				{
					if (dataVector.at(i).avgT > 0 && dataVector.at(i).inside == false)
					{
						counter = 0;
						break;
					}
					counter++;
				}
			}
		}
		s = "Winter began on the date: ";
	}
	if (d1.day[0] > 0)
	{
		s += to_string(d1.day[0]) + "-" + to_string(d1.day[1]) + "-" + to_string(d1.day[2]);
	}
	else
	{
		if (winter == true)
		{
			s = "Winter never began acording to temperature";
		}
		else
		{
			s = "Autum never began acording to temperature";
		}
	}
	

	return s;
}

DataClass::DataClass()
{
	
	getData(false); //Calls function to add outside values
	getData(true); //Calls function to add inside values
	coll.listDataDetail.clear();
}



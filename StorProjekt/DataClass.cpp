#include "DataClass.h"
#include "DataCollector.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

using namespace DC;
using namespace Collector;




	/*
	Function calculates an avereage value of provided type.
	This function is used for preparing values to later be entered into main buffer dataVector by different function.
	*/
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

	/*
	Function retrives the index of where specific date in- or outdoors in list.
	*/
int DC::DataClass::searchDate(bool inside, int day)
{
	int tDay[3];

	//formates date variable to compare against entries in dataVector.
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


	/*
	Finds index of lowest value based on if inside or outside.
	*/
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


	/*
	Finds index of highest value based on if inside or outside.
	*/
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


	/*
	Function used by bubbleSort and listSort to swap values of 2 data points in dataVector.
	*/
void DC::DataClass::swap(dataDay *a, dataDay *b)
{
	dataDay t = *a;
	*a = *b;
	*b = t;
}

	
	/*
	Function is used to partition and sort, utilizing a quicksort style function. It is used by the function listSort.
	listSort() is not used in program as is.
	*/
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


	/*
	Function is an adaptation of a quicksort style sorting method. 
	function is not used in program.
	*/
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

	/*
	Function sorts list based on what type of value to sort, i.e is it sorting by mold, temp, humidity or date.
	Highest value will be placed at the end of dataVector while lowest will be placed at begining (i.e 0)
	Since the array that is to be sorted is a private vector of this class, no array or list needs to be passed to function.
	*/
void DC::DataClass::bubbleSort(int high, char type)
{
	
	if (type == 'm') //sorts based on mold
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
	else if (type == 'h') //sorts based on humidity
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
	else if (type == 't') //sorts based on temperature
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
	else if (type == 'd') //sorts based on date
	{
		for (int n = 3; n > 0; n--) //starts whith sorting by day, then month.
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

	/*
	Function is used by class constructor to retrive and add values to main buffer dataVector.
	This function condenses the data from the list listDataDetrail (consisting of all lines of data from .txt) down to a list of per day avreages. 
	*/
void DataClass::getData(bool inside)
{
	dataDay d; //declare struct for adding later into list.
	
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

		//calls functions to calculate avregeas for mold, temp and humid
		d.avgM = calcAvreage(inside, 1, index); 
		d.avgT = calcAvreage(inside, 2, index);
		d.avgH = calcAvreage(inside, 3, index);

		//sets index for last entry on latest date in listDataDetail.
		index[1] = index[0];

		

		dataVector.push_back(d); //Adds element onto main buffer.
		if (index[0] != coll.listDataDetail.size()) //if not end of vector, continue with next date
		{
			for (int i = 0; i < 3; i++)
			{
				date[i] = coll.listDataDetail.at(index[0] + 1).day[i]; //sets start date for next day
			}
		}
		else
		{
			//sets -1 to breake cycle
			index[0] = -1; 
		}


	} while (index[0] != -1);

	

}




/*
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
}*/

	/*
	Purpose of function is to compile a string to be printed based on date and requested type provided.
	string is printed to user in main()
	*/
string DC::DataClass::getAvreage(bool inside, char type, int date)
{
	int index = searchDate(inside, date); //calls search funktion for index of where value is located in dataVector.
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


	/*
	Used by front end to retrive and compile data from dataVector into maximum value of specified type into string.
	string is printed to user in main()
	*/
string DC::DataClass::getMax(bool inside, char type)
{
	
	string s;
	int n = dataVector.size();
	//listSort(type, 0, n - 1);
	bubbleSort(n, type); //calls sorting of list to speed up linear search
	int index = searchHigh(inside, n - 1); //calls function for index of max value of specified type
	
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
	for (int i = 0 ; i < 4 ; i++, s+= "\n") //loops to retrive the next dates of intresst, i.e other days of highest value.
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


/*
Used by front end to retrive and compile data from dataVector into minimum value of specified type into string.
string is printed to user in main()
*/
std::string DC::DataClass::getMin(bool inside, char type)
{


	string s;
	int n = dataVector.size();
	//listSort(type, 0, n - 1);
	bubbleSort(n, type); //calls sorting of list to speed up linear search
	int index = searchLow(inside, 0); //calls function for index of min value of specified type

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
	for (int i = 0; i < 4; i++, s += "\n") //loops to retrive the next dates of intresst, i.e other days of lowest value.
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

	/*
	Function determines if and when winter or autum began.
	*/
std::string DC::DataClass::getWintAut(bool winter)
{
	string s;
	int start = 0, counter = 0;
	dataDay d1;
	bubbleSort(dataVector.size(), 'd');
	if (winter == false)
	{
		for (int i = start; i < dataVector.size()-1 && counter < 5 ; i++) //linear loop through list
		{
			if (dataVector.at(i).avgT <= 10 && dataVector.at(i).inside == false) //if a temperature that meets criteria is found, date is stored.
			{				
				counter = 1;
				d1 = dataVector.at(i);
				start = i; //sets index of location of first date found.
				for (int j = start; counter < 5; i++) 
				{
					//if 5 values that does also meet criteria is found counter ticks up
					if (dataVector.at(i).avgT > 10 && dataVector.at(i).inside == false)
					{
						counter = 0;
						break;
					}
					counter++;
				}
				if (counter == 0) //if didn't meet criteria for autum, date resets for later failsafe
				{
					d1.day[0] = 0;
				}
			}
		}
		s = "Autum began on the date: ";
	}

	else //function is a mirrored version for retriving winter.
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
				if (counter == 0) //if didn't meet criteria for winter, date resets for later failsafe
				{
					d1.day[0] = 0;
				}
			}
		}
		s = "Winter began on the date: ";
	}
	if (d1.day[0] > 0) //checks to see if any applicable date was found.
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

	/*
	Constructor of function.
	Upon program start class is constructed and calls backend for retrival of data.
	*/
DataClass::DataClass()
{
	
	getData(false); //Calls function to add outside values
	getData(true); //Calls function to add inside values
	coll.listDataDetail.clear();
}



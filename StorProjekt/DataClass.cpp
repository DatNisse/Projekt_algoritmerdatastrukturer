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

void DC::DataClass::swap(dataDay* a, dataDay* b)
{
	dataDay t = *a;
	*a = *b;
	*b = t;
}

int DC::DataClass::partition(int low, int high, char type)
{
	
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		if (type == 'm')
		{
			// If current element is smaller than the pivot  
			if (dataVector[j].avgM < dataVector[high].avgM)
			{
				i++; // increment index of smaller element  
				swap(&dataVector[i], &dataVector[j]);
			}
		}
		else if (type == 'h')
		{
			// If current element is smaller than the pivot  
			if (dataVector[j].avgH < dataVector[high].avgH)
			{
				i++; // increment index of smaller element  
				swap(&dataVector[i], &dataVector[j]);
			}
		}
		else if (type == 't')
		{
			// If current element is smaller than the pivot  
			if (dataVector[j].avgT < dataVector[high].avgT)
			{
				i++; // increment index of smaller element  
				swap(&dataVector[i], &dataVector[j]);
			}
		}
		else if (type == 'i')
		{
			// If current element is smaller than the pivot  
			
		}
		else if (type == 'o')
		{
			// If current element is smaller than the pivot  
			
		}
	}
	swap(&dataVector[i + 1], &dataVector[high]);
	return (i + 1);
	
	//return 0;
}

void DC::DataClass::listSort(bool inside, char type) //sorts list depending on requested value
{

}



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

		for (int i = 0; i < 3; i++)
		{
			date[i] = coll.listDataDetail.at(index[0] + 1).day[i]; //sets start date for next day
		}


	} while (index[0] != -1);

	

}





DataClass::DataClass()
{
	
	getData(false); //Calls function to add outside values
	getData(true); //Calls function to add inside values
	coll.listDataDetail.clear();
}



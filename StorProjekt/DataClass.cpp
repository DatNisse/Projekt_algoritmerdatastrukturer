#include "DataClass.h"
#include "DataCollector.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

using namespace DC;
using namespace Collector;





void DataClass::getData()
{
	
	data d; //defines data struct for insertion in dataVector
	coll.readData(); //calls backend to retrive data from .txt

	cout << coll.rawData.size() << endl; //prints the size of the rawdata vector which is created

	for (int n = 0; n < coll.rawData.size(); n+=5)
	{
		for (size_t i = 0; i < 5; i++)
		{	
			if (i == 0) //assings date
			{
				d.day[0] = stoi(coll.rawData[i + n].substr(0, 4));
				d.day[1] = stoi(coll.rawData[i + n].substr(5, 2));
				d.day[2] = stoi(coll.rawData[i + n].substr(8, 2));
			}
			else if (i == 1) //assigns time
			{
				d.time[0] = stoi(coll.rawData[i + n].substr(0, 2));
				d.time[1] = stoi(coll.rawData[i + n].substr(3, 2));
				d.time[2] = stoi(coll.rawData[i + n].substr(6, 2));
			}
			else if (i == 2) //assigns if inside
			{
				if (coll.rawData[i + n] == "Inne")
				{
					d.inside = true;
				}
				else
				{
					d.inside = false;
				}
			}
			else if (i == 3) //assigns temp
			{
				d.temp = stod(coll.rawData[i + n]);
			}
			else if (i == 4) //assigns humidity
			{
				d.humid = stoi(coll.rawData[i + n]);
			}
		}

		dataVector.push_back(d); //adds the data element to the usable list
	}
	
	coll.rawData.~vector(); //deconstructs rawdata vector
}



DataClass::DataClass()
{
	
	Collector::DataCollector collector;

	getData();
}



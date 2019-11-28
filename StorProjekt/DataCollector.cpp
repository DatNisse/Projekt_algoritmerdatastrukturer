#include "DataCollector.h"
#include "DataClass.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Collector;
using namespace DC;
	

void DataCollector::sortDataDetail()
{

	data d; //defines data struct for insertion in dataVector

	cout << rawData.size() << endl; //prints the size of the rawdata vector which is created

	for (int n = 0; n < rawData.size(); n += 5)
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (i == 0) //assings date
			{
				d.day[0] = stoi(rawData[i + n].substr(0, 4));
				d.day[1] = stoi(rawData[i + n].substr(5, 2));
				d.day[2] = stoi(rawData[i + n].substr(8, 2));
			}
			else if (i == 1) //assigns time
			{
				d.time[0] = stoi(rawData[i + n].substr(0, 2));
				d.time[1] = stoi(rawData[i + n].substr(3, 2));
				d.time[2] = stoi(rawData[i + n].substr(6, 2));
			}
			else if (i == 2) //assigns if inside
			{
				if (rawData[i + n] == "Inne")
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
				d.temp = stod(rawData[i + n]);
			}
			else if (i == 4) //assigns humidity
			{
				d.humid = stoi(rawData[i + n]);
			}
		}
		
		d.mogel = moldIndex(d.temp, d.humid);
		listDataDetail.push_back(d); //adds the data element to the usable list

	}
}

double DataCollector::moldIndex(int h, double t)
{
	/*
			The mold diagram uses the following curve for mold risk with the formula: y = 100 - (22 / 15) x; where y is the humidity and x is the temperature.
			The "100" is the start value of the curve and the "22 / 15" is the slope of the diagram.
			Since the angle of the slope is unchanging throughout the whole diagram it can be used for values on the entire sloped part of the diagram.
			Since the angle of the horizontal line is also unchanging, it can be described as "t / 78" for the same effect. Values above 1 does have a chance of mold.
		*/

	double k0 = 22 / 15, kv; //k0 is the slope of the zero mold slope, kv is the slope for the data point.
	double mold;

	if (t <= 0 || t > 50) // if any of these cases are true, the data points slope is outside the "mold-zone", therefore default value is set to 0.
	{
		mold = 0;
	}
	else
	{
		if (t < 15) //determines if the value is on flat or sloped part of curve
		{
			kv = (100 - h) / t;
			mold = kv / k0;
		}
		else
		{
			mold = h / 78;
		}
	}

	return mold;
}

DataCollector::DataCollector()
{
	readData(); //calls function to retrive data from .txt


}

void DataCollector::readData()
{
	int n = 0;
	string tmp;
	ifstream text("tempdata4.txt");

	if (text.is_open())
	{
		while (!text.eof())
		{
			getline(text, tmp, ' ');
			rawData.push_back(tmp);
			getline(text, tmp, ',');
			rawData.push_back(tmp);
			getline(text, tmp, ',');
			rawData.push_back(tmp);
			getline(text, tmp, ',');
			rawData.push_back(tmp);
			getline(text, tmp);
			rawData.push_back(tmp);
			n++;
			if (n%10000 == 0)
			{
				cout << ".";
			}
		}
		cout << endl;
	}

	
}





#include "DataCollector.h"
#include "DataClass.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Collector;
using namespace DC;
	

	/*
	Function organises strings from rawData into data structs which are added to listDataDetail
	*/
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
		
		d.mogel = moldIndex(d.humid, d.temp); //calls function to calculate mold index for data point.
		listDataDetail.push_back(d); //adds the data element to the usable list
	}
	rawData.clear();
	

}


	/*
	Function calculates distance of point from curve to give a value of how high the risk of mold is.
	The function does this by calculating the closest point to the curve and then calculates the distance.
	*/
double DataCollector::moldIndex(int h, double t)
{
		/*
			The mold diagram uses the following curve for mold risk with the formula: y = 100 - (22 / 15) x; where y is the humidity and x is the temperature.
			The "100" is the start value of the curve and the negative of "22 / 15" is the slope of the diagram.

			To calculate the distance from the curve, the function uses the formula: M = ((x1 + x2)/2, (y1 + y2)/2).
			this function finds the closest point on the curve to the data point h and t.

			the function then uses the formula: d = sqrt((t - xm)^2 + (h - ym)^2) 
			where xm is the closest temperature(i.e x value) and ym is the closest humidity(i.e y value)
		*/

	
	
	double mold, xm, ym, dx, dy;
	double k0 = 22.0 / 15.0; //k0 is the slope of the zero mold slope, kv is the slope for the data point.
	if (t <= 0 || t > 50 ) // if any of these cases are true, the data points slope is outside the "mold-zone", therefore default value is set to 0.
	{
		mold = 0;
	}
	else
	{
		if (t < 15.0) //determines if the value is on flat or sloped part of curve
		{
			/*
			Old way of moldindex
			//kv = (100 - h) / t;
			//mold = (kv / k0);
			//mold = ((h - 78.0) * (t / 15.0)) * 0.22
			*/
			xm = (((100 - h) / k0) + t) / 2.0;
			ym = ((100 - k0 * t) + h) / 2.0;
			if (ym > h) //if the data point provided for humidity is below the curve, the mold risk is zero
			{
				mold = 0;
			}
			else
			{
				dx = pow((t - xm), 2);
				dy = pow((h - ym), 2);
				mold = sqrt((dx + dy));
			}
		}
		else
		{
			/*
			Old moldy way
			mold = (double(h) / double(78.0)); //if the value falls under the liniear segment of the curve, a simple ratio is calculated between line and data point for data consistency.
			*/
			if (h < 78)
			{
				//if the value provided is less than the value of the plane, there is zero risk for mold.
				mold = 0;
			}
			else
			{
				//since this part of the curve is a plane, t = xm. therefore the distance is simply h - y
				mold = h - 78.0;
			}
			
		}
	}

	return mold;
}

	/*
	Does a linear search for where the next date is in listDataDetail vector
	*/
int Collector::DataCollector::getIndex(int date[3], int prevIndex)
{
	
	for (int i = prevIndex + 1; i < listDataDetail.size(); i++)
	{
		if (listDataDetail.at(i).day[0] != date[0] || listDataDetail.at(i).day[1] != date[1] || listDataDetail.at(i).day[2] != date[2])
		{
			return i - 1; //returns last member of specified date
		}
		
	}

	return int(listDataDetail.size()); //if nothing was found, returns end of list
}

	/*
	Constructor for DataCollector, on construction runs readData to retrive data from .txt
	*/
DataCollector::DataCollector()
{
	readData();

}

	/*
	Function reads .txt file and collects the data into strings which are then added to the rawData list.
	*/
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
			if (n%10000 == 0) //to indicate progress for user, it will write out a dot every 10 000 value added.
			{
				cout << ".";
			}
		}
		cout << endl;
	}

	cout << "Begining sorting..." << endl;
	sortDataDetail(); //calls function to sort the retrived data into structs per data point.

	
}





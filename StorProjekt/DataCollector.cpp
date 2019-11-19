#include "DataCollector.h"
#include "DataClass.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Collector;
using namespace DC;

DataCollector::DataCollector()
{

}

int DataCollector::ReadData()
{
	string tmp;
	ifstream text("tempdata4short.txt");

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

		}
	}

	return int(&(rawData));
}



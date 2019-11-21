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





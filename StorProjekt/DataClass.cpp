#include "DataClass.h"
#include "DataCollector.h"

#include <vector>
using namespace std;

using namespace DC;


struct data
{
	int a;
};



void DataClass::getData()
{
	
	Collector::DataCollector coll;

	string temp = coll.ReadData();
	
}

DataClass::DataClass()
{
	getData();
}



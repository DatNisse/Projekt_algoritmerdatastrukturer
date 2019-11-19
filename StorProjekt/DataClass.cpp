#include "DataClass.h"
#include "DataCollector.h"

#include <vector>
using namespace std;

using namespace DC;
using namespace Collector;





void DataClass::getData()
{
	
	Collector::DataCollector coll;

	int p = coll.ReadData();

	

}

DataClass::DataClass()
{
	Collector::DataCollector collector;
	getData();
}



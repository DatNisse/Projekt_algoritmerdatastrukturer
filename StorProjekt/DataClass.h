#pragma once
#include "DataCollector.h"
#include <vector>

namespace DC
{
	class DataClass
	{
	private:
		
		struct dataDay
		{
			int day[3];
			bool inside;
			double avgM;
			double avgT;
			double avgH;
		};
		Collector::DataCollector coll;
		std::vector < DC::DataClass::dataDay > dataVector;

		void swap(dataDay* a, dataDay* b);
		int partition(int low, int high, char type);
		void listSort(char type, int low, int high);
		void inoutSort(bool inside);

		double calcAvreage(bool inside, int type, int refInd[2]);
		void getData(bool inside);
		

	public:
		double avreage(bool inside, char type);
		double minMax(bool inside, char type, int date[3]);

		DataClass();

	};
}



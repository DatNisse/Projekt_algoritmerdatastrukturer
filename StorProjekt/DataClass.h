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
		
		
		

		double calcAvreage(bool inside, int type, int refInd[2]);

		void swap(dataDay* a, dataDay* b);
		int partition(int low, int high, char type);
		void listSort(bool inside, char type);
		void inoutSort(bool inside);

		Collector::DataCollector coll;
		void getData(bool inside);
		
		
		

		
		std::vector < DC::DataClass::dataDay > dataVector;

	public:
		
		double avreage();
		double minMax();
		

		DataClass();

	};
}



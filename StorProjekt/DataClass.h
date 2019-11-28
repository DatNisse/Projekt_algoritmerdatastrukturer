#pragma once
#include "DataCollector.h"
#include <vector>

namespace DC
{
	class DataClass
	{
	private:
		
		void calcAvreage(bool inside);
		void calcMinMax(bool inside, bool max);

		Collector::DataCollector coll;
		void getData();
		
		
		std::vector < DC::DataClass::dataDay > dataVector;

		struct dataDay
		{
			int day[3];
			bool inside;
			double mogel;
			double topT;
			double avgT;
			double lowT;
			int topH;
			int avgH;
			int lowH;
		};


	public:
		
		double avreage();
		double minMax();
		

		DataClass();

	};
}



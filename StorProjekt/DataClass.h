#pragma once
#include "DataCollector.h"
#include <vector>

namespace DC
{
	class DataClass
	{
	private:
		
		struct data
		{
			int day[3];
			int time[3];
			bool inside;
			double temp;
			int humid;
		};

		Collector::DataCollector coll;
		void getData();
		
		
		std::vector < DC::DataClass::data > dataVector;

		

	public:
		
		DataClass();

	};
}



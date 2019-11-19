#pragma once
#include "DataCollector.h"
#include <vector>

namespace DC
{
	class DataClass
	{
	private:
		
		void getData();
		
		struct data
		{
			int day[3];
			int time[2];
			bool inside;
			double temp;
			int humid;
		};
		std::vector<data> dataVector;

	public:

		DataClass();

	};
}



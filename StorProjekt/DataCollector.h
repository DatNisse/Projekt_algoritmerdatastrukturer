#pragma once
#include <string>
#include <vector>

namespace Collector
{
	class DataCollector
	{
	public:
		
		DataCollector();
		std::vector<std::string> rawData;
		void readData();
		

	};
}



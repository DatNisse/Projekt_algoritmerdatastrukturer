#pragma once
#include <string>
#include <vector>



namespace Collector
{
	class DataCollector
	{
	private:
		struct data
		{
			int day[3];
			int time[3];
			bool inside;
			double mogel;
			double temp;
			int humid;

		};
		void sortDataDetail();
		std::vector<std::string> rawData;
		double moldIndex(int h, double t);
		void readData();

	public:
		
		DataCollector();
		std::vector<data> listDataDetail;
		
		
		

	};
}



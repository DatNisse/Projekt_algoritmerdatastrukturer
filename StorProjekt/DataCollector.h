#pragma once
#include <string>
#include <vector>



namespace Collector
{
	class DataCollector
	{
	private:
		struct data //middle ground struct, used for ease of calculation and potential of "VG-Uppgift".
		{
			int day[3];
			int time[3];
			bool inside;
			double mogel;
			double temp;
			int humid;

		};
		void sortDataDetail();
		std::vector<std::string> rawData; //raw list of strings read from the .txt file.

		double moldIndex(int h, double t);
		void readData();
	public:
		int getIndex(int date[3], int prevIndex);
		DataCollector();
		std::vector<data> listDataDetail; //semi refined list catagoriezed into day structs. same level of detail as rawdata
		
		
		

	};
}



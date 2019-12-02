#pragma once
#include "DataCollector.h"
#include <string>
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
		int searchDate(bool inside, int day);
		int searchLow(bool inside, int start);
		int searchHigh(bool inside, int start);
		void swap(dataDay* a, dataDay* b);
		int partition(int low, int high, char type);
		void listSort(char type, int low, int high);
		void bubbleSort(int high, char type);
		

		double calcAvreage(bool inside, int type, int refInd[2]);
		void getData(bool inside);
		

	public:
		void fixDate(std::string date, int a[3]);
		std::string avreage(bool inside, char type, int date);
		std::string getMax(bool inside, char type);
		std::string getMin(bool inside, char type);
		std::string getWintAut(bool winter);

		DataClass();

	};
}



#pragma once
#include "DataCollector.h"
#include <string>
#include <vector>

namespace DC
{
	class DataClass
	{
	private:

		struct dataDay //struct for avreages per day
		{
			int day[3];
			bool inside;
			double avgM;
			double avgT;
			double avgH;
		};
		Collector::DataCollector coll; //calls constructor of datacollector to begin collecting data
		std::vector < DC::DataClass::dataDay > dataVector; //main buffer for data, data is read upon start and, in the end, stored here for use by user
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
		//void fixDate(std::string date, int a[3]);
		std::string getAvreage(bool inside, char type, int date);
		std::string getMax(bool inside, char type);
		std::string getMin(bool inside, char type);
		std::string getWintAut(bool winter);
		void printAll();

		DataClass();

	};
}



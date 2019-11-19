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
			int a;
		};
		void getData();

	public:

		std::vector<data> dataVector;

		DataClass();

	};
}



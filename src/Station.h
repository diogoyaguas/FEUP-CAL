#pragma once
#include "Stop.h"
#include <vector>
#include <string>

class Station
{
	int stationID;
	std::vector<Stop> stops;
	string name;

	double dist = 0;
	Station *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue
public:
	Station();
	~Station();
};


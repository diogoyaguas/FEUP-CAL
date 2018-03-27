#pragma once
#include "Stop.h"
#include <vector>

class Station
{
	int stationID;
	std::vector<Stop> stops;

public:
	Station();
	~Station();
};


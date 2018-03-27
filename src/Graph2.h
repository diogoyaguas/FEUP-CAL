#pragma once
#include "Station.cpp"
#include <vector>

class Graph2
{
	std::vector<Station*> stationSet;
	Station *findStation(const int &stationID) const;
public:
	Graph2();
	~Graph2();
};


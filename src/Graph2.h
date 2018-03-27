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

	int getNumStations() const;
	bool addStation(Station* station);
	bool removeStation(Station* station);
	bool addLink(LineID lineID, Station* source, Station* dest);
	bool removeLink(Station* source, Station* dest, LineID lineID);
};


#pragma once
#include "Stop.h"
#include "MutablePriorityQueue.h"
#include "Link.h"
#include <vector>
#include <string>

class Station
{
	int stationID;
	double x;
	double y;
	string name;
	std::vector<Stop> stops;
	std::vector<Link> connections;

	double dist = 0;
	Station *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue
public:
	Station();
	Station(int stationID, double x, double y, string name);
	Station(int stationID, double x, double y, vector<Stop> stops, string name);
	~Station();

	bool operator<(Station & station) const; // // required by MutablePriorityQueue
	double getDist() const;
	Station *getPath() const;

	friend class Graph2;
	friend class MutablePriorityQueue<Station>;
};


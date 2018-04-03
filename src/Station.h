#ifndef FEUP_CAL_STATION_H
#define FEUP_CAL_STATION_H

#include "Stop.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <string>

class Link;

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
	double getX() { return this->x;}
	double getY() { return this->y;}
	double getDist() const;
	Station *getPath() const;
	int getID() { return this->stationID;}

	void addLinkTo(Station* dest, LineID lineID);
	void addStop(Stop stop);
	bool removeLinksTo(Station * dest);
	bool removeLinkTo(Station * dest, LineID lineID);

	Stop* findStop(LineID lineID);

	double calculateDistanceTo(Station* dest);

	void updateTimeWeightsFrom(LineID lineID);

	friend class Graph2;
	friend class MutablePriorityQueue<Station>;

	vector<Stop> getStops();

	vector<Link> getConnections();
};

class Link
{
	LineID lineID;
	Station* dest; //Destination Vertex
	double travelSpeed;
	double weight; //Needs to be calculated depending on search parameters.
public:
	Link();
	Link(LineID lineID, Station* dest);
	Link(LineID lineID, Station* dest, double travelTime);
	~Link();

	friend class Graph2;
	friend class Station;
};

#endif //FEUP_CAL_STATION_H

#ifndef FEUP_CAL_STATION_H
#define FEUP_CAL_STATION_H

#include "Stop.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <string>

class Link;

class Station
{
	string stationID;
	int x;
	int y;
	string name;
	vector<Stop> stops;
	vector<Link> connections;

	double dist = 0;
	Station *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue
public:
	Station();
	Station(string stationID, int x, int y, string name);
	Station(string stationID, int x, int y, vector<Stop> stops, string name);
	~Station();

	bool operator<(Station & station) const; // // required by MutablePriorityQueue
	double getX() { return this->x;}
	int getY() { return this->y;}
	double getDist() const;
	Station *getPath() const;
	const string & getID() { return this->stationID;}
	string getName() { return this->name; }

	void addLinkTo(Station* dest, LineID lineID);
	void addStop(Stop stop);
	bool removeLinksTo(Station * dest);
	bool removeLinkTo(Station * dest, LineID lineID);

	Stop* findStop(LineID lineID);

	double calculateDistanceTo(Station* dest);

	void updateTimeWeightsFrom(LineID lineID);

	//friend class Graph2;
	friend class MutablePriorityQueue<Station>;

	vector<Stop> getStops();

	vector<Link> getConnections();

	//Calculates the Euclidean distance to the other station
	double getDistTo(Station* other);


};

class Link
{
	LineID lineID;
	Station* dest; //Destination Vertex
	double travelSpeed;
	double weight; //Needs to be calculated depending on search parameters.

	int idSource; //testing graphviewer 
	int idDest;//testing graphviewer

public:
	Link();
	Link(LineID lineID, Station* dest);
	Link(LineID lineID, Station* dest, double travelTime);
	~Link();
	

	Link(LineID lineID, int idSource, int idDest); //test


	Station* getDest();
	double getTravelSpeed();
	double getWeight();
    LineID getLineID();
	int getIdSource();
	int getIdDest();

	friend class Graph2;
	friend class Station;


};

#endif //FEUP_CAL_STATION_H

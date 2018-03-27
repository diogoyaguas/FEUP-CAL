#include "Station.h"



Station::Station()
{
}

Station::Station(int stationID, string name)
{
	this->stationID = stationID;
	this->name = name;
}

Station::Station(int stationID, vector<Stop> stops, string name)
{
	this->stationID = stationID;
	this->stops = stops;
	this->name = name;
}


Station::~Station()
{
}

bool Station::operator<(Station & station) const
{
	return this->dist < station.dist;
}

double Station::getDist() const
{
	return dist;
}

Station * Station::getPath() const
{
	return path;
}

#include "Station.h"



Station::Station()
{
}

Station::Station(int stationID, double x, double y, string name) : stationID(stationID), x(x), y(y), name(name)
{
}

Station::Station(int stationID, double x, double y, vector<Stop> stops, string name) : stationID(stationID), x(x), y(y), name(name)
{
	this->stops = stops;
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

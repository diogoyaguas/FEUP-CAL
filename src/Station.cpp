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

void Station::addLinkTo(Station * dest, LineID lineID)
{
	connections.push_back(Link(lineID, dest));
}

bool Station::removeLinksTo(Station * dest)
{
	for (auto it = connections.begin(); it != connections.end(); it++)
		if (it->dest == dest) {
			connections.erase(it);
			return true;
		}
	return false;
}

bool Station::removeLinkTo(Station * dest, LineID lineID)
{
	for (auto it = connections.begin(); it != connections.end(); it++)
		if (it->dest == dest && it->lineID == lineID) {
			connections.erase(it);
			return true;
		}
	return false;
}

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

Stop * Station::findStop(LineID lineID)
{
	Stop* stop = nullptr;
	for (int i = 0; i < stops.size(); i++) {
		if (stops.at(i).lineID == lineID) {
			stop = &(stops.at(i));
			break;
		}
	}
	return stop;
}

void Station::updateTimeWeightsFrom(LineID lineID)
{
	Stop* entryStop = findStop(lineID);
	if (entryStop != nullptr) {
		double entryTime = entryStop->timeToStation;
		for (size_t i = 0; i < connections.size(); i++)
		{
			if (connections.at(i).lineID == lineID) continue;	//Continues on the same line, no need to change stops
			Stop* exitStop = findStop(connections.at(i).lineID);
			if (exitStop != nullptr) {
				double exitTime = exitStop->timeToStation;
				connections.at(i).weight += entryTime + exitTime; //TODO: it needs to add this to the BASE weight, or else it will add on top of other updates.
			}
			else {
				cout << "Warning: Unable to find the exit stop!\n";
			}
		}
	}
	else {
		cout << "Warning: Unable to find the entry stop!\n";
	}
}

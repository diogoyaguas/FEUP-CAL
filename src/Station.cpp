#include "Station.h"
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

Station::Station() = default;

Station::~Station() = default;

Station::Station(string stationID, int x, int y, string name) : stationID(std::move(stationID)), x(x), y(y), name(
        std::move(name)) {
}

Station::Station(string stationID, int x, int y, vector<Stop> stops, string name) : stationID(std::move(stationID)), x(x), y(y),
                                                                                       name(std::move(std::move(name))) {
    this->stops = std::move(stops);
}

bool Station::operator<(Station &station) const {
    return this->dist < station.dist;
}

double Station::getDist() const {
    return dist;
}

Station *Station::getPath() const {
    return path;
}

void Station::addLinkTo(Station *dest, LineID lineID) {
    connections.emplace_back(lineID, dest);
}

void Station::addStop(Stop stop) {

    this->stops.push_back(stop);
}

bool Station::removeLinksTo(Station *dest) {
    for (auto it = connections.begin(); it != connections.end(); it++)
        if (it->dest == dest) {
            connections.erase(it);
            return true;
        }
    return false;
}

bool Station::removeLinkTo(Station *dest, LineID lineID) {
    for (auto it = connections.begin(); it != connections.end(); it++)
        if (it->dest == dest && it->lineID == lineID) {
            connections.erase(it);
            return true;
        }
    return false;
}

Stop *Station::findStop(LineID lineID) {
    Stop *stop = nullptr;
    for (auto &i : stops) {
        if (i.lineID == lineID) {
            stop = &i;
            break;
        }
    }
    return stop;
}

double Station::calculateDistanceTo(Station *dest) {
    return sqrt(x * dest->x + y * dest->y);
}

void Station::updateTimeWeightsFrom(LineID lineID) {
    Stop *entryStop = findStop(lineID);
    if (entryStop != nullptr) {
        double entryTime = entryStop->timeToStation;
        for (auto &connection : connections) {
            if (connection.lineID == lineID) continue;    //Continues on the same line, no need to change stops
            Stop *exitStop = findStop(connection.lineID);
            if (exitStop != nullptr) {
                double exitTime = exitStop->timeToStation;
                connection.weight += entryTime +
                                            exitTime; //TODO: it needs to add this to the BASE weight, or else it will add on top of other updates.
            } else {
                cout << "Warning: Unable to find the exit stop!\n";
            }
        }
    } else {
        cout << "Warning: Unable to find the entry stop!\n";
    }
}

vector<Stop> Station::getStops() {

    return stops;
}

vector<Link> Station::getConnections() {

    return connections;
}

double Station::getDistTo(Station * other)
{
	return sqrt(pow(x - other->getX(), 2) + pow(y - other->getY(), 2));
}


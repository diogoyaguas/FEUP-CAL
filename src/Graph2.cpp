#include "Graph2.h"
#include "Station.h"
#include <limits>
#include <cmath>

using namespace std;

#define INF numeric_limits<double>::max()

Station * Graph2::findStation(const int & stationID) const
{
	for (auto s : stationSet)
		if (s->stationID == stationID)
			return s;
	return nullptr;
}

Graph2::Graph2()
{
}


Graph2::~Graph2()
{
}

int Graph2::getNumStations() const
{
	return stationSet.size();
}

bool Graph2::addStation(Station * station)
{
	if (findStation(station->stationID) != NULL)
		return false;
	stationSet.push_back(station);
	return true;
}

bool Graph2::removeStation(Station * station)
{
	auto v1 = findStation(station->stationID);
	auto v2 = findStation(station->stationID);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeLinksTo(v2);
}

bool Graph2::addLink(LineID lineID, Station * source, Station * dest)
{
	auto s1 = findStation(source->stationID);
	auto s2 = findStation(dest->stationID);
	if (s1 == NULL || s2 == NULL)
		return false;
	s1->addLinkTo(s2, lineID);
	return true;
}

bool Graph2::removeLink(Station * source, Station * dest, LineID lineID)
{
	auto s1 = findStation(source->stationID);
	auto s2 = findStation(dest->stationID);
	if (s1 == NULL || s2 == NULL)
		return false;
	return s1->removeLinkTo(s2, lineID);
}

void Graph2::calculateBaseTimeWeights()
{
	for (size_t i = 0; i < stationSet.size(); i++)
	{
		Station* s = stationSet.at(i);
		for (size_t j = 0; j < s->connections.size(); j++)
		{
			Station* d = s->connections.at(i).dest;
			s->connections.at(i).weight = s->calculateDistanceTo(d) / s->connections.at(i).travelSpeed;
		}
	}
}

void Graph2::dijkstraTimePath(const int & stationID)
{
	auto i = stationSet.begin();
	for (; i != stationSet.end(); i++) {
		Station* s = *i;
		s->dist = INF;
		s->path = NULL;
	}

	Station* orig = findStation(stationID);
	orig->dist = 0;

	MutablePriorityQueue< Station > q;
	q.insert(orig);

	while (!q.empty()) {
		Station* s = q.extractMin();
		for (vector<Link>::iterator i = s->connections.begin(); i != s->connections.end(); i++) {
			Station* w = i->dest;
			if (w->getDist() > s->getDist() + i->weight) {
				double oldDist = w->dist;
				w->dist = s->getDist() + i->weight;
				w->path = s;
				if (oldDist == INF) q.decreaseKey(w);
				else q.insert(w);
			}
		}
	}
}

vector<Station*> Graph2::getTimePath()
{
	//TODO
	return vector<Station*>();
}

vector<Station*> Graph2::getStations()
{
	return stationSet;
}

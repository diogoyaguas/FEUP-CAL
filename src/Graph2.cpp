#include "Graph2.h"



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

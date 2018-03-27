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

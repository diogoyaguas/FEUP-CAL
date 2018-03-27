#pragma once
#include "Station.h"
#include "Line.h"
class Link
{
	LineID lineID;
	Station* dest; //Destination Vertex
	double travelTime;
public:
	Link();
	Link(LineID lineID, Station* dest);
	Link(LineID lineID, Station* dest, double travelTime);
	~Link();

	friend class Graph2;
	friend class Station;
};


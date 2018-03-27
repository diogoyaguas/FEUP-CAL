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
	~Link();
};


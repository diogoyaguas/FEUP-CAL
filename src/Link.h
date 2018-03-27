#pragma once
#include "Station.h"
class Link
{
	Station* dest; //Destination Vertex
	double travelTime;
public:
	Link();
	~Link();
};


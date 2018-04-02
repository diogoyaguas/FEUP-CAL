#include "Station.h"

Link::Link()
{
}

Link::Link(LineID lineID, Station * dest) : dest(dest)
{
	this->lineID = lineID;
	this->travelSpeed = 0;
	//TODO: calculate travelTime;
}

Link::Link(LineID lineID, Station * dest, double travelSpeed) : dest(dest), travelSpeed(travelSpeed)
{
	this->lineID = lineID;
}


Link::~Link()
{
}

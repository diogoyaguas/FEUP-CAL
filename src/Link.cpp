#include "Link.h"



Link::Link()
{
}

Link::Link(LineID lineID, Station * dest) : dest(dest)
{
	this->lineID = lineID;
	this->travelTime = 0;
	//TODO: calculate travelTime;
}

Link::Link(LineID lineID, Station * dest, double travelTime) : dest(dest), travelTime(travelTime)
{
	this->lineID = lineID;
}


Link::~Link()
{
}

#include "Stop.h"



Stop::Stop()
{
	this->timeToStation = 0;
	this->visited = false;
}

Stop::Stop(LineID lineID, double timeToStation)
{
	this->lineID = lineID;
	this->timeToStation = timeToStation;
	this->visited = false;
}


Stop::~Stop()
{
}

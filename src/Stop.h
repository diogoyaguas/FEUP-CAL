#pragma once
#include "Line.h"

class Stop
{
	LineID lineID;
	double timeToStation;
	bool visited;
public:
	Stop();
	Stop(LineID lineID, double timeToStation);
	~Stop();
	double getTimeToStation() {return timeToStation;}
    LineID getLineID() { return lineID;}
	friend class Station;
};


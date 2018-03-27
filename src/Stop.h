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
};


#pragma once

#include "Line.h"
#include <string>

class Stop {
    string stopID;
    LineID lineID;
    double timeToStation;
    bool visited;
public:
    Stop();

    Stop(string stopID, LineID lineID, double timeToStation);

    ~Stop();

    double getTimeToStation() { return timeToStation; }

    LineID getLineID() { return lineID; }

    string getStopID() { return stopID; }

    bool getVisited() { return visited; }

    friend class Station;
};


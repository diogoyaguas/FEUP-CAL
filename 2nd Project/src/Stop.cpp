#include "Stop.h"

#include <utility>

Stop::Stop() {
    this->timeToStation = 0;
    this->visited = false;
}

Stop::Stop(string stopID, LineID lineID, double timeToStation) {
    this->stopID = std::move(stopID);
    this->lineID = lineID;
    this->timeToStation = timeToStation;
    this->visited = false;
}

Stop::~Stop() = default;

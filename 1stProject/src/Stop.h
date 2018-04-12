#pragma once

#include "Line.h"
#include <string>
/**
 * @brief Class that handles the stops
 */
class Stop {
    string stopID;
    LineID lineID;
    double timeToStation;
    bool visited;
public:
    /**
     * @brief Default constructor of class Stop
     */
    Stop();
    /**
     * @brief Constructor of class Stop
     * @param stopID
     * @param lineID
     * @param timeToStation
     */
    Stop(string stopID, LineID lineID, double timeToStation);
    /**
     * @brief Default destructor of class Stop
     */
    ~Stop();
    /**
     * @brief Getter of time to get to a certain station from a stop
     * @return double - time to station
     */
    double getTimeToStation() { return timeToStation; }
    /**
     * @brief Getter of Line id
     * @return LineID - object to class LineID
     */
    LineID getLineID() { return lineID; }
    /**
     * @brief Getter of id of a stop
     * @return string - stop id
     */

    string getStopID() { return stopID; }
    /**
     * @brief Checks if a station was already visited
     * @return bool - true if visited, false otherwise
     */
    bool getVisited() { return visited; }

    friend class Station;
};


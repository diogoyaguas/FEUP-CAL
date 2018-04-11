#ifndef FEUP_CAL_STATION_H
#define FEUP_CAL_STATION_H

#include "Stop.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <string>
/**
 * @brief Class that handles the links
 */
class Link;

class Station
{
	string stationID;
	int x;
	int y;
	string name;
	vector<Stop> stops;
	vector<Link> connections;

	double dist = 0;
	Station *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue
public:
	/**
	 * @brief Default constructor of class Station
	 */
	Station();
	/**
	 * @brief Constructor of class Station
	 * @param stationID
	 * @param x
	 * @param y
	 * @param name
	 */
	Station(string stationID, int x, int y, string name);
	/**
	 * @brief Constructor of class Station
	 * @param stationID
	 * @param x
	 * @param y
	 * @param stops
	 * @param name
	 */
	Station(string stationID, int x, int y, vector<Stop> stops, string name);
	/**
	 * @brief Default destructor
	 */
	~Station();
	/**
	 * @brief Overload of < operator for station
	 * @param station - object of class Station
	 *
	 */
	bool operator<(Station & station) const; // // required by MutablePriorityQueue
	/**
	 * @brief Getter of param x
	 * @return int - x of Station
	 */
	int getX() { return this->x;}
	/**
	 * @brief Getter of param y
	 * @return int - y of Station
	 */
	int getY() { return this->y;}
	/**
	 * @brief Getter of param dist
	 * @return double - dist of Station
	 */
	double getDist() const;
	/**
	 * @brief Getter of param path
	 * @return pointer to Station - path of Station
	 */
	Station *getPath() const;
	/**
	 * @brief Getter of Stations id
	 * @return string - id of Station
	 */
	const string & getID() { return this->stationID;}
	/**
	 * @brief Getter of Stations name
	 * @return string - name of station
	 */
	string getName() { return this->name; }
	/**
	 * @brief Adds link to stations. (Adds a connection)
	 * @param dest (destionation)
	 * @param lineID
	 */

	void addLinkTo(Station* dest, LineID lineID);
	/**
	 * @brief Adds stop to station
	 * @param stop - object of class Stop
	 */
	void addStop(Stop stop);
	/**
	 * @brief Removes connection to a station/stop
	 * @param dest
	 * @return bool
	 */
	bool removeLinksTo(Station * dest);
	/**
	 * @brief Removes connection to a station/stop
	 * @param dest
	 * @param lineID
	 * @return
	 */
	bool removeLinkTo(Station * dest, LineID lineID);
	/**
	 * @brief Checks for a stop in a station
	 * @param lineID
	 * @return pointer to an object of the class Stop
	 */
	Stop* findStop(LineID lineID);
	/**
	 * @brief Calculates distance to a station
	 * @param dest
	 * @return distance (double)
	 */

	double calculateDistanceTo(Station* dest);
	/**
	 * @brief Updates time weights from a line
	 * @param lineID
	 */
	void updateTimeWeightsFrom(LineID lineID);


	friend class MutablePriorityQueue<Station>;
	/**
	 * @brief Getter of vector of Stops
	 * @return vector of objects of class Stop
	 */
	vector<Stop> getStops();
	/**
	 * @brief Getter of connections
	 * @return vector of objects of class Link
	 */
	vector<Link> getConnections();

	/**
	 * @brief Calculates the Euclidean distance to the other station
	 * @param other - pointer to object of class Station
	 * @return double - distance to other station
	 */
	double getDistTo(Station* other);
};

class Link
{
	LineID lineID;
	Station* dest; //Destination Vertex
	double travelSpeed;
	double weight; //Needs to be calculated depending on search parameters.

	int idSource; //testing graphviewer 
	int idDest;//testing graphviewer

public:
	/**
	 * @brief Default constructor of class Link
	 */
	Link();
	/**
	 * @brief Constructor of class Link
	 * @param lineID
	 * @param dest
	 */
	Link(LineID lineID, Station* dest);
	/**
	 * @brief Constructor of class Link
	 * @param lineID
	 * @param dest
	 * @param travelTime
	 */
	Link(LineID lineID, Station* dest, double travelTime);
	/**
	 * @brief Default destructor of class Link
	 */
	~Link();
	/**
	 * @brief Constructor of class Link
	 * @param lineID
	 * @param idSource
	 * @param idDest
	 */

	Link(LineID lineID, int idSource, int idDest); //test
	/**
	 *
	 * @brief Getter of dest
	 * @return pointer to an object of the class Station
	 */

	Station* getDest();
	/**
	 * @brief Getter of travel speed
	 * @return double - travel speed
	 */
	double getTravelSpeed();
	/**
	 * @brief Getter of weight of link
	 * @return double - weigth
	 */
	double getWeight();
	/**
	 * @brief Getter of Line id
	 * @return object of class LineID
	 */
    LineID getLineID();
	/**
	 * @brief Getter of origin stop
	 * @return int - id source
	 */
	int getIdSource();
	/**
	 * @brief Getter of destination stop
	 * @return int - id dest
	 */
	int getIdDest();


	friend class Station;


};

#endif //FEUP_CAL_STATION_H

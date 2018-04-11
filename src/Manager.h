#ifndef FEUP_CAL_MANAGER_H
#define FEUP_CAL_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "graphviewer.h"
#include "Station.h"
#include "Graph.h"

using namespace std;
/**
 * @brief Main class of the program. Contains the principal functions of the project, such as the algorithms used
 */
class Manager {

private:
    static vector<Station> myStation;
    static vector<Line> myLine;
    static Graph<string> graphDistance;
    static Graph<string> graphTime;
    static Graph<string> graphPrice;
    static Graph<string> graphTranshipment;

    static GraphViewer *gv;



public:
    /**
	 * @brief Default construtor of class Manager
	 */
    Manager();

    /**
     * @brief Loads the data from the station file, creating objects of the Station class and adding to the respective vertex in myStation
     *
     */
    static void loadStations();

    /**
    * Function that loads the data from the lines file into the structures in Graph.h
    */
    static void loadLines();

    /**
     * @brief Function that loads all the data
	*
	*/
    static void loadData();
    /**
     * @brief Function that allows the user to pick a destination and checks if the option is valid
     * @return string - id of destination
     */
    static string chooseDestination();
    /**
     * @brief Function that asks user the id of the station of origin
     * @return string - id of origin
     */
    static string chooseOrigin();
    /**
     *@brief Checks if the chosen id is valid
     * @param id
     * @param stations - vector of objects from class Station
     * @return bool - true if the id is valid, false otherwise
     */
    static bool VerifyChoice(string id, vector<Station> stations);
    /**
     * @brief Function that prints the graph with graphviewer
     */
    static void printGraph();
    /**
     * @brief Function that paints the itenerary of the user
     * @param path
     * @param gv
     */
    static void paintPath(vector<string> path);
    /**
     * @brief Algorithm to choose the itenerary with minimum distance
     * @param origin - string (id of the origin)
     * @param destination - string (id of the destination)
     */
    static void chooseShorterPath(const string &origin, const string &destination);
    /**
     * @brief Algorithm to choose the fastest itenerary for the user
     * @param origin - string (id of the origin)
     * @param destination - string (id of the destination)
     */
    static void chooseFastestPath(const string &origin, const string &destination);
    /**
     * @brief Algorithm to choose the cheapest itenerary for the user
     * @param origin - string (id of the origin)
     * @param destination -  string (id of the destination)
     */
    static void chooseCheaperPath(const string &origin, const string &destination);
    /**
     * @brief Algorithm to choose the itenerary with less number of transhipments
     * @param origin - string (id of the origin)
     * @param destination -  string (id of the destination)
     */
    static void chooseLessTranshipmentPath(const string &origin, const string &destination);
    /**
     * @brief Finds a station with the id wanted
     * @param id - string (id of the station)
     * @return object of the class Station
     */
    static Station findStation(const string &id);
    /**
     * @brief Reads the stops from the lines file and loads them
     */
    static void loadStops();
    /**
     * @brief Getter of type of transport (Bus, Subway or Train)
     * @param id
     * @return string - Type of transport ("Bus", "Subway" or "Train")
     */
    static string getTransport(const string &id);
    /**
     * @brief Finds a stop with the id wanted
     * @param id - string (id of the stop)
     * @return object of the class Station
     */
    static Station findStop(const string &id);
    /**
     * @brief Getter of vector of stations
     * @return vector of objects from the class Station
     */
    static vector<Station> getStation() { return myStation; }
    /**
     * @brief Checks if the string contains only digits
     * @param str
     * @return bool - true if contains only digits, false otherwise
     */
    static bool is_digits(const string &str);
    /**
     * @brief Getter of line id
     * @param s - object of class Station
     * @param id - id of the wanted stop
     * @return int - id of the line
     */
    static int getLine(Station s, const string &id);
    /**
     * @brief Function that allows the program to continue and return to main menu after a function was finished
     */
    static void continueFunction();
    /**
     * @brief Setter of vector of lines
     * @param vector of objects of class Line
     */
    static void setMyLine(vector<Line> vector);
};


#endif //FEUP_CAL_MANAGER_H

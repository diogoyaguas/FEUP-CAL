#ifndef FEUP_CAL_MANAGER_H
#define FEUP_CAL_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <map>
#include "graphviewer.h"
#include "Station.h"
#include "Graph.h"

using namespace std;

/**
 * @brief Main class of the program. Contains the principal functions of the project, such as the algorithms used
 */
class Manager {


    typedef pair<int, Station> APR;
    typedef pair<int, Line> APR2;

    struct APR_Greater_Than {
        bool operator()(APR a, APR b) const {
            return a.first > b.first;
        }
    };

    struct APR2_Greater_Than {
        bool operator()(APR2 a, APR2 b) const {
            return a.first > b.first;
        }
    };

private:
    static vector<Station> myStation;
    static vector<int> myEdges;
    static vector<Line> myLines;
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
     * @brief Function that allows the user to pick a destination from the stops in the given line and checks if the option is valid
     * @param lineDestination the line whose stop you want to go to.
     * @return string - id of destination
     */
    static string chooseDestination(Line lineDestination);

    /**
     * @brief Function that asks user the id of the station of origin
     * @return string - id of origin
     */
    static string chooseOrigin();

    /**
     * @brief Function that asks user the id of the station of origin, based on the given line.
     * @param lineOrigin the line whose stop you're departing from.
     * @return string - id of origin
     */
    static string chooseOrigin(Line lineOrigin);

    /**
    * @brief Function that asks user the line of the station of origin
    * @return Line - line of origin
    */
    static Line chooseOriginLine();

    /**
    * @brief Function that asks user the line of the station of the destination
    * @return Line - line of the destination
    */
    static Line chooseDestinationLine();

    /**
     *@brief Checks if the chosen id is valid
     * @param id
     * @param stations - vector of objects from class Station
     * @return bool - true if the id is valid, false otherwise
     */
    static bool VerifyChoice(string id, vector<Station> stations);

    /**
    *@brief Checks if the chosen id is valid
    * @param id
    * @param lines - vector of objects from class Station
    * @return bool - true if the id is valid, false otherwise
    */
    static bool VerifyChoice(string id, vector<Line> lines);

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
    * @brief Finds a line with the name wanted
    * @param name - string (id of the line)
    * @return object of the class Line
    */
    static Line findLine(const string &name);

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
     * @brief Getter of vector of lines
     * @return vector of objects from the class Line
     */
    static vector<Line> getLines() { return myLines; }

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
    static string getLine(Station s, const string &id);

    /**
     * @brief Function that allows the program to continue and return to main menu after a function was finished
     */
    static void continueFunction();

    /**
     * @brief Search for a Station with exact name
     * @param name
     * @return vector of objects from the class Station
     */
    static vector<Station> searchExactStation(string name);

    /**
     * @brief Search for a Station with exact name
     * @param name
     * @param stations
     * @return vector of objects from the class Station
     */
    static vector<Station> searchExactStation(string name, vector<Station> stations);

    /**
     * @brief Search for a Line with exact name
     * @param name
     * @return vector of objects from the class Line
     */
    static vector<Line> searchExactLine(string name);

    /**
     * @param pattern
     * @param f
     */
    static void preKpm(string pattern, int f[]);

    /**
     * @param pattern
     * @param target
     * @return true or false
     */
    static bool kpm(string pattern, string target);

    /**
     * @brief Reset colors of edges
     */
    static void resetColors();

    /**
     * @brief Choose exact origin by name
     * @param stations
     * @return id of Station
     */
    static string chooseExactOrigin(vector<Station> stations);

    /**
     * @brief Choose exact origin line by name
     * @param lines
     * @return id of Line
     */
    static string chooseExactLineOrigin(vector<Line> lines);

    /**
     * @brief Approximate matching string to Station's name
     * @param name
     * @return vector of objects from the class Station
     */
    static vector<Station> approximateStringMatchingStation(string name);

    /**
     * @brief Approximate matching string to Station's name
     * @param name
     * @param stations
     * @return vector of objects from the class Station
     */
    static vector<Station> approximateStringMatchingStation(string name, vector<Station> stations);

    /**
     * @brief Approximate matching string to Line's name
     * @param name
     * @return vector of objects from the class Line
     */
    static vector<Line> approximateStringMatchingLine(string name);

    /**
     * @brief Manage words
     * @param sentence
     * @return vector of strings
     */
    static vector<string> manageWords(const string &sentence);

    /**
     * @brief Edit distance to compare strings
     * @param pattern
     * @param text
     * @return int distance
     */
    static int editDistance(string pattern, string text);

    /**
     * @brief Find approximate matching strings
     * @param pattern
     * @param text
     * @return int total edit distance
     */
    static int findApproxMatchingStrings(const string &pattern, string text);

    /**
     * @brief Find id Station
     * @param name
     * @return id Station
     */
    static const string findIdStation(string name);

    /**
     * @brief Sort vector Station
     * @param s1
     * @param s2
     * @return true or false
     */
    static bool sortStations(Station s1, Station s2);

    /**
     * @brief Sort vector Lines
     * @param l1
     * @param l2
     * @return true or false
     */
    static bool sortLines(Line l1, Line l2);

    /**
     * @brief Transform a two digits number into one digit
     * @param id
     * @return string with one digiti number
     */
    static string twoDigitsIdToOne(string id);

    /**
     * @brief Getter of Lines from a Station
     * @param name
     * @return Lines from a Station
     */
    static vector<Line> getLinesFromStation(string name);
};


#endif //FEUP_CAL_MANAGER_H

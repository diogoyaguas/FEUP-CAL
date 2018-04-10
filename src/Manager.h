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

class Manager {

private:
    static vector<Station>  myStation;
    static vector<Line> myLine;
	static Graph<string> graphDistance;
    static Graph<string> graphTime;
	static Graph<string> graphPrice;
    static Graph<string> graphTranshipment;

/**
	 * Construtor default.
	 */

public:
	Manager();
    /**
     * A function that loads the data from the station file, creating objects of the Station class and adding to the respective vertex in myStation.
     */
    static void loadStations();

	/**
	* Function that loads the data from the lines file into the structures in Graph.h.
	*/
	static void loadLines();

    /**
	* Function that loads all the data.
	*/
    static void loadData( );

	static string chooseDestination();

	static string chooseOrigin();

	static bool VerifyChoice(string id, vector<Station> stations);


	static void printGraph(GraphViewer *gv);
	static void paintPath(vector<string> path, GraphViewer *gv);

    static void chooseShorterPath(const string &origin, const string &destination, GraphViewer *gv);

    static Station findStation(const string &id);

	static void loadStops( );

    static string getTransport(const string &id);

	static Station findStop(const string &id);


	static vector<Station> getStation() { return myStation;}

	static bool is_digits(const string &str);

	static int getLine(Station s, const string &id);

    static void chooseFastestPath(const string &origin, const string &destination, GraphViewer *gv);

    static void chooseCheaperPath(const string &origin, const string &destination, GraphViewer *gv);

    static void chooseLessTranshipmentPath(const string &origin, const string &destination, GraphViewer *gv);
};


#endif //FEUP_CAL_MANAGER_H

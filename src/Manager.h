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
	static Graph<string> graph;


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
    static void loadData();

	static string chooseDestination();

	static string chooseOrigin();

	static bool VerifyChoice(string id, vector<Station> stations);

	void initGv(GraphViewer *gv);
	//void printGraph(GraphViewer *gv);
	//void paintPath();
};


#endif //FEUP_CAL_MANAGER_H

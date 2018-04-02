#ifndef FEUP_CAL_MANAGER_H
#define FEUP_CAL_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "Station.h"
#include "Graph2.h"
#include "Graph.h"

class Manager {

private:
    static vector<Station>  myStation;
    static vector<Line> myLine;
/**
	 * Construtor default.
	 */
    Manager();
public:

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

    static void mainMenu();

	static Graph * parseGraphForPrice(Graph2 graph);
};


#endif //FEUP_CAL_MANAGER_H

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
#include "Graph2.h"
#include "Graph.h"

class Manager {

private:
    static vector<Station>  myStation;
    static vector<Line> myLine;
	static Graph2 graph;

	GraphViewer *gv;
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

	static int chooseDestination();
	static int chooseOrigin();

	static bool VerifyChoice(int id, vector<Station> stations);

	static Graph * parseGraphForPrice(Graph2 graph);
	static Graph * parseGraphForDistance(Graph2 graph);

    Graph *parseGraphForTime(Graph2 graph);

	void initGv(GraphViewer *gv);
	void printGraph(GraphViewer *gv, Graph2 graph);
	void paintPath();
};


#endif //FEUP_CAL_MANAGER_H

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


class Manager {

private:

    vector<Station>  myStation;
    vector<Link> myLink;
    vector<Line> myLine;

    GraphViewer *graph;

public:

    Manager();

    ~Manager();

    /**
     * A function that loads the data from the station file, creating objects of the Station class and adding to the respective vertex in myStation.
     */
    void loadStations();

    /**
     * Function that loads the data from the edge file into the structures in Graph.h.
     */
    void loadLinks();

	/**
	* Function that loads the data from the lines file into the structures in Graph.h.
	*/
	void loadLines();

    /**
	* Function that loads the data from the stops file into the structures in Graph.h.
	*/
    void loadStops();


    /**
	* Function that loads all the data.
	*/
    void loadData();
};


#endif //FEUP_CAL_MANAGER_H

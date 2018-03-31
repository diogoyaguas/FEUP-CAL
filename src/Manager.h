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

    static Manager* singleton_instance;
    vector<Station>  myStation;
    vector<Line> myLine;

    GraphViewer *graph;

public:

    /**
	 * Construtor default.
	 */
    Manager();

    /**
	 * Destrutor default.
	 */
    ~Manager();

    static Manager* instance() {
        if (!singleton_instance)
            singleton_instance = new Manager;

        return singleton_instance;
    }


    /**
     * A function that loads the data from the station file, creating objects of the Station class and adding to the respective vertex in myStation.
     */
    void loadStations();

    /**
     * Function that loads the data from the links file into the structures in Graph.h.
     */
    void loadLinks();

	/**
	* Function that loads the data from the lines file into the structures in Graph.h.
	*/
	void loadLines();

    /**
	* Function that loads all the data.
	*/
    void loadData();

    void mainMenu();
};


#endif //FEUP_CAL_MANAGER_H

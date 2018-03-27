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

    Graph<Station> myStation;
    vector<Station> vecStation;

    GraphViewer *graph;

public:

    Manager();

    ~Manager();

    /**
     * A function that loads the data from the node file, creating objects of the Station class and adding to the respective vertex in myStation.
     */
    void loadStations();

    /**
     * Function that loads the data from the edge file into the structures in Graph.h.
     */
    void loadEdges();

};


#endif //FEUP_CAL_MANAGER_H

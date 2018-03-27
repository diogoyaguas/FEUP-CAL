//
// Created by diogo on 27/03/2018.
//

#include "Manager.h"

Manager::Manager() {

}

Manager::~Manager() {

}

void Manager::loadStations() {

    string line;

    ifstream file("Stations.txt");

    if (file.is_open()) {
        while (getline(file, line)) {

            stringstream linestream(line);
            string data;

            int id;
            int x;
            int y;
            string name;

            linestream >> id;

            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> x;
            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> y;
            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> name;

            Station station = Station(id, x, y, name);

            myStation.addVertex(station);
        }

        file.close();
    } else {
        cerr << "n File not found!\n";
    }
    return;
}

void Manager::loadEdges() {

    string line;

    ifstream file("edges.txt");

    if (file.is_open()) {
        while (getline(file, line)) {

            std::stringstream linestream(line);
            string data;

            int idEdge;
            int idOriginStation;
            int idEndStation;

            linestream >> idEdge;

            std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> idOriginStation;
            std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> idEndStation;

            Station n;
            Station StationInit;
            Station StationFinal;

            for (unsigned int i = 0; i < myStation.getVertexSet().size(); i++) {

                if (idOriginStation == myStation.getVertexSet().at(i)->getInfo().getID())
                    StationInit = myStation.getVertexSet().at(i)->getInfo();

                if (idEndStation == myStation.getVertexSet().at(i)->getInfo().getID()) {
                    StationFinal = myStation.getVertexSet().at(i)->getInfo();
                }
            }

            double weight;
            weight = sqrt(pow(StationFinal.getX() - StationInit.getX(), 2)
                    + pow(StationFinal.getY() - StationInit.getY(), 2));
            myStation.addEdge(StationInit, StationFinal, weight);

        }

        file.close();
    } else {
        cerr << "e File not found!\n";
    }
    return;
}

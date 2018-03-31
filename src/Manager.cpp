
#include <cmath>
#include "Manager.h"

Manager::Manager() {

}

Manager::~Manager() {

}

void Manager::loadStations() {

    string line;

    ifstream file("stations.txt");

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

            myStation.push_back(station);
        }

        file.close();
    } else {
        cerr << "n File not found!\n";
    }
}

void Manager::loadLines() {

	string line;

	ifstream file("lines.txt");

	if (file.is_open()) {
		while (getline(file, line)) {

			stringstream linestream(line);
			string data;

			LineID lineId;
			vector<int> stopsId;
			int stopID;

			linestream >> lineId.lineID;
			getline(linestream, data, ';');
			linestream >> lineId.type;

			while (!data.empty()) {
				getline(linestream, data, ';'); // read up-to the first ; (discard ;).
				linestream >> stopID;
				stopsId.push_back(stopID);
				
			}
            auto lines = Line(lineId, stopsId);
            myLine.push_back(lines);

		}

		file.close();
	}
	else {
		cerr << "n File not found!\n";
	}
}

void Manager::loadLinks() {

    string line;

    ifstream file("links.txt");

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

            for (unsigned int i = 0; i < myStation.size(); i++) {

                if (idOriginStation == myStation.at(i).getID())
                    StationInit = myStation.at(i);

                if (idEndStation == myStation.at(i).getID()) {
                    StationFinal = myStation..at(i);
                }
            }

            double weight;
            weight = sqrt(pow(StationFinal.getX() - StationInit.getX(), 2)
                    + pow(StationFinal.getY() - StationInit.getY(), 2));



        }

        file.close();
    } else {
        cerr << "e File not found!\n";
    }
}

void Manager::loadStops() {

}


void Manager::loadData() {
    loadStations();
    loadLinks();
    loadLines();
}



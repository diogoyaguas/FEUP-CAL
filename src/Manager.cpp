#include "Manager.h"

Manager::Manager() = default;

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

            LineID lineId{};
            vector<int> stopsId;
            int stopID;
            int timeToStation;
            int idOriginStation;
            int idEndStation;

            linestream >> lineId.lineID;
            getline(linestream, data, ';');
            linestream >> lineId.type;

            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> stopID;
            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> timeToStation;

            stopsId.push_back(stopID);
            Stop stop = Stop(lineId, timeToStation);

            for (auto station: myStation) {

                if (station.getID() == stopID) {
                    station.addStop(stop);
                }
            }

            while (!data.empty()) {

                idOriginStation = stopID;
                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> idEndStation;
                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> timeToStation;

                for (auto origin: myStation) {

                    if (idOriginStation == origin.getID()) {

                        for (auto final: myStation) {

                            if (idEndStation == final.getID()) {

                                origin.addLinkTo(&final, lineId);
                            }
                        }
                    }
                }

                stopID = idEndStation;

                stopsId.push_back(stopID);
                stop= Stop(lineId, timeToStation);

                for (auto station: myStation) {

                    if (station.getID() == stopID) {

                        station.addStop(stop);
                    }
                }

            }
            auto lines = Line(lineId, stopsId);
            myLine.push_back(lines);

        }
        file.close();
    } else {
        cerr << "n File not found!\n";
    }
}

void Manager::loadData() {
    loadStations();
    loadLines();
}

void Manager::mainMenu() {

    string origin, destination;

    cout << "Where are you ?" << endl << "::: ";
    cin >> origin;
    cout << "Where do you want to go" << endl << "::: ";
    cin >> destination;

}

Graph * Manager::parseGraphForPrice(Graph2 graph)
{
	return nullptr;
}

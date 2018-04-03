#include "Manager.h"

Manager::Manager() = default;

vector<Station> Manager::myStation = {};
vector<Line> Manager::myLine = {};

void Manager::loadStations() {

    string line;

    ifstream file("../src/stations.txt");

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
        cerr << "File not found!\n";
    }
}

void Manager::loadLines() {

    string line;

    ifstream file("../src/lines.txt");

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
                stop = Stop(lineId, timeToStation);

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
        cerr << "File not found!\n";
    }
}

void Manager::loadData() {
    loadStations();
    loadLines();
}


bool Manager::VerifyChoice(int id, vector<Station*> &stations) {

	for (auto station : stations) {

		if (station->getID() == id) {
			return true;
		}
		
	}
	return false;
}


int Manager::chooseOrigin() {

	int origin;
	Graph2* graph = new Graph2();

	vector<Station*> stations = graph->getStations();

	cout << "STATIONS:" << endl << endl;
	for (auto station : stations) {

		cout << station->getID() << " - " << station->getName() << endl;

	}

    cout << "Where are you ? (Choose the id of the station)" << endl << "::: Id - ";
	cin >> origin;
	while (!VerifyChoice(origin, stations)) {
		cout << endl << "# Invalid id. Please select again: ";
		cin >> origin;
	}

	return origin;

}

int Manager::chooseDestination() {
	int destination;
	Graph2* graph = new Graph2();

	vector<Station*> stations = graph->getStations();

	cout << "Where do you want to go ? (Choose the id of the station) " << endl << "::: Id - ";
	cin >> destination;
	while (!VerifyChoice(destination, stations)) {
		cout << endl << "# Invalid id. Please select again: ";
		cin >> destination;
	}

	return destination;

}

Graph * Manager::parseGraphForPrice(Graph2 graph)
{
	Graph* newGraph = new Graph();

    vector<Station *> stations = graph.getStations();

    for (size_t i = 0; i < stations.size(); i++) {
        newGraph->addVertex(stations[i]->getID());
    }

    for (size_t i = 0; i < stations.size(); i++) {
        Station *station = stations[i];
        vector<Link> links = station->getConnections();
        for (size_t j = 0; j < links.size(); j++) {
            newGraph->addEdge(station->getID(), links[j].getDest()->getID(), 1);
        }
    }

    return newGraph;
}

Graph *Manager::parseGraphForDistance(Graph2 graph) {
    Graph *newGraph = new Graph();

    vector<Station *> stations = graph.getStations();

    for (size_t i = 0; i < stations.size(); i++) {
        newGraph->addVertex(stations[i]->getID());
    }

    for (size_t i = 0; i < stations.size(); i++) {
        Station *station = stations[i];
        vector<Link> links = station->getConnections();
        for (size_t j = 0; j < links.size(); j++) {
            newGraph->addEdge(station->getID(), links[j].getDest()->getID(), station->getDistTo(links[j].getDest()));
        }
    }


    return newGraph;
}
/*
Graph *Manager::parseGraphForTime(Graph2 graph) {

    int id = 0;
    double time;

    auto *newGraph = new Graph();

    for (auto s: graph.getStations()) {

        newGraph->addVertex(s->getID());

    }

    for (auto s: graph.getStations()) {

        for (auto st: s->getStops()) {

            do{
                id++;
            } while(!newGraph->addVertex(id));
            newGraph->addEdge(id, s->getID(), st.getTimeToStation());

        }
    }

    for (auto s: graph.getStations()) {

        for (auto st: s->getStops()) {

            for (auto l: s->getConnections()) {

                if (st.getLineID().lineID == l.getLineID().lineID) {

                    time = s->calculateDistanceTo(l.getDest()) / l.getTravelSpeed();
                    newGraph->addEdge(id, l.getDestination().get, time);
                }
            }

            id++;
        }
    }

    return newGraph;
}*/

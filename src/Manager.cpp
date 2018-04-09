#include "Manager.h"

Manager::Manager() = default;

vector<Station> Manager::myStation = {};
vector<Line> Manager::myLine = {};
Graph<string> Manager::graph = {};

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

            Station station = Station(to_string(id), x, y, name);

            myStation.push_back(station);
            graph.addVertex(to_string(id), x, y);
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
            vector<string> stopsId;

            string temp;
            string stopID;
            Stop stop;
            int timeToStation;
            string idOriginStation;

            linestream >> lineId.lineID;
            getline(linestream, data, ';');
            linestream >> lineId.type;

            while (!data.empty()) {

                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> stopID;
                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> timeToStation;

                stopID = to_string(lineId.lineID) + to_string(lineId.type) + stopID;
                stopsId.push_back(stopID);
                stop = Stop(stopID, lineId, timeToStation);

                for (auto station: myStation) {

                    if (station.getID() == stopID) {
                        station.addStop(stop);
                        graph.addVertex(stopID, station.getX(), station.getY());
                        graph.addEdge(station.getID(), stopID);
                        graph.addEdge(stopID, station.getID());
                    }
                }

                if (!data.empty()) {
                    temp = data;
                    idOriginStation = stopID;

                    getline(linestream, temp, ';'); // read up-to the first ; (discard ;).
                    linestream >> stopID;
                    getline(linestream, temp, ';'); // read up-to the first ; (discard ;).
                    linestream >> timeToStation;

                    stopID = to_string(lineId.lineID) + to_string(lineId.type) + stopID;
                    graph.addEdge(idOriginStation, stopID);
                    graph.addEdge(stopID, idOriginStation);
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

bool Manager::VerifyChoice(string id, vector<Station> stations) {

    for (auto station : stations) {

        if (station.getID() == id) {
            return true;
        }

    }
    return false;
}


string Manager::chooseOrigin() {

    string origin;

    vector<Station> stations = myStation;

    cout << "STATIONS:" << endl << endl;
    for (auto station : stations) {

        cout << station.getID() << " - " << station.getName() << endl;

    }

    cout << "\nWhere are you ? (Choose the id of the station)" << endl << "::: ";
    cin >> origin;
    while (!VerifyChoice(origin, stations)) {
        cout << endl << "# Invalid id. Please select again: ";
        cin >> origin;
    }

    return origin;

}

string Manager::chooseDestination() {
    string destination;

    vector<Station> stations = myStation;

    cout << "Where do you want to go ? (Choose the id of the station) " << endl << "::: ";
    cin >> destination;
    while (!VerifyChoice(destination, stations)) {
        cout << endl << "# Invalid id. Please select again: ";
        cin >> destination;
    }

    return destination;

}

/*

void Manager::paintPath(vector<Node> path) {
	
	
	//Ainda nao sei como fazer, com o caminho que vai ter de percorrer ja feito, temos de o percorrer e colocar cada
	//aresta a verde
	
	

	for (size_t i = 0; i < path.size() - 1; i++) {
		int id = path.at(i).getID() * 1000 + path.at(i + 1).getID(); //nao percebo muito bem esta parte

		gv->setEdgeThickness(id, 4);
		gv->setEdgeColor(id, GREEN);
	}


	gv->rearrange();
	

} */
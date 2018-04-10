#include "Manager.h"

Manager::Manager() = default;

vector<Station> Manager::myStation;
vector<Line> Manager::myLine = {};
Graph<string> Manager::graphDistance = {};
Graph<string> Manager::graphTime = {};
Graph<string> Manager::graphPrice = {};
Graph<string> Manager::graphTranshipment = {};

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
            graphDistance.addVertex(to_string(id), x, y);
            graphTime.addVertex(to_string(id), x, y);
            graphPrice.addVertex(to_string(id), x, y);
            graphTranshipment.addVertex(to_string(id), x, y);
        }

        file.close();
    } else {
        cerr << "File not found!\n";
    }
}

void Manager::loadStops() {

    string line;

    ifstream file("../src/lines.txt");

    if (file.is_open()) {
        while (getline(file, line)) {

            stringstream linestream(line);
            string data;

            LineID lineId{};
            vector<string> stopsId;
            vector<Stop> stops;

            string stopID;
            string idStop;
            string idOriginStation;
            Stop stop;
            int timeToStation;
            int id;

            linestream >> lineId.lineID;
            getline(linestream, data, ';');
            linestream >> lineId.type;

            while (linestream.rdbuf()->in_avail() != 0) {

                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> id;
                idStop = to_string(id);

                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> timeToStation;

                stopID = to_string(lineId.lineID) + lineId.type + to_string(id);
                stopsId.push_back(stopID);
                stop = Stop(stopID, lineId, timeToStation);

                for (auto &station: myStation) {

                    if (station.getID() == idStop) {
                        station.addStop(stop);
                        graphDistance.addVertex(stopID, station.getX(), station.getY());
                        graphTime.addVertex(stopID, station.getX(), station.getY());
                        graphPrice.addVertex(stopID, station.getX(), station.getY());

                        graphDistance.addEdge(station.getID(), stopID, 'd');
                        graphDistance.addEdge(stopID, station.getID(), 'd');

                        graphTime.addEdgeTime(station.getID(), stopID, stop.getTimeToStation());
                        graphTime.addEdgeTime(stopID, station.getID(), stop.getTimeToStation());

                        graphPrice.addEdgePrice(station.getID(), stopID, 0);
                        graphPrice.addEdgePrice(stopID, station.getID(), 0);

                        graphTranshipment.addEdgeTranshipment(station.getID(), stopID, 0.5);
                        graphTranshipment.addEdgeTranshipment(stopID, station.getID(), 0.5);

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

void Manager::loadLines() {

    string line;

    ifstream file("../src/lines.txt");

    if (file.is_open()) {
        while (getline(file, line)) {

            stringstream linestream(line);
            string data;

            LineID lineId{};
            vector<string> stopsId;

            string stopID;
            string idStop;
            string idOriginStation;
            Stop stop;
            int timeToStation;
            int id;

            linestream >> lineId.lineID;
            getline(linestream, data, ';');
            linestream >> lineId.type;

            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> id;
            idStop = to_string(id);
            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> timeToStation;

            stopID = to_string(lineId.lineID) + lineId.type + to_string(id);

            while (linestream.rdbuf()->in_avail() != 0) {

                idOriginStation = stopID;

                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> id;
                idStop = to_string(id);
                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> timeToStation;

                stopID = to_string(lineId.lineID) + lineId.type + to_string(id);

                graphDistance.addEdge(idOriginStation, stopID, 'd');
                graphDistance.addEdge(stopID, idOriginStation, 'd');

                graphTime.addEdge(idOriginStation, stopID, 't');
                graphTime.addEdge(stopID, idOriginStation, 't');

                graphPrice.addEdge(idOriginStation, stopID, 'p');
                graphPrice.addEdge(stopID, idOriginStation, 'p');

                graphTranshipment.addEdgeTranshipment(idOriginStation, stopID, 0);
                graphTranshipment.addEdgeTranshipment(stopID, idOriginStation, 0);

            }
        }

        file.close();
    } else {
        cerr << "File not found!\n";
    }

}

void Manager::loadData() {
    loadStations();
    loadStops();
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

void Manager::chooseShorterPath(const string &origin, const string &destination) {

    graphDistance.dijkstraShortestPath(origin);
    vector<string> path = graphDistance.getPath(origin, destination);
    string name;
    Station station;

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: " << findStation(destination).getName()
         << endl << endl;


    for (const auto &i : path) {

        if (is_digits(i)) {
            station = findStation(i);
            cout << station.getName() << ": " << endl;
        } else {

            station = findStop(i);
            cout << "\t" << station.getName() << " | " << getTransport(i) << " on line " << getLine(station, i) << endl;
        }
    }


}

void Manager::chooseFastestPath(const string &origin, const string &destination) {

    graphTime.dijkstraShortestPath(origin);
    vector<string> path = graphTime.getPath(origin, destination);
    string name;
    Station station;

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: " << findStation(destination).getName()
         << endl << endl;

    for (const auto &i : path) {

        if (is_digits(i)) {
            station = findStation(i);
            cout << station.getName() << ": " << endl;
        } else {

            station = findStop(i);
            cout << "\t" << station.getName() << " | " << getTransport(i) << " on line " << getLine(station, i) << endl;
        }
    }
}

void Manager::chooseCheaperPath(const string &origin, const string &destination) {

    graphPrice.dijkstraShortestPath(origin);
    vector<string> path = graphPrice.getPath(origin, destination);
    string name;
    Station station;

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: " << findStation(destination).getName()
         << endl << endl;

    for (const auto &i : path) {

        if (is_digits(i)) {
            station = findStation(i);
            cout << station.getName() << ": " << endl;
        } else {

            station = findStop(i);
            cout << "\t" << station.getName() << " | " << getTransport(i) << " on line " << getLine(station, i) << endl;
        }
    }

}

void Manager::chooseLessTranshipmentPath(const string &origin, const string &destination) {

    graphTranshipment.dijkstraShortestPath(origin);
    vector<string> path = graphTranshipment.getPath(origin, destination);
    string name;
    Station station;

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: " << findStation(destination).getName()
         << endl << endl;

    for (const auto &i : path) {

        if (is_digits(i)) {
            station = findStation(i);
            cout << station.getName() << ": " << endl;
        } else {

            station = findStop(i);
            cout << "\t" << station.getName() << " | " << getTransport(i) << " on line " << getLine(station, i) << endl;
        }
    }


}

Station Manager::findStation(const string &id) {

    for (Station s: getStation()) {

        if (s.getID() == id) {

            return s;
        }
    }

}



    Station Manager::findStop(const string &id) {

        for (auto s: getStation()) {

            for (auto p: s.getStops()) {

                if (p.getStopID() == id) {

                    return s;
                }
            }
        }
    }

    bool Manager::is_digits(const std::string &str) {
        return str.find_first_not_of("0123456789") == std::string::npos;
    }

    string Manager::chooseOrigin() {

        string origin;

        vector<Station> stations = getStation();

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

        vector<Station> stations = getStation();

        cout << "Where do you want to go ? (Choose the id of the station) " << endl << "::: ";
        cin >> destination;
        while (!VerifyChoice(destination, stations)) {
            cout << endl << "# Invalid id. Please select again: ";
            cin >> destination;
        }

        return destination;

    }

    string Manager::getTransport(const string &id) {

        if (id.find('a') != string::npos) {

            return "bus";
        } else if (id.find('b') != string::npos) {

            return "subway";
        } else if (id.find('c') != string::npos) {

            return "train";
        } else return "";
    }

    int Manager::getLine(Station s, const string &id) {

        for (auto p: s.getStops()) {

            if (id == p.getStopID()) {

                return p.getLineID().lineID;
            }
        }
    }


    void Manager::initGv(GraphViewer *gv) {

        gv->createWindow(800, 800);
        gv->defineEdgeColor("gray");

        gv->defineVertexColor("yellow");

    }

    void Manager::printGraph(GraphViewer *gv) {


        for (auto station :  getStation()) {

            int id = stoi(station.getID());
            int x = station.getX();
            int y = station.getY();

            gv->setVertexLabel(id, station.getName());
            gv->addNode(id, x, y);

        }


        for(auto station :getStation()){

             int idOrigin = stoi(station.getID());

             for (auto link : station.getConnections()) {

                 int idDest = stoi(link.getDest()->getID());
                 int lineID = link.getLineID().lineID;

                 gv->addEdge(lineID, idOrigin, idDest, EdgeType::UNDIRECTED);
             }



         }




        gv->rearrange();
    }


/*
void Manager::paintPath(vector<string> path, GraphViewer *gv) {
	
	
	//Ainda nao sei como fazer, com o caminho que vai ter de percorrer ja feito, temos de o percorrer e colocar cada
	//aresta a verde


	for (size_t i = 0; i < path.size() - 1; i++) {
		string id = path.at(i);
		gv->setEdgeThickness(id, 4);
		gv->setEdgeColor(id, GREEN);
	}


	gv->rearrange();
	

}*/
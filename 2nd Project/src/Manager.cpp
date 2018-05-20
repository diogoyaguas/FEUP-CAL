#include "Manager.h"
#include <chrono>
#include <thread>
#include <iomanip>
#include <iterator>

GraphViewer *Manager::gv = new GraphViewer(600, 600, false);
vector<Station> Manager::myStation;
vector<int> Manager::myEdges;
vector<Line> Manager::myLines;
Graph<string> Manager::graphDistance = {};
Graph<string> Manager::graphTime = {};
Graph<string> Manager::graphPrice = {};
Graph<string> Manager::graphTranshipment = {};

Manager::Manager() = default;

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
            getline(linestream, name);

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
            getline(linestream, data, ';');
            getline(linestream, lineId.name, ';');

            while (linestream.rdbuf()->in_avail() != 0) {


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
                        graphTranshipment.addVertex(stopID, station.getX(), station.getY());

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

                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            }

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
            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> lineId.type;

            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            getline(linestream, lineId.name, ';');

            linestream >> id;
            idStop = to_string(id);
            getline(linestream, data, ';'); // read up-to the first ; (discard ;).
            linestream >> timeToStation;

            stopID = to_string(lineId.lineID) + lineId.type + to_string(id);
            stopsId.push_back(stopID);

            while (linestream.rdbuf()->in_avail() != 0) {

                idOriginStation = stopID;

                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> id;
                idStop = to_string(id);
                getline(linestream, data, ';'); // read up-to the first ; (discard ;).
                linestream >> timeToStation;

                stopID = to_string(lineId.lineID) + lineId.type + to_string(id);
                stopsId.push_back(stopID);

                graphDistance.addEdge(idOriginStation, stopID, 'd');
                graphDistance.addEdge(stopID, idOriginStation, 'd');

                graphTime.addEdge(idOriginStation, stopID, 't');
                graphTime.addEdge(stopID, idOriginStation, 't');

                graphPrice.addEdge(idOriginStation, stopID, 'p');
                graphPrice.addEdge(stopID, idOriginStation, 'p');

                graphTranshipment.addEdgeTranshipment(idOriginStation, stopID, 0.0);
                graphTranshipment.addEdgeTranshipment(stopID, idOriginStation, 0.0);

            }

            Line station_line = Line(lineId, stopsId);
            myLines.push_back(station_line);
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

    id = twoDigitsIdToOne(id);

    for (auto station : stations) {

        if (station.getID() == id) {
            return true;
        }

    }
    return false;
}

bool Manager::VerifyChoice(string id, vector<Line> lines) {
    for (auto line : lines) {
        if (line.getLineID().name == id) {
            return true;
        }
    }
    return false;
}

void Manager::chooseShorterPath(const string &origin, const string &destination) {

    graphDistance.dijkstraShortestPath(origin);
    vector<string> path = graphDistance.getPath(origin, destination);
    Station station;
    bool entry = false;
    int size = 0;
    double distance = graphDistance.getWeight(origin, destination);

    if (path.size() < 2) {

        cout << "<<< No path available >>>\n" << endl;
        return;
    }

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: "
         << findStation(destination).getName();

    for (unsigned int j = 0; j < path.size(); j++) {

        string i = path.at(j);
        if (is_digits(i)) {
            station = findStation(i);
            if (!entry) {
                cout << "\n\nEnter in " << station.getName() << ": \n\n";
                entry = true;
            } else if (j != path.size() - 1) {
                cout << "\nChange in " << station.getName() << ": \n\n";
            } else {

                cout << "\nYou arrived to " << station.getName() << " in " << distance / 100 << " km\n";
            }
        } else {
            station = findStop(i);
            size = station.getName().size();
            cout << setw(8 + size) << setfill(' ') << station.getName() << setw(17 - size) << setfill(' ') << " | "
                 << getTransport(i) << " on " << getLine(station, i) << "\n";
        }
    }


    paintPath(path);
    continueFunction();
    resetColors();

}

void Manager::chooseFastestPath(const string &origin, const string &destination) {

    graphTime.dijkstraShortestPath(origin);
    vector<string> path = graphTime.getPath(origin, destination);
    Station station;
    bool entry = false;
    int size = 0;
    double time = graphTime.getWeight(origin, destination);

    if (path.size() < 2) {

        cout << "<<< No path available >>>\n" << endl;
        return;
    }

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: "
         << findStation(destination).getName();

    for (unsigned int j = 0; j < path.size(); j++) {

        string i = path.at(j);
        if (is_digits(i)) {
            station = findStation(i);
            if (!entry) {
                cout << "\n\nEnter in " << station.getName() << ": \n\n";
                entry = true;
            } else if (j != path.size() - 1) {
                cout << "\nChange in " << station.getName() << ": \n\n";
            } else {

                cout << "\nYou arrived to " << station.getName() << " in " << (int) time << " minutes\n";
            }
        } else {
            station = findStop(i);
            size = station.getName().size();
            cout << setw(8 + size) << setfill(' ') << station.getName() << setw(17 - size) << setfill(' ') << " | "
                 << getTransport(i) << " on Line " << getLine(station, i) << "\n";
        }
    }

    paintPath(path);
    continueFunction();
    resetColors();

}

void Manager::chooseCheaperPath(const string &origin, const string &destination) {

    graphPrice.dijkstraShortestPath(origin);
    vector<string> path = graphPrice.getPath(origin, destination);
    Station station;
    bool entry = false;
    int size = 0;
    double euros = graphPrice.getWeight(origin, destination);

    if (path.size() < 2) {

        cout << "<<< No path available >>> \n" << endl;
        return;
    }

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: "
         << findStation(destination).getName();

    for (unsigned int j = 0; j < path.size(); j++) {

        string i = path.at(j);
        if (is_digits(i)) {
            station = findStation(i);
            if (!entry) {
                cout << "\n\nEnter in " << station.getName() << ": \n\n";
                entry = true;
            } else if (j != path.size() - 1) {
                cout << "\nChange in " << station.getName() << ": \n\n";
            } else {

                cout << "\nYou arrived to " << station.getName() << " for " << fixed << setprecision(2) << euros
                     << " euros\n";
            }
        } else {
            station = findStop(i);
            size = station.getName().size();
            cout << setw(8 + size) << setfill(' ') << station.getName() << setw(17 - size) << setfill(' ') << " | "
                 << getTransport(i) << " on Line " << getLine(station, i) << "\n";
        }
    }

    paintPath(path);
    continueFunction();
    resetColors();

}

void Manager::chooseLessTranshipmentPath(const string &origin, const string &destination) {

    graphTranshipment.dijkstraShortestPath(origin);
    vector<string> path = graphTranshipment.getPath(origin, destination);
    Station station;
    bool entry = false;
    int size = 0;
    int transhipment = 0;

    if (path.size() < 2) {

        cout << "<<< No path available >>>\n" << endl;
        return;
    }

    cout << "Origin: " << findStation(origin).getName() << endl << "Destination: "
         << findStation(destination).getName();

    for (unsigned int j = 0; j < path.size(); j++) {

        string i = path.at(j);
        if (is_digits(i)) {
            station = findStation(i);
            if (!entry) {
                cout << "\n\nEnter in " << station.getName() << ": \n\n";
                entry = true;
            } else if (j != path.size() - 1) {
                cout << "\nChange in " << station.getName() << ": \n\n";
                transhipment++;
            } else {

                cout << "\nYou arrived to " << station.getName() << " with " << transhipment << " transhipment(s)\n";
            }
        } else {
            station = findStop(i);
            size = station.getName().size();
            cout << setw(8 + size) << setfill(' ') << station.getName() << setw(17 - size) << setfill(' ') << " | "
                 << getTransport(i) << " on Line " << getLine(station, i) << "\n";
        }
    }
    paintPath(path);
    continueFunction();
    resetColors();

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

Line Manager::findLine(const string &name) {
    for (Line l : myLines) {

        if (l.getLineID().name == name) {

            return l;
        }
    }
}

const string &Manager::findIdStation(string name) {

    for (Station s: getStation()) {

        if (s.getName() == name) {

            return s.getID();
        }
    }
}

bool Manager::is_digits(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

string Manager::chooseOrigin() {

    string origin;
    vector<Station> origins;
    vector<Station> stations = getStation();

    cout << "STATIONS:" << endl << endl;
    for (auto station : stations) {

        cout << setfill('0') << setw(2) << station.getID() << " - " << station.getName() << endl;

    }

    cout << "\nWhere are you ?" << endl << "::: ";
    cin >> origin;
    if (is_digits(origin)) {
        while (!VerifyChoice(origin, stations)) {
            cout << endl << "# Invalid id. Please select again: ";
            cin >> origin;
        }

        origin = twoDigitsIdToOne(origin);

    } else {

        origins = searchExactStation(origin);
        if (origins.empty())origins = approximateStringMatchingStation(origin);
        if (origins.size() == 1) return findIdStation(origin);
        else {

            origin = chooseExactOrigin(origins);

        }
    }

    return origin;

}

string Manager::chooseOrigin(Line lineOrigin) {
    string origin;
    vector<Station> origins;
    vector<Station> stations = getStation();

    //remove stations not belonging to line
    for (auto it = stations.begin(); it != stations.end(); it++) {
        if (it->findStop(lineOrigin.getLineID()) == nullptr) {
            it = stations.erase(it);
            it--;
        }
    }

    cout << "STATIONS:" << endl << endl;
    for (auto station : stations) {

        cout << setfill('0') << setw(2) << station.getID() << " - " << station.getName() << endl;

    }

    cout << "\nWhere do you want to go ? (Choose the id of the station) " << endl << "::: ";
    cin >> origin;
    if (is_digits(origin)) {
        while (!VerifyChoice(origin, stations)) {
            cout << endl << "# Invalid id. Please select again: ";
            cin >> origin;
        }

        origin = twoDigitsIdToOne(origin);

    } else {

        origins = searchExactStation(origin, stations);
        if (origins.empty())origins = approximateStringMatchingStation(origin, stations);
        if (origins.size() == 1) return findIdStation(origin);
        else {

            origin = chooseExactOrigin(origins);

        }
    }

    return origin;
}

string Manager::chooseDestination() {
    string destination;
    vector<Station> destinations;
    vector<Station> stations = getStation();

    cout << "\nWhere do you want to go ? (Choose the id of the station) " << endl << "::: ";
    cin >> destination;
    if (is_digits(destination)) {
        while (!VerifyChoice(destination, stations)) {
            cout << endl << "# Invalid id. Please select again: ";
            cin >> destination;
        }

        destination = twoDigitsIdToOne(destination);

    } else {

        destinations = searchExactStation(destination);
        if (destinations.empty())destinations = approximateStringMatchingStation(destination);
        if (destinations.size() == 1) return findIdStation(destination);
        else {

            destination = chooseExactOrigin(destinations);

        }
    }

    return destination;

}

string Manager::chooseDestination(Line lineDestination) {
    string destination;
    vector<Station> destinations;
    vector<Station> stations = getStation();

    //remove stations not belonging to line
    for (auto it = stations.begin(); it != stations.end(); it++) {
        if (it->findStop(lineDestination.getLineID()) == nullptr) {
            it = stations.erase(it);
            it--;
        }
    }

    cout << "\nWhere do you want to go ? (Choose the id of the station) " << endl << "::: ";
    cin >> destination;
    if (is_digits(destination)) {
        while (!VerifyChoice(destination, stations)) {
            cout << endl << "# Invalid id. Please select again: ";
            cin >> destination;
        }

        destination = twoDigitsIdToOne(destination);

    } else {

        destinations = searchExactStation(destination, stations);
        if (destinations.empty())destinations = approximateStringMatchingStation(destination, stations);
        if (destinations.size() == 1) return findIdStation(destination);
        else {

            destination = chooseExactOrigin(destinations);

        }
    }

    return destination;
}

Line Manager::chooseOriginLine() {
    Line originLine;
    vector<Line> lines = myLines;
    vector<Line> results;

    string origin;

    cout << "LINES:" << endl << endl;
    for (Line line : lines) {
        LineID lineID = line.getLineID();
        cout << setfill('0') << setw(2) << lineID.lineID << " - ";
        if (lineID.type == 'a') cout << setfill('0') << " Bus ";
        else if (lineID.type == 'b') cout << setfill('0') << "Metro";
        else if (lineID.type == 'c') cout << setfill('0') << "Train";
        cout << " - " << lineID.name << endl;
    }

    cout << "\nIn what line is your departure station in?" << endl << "::: ";
    cin >> origin;

    results = searchExactLine(origin);
    if (results.empty()) results = approximateStringMatchingLine(origin);
    if (results.size() == 1) return findLine(origin);
    else {
        origin = chooseExactLineOrigin(results);
    }

    return originLine;
}

Line Manager::chooseDestinationLine() {
    Line destinationLine;
    vector<Line> results;

    string destination;

    cout << "\nIn what line is your arrival station in?" << endl << "::: ";
    cin >> destination;
    results = searchExactLine(destination);
    if (results.empty()) results = approximateStringMatchingLine(destination);
    if (results.size() == 1) return findLine(destination);
    else {
        destination = chooseExactLineOrigin(results);
    }

    return destinationLine;
}

string Manager::getTransport(const string &id) {

    if (id.find('a') != string::npos) {

        return "Bus";
    } else if (id.find('b') != string::npos) {

        return "Subway";
    } else if (id.find('c') != string::npos) {

        return "Train";
    } else return "";
}

int Manager::getLine(Station s, const string &id) {

    for (auto p: s.getStops()) {

        if (id == p.getStopID()) {

            return p.getLineID().lineID;
        }
    }
}

void Manager::printGraph() {

    gv->setBackground("res/background.png");
    gv->createWindow(800, 800);
    gv->defineEdgeCurved(false);
    gv->defineEdgeColor("grey");
    gv->defineVertexIcon("res/station.png");
    for (unsigned int i = 0; i < graphDistance.getVertexSet().size(); i++) {

        string id = graphDistance.getVertexSet().at(i)->getInfo();
        Station station;

        if (is_digits(id)) {
            station = findStation(id);
        } else station = findStop(id);

        int idt = stoi(station.getID());
        int x = station.getX();
        int y = station.getY();

        gv->setVertexLabel(idt, station.getName());
        gv->addNode(idt, 50 + 5 * x, -(y * 5) + 700);

    }

    for (unsigned int i = 0; i < graphDistance.getVertexSet().size(); i++) {

        string j = graphDistance.getVertexSet().at(i)->getInfo();

        Station station;

        if (is_digits(j)) {
            station = findStation(j);
        } else station = findStop(j);

        int idOrigin = stoi(station.getID());

        vector<Edge<string> > adj = graphDistance.getVertexSet().at(i)->getAdj();

        for (auto &k : adj) {

            string id = k.getDest()->getInfo();

            if (is_digits(id)) {
                station = findStation(id);
            } else station = findStop(id);

            int idDestination = stoi(station.getID());

            if (idOrigin == idDestination) continue;

            int idEdge = 1000 * idOrigin + idDestination;

            string weight = to_string(k.getWeight());

            if (weight.find('.') != string::npos) {
                for (size_t l = weight.find('.') + 2; l < weight.size(); l++)
                    weight.erase(l);
            }

            gv->addEdge(idEdge, idOrigin, idDestination, EdgeType::UNDIRECTED);
            myEdges.push_back(idEdge);
        }

    }

    gv->rearrange();
}

void Manager::paintPath(vector<string> path) {

    for (size_t i = 0; i < path.size() - 2; i++) {

        string j = path.at(i), k = path.at(i + 1);

        Station origin, destination;

        if (is_digits(j)) {
            origin = findStation(j);
        } else origin = findStop(j);

        if (is_digits(k)) {
            destination = findStation(k);
        } else destination = findStop(k);

        int id = stoi(origin.getID()) * 1000 + stoi(destination.getID());
        int other_id = stoi(destination.getID()) * 1000 + stoi(origin.getID());

        gv->removeEdge(other_id);
        gv->setEdgeThickness(id, 4);
        string transport = getTransport(path.at(i));
        if (transport == "Bus") gv->setEdgeColor(id, "BLUE");
        else if (transport == "Subway") gv->setEdgeColor(id, "YELLOW");
        else if (transport == "Train") gv->setEdgeColor(id, "GREEN");
    }

    gv->rearrange();

}

void Manager::resetColors() {

    for (int id : myEdges) {

        gv->removeEdge(id);

    }

    for (unsigned int i = 0; i < graphDistance.getVertexSet().size(); i++) {

        string j = graphDistance.getVertexSet().at(i)->getInfo();

        Station station;

        if (is_digits(j)) {
            station = findStation(j);
        } else station = findStop(j);

        int idOrigin = stoi(station.getID());

        vector<Edge<string> > adj = graphDistance.getVertexSet().at(i)->getAdj();

        for (auto &k : adj) {

            string id = k.getDest()->getInfo();

            if (is_digits(id)) {
                station = findStation(id);
            } else station = findStop(id);

            int idDestination = stoi(station.getID());

            if (idOrigin == idDestination) continue;

            int idEdge = 1000 * idOrigin + idDestination;

            string weight = to_string(k.getWeight());

            if (weight.find('.') != string::npos) {
                for (size_t l = weight.find('.') + 2; l < weight.size(); l++)
                    weight.erase(l);
            }

            gv->addEdge(idEdge, idOrigin, idDestination, EdgeType::UNDIRECTED);
            myEdges.push_back(idEdge);
        }

    }

    gv->rearrange();

}

void Manager::continueFunction() {

    while (true) {
        cout << "\n<<< Press enter to continue >>>" << endl;
        int ignoredChar = getchar();
        if (ignoredChar == '\n') {
            break;
        }
    }
}

vector<Station> Manager::searchExactStation(string name) {

    vector<Station> stops;

    for (auto s : myStation) {

        if (kpm(name, s.getName())) {

            stops.push_back(s);
        }
    }

    return stops;
}

vector<Station> Manager::searchExactStation(string name, vector<Station> stations) {
    vector<Station> stops;

    for (auto s : stations) {

        if (kpm(name, s.getName())) {

            stops.push_back(s);
        }
    }

    return stops;
}

vector<Line> Manager::searchExactLine(string name) {
    vector<Line> lines;

    for (auto l : myLines) {

        if (kpm(name, l.getLineID().name)) {

            lines.push_back(l);
        }
    }

    return lines;
}

void Manager::preKpm(string pattern, int f[]) {

    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++) {
        k = f[i - 1];
        while (k >= 0) {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

bool Manager::kpm(string pattern, string target) {
    int m = pattern.length();
    int n = target.length();
    auto *f = new int[m];
    preKpm(pattern, f);
    int i = 0;
    int k = 0;
    while (i < n) {
        if (k == -1) {
            i++;
            k = 0;
        } else if (target[i] == pattern[k]) {
            i++;
            k++;
            if (k == m)
                return true;
        } else
            k = f[k];
    }
    return false;
}

string Manager::chooseExactOrigin(vector<Station> exactStation) {

    string origin;

    sort(exactStation.begin(), exactStation.end(), sortStations);
    cout << "\nDid you meant to say:" << endl << endl;
    for (auto s : exactStation) {

        cout << setfill('0') << setw(2) << s.getID() << " - " << s.getName() << endl;

    }

    cout << "\nWhere are you ?" << endl << "::: ";
    cin >> origin;
    while (!VerifyChoice(origin, exactStation)) {
        cout << endl << "# Invalid id. Please select again: ";
        cin >> origin;
    }

    return origin;

}

string Manager::chooseExactLineOrigin(vector<Line> lines) {
    string origin;

    sort(lines.begin(), lines.end(), sortLines);
    cout << "\nDid you meant to say:" << endl << endl;

    for (auto l : lines) {
        if (l.getLineID().type == 'a') cout << setfill('0') << "Bus - ";
        else if (l.getLineID().type == 'b') cout << setfill('0') << "Metro - ";
        else if (l.getLineID().type == 'b') cout << setfill('0') << "Train - ";
        cout << setw(2) << l.getLineID().lineID << " - " << l.getLineID().name << endl;
    }

    cout << "\nWhere are you ?" << endl << "::: ";
    cin >> origin;
    while (!VerifyChoice(origin, lines)) {
        cout << endl << "# Invalid id. Please select again: ";
        cin >> origin;
    }

    return origin;
}

vector<Station> Manager::approximateStringMatchingStation(string name) {

    APR current;
    vector<APR> heap;
    vector<Station> topToReturn;
    for (auto s: getStation()) {
        string temp = s.getName();
        int actualValue = findApproxMatchingStrings(name, s.getName());

        current.first = actualValue;
        current.second = s;
        heap.push_back(current);
    }
    make_heap(heap.begin(), heap.end(), APR_Greater_Than());
    heap = vector<APR>(heap.begin(), heap.begin() + 5);
    for (auto &it : heap) {
        topToReturn.push_back(it.second);
    }
    return topToReturn;
}

vector<Station> Manager::approximateStringMatchingStation(string name, vector<Station> stations) {
    APR current;
    vector<APR> heap;
    vector<Station> topToReturn;
    for (auto s : stations) {
        string temp = s.getName();
        int actualValue = findApproxMatchingStrings(name, s.getName());

        current.first = actualValue;
        current.second = s;
        heap.push_back(current);
    }
    make_heap(heap.begin(), heap.end(), APR_Greater_Than());
    heap = vector<APR>(heap.begin(), heap.begin() + 5);
    for (auto &it : heap) {
        topToReturn.push_back(it.second);
    }
    return topToReturn;
}

vector<Line> Manager::approximateStringMatchingLine(string name) {
    APR2 current;
    vector<APR2> heap;
    vector<Line> topToReturn;
    for (auto l : myLines) {
        string temp = l.getLineID().name;
        int actualValue = findApproxMatchingStrings(name, l.getLineID().name);

        current.first = actualValue;
        current.second = l;
        heap.push_back(current);
    }
    make_heap(heap.begin(), heap.end(), APR2_Greater_Than());
    heap = vector<APR2>(heap.begin(), heap.begin() + 5);
    for (auto &it : heap) {
        topToReturn.push_back(it.second);
    }
    return topToReturn;
}

vector<string> Manager::manageWords(const string &sentence) {

    istringstream iss(sentence);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    if (tokens.empty()) {
        tokens.emplace_back("");
    }
    return tokens;
}

int Manager::findApproxMatchingStrings(const string &pattern, string text) {

    int totalEditDistance = 0;
    int currentEditDistance;
    int currentTotalDistance = 0;
    vector<string> textSplitted = manageWords(text);
    vector<string> patternSplitted = manageWords(pattern);
    if (textSplitted.size() != patternSplitted.size()) {
        totalEditDistance += abs((int) (textSplitted.size() - patternSplitted.size()));
    }
    for (auto &itP : patternSplitted) {
        for (auto &itT : textSplitted) {
            currentEditDistance = editDistance(itP, itT);
            if (currentEditDistance == 0) {
                currentTotalDistance = currentTotalDistance / 2;
                break;
            }
            currentTotalDistance += currentEditDistance;
        }
        totalEditDistance += currentTotalDistance;
    }

    return totalEditDistance;
}

int Manager::editDistance(string pattern, string text) {

    int n = text.length();
    vector<int> d(static_cast<unsigned int>(n + 1));
    int old, neww;
    for (int j = 0; j <= n; j++)
        d[j] = j;
    int m = pattern.length();
    for (int i = 1; i <= m; i++) {
        old = d[0];
        d[0] = i;
        for (int j = 1; j <= n; j++) {
            if (pattern[i - 1] == text[j - 1]) neww = old;
            else {
                neww = min(old, d[j]);
                neww = min(neww, d[j - 1]);
                neww = neww + 1;
            }
            old = d[j];
            d[j] = neww;
        }
    }
    return d[n];
}

bool Manager::sortStations(Station s1, Station s2) { return stoi(s1.getID()) < stoi(s2.getID()); }

bool Manager::sortLines(Line l1, Line l2) { return stoi(l1.getLineID().name) < stoi(l2.getLineID().name); }

string Manager::twoDigitsIdToOne(string id) {

    if (id.size() == 2 && id[0] == '0') {

        id = id[1];
    }

    return id;
}

vector<Line> Manager::getLinesFromStation(string name) {
    vector<Line> lines = myLines;
    Station s = findStation(name);

    for (auto it = lines.begin(); it != lines.end(); it++) {
        if (s.findStop(it->getLineID()) == nullptr) {
            it = lines.erase(it);
            it--;
        }
    }

    return lines;
}








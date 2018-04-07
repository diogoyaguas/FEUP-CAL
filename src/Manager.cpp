#include "Manager.h"

Manager::Manager() = default;

vector<Station> Manager::myStation = {};
vector<Line> Manager::myLine = {};
Graph2 Manager::graph = {};

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

bool Manager::VerifyChoice(int id, vector<Station> stations) {

	for (auto station : stations) {

		if (station.getID() == id) {
			return true;
		}
		
	}
	return false;
}

int Manager::chooseOrigin() {

	int origin;
    auto * graph = new Graph2();

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

int Manager::chooseDestination() {
	int destination;
	/*Graph2* graph = new Graph2();
	vector<Station*> stations = graph->getStations();

	so para saber como estava antes
	*/

	vector<Station> stations = myStation;

	cout << "Where do you want to go ? (Choose the id of the station) " << endl << "::: ";
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

/*Graph *Manager::parseGraphForTime(Graph2 graph) {

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
                    newGraph->addEdge(id, l.getDest()->getID(), time);
                }
            }

            id++;
        }
    }

    return newGraph;
}*/


void Manager::initGv(GraphViewer *gv) {

	gv->createWindow(800, 800);
	gv->defineEdgeColor(GRAY);
	gv->defineEdgeCurved(false);
	gv->defineVertexColor(YELLOW);
	
}


void Manager::printGraph(GraphViewer *gv, Graph2 graph) {
	
	for (auto station : graph.getStations())
	{
		int stationID = station->getID();
		int x = station->getX();
		int y = station->getY();
		string name = station->getName();
		
		gv->addNode(stationID, x, y);
		gv->setVertexLabel(stationID, to_string(stationID));
	}

	for (auto link : graph.getLinks()) {

		int idLine = link.getLineID().lineID;
		int idSource = link.getIdSource();
		int idDest = link.getIdDest();

		gv->addEdge(idLine, idSource, idDest, EdgeType::DIRECTED);

		/*Basicamente no graph2 cada vez que se adiciona um link, estou a guardar num vector de links o id da linha, o
		* id da partida e o id do destino, para criar a aresta no graphviewer percorro o vector de links e adiciono cada aresta
		* nao sei se esta bem nem posso testar para ja, digam-me se concordam 
		*/

	}



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
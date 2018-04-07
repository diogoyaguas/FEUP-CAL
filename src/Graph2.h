#ifndef FEUP_CAL_GRAPH_H_
#define FEUP_CAL_GRAPH_H_

#include "Station.h"
#include <vector>

class Graph2
{
	vector<Station*> stationSet;
	vector<Link> links; //arestas necessarias para adicionar ao grafico, nao sei se e a melhor maneira, mas foi o que arranjei
	Station *findStation(const int &stationID) const;
public:
	Graph2();
	~Graph2();

	int getNumStations() const;
	bool addStation(Station* station);
	bool removeStation(Station* station);
	bool addLink(LineID lineID, Station* source, Station* dest);
	bool removeLink(Station* source, Station* dest, LineID lineID);

	void calculateBaseTimeWeights();
	void dijkstraTimePath(const int &stationID);
	vector<Station*> getTimePath();
	vector<Station*> getStations();
    void setStation(vector<Station*> station);
	vector<Link> getLinks();
};


#endif

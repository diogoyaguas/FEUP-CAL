/*
* Graph.h
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

class Edge;
class Graph;
class Vertex;


/****************** Provided structures  ********************/


class Vertex {
	int nodeID;                // contents
	vector<Edge> adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	void addEdge(Vertex *dest, double w);
	bool removeEdgeTo(Vertex *d);
public:
	Vertex(int in);
	friend class Graph;
};


class Edge {
	Vertex * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex *d, double w);
	friend class Graph;
	friend class Vertex;
};


class Graph {
	vector<Vertex*> vertexSet;    // vertex set

	void dfsVisit(Vertex *v, vector<int> & res) const;
	Vertex *findVertex(const int &in) const;
	bool dfsIsDAG(Vertex *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const int &in);
	bool removeVertex(const int &in);
	bool addEdge(const int &sourc, const int &dest, double w);
	bool removeEdge(const int &sourc, const int &dest);
	vector<int> dfs() const;
	vector<int> bfs(const int &source) const;
	vector<int> topsort() const;
	int maxNewChildren(const int &source, int &inf) const;
	bool isDAG() const;
};

#endif /* GRAPH_H_ */
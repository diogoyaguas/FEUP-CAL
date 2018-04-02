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

/****************** Provided constructors and functions ********************/


Vertex::Vertex(int in) : nodeID(in) {}

Edge::Edge(Vertex *d, double w) : dest(d), weight(w) {}


int Graph::getNumVertex() const {
	return vertexSet.size();
}

/*
* Auxiliary function to find a vertex with a given content.
*/
Vertex * Graph::findVertex(const int &in) const {
	for (auto v : vertexSet)
		if (v->nodeID == in)
			return v;
	return NULL;
}

/****************** 1a) addVertex ********************/

/*
*  Adds a vertex with a given content or info (in) to a graph (this).
*  Returns true if successful, and false if a vertex with that content already exists.
*/
bool Graph::addVertex(const int &in) {
	if (findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in));
	return true;
}

/****************** 1b) addEdge ********************/

/*
* Adds an edge to a graph (this), given the contents of the source and
* destination vertices and the edge weight (w).
* Returns true if successful, and false if the source or destination vertex does not exist.
*/
bool Graph::addEdge(const int &sourc, const int &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w);
	return true;
}

/*
* Auxiliary function to add an outgoing edge to a vertex (this),
* with a given destination vertex (d) and edge weight (w).
*/
void Vertex::addEdge(Vertex *d, double w) {
	adj.push_back(Edge(d, w));
}


/****************** 1c) removeEdge ********************/

/*
* Removes an edge from a graph (this).
* The edge is identified by the source (sourc) and destination (dest) contents.
* Returns true if successful, and false if such edge does not exist.
*/
bool Graph::removeEdge(const int &sourc, const int &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

/*
* Auxiliary function to remove an outgoing edge (with a given destination (d))
* from a vertex (this).
* Returns true if successful, and false if such edge does not exist.
*/
bool Vertex::removeEdgeTo(Vertex *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
	return false;
}


/****************** 1d) removeVertex ********************/

/*
*  Removes a vertex with a given content (in) from a graph (this), and
*  all outgoing and incoming edges.
*  Returns true if successful, and false if such vertex does not exist.
*/
bool Graph::removeVertex(const int &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->nodeID == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}


/****************** 2a) dfs ********************/

/*
* Performs a depth-first search (dfs) in a graph (this).
* Returns a vector with the contents of the vertices by dfs order.
* Follows the algorithm described in theoretical classes.
*/
vector<int> Graph::dfs() const {
	vector<int> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
		if (!v->visited)
			dfsVisit(v, res);
	return res;
}

/*
* Auxiliary function that visits a vertex (v) and its adjacent, recursively.
* Updates a parameter with the list of visited node contents.
*/
void Graph::dfsVisit(Vertex *v, vector<int> & res) const {
	v->visited = true;
	res.push_back(v->nodeID);
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (!w->visited)
			dfsVisit(w, res);
	}
}

/****************** 2b) bfs ********************/

/*
* Performs a breadth-first search (bfs) in a graph (this), starting
* from the vertex with the given source contents (source).
* Returns a vector with the contents of the vertices by dfs order.
* Follows the algorithm described in theoretical classes.
*/
vector<int> Graph::bfs(const int & source) const {
	vector<int> res;
	auto s = findVertex(source);
	if (s == NULL)
		return res;
	queue<Vertex *> q;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->nodeID);
		for (auto & e : v->adj) {
			auto w = e.dest;
			if (!w->visited) {
				q.push(w);
				w->visited = true;
			}
		}
	}
	return res;
}

/****************** 2c) toposort ********************/

/*
* Performs a topological sorting of the vertices of a graph (this).
* Returns a vector with the contents of the vertices by topological order.
* If the graph has cycles, returns an empty vector.
* Follows the algorithm described in theoretical classes.
*/

vector<int> Graph::topsort() const {
	vector<int> res;

	for (auto v : vertexSet)
		v->indegree = 0;
	for (auto v : vertexSet)
		for (auto & e : v->adj)
			e.dest->indegree++;

	queue<Vertex*> q;
	for (auto v : vertexSet)
		if (v->indegree == 0)
			q.push(v);

	while (!q.empty()) {
		Vertex* v = q.front();
		q.pop();
		res.push_back(v->nodeID);
		for (auto & e : v->adj) {
			auto w = e.dest;
			w->indegree--;
			if (w->indegree == 0)
				q.push(w);
		}
	}

	if (res.size() != vertexSet.size()) {
		cout << "Ordenacao Impossivel!" << endl;
		res.clear();
		return res;
	}

	return res;
}

/****************** 3a) maxNewChildren  ********************/

/*
* Performs a breadth-first search in a graph (this), starting
* from the vertex with the given source contents (source).
* During the search, determines the vertex that has a maximum number
* of new children (adjacent not previously visited), and returns the
* contents of that vertex and the number of new children.
*/

int Graph::maxNewChildren(const int & source, int &inf) const {
	auto s = findVertex(source);
	if (s == NULL)
		return 0;
	queue<Vertex *> q;
	int maxChildren = 0;
	inf = s->nodeID;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		int nChildren = 0;
		for (auto & e : v->adj) {
			auto w = e.dest;
			if (!w->visited) {
				w->visited = true;
				q.push(w);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v->nodeID;
		}
	}
	return maxChildren;
}

/****************** 3a) isDAG  ********************/

/*
* Performs a depth-first search in a graph (this), to determine if the graph
* is acyclic (acyclic directed graph or DAG).
* During the search, a cycle is found if an edge connects to a vertex
* that is being processed in the the stack of recursive calls (see theoretical classes).
* Returns true if the graph is acyclic, and false otherwise.
*/

bool Graph::isDAG() const {
	for (auto v : vertexSet) {
		v->visited = false;
		v->processing = false;
	}
	for (auto v : vertexSet)
		if (!v->visited)
			if (!dfsIsDAG(v))
				return false;
	return true;
}

/**
* Auxiliary function that visits a vertex (v) and its adjacent, recursively.
* Returns false (not acyclic) if an edge to a vertex in the stack is found.
*/
bool Graph::dfsIsDAG(Vertex *v) const {
	v->visited = true;
	v->processing = true;
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (w->processing)
			return false;
		if (!w->visited)
			if (!dfsIsDAG(w))
				return false;
	}
	v->processing = false;
	return true;
}

#endif /* GRAPH_H_ */
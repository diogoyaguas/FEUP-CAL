#ifndef GRAPH_H_
#define GRAPH_H_

#include "MutablePriorityQueue.h"
#include <cctype>
#include <algorithm>

#undef max

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;

const double busSpeed = 1800.0;
const double metroSpeed = 10000.0;
const double trainSpeed = 1800.0;

/*
 * ************************************************
 * 					  VERTEX					  *
 * ************************************************
 */

template<class T>
class Vertex {
    T info;
    vector<Edge<T> > adj;
    int xCoordinate, yCoordinate;
    bool visited;
    bool processing;
    int indegree;

    double dist = 0;
    Vertex<T> *path = nullptr;
    int queueIndex = 0;        // required by MutablePriorityQueue

    void addEdge(Vertex<T> *dest, double w);

    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in, int xCo, int yCo);

    bool operator<(Vertex<T> &vertex) const; // // required by MutablePriorityQueue

    T getInfo() const;

    T *getInfoPointer() {
        return &info;
    }

    int getIndegree() const;

    double getDist() const;

    int getXCoordinate() const;

    int getYCoordinate() const;

    Vertex *getPath() const;

    vector<Edge<T> > getAdj() const;

    void setDist(double d);

    void setPath(Vertex<T> *vert);

    void setInfo(T info);

    void showVertexInfo() const;

    friend class Graph<T>;

    friend class MutablePriorityQueue<Vertex<T>>;
};

template<class T>
Vertex<T>::Vertex(T in, int xCo, int yCo) :
        info(in), xCoordinate(xCo), yCoordinate(yCo) {
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template<class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const {
    return this->dist < vertex.dist;
}

template<class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template<class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template<class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template<class T>
vector<Edge<T> > Vertex<T>::getAdj() const {
    return this->adj;
}

template<class T>
int Vertex<T>::getIndegree() const {
    return this->indegree;
}

template<class T>
int Vertex<T>::getXCoordinate() const {

    return this->xCoordinate;
}

template<class T>
int Vertex<T>::getYCoordinate() const {

    return this->yCoordinate;
}

template<class T>
void Vertex<T>::setDist(double d) {
    this->dist = d;
}

template<class T>
void Vertex<T>::setPath(Vertex<T> *vert) {
    this->path = vert;
}

template<class T>
void Vertex<T>::setInfo(T info) {
    this->info = info;
}

template<class T>
void Vertex<T>::showVertexInfo() const {

    cout << "Node nº " << to_string(this->info) << endl;
    cout << "\t -Coordinate x: " << to_string(this->xCoordinate) << endl;
    cout << "\t -Coordinate y: " << to_string(this->yCoordinate) << endl;
    cout << "\t -All Adjacent Nodes: ";

    if (this->adj.size() == 0)
        cout << "No Adjacent Nodes to this Node\n";
    else {
        for (size_t t = 0; t < this->adj.size(); t++) {

            if (t == this->adj.size() - 1)
                cout << to_string(this->adj.at(t).dest->info);
            else
                cout << to_string(this->adj.at(t).dest->info) << ", ";
        }
    }
    cout << endl;
}

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {

    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest == d) {
            adj.erase(it);
            return true;
        }

    return false;
}

/*
 * ************************************************
 * 					  EDGE  					  *
 * ************************************************
 */

template<class T>
class Edge {
    Vertex<T> *dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);

    friend class Graph<T>;

    friend class Vertex<T>;

    double getWeight() const {
        return weight;
    }

    Vertex<T> *getDest() const {

        return this->dest;
    }

    void setWeight(double w) {
        weight = w;
    }

};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
        dest(d), weight(w) {
}

/*
 * ************************************************
 * 					  GRAPH  					  *
 * ************************************************
 */

template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

    Vertex<T> *findVertex(const T &in) const;

    bool dfsIsDAG(Vertex<T> *v) const;

public:
    int getNumVertex() const;

    vector<Vertex<T> *> getVertexSet() const;

    bool addVertex(const T &in, int xCoordinate, int yCoordinate);

    bool removeVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, char c);

    bool addEdgeTime(const T &sourc, const T &dest, double c);

    bool addEdgePrice(const T &sourc, const T &dest, double c);

    bool addEdgeTranshipment(const T &sourc, const T &dest, double c);

    bool removeEdge(const T &sourc, const T &dest);

    bool isDAG() const;

    vector<T> dfs() const;

    vector<T> bfs(const T &source) const;

    vector<T> topsort() const;

    vector<T> getPath(const T &origin, const T &dest);

    double getWeight(const T &origin, const T &dest);

    int maxNewChildren(const T &source, T &inf) const;

    void unweightedShortestPath(const T &orig);

    void dijkstraShortestPath(const T &origin);

    double calculateEdgeWeightDistance(const T &sourc, const T &dest);

    double calculateEdgeWeightTime(const T &sourc, const T &dest);

    double calculateEdgeWeightPrice(const T &sourc, const T &dest);

    char getTransport(const string &id);
};

template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {

    return this->vertexSet;
}

template<class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template<class T>
bool Graph<T>::addVertex(const T &in, int xCoordinate, int yCoordinate) {

    auto v1 = findVertex(in);

    if (v1 != NULL)
        return false;

    vertexSet.push_back(new Vertex<T>(in, xCoordinate, yCoordinate));

    return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, char c) {

    double w = 0;
    switch (c) {
        case 'd':
            w = calculateEdgeWeightDistance(sourc, dest);
            break;
        case 't':
            w = calculateEdgeWeightTime(sourc, dest);
            break;
        case 'p':
            w = calculateEdgeWeightPrice(sourc, dest);
            break;
        default:break;
    }

    auto vs = findVertex(sourc);
    auto vd = findVertex(dest);


    if (vs == NULL || vd == NULL)
        return false;

    vs->addEdge(vd, w);
    return true;
}

template<class T>
bool Graph<T>::addEdgeTime(const T &sourc, const T &dest, double c) {

    double w = c;

    auto vs = findVertex(sourc);
    auto vd = findVertex(dest);


    if (vs == NULL || vd == NULL)
        return false;

    vs->addEdge(vd, w);
    return true;
}

template<class T>
bool Graph<T>::addEdgePrice(const T &sourc, const T &dest, double c) {

    double w = c;

    auto vs = findVertex(sourc);
    auto vd = findVertex(dest);


    if (vs == NULL || vd == NULL)
        return false;

    vs->addEdge(vd, w);
    return true;
}

template<class T>
bool Graph<T>::addEdgeTranshipment(const T &sourc, const T &dest, double c) {

    double w = c;

    auto vs = findVertex(sourc);
    auto vd = findVertex(dest);


    if (vs == NULL || vd == NULL)
        return false;

    vs->addEdge(vd, w);
    return true;
}

template<class T>
double Graph<T>::calculateEdgeWeightDistance(const T &sourc, const T &dest) {

    double w = 0;
    auto vs = findVertex(sourc);
    auto vd = findVertex(dest);

    w = pow(vd->getXCoordinate() - vs->getXCoordinate(), 2);
    w += pow(vd->getYCoordinate() - vs->getYCoordinate(), 2);
    return sqrt(w);
}

template<class T>
double Graph<T>::calculateEdgeWeightTime(const T &sourc, const T &dest) {

    double w = calculateEdgeWeightDistance(sourc, dest);
    switch (getTransport(sourc)) {

        case 'b':
            w = w / busSpeed;
            break;
        case 's':
            w = w / metroSpeed;
            break;
        case 't':
            w = w / trainSpeed;
            break;
        default:break;
    }
    return sqrt(w);
}

template<class T>
double Graph<T>::calculateEdgeWeightPrice(const T &sourc, const T &dest) {

    double w = 0;

    switch (getTransport(sourc)) {

        case 'b':
            w = 0.1;
            break;
        case 's':
            w = 0.2;
            break;
        case 't':
            w = 0.3;
            break;
        default:break;
    }
    return sqrt(w);
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {

    auto vs = findVertex(sourc);
    auto vd = findVertex(dest);

    if (vs == NULL || vd == NULL)
        return false;

    return vs->removeEdgeTo(vd);
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->info == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    }
    return false;
}

template<class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;

    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (!v->visited)
            dfsVisit(v, res);
    return res;
}

template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {

    v->visited = true;
    res.push_back(v->info);

    for (auto &x : v->adj) {
        auto y = x.dest;
        if (!y->visited)
            dfsVisit(y, res);
    }
}

template<class T>
vector<T> Graph<T>::bfs(const T &source) const {

    vector<T> res;

    auto sourc = findVertex(source);
    if (sourc == NULL)
        return res;
    queue<Vertex<T> *> queue;

    queue.push(sourc);
    sourc->visited = true;

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        res.push_back(v->info);
        for (auto &edge : v->adj) {
            auto w = edge.dest;
            if (!w->visited) {
                queue.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->indegree = 0;
    for (auto v : vertexSet)
        for (auto &edge : v->adj)
            edge.dest->indegree++;

    queue<Vertex<T> *> queue;
    for (auto v : vertexSet) {
        if (v->indegree == 0)
            queue.push(v);
    }

    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        res.push_back(v->info);
        for (auto &edge : v->adj) {
            auto w = edge.dest;
            w->indegree--;
            if (w->indegree == 0) {
                queue.push(w);
            }
        }
    }

    if (vertexSet.size() != res.size()) {
        cout << "É impossível ordenar topologicamente!" << endl;
        res.clear();
        return res;
    }
    return res;
}

template<class T>
int Graph<T>::maxNewChildren(const T &source, T &inf) const {
    auto s = findVertex(source);
    if (s == NULL)
        return -1;

    int maxChild = 0;
    queue<Vertex<T> *> q;
    inf = s->info;

    for (auto v = vertexSet.begin(); v != vertexSet.end(); v++) {
        (*v)->visited = false;
    }
    s->visited = true;
    q.push(s);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        int children = 0;
        for (auto &e : v->adj) {
            auto d = e.dest;
            if (!d->visited) {
                d->visited = true;
                q.push(d);
                children++;
            }
        }
        if (maxChild < children) {
            maxChild = children;
            inf = v->info;
        }
    }
    return maxChild;
}

template<class T>
bool Graph<T>::isDAG() const {

    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet) {
        if (!v->visited) {
            if (!dfsIsDAG(v))
                return false;
        }
    }
    return true;
}

template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {

    v->visited = true;
    v->processing = true;
    for (auto &e : v->adj) {
        auto d = e.dest;
        if (d->processing) {
            return false;
        }
        if (!d->visited) {
            if (!dfsIsDAG(d)) {
                return false;
            }
        }
    }
    v->processing = false;
    return true;
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) {
    vector<T> res;
    auto v1 = findVertex(origin);
    auto v2 = findVertex(dest);

    if (v1 == NULL || v2 == NULL)
        return res;

    while (v2->getPath() != NULL) {

        res.push_back(v2->getInfo());

        v2 = v2->getPath();

    }

    res.push_back(origin);

    reverse(res.begin(), res.end());

    return res;
}

template<class T>
double Graph<T>::getWeight(const T &origin, const T &dest){

    double distance = 0;
    auto v1 = findVertex(origin);
    auto v2 = findVertex(dest);

    if (v1 == NULL || v2 == NULL)
        return distance;

    while (v2->getPath() != NULL) {

        distance += v2->getDist();

        v2 = v2->getPath();

    }

    return distance;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

    int infinite = std::numeric_limits<int>::max();

    for (auto v : vertexSet) {
        v->setDist(infinite);
        v->setPath(NULL);
    }
    auto s = findVertex(orig);
    s->dist = 0;
    queue<Vertex<T> *> q;
    q.push(s);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto &e : v->adj) {

            auto w = e.dest;
            if (w->getDist() == infinite) {
                w->dist = v->dist + 1;
                w->path = v;
                q.push(w);
            }
        }
    }
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

    auto s = findVertex(origin);

    int INF = std::numeric_limits<int>::max();

    for (auto v : vertexSet) {
        v->setDist(INF);
        v->setPath(NULL);
        v->visited = false;
    }

    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;

    q.insert(s);

    while (!q.empty()) {

        auto v = q.extractMin();

        for (auto &e : v->adj) {

            auto w = e.dest;

            double old_d = w->getDist();
            double new_d = v->getDist() + e.weight;

            if (old_d > new_d) {

                w->setDist(new_d);

                w->setPath(v);

                if (!w->visited) {
                    q.insert(w);
                } else {
                    q.decreaseKey(w);
                }
                w->visited = true;
            }
        }
    }
}

template<class T>
char Graph<T>::getTransport(const string &id) {

    if (id.find('a') != string::npos) {

        return 'b';
    } else if (id.find('b') != string::npos) {

        return 's';
    } else if (id.find('c') != string::npos) {

        return 't';
    } else return ' ';
}

#endif /* GRAPH_H_ */

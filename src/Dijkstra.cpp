//O algoritmo desenvolvido na prática, não testado!

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	
	auto i = vertexSet.begin();
	for (; i != vertexSet.end(); i++) {
		Vertex<T>* vert = *i;
		vert->dist = INF;
		vert->path = NULL;
	}

	Vertex<T>* orig = findVertex(origin);
	orig->dist = 0;

	MutablePriorityQueue< Vertex<T> > q;
	q.insert(orig);

	while (!q.empty()) {
		Vertex<T>* v = q.extractMin();
		for (auto i = v->adj.begin(); i != v->adj.begin(); i++) {
			Vertex<T>* w = i->dest;
			if (w->getDist() > v->getDist() + i->weight) {
				double oldDist = w->dist;
				w->dist = v->getDist() + i->weight;
				w->path = v;
				if (oldDist == INF) q.decreaseKey(w);
				else q.insert(w);
			}
		}
	}
}

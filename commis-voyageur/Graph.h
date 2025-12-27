#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int u, v;
    double weight;
    
    Edge(int start, int end, double w) : u(start), v(end), weight(w) {}
    Edge() : u(0), v(0), weight(0.0) {}
};

class GraphMST {
public:
    GraphMST(int n);
    ~GraphMST();
    void addEdge(int u, int v, double w);
    double getMSTWeight();
    std::vector<Edge> getMSTEdges();

private:
    int numVertices;
    std::vector<Edge> edges;
};

#endif

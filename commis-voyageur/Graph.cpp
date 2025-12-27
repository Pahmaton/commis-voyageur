#include "Graph.h"
#include "DSU.h"
#include <algorithm>

GraphMST::GraphMST(int n) : numVertices(n) {}

GraphMST::~GraphMST() {}

void GraphMST::addEdge(int u, int v, double w) {
    edges.push_back(Edge(u, v, w));
}

// Сортировка ребер
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

double GraphMST::getMSTWeight() {
    std::sort(edges.begin(), edges.end(), compareEdges);
    DSU dsu(numVertices);
    double totalWeight = 0;
    
    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            totalWeight += edge.weight;
            dsu.unite(edge.u, edge.v);
        }
    }
    return totalWeight;
}

std::vector<Edge> GraphMST::getMSTEdges() {
    std::sort(edges.begin(), edges.end(), compareEdges);
    DSU dsu(numVertices);
    std::vector<Edge> mstResult;
    
    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            mstResult.push_back(edge);
            dsu.unite(edge.u, edge.v);
        }
    }
    return mstResult;
}

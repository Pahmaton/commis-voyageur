#include "Experiments.h"
#include "Graph.h"
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <numeric>
#include <algorithm>

double getNormalRandom() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<> urd(0.0, 1.0);
    
    double u1 = urd(gen);
    double u2 = urd(gen);
    
    double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * M_PI * u2);
    return z0;
}

double getDistance(const Point& a, const Point& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

void dfs(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<int>& path) {
    visited[u] = true;
    path.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, path);
        }
    }
}

double solveApproxTSP(int n, const std::vector<Point>& points) {
    GraphMST graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            graph.addEdge(i + 1, j + 1, getDistance(points[i], points[j]));
        }
    }
    
    std::vector<Edge> mst = graph.getMSTEdges();

    std::vector<std::vector<int>> adj(n + 1);
    for (const auto& e : mst) {
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }
    
    std::vector<int> path;
    std::vector<bool> visited(n + 1, false);
    dfs(1, adj, visited, path);

    double dist = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        dist += getDistance(points[path[i]-1], points[path[i+1]-1]);
    }
    // Замыкаем
    if (!path.empty()) {
        dist += getDistance(points[path.back()-1], points[path[0]-1]);
    }
    
    return dist;
}

double solveOptimalTSP(int n, const std::vector<Point>& points) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    
    double minLen = 1e18;
    
    do {
        double currentLen = 0;
        for (int i = 0; i < n - 1; ++i) {
            currentLen += getDistance(points[p[i]], points[p[i+1]]);
        }
        currentLen += getDistance(points[p[n-1]], points[p[0]]);
        minLen = std::min(minLen, currentLen);
        
    } while (std::next_permutation(p.begin(), p.end()));
    return minLen;
}

void runExperiments() {
    std::cout << "Starting Experiments...\n";
    std::cout << "N\tMean Ratio\tStdDev\n";
    
    for (int n = 2; n <= 10; ++n) {
        std::vector<double> ratios;
        int trials = 10;
        
        for (int t = 0; t < trials; ++t) {
            std::vector<Point> points(n);
            for (int i = 0; i < n; ++i) {
                points[i] = {getNormalRandom(), getNormalRandom()};
            }
            
            double approx = solveApproxTSP(n, points);
            double optimal = solveOptimalTSP(n, points);
            
            if (optimal > 1e-9) {
                ratios.push_back(approx / optimal);
            }
        }
        
        double sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
        double mean = sum / ratios.size();
        
        double sq_sum = 0.0;
        for (double r : ratios) {
            sq_sum += (r - mean) * (r - mean);
        }
        double stdDev = std::sqrt(sq_sum / ratios.size());
        
        std::cout << n << "\t" << mean << "\t\t" << stdDev << "\n";
    }
}

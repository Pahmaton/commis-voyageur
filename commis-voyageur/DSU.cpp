#include "DSU.h"
#include <algorithm>

DSU::DSU(int n) : size(n + 1) {
    parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

DSU::~DSU() {
    cleanup();
}

void DSU::cleanup() {
    if (parent) {
        delete[] parent;
        parent = nullptr;
    }
    if (rank) {
        delete[] rank;
        rank = nullptr;
    }
}

void DSU::copyFrom(const DSU& other) {
    size = other.size;
    parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; ++i) {
        parent[i] = other.parent[i];
        rank[i] = other.rank[i];
    }
}

DSU::DSU(const DSU& other) : parent(nullptr), rank(nullptr), size(0) {
    copyFrom(other);
}

DSU& DSU::operator=(const DSU& other) {
    if (this != &other) {
        cleanup();
        copyFrom(other);
    }
    return *this;
}

int DSU::find(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}

void DSU::unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

#ifndef DSU_H
#define DSU_H

class DSU {
public:
    explicit DSU(int n);
    
    ~DSU();
    DSU(const DSU& other);
    DSU& operator=(const DSU& other);

    int find(int v);
    void unite(int a, int b);

private:
    int* parent;
    int* rank;
    int size;
    
    void cleanup();
    void copyFrom(const DSU& other);
};

#endif

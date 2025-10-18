#include <bits/stdc++.h>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, w;

    // Comparator for sorting edges based on weight
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

// Disjoint Set Union (DSU) structure
struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i)
            make_set(i);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]); // Path compression
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    bool connected(int a, int b) {
        return find_set(a) == find_set(b);
    }
};

// Kruskal's Algorithm
int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; ++i)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    // Sorting edges by weight
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    vector<Edge> result;
    int mst_weight = 0;

    for (auto &edge : edges) {
        if (!dsu.connected(edge.u, edge.v)) {
            dsu.union_sets(edge.u, edge.v);
            result.push_back(edge);
            mst_weight += edge.w;
        }
    }

    cout << "\nMinimum Spanning Tree Weight: " << mst_weight << "\n";
    cout << "Edges in MST:\n";
    for (auto &e : result)
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";

    return 0;
}


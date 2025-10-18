#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    int totalWeight = 0;
    vector<Edge> mst;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalWeight += e.w;
            mst.push_back(e);
        }
    }

    cout << "Minimum Spanning Tree Weight: " << totalWeight << "\n";
    cout << "Edges in MST:\n";
    for (auto &e : mst)
        cout << e.u << " - " << e.v << " (Weight: " << e.w << ")\n";

    return 0;
}

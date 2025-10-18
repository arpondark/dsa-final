#include <bits/stdc++.h>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, w;

    // Comparator for priority queue (min-heap based on weight)
    bool operator>(const Edge &other) const {
        return w > other.w;
    }
};

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // Adjacency list: node -> list of (neighbor, weight)
    vector<vector<pair<int, int>>> adj(n + 1);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<bool> inMST(n + 1, false);
    vector<Edge> result;
    int mst_weight = 0;

    // Priority queue of edges (min-heap)
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    // Start from node 1 (can be any)
    inMST[1] = true;
    for (auto &[v, w] : adj[1]) {
        pq.push({1, v, w});
    }

    // Main Prim's loop
    while (!pq.empty() && result.size() < n - 1) {
        Edge e = pq.top();
        pq.pop();

        if (inMST[e.v]) continue; // Skip if vertex already in MST

        inMST[e.v] = true;
        result.push_back(e);
        mst_weight += e.w;

        for (auto &[next, wt] : adj[e.v]) {
            if (!inMST[next]) {
                pq.push({e.v, next, wt});
            }
        }
    }

    cout << "\nMinimum Spanning Tree Weight: " << mst_weight << "\n";
    cout << "Edges in MST:\n";
    for (auto &e : result) {
        cout << e.u << " - " << e.v << " (Weight: " << e.w << ")\n";
    }

    return 0;
}


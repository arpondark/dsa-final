#include <bits/stdc++.h>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, w;
    bool operator>(const Edge &other) const {
        return w > other.w;
    }
};

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // Store minimum edge for each pair (u, v)
    map<pair<int, int>, int> minEdge;

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u > v) swap(u, v); // to avoid (u,v) and (v,u) duplicates
        if (minEdge.find({u, v}) == minEdge.end() || minEdge[{u, v}] > w)
            minEdge[{u, v}] = w;
    }

    // Build adjacency list from filtered edges
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto &e : minEdge) {
        int u = e.first.first;
        int v = e.first.second;
        int w = e.second;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Prim's Algorithm
    vector<bool> inMST(n + 1, false);
    vector<Edge> result;
    int mst_weight = 0;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    // Start from node 1
    inMST[1] = true;
    for (auto &[v, w] : adj[1]) {
        pq.push({1, v, w});
    }

    while (!pq.empty() && result.size() < n - 1) {
        Edge e = pq.top();
        pq.pop();

        if (inMST[e.v]) continue;

        inMST[e.v] = true;
        result.push_back(e);
        mst_weight += e.w;

        for (auto &[next, wt] : adj[e.v]) {
            if (!inMST[next]) pq.push({e.v, next, wt});
        }
    }

    // Step 4: Output
    cout << "\nMinimum Spanning Tree Weight: " << mst_weight << "\n";
    cout << "Edges in MST:\n";
    for (auto &e : result) {
        cout << e.u << " - " << e.v << " (Weight: " << e.w << ")\n";
    }

    return 0;
}


#include <bits/stdc++.h>
using namespace std;

// Edge structure
struct Edge {
    int u, v, w;
};

void dijkstra(int n, vector<vector<pair<int, int>>> &adj, int source) {
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[source] = 0;

    // Set stores pairs of (distance, vertex)
    set<pair<int, int>> s;
    s.insert({0, source});

    while (!s.empty()) {
        auto [d, u] = *s.begin();
        s.erase(s.begin());

        // Skip if we already found a better distance
        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                // If a better path is found, update it
                if (dist[v] != INT_MAX)
                    s.erase({dist[v], v});

                dist[v] = dist[u] + w;
                parent[v] = u;
                s.insert({dist[v], v});
            }
        }
    }

    cout << "\nShortest distances from vertex " << source << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "To vertex " << i << " -> Distance: ";
        if (dist[i] == INT_MAX)
            cout << "INF";
        else
            cout << dist[i];
        cout << "\n";
    }

    cout << "\nShortest paths:\n";
    for (int i = 0; i < n; ++i) {
        if (i == source) continue;
        cout << "Path to " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "No path\n";
            continue;
        }
        vector<int> path;
        for (int v = i; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j];
            if (j + 1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> adj(n);

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back({edges[i].v, edges[i].w});
        adj[edges[i].v].push_back({edges[i].u, edges[i].w}); // For undirected graph
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    dijkstra(n, adj, source);

    return 0;
}

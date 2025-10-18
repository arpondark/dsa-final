#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

void dijkstra(int n, vector<vector<pair<int, int>>> &adj, int source, int dest, vector<int> &mummy) {
    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    dist[source] = 0;

    set<pair<int, int>> s;
    s.insert({0, source});

    while (!s.empty()) {
        auto [d, u] = *s.begin();
        s.erase(s.begin());

        if (d > dist[u]) continue;
        if (mummy[u]) continue; // skip mummy chambers

        for (auto &[v, w] : adj[u]) {
            if (mummy[v]) continue;
            if (dist[u] + w < dist[v]) {
                if (dist[v] != INT_MAX)
                    s.erase({dist[v], v});
                dist[v] = dist[u] + w;
                parent[v] = u;
                s.insert({dist[v], v});
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No safe path available\n";
        return;
    }

    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    int total = dist[dest];

    cout << "Safe Path:\n";
    for (int node : path)
        cout << "->" << node;
    cout << "\nThe total length of the safe route is:\n" << total << "\n";
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back({edges[i].v, edges[i].w});
        adj[edges[i].v].push_back({edges[i].u, edges[i].w});
    }

    vector<int> mummy(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> mummy[i];

    int dest;
    cin >> dest;

    dijkstra(n, adj, 1, dest, mummy);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Function to perform Dijkstras algorithm
vector<int> dijkstra(int n, vector<vector<pair<int,int>>> &adj, vector<int> &mummy, int start) {
    vector<int> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;
        if (mummy[u] == 1) continue; // Skip mummy chambers

        for (auto &[v, w] : adj[u]) {
            if (mummy[v] == 1) continue; // Avoid mummy chambers
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return parent; // return parent vector to reconstruct path
}

// Function to reconstruct path
vector<int> reconstructPath(int start, int end, vector<int> &parent) {
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    if (path[0] != start) path.clear();
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> mummy(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> mummy[i];
    }

    int treasure;
    cin >> treasure;

    int start = 1;

    vector<int> parent = dijkstra(n, adj, mummy, start);

    vector<int> path = reconstructPath(start, treasure, parent);

    if (path.empty()) {
        cout << "No safe path exists.\n";
        return 0;
    }

    int totalDistance = 0;
    for (int i = 1; i < (int)path.size(); i++) {
        for (auto &[v, w] : adj[path[i - 1]]) {
            if (v == path[i]) {
                totalDistance += w;
                break;
            }
        }
    }

    cout << "Safe Path:\n";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << "->" << path[i];
    }
    cout << "\nThe total length of the safe route is:\n" << totalDistance << "\n";

    return 0;
}


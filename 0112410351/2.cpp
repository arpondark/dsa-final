#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

pair<vector<int>, vector<int>> dijkstra(int n, vector<vector<pair<int,int>>> &adj, int src) {
    vector<int> dist(n, INF), parent(n, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
    }
    return {dist, parent};
}

vector<int> buildPath(int src, int dest, vector<int> &parent) {
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return (path.front() == src) ? path : vector<int>();
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    int s, t, k;
    cin >> s >> t >> k;

    auto [dist1, par1] = dijkstra(n, adj, s);
    auto [dist2, par2] = dijkstra(n, adj, k);

    if (dist1[k] == INF || dist2[t] == INF) {
        cout << "No valid path\n";
        return 0;
    }

    int total = dist1[k] + dist2[t];
    cout << "Shortest distance from " << s << " to " << t << " passing through " << k << ": " << total << "\n";

    vector<int> path1 = buildPath(s, k, par1);
    vector<int> path2 = buildPath(k, t, par2);
    path2.erase(path2.begin());
    path1.insert(path1.end(), path2.begin(), path2.end());

    cout << "Path: ";
    for (int i = 0; i < path1.size(); ++i)
        cout << path1[i] << (i + 1 == path1.size() ? "\n" : " -> ");
}

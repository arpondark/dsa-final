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
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

pair<int, vector<Edge>> kruskal(int n, vector<Edge> &edges, int skipEdge = -1, int addEdge = -1) {
    DSU dsu(n);
    int total = 0, cnt = 0;
    vector<Edge> result;
    for (int i = 0; i < edges.size(); i++) {
        if (i == skipEdge) continue;
        if (dsu.unite(edges[i].u, edges[i].v)) {
            total += edges[i].w;
            result.push_back(edges[i]);
            cnt++;
        }
    }
    if (cnt != n - 1) return {INT_MAX, {}};
    return {total, result};
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end());
    auto [mstWeight, mstEdges] = kruskal(n, edges);
    int secondBest = INT_MAX;
    vector<Edge> secondMST;

    for (int i = 0; i < mstEdges.size(); i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (edges[j].u == mstEdges[i].u && edges[j].v == mstEdges[i].v && edges[j].w == mstEdges[i].w) {
                idx = j;
                break;
            }
        }
        auto [w, newEdges] = kruskal(n, edges, idx);
        if (w > mstWeight && w < secondBest) {
            secondBest = w;
            secondMST = newEdges;
        }
    }

    cout << "Second Best MST Weight: " << secondBest << "\n";
    cout << "Edges in Second Best MST:\n";
    for (auto &e : secondMST)
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";
    return 0;
}

/*
added and deleted node part

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
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

pair<int, vector<Edge>> kruskal(int n, vector<Edge> &edges, int skipEdge = -1) {
    DSU dsu(n);
    int total = 0, cnt = 0;
    vector<Edge> result;
    for (int i = 0; i < edges.size(); i++) {
        if (i == skipEdge) continue;
        if (dsu.unite(edges[i].u, edges[i].v)) {
            total += edges[i].w;
            result.push_back(edges[i]);
            cnt++;
        }
    }
    if (cnt != n - 1) return {INT_MAX, {}};
    return {total, result};
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end());
    auto [mstWeight, mstEdges] = kruskal(n, edges);
    int secondBest = INT_MAX;
    vector<Edge> secondMST;

    for (int i = 0; i < mstEdges.size(); i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (edges[j].u == mstEdges[i].u && edges[j].v == mstEdges[i].v && edges[j].w == mstEdges[i].w) {
                idx = j;
                break;
            }
        }
        auto [w, newEdges] = kruskal(n, edges, idx);
        if (w > mstWeight && w < secondBest) {
            secondBest = w;
            secondMST = newEdges;
        }
    }

    cout << "Best MST Weight: " << mstWeight << "\n";
    cout << "Second Best MST Weight: " << secondBest << "\n";
    cout << "Weight Difference: " << secondBest - mstWeight << "\n\n";

    // Detect added and removed edges
    set<tuple<int,int,int>> mstSet, secondSet;
    for (auto &e : mstEdges)
        mstSet.insert({min(e.u,e.v), max(e.u,e.v), e.w});
    for (auto &e : secondMST)
        secondSet.insert({min(e.u,e.v), max(e.u,e.v), e.w});

    cout << "Edges removed from MST:\n";
    for (auto &e : mstSet)
        if (!secondSet.count(e))
            cout << get<0>(e) << " - " << get<1>(e) << " (" << get<2>(e) << ")\n";

    cout << "\nEdges added in Second MST:\n";
    for (auto &e : secondSet)
        if (!mstSet.count(e))
            cout << get<0>(e) << " - " << get<1>(e) << " (" << get<2>(e) << ")\n";

    cout << "\nSecond Best MST Edges:\n";
    for (auto &e : secondMST)
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";

    return 0;
}

*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rank;

    // Constructor
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 1; i <= n; i++)
            make_set(i);
    }

    // Initialize a node's parent and rank
    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    // Find the representative of a set with path compression
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    // Union by rank
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

    // Check if two elements belong to the same set
    bool connected(int a, int b) {
        return find_set(a) == find_set(b);
    }
};

int main() {
    int n, q;
    cout << "Enter number of elements and queries: ";
    cin >> n >> q;

    DSU dsu(n);

    cout << "Enter queries:\n";
    cout << "1 a b -> Union(a, b)\n";
    cout << "2 a b -> Check if a and b are connected\n\n";

    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;

        if (type == 1) {
            dsu.union_sets(a, b);
            cout << "Union performed on " << a << " and " << b << "\n";
        }
        else if (type == 2) {
            if (dsu.connected(a, b))
                cout << a << " and " << b << " are connected.\n";
            else
                cout << a << " and " << b << " are NOT connected.\n";
        }
        else {
            cout << "Invalid query type.\n";
        }
    }

    return 0;
}
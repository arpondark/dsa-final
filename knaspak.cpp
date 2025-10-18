#include <bits/stdc++.h>
using namespace std;

int knapsack(int n, int W, vector<int> &wt, vector<int> &val, vector<int> &taken) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int w = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            taken[i - 1] = 1;
            w -= wt[i - 1];
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    cin >> n >> W;

    vector<int> wt(n), val(n);
    for (int i = 0; i < n; i++) cin >> wt[i];
    for (int i = 0; i < n; i++) cin >> val[i];

    vector<int> used(n, 0);
    int bag = 1;

    while (true) {
        // Prepare remaining items for this iteration
        vector<int> cur_wt, cur_val, map_idx;
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                cur_wt.push_back(wt[i]);
                cur_val.push_back(val[i]);
                map_idx.push_back(i);
            }
        }

        cout << "Using the knapsack no " << bag << "\n";

        if (cur_wt.empty()) {
            cout << "profit 0\n";
            break;
        }

        vector<int> taken(cur_wt.size(), 0);
        int profit = knapsack(cur_wt.size(), W, cur_wt, cur_val, taken);

        if (profit == 0) {
            cout << "profit 0\n";
            break;
        }

        for (int i = 0; i < (int)taken.size(); i++) {
            if (taken[i]) {
                int idx = map_idx[i];
                cout << "Taken item " << idx + 1 << "\n";
                used[idx] = 1;
            }
        }

        cout << "profit = " << profit << "\n";
        bag++;
    }
}

#include <bits/stdc++.h>
using namespace std;

int knapsackBottomUp(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i-1] <= w) {
                dp[i][w] = max(val[i-1] + dp[i-1][w - wt[i-1]], dp[i-1][w]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    // Reconstruct chosen items
    int res = dp[n][W];
    int w = W;
    vector<int> chosenItems;

    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i-1][w]) {
            // Item i-1 is included
            chosenItems.push_back(i-1);
            res -= val[i-1];
            w -= wt[i-1];
        }
    }

    cout << "Maximum value (Bottom-Up): " << dp[n][W] << endl;

    cout << "Items taken (0-based index): ";
    reverse(chosenItems.begin(), chosenItems.end());
    for (int idx : chosenItems) {
        cout << idx << " (value=" << val[idx] << ", weight=" << wt[idx] << ")  ";
    }
    cout << endl;

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> val(n), wt(n);

    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) cin >> val[i];

    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) cin >> wt[i];

    cout << "Enter maximum capacity of knapsack: ";
    cin >> W;

    knapsackBottomUp(W, wt, val, n);

    return 0;
}


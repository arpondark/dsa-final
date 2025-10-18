#include <bits/stdc++.h>
using namespace std;

int knapsackMemo(int W, vector<int>& wt, vector<int>& val, int n, vector<vector<int>>& dp) {
    if (n == 0 || W == 0) return 0;

    if (dp[n][W] != -1) return dp[n][W];

    if (wt[n-1] <= W) {
        dp[n][W] = max(
            val[n-1] + knapsackMemo(W - wt[n-1], wt, val, n-1, dp),
            knapsackMemo(W, wt, val, n-1, dp)
        );
    } else {
        dp[n][W] = knapsackMemo(W, wt, val, n-1, dp);
    }
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

    vector<vector<int>> dp(n+1, vector<int>(W+1, -1));

    cout << "Maximum value (Top-Down): "
         << knapsackMemo(W, wt, val, n, dp) << endl;

    return 0;
}


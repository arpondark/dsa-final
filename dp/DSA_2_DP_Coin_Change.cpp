#include <bits/stdc++.h>
using namespace std;

void coinChange(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<int> dp(amount + 1, INT_MAX);  // dp[x] = min coins to make x
    vector<int> parent(amount + 1, -1);   // store last coin used

    dp[0] = 0; // base case: 0 coins for amount 0

    // Fill DP table
    for (int coin : coins) {
        for (int x = coin; x <= amount; x++) {
            if (dp[x - coin] != INT_MAX && dp[x - coin] + 1 < dp[x]) {
                dp[x] = dp[x - coin] + 1;
                parent[x] = coin; // remember which coin was used
            }
        }
    }

    if (dp[amount] == INT_MAX) {
        cout << "It is not possible to form amount " << amount << " with given coins." << endl;
        return;
    }

    cout << "Minimum number of coins required: " << dp[amount] << endl;

    // Reconstruct coins used
    cout << "Coins used: ";
    int curr = amount;
    vector<int> result;
    while (curr > 0) {
        int coin = parent[curr];
        result.push_back(coin);
        curr -= coin;
    }

    for (int c : result) cout << c << " ";
    cout << endl;
}

int main() {
    int n, amount;
    cout << "Enter number of coin types: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter coin values: ";
    for (int i = 0; i < n; i++) cin >> coins[i];

    cout << "Enter target amount: ";
    cin >> amount;

    coinChange(amount, coins);

    return 0;
}


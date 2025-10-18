#include <bits/stdc++.h>
using namespace std;

void rodCutting(vector<int>& price, int n) {
    vector<int> dp(n+1, 0);       // dp[i] = max revenue for rod of length i
    vector<int> cut(n+1, 0);      // cut[i] = best first cut length for rod of length i

    // Build DP table
    for (int i = 1; i <= n; i++) {
        int max_val = INT_MIN;
        for (int j = 1; j <= i; j++) {
            if (max_val < price[j-1] + dp[i-j]) {
                max_val = price[j-1] + dp[i-j];
                cut[i] = j; // store cut length
            }
        }
        dp[i] = max_val;
    }

    cout << "Maximum Revenue: " << dp[n] << endl;

    // Reconstruct solution
    cout << "Pieces cut (lengths): ";
    int length = n;
    while (length > 0) {
        cout << cut[length] << " ";
        length -= cut[length];
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter rod length: ";
    cin >> n;

    vector<int> price(n);
    cout << "Enter prices for lengths 1 to " << n << ": ";
    for (int i = 0; i < n; i++) cin >> price[i];

    rodCutting(price, n);

    return 0;
}


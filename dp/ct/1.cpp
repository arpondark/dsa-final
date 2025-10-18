#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, K;
    cin >> n >> K;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vector<vector<bool>> dp(n + 1, vector<bool>(K + 1, false));

    // Base case: sum 0 is always possible (empty subset)
    for (int i = 0; i <= n; i++) dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            if (A[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - A[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    cout << (dp[n][K] ? "True" : "False") << endl;
    return 0;
}

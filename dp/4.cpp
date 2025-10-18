#include <bits/stdc++.h>
using namespace std;

int maximizeCuts(int n, int x, int y, int z) {
    vector<int> dp(n + 1, -1e9);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (i >= x) dp[i] = max(dp[i], dp[i - x] + 1);
        if (i >= y) dp[i] = max(dp[i], dp[i - y] + 1);
        if (i >= z) dp[i] = max(dp[i], dp[i - z] + 1);
    }
    return dp[n] < 0 ? 0 : dp[n];
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N, X, Y, Z;
        cin >> N >> X >> Y >> Z;
        cout << maximizeCuts(N, X, Y, Z) << endl;
    }
    return 0;
}

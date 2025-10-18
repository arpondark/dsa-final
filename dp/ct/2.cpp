#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << 1 << endl;
        return 0;
    }

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    if (n >= 1) dp[1] = 1;
    if (n >= 2) dp[2] = 2;

    for (int i = 3; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    cout << dp[n] << endl;
    return 0;
}

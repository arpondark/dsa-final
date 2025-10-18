#include <bits/stdc++.h>
using namespace std;

int maxNonAdjacentSum(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    if (n == 1) return arr[0];

    vector<int> dp(n);
    dp[0] = arr[0];
    dp[1] = max(arr[0], arr[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], arr[i] + dp[i - 2]);
    }
    return dp[n - 1];
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> arr(N);
        for (int i = 0; i < N; i++) cin >> arr[i];
        cout << maxNonAdjacentSum(arr) << endl;
    }
    return 0;
}

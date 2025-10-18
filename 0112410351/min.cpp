#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7;
int solve()
{
    int n, x;
    if (!(cin >> n >> x))
    {
        return -1;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= x; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[j] <= i)
            {
                if (dp[i - a[j]] != INF)
                {
                    dp[i] = min(dp[i], dp[i - a[j]] + 1);
                }
            }
        }
    }

    if (dp[x] != INF)
    {
        return dp[x];
    }
    return -1;
}

int main()
{

    int result = solve();
    if (result != -1)
    {
        cout << result << '\n';
    }
    else
    {
        cout << -1 << '\n';
    }
    return 0;
}
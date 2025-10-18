#include <bits/stdc++.h>
using namespace std;  //assignment

int solve(vector<int>& cost)
{
    int n = cost.size();
    vector<int> dp(n+1,0);
    for(int i=2;i<=n;i++)
    {
        dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
    }

    return dp[n];
}

int main()
{
    int n;
    cin >> n;
    vector<int> cost(n);
    for(int i=0;i<n;i++)
        cin >> cost[i];

    cout << solve(cost) << endl;
    return 0;
}
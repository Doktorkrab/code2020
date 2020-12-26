#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
 
#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif
 
int n, m;
vector<vector<int>> arr;
vector<vector<int>> dp;

int solve() {
    if (!(cin >> n >> m))
        return 1;
    arr.resize(n, vector<int>(m));
    dp.resize(n, vector<int>(m, (int)1e9));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    fill(ALL(dp[0]), 0);
    for (int i = 1; i < n; i++){
        for (int j = 0; j < m; j++)
            for (int k = 0; k < m; k++)
                dp[i][j] = min(dp[i][j], max(dp[i - 1][k], abs(arr[i][j] -arr[i - 1][k])));
    }
    cout << (*min_element(ALL(dp[n - 1]))) << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
//#ifdef LOCAL
//        cout << "------------------------------\n";
//#endif
    }
}

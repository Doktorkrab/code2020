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

int n, k;
const int MAXN = 1e5 + 7;
const ll INF = 1e18;

ll dp[MAXN];
ll arr[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    dp[0] = 0;
    for (int i = 0; i < n; i++){
        ll sum = 0;
        dp[i + 1] = INF;
        for (int j = i; j >= 0 && i - j <= k; j--){
            dp[i + 1] = min(dp[i + 1], dp[j] + arr[j] + sum / 2);
            sum += arr[j];
        }
    }
    for (int i = 0; i <= n; i++)
        cout << dp[i] << " \n"[i == n];
    cout << dp[n] << '\n';
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
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

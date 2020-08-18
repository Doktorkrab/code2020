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
 
int n;
string s;
const int MAXN = 1e5 + 7;
ll dp[MAXN];
 
int solve() {
    if (!(cin >> n >> s))
        return 1;
    n = SZ(s);
    unordered_map<ll, int> was;
    ll ans = 0;
    // dp[0] = 0;
    was[1] = 0;
    ll pref = 0;
    for (int i = 0; i < n; i++)
        dp[i] = 0;
    for (int i = 0; i < n; i++){
        pref += (s[i] - '0');
        ll now = pref - i;
        if (was.count(now)){
            dp[i] = dp[was[now]] + 1;
            ans += dp[i];
        }
        was[now] = i;
    }
    // for (int i = 0; i < n; i++)
    //     cout << dp[i] << " \n"[i + 1 == n];
    cout << ans << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
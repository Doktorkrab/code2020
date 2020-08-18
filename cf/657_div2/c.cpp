#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll 
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
const int MAXN = 1e5 + 7;
pair<int, int> have[MAXN];
int prefix[MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++)
        cin >> have[i].first >> have[i].second;
    sort(have, have + m);
    for (int i = 0; i < m; i++)
        prefix[i + 1] = prefix[i] + have[i].first;
    // for (int)
    // int pos = 0;
    int ans = 0;
    for (int i = 0; i < m; i++){
        int cnt = min(n, m - (int)(upper_bound(have, have + m, make_pair(have[i].second, (int) -1)) - have));
        assert(m - cnt >= 0 && m - cnt <= m);
        int now = prefix[m] - prefix[m - cnt];
        if (n - cnt > 0){
            if (m - cnt <= i)
                now += have[i].second * (n - cnt);
            else
                now += have[i].first + (n - cnt - 1) * have[i].second;
        }
        // cout << i << ' ' << now << '\n';
        ans = max(ans, now);
    }
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
// #ifdef LOCAL
//         cout << "------------------------------\n";
// #endif
    }
}
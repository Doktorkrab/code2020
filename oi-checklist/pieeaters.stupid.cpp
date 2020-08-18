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

struct Segment{
    int w, l, r;
};
 
const int MAXN = 55;
const int MAXM = 21;
int n, m;
Segment segments[MAXM];
int dp[1 << MAXM];
int color[MAXN];
int prefix[MAXN];
int ev[MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++)
        cin >> segments[i].w >> segments[i].l >> segments[i].r;
    int ans = 0;
    fill(dp, dp + (1 << MAXM), 0);
    for (int mask = 0; mask < (1 << m); mask++){
        fill(color, color + n + 1, 1);
        fill(ev, ev + n + 1, 0);

        for (int i = 0; i < m; i++){
            if ((mask >> i) & 1){
                ev[segments[i].l]++;
                ev[segments[i].r + 1]--;
            }
        }
        int cnt = 0;
        for (int i = 0; i <= n; i++){
            cnt += ev[i];
            if (cnt)
                color[i] = 0;
        }
        for (int i = 0; i <= n; i++)
            prefix[i + 1] = prefix[i] + color[i];

        for (int new_seg = 0; new_seg < m; new_seg++){
            if ((mask >> new_seg) & 1)
                continue;
            if (prefix[segments[new_seg].r + 1] - prefix[segments[new_seg].l] == 0)
                continue;
            dp[mask | (1 << new_seg)] = max(dp[mask] + segments[new_seg].w, dp[mask | (1 << new_seg)]);
            ans = max(dp[mask | (1 << new_seg)], ans);
        }
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
#endif
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
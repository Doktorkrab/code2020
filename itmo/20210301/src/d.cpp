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
const int MAXN = 2e5 + 7;
const ll INF = 1e18;
ll q[MAXN];
ll t[MAXN];
ll dp[MAXN];

struct Line {
    ll k, b;

    Line() : k(0), b(INF) {}

    Line(ll k, ll b) : k(k), b(b) {}

    ll operator()(ll x) const {
        return k * x + b;
    }
};
struct LiChao {
    Line tree[4 * MAXN];
    LiChao() {}
    ll get(int v, int tl, int tr, int x) {
        if (tr - tl == 1)
            return tree[v](x);
        int tm = (tl + tr) / 2;
        if (x < tm)
            return min(tree[v](x), get(v * 2, tl, tm, x));
        return min(tree[v](x), get(v * 2 + 1, tm, tr, x));
    }

    void add(int v, int tl, int tr, Line x) {
//    cerr << v << ' ' << tl << ' ' << tr << '\n';
        int tm = (tl + tr) / 2;
        bool mid = x(tm) < tree[v](tm);
        bool lft = x(tl) < tree[v](tl);
        if (mid)
            swap(x, tree[v]);
        if (tr - tl == 1)
            return;
        if (lft != mid)
            add(v * 2, tl, tm, x);
        else
            add(v * 2 + 1, tm, tr, x);
    }
    void add(Line x){
        add(1, 0, MAXN, x);
    }
    ll get(int x){
        return get(1, 0, MAXN, x);
    }
};
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> q[i] >> t[i];
    fill(dp, dp + n + 300, INF);
    dp[0] = 0;
    ll ans = TMAX(ll);
    vector<LiChao> mod2(2), mod4(4), mod6(6);
    for (int i = 0; i < n + 300; i++) {
        dp[i] = min(dp[i], mod2[i % 2].get(i / 2));
        dp[i] = min(dp[i], mod4[i % 4].get(i / 4));
        dp[i] = min(dp[i], mod6[i % 6].get(i / 6));
        if (t[i] == 1)
            mod2[i % 2].add(Line(q[i], dp[i] - i / (2 * t[i]) * q[i]));
        if (t[i] == 2)
            mod4[i % 4].add(Line(q[i], dp[i] - i / (2 * t[i]) * q[i]));
        if (t[i] == 3)
            mod6[i % 6].add(Line(q[i], dp[i] - i / (2 * t[i]) * q[i]));
//        ll add = 0;
//        for (ll j = i + 2 * t[i]; j < n + 500; j += 2 * t[i]){
//            add += q[i];
//            if (j < n)
//                dp[j] = min(dp[j], dp[i] + add);
//            else if (j > n)
//                ans = min(ans, dp[i] + add);
//        }
    }
//    for (int i = 0; i < n; i++)
//        cout << dp[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < n + 300; i++)
//        cout << dp[i] << " \n"[i + 1 == n + 300];
    for (int i = n + 1; i < n + 300; i++)
        ans = min(dp[i], ans);
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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

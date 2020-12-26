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

int n, q;
const int MAXN = 1e3 + 7;
const ll INF = 1e18;
vector<pair<int, ll>> g[MAXN];

ll query(int v, int p, int l, int r) {
//    cout << v << ' ' << (l <= v && v <= r) << '\n';
    ll have = (l <= v && v <= r && SZ(g[v]) == 1 ? 0 : INF);
    for (auto[u, w] : g[v])
        if (u != p)
            have = min(have, query(u, v, l, r) + w);
//    cout << v + 1 << " " << have << '\n';
    return have;
}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 1; i < n; i++) {
        int v, w;
        cin >> v >> w;
        --v;
        g[v].emplace_back(i, w);
        g[i].emplace_back(v, w);
    }
    for (int i = 0; i < q; i++) {
        int v, l, r;
        cin >> v >> l >> r;
        --v, --l, --r;
        cout << query(v, -1, l, r) << '\n';
    }
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

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

//#define int ll
int n, m, k;
const int MAXN = 1e6;
const ll MAXC = 1e9 + 1;
vector<int> g[MAXN];
ll ans = 0;
ll arr[MAXN];
int vs, us;

void dfs(int v, int p, ll c) {
    if (SZ(g[v]) == 1) {
//        cout << v + 1 << ' ' << c << ' '
//             << (lower_bound(arr, arr + m, 1LL * c * (k + 1)) - lower_bound(arr, arr + m, 1LL * c * k)) << '\n';

        ans += k * (lower_bound(arr, arr + m, 1LL * c * (k + 1)) - lower_bound(arr, arr + m, 1LL * c * k));
        return;
    }
    if (1LL * c * (SZ(g[v]) - 1) >= MAXC)
        c = MAXC;
    else
        c = 1LL * c * (SZ(g[v]) - 1);
    for (int u : g[v])
        if (u != p)
            dfs(u, v, c);
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < m; i++)
        cin >> arr[i];
    sort(arr, arr + m);
    for (int i = 0; i + 1 < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (i == 0)
            vs = v, us = u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs(vs, us, 1);
    dfs(us, vs, 1);
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

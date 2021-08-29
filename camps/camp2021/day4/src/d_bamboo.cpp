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
ll gold;
struct Edge {
    ll u, t, d;
};
const int MAXN = 1e5 + 7;
const int MOD = 1e9 + 7;
vector<Edge> g[MAXN];
int perm[MAXN];
int pos[MAXN];
ll t[MAXN];
ll t1[MAXN];
ll prefix_t[MAXN];
ll prefix_t1[MAXN];
ll d[MAXN];
ll prefix_d[MAXN];
ll prefix_td[MAXN];
ll prefix_t1d[MAXN];
int pnt = 0;

ll add(ll a, ll b) {
    return (a + MOD + b) % MOD;
}

ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

void dfs(int v, int p = -1) {
    perm[pnt] = v;
    pos[v] = pnt++;
    for (auto e : g[v]) {
        if (e.u == p)
            continue;
        t[pos[v]] = e.t;
        t1[pos[v] + 1] = e.t;
        d[pos[v]] = e.d;
        dfs(e.u, v);
    }
}

int solve() {
    if (!(cin >> n >> gold))
        return 1;
    for (int i = 0; i + 1 < n; i++) {
        int v, u, t, d;
        cin >> v >> u >> d >> t;
        --v, --u;
        g[v].push_back({u, t, d});
        g[u].push_back({v, t, d});
    }
    int where = -1;
    for (int i = 0; i < n; i++)
        if (SZ(g[i]) == 1) {
            where = i;
            break;
        }
    dfs(where, -1);
    for (int i = 0; i < n; i++) {
        prefix_t[i + 1] = add(prefix_t[i], t[i]);
        prefix_t1[i + 1] = add(prefix_t1[i], t1[i]);
        prefix_d[i + 1] = add(prefix_d[i], d[i]);
    }
    for (int i = 0; i < n; i++) {
        prefix_td[i + 1] = add(prefix_td[i], mul(t[i], prefix_d[i]));
        prefix_t1d[i + 1] = add(prefix_t1d[i], mul(t1[i], prefix_d[i]));
    }
    int q;
    cin >> q;
//    for (int i = 0; i <= n; i++)
//        cout << prefix_t1[i] << " \n"[i == n];
//    for (int i = 0; i <= n; i++)
//        cout << prefix_d[i] << " \n"[i == n];
//    for (int i = 0; i <= n; i++)
//        cout << prefix_t1d[i] << " \n"[i == n];
//    for (int i = 0; i < n; i++)
//        cout << t1[i] << " \n"[i == n - 1];
    for (int i = 0; i < q; i++) {
        int type, x, y;
        cin >> type >> x >> y;
        --x, --y;
        assert(type == 1);
        x = pos[x];
        y = pos[y];
        ll gg, cost;
        if (x > y) {
            gg = mul(gold, add(prefix_d[x], -prefix_d[y]));
            cost = add(mul(prefix_d[x], add(prefix_t1[x + 1], -prefix_t1[y + 1])), -add(prefix_t1d[x + 1], -prefix_t1d[y + 1]));
        } else {
            gg = mul(gold, add(prefix_d[y], -prefix_d[x]));
            cost = add(add(prefix_td[y], -prefix_td[x]), -mul(prefix_d[x], add(prefix_t[y], -prefix_t[x])));
        }
        cout << add(cost, gg) << '\n';
    }
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
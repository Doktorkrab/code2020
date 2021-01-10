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
const int MAXN = 5e4 + 7;
int sz[MAXN];
int start[MAXN];
int tin[MAXN];
int tout[MAXN];
int tree[4 * MAXN];
int id[MAXN];
int arr[MAXN];
int par[MAXN];
vector<int> g[MAXN];
int N;
int timer = 0;

int calc_sz(int v, int p = -1) {
    par[v] = max(0, p);
    sz[v] = 1;
    tin[v] = timer++;
    for (int u : g[v])
        if (u != p)
            sz[v] += calc_sz(u, v);
    int mx = -1;
    for (int i = 0; i < SZ(g[v]); i++)
        if (g[v][i] != p && (mx == -1 || sz[g[v][i]] > sz[g[v][mx]]))
            mx = i;
    if (mx != -1)
        swap(g[v][0], g[v][mx]);
    tout[v] = timer++;
    return sz[v];
}

int pnt = 0;

void build_hld(int v, int p = -1, int start_v = -1) {
    if (start_v == -1)
        start_v = v;
    start[v] = start_v;
    id[v] = pnt;
    tree[pnt++ + N] = arr[v];
    if (!SZ(g[v]))
        return;
    if (g[v][0] != p)
        build_hld(g[v][0], v, start_v);
    for (int u : g[v])
        if (u != p && g[v][0] != u)
            build_hld(u, v, -1);
}

bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int get(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l)
        return 0;
    if (l <= tl && tr <= r)
        return tree[v];
    int tm = (tl + tr) / 2;
    return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
}

void upd(int v, int tl, int tr, int pos, int x) {
    if (pos < tl || tr <= pos)
        return;
    if (tr - tl == 1) {
        tree[v] = x;
        return;
    }
    int tm = (tl + tr) / 2;
    upd(v * 2, tl, tm, pos, x);
    upd(v * 2 + 1, tm, tr, pos, x);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get_ans(int a, int b) {
    int ans = 0;
    for (int i = 0; i < 2; i++) {
        while (!is_anc(start[a], b)) {
            ans = max(ans, get(1, 0, N, id[start[a]], id[a] + 1));
            a = par[start[a]];
        }
        swap(a, b);
    }
    if (id[a] > id[b])
        swap(a, b);
    return max(ans, get(1, 0, N, id[a], id[b] + 1));
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    N = 1;
    while (N < n)
        N *= 2;
    calc_sz(0);
    build_hld(0);
    for (int i = N - 1; i >= 0; i--)
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        char type;
        cin >> type;
        if (type == '?') {
            int a, b;
            cin >> a >> b;
            cout << get_ans(a - 1, b - 1) << '\n';
        } else {
            int a, h;
            cin >> a >> h;
            upd(1, 0, N, id[a - 1], h);
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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

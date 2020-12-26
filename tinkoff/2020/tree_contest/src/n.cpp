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
const int MAXN = 1e5 + 7;
const int MAXLOG = 20;
int bin_p[MAXLOG][MAXN];
vector<int> g[MAXN];
int tin[MAXN], tout[MAXN];
int timer = 0;

void calc_parents(int v, int p) {
    bin_p[0][v] = p;
    for (int i = 1; i < MAXLOG; i++)
        bin_p[i][v] = bin_p[i - 1][bin_p[i - 1][v]];
}

void prepare_lca(int v, int p = -1) {
    tin[v] = timer++;
    calc_parents(v, p);
    for (int u : g[v])
        if (u != p)
            prepare_lca(u, v);
    tout[v] = timer++;
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int a, int b) {
    if (is_anc(a, b))
        return a;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        int v = bin_p[i][a];
        if (!is_anc(v, b))
            a = v;
    }
    return bin_p[0][a];
}

int solve() {
    if (!(cin >> n))
        return 1;
    if (n == 0)
        return 1;
    for (int i = 0; i < n; i++) {
        for (auto &p : bin_p)
            p[i] = 0;
        g[i].clear();
    }
    timer = 1;
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    prepare_lca(0, 0);
    cin >> m;
    int root = 0;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;
        if (type == '!') {
            cin >> root;
            root--;
            continue;
        }
        int a, b;
        cin >> a >> b;
        --a, --b;
        int l = lca(a, b);
        if (l == root || !is_anc(l, root)) {
            cout << l + 1 << '\n';
            continue;
        }
        int l1 = lca(root, a);
        int l2 = lca(root, b);
        if (is_anc(l1, l2))
            swap(l1, l2);
        cout << l1 + 1 << '\n';
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

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
const int MAXN = 3e5 + 7;
vector<int> g[MAXN], g1[MAXN];
int topsort[MAXN], pnt = 0;
int color[MAXN];
bool used[MAXN];

inline void add_edge(int a, int b) {
//    cout << a << "->" << b << '\n';
    g[a].push_back(b);
    g1[b].push_back(a);
}

void build_topsort(int v) {
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            build_topsort(u);
    topsort[pnt++] = v;
}

void paint(int v, int c) {
    color[v] = c;
    for (int u : g1[v])
        if (color[u] == -1)
            paint(u, c);
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < 2 * n; i++) {
        g[i].clear();
        g1[i].clear();
    }
    pnt = 0;
    for (int i = 0; i < m; i++) {
        int x1, v1, x2, v2;
        cin >> x1 >> v1 >> x2 >> v2;
        x1 = x1 * 2 + v1;
        x2 = x2 * 2 + v2;
        add_edge(x1 ^ 1, x2);
        add_edge(x2 ^ 1, x1);
    }
    fill(used, used + 2 * n, false);
    for (int i = 0; i < 2 * n; i++)
        if (!used[i])
            build_topsort(i);

    fill(color, color + 2 * n, -1);
    int c = 0;
    for (int i = 0; i < 2 * n; i++) {
        int v = topsort[2 * n - i - 1];
        if (color[v] == -1)
            paint(v, c++);
    }
    for (int i = 0; i < 2 * n; i += 2) {
        if (color[i] > color[i ^ 1])
            cout << "0";
        else
            cout << "1";
    }
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("n.in", "r", stdin);
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

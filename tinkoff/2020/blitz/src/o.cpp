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
vector<int> g[MAXN];
int pnt[MAXN];
int tin[MAXN];
int fup[MAXN];
int used[MAXN];
pair<int, int> edges[MAXN];
int timer;
int cnt = 0;

int ask(int v) {
    cout << "? " << v + 1 << endl;
    assert(++cnt <= 3 * n);
    int x;
    cin >> x;
    assert(x != -2);
    return x - 1;
}

vector<pair<int, int>> bridges;

int dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int e : g[v]) {
        int u = (edges[e].first ^ edges[e].second ^ v);
        if (e == p)
            continue;
        if (!used[u]) {
            fup[v] = min(fup[v], dfs(u, e));
            if (tin[v] < fup[u])
                bridges.emplace_back(v, u);
        } else {
            fup[v] = min(fup[v], tin[u]);
        }
    }
    return fup[v];
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    if (m > 2 * n) {
        cout << "! No" << endl;
        return 1;
    }
    int pnt = 0;
    for (int i = 0; i < n; i++) {
        while (true) {
            int x = ask(i);
            if (x < 0)
                break;
            edges[pnt] = {i, x};
            g[i].push_back(pnt);
            g[x].push_back(pnt++);
        }
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);
    if (SZ(bridges) >= (m + 1) / 2) {
        cout << "! Yes" << endl;
        for (int i = 0; i < (m + 1) / 2; i++)
            cout << bridges[i].first + 1 << ' ' << bridges[i].second + 1 << '\n';
        return 1;
    }
    cout << "! No" << endl;
    return 1;
}

signed main() {
//#ifdef LOCAL
//    freopen("o.in", "r", stdin);
//#endif
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
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

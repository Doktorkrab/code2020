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
const int MAXN = 2e5 + 7;
vector<int> g[MAXN];
pair<int, int> edges[2 * MAXN];
int bus[4 * MAXN];
bool used[MAXN];
bool rdy[MAXN];
int orig[MAXN];
int pnt = 0;

void dfs(int v) {
    orig[v] = pnt++;
    bus[orig[v]] = v;
    used[v] = true;
    for (int e : g[v]) {
        auto &[u1, u2] = edges[e];
        int nxt = (u2 ^ u1 ^ v);
        if (used[nxt]) {
            continue;
        }
        rdy[e] = true;
        dfs(nxt);
    }
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(i);
        g[u].push_back(i);
        edges[i] = {v, u};
    }
    dfs(0);
    for (int i = 0; i < m; i++) {
        if (rdy[i]) {
            auto &[v, u] = edges[i];
            v = orig[v];
            u = orig[u];
        }
    }
    for (int i = 0; i < m; i++) {
        if (!rdy[i]) {
            bus[pnt] = edges[i].second;
            edges[i].second = pnt++;
            edges[i].first = orig[edges[i].first];
        }
    }
    cout << pnt << '\n';
    for (int i = 0; i < pnt; i++)
        cout << bus[i] + 1 << " \n"[i + 1 == pnt];
    for (int i = 0;i < m; i++)
        cout << edges[i].first + 1 << ' ' << edges[i].second + 1 << '\n';
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

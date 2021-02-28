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
vector<int> g[MAXN];
int ans[MAXN];

void dfs(int v, int d = 0, int p = -1) {
    ans[d]++;
    for (int u : g[v]) {
        if (u != p)
            dfs(u, d + 1, v);
    }
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        g[--v].push_back(--u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++)
        dfs(i);
    for (int i = 1; i < n; i++)
        cout << ans[i] / 2 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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

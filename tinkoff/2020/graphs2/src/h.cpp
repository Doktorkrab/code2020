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

int n, m, q;
const int MAXN = 2e5 + 7;
vector<int> g[2 * MAXN];
bool used[2 * MAXN];

void dfs(int v) {
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            dfs(u);
}

int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < n + m; i++)
        g[i].clear(), used[i] = false;

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        g[x].push_back(y + n);
        g[y + n].push_back(x);
    }
    int ans = 0;
    for (int i = 0; i < n + m; i++)
        if (!used[i])
            ans++, dfs(i);
    cout << ans - 1 << '\n';
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

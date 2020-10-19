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

const int MAXN = 3e5 + 7;
int n, m;
vector<int> g[MAXN];
bool used[MAXN];


int solve() {
    if (!(cin >> n >> m))
        return 1;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        for (int u : g[i])
            used[u] = true;
        for (int u : g[i]) {
            if (make_pair(SZ(g[u]), u) >= make_pair(SZ(g[i]), i))
                continue;
            for (int w : g[u])
                if (make_pair(SZ(g[w]), w) < make_pair(SZ(g[u]), u) && used[w]) {
//                    cout << i << ' ' << u << ' ' << w << '\n';
                    ans++;
                }
        }
        for (int u : g[i])
            used[u] = false;
    }
    cout << ans << '\n';
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

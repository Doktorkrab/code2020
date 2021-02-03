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

int n, root;
const int MAXN = 1e5 + 7;
vector<pair<int, int>> g[MAXN];
int dp[MAXN];

int get_ans(int v, int p = -1) {
    dp[v] = 0;
//    cout << "in " << v + 1 << '\n';
    for (auto[u, _] : g[v])
        if (u != p)
            dp[v] ^= get_ans(u, v) + 1;
//    cout << "out " << v + 1 << '\n';
    return dp[v];
}

int restore_ans(int v, int p = -1, int need = 0) {
    for (auto[u, x] : g[v]) {
        if (u == p)
            continue;
        int want = dp[v] ^(dp[u] + 1);
        if (want == need)
            return x;
        int y = restore_ans(u, v, (want ^ need) - 1);
        if (y != -1)
            return y;
    }
    return -1;
}

int solve() {
    if (!(cin >> n >> root))
        return 1;
    root--;
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].emplace_back(u, i);
        g[u].emplace_back(v, i);
    }
    if (get_ans(root, -1) == 0) {
        cout << "2\n";
        return 0;
    }
//    for (int i = 0; i < n; i++)
//        cout << dp[i] << " \n"[i + 1 == n];
    cout << "1\n" << restore_ans(root, -1, 0) + 1 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("i.in", "r", stdin);
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

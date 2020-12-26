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
const int MAXN = 2e3 + 7;
bool g[MAXN][MAXN];
ll costs1[MAXN];
pair<ll, int> costs[MAXN];
ll get_ans(){
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll best = 0;
        for (int j = i + 1; j < n; j++) {
            if (g[i][j] || i == j)
                continue;
            for (int k = 0; k < n; k++) {
                if (costs[k].second != i && costs[k].second != j) {
                    ans = max(ans, costs1[i] + costs1[j] + costs[k].first);
                    best = max(best, costs1[i] + costs1[j] + costs[k].first);
                    break;
                }
            }
        }
//        cout << best << ' ';
    }
//    cout << '\n';
    return ans;
}

int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> costs[i].first;
        costs[i].second = i;
        costs1[i] = costs[i].first;
    }
    sort(costs, costs + n);
    reverse(costs, costs + n);
    for (int i  = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v][u] = g[u][v] = true;
    }
    for (int i = 0; i < q; i++){
        int type, v, u;
        cin >> type >> v >> u;
        --v, --u;
        if (type == 1)
            g[v][u] = g[u][v] = true;
        else if (type == 2)
            g[u][v] = g[v][u] = false;
        cout << get_ans() << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

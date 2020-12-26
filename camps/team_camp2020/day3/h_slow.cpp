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
 
int n, m, k;
const int MAXN = 5e5 + 7;
vector<int> g[MAXN];
int color[MAXN];
int par[MAXN];
bool used[MAXN];
int chosen[MAXN];
bool dfs(int v, int p){
    used[v] = true;
    par[v] = p;
    for (int u : g[v])
        if (!chosen[color[u]])
            continue;
        else if (used[u] && par[u] != 1 - p)
            return true;
        else if (!used[u] && dfs(u, 1 - p))
            return true;
    return false;
}
int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> color[i];
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int ans = 0;
    for (int i = 1; i <= k; i++)
        for (int j = i + 1; j <= k; j++){
            fill(used, used + n, 0);
            fill(par, par + n, -1);
            chosen[i] = chosen[j] = 1;
            bool good = true;
            for (int v = 0; v < n; v++)
                if (!used[v] && chosen[color[v]]) {
                    int t = !dfs(v, 0);
//                    cout << i << " " << j << ' ' << v << ' ' << t << '\n';
                    good &= t;
                }
            if (good) {
                ans++;
//                cout << i << ' ' << j << '\n';
            }
            chosen[i] = chosen[j] = 0;
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

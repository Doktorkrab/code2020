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
const int MAXN = 2e4;
vector<int> g[MAXN];
int cost[MAXN];

 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    int best = 0;
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
        best += cost[i];
    }
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    auto get = [&](int a, int b){
        return (a >> b) & 1;
    };
    for (int mask = 0; mask < (1 << n); mask++){
        bool good = true;
        int ans = 0;
        for (int i = 0; i < n; i++){
            if (get(mask, i)){
                ans += cost[i];
                continue;
            }
            int cnt = 0;
            for (int u : g[i]){
                if (get(mask, u)){
                    cnt = 1;
                    break;
                }
            }
            if (!cnt){
                good = false;
                break;
            }
        }
        if (good)
            best = min(ans, best);
    }
    cout << best << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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

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
 
int n, m, d, q;
const int MAXN = 2e5 + 7;
pair<int, pair<int, int>> edges[MAXN];
int color[MAXN];
 
int solve() {
    if (!(cin >> n >> m >> d >> q))
        return 1;
    for (int i = 0; i < m; i++){
        int v, u, c;
        cin >> v >> u >> c;
        --v, --u;
        edges[i] = {c, {v, u}};
    }
    for (int i = 0; i < n; i++)
        cin >> color[i];
    for (int i = 0; i < q; i++){
        int y, x;
        cin >> y >> x;
        color[--y] = x;
        int ans = TMAX(int);
        for (int j = 0; j < m; j++){
            auto [c, tt] = edges[j];
            auto [v, u] = tt;
            if (color[v] != color[u])
                ans = min(ans, c);
        }
        cout << ans << '\n';
    }
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

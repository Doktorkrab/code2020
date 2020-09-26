#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll

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
 
int n, m, p;
const int MAXN = 4e4 + 7;
vector<int> g1[MAXN], g2[MAXN];
int dp1[MAXN], dp2[MAXN];
int a[MAXN], b[MAXN];
 
int solve() {
    if (!(cin >> n >> m >> p))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        g1[i].clear();
        dp1[i] = a[i];
    }
    for (int i = 0; i < m; i++){
        cin >> b[i];
        g2[i].clear();
        dp2[i] = b[i];
    }

    for (int i = 0; i < p; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g1[v].push_back(u);
        g2[u].push_back(v);
    }
    for (int i = 0; i < n; i++){
        sort(ALL(g1[i]));
        g1[i].erase(unique(ALL(g1[i])), g1[i].end());
    }
    for (int i = 0; i < m; i++){
        sort(ALL(g2[i]));
        g2[i].erase(unique(ALL(g2[i])), g2[i].end());
    }
    for (int i = 0; i < n; i++){
        int have = 0;
        for (int u : g1[i]){
            int was = dp2[u];
            dp2[u] = max(dp2[u], have + a[i] + b[u]);
            have = max(have, was);
        }
    }
    for (int i = 0; i < m; i++){
        int have = 0;
        for (int u : g2[i]){
            int was = dp1[u];
            dp1[u] = max(dp1[u], have + b[i] + a[u]);
            have = max(have, was);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, dp1[i]);
    for (int i = 0; i < m; i++)
        ans = max(ans, dp2[i]);
    cout << ans << '\n';
    //for (int i = 0; i < n; i++)
        //cout << dp1[i] << " \n"[i + 1 == n];
    //for (int i = 0; i < m; i++)
        //cout << dp2[i] << " \n"[i + 1 == m];
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

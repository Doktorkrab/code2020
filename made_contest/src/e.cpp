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
vector<int> g[MAXN], g1[MAXN];
vector<int> gn[MAXN];
int p[MAXN];
int p_min[MAXN], p_max[MAXN];
int dp[MAXN];
bool used[MAXN];

vector<int> topsort;
int comp[MAXN];
multiset<int> enters[MAXN];

int get_ans(int v){
    if (used[v])
        return max(dp[v], p_max[v]);
    used[v] = true;
    for (int u : gn[v])
        dp[v] = max(dp[v], get_ans(u));
    return max(dp[v], p_max[v]);
}

void get_topsort(int v){
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            get_topsort(u);
    topsort.push_back(v);
}

void paint(int v, int c){
    comp[v] = c;
    enters[c].insert(p[v]);
    p_max[c] = max(p_max[c], p[v]);
    p_min[c] = min(p_min[c], p[v]);
    for (int u : g1[v])
        if (comp[u] == -1)
            paint(u, c);
}
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        gn[i].clear();
        g[i].clear();
        g1[i].clear();
        enters[i].clear();
    }
    for (int i = 0; i < n; i++){
        cin >> p[i];
    }
    fill(used, used + n, 0);
    fill(dp, dp + n, TMIN(int));
    fill(p_max, p_max + n, TMIN(int));
    fill(p_min, p_min + n, TMAX(int));
    fill(comp, comp + n, -1);

    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g1[u].push_back(v);
    }

    for (int i = 0; i < n; i++)
        if (!used[i])
            get_topsort(i);

    reverse(ALL(topsort));
    int color = 0;
    for (int v : topsort){
        if (comp[v] == -1){
            paint(v, color++);
        }
    }
//    for (int i = 0; i < n; i++)
//        cout << comp[i] << " \n"[i + 1 == n];
    ll ans = TMIN(int);
    for (int i = 0; i < n; i++){
        auto& kek = enters[comp[i]];
        kek.erase(kek.find(p[i]));
        if (SZ(kek) != 0)
            ans = max(ans, (*kek.rbegin()) - 1LL * p[i]);
        kek.insert(p[i]);
        for (int u : g[i]){
            if (comp[u] != comp[i])
                gn[comp[i]].push_back(comp[u]);
        }
    }
    fill(used, used + n, 0);
    for (int i = 0; i < color; i++){
        get_ans(i);
        ans = max(ans, 1LL * dp[i] - p_min[i]);
    }
//    for (int i = 0; i < n; i++)
//        cout << dp[i] << " \n"[i + 1 == n];
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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

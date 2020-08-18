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
const int MAXN = 2e5 + 7;
vector<int> g[MAXN];
int sz[MAXN];
int par[MAXN];
int used[MAXN];

int calc_sz(int v, int p){
    sz[v] = 1;
    for (int u : g[v])
        if (u != p && !used[u])
            sz[v] += calc_sz(u, v);
    return sz[v];
}

int find_centroid(int v, int p, int need){
    for (int u : g[v])
        if (u != p && !used[u] && sz[u] > need / 2)
            return find_centroid(u, v, need);
    return v;
}
int decompose(int v){
    if (sz[v] == 1){
        return v;
    }
    calc_sz(v, -1);
    v = find_centroid(v, -1, sz[v]);
    // cout << v + 1 << '\n';
    used[v] = 1;
    for (int u : g[v])
        if (!used[u]){
            par[decompose(u)] = v;
        }
    return v;
}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        g[i].clear();
        sz[i] = 0;
        par[i] = -1;
        used[i] = 0;
    }
    for (int i = 1; i < n; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    decompose(0);
    int cnt = 0;
    for (int i = 0; i < n; i++)
        cnt += (par[i] == -1);
    assert(cnt == 1);
    for (int i = 0; i < n; i++)
        cout << par[i] + 1 << " \n"[i + 1 == n];
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
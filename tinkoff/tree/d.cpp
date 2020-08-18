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
const int MAXN = 1e5 + 7;
const int INF = 1e9 + 7;
vector<int> g[MAXN];
int sz[MAXN];
vector<pair<int, int>> par[MAXN];
int color[MAXN];
vector<int> colors[MAXN];
vector<pair<int, int>> queryes[MAXN];
int ans[MAXN];
int used[MAXN];
int l[MAXN];
int calc_size(int v, int p){
    sz[v] = 1;
    for (int u : g[v])
        if (u != p && !used[u])
            sz[v] += calc_size(u, v);
    return sz[v];
}

void push_parent(int v, int p, int x, int d){
    par[v].push_back({x, d});
    for (int u : g[v])
        if (u != p && !used[u])
            push_parent(u, v, x, d + 1);
}

int find_centroid(int v, int p, int need){
    for (int u : g[v])
        if (u != p && !used[u] && sz[u] > need / 2)
            return find_centroid(u, v, need);
    return v;
}

void decompostion(int v){
    calc_size(v, -1);
    if (sz[v] == 1){
        par[v].push_back({v, 0});
        return;
    }

    v = find_centroid(v, -1, sz[v]);
    used[v] = 1;
    push_parent(v, -1, v, 0);
    for (int u : g[v])
        if (!used[u])
            decompostion(u);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        g[i].clear();
        par[i].clear();
        color[i] = used[i] = 0;
        colors[i].clear();
        queryes[i].clear();
        l[i] = INF;
    }

    for (int i = 1; i < n; i++){
        int x;
        cin >> x;
        g[i].push_back(x);
        g[x].push_back(i);
    }
    for (int i = 0; i < n; i++){
        cin >> color[i];
        colors[color[i]].push_back(i);
    }
    decompostion(0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        int v, c;
        cin >> v >> c;
        ans[i] = INF;
        queryes[c].push_back({v, i});

    }
    for (int i = 0; i < n; i++){
        for (int v : colors[i])
            for (auto [u, w] : par[v])
                l[u] = min(l[u], w);
        for (auto [v, id] : queryes[i]){
            for (auto [u, w] : par[v])
                ans[id] = min(ans[id], l[u] + w);
        }

        for (int v : colors[i])
            for (auto [u, w] : par[v])
                l[u] = INF;
    }
    for (int i = 0; i < m; i++)
        if (ans[i] >= INF)
            cout << -1 << " \n"[i + 1 == m];
        else
            cout << ans[i] << " \n"[i + 1 == m];
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
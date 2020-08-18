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
const int MAXN = 1e5 + 7;
vector<int> g[MAXN];
vector<int> g1[MAXN];
int color[MAXN];
int used[MAXN];
int sz[MAXN];
vector<int> comps[MAXN];
vector<int> topsort;
void paint(int v, int c){
    color[v] = c;
    sz[c]++;
    comps[c].push_back(v);
    for (int u : g1[v]){
        if (color[u] == -1)
            paint(u, c);
    }
}
void dfs(int v){
    used[v] = 1;
    for (int u : g[v]){
        if (!used[u])
            dfs(u);
    }
    topsort.push_back(v);
}
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g1[u].push_back(v);
    }
    for (int i = 0; i < n; i++){
        if (!used[i])
            dfs(i);
    }
    reverse(ALL(topsort));
    fill(color, color + n, -1);
    int c = 0;
    for (int i : topsort)
        if (color[i] == -1){
            paint(i, c);
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
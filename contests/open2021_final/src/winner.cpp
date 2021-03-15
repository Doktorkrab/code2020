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
vector<int> g[MAXN];
int depth[MAXN];
int parents[MAXN];
int max_depth[MAXN];

void calc_depth(int v, int d, int p){
    depth[v] = d;
    parents[v] = p;
    for (int u : g[v])
        if (u != p)
            calc_depth(u, d + 1, v);
}
int ans, ban;

int calc_up(int v, int p){
    max_depth[v] = 0;
    for (int u : g[v]){
        if (u == p || u == ban)
            continue;
        max_depth[v] = max(max_depth[v], calc_up(u, v) + 1);
    }
    return max_depth[v];
}


void calc_down(int v, int p){
    max_depth[v] = 0;
    for (int u : g[v]){
        if (u == p)
            continue;
        calc_down(u, v);
        if (v == ban)
            ans = max(ans, min(max_depth[v], depth[v] - 1) + max_depth[u] + 1);
        max_depth[v] = max(max_depth[v], max_depth[u] + 1);
    }
}

 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i + 1 < n; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 3; i < 4; i++){
        calc_depth(i, 0, -1);
        bool good = false;
        for (ban = 0; ban < n; ban++){
            if (i == ban)
                continue;
            ans = 0;
            calc_down(ban, parents[ban]);
            calc_up(i, -1);
//            for (int j = 0; j < n; j++)
//                cout << max_depth[j] << " \n"[j + 1 == n];
//            cout << ans << ' ' << max_depth[parents[ban]] + depth[parents[ban]] << ' ' << parents[ban] << '\n';
            if (max_depth[parents[ban]] + depth[parents[ban]] > ans){
                good = true;
                break;
            }
        }
        if (good){
//            cout << i + 1 << '\n';
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("winner.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

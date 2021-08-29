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
 
int n, m, s, t;
const int MAXN = 2e5 + 7;
const ll INF = 1e18;
vector<pair<int, int>> g[MAXN];
ll dist[MAXN];
int parent[MAXN];
bool used[MAXN];

void dijkstra(int s, int t){
    fill(dist, dist + n, INF);
    fill(used, used + n, false);
    fill(parent, parent + n, -1);
    dist[s] = 0;
    for (int i = 0; i < n; i++){
        int v = -1;
        for (int u = 0; u < n; u++){
            if (!used[u] && (v == -1 || dist[v] > dist[u]))
                v = u;
        }
        if (v == -1)
            break;
        used[v] = true;
        for (auto [u, w] : g[v]){
            if (dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;
                parent[u] = v;
            }
        }
    }
}

int solve() {
    if (!(cin >> n >> m >> s >> t))
        return 1;
    --s, --t;
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < m; i++){
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
    }
    dijkstra(s, t);
    if (dist[t] >= INF)
        cout << "-1\n";
    else {
        cout << dist[t] << '\n';
        vector<int> ans;
        int v = t;
        while (v != -1){
            ans.push_back(v);
            v = parent[v];
        }
        reverse(ALL(ans));
        cout << SZ(ans) << '\n';
        for (int v : ans)
            cout << v + 1 << " ";
        cout << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("dijkstra_without_heap.in", "r", stdin);
#else
    freopen("dist.in", "r", stdin);
    freopen("dist.out", "w", stdout);
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

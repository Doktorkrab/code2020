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
const int MAXN = 50;
const int INF = 1e9;
pair<int, string> dist[MAXN];
string have[MAXN];
vector<int> g[MAXN];
bool used[MAXN];
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        g[i].clear();
        cin >> have[i];
    }
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    fill(dist, dist + n, make_pair(INF, ""));
    dist[0] = {SZ(have[0]), have[0]};
    set<pair<pair<int, string>, int>> q = {{dist[0], 0}};
    fill(used, used + n, false);
    while (SZ(q)){
        auto [d, v] = (*q.begin());
        q.erase(q.begin());
        if (used[v])
            continue;
        used[v] = true;
        for (int u : g[v]){
            pair<int, string> nxt = {d.first + SZ(have[u]), d.second + have[u]};
            if (dist[u] > nxt){
                dist[u] = nxt;
                q.emplace(dist[u], u);
            }
        }
    }
    cout << dist[n - 1].second << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

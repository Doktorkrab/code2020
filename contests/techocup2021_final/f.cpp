#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
//#define int ll
#define SZ(X) (int)(X).size()
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define TMAX(X) numeric_limits<X>::max();
#define TMIN(X) numeric_limits<X>::min();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;
int add(int a, int b){
    return ((a + b) % MOD + MOD) % MOD;
}

int mul(int a, int b){
    return (1LL * a * b) % MOD;
}


int n, m, q;
const int MAXN = 600;
const ll INF = 1e18;
ll dist[MAXN][MAXN];
vector<pair<int, ll>> triples[MAXN];
vector<pair<int, ll>> g[MAXN];
ll dist_dijkstra[MAXN];
pair<pair<int, int>, ll> edges[600 * 600];
bool used[MAXN];
bool ans[MAXN * MAXN];
void dijkstra(int start_v){
    fill(dist_dijkstra, dist_dijkstra + n, INF);
    fill(used, used + n, false);
    for (auto [a, b] : triples[start_v])
        dist_dijkstra[a] = -b;
    for (int i = 0; i < n; ++i){
        int v = -1;
        for (int j = 0; j < n; j++){
            if (!used[j] && (v == -1 || dist_dijkstra[v] > dist_dijkstra[j]))
                v = j;
        }
        if (v == -1)
            break;
        used[v] = true;
        for (auto [u, w] : g[v])
            if (dist_dijkstra[u] > dist_dijkstra[v] + w)
                dist_dijkstra[u] = dist_dijkstra[v] + w;
    }
}
int solve(){
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        triples[i].clear(), g[i].clear();
    fill(ans, ans + m, false);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = INF;
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;
    for (int i = 0; i < m; i++){
        int v, u;
        ll w;
        cin >> v >> u >> w;
        --v, --u;
        dist[v][u] = min(dist[v][u], w);
        dist[u][v] = min(dist[u][v], w);
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
        edges[i] = {{v, u}, w};
    }
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    cin >> q;
    for (int i = 0; i < q; i++){
        int v, u, l;
        cin >> v >> u >> l;
        --v, --u;
        triples[v].emplace_back(u, l);
    }
    for (int i = 0; i < n; i++){
        dijkstra(i);
        for (int j = 0; j < m; j++){
            auto [e, w] = edges[j];
            auto [v, u] = e;
            if ((-dist[i][v] - w >= dist_dijkstra[u]) || (-dist[i][u] - w >= dist_dijkstra[v]))
                ans[j] = true;
        }
    }
    cout << count(ans, ans + m, true) << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1;
    for (int test = 1; test <= tests; test++){
        if (solve())
            break;
#ifdef LOCAL
        cout << "-----------\n";
#endif
    }
    return 0;
}

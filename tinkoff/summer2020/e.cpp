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
vector<int> g_rev[MAXN];
vector<int> g1[MAXN];
vector<int> g1_rev[MAXN];
bool used[MAXN];
bool from_start[2][MAXN];
int sz[MAXN];
int color[MAXN];
int degree[2][MAXN];
int dp[2][MAXN];
vector<int> topsort;

void build_topsort(int v){
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            build_topsort(u);
    topsort.push_back(v);
}

void paint(int v, int c){
    color[v] = c;
    sz[c]++;
    for (int u : g_rev[v])
        if (color[u] == -1)
            paint(u, c);
}
void mark(int v, bool rev){
    from_start[rev][v] = true;
    for (int u : g1[v])
        if (!from_start[rev][u])
            mark(u, rev);
    if (!rev){
        for (int u : g1_rev[v])
            if (!from_start[1][u])
                mark(u, true);
    }
}
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g_rev[u].push_back(v);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            build_topsort(i);
    //for (int i : topsort)
        //cout << i + 1 << ' ';
    //cout << '\n';
    reverse(ALL(topsort));
    fill(color, color + n, -1);
    int c = 0;
    for (int i : topsort)
        if (color[i] == -1)
            paint(i, c++);
    for (int v = 0; v < n; v++)
        for (int u : g[v])
            if (color[v] != color[u]){
                g1[color[v]].push_back(color[u]);
                g1_rev[color[u]].push_back(color[v]);
            }
    //for (int i = 0; i < n; i++)
        //cout << color[i] << " \n"[i + 1 == n];
    n = c;
    //cout << n << '\n';
    for (int i = 0; i < n; i++){
        sort(ALL(g1[i]));
        g1[i].erase(unique(ALL(g1[i])), g1[i].end());
        sort(ALL(g1_rev[i]));
        g1_rev[i].erase(unique(ALL(g1_rev[i])), g1_rev[i].end());
    }
    mark(color[0], 0);
    for (int i = 0; i < n; i++){
        for (int u : g1_rev[i]){
            if (from_start[0][u])
                degree[0][i]++;
            if (from_start[1][u])
                degree[1][i]++;
        }
        for (int u : g1[i])
            if (from_start[0][u])
                degree[1][i]++;
    }
    
    //for (int gg = 0; gg < 2; gg++){
        //for (int i = 0; i < n; i++)
            //cout << degree[gg][i] << " \n"[i + 1 == n];
        //cout << '\n';
    //}
    //cout << "xxxxxxxxxxxxxxxxxxxxxxx\n";
    deque<pair<int, int>> have = {{0, color[0]}};
    fill(dp[0], dp[0] + n, 0);
    fill(dp[1], dp[1] + n, 0);
    //degree[1][0] = 0; // pls, never update
    while (!have.empty()){
        auto [rev, v] = have.front();
        have.pop_front();
        for (int u : g1[v]){
            dp[rev][u] = max(dp[rev][u], dp[rev][v] + sz[v]);
            //cout << v << " -> " << u << '\n';
            degree[rev][u]--;
            //cout << degree[rev][u] << '\n';
            if (degree[rev][u] == 0)
                have.push_back({rev, u});
        }
        if (rev == 0){
            for (int u : g1_rev[v]){
                dp[1][u] = max(dp[1][u], dp[rev][v] + sz[v]);
                //cout << v << " ->(rev) " << u << '\n';
                degree[1][u]--;
                if (degree[1][u] == 0){
                    have.push_back({1, u});
                }
            }
        }
    }
    //for (int gg = 0; gg < 2; gg++){
        //for (int i = 0; i < n; i++)
            //cout << dp[gg][i] << " \n"[i + 1 == n];
        //cout << '\n';
    //}
    cout << max(sz[color[0]], max(dp[0][color[0]], dp[1][color[0]])) << '\n';
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

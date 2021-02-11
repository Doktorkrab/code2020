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
 
int n, m, l;
const int MAXN = 1e4 + 7;
vector<int> g[MAXN], g1[MAXN], g2[MAXN];
int topsort[MAXN];
int color[MAXN];
bool used[MAXN];
int cnt[MAXN];
int mark[MAXN];
int dp[MAXN];
int pnt = 0;

void dfs(int v){
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            dfs(u);
    topsort[pnt++] = v;
}

void paint(int v, int c){
    color[v] = c;
    cnt[c] += mark[v];
    for (int u : g1[v])
        if (color[u] == -1)
            paint(u, c);
}

int calc_dp(int v){
    if (used[v])
        return dp[v];
    for (int u : g[v])
        dp[v] = max(dp[v], calc_dp(u) + cnt[v]);
    return dp[v];
}

int solve() {
    if (!(cin >> n >> m >> l))
        return 1;
    for (int i = 0; i <= l; i++){
        if (i - m >= 0) {
            g[i].push_back(i - m);
            g1[i - m].push_back(i);
        }
        if (i + n <= l){
            g[i].push_back(i + n);
            g1[i + n].push_back(i);
        }
    }
    int f;
    cin >> f;
    for (int i = 0; i < f; i++){
        int x;
        cin >> x;
        mark[x]++;
    }
    for (int i = 0; i <= l; i++)
        if (!used[i])
            dfs(i);
    reverse(topsort, topsort + l + 1);
    int c = 0;
    fill(color, color + l + 1, -1);
    for (int i = 0; i <= l; i++)
        if (color[i] == -1)
            paint(i, c++);
    for (int i = 0; i <= l; i++)
        for (int u : g[i])
            if (color[i] != color[u])
                g2[color[i]].push_back(color[u]);
    fill(used, used + c, 0);
    cout << calc_dp(color[0]) << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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

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
const int MAXN = 4e5 + 7;
vector<int> g[MAXN];
vector<int> g1[MAXN];
int a[MAXN];
int dp_tree[2][MAXN];
int used[MAXN];
int on_cycle[MAXN];
int timer;
pair<int, int> edges[MAXN];
vector<int> was;
vector<int> cycle;
bool find_cycle(int v, int p = -1){
    used[v] = timer;
    was.push_back(v);
    for (int x : g1[v]){
        if (x == p)
            continue;
        int u = v ^ edges[x].first ^ edges[x].second;
        if (used[u] == timer){
            int pnt = SZ(was) - 1;
            while (pnt >= 0 && was[pnt] != u){
                cycle.push_back(was[pnt]);
                on_cycle[was[pnt--]] = true;
            }
            cycle.push_back(u);
            on_cycle[u] = true;
            was.pop_back();
            return true;
        }
        if (used[u] != timer && find_cycle(u, x)) {
            was.pop_back();
            return true;
        }
    }
    was.pop_back();
    return false;
}

void calc_dp_tree(int v, int p = -1){
    dp_tree[0][v] = 0;
    dp_tree[1][v] = 1;
    for (int u : g[v]){
        if (u == p || on_cycle[u])
            continue;
        calc_dp_tree(u, v);
        dp_tree[1][v] += dp_tree[0][u];
        dp_tree[0][v] += max(dp_tree[1][u], dp_tree[0][u]);
    }
}
void mark_used(int v){
    used[v] = timer;
    for (int u : g[v])
        if (used[u] != timer)
            mark_used(u);
}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    fill(used, used + n, -1);
    timer = 0;
    int pnt1 = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] != -1) {
            a[i]--;
            g[a[i]].push_back(i);
            g1[a[i]].push_back(pnt1);
            g[i].push_back(a[i]);
            g1[i].push_back(pnt1);
            edges[pnt1++] = {i, a[i]};
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (used[i] != -1)
            continue;
        ++timer;
        if (!find_cycle(i)){
            calc_dp_tree(i);
            ans += max(dp_tree[0][i], dp_tree[1][i]);
            continue;
        }
        ++timer;
        mark_used(i);
        for (int x : cycle)
            calc_dp_tree(x);
        int best = 0;
        for (int frst = 0; frst < 2; frst++){
            vector<vector<int>> dp(2, vector<int>(SZ(cycle)));
            dp[frst][0] = dp_tree[frst][cycle[0]];
            for (int j = 1; j + 1 < SZ(cycle); j++){
                dp[0][j] = dp_tree[0][cycle[j]] + max(dp[0][j - 1], dp[1][j - 1]);
                dp[1][j] = dp_tree[1][cycle[j]] + dp[0][j - 1];
            }
            int m = SZ(cycle) - 1;
            if (m != 0) {
                dp[0][m] = dp_tree[0][cycle[m]] + max(dp[0][m - 1], dp[1][m - 1]);
                if (!frst)
                    dp[1][m] = dp_tree[1][cycle[m]] + dp[0][m - 1];
            }
            best = max(best, max(dp[0][m], dp[1][m]));
        }
        for (int x : cycle)
            on_cycle[x] = false;
        cycle.clear();
        ans += best;
//        assert(0);
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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

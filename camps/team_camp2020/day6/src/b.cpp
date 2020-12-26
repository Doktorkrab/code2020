#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

#define int ll
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

const int MAXN = 17;
int edges[MAXN];
pair<int, int> adj[] = {{0,  1},
                        {1,  2},
                        {2,  3},
                        {0,  4},
                        {1,  5},
                        {2,  6},
                        {3,  7},
                        {4,  5},
                        {5,  6},
                        {6,  7},
                        {4,  8},
                        {5,  9},
                        {6,  10},
                        {7,  11},
                        {8,  9},
                        {9,  10},
                        {10, 11}};
int deg[MAXN];
int cnt[MAXN];
int comp[MAXN];
ll sum[MAXN];
ll sum_e[MAXN];
int cnt_odd[MAXN];
int used[MAXN];
unsigned n = 12, m = 17;
unsigned mask;
vector<int> g[MAXN];
void paint(int v, int c){
    comp[v] = c;
    used[v] = true;
    deg[v] = 0;
    for (int i : g[v]){
        int u = adj[i].first + adj[i].second - v;
        deg[v] += cnt[i] - (int)((mask >> i) & 1);
        sum[c] += sum_e[i];
        if ((mask >> i) & 1)
            sum[c]--;
        if (used[u] || (cnt[i] - (int)((mask >> i) & 1)) == 0)
            continue;
        paint(u, c);
    }
    cnt_odd[c] += (deg[v] & 1);
}
int solve() {
    if (!(cin >> edges[0]))
        return 1;
    for (int i = 1; i < 17; i++) {
        cin >> edges[i];
    }
    for (int i = 0; i < 17; i++){
        int x = edges[i];
        while (x > 0)
            sum_e[i] += (x + 1) / 2, cnt[i]++, x /= 2;
    }
//    for (int i = 0; i < m; i++)
//        cout << sum_e[i] << " \n"[i + 1 == m];
    int ind = 0;
    for (auto [a, b] : adj){
        g[a].push_back(ind);
        g[b].push_back(ind++);
    }
    ll ans = 0;
    for (mask = 0; mask < (1U << m); mask++){
        bool good = true;
        fill(deg, deg + n, 0);
        for (unsigned i = 0; i < m; i++)
            if (cnt[i] == 0 && ((mask >> i) & 1U)){
                good = false;
                break;
            }
        if (!good)
            continue;
        fill(comp, comp + n, -1);
        fill(sum, sum + n, 0);
        fill(used, used + n, 0);
        fill(deg, deg + n, 0);
        fill(cnt_odd, cnt_odd + n, 0);
        int c = 0;
        for (int i = 0; i < n; i++)
            if (!used[i])
                paint(i, c++);
        for (int i = 0; i < c; i++)
            if (cnt_odd[i] == 2 || cnt_odd[i] == 0)
                ans = max(ans, sum[i] / 2);
    }
    cout << ans << '\n';
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

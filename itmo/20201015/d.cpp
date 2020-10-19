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
const int MAXN = 2e5 + 7;
vector<pair<int, char>> g[MAXN];
int d[MAXN];
bool used[MAXN];
int p[MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    fill(d, d + n, n + 100);
    for (int i = 0; i < m; i++){
        int v, u;
        char x;
        cin >> v >> u >> x;
        --v, --u;
        g[v].emplace_back(u, x);
        g[u].emplace_back(v, x);
    }
    d[n - 1] = 0;
    deque<int> have = {n - 1};
    while (!have.empty()){
        int top = have.front();
        have.pop_front();
        if (used[top])
            continue;
        used[top] = true;
        for (auto [x, c] : g[top])
            if (d[x] > d[top] + 1){
                d[x] = d[top] + 1;
                have.push_back(x);
            }
    }
//    cerr << "here\n";
//    for (int i = 0; i < n; i++)
//        cerr << d[i] << " \n"[i + 1 == n];
    vector<int> cur_layer = {0};
    string ans;
    fill(used, used + n, 0);
    fill(p, p + n, -1);
    while (1){
//        assert(SZ(cur_layer));
        bool good = true;
        for (int x : cur_layer)
            good &= (x != n - 1);
        if (!good)
            break;
        vector<int> next_layer;
        char mn = TMAX(char);
        for (int x : cur_layer)
            for (auto [v, c] : g[x]) {
//                cerr << d[v] << ' ' << d[x] << ' ' << v << ' ' << x << '\n';
                if (d[v] + 1 == d[x])
                    mn = min(c, mn);
            }
        ans += mn;
        for (int x : cur_layer)
            for (auto [v, c] : g[x])
                if (d[v] + 1 == d[x] && c == mn && !used[v]){
                    next_layer.push_back(v);
                    used[v] = true;
                    p[v] = x;
                }
        swap(next_layer, cur_layer);
    }
    vector<int> path;
    int v = n - 1;
    while (v != -1){
        path.push_back(v + 1);
        v = p[v];
    }
    reverse(ALL(path));
    cout << SZ(path) - 1 << '\n';
    for (int i : path)
        cout << i << " ";
    cout << '\n';
    cout << ans << '\n';
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

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

int n, q;
const int MAXN = 1e5 + 7;
vector<int> g[MAXN];
int ans_klen[MAXN]; // k <= n
int sizes[MAXN];
int pnt = 0;
void dfs_klen(int v, int p) {
    ans_klen[pnt++] = v + 1;
    sort(ALL(g[v]));
    for (int u : g[v])
        if (u != p)
            dfs_klen(u, v);
}
int calc_sz(int v, int p) {
    sizes[v] = 1;
    for (int u : g[v])
        if (u != p)
            sizes[v] += calc_sz(u, v);
    return sizes[v];
}
int find_ans(int v, int p, int x) {
    if (x == 0)
        return v;
    --x;
    for (int u : g[v]) {
        if (u == p)
            continue;
        if (sizes[u] > x)
            return find_ans(u, v, x);
        x -= sizes[u];
    }
    assert(0);
}
pair<int, int> solve_stupid(int x) {
    --x;
    int start = x / n;
    x %= n;
    fill(sizes, sizes + n, 0);
    calc_sz(start, -1);
    return {start, find_ans(start, -1, x)};
}

int order[MAXN];
int pos[MAXN];
void restore_order(int v, int p){
    pos[v] = pnt;
    order[pnt++] = v;
    for (int u : g[v])
        if (u != p)
            restore_order(u, v);
}
void solve_bamboo(){
    pnt = 0;
    int root = 0;
    for (int i = 0; i < n; i++){
        if (SZ(g[i]) == 1){
            root = i;
            break;
        }
    }
    restore_order(root, -1);
    for (int i = 0; i < q; i++){
        int k;
        cin >> k;
        --k;
        int start = k / n;
        k %= n;
        cout << start + 1 << ' ';
        int ps = pos[start];
        if (ps == 0){
            cout << order[k] + 1 << '\n';
            continue;
        }
        if (ps == n - 1){
            cout << order[n - k - 1] + 1 << '\n';
            continue;
        }
        if (k == 0){
            cout << start + 1 << '\n';
            continue;
        }
        if (order[ps - 1] < order[ps + 1]){
            if (ps >= k) {
                cout << order[ps - k] + 1 << '\n';
                continue;
            }
            k -= ps;
            cout << order[ps + k] + 1 << '\n';
            continue;
        }
        if (k < n - ps){
            cout << order[ps + k] + 1 << '\n';
            continue;
        }
        k -= n - ps;
        cout << order[ps - k] + 1 << '\n';
    }
}
int solve() {
    if (!(cin >> n >> q))
        return 1;
    int cnt_2 = 0;
    int cnt_1 = 0;
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++){
        if (SZ(g[i]) == 1)
            cnt_1++;
    }
    pnt = 1;
    dfs_klen(0, -1);
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k <= n)
            cout << 1 << ' ' << ans_klen[k] << '\n';
        else {
            auto ans = solve_stupid(k);
            cout << ans.first + 1 << ' ' << ans.second + 1 << '\n';
        }
    }
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

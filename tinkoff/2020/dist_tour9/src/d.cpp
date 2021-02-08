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
const int MAXN = 1e5;
const int INF = 1e9;
vector<int> g[MAXN];
int color[MAXN];
bool is_marked[MAXN];
int d[MAXN];
int d1[MAXN];

int dfs(int v, int p) {
    d[v] = INF;
    for (int u : g[v]) {
        if (u != p)
            d[v] = min(d[v], dfs(u, v) + 1);
    }
    if (is_marked[v]) {
        d1[v] = d[v];
        d[v] = 0;
    }
//    cout << v << " " << is_marked[v] << ' ' << d[v] << ' ' << d1[v] << '\n';
    return d[v];
}

void dfs(int v, int p, int up) {
    if (is_marked[v]) {
        d1[v] = min(d1[v], up);
        up = 0;
    }
    d[v] = min(d[v], up);
    vector<pair<int, int>> have;
    for (int u : g[v])
        if (u != p)
            have.emplace_back(d[u] + 1, u);
    sort(ALL(have));
    for (int u : g[v])
        if (u != p) {
            int x = up;
            if (u == have[0].second && SZ(have) > 1)
                x = min(x, have[1].first);
            else if (u != have[0].second)
                x = min(x, have[0].first);
            dfs(u, v, x + 1);
        }
}

int find_ans() {
    if (count(color, color + n, 0) == 1 || count(color, color + n, 1) == 1)
        return INF;
    assert(count(color, color + n, -1) == 0);
    vector<vector<int>> colors(2);
    for (int i = 0; i < n; i++)
        colors[color[i]].push_back(i);
    int ans = 0;
    for (int i = 0; i < 2; i++) {
        fill(is_marked, is_marked + n, false);
        fill(d, d + n, INF);
        fill(d1, d1 + n, INF);
        for (int x : colors[i])
            is_marked[x] = true;
        dfs(0, -1);
//        cout << i << ": ";
//        for (int x = 0; x < n; x++)
//            cout << d[x] << " \n"[x + 1 == n];
        dfs(0, -1, INF);
//        cout << i << ": ";
//        for (int x = 0; x < n; x++)
//            cout << d1[x] << " \n"[x + 1 == n];
        for (int x : colors[i])
            ans = max(ans, d1[x]);
    }
    return ans;
}

int dfs1(int v, int p) {
    if (is_marked[v])
        return 0;
    int d = INF;
    for (int u : g[v])
        if (u != p)
            d = min(d, dfs(u, v) + 1);
    return d;
}


int find_ans1() {
    vector<vector<int>> colors(2);
    for (int i = 0; i < n; i++)
        colors[color[i]].push_back(i);
    int ans = 0;
    for (int i = 0; i < 2; i++) {
        fill(is_marked, is_marked + n, false);
        for (int x : colors[i])
            is_marked[x] = true;
        for (int x : colors[i]) {
            is_marked[x] = false;
            ans = max(ans, dfs1(x, -1));
            is_marked[x] = true;
        }
    }
    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();

    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    vector<int> minuses;
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        if (color[i] == -1)
            minuses.push_back(i);
    }
    vector<int> best = {color, color + n};
    int best_ans = INF;
    if (SZ(minuses) == 0) {
        best_ans = find_ans();
    } else {
        for (int mask = 0; mask < (1 << SZ(minuses)); mask++) {
            for (int i = 0; i < SZ(minuses); i++)
                color[minuses[i]] = ((mask >> i) & 1);
            int now = find_ans();
//        int now1 = find_ans1();
//        for (int i = 0; i < n; i++)
//            cout << color[i] << " \n"[i + 1 == n];
//        cout << now << ' ' << now1 << endl;
//        assert(now == now1);
            if (now == -1)
                continue;
            if (now < best_ans) {
                best_ans = now;
                best = vector<int>{color, color + n};
            }
        }
    }
    if (best_ans == INF)
        best_ans = -1;
    cout << best_ans << '\n';
    if (best_ans != -1) {
        for (int i = 0; i < n; i++) {
            assert(best[i] != -1);
            cout << best[i] << " \n"[i + 1 == n];
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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
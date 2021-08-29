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

const int MAXN = 1e4 + 7;
const int MAXLOG = 15;
int now[MAXN];
int tin[MAXN];
int tout[MAXN];
int timer;
int p[MAXN];
pair<pair<int, int>, int> butttons[MAXN];
vector<int> g[MAXN];
pair<int, int> sparse[MAXLOG][2 * MAXN];
int id[MAXN];
int cnt[MAXN];
int depth[MAXN];
int logs[2 * MAXN];
bool used[MAXN];
int pnt = 0;

void precalc(int v, int p = -1, int d = 1) {
    ::p[v] = p;
    tin[v] = timer++;
    sparse[0][pnt] = {d, v};
    id[v] = pnt++;
    depth[v] = d;
    for (int u : g[v]) {
        if (u != p) {
            precalc(u, v, d + 1);
            sparse[0][pnt++] = {d, v};
        }
    }
    tout[v] = timer++;
}

void build_sparse() {
    for (int log = 1; log < MAXLOG; log++) {
        for (int i = 0; i + (1 << log) <= pnt; i++) {
            sparse[log][i] = min(sparse[log - 1][i], sparse[log - 1][i + (1 << (log - 1))]);
        }
    }
    for (int i = 2; i <= pnt; i++)
        logs[i] = logs[i / 2] + 1;
}

bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    a = id[a];
    b = id[b];
    if (a > b)
        swap(a, b);
    int len = logs[b - a];
    return min(sparse[len][a], sparse[len][b - (1 << len)]).second;
}

int get_cnt(int v, int u, int c) {
    int cnt = (now[v] == c) + (now[u] == c && v != u);
    while (!is_anc(v, u)) {
        v = p[v];
        if (v != u && now[v] == c)
            cnt++;
    }
    while (v != u) {
        u = p[u];
        if (v != u && now[u] == c)
            cnt++;
    }
    return cnt;
}

deque<int> q;

void update_path(int v, int u, int id) {
    if (used[id])
        return;
    const auto&[path, c] = butttons[id];
    const auto&[a, b] = path;
    int l = lca(a, b);
    auto check = [&](int x) {
        return is_anc(l, x) && (is_anc(x, butttons[id].first.first) || is_anc(x, butttons[id].first.second)) &&
               (now[x] != butttons[id].second && now[x] != 2);
    };
    if (check(v))
        cnt[id]++;
    if (check(u) && v != u)
        cnt[id]++;
    while (!is_anc(v, u)) {
        v = p[v];
        if (v != u && check(v))
            cnt[id]++;
    }
    while (v != u) {
        u = p[u];
        if (v != u && check(u))
            cnt[id]++;
    }
    if (cnt[id] == depth[a] + depth[b] - 2 * depth[l] + 1)
        q.push_back(id);
}

void color_path(int v, int u){
    now[v] = now[u] = 2;
    while (!is_anc(v, u)){
        now[v] = 2;
        v = p[v];
    }
    while (v != u){
        now[u] = 2;
        u = p[u];
    }
    now[v] = 2;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> now[i], g[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    precalc(0, 0);
    build_sparse();
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j + (1 << i) <= pnt; j++)
//            cout << "(" << sparse[i][j].first << ", " << sparse[i][j].second << ")" << " \n"[j + (1 << i) == pnt];
    cin >> m;
    for (int i = 0; i < m; i++) {
        int v, u, c;
        cin >> v >> u >> c;
        butttons[i] = {{--v, --u}, c};
        cnt[i] = get_cnt(v, u, c);
//        cout << v + 1 << ' ' << u + 1 << ' ' << lca(v, u) + 1 << '\n';
//        cout << cnt[i] << ' ' << depth[v] + depth[u] - 2 * depth[lca(v, u)] + 1 << '\n';
        if (cnt[i] == depth[v] + depth[u] - 2 * depth[lca(v, u)] + 1)
            q.push_back(i);
    }
    vector<int> ans;
    while (SZ(q)) {
        int x = q.front();
        q.pop_front();
        if (used[x])
            continue;
        used[x] = true;
        ans.push_back(x);
//        cout << x + 1 << "\n";
        auto[path, c] = butttons[x];
        auto[v, u] = path;
        for (int i = 0; i < m; i++)
            update_path(v, u, i);
        color_path(v, u);
//        for (int i = 0; i < m; i++)
//            cout << cnt[i] << " \n"[i + 1 == m];
//        for (int i = 0; i < n; i++)
//            cout << now[i] << " \n"[i + 1 == n];
    }
    if (count(now, now + n, 1) != 0) {
        cout << "-1\n";
        return 0;
    }
    cout << SZ(ans) << '\n';
    reverse(ALL(ans));
    for (int x : ans)
        cout << x + 1 << " ";
    cout << '\n';
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
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

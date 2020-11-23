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
const int MAXN = 1e5 + 7;
pair<int, int> points[MAXN];
vector<int> have_x[MAXN];
vector<int> have_y[MAXN];
struct Edge {
    int to, index;
};
vector<Edge> g[2 * MAXN];
int timer = 0;
bool used[2 * MAXN];
bool is_bridge[2 * MAXN];
int tin[2 * MAXN];
int fup[2 * MAXN];
int szs[2 * MAXN];
int comps[2 * MAXN];

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (auto[u, i] : g[v]) {
        if (u == p)
            continue;
        if (!used[u]) {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[u] > fup[v]) {
                is_bridge[i] = true;
            }
        } else
            fup[v] = min(fup[v], tin[u]);
    }
}

void dfs1(int v, int c, int rel) {
    if (v < rel)
        szs[c]++;
    comps[v] = c;
    for (auto[u, i] : g[v])
        if (!is_bridge[i] && comps[u] != comps[v])
            dfs1(u, c, rel);
}

vector<int> c_x, c_y;
int pnt = 0;

void init() {
    pnt = 0;
    for (int i = 0; i < SZ(c_x) + SZ(c_y); i++) {
        g[i].clear();
        used[i] = false;
        tin[i] = fup[i] = 0;
        szs[i] = 0;
        comps[i] = -1;
    }
    fill(is_bridge, is_bridge + n, false);
}

void add_edge(int v, int u) {
    cout << v << "<=>" << u << ' ' << pnt << '\n';
    g[v].push_back({u, pnt});
    g[u].push_back({v, pnt});
    pnt++;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    c_x.clear();
    c_y.clear();
    c_x.reserve(n);
    c_y.reserve(n);
    for (int i = 0; i < n; i++) {
        c_x.push_back(points[i].first);
        c_y.push_back(points[i].second);
    }
    sort(ALL(c_x));
    c_x.resize(unique(ALL(c_x)) - c_x.begin());
    sort(ALL(c_y));
    c_y.resize(unique(ALL(c_y)) - c_y.begin());
    vector<int> cnt_x(SZ(c_y));
    vector<int> cnt_y(SZ(c_x));
    if (SZ(c_x) == 1 || SZ(c_y) == 1) {
        cout << "4\n";
        return 0;
    }
    if (SZ(c_x) == n && SZ(c_y) == n) {
        cout << "4\n";
        return 0;
    }
    for (int i = 0; i < SZ(c_x); i++)
        have_x[i].clear();
    for (int i = 0; i < SZ(c_y); i++)
        have_y[i].clear();
    int ans = 3;
    for (int i = 0; i < n; i++) {
        auto &[a, b] = points[i];
        a = (int) (lower_bound(ALL(c_x), a) - c_x.begin());
        b = (int) (lower_bound(ALL(c_y), b) - c_y.begin());
        have_x[a].push_back(b);
        have_y[b].push_back(a);
    }
    int ccx = 0, ccy = 0;
    init();
    for (int i = 0; i < SZ(c_x); i++) {
        sort(ALL(have_x[i]));
        for (int j = 0; j < SZ(have_x[i]); j++) {
            if (SZ(have_x[i]) > 1) {
                cnt_x[have_x[i][j]]++;
                add_edge(i, have_x[i][j] + SZ(c_x));
            }
        }
        if (SZ(have_x[i]) > 1)
            ccx++;
    }
    for (int i = 0; i < SZ(c_x) + SZ(c_y); i++)
        if (!used[i])
            dfs(i, -1);
    int color = 0;
    for (int i = 0; i < SZ(c_x); i++) {
        if (comps[i] == -1) {
            dfs1(i, color, SZ(c_x));
            if (szs[color++] >= 2) {
                cout << "0\n";
                return 0;
            }
        }
    }
//    cerr << "lol\n";
    init();
    for (int i = 0; i < SZ(c_y); i++) {
        sort(ALL(have_y[i]));
        for (int j = 0; j < SZ(have_y[i]); j++) {
            if (SZ(have_y[i]) > 1) {
                cnt_y[have_y[i][j]]++;
                add_edge(i, have_y[i][j] + SZ(c_y));
            }
        }
        if (SZ(have_y[i]) > 1)
            ccy++;
    }
    for (int i = 0; i < SZ(c_x) + SZ(c_y); i++)
        if (!used[i])
            dfs(i, -1);
    color = 0;
    for (int i = 0; i < SZ(c_y); i++) {
        if (comps[i] == -1) {
            dfs1(i, color, SZ(c_y));
            if (szs[color++] >= 2) {
                cout << "0\n";
                return 0;
            }
        }
    }
    bool can = false;
    for (int i = 0; i < SZ(c_x); i++) {
        int have_1 = 0;
        int have_11 = 0;
        for (int j : have_x[i]) {
            if (cnt_x[j] > 1)
                have_1++;
            if (SZ(have_x[i]) > 1)
                can |= SZ(have_y[j]) > 1;
            if (SZ(have_y[j]) > 1)
                have_11++;
        }
        if (have_1 > 1 || have_11 > 1) {
            ans = 1;
            break;
        }
    }
    for (int i = 0; i < SZ(c_y); i++) {
        int have_1 = 0;
        int have_11 = 0;
        for (int j : have_y[i]) {
            if (cnt_y[j] > 1)
                have_1++;
            if (SZ(have_y[i]) > 1)
                can |= SZ(have_x[j]) > 1;
            if (SZ(have_x[j]) > 1)
                have_11++;
        }
        if (have_1 > 1 || have_11 > 1) {
            ans = 1;
            break;
        }
    }
//    cout << ccx << ' ' << ccy << ' ' << can << '\n';
    if (ans > 2 && (ccx > 1 || ccy > 1 || can))
        ans = 2;
    cout << ans << '\n';
    return 0;
}

signed main() {
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

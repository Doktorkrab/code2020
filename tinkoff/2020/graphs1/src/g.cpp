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

int n, m, day;
const int MAXN = 1e5 + 7;
vector<int> g[MAXN], g1[MAXN], g2[MAXN];
int h[MAXN];
int topsort[MAXN], pnt = 0;
int sz[MAXN];
int p[MAXN];
int color[MAXN];
bool used[MAXN];
bool good[MAXN];

void build_topsort(int v) {
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            build_topsort(u);
    topsort[pnt++] = v;
}

void paint(int v, int c) {
    color[v] = c;
    sz[c]++;
    p[c] = v;
    for (int u : g1[v])
        if (color[u] == -1)
            paint(u, c);
}

vector<int> ans;

void calc_ans(int v) {
    ans.push_back(v);
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            calc_ans(u);
}


int solve() {
    if (!(cin >> n >> m >> day))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        g[i].clear();
        g1[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        int nxt_v = (h[v] + 1) % day, nxt_u = (h[u] + 1) % day;
        if (nxt_v == h[u]) {
            g[v].push_back(u);
            g1[u].push_back(v);
//            cout << v + 1 << "->" << u + 1 << '\n';
        }
        if (nxt_u == h[v]) {
            g[u].push_back(v);
            g1[v].push_back(u);
//            cout << u + 1 << "->" << v + 1 << '\n';
        }
    }
    fill(used, used + n, false);
    pnt = 0;
    for (int i = 0; i < n; i++)
        if (!used[i])
            build_topsort(i);
    int c = 0;
    fill(sz, sz + n, 0);
    fill(color, color + n, -1);
    for (int i = n - 1; i >= 0; i--)
        if (color[topsort[i]] == -1)
            paint(topsort[i], c++);
//    for (int i = 0; i < n; i++)
//        cout << color[i] << " \n"[i + 1 == n];
    fill(good, good + c, true);
    for (int v = 0; v < n; v++) {
        for (int u : g[v])
            if (color[v] != color[u])
                good[color[v]] = false;
    }
    int best = -1;
    for (int i = 0; i < c; i++)
        if (good[i] && (best == -1 || sz[best] > sz[i]))
            best = i;
    ans.clear();
    fill(used, used + n, false);
    calc_ans(p[best]);
    cout << SZ(ans) << '\n';
    for (int x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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

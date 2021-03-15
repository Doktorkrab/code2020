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
const int MAXN = 3e5 + 7;
const int MAXLOG = 18;
vector<int> g[MAXN];
int tin[MAXN];
int tout[MAXN];
int par[MAXLOG][MAXN];
int depth[MAXN];
int timer;

void dfs(int v, int p = 0, int d = 0) {
    par[0][v] = p;
    for (int i = 1; i < MAXLOG; i++)
        par[i][v] = par[i - 1][par[i - 1][v]];
    tin[v] = timer++;
    depth[v] = d;
    for (int u : g[v])
        if (u != p)
            dfs(u, v, d + 1);
    tout[v] = timer++;
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int a, int b) {
    if (is_anc(a, b))
        return a;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        int v = par[i][a];
        if (!is_anc(v, b))
            a = v;
    }
    return par[0][a];
}

vector<int> g1[MAXN];
int ans[MAXN];
int mark[MAXN];

int dfs1(int v, int p = -1) {
    int now = mark[v];
    for (int u : g1[v]) {
        if (u == p)
            continue;
        int was = dfs1(u, v);
        ans[0] -= depth[u] - depth[v];
        ans[was] += depth[u] - depth[v];
        now += was;
    }
    return now;
}

void find_ans(vector<int> &a) {
    sort(ALL(a), [&](int x, int y) {
        return tin[x] < tin[y];
    });
    int k = SZ(a);
    for (int i = 0; i <= k; i++)
        ans[i] = 0;
    ans[0] = n;
    int start = -1;
    for (int x : a) {
        mark[x] = 1;
        if (start == -1 || depth[start] > depth[x])
            start = x;
    }

    for (int i = 0; i + 1 < k; i++) {
        int l = lca(a[i], a[i + 1]);
        if (start == -1 || depth[start] > depth[l])
            start = l;
        a.push_back(l);
    }
    sort(ALL(a), [&](int x, int y) {
        return tin[x] < tin[y];
    });
    for (int x : a)
        g1[x].clear();
    vector<int> stack;
    a.erase(unique(ALL(a), [&](int x, int y) { return tin[x] == tin[y]; }), a.end());
    for (int x : a) {
        while (SZ(stack) && tout[stack.back()] < tin[x])
            stack.pop_back();
        if (SZ(stack)) {
//            cout << stack.back() + 1 << "<->" << x  + 1 << '\n';
            g1[stack.back()].push_back(x);
            g1[x].push_back(stack.back());
        }
        stack.push_back(x);
    }
    int was = dfs1(start);
    ans[0] -= depth[start] + 1;
    ans[was] += depth[start] + 1;
    for (int i = 0; i <= k; i++)
        cout << ans[i] << " \n"[i == k];
    for (int x : a)
        mark[x] = 0;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i + 1 < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    timer = 0;
    dfs(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        vector<int> arr(x);
        for (int &y : arr) {
            cin >> y;
            --y;
        }
        find_ans(arr);
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
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

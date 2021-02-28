
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

int n, m, q;

const int MAXN = 2e5 + 7;
int p[MAXN];
int sz[MAXN];

int find_set(int v) {
    if (p[v] == v)
        return v;
    return p[v] = find_set(p[v]);
}

bool un(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return false;
    if (sz[a] > sz[b])
        swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
    return true;
}

struct Edge {
    int w, v, u;

    bool operator<(const Edge &rhs) const {
        return std::tie(w, v, u) < std::tie(rhs.w, rhs.v, rhs.u);
    }
};

set<Edge> edges;

int find_ans() {
    int ans = 0;
    iota(p, p + n + 1, 0);
    fill(sz, sz + n + 1, 1);
    for (auto[w, v, u] : edges) {
        if (un(v, u))
            ans += w;
    }
    return ans;
}
int arr[MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        arr[i] = x;
        edges.insert({x, 0, i});
    }

    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        edges.insert({w, v, u});
    }
    cin >> q;
    for (int i = 0; i < q; i++){
        int x, w;
        cin >> x >> w;
        edges.erase({arr[x], 0, x});
        arr[x] = w;
        edges.insert({arr[x], 0, x});
        cout << find_ans() << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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

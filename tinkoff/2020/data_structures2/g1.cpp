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
const int MAXN = 5e5 + 7;
const int MOD = 1e9;
int arr[MAXN];
int versions[MAXN];

struct Node {
    int left = -1, right = -1;
    int sum = 0;

    Node() = default;
};

vector<Node> nodes;
int nxt_node = 0;

int new_node() {
    nodes.emplace_back();
    return nxt_node++;
}

int build(int l, int r) {
    int node = new_node();
    if (r - l < 1)
        return -1;
    if (r - l == 1) {
        nodes[node].sum = 0;
        return node;
    }
    int m = (l + r) / 2;
    nodes[node].left = build(l, m);
    nodes[node].right = build(m, r);
    nodes[node].sum = nodes[nodes[node].left].sum + nodes[nodes[node].right].sum;
    return node;
}

int add(int v, int tl, int tr, int pos, int x) {
//    cerr << v << ' ' << tl << ' ' << tr << ' ' << pos << ' ' << x << '\n';
    assert(v != -1);
    int node = new_node();
    nodes[node] = nodes[v];
    if (tr - tl == 1) {
        nodes[node].sum += x;
        return node;
    }
    int tm = (tl + tr) / 2;
    if (pos < tm)
        nodes[node].left = add(nodes[v].left, tl, tm, pos, x);
    else
        nodes[node].right = add(nodes[v].right, tm, tr, pos, x);
    nodes[node].sum = nodes[nodes[node].left].sum + nodes[nodes[node].right].sum;
    return node;
}

int get(int v1, int v2, int tl, int tr, int x) {
    assert(v1 != -1 && v2 != -1);
    if (tr - tl == 1)
        return tl;
    int tm = (tl + tr) / 2;
//    cout << tl + 1 << ' ' << tr << " " << nodes[v1].sum << ' ' << nodes[v2].sum << ' ' << x << '\n';
    if (nodes[nodes[v2].left].sum - nodes[nodes[v1].left].sum > x)
        return get(nodes[v1].left, nodes[v2].left, tl, tm, x);
    return get(nodes[v1].right, nodes[v2].right, tm, tr, x - (nodes[nodes[v2].left].sum - nodes[nodes[v1].left].sum));
}

int solve() {
    if (!(cin >> n))
        return 1;
    int l, m;
    vector<int> to_sort(n);

    cin >> arr[0] >> l >> m;
    to_sort[0] = arr[0];
    for (int i = 1; i < n; i++)
        to_sort[i] = arr[i] = (int) ((1LL * arr[i - 1] * l + m) % MOD);
    sort(ALL(to_sort));
    to_sort.erase(unique(ALL(to_sort)), to_sort.end());
    m = SZ(to_sort);

    versions[0] = build(0, m);
    for (int i = 0; i < n; i++) {
        arr[i] = (int) (lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
        versions[i + 1] = add(versions[i], 0, m, arr[i], 1);
    }
    int b;
    cin >> b;
    ll ans = 0;
    while (b--) {
        int g, x1, lx, mx, y1, ly, my, k1, lk, mk;
        cin >> g >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
        int l, r;
        for (int i = 0; i < g; i++) {
            l = min(x1, y1);
            r = max(x1, y1);
            int tt = get(versions[l - 1], versions[r], 0, m, k1 - 1);
//            cout << l << ' ' << r << ' ' << k1 << ' ' << tt << '\n';
            ans += 1LL * to_sort[tt];
            x1 = (int) (1LL * (l - 1) * lx + mx) % n + 1;
            y1 = (int) (1LL * (r - 1) * ly + my) % n + 1;
            k1 = (int) (1LL * (k1 - 1) * lk + mk) % (max(x1, y1) - min(x1, y1) + 1) + 1;
        }
    }
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

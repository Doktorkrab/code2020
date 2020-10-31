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

int n, s, m;
struct Node {
    int min = TMAX(int);
    int left = -1;
    int right = -1;
};

const int MAXC = 1e7;
const int MAXN = 2e5 + 7;
Node *nodes;
int pnt = 0;

int new_node() {
    return pnt++;
}

int build(int l, int r) {
    int node = new_node();
    if (r - l == 1) {
        if (l == 0)
            nodes[node].min = TMAX(int);
        else
            nodes[node].min = -1;
        return node;
    }
    int m = (l + r) / 2;
    nodes[node].left = build(l, m);
    nodes[node].right = build(m, r);
    nodes[node].min = min(nodes[nodes[node].left].min, nodes[nodes[node].right].min);
    return node;
}

int update(int v, int tl, int tr, int pos, int x) {
    if (pos < tl || tr <= pos)
        return v;
    if (tr - tl == 1) {
        int node = new_node();
//        cout << node << ' ' << tl << ' ' << tr << ' ' << x << "!\n";
        nodes[node].min = x;
        return node;
    }
    int tm = (tl + tr) / 2;
    int node = new_node();
    nodes[node].left = update(nodes[v].left, tl, tm, pos, x);
    nodes[node].right = update(nodes[v].right, tm, tr, pos, x);
    nodes[node].min = min(nodes[nodes[node].left].min, nodes[nodes[node].right].min);
//    cout << node << ' ' << tl << ' ' << tr << ' ' << nodes[node].min << '\n';
//    cout << '\t' << nodes[node].left << ' ' << nodes[node].right << '\n';
    return node;
}

int get(int v, int tl, int tr, int x) {
//    cout << v << ' ' << tl << ' ' << tr << ' ' << nodes[v].min << '\n';
    if (tr - tl == 1)
        return tl;
    if (nodes[v].min >= x)
        return 0;
    int tm = (tl + tr) / 2;
    if (nodes[nodes[v].left].min < x)
        return get(nodes[v].left, tl, tm, x);
    return get(nodes[v].right, tm, tr, x);
}

pair<int, pair<int, int>> arr[MAXN];
int versions[MAXN];

int solve() {
    if (!(cin >> n >> s >> m))
        return 1;
    nodes = new Node[MAXC];
    vector<int> to_compress(4 * m + 2);
    for (int i = 0; i < m; i++) {
        int c, a, b;
        cin >> c >> a >> b;
//        --c;
        to_compress[4 * i] = a + 1;
        to_compress[4 * i + 1] = b;
        to_compress[4 * i + 2] = a;
        to_compress[4 * i + 3] = b + 1;
        arr[i] = {c, {a + 1, b}};
    }
    to_compress[4 * m] = 0;
    to_compress[4 * m + 1] = TMAX(int);
    sort(ALL(to_compress));
    to_compress.erase(unique(ALL(to_compress)), to_compress.end());
    vector<vector<pair<int, int>>> scan(SZ(to_compress));
    ++s;
    for (int i = 0; i < m; i++) {
        int l = (int) (lower_bound(ALL(to_compress), arr[i].second.first) - to_compress.begin());
        int r = (int) (lower_bound(ALL(to_compress), arr[i].second.second) - to_compress.begin());
        scan[l].push_back({arr[i].first, TMAX(int)});
        scan[r].push_back({arr[i].first, arr[i].second.second - 1});
    }
    versions[0] = build(0, s);
    for (int i = 0; i < SZ(to_compress); i++) {
//        sort(ALL(scan[i]));
//        cout << "?" << i << ' ' << SZ(scan[i]) << '\n';
        versions[i + 1] = versions[i];
        for (auto[pos, x] : scan[i]) {
//            cout << i << ' ' << to_compress[i] <<  ' ' << pos << ' ' << x << '\n';
            versions[i + 1] = update(versions[i + 1], 0, s, pos, x);
        }
    }
//    cout << '\n';
    int q;
    int p = 0;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l += p;
        r += p;
        r = (int) (lower_bound(ALL(to_compress), r) - to_compress.begin());
//        cout << to_compress[r] << '\n';
        p = get(versions[r + 1], 0, s, l);
        if (p > s)
            p = 0;
        cout << p << '\n';
    }
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

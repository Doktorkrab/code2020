#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// #define int uint64_t
using namespace std;
int n;

struct Node {
    int x = 0;
    int left = -1;
    int right = -1;
};
const int MAXN = 1e6 + 7;
const int MAXC = 1e7 + 1;
int pnt = 0;
Node *nodes;

int new_node() {
    return pnt++;
}

int build(int L, int R) {
    int now = new_node();
    if (R - L == 1) {
        nodes[now].x = 0;
        return now;
    }
    int M = (L + R) / 2;
    nodes[now].left = build(L, M);
    nodes[now].right = build(M, R);
    nodes[now].x = nodes[nodes[now].left].x + nodes[nodes[now].right].x;
    return now;
}

int upd(int root, int tl, int tr, int pos, int x) {
    if (pos < tl || tr <= pos) return root;
    if (tr - tl == 1) {
        int now = new_node();
        nodes[now].x = nodes[root].x + x;
        return now;
    }
    int tm = (tl + tr) / 2;
    int now = new_node();
    nodes[now].left = upd(nodes[root].left, tl, tm, pos, x);
    nodes[now].right = upd(nodes[root].right, tm, tr, pos, x);
    nodes[now].x = nodes[nodes[now].left].x + nodes[nodes[now].right].x;
    return now;
}

int64_t get_ans(int lft, int rgt, int64_t need, int tl, int tr) {
    if (tr - tl == 1) return tl;
    int tm = (tl + tr) / 2;
    if (nodes[nodes[rgt].left].x - nodes[nodes[lft].left].x >= need)
        return get_ans(nodes[lft].left, nodes[rgt].left, need, tl, tm);
    return get_ans(nodes[lft].right, nodes[rgt].right, need - (nodes[nodes[rgt].left].x - nodes[nodes[lft].left].x),
                   tm, tr);
}

int versions[MAXN];
int to_compress[MAXN];

inline void init() {}

inline void solve() {
    nodes = new Node[MAXC];
    int64_t l, m;
    int a;
    cin >> a >> l >> m;
//    cerr << "aaa\n";
    const int MOD = 1e9;
    int b = a;
    to_compress[0] = a;
    for (int i = 1; i < n; i++) {
        b = (1LL * b * l + m) % MOD;
        to_compress[i] = b;
    }
    sort(to_compress, to_compress + n);
    int sz = unique(to_compress, to_compress + n) - to_compress;
    b = a;
    versions[0] = build(0, sz);
    b = a;
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(to_compress, to_compress + sz, b) -
                  to_compress;
        versions[i + 1] = upd(versions[i], 0, sz, pos, 1);
        b = (1LL * b * l + m) % MOD;
    }
    cin >> b;
    int64_t ans = 0;
    for (int gg = 0; gg < b; gg++) {
        int64_t g, x, lx, mx, y, ly, my, k, lk, mk;
        cin >> g >> x >> lx >> mx >> y >> ly >> my >> k >> lk >> mk;
        int64_t i = min(x, y), j = max(x, y);
        while (g--) {
            ans += to_compress[get_ans(versions[i - 1], versions[j], k, 0, sz)];
            x = 1LL * ((i - 1) * lx + mx) % n + 1;
            y = 1LL * ((j - 1) * ly + my) % n + 1;
            i = min(x, y), j = max(x, y);
            k = 1LL * (((k - 1) * lk + mk) % (j - i + 1)) + 1;
        }
    }
    cout << ans << '\n';
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n) solve();
}

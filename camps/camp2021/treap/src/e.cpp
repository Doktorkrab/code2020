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
mt19937 rnd(239);
const int MAXNODE = 1e6;

struct Treap {
    struct Node {
        int x = 0, y = 0;
        int l = -1, r = -1;
        int sz = 1;
        ll sum = 0;

        Node(int x) : x(x), y(rnd()), sum(x) {}

        Node() {}
    };

    Node nodes[MAXNODE];
    int pnt = 0;
    int root = -1;

    int new_node(int x) {
        assert(pnt < MAXNODE);
        nodes[pnt] = Node(x);
        return pnt++;
    }

    int safe_sz(int a) {
        return (a == -1 ? 0 : nodes[a].sz);
    }

    ll safe_sum(int a) {
        return (a == -1 ? 0 : nodes[a].sum);
    }

    int recalc(int a) {
        nodes[a].sz = 1 + safe_sz(nodes[a].l) + safe_sz(nodes[a].r);
        nodes[a].sum = nodes[a].x + safe_sum(nodes[a].l) + safe_sum(nodes[a].r);
        return a;
    }

    int merge(int a, int b) {
        if (a == -1)
            return b;
        if (b == -1)
            return a;
        Node &na = nodes[a];
        Node &nb = nodes[b];
        if (na.y > nb.y) {
            na.r = merge(na.r, b);
            return recalc(a);
        }
        nb.l = merge(a, nb.l);
        return recalc(b);
    }

    pair<int, int> split(int x, int k) {
        if (x == -1)
            return {-1, -1};
        Node &a = nodes[x];
        if (a.x < k) {
            auto res = split(a.r, k);
            a.r = res.first;
            return {recalc(x), res.second};
        }
        auto res = split(a.l, k);
        a.l = res.second;
        return {res.first, recalc(x)};
    }

    ll get(int l, int r) {
        auto x = split(root, l);
        auto x1 = split(x.second, r + 1);
        ll res = safe_sum(x1.first);
        root = merge(x.first, merge(x1.first, x1.second));
        return res;
    }

    bool find(int x, int k) {
        if (x == -1)
            return false;
        if (nodes[x].x == k)
            return true;
        if (nodes[x].x < k)
            return find(nodes[x].r, k);
        return find(nodes[x].l, k);
    }

    void insert(int x) {
        if (root == -1) {
            root = new_node(x);
            return;
        }
        if (find(root, x))
            return;
        auto t = split(root, x);
        root = merge(t.first, merge(new_node(x), t.second));
    }

    void erase(int x) {
        auto t = split(root, x);
        auto t1 = split(t.second, x + 1);
        root = merge(t.first, t1.second);
    }
};


int solve() {
    if (!(cin >> n))
        return 1;
    Treap t;
    ll was = 0;
    const int MOD = 1e9;
    for (int i = 0; i < n; i++) {
        char type;
        cin >> type;
        if (type == '+') {
            int x;
            cin >> x;
            t.insert((x + was) % MOD);
            was = 0;
        } else {
            int l, r;
            cin >> l >> r;
            cout << (was = t.get(l, r)) << '\n';
        }

    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
#else
    freopen("sum2.in", "r", stdin);
    freopen("sum2.out", "w", stdout);
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

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

struct SegmentTree {
    struct Node {
        int mn = 0; // min
        int mx = 0; // max
        int push = 0; //+=
        int val = 0; // cnt
        int kek = 0;
        Node() = default;

        explicit Node(int x) : mn(x), mx(x) {}

        Node(const Node &a, const Node &b) {
            mn = min(a.mn, b.mn);
            mx = max(a.mx, b.mx);
            val = a.val + b.val;
        }
    };

    Node *tree;
    int N = 1;

    SegmentTree(int sz) {
        while (N < sz)
            N *= 2;
        tree = new Node[2 * N];
        for (int i = 0; i < N; i++)
            tree[i + N] = Node(-i);
        for (int i = N - 1; i >= 0; i--)
            tree[i] = Node(tree[2 * i], tree[2 * i + 1]);
    }

    void push(int v) {
        tree[v].mn += tree[v].push;
        tree[v].mx += tree[v].push;
        if (v < N) {
            tree[2 * v].push += tree[v].push;
            tree[2 * v + 1].push += tree[v].push;
        }
        tree[v].push = 0;
    }

    void push_seg(int v, int tl, int tr, int l, int r, int x) {
        push(v);
        if (tr <= l || r <= tl)
            return;
        if (l <= tl && tr <= r) {
            tree[v].push += x;
            push(v);
            return;
        }
        int tm = (tl + tr) / 2;
        push_seg(v * 2, tl, tm, l, r, x);
        push_seg(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
    }

    void push_seg(int l, int r, int x) {
        push_seg(1, 0, N, l, r, x);
    }

    int get_pr(int v, int tl, int tr, int l, int r) {
        push(v);
//        cout << v << ' ' << tl << ' ' << tr << ' ' << tree[v].mx << ' ' << tree[v].mn << '\n';
        if (tr <= l || r <= tl || tree[v].mx < 0)
            return 0;
        if (l <= tl && tr <= r && tree[v].mn >= 0)
            return tr - tl;
        int tm = (tl + tr) / 2;
        int ret = get_pr(v * 2, tl, tm, l, r);
        if (ret < tm - tl)
            push(v * 2 + 1);
        else
            ret += get_pr(v * 2 + 1, tm, tr, l, r);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
        return ret;
    }

    int get_pr(int l, int r) {
        return get_pr(1, 0, N, l, r);
    }

    int get_cnt(int v, int tl, int tr, int l, int r) {
        push(v);
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r)
            return tree[v].val;
        int tm = (tl + tr) / 2;
        int ret = get_cnt(v * 2, tl, tm, l, r) + get_cnt(v * 2 + 1, tm, tr, l, r);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
        return ret;
    }

    int get_cnt(int l, int r) {
        return get_cnt(1, 0, N, l, r);
    }

    void upd(int v, int tl, int tr, int pos, int x) {
        push(v);
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            tree[v].val += x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
    }
    void upd(int pos, int x){
        upd(1, 0, N, pos, x);
    }
};

int solve() {
    if (!(cin >> n))
        return 1;
    SegmentTree st(MAXN);
    st.upd(0, 1);
    st.push_seg(1, MAXN, 1);
    for (int i = 0; i < n; i++){
        char type;
        int a;
        cin >> type >> a;
        if (type == '+'){
            st.upd(a, 1);
            st.push_seg(a + 1, MAXN, 1);
        }
        else {
            st.upd(a, -1);
            st.push_seg(a + 1, MAXN, -1);
        }
//        cout << '\t' << st.get_pr(0, MAXN) << '\n';
        cout << st.get_cnt(0, st.get_pr(0, MAXN)) << '\n';
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


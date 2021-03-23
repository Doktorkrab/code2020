#include <bits/stdc++.h>

using namespace std;

template<int MAXNODES>
struct SegmentTree {
    struct Node {
        int x;
    };
    Node nodes[MAXNODES];

    Node merge(const Node &a, const Node &b) {
        return {a.x + b.x};
    }

    int N;

    SegmentTree(int sz) {
        N = 1;
        while (N < sz)
            N *= 2;
    }

    SegmentTree(int sz, const int *arr) {
        N = 1;
        while (N < sz)
            N *= 2;
        for (int i = 0; i < sz; i++)
            nodes[i + N] = {arr[i]};
        for (int i = N - 1; i >= 1; i--)
            nodes[i] = merge(nodes[2 * i], nodes[2 * i + 1]);
    }

    void upd(int v, int tl, int tr, int pos, int x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            nodes[v] = {x};
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        nodes[v] = merge(nodes[2 * v], nodes[2 * v + 1]);
    }

    Node get(int v, int tl, int tr, int l, int r) {
        if (tr <= l || r <= tl)
            return {0};
        if (l <= tl && tr <= r)
            return nodes[v];
        int tm = (tl + tr) / 2;
        return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    void upd(int pos, int x) {
        upd(1, 0, N, pos, x);
    }

    int get(int l, int r) {
        return get(1, 0, N, l, r).x;
    }
};

const int MAXN = 10;
int arr[MAXN];

// Fenwick
int tree[MAXN], n;

void upd(int pos, int x) {
    for (int i = pos; i < MAXN; i |= (i + 1)) {
        tree[i] += x;
    }
}

int get(int r) {
    int ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

int get(int l, int r) {
    return get(r - 1) - get(l - 1);
}

int prefix[MAXN];

void build_prefixes() {
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
}

int get_prefixes(int l, int r) {
    return prefix[r] - prefix[l];
}

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        n = rnd() % 5 + 1;
        fill(tree, tree + MAXN, 0);
        for (int i = 0; i < n; i++)
            arr[i] = rnd() % 10;
        SegmentTree<4 * MAXN> segmentTree(n, arr);
        build_prefixes();
        for (int i = 0; i < n; i++)
            upd(i, arr[i]);
        for (int i = 0; i < n; i++) {
            int l = rnd() % n, r = rnd() % n;
            if (l > r)
                swap(l, r);
            int a = get(l, r + 1);
            int b = segmentTree.get(l, r + 1);
            int c = get_prefixes(l, r + 1);
            if (a != b || b != c || c != a) {
                cout << n << '\n';
                for (int i = 0; i < n; i++)
                    cout << arr[i] << " \n"[i + 1 == n];
                cout << l + 1 << ' ' << r + 1 << '\n';
                cout << a << '\n' << b << '\n' << c << '\n';
                return 0;
            }
        }
    }
}
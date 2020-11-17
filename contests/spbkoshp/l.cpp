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

int n, q;
const int MAXN = 2e5 + 7;

struct SegmentTree {
    int tree[4 * MAXN]{};
    int N = 1;
    SegmentTree() = default;
    SegmentTree(int sz, int *arr) {
        while (N < sz)
            N *= 2;
        for (int i = 0; i < sz; i++)
            tree[i + N] = arr[i];
        for (int i = N - 1; i >= 0; i--)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    int get(int v, int tl, int tr, int l, int r){
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
    }
    int get(int l, int r){
        return get(1, 0, N, l, r);
    }

    void upd(int v, int tl, int tr, int pos, int x){
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1){
            tree[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
    void upd(int pos, int x){
        upd(1, 0, N, pos, x);
    }
};

SegmentTree k_x;
SegmentTree k_y;
SegmentTree b_x;
SegmentTree b_y;
pair<int, int> get(int pos){
    int x = pos + k_x.get(0, pos + 1) * pos + b_x.get(0, pos + 1);
    int y = 0 + k_y.get(0, pos + 1) * pos + b_y.get(0, pos + 1);
//    cout << k_x.get(0, pos + 1) << '\n';
//    cout << pos << ' ' << x << ' ' << y << endl;
    assert(0 <= x && x < n);
    assert(0 <= y && y < n);
    return {x, y};
}
int arr[MAXN];

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        arr[i] = 0;
    k_x = SegmentTree(n + 100, arr);
    k_y = SegmentTree(n + 100, arr);
    b_x = SegmentTree(n + 100, arr);
    b_y = SegmentTree(n + 100, arr);
    for (int i = 0; i < q; i++){
        int type;
        cin >> type;
        if (type == 1){
            int l, r;
            cin >> l >> r;
            --l;
            auto pos_l = get(l);
            auto pos_r = get(r - 1);
            if (pos_l.first == pos_r.first){
                k_x.upd(l, 1);
                k_x.upd(r, -1);
                b_x.upd(l, -l);
                b_x.upd(r, l);

                k_y.upd(l, -1);
                k_y.upd(r, 1);
                b_y.upd(l, l);
                b_y.upd(r, -l);
            }
            else {
                k_y.upd(l, 1);
                k_y.upd(r, -1);
                b_y.upd(l, -l);
                b_y.upd(r, l);

                k_x.upd(l, -1);
                k_x.upd(r, 1);
                b_x.upd(l, l);
                b_x.upd(r, -l);
            }
        }
        if (type == 2){
            int pos;
            cin >> pos;
            auto [x, y] = get(pos - 1);
            cout << x + 1 << ' ' << y << '\n';
        }
//        for (int j = 0; j < n; j++){
//            auto [x, y] = get(j);
//            cout << x + 1 << ' ' << y << '\n';
//        }
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

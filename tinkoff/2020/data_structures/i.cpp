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

const int MAXN = 2e5 + 7;
int n;
pair<int, int> arr[2 * MAXN];
int upd[MAXN];

struct SegmentTree {
    struct Node {
        int mx, to_push;
    };
    Node tree[4 * MAXN];
    int N = 1;

    void push(int v) {
        if (v < N) {
            tree[2 * v].mx += tree[v].to_push;
            tree[2 * v + 1].mx += tree[v].to_push;
            tree[2 * v].to_push += tree[v].to_push;
            tree[2 * v + 1].to_push += tree[v].to_push;
        }
        tree[v].to_push = 0;
    }

    SegmentTree(int n) {
        while (N < n)
            N *= 2;
    }

    void upd_seg(int v, int tl, int tr, int l, int r, int x) {
        if (tr <= l || r <= tl)
            return;
        if (l <= tl && tr <= r) {
            tree[v].mx += x;
            tree[v].to_push += x;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd_seg(v * 2, tl, tm, l, r, x);
        upd_seg(v * 2 + 1, tm, tr, l, r, x);
        tree[v].mx = max(tree[2 * v].mx, tree[2 * v + 1].mx);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r)
            return tree[v].mx;
        push(v);
        int tm = (tl + tr) / 2;
        int ret = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v].mx = max(tree[2 * v].mx, tree[2 * v + 1].mx);
        return ret;
    }

    int get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    void upd_seg(int l, int r, int x) {
        upd_seg(1, 0, N, l, r, x);
    }
};


int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> arr[i + n].first;
        arr[i + n].second = i + n;
    }
    sort(arr, arr + 2 * n);
    reverse(arr, arr + 2 * n);

    SegmentTree seg(n + 1);
    for (int i = 0; i < 2 * n; i++) {
//        cout << "! ";
        if (arr[i].second < n) {
//            cout << arr[i].second << ' ' << n << '\n';
            seg.upd_seg(arr[i].second + 1, n + 1, 1);
        } else {
//            cout << "0 " << arr[i].second - n + 1 << '\n';
            seg.upd_seg(0, arr[i].second - n + 1, 1);
        }
        int mx = seg.get(0, n + 1);
//        cout << arr[i].first << ' ' << mx << '\n';
        if (mx <= n)
            upd[mx] = max(upd[mx], arr[i].first);
    }
    for (int i = n - 1; i >= 0; i--)
        upd[i] = max(upd[i], upd[i + 1]);
    for (int i = 1; i <= n; i++)
        cout << upd[i] << " \n"[i == n];
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

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


const int MAXN = 1e5 + 7;
int n, m;
int arr[MAXN];

struct SegmentTree {
    struct Node {
        vector<int> sorted;

        void merge(const Node &a, const Node &b) {
            sorted.resize(SZ(a.sorted) + SZ(b.sorted));
            std::merge(ALL(a.sorted), ALL(b.sorted), sorted.begin());
        }
    };

    Node tree[4 * MAXN];
    int N;

    SegmentTree(int *arr, int n) {
        N = 1;
        while (N < n)
            N *= 2;
        for (int i = 0; i < n; i++)
            tree[i + N].sorted = {arr[i]};
        for (int i = N - 1; i >= 1; i--)
            tree[i].merge(tree[2 * i], tree[2 * i + 1]);
    }

    int get(int v, int tl, int tr, int l, int r, int x, int y) {
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r) {
            int low = lower_bound(ALL(tree[v].sorted), x) - tree[v].sorted.begin();
            int high = lower_bound(ALL(tree[v].sorted), y) - tree[v].sorted.begin();
            return high - low;
        }
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, r, x, y) + get(v * 2 + 1, tm, tr, l, r, x, y);
    }

    int get(int l, int r, int x, int y) {
        return get(1, 0, N, l, r, x, y);
    }
};


int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    SegmentTree seg(arr, n);
    for (int i = 0; i < m; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        --l, y++;
        cout << seg.get(l, r, x, y) << '\n';
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

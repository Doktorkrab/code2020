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
struct SegmentTree {
    struct Node {
        int mx = 0;
        int suffix = 0;
        int prefix = 0;
        int suffix_x = 0;
        int prefix_x = 0;

        Node() = default;

        Node(const Node &a, const Node &b, int l, int m, int r) {
            mx = max(a.mx, b.mx);
            prefix = a.prefix;
            suffix = b.suffix;
            prefix_x = a.prefix_x;
            suffix_x = b.suffix_x;
            if (a.suffix_x < b.prefix_x) {
                mx = max(a.suffix + b.prefix, mx);
                if (a.suffix == m - l)
                    prefix = a.suffix + b.prefix;
                if (b.prefix == r - m)
                    suffix = a.suffix + b.prefix;
            }
        }
    };

    Node tree[4 * MAXN];
    int N;
    explicit SegmentTree(int sz){
        N = 1;
        while (N < sz)
            N *= 2;
    }
    void upd(int v, int tl, int tr, int pos, int x){
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1){
            tree[v].mx = tree[v].prefix = tree[v].suffix = 1;
            tree[v].suffix_x = tree[v].prefix_x = x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        tree[v] = Node(tree[v * 2], tree[v * 2 + 1], tl, tm, tr);
    }
    void upd(int pos, int x){
        upd(1, 0, N, pos, x);
    }
    int get() const {
        return tree[1].mx;
    }
};
int n, q;
int pos[MAXN];
int arr[MAXN];

int calc_ans() {
    int ans = 1;
    int now = 1;
    for (int i = 1; i < n; i++) {
        if (pos[i - 1] < pos[i])
            now++;
        else
            now = 1;
        ans = max(ans, now);
    }
    return n - ans;
}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    SegmentTree have(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
        pos[arr[i]] = i;
        have.upd(arr[i], i);
    }
    cout << n - have.get() << '\n';
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        swap(arr[x], arr[y]);
        pos[arr[x]] = x;
        pos[arr[y]] = y;
        have.upd(arr[x], x);
        have.upd(arr[y], y);
        cout << n - have.get() << '\n';
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

#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

const int MAX_MEM = 2e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
    char *res = mem + mpos;
    mpos += n;
    assert(mpos <= MAX_MEM);
    return (void *)res;
}
inline void operator delete ( void * ) { }
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
int r, c;
const int MAXN = 15005;
pair<int, int> have[MAXN];

struct SegmentTree {
    struct Node {
        int sum, push;
    };
    int N;
    vector<Node> nodes;

    SegmentTree(int sz) {
        N = 1;
        while (N < sz)
            N *= 2;
        nodes.resize(2 * N);
    }

    void push(int v, int tl, int tr) {
        if (nodes[v].push == -1)
            return;
        nodes[v].sum = (tr - tl) * nodes[v].push;
        if (v < N) {
            nodes[2 * v].push = nodes[v].push;
            nodes[2 * v + 1].push = nodes[v].push;
        }
        nodes[v].push = -1;
    }

    void push_seg(int v, int tl, int tr, int l, int r, int x) {
        push(v, tl, tr);
        if (r <= tl || tr <= l)
            return;
        if (l <= tl && tr <= r) {
            nodes[v].push = x;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        push_seg(v * 2, tl, tm, l, r, x);
        push_seg(v * 2 + 1, tm, tr, l, r, x);
        nodes[v].sum = nodes[2 * v].sum + nodes[2 * v + 1].sum;
    }

    int get(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (r <= tl || tr <= l)
            return 0;
        if (l <= tl && tr <= r)
            return nodes[v].sum;
        int tm = (tl + tr) / 2;
        int res = get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
        nodes[v].sum = nodes[2 * v].sum + nodes[2 * v + 1].sum;
        return res;
    }

    void push_seg(int l, int r, int x) {
        push_seg(1, 0, N, l, r, x);
    }

    int get(int l, int r) {
        return get(1, 0, N, l, r);
    }
};

vector<SegmentTree> sts;

bool check(int mm) {
    for (int i = 0; i < r; i++)
        sts[i].push_seg(0, c, 0);
    for (int i = 0; i < n; i++) {
        auto[x, y] = have[i];
        for (int j = 0; x - j >= 0 && j <= mm; j++) {
            int lft = (y - (mm - j));
            int rgt = (y + (mm - j) + 1);
            lft = max(0, lft);
            rgt = min(c, rgt);
            sts[x - j].push_seg(lft, rgt, 1);
        }
        for (int j = 0; x + j < r && j <= mm; j++) {
            int lft = (y - (mm - j));
            int rgt = (y + (mm - j) + 1);
            lft = max(0, lft);
            rgt = min(c, rgt);
            sts[x + j].push_seg(lft, rgt, 1);
        }
    }
    for (int i = 0; i < r; i++) {
//        cout << sts[i].get(0, c) << '\n';
        if (sts[i].get(0, c) != c)
            return false;
    }
    return true;
}

int solve() {
    if (!(cin >> r >> c >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> have[i].first >> have[i].second;
        have[i].first--;
        have[i].second--;
    }
    if (n == 1) {
        auto[a, b] = have[0];
        a++, b++;
        cout << max(abs(a - 1) + abs(b - 1),
                    max(abs(a - r) + abs(b - 1), max(abs(a - r) + abs(b - c), abs(a - 1) + abs(b - c)))) << '\n';
        return 0;
    }
    sts.resize(r, SegmentTree(c));
    int low = 0, high = r + c;
//    cout << check(3) << '\n';
//    return 0;
    while (high - low > 1) {
        int mid = (high + low) / 2;
        if (!check(mid))
            low = mid;
        else
            high = mid;
    }
    cout << high << '\n';

    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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

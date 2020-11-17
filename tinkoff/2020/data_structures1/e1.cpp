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
#define int ll
const int INF = 1e18;
int n, d;

struct SegmentTree {
    struct Node {
        vector<int> have;

        explicit Node() : have(d, -INF) {}
    };

    Node merge(const Node &a, const Node &b) {
        Node ret;
        for (int i = 0; i < d; i++)
            for (int j = 0; j < d; j++) {
                ret.have[(i + j) % d] = max(ret.have[(i + j) % d], a.have[i] + b.have[j]);
            }
        return ret;
    }

    vector<Node> have;
    int N = 1;

    SegmentTree(int sz, vector<vector<int>> &arr) {
        while (N < sz)
            N *= 2;
        have.resize(2 * N, Node());
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < 3; j++) {
//                cout << i << ' ' << j << ' ' << max(have[i + N].have[arr[i][j] % d], arr[i][j]) << ' ' << have[i + N].have[arr[i][j] % d] << '\n';
                have[i + N].have[arr[i][j] % d] = max(have[i + N].have[arr[i][j] % d], arr[i][j]);
            }}
        for (int i = N - 1; i >= 1; i--)
            have[i] = merge(have[2 * i], have[2 * i + 1]);
    }

    Node get(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l){
            auto ret = Node();
            ret.have[0] = 0;
            return ret;
        }
        if (l <= tl && tr <= r) {
//            cout << l << ' ' << r << ' ' << tl << ' ' << tr << '\n';
            return have[v];
        }
        int tm = (tl + tr) / 2;
        return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }
    Node get(int l, int r){
        return get(1, 0, N, l, r);
    }
};

int solve() {
    if (!(cin >> n >> d))
        return 1;
    vector<vector<int>> arr(n, vector<int>(3));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 3; j++)
            cin >> arr[i][j];
    }
    SegmentTree st(n, arr);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        cout << max(-1LL, st.get(l - 1, r).have[0]) << '\n';
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
//#ifdef LOCAL
//        cout << "------------------------------\n";
//#endif
    }
}

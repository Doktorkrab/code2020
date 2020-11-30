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
const int INF = 1e9 + 239;
int n;
int p[MAXN];
int arr[MAXN];
set<int> l;
set<int> r;
set<pair<int, pair<int, int>>> mins;
struct SegmentTree {
    int tree[4 * MAXN]{};
    int N = 1;
    SegmentTree() = default;
    SegmentTree(int sz, const int *a) {
        while (N < sz)
            N *= 2;
        for (int i = 0; i < sz; i++)
            tree[i + N] = a[i];
        for (int i = N - 1; i >= 1; i--)
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l)
            return INF;
        if (l <= tl && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }
    int get(int l, int r){
        return get(1, 0, N, l, r);
    }
};
SegmentTree st;

void split(int x){
    int ll = (*prev(l.upper_bound(x)));
    int rr = (*r.upper_bound(x));
    int mn = st.get(ll, rr);
    mins.erase({mn, {ll, rr}});
    if (x + 1 == n || x + 1 >= rr)
        r.erase(rr);
    else {
        l.insert(x + 1);
        mins.insert({st.get(x + 1, rr), {x + 1, rr}});
    }
    if (x == 0 || ll >= x)
        l.erase(ll);
    else {
        r.insert(x);
        mins.insert({st.get(ll, x), {ll, x}});
    }
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    st = SegmentTree(n, arr);
    l.clear();
    r.clear();
    mins.clear();
    l.insert(0);
    r.insert(n);
    mins.insert({st.get(0, n), {0, n}});
    for (int i = 0; i + 1 < n; i++){
        split(p[i]);
        auto [mn, brd] = (*mins.rbegin());
        cout << brd.first + 1 << ' ' << brd.second << '\n';
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

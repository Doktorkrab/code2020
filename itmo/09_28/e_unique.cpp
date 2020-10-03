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
 
int n, m, k;
const int MAXN = 1e5 + 7;
struct Node{
    int x, extra = 0;
};

struct SegmentTree{
    Node st[4 * MAXN];
    int N;
    SegmentTree(int n){
        N = 1;
        while (N < n)
            N *= 2;
        for (int i = 0; i <= 2 * N; i++)
            st[i].extra = -1;
    }
    void push(int v, int l, int r){
        if (st[v].extra == -1)
            return;
        st[v].x = (r - l) * st[v].extra;
        if (v >= N)
            return;
        st[2 * v].extra = st[2 * v + 1].extra = st[v].extra;
        st[v].extra = -1;
    }
    void pull(int v){
        st[v].x = st[2 * v].x + st[2 * v + 1].x;
    }
    
    int get(int v, int tl, int tr, int l, int r){
        push(v, tl, tr);
        //cout << v << ' ' << tl + 1 << ' ' << tr << ' ' << l + 1 << ' ' << r << ' ' << st[v].x << '\n';
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r){
            return st[v].x;
        }
        int tm = (tl + tr) / 2;
        int ret = get(2 * v, tl, tm, l, r) + get(2 * v + 1, tm, tr, l, r);
        pull(v);
        return ret;
    }
    int get(int l, int r){
        return get(1, 0, N, l, r);
    }

    void upd(int v, int tl, int tr, int l, int r, int x){
        push(v, tl, tr);
        if (tr <= l || r <= tl)
            return;
        if (l <= tl && tr <= r){
            st[v].extra = x;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, x);
        upd(v * 2 + 1, tm, tr, l, r, x);
        pull(v);
    }

    void upd(int l, int r, int x){
        upd(1, 0, N, l, r, x);
    }

};
struct Query{
    int l, r, x;
    bool operator<(const Query& oth) const {
        return x < oth.x;
    }
};

Query queries[MAXN];
const int MOD = 1e9 + 7;
int bp(int a, int b){
    int res = 1;
    for (; b > 0; b >>= 1){
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
    }
    return res;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    SegmentTree seg(n);
    for (int i = 0; i < m; i++){
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        queries[i] = {l, r, x};
    }
    sort(queries, queries + m);
    ll ans = 1;
    //cout << seg.get(0, 1) << '\n';
    //seg.upd(0, 1, 1);
    //cout << seg.get(0, 1) << '\n';
    //return 0;
    for (int i = 0; i < m; i++){
        auto [l, r, x] = queries[i];
        int cnt = (r - l) - seg.get(l, r);
        //cout << l + 1 << ' ' << r << ' ' << cnt << '\n';
        seg.upd(l, r, 1);
        //if (cnt == 0)
            //continue;
        //cout << (bp(x, cnt) + MOD - bp(x - 1, cnt)) % MOD << '\n';
        ans = ans * ((bp(x, cnt) + MOD - bp(x - 1, cnt)) % MOD) % MOD;
    }
    cout << ans * (bp(k, n - seg.get(0, n))) % MOD << '\n';
    return 0;
}
 
signed main() {
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        //cout << "------------------------------\n";
#endif
    }
}

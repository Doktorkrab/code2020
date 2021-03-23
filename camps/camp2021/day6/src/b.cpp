#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;

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
//const ull MOD = 1e9 + 7;
const ull MOD = 1566566543;
const ull BASE = 239;

ull bases[MAXN];

inline ull add(ull a, ull b){
    return (a % MOD + b % MOD + MOD) % MOD;
}
inline ull mul(ull a, ull b){
    return (a * b) % MOD;
}

template <int MAXSZ>
struct SegmentTree{
    struct Node{
        ull x = 0, push = 0;
        ull cnt = 0;
        Node() = default;
        Node(ull x, ull cnt) : x(x), cnt(cnt) {}
    };
    Node nodes[MAXSZ];
    int N;
    explicit SegmentTree(int sz){
        N = 1;
        while (N < sz)
            N *= 2;
        fill(nodes, nodes + 2 * N, Node(MOD, 0));
        for (int i = 0; i < sz; i++)
            nodes[i + N].cnt = 1;
        for (int i = N - 1; i >= 1; i--)
            nodes[i] = merge(nodes[2 * i], nodes[2 * i + 1]);
     }
    void push(int v, int l, int r){
        nodes[v].x = add(nodes[v].x, nodes[v].push);
        if (v < N) {
            nodes[2 * v].push = add(nodes[2 * v].push, nodes[v].push);
            nodes[2 * v + 1].push = add(nodes[2 * v + 1].push, nodes[v].push);
        }
        nodes[v].push = 0;
    }
    Node merge(const Node& a, const Node& b){
        Node c;
        c.x = min(a.x, b.x);
        if (a.x == c.x)
            c.cnt += a.cnt;
        if (b.x == c.x)
            c.cnt += b.cnt;
        return c;
    }
    void push_seg(int v, int tl, int tr, int l, int r, ull x){
        push(v, tl, tr);
        if (r <= tl || tr <= l)
            return;
        if (l <= tl && tr <= r){
            nodes[v].push = add(nodes[v].push, x);
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        push_seg(v * 2, tl, tm, l, r, x);
        push_seg(v * 2 + 1, tm, tr, l, r, x);
        nodes[v] = merge(nodes[2 * v], nodes[2 * v + 1]);
    }
    Node get(int v, int tl, int tr, int l, int r){
        push(v, tl, tr);
        if (r <= tl || tr <= l)
            return Node(TMAX(ull), 0);
        if (l <= tl && tr <= r)
            return nodes[v];
        int tm = (tl + tr) / 2;
        auto res = merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        nodes[v] = merge(nodes[2 * v], nodes[2 * v + 1]);
        return res;
    }
    void push_seg(int l, int r, ull what){
        push_seg(1, 0, N, l, r, what);
    }

    Node get(int l, int r){
        return get(1, 0, N, l, r);
    }
};
mt19937 rnd(239);
int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < MAXN; i++)
        bases[i] = rnd() % MOD;
    SegmentTree<4 * MAXN> st(n);
//    cout << "ready\n";
    for (int i = 0; i < q; i++){
        int type, l, r;
        cin >> type >> l >> r;
        --l;
        if (type == 2){
            auto res = st.get(l, r);
//            cout << res.x << ' ' << res.cnt << '\n';
            cout << (res.cnt >= (r - l)) << '\n';
        }
        else {
            int x;
            cin >> x;
            st.push_seg(l, r, bases[x]);
        }
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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

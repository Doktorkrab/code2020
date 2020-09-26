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
 
int n;
const int MAXN = 5e4 + 7;
const int MAXLOG = 15;


template<int (*F)(int, int)>
struct Sparse{
    int sparse[MAXLOG][MAXN];
    int logs[MAXN];
    Sparse () {}
    void build(int* arr, int n){
        for (int i = 0; i < MAXLOG; i++)
            for (int j = 0; j < MAXN; j++)
                sparse[i][j] = 0;
        for (int i = 0; i < n; i++)
            sparse[0][i] = arr[i];
        for (int log = 1; log < MAXLOG; log++)
            for (int i = 0; i + (1 << log) <= n; i++)
                sparse[log][i] = F(sparse[log - 1][i], sparse[log - 1][i + (1 << (log - 1))]);
        logs[1] = 0;
        for (int i = 2; i < MAXN; i++)
            logs[i] = logs[i / 2] + 1;
    }
    ll get(int l, int r){
        if (l >= r)
            return 0;
        int log = logs[r - l];
        return F(sparse[log][l], sparse[log][r - (1 << log)]);
    }
};
template<typename A>
A _max(A a, A b){
    if (a > b)
        return a;
    return b;
}
struct Node{
    ll max = LONG_LONG_MIN;
    int pos = 1e9+7;
    Node () {}
    Node(ll m, int p) : max(m), pos(p) {}
    bool operator<(const Node& oth) const {
        if (max == oth.max)
            return pos > oth.pos;
        return max < oth.max;
    }
};
Sparse<gcd> gcd_sparse;
Sparse<_max<int>> max_sparse;
int arr[MAXN];
int best_end[MAXN];
ll prefix[MAXN];
Node t[4 * MAXN];
int N;
void build(){
    N = 1;
    while (N <= n)
        N *= 2;
    for (int i = 0; i <= n; i++)
        t[i + N] = Node(prefix[i], i);
    for (int i = N - 1; i >= 1; i--)
        t[i] = max(t[2 * i], t[2 * i + 1]);
}

Node get(int v, int tl, int tr, int l, int r){
    if (r <= tl || tr <= l)
        return Node();
    // cout << v << ' ' << tl << ' ' << tr << ' ' << l << ' ' << r << ' ' << t[v].max << ' ' << t[v].pos << '\n';
    if (l <= tl && tr <= r)
        return t[v];
    int tm = (tl + tr) / 2;
    return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
}

ll relax(int start, int oldl){
    // cout << start << ' ' << oldl << '\n';
    if (oldl >= n)
        return 0;
    int l = oldl + 1, r = n + 1;
    int have = gcd_sparse.get(start, oldl + 1);
    while (r - l > 1){
        int m = (l + r) / 2;
        if (gcd_sparse.get(start, m) == have)
            l = m;
        else
            r = m;
    }
    // cout << l << ' ' << r << '\n';
    // cout << gcd_sparse.get(start, l) << ' ' << gcd_sparse.get(start, r) << '\n';
    Node tt = get(1, 0, N, start, r);
    int ans_r = tt.pos;
    // ass(start <= ans_r);
    // cout << ans_r << '\n'
    ll here = have * (prefix[ans_r] - prefix[start] - max_sparse.get(start, ans_r));
    cout << start + 1 << ' ' << l << ' ' << tt.max << ' ' << ans_r << ' ' << here << '\n';
    // exit(0);
    // cout << start << ' ' << ans_r << ' ' << here << "\n";
    return max(here, relax(start, l));
}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    gcd_sparse.build(arr, n);
    max_sparse.build(arr, n);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
    build();
    ll best = 0;
    for (int i = 0; i < n; i++){
        ll tmp = relax(i, i + 1);
        cout << i + 1 << ' ' << tmp << '\n';
        best = max(best, tmp);
    }
    cout << best << '\n';
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
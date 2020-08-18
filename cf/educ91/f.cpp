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
 
struct Node{
    int val[4], len;
    Node () : len(0){
        for (int i = 0; i < 4; i++)
            val[i] = 0;
    }
};


const int MAXN = 5e5 + 7;
const int MOD = 998244353;
int have[MAXN];
Node st[4 * MAXN];

Node merge(const Node& a, const Node& b, int l, int r){
    Node c;
    int na = (a.len == 1 ? 0 : 1);
    int nb = (b.len == 1 ? 0 : 2);
    c.len = a.len + b.len;
    c.val[0] = (a.val[na] * b.val[nb]) % MOD;
    c.val[1] = (a.val[na] * b.val[3]) % MOD;
    c.val[2] = (a.val[3] * b.val[nb]) % MOD;
    c.val[3] = (a.val[3] * b.val[3]) % MOD;
    if (l != 1)
        return c;
    int choices = 19 - (10 * l + r);
    na = (a.len == 1 ? 2 : 0);
    nb = (b.len == 1 ? 1 : 0);
    c.val[na + nb] += (((a.val[0] * b.val[0]) % MOD) * choices) % MOD;
    c.val[na + nb] %= MOD;
    c.val[1 + na] += (((a.val[0] * b.val[1]) % MOD) * choices) % MOD;
    c.val[1 + na] %= MOD;
    c.val[2 + nb] += (((a.val[2] * b.val[0]) % MOD) * choices) % MOD;
    c.val[2 + nb] %= MOD;
    c.val[3] += (((a.val[2] * b.val[1]) % MOD) * choices) % MOD;
    c.val[3] %= MOD;
    return c;
}

void build(int v, int l, int r){
    st[v].len = r - l;
    if (st[v].len == 1){
        st[v].val[0] = 1;
        st[v].val[3] = have[l] + 1;
        return; 
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    st[v] = merge(st[v * 2], st[v * 2 + 1], have[m - 1], have[m]);
}

void upd(int v, int l, int r, int pos, int x){
    if (r - l == 1){
        have[l] = x;
        st[v].val[3] = have[l] + 1;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m)
        upd(v * 2, l, m, pos, x);
    else
        upd(v * 2 + 1, m, r, pos, x);
    st[v] = merge(st[2 * v], st[2 * v + 1], have[m - 1], have[m]);
}

int n, m;
string inp;

 
int solve() {
    if (!(cin >> n >> m >> inp))
        return 1;
    for (int i = 0; i < n; i++)
        have[i] = inp[i] - '0';
    fill(st, st + 4 * n, Node());
    build(1, 0, n);
    // cout << st[1].val[3] << '\n';
    for (int i = 0; i < m; i++){
        int x, v;
        cin >> x >> v;
        --x;
        upd(1, 0, n, x, v);
        cout << st[1].val[3] << '\n';
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
// #ifdef LOCAL
//         cout << "------------------------------\n";
// #endif
    }
}
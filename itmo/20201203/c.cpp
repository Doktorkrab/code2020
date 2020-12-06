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
const ll INF = 1e18;
const ll shift = 1e5 + 7;
struct Line{
    ll k = 0, b = -INF, index = -1;
    Line() = default;
    ll operator()(ll x) const{
        return 1LL * k * (x - shift) + b;
    }
    bool operator< (const Line& x){
        return tie(k, b) < tie(x.k, x.b);
    }
};
const int MAXN = 3e5;

Line lines[MAXN];
Line *tree;
void add(int v, int tl, int tr, Line x){
    int tm = (tl + tr) / 2;
    bool mid = x(tm) > tree[v](tm);
    bool left = x(tl) > tree[v](tl);
    if (mid)
        swap(x, tree[v]);
    if (tr - tl == 1)
        return;
    if (left != mid)
        add(v * 2, tl, tm, x);
    else
        add(v * 2 + 1, tm, tr, x);
}
Line get(int v, int tl, int tr, ll x){
    if (tr - tl == 1)
        return tree[v];
    int tm = (tl + tr) / 2;
    if (x < tm) {
        Line ret = get(v * 2, tl, tm, x);
        if (ret(x) > tree[v](x))
            return ret;
        return tree[v];
    }
    Line ret = get(v * 2 + 1, tm, tr, x);
    if (ret(x) > tree[v](x))
        return ret;
    return tree[v];
}
void push(const Line& x){
    add(1, 0, MAXN, x);
}
Line get(ll x){
    return get(1, 0, MAXN, x);
}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> lines[i].k >> lines[i].b;
        lines[i].k *= -1;
        lines[i].index = i;
    }
    for (int i = 0; i < n; i++)
        push(lines[i]);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        ll x;
        cin >> x;
        cout << get(x + shift).index + 1 << " \n"[i + 1 == q];
    }
    return 0;
}

signed main() {
    tree = new Line[4 * MAXN];
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
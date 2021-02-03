#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
//#define int ll

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

int n, a, b, c, m;
ll to_minus;
mt19937 rnd(1337);

int rec(int d, int alpha, int beta, int pos) {
    if (d == n) {
        pos -= to_minus;
        ll ans = 1LL * a * pos % m * pos % m;
        ans += (1LL * b * pos) % m;
        ans += c;
        return ans % m;
    }
    if (d % 2 == 0) {
        int a_nxt = pos * 2;
        int b_nxt = pos * 2 + 1;
        if (rnd() % 2)
            swap(a_nxt, b_nxt);
        int nxt = rec(d + 1, alpha, beta, a_nxt);
        alpha = max(alpha, nxt);
        int ans = nxt;
        if (alpha == beta)
            return beta;
        if (alpha > beta)
            return nxt;
        nxt = rec(d + 1, alpha, beta, b_nxt);
        nxt = max(alpha, nxt);
        if (alpha == beta)
            return beta;
        return max(nxt, ans);
    } else {
        int a_nxt = pos * 2;
        int b_nxt = pos * 2 + 1;
        if (rnd() % 2)
            swap(a_nxt, b_nxt);
        int nxt = rec(d + 1, alpha, beta, a_nxt);
        beta = min(beta, nxt);
        int ans = nxt;
        if (alpha == beta)
            return beta;
        if (alpha > beta)
            return nxt;
        nxt = rec(d + 1, alpha, beta, b_nxt);
        nxt = min(beta, nxt);
        if (alpha == beta)
            return beta;
        return min(nxt, ans);
    }
}

int solve() {
    if (!(cin >> n >> a >> b >> c >> m))
        return 1;

    to_minus = (1LL << n);
    cout << rec(0, 0, m, 1) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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

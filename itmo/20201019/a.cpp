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

int n, m, k;
const int MAXN = 1005;
const int MOD = 1e9 + 7;
const int REV = 500000004;
map<int, int> h, w;

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int add(int a, int b) {
    int ret = (a + b) % MOD;
    if (ret < 0)
        ret += MOD;
    return ret;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;

    h[n - 1] = 1;
    w[m] = 1;
    for (int i = 0; i < k; i++) {
        char x;
        int a, b;
        cin >> x >> a >> b;
        --a;
        if (x == 'R') {
            if (!h.count(a))
                h[a] = 1;
            h[a] = (1LL * h[a] * b) % MOD;
        } else {
            if (!w.count(a + 1))
                w[a + 1] = 1;
            w[a + 1] = (1LL * w[a + 1] * b) % MOD;
        }
    }
    int lst = 0;
    int ans = 0;
    for (auto[a, b] : w) {
//        cout << a << ' ' << b << '\n';
        ans = add(ans, mul(add(mul(n, a), mul(m, mul(n, mul(n - 1, REV)))), b));
    }
//    cout << ans << '\n';
    for (auto[a, b] : h) {
        ans += mul(b, add(mul(m, mul(m, a)), mul(m, mul(m + 1, REV))));
//        cout << add(mul(m, mul(m, a)), mul(m, mul(m + 1, REV))) << '\n';
//        cout << "!!" << ans << '\n';
        ans %= MOD;
        int lst1 = 1;
        for (auto[a1, b1] : w) {
            int beg = lst1, end = a1 - 1;
            if (beg <= end) {
                ans += mul(a - lst, add(-mul(REV, mul(beg, (beg - 1))), +(mul(REV, mul(end, end + 1)))));
                ans %= MOD;
//                cout << "???" << mul(REV, mul(beg, (beg - 1))) << ' ' << mul(REV, mul(end, end + 1)) << '\n';
//                cout << a - lst << ' ' << add(-mul(REV, mul(beg, (beg - 1))), +(mul(REV, mul(end, end + 1)))) << '\n';
//                cout << "!!!" << ans << '\n';
            }
            beg = lst, end = a - 1;
            if (beg <= end) {
                int cnt = a1 - lst1;
                int end1 = mul(end, mul(end + 1, REV));
                int beg1 = mul(beg, mul(beg - 1, REV));
                ans = add(ans, mul(m, mul(cnt, end1 - beg1)));
//                cout << mul(cnt, end1 - beg1) << ' ' << cnt << ' ' << beg1 << ' ' << end1 << '\n';
            }
            int pos = add(mul(m, a), a1);
//            cout << ans << ' ' << mul(pos, b + b1) << '\n';
            ans = add(ans, -mul(pos, (b + b1)));
            ans = add(ans, mul(pos, mul(b, b1)));
//            cout << mul(pos, mul(b, b1)) << '\n';
            lst1 = a1 + 1;
        }
        lst = a + 1;
    }
    cout << ans << '\n';
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

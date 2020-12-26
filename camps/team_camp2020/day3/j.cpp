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

const int MAXN = 2e5 + 7;
const int MOD = 998244353;
int n;
int arr[2 * MAXN];
int fact[2 * MAXN];

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

int bp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int inv(int a) {
    return bp(a, MOD - 2);
}

int c(int n, int k) {
//    cerr << fact[n] << ' ' << fact[k] << ' ' << fact[n - k] << '\n';
    return mul(fact[n], inv(mul(fact[k], fact[n - k])));
}

int solve() {
    if (!(cin >> n))
        return 1;
    n *= 2;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n / 2);
    sort(arr + n / 2, arr + n);
    reverse(arr + n / 2, arr + n);
    int ans = 0;
    for (int i = 0; i < n / 2; i++) {
        ans = add(ans, abs(arr[i] - arr[i + n / 2]) % MOD);
//        cerr << ans << '\n';
    }
    fact[0] = 1;
    for (int i = 1; i < 2 * MAXN; i++)
        fact[i] = mul(fact[i - 1], i);
//    cerr << c(n, n / 2) << ' ' << ans << '\n';
    cout << mul(c(n, n / 2), ans) << '\n';
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

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

int n, k;
const int MAXN = 2e6 + 7;
const int MOD = 1e9 + 7;
int sum[MAXN];
int min_d[MAXN];
int primes[MAXN];
int fact[MAXN];
int rev_fact[MAXN];
int cnt[MAXN];
int pnt = 0;

inline int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

inline int add(int a, int b) {
    return (a + b) % MOD;
}

int bp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b /= 2;
    }
    return res;
}

int rev(int a) {
    return bp(a, MOD - 2);
}

void prepare_fact() {
    fact[0] = 1;
    rev_fact[0] = 1;
    for (int i = 1; i <= n + k; i++) {
        fact[i] = mul(i, fact[i - 1]);
        rev_fact[i] = rev(fact[i]);
    }
}

int c(int n, int k) {
    if (n < k)
        return 0;
    return mul(fact[n], mul(rev_fact[k], rev_fact[n - k]));
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    prepare_fact();
    pnt = 0;
    sum[1] = 0;
//    cerr << "her\n";
    for (int i = 2; i <= n; i++) {
        if (sum[i] == 0) {
            sum[i] = 1;
            primes[pnt++] = i;
            min_d[i] = i;
            cnt[i] = 1;
        }
        for (int j = 0; j < pnt && primes[j] <= min_d[i] && 1LL * i * primes[j] <= n; j++) {
            if (min_d[i] == primes[j])
                cnt[i * primes[j]] = cnt[i];
            else
                cnt[i * primes[j]] = cnt[i] + 1;
            sum[i * primes[j]] = sum[i] + 1;
            min_d[i * primes[j]] = primes[j];
        }
    }
    int ans = 0;
    vector<int> kek(n + 1);
    for (int d = 1; d <= n; d++) {
        for (int x = d; x <= n; x += d) {
            kek[x] += c(pnt - cnt[d] + (k - sum[d]), k - sum[d]);
            ans = add(ans, mul(x, c(pnt - cnt[d] + (k - sum[d]), k - sum[d])));
        }
    }
//    for (int i = 1; i <= n; i++)
//        cout << kek[i] << ' ' << i << '\n';
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

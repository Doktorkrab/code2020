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

ll n;
mt19937 rnd(239);

ll get_rand(ll a, ll b) {
    return a + (rnd() % (b - a + 1));
}

ll gcd(ll a, ll b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

ll pow_fast(ll a, ll b, ll mod) {
    ll res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1)
            res = ((__int128) res * a) % mod;
        a = ((__int128) a * a) % mod;
    }
    return res;
}

bool miller_rabin(ll x) {
    if (x == 2)
        return true;
    if (x == 1)
        return false;
    assert(x > 2);
    ll m = x - 1;
    ll s = 0;
    while (m % 2 == 0) {
        s++;
        m /= 2;
    }
    for (int i = 0; i < 50; i++) {
        ll t = get_rand(2, x - 1);
        ll cur = pow_fast(t, m, x);
        if (cur == 1 || cur == x - 1)
            continue;
        bool good = false;
        for (int j = 0; j < s - 1; j++) {
            cur = pow_fast(cur, 2, x);
            if (cur == 1)
                return false;
            if (cur == x - 1) {
                good = true;
                break;
            }
        }
        if (!good)
            return false;
    }
    return true;
}

bool check(int x) {
    if (x == 1)
        return false;
    for (int f = 2; f * f <= x; f++)
        if (x % f == 0)
            return false;
    return true;
}

int solve() {
    if (!(cin >> n))
        return 1;
    cout << (miller_rabin(n) ? "YES\n" : "NO\n");
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
#else
    freopen("again.in", "r", stdin);
    freopen("again.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}

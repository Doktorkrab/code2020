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


int solve() {
    if (!(cin >> n))
        return 1;
    ll x = sqrtl(n) + 100;
    vector<bool> is_prime(x + 1, true);
    unordered_map<ll, int> cnt;
    int now = 1;
    for (ll i = 2; i <= x; i++) {
        if (!is_prime[i])
            continue;
        cnt[i] = now++;
        for (ll j = 1LL * i * i; j <= x; j += i)
            is_prime[j] = false;
    }
    x = n;
    int ans = 0;
    for (ll f = 2; f * f <= x; f++) {
        while (n % f == 0) {
            ans ^= cnt[f];
            n /= f;
        }
    }
    if (n > 1 && cnt.count(n)) {
        ans ^= cnt[n];
        n = 1;
    }
    if (n == 1 && ans == 0)
        cout << "Vasya\n";
    else
        cout << "David\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("m.in", "r", stdin);
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

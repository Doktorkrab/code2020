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

ll n, m;
vector<ll> fact;

void factor(ll x) {
    fact.clear();
    ll was = x;

    for (ll f = 2; f * f <= was; f++) {
        if (x % f != 0)
            continue;
        fact.push_back(f);
        while (x % f == 0) {
            x /= f;
        }
    }
    if (x > 1)
        fact.push_back(x);
}

ll ans = 0;

void rec(int pos, int minus_one, ll have) {
    if (pos == SZ(fact))
        return;
    rec(pos + 1, minus_one, have);
    have *= fact[pos];
    minus_one *= -1;
    if (have != 1)
        ans -= minus_one * (n / have);
    rec(pos + 1, minus_one, have);
}


int solve() {
    if (!(cin >> n >> m))
        return 1;
    ans = n;
    factor(m);
    rec(0, -1, 1);
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

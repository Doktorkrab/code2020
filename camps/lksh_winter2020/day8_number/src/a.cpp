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

int l, r;
const int MAXN = 1e8 + 7;
vector<int> primes;
int d[MAXN];

int solve() {
    if (!(cin >> l >> r))
        return 1;
    ll ans = 0;
    for (int i = 2; i <= r; i++) {
        if (d[i] == 0) {
            d[i] = i;
            primes.push_back(i);
        }
        if (l <= i)
            ans += d[i];
        for (int x : primes) {
            if (x > d[i] || x * i > r)
                break;
            d[x * i] = x;
        }
    }
    cout << ans << '\n';
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

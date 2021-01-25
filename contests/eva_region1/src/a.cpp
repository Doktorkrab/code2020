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

ll a, b;

pair<ll, ll> stupid() {
    for (int i = 2; i <= 1000; i++)
        for (int j = i + 1; j <= 1000; j++)
            if (a % i == b % j && j % i == 0) {
                return {i, j};
            }
    return {-1, -1};
}

bool check(ll i, ll j) {
    return a % i == b % j && j % i == 0;
}

ll find_min(ll x) {
    for (ll f = 2; f * f <= x; f++)
        if (x % f == 0)
            return f;
    return x;
}

pair<ll, ll> smart() {
    if (a == 1 && b == 1)
        return {2, 4};
    if (a == 2 && b == 2)
        return {3, 6};
    if (a == 3 && b == 3)
        return {4, 8};
    if (a == b) {
        if (a % 4 == 2 || a % 4 == 3)
            return {2, 2 * find_min(a / 2)};
        return {2, 4};
    }
    ll x = b - a;
    vector<ll> have;
//    cout << a << ' ' << b << " " << x << '\n';
    for (ll f = 2; f * f <= x; f++) {
//        cout << x << ' ' << f << '\n';
        int was = 0;
        while (x % f == 0) {
            x /= f;
            was++;
        }
        if (was > 0) {
            have.push_back(f);
        }
    }
    if (x > 1)
        have.push_back(x);
    sort(ALL(have));
    vector<ll> have1;
    pair<ll, ll> best = {TMAX(ll), TMAX(ll)};
    for (ll x : have) {
        ll n = a / x;
        ll m = (b - a) / x + n;
//        cout << x << ' ' << m << ' ' << b - x * m << " " << a - x * n << '\n';
        if (m != 1)
            best = min(best, {x, find_min(m) * x});
    }
    if (best.first == TMAX(ll))
        return {-1, -1};
    return best;
}

int solve() {
    if (!(cin >> a >> b))
        return 1;
//    auto[x, y] = stupid();
    auto[x1, y1] = smart();
//    cout << x << ' ' << y << '\n';
    cout << x1 << ' ' << y1 << '\n';
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

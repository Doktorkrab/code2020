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

int A, B, c;

struct GCD_result {
    ll g, x0, y0;
};

GCD_result gcd(int a, int b) {
    if (a == 0)
        return {b, 0, 1};
    auto[g, x0, y0] = gcd(b % a, a);
    return {g, y0 - 1LL * (b / a) * x0, x0};
}

int solve() {
    if (!(cin >> A >> B >> c))
        return 1;

    auto[g, x, y] = gcd(A, B);
    if (c % g != 0) {
        cout << "Impossible\n";
        return 0;
    }
    x *= c / g;
    y *= c / g;
    ll k = x / (B / g);
    if (x < 0)
        k = (x - (B / g) + 1) / (B / g);
    x -= k * (B / g);
    y += k * (A / g);

    cout << x << ' ' << y << '\n';

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

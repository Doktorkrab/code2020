#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

#define int ll
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

int n, m;


int solve() {
    if (!(cin >> n >> m))
        return 1;
    int l = 0, r = 1e18;
    while (r - l > 1) {
        ll mid = l + (r - l) / 2;
//        cout << m + mid * (mid + 1) / 2 - n * mid << ' ' << mid << '\n';
        if (n - mid <= 0 || m + mid * (mid - 1) / 2 <= n * mid)
            r = mid;
        else
            l = mid;
    }
    if (m + r * (r - 1) / 2 - n * r <= 0)
        cout << "Impostors\n";
    else
        cout << "Crewmates\n";

    cout << r << '\n';
    return 0;
}

signed main() {
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

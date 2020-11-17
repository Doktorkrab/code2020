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
#define int ll

int n;
int ans;

void upd(int x) {
    if (x == 0) {
        return;
    }
    int kek = n / (2 * x + 1) * 2;
    if (n % x == 0) {
        ans = min(ans, abs(x - n / x));
    }
    if (n % (2 * x + 1) == 0) {
        ans = min(ans, abs(kek - (x + 1)));
    }
    if (n % (2 * x + 1) == x) {
        ans = min(ans, abs(kek + 1 - (x + 1)));
    }
    if (n % (2 * x + 1) == x + 1) {
        ans = min(ans, abs(kek + 1 - (x + 1)));
    }
}

int solve() {
    if (!(cin >> n))
        return 1;
    ans = n;
    for (int i = 1; i <= n; i++) {
        upd(i);
//        cout << i << ' ' << ans << '\n';
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

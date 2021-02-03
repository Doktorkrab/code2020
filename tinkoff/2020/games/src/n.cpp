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

int n;


int solve() {
    if (!(cin >> n))
        return 1;
    int x = 0;
    for (int i = 0; i < n; i++) {
        int y;
        cin >> y;
        if (y % 4 == 0)
            x ^= y - 1;
        else if (y % 4 == 3)
            x ^= y + 1;
        else
            x ^= y;
    }
    if (x)
        cout << "FIRST\n";
    else
        cout << "SECOND\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("n.in", "r", stdin);
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

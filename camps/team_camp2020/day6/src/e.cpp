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

int a, b, c, d;


int solve() {
    if (!(cin >> a))
        return 1;
    cin >> b >> c >> d;
    if (c == 1 && d == 1) {
        cout << "YES\n";
        return 0;
    }
    if (a == 1 && b == 1) {
        cout << "NO\n";
        cout << "0\n";
        return 0;
    }
    if (b == 1 && d != 1) {
        cout << "NO\n";
        cout << 2 << '\n';
        cout << "1 0\n";
        cout << "-1 0\n";
        return 0;
    }
    if (a == 1 && c != 1) {
        cout << "NO\n";
        cout << 2 << '\n';
        cout << "0 1\n";
        cout << "0 -1\n";
        return 0;
    }
    if (a != 1 && b != 1 && (c == 1 || d == 1)) {
        cout << "NO\n";
        cout << 4 << '\n';
        if (c == 1) {
            cout << "0 1\n";
            cout << "0 -1\n";
            cout << "1 1\n";
            cout << "-1 0\n";
        } else {
            cout << "1 1\n";
            cout << "0 -1\n";
            cout << "0 1\n";
            cout << "-1 0\n";
        }
        return 0;
    }
    if (c < a) {
        cout << "NO\n";
        cout << 4 << '\n';
        cout << "0 -1\n";
        cout << "0 1\n";
        cout << a - 1 << " 0\n";
        cout << "-1 0\n";
        return 0;
    } else if (d < b) {
        cout << "NO\n";
        cout << 4 << '\n';
        cout << "-1 0\n";
        cout << "1 0\n";
        cout << "0 " << b - 1 << '\n';
        cout << "0 -1\n";
        return 0;
    } else {
        cout << "YES\n";
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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
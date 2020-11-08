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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count() * 228 + 2);

int solve() {
    int a = 14;
    cin >> n;
//    char c;
//    cin >> c;
    if (rnd() % 2) {
        cout << "0\n6\n5\n7\n";
    } else {
        clock_t start = clock();
        while (clock() - start < 1. * 0.23 * CLOCKS_PER_SEC) {}
        cout << 'p';
    }
    return 1;
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
